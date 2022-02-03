#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string &archivo, int num_instancias, bool tapa_sup, bool tapa_inf, eje ejeR)
{
   // completar ......(práctica 2)
   ply::read_vertices(archivo, perfil);
   ejeRevolucion = ejeR;

   crearMalla(perfil, num_instancias, tapa_sup, tapa_inf);

   asignarColores();
   calcular_normales();
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf, eje ejeR)
{
   perfil = archivo;
   ejeRevolucion = ejeR;

   crearMalla(perfil, num_instancias, tapa_sup, tapa_inf);
   asignarColores();
   calcular_normales();
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_sup, bool tapa_inf)
{
   float coorX, coorY, coorZ;

   float angulo;
   //muestra tabla vertices
   numInstancias = num_instancias;
   perfil = sentido(perfil_original);
   verticeTapaSuperior = tieneVerticeSuperior(perfil);
   verticeTapaInferior = tieneVerticeInferior(perfil);

   //Si tenemos algun vertice de tapa lo eliminamos del perfil y procedemos a la rotación si este vertice
   if (verticeTapaSuperior[0] != 1 && verticeTapaSuperior[1] != 1 && verticeTapaSuperior[2] != 1)
   {
      perfil.erase(perfil.end() - 1);
   }
   else
   {
      switch (ejeRevolucion)
      {
      case EJEX:
         verticeTapaSuperior = {perfil.back()[0], 0, 0};

         break;
      case EJEY:
         verticeTapaSuperior = {0, perfil.back()[1], 0};

         break;
      case EJEZ:
         verticeTapaSuperior = {0, 0, perfil.back()[2]};
         break;
      }
   }
   if (verticeTapaInferior[0] != 1 && verticeTapaInferior[1] != 1 && verticeTapaInferior[2] != 1)
   {
      perfil.erase(perfil.begin());
   }
   else
   {
      switch (ejeRevolucion)
      {
      case EJEX:
         verticeTapaInferior = {perfil.front()[0], 0, 0};

         break;
      case EJEY:
         verticeTapaInferior = {0, perfil.front()[1], 0};

         break;
      case EJEZ:
         verticeTapaInferior = {0, 0, perfil.front()[2]};
         break;
      }
   }

   //Añado primero los puntos
   //Divido toda la rotación dependiendo del numero de instacias que haya
   for (int i = 0; i < num_instancias; i++) // Para cada angulo
   {
      angulo = (2 * M_PI * i) / num_instancias;
      for (int j = 0; j < perfil.size(); j++) // Todos los vertices que hay en un ángulo
      {
         switch (ejeRevolucion)
         {
         case EJEX:
            coorX = perfil[j][0];
            coorY = perfil[j][1] * cos(angulo) - perfil[j][2] * sin(angulo);
            coorZ = perfil[j][1] * sin(angulo) + perfil[j][2] * cos(angulo);
            break;
         case EJEY:
            coorX = perfil[j][0] * cos(angulo) + perfil[j][2] * sin(angulo);
            coorY = perfil[j][1];
            coorZ = perfil[j][0] * -sin(angulo) + perfil[j][2] * cos(angulo);
            break;
         case EJEZ:
            coorX = perfil[j][0] * cos(angulo) - perfil[j][1] * sin(angulo);
            coorY = perfil[j][0] * sin(angulo) + perfil[j][1] * cos(angulo);
            coorZ = perfil[j][2];
            break;
         }

         v.push_back({coorX, coorY, coorZ}); //Añado el punto
      }
   }
   //Añado los triangulos
   int v1, v2, v3;
   for (int i = 0; i < num_instancias; i++) // Para cada angulo
   {
      for (int j = 0; j < perfil.size() - 1; j++) // Todos los vertices que hay en un ángulo
      {
         if (i == (num_instancias - 1)) // este if lo hago para hacer la ultima cara
         {
            v1 = perfil.size() * i + j;
            v2 = j;
            v3 = v2 + 1;

            f.push_back({v1, v2, v3});
            //Creo el triangulo inferior y lo añado a la tabla de caras
            v2 = v2 + 1;
            v3 = v1 + 1;
            f.push_back({v1, v2, v3});
         }
         else
         {
            //Primero creo el triangulo superior y lo añado a la tabla de caraas
            v1 = perfil.size() * i + j;
            v2 = perfil.size() * (i + 1) + j;
            v3 = v2 + 1;

            f.push_back({v1, v2, v3});
            //Creo el triangulo inferior y lo añado a la tabla de caras
            v2 = v2 + 1;
            v3 = v1 + 1;
            f.push_back({v1, v2, v3});
         }
      }
   }

   //Creamos las tapas si se nos pide
   crearTapaInferior(num_instancias, tapa_inf);
   crearTapaSuperior(num_instancias, tapa_sup);
}

