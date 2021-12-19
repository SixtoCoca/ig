#include "aux.h"
#include "malla.h"
#include "cono.h"

Cono::Cono(int num_vert_perfil, int num_instancias_perf, float altura, float radio,eje ejeR)
{

   std::vector<Tupla3f> p = {};

   p.push_back({0, 0, 0});
   ejeRevolucion = ejeR;
   switch (ejeRevolucion)
   {
   case EJEX:
      for (int i = 0; i <= num_vert_perfil; i++)
      {
         p.push_back({altura * (1.0 * i / num_vert_perfil), radio - radio * (1.0 * i / num_vert_perfil), 0});
      }
      break;
   case EJEY:
      for (int i = 0; i < num_vert_perfil; i++)
      {
         p.push_back({radio - radio * (1.0 * i / num_vert_perfil), altura * (1.0 * i / num_vert_perfil), 0});
      }
      p.push_back({0.0, altura, 0.0});
      break;
   case EJEZ:
      for (int i = 0; i <= num_vert_perfil; i++)
      {
         p.push_back({0.0, radio - radio * (1.0 * i / num_vert_perfil),altura * (1.0 * i / num_vert_perfil)});
      }
      p.push_back({0.0, 0.0, altura});
      break;
   }

   ObjRevolucion::crearMalla(p, num_instancias_perf, 1, 1);
   asignarColores();
   calcular_normales();
}
