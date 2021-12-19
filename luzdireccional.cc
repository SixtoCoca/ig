#include "luzdireccional.h"

// *****************************************************************************
//
// Clase luzdireccional (práctica 3)
//
// *****************************************************************************

LuzDireccional::LuzDireccional(const Tupla3f &direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso)
{
   id = idLuzOpenGL;
   posicion[0] = direccion[0];
   posicion[1] = direccion[1];
   posicion[2] = direccion[2];
   posicion[3] = 0.0;
   origen = {direccion[0], direccion[1], direccion[2],0};

   alfa = abs(atan2f(direccion(0), direccion(2)));
   beta = asin(direccion(1) / sqrt(direccion.lengthSq()));

   this->colorAmbiente = colorAmbiente;
   this->colorEspecular = colorEspecular;
   this->colorDifuso = colorDifuso;
}

void LuzDireccional::variarAnguloAlfa(float incremento)
{
   alfa = alfa + incremento;
   if (alfa > M_PI*2.0 ){
      alfa -= M_PI*2.0;

   } else if (alfa < 0){
      alfa += M_PI*2.0;
   }
   std::cout << alfa*180/M_PI << "º <--- angulo alfa" << std::endl;
   
   posicion[0] = sin(alfa) * cos(beta) * sqrt(origen.lengthSq());
   posicion[1] = sin(beta) * sqrt(origen.lengthSq());
   posicion[2] = cos(alfa) * cos(beta) * sqrt(origen.lengthSq());
}
void LuzDireccional::variarAnguloBeta(float incremento)
{
   beta = (int)(beta + incremento) % 360;

   std::cout << beta << "<--- angulo beta" << std::endl;

   posicion[0] = sin(alfa) * cos(beta) * sqrt(origen.lengthSq());
   posicion[1] = sin(beta) * sqrt(origen.lengthSq());
   posicion[2] = cos(beta) * cos(alfa) * sqrt(origen.lengthSq());
}