std::vector<Tupla3f> ObjRevolucion::sentido(std::vector<Tupla3f> perfilAntes)
{
   std::vector<Tupla3f> aux;
   switch (ejeRevolucion)
   {
   case EJEX:
      if (perfilAntes.front()[0] > perfilAntes.back()[0])
      {
         for (int i = perfilAntes.size() - 1; i >= 0; i--)
         {
            aux.push_back(perfilAntes[i]);
         }
         return aux;
      }
      else
      {
         return perfilAntes;
      }
   case EJEY:
      if (perfilAntes.front()[1] > perfilAntes.back()[1])
      {
         for (int i = perfilAntes.size() - 1; i >= 0; i--)
         {
            aux.push_back(perfilAntes[i]);
         }
         return aux;
      }
      else
      {
         return perfilAntes;
      }
      break;
   case EJEZ:
      if (perfilAntes.front()[2] > perfilAntes.back()[2])
      {
         for (int i = perfilAntes.size() - 1; i >= 0; i--)
         {
            aux.push_back(perfilAntes[i]);
         }
         return aux;
      }
      else
      {
         return perfilAntes;
      }
      break;
   }
}

Tupla3f ObjRevolucion::tieneVerticeSuperior(std::vector<Tupla3f> p)
{
   switch (ejeRevolucion)
   {
   case EJEX:
      if (p.back()[1] == 0 && p.back()[2] == 0)
      {
         return p.back();
      }
      else
      {
         return {1, 1, 1};
      }
      break;
   case EJEY:
      if (p.back()[0] == 0 && p.back()[2] == 0)
      {
         return p.back();
      }
      else
      {
         return {1, 1, 1};
      }
      break;
   case EJEZ:
      if (p.back()[0] == 0 && p.back()[1] == 0)
      {
         return p.back();
      }
      else
      {
         return {1, 1, 1};
      }
      break;
   }
}

void ObjRevolucion::crearTapaInferior(int num_instancias, bool tapa_inf)
{
   if (tapa_inf)
   {
      v.push_back(verticeTapaInferior);
      for (int i = 0; i < num_instancias; i++)
      {
         if (i == (num_instancias - 1)) //aqui es el ultimo perfil que tiene que hacer cara con el primero
         {
            f.push_back({0, perfil.size() * i, v.size() - 1});
         }
         else
         {

            f.push_back({perfil.size() * (i + 1), perfil.size() * i, v.size() - 1});
         }
      }
   }
}

Tupla3f ObjRevolucion::tieneVerticeInferior(std::vector<Tupla3f> p)
{
   switch (ejeRevolucion)
   {
   case EJEX:
      if (p.front()[1] == 0 && p.front()[2] == 0)
      {
         return p.front();
      }
      else
      {
         return {1, 1, 1};
      }
      break;
   case EJEY:
      if (p.front()[0] == 0 && p.front()[2] == 0)
      {
         return p.front();
      }
      else
      {
         return {1, 1, 1};
      }
      break;
   case EJEZ:
      if (p.front()[0] == 0 && p.front()[1] == 0)
      {
         return p.front();
      }
      else
      {
         return {1, 1, 1};
      }
      break;
   }
}

void ObjRevolucion::crearTapaSuperior(int num_instancias, bool tapa_sup)
{
   if (tapa_sup)
   {
      v.push_back(verticeTapaSuperior);
      for (int i = 0; i < num_instancias; i++)
      {
         if (i == (num_instancias - 1)) //aqui es el ultimo perfil que tiene que hacer cara con el primero
         {
            f.push_back({(perfil.size() * (i + 1)) - 1, perfil.size() - 1, v.size() - 1});
         }
         else
         {

            f.push_back({(perfil.size() * (i + 1)) - 1, (perfil.size() * (i + 2)) - 1, v.size() - 1});
         }
      }
   }
}

void ObjRevolucion::pintarConTapas(bool modo, bool ajedrez, bool alambre, bool solido, bool puntos, bool luz, bool tapas,bool seleccionado)
{
   int tamOriginal = f.size();
   int tamOriginalCaraPar = caraPar.size();
   int tamOriginalCaraImpar = caraImpar.size();
   if (tapas)
   {
      draw(modo, ajedrez, alambre, solido, puntos, luz,seleccionado,false);
   }
   else
   {
      f.resize(f.size() - 2 * numInstancias);
      caraImpar.resize(caraImpar.size() - numInstancias);
      caraPar.resize(caraPar.size() - numInstancias);
      draw(modo, ajedrez, alambre, solido, puntos, luz,seleccionado,false);
   }
   f.resize(tamOriginal);
   caraImpar.resize(tamOriginalCaraImpar);
   caraPar.resize(tamOriginalCaraPar);
}

// void ObjRevolucion::asignarPuntosTextura()
// {
// }
/*
      //mostrar tabla vertices
   for (int i = 0; i < v.size(); i++)
   {
      std::cout << "|" << v[i][0] << " " << v[i][1] << " " << v[i][2] << " |";
      std::cout << std::endl;
   }
   std::cout << std::endl;

      //mostrar tabla caras

   for (int i = 0; i < f.size(); i++)
   {
      std::cout << "|" << f[i][0] << " " << f[i][1] << " " << f[i][2] << " |";
      std::cout << std::endl;
   }
   std::cout << std::endl;
*/