#include "aux.h"
#include "malla.h"
#include "esfera.h"

Esfera::Esfera(int num_vert_perfil, int num_instancias_perf, float radio)
{
   std::vector<Tupla3f> p={};
   ejeRevolucion = EJEY;
   // p.push_back({0, -radio, 0});

   for (int i = 0; i < num_vert_perfil; i++)
   {
      p.push_back({sqrt(radio * radio - (2 * radio * (i * 1.0 / num_vert_perfil) - radio) * (2 * radio * (i * 1.0 / num_vert_perfil) - radio)), 2 * radio * (i * 1.0 / num_vert_perfil) - radio, 0});
   }
   p.push_back({0.0, radio, 0.0});

   ObjRevolucion::crearMalla(p, num_instancias_perf, 1, 1);
   asignarColores();
   calcular_normales();

}
