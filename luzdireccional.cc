#include "luzdireccional.h"

// *****************************************************************************
//
// Clase luzdireccional (práctica 3)
//
// *****************************************************************************

LuzDireccional::LuzDireccional(const Tupla2f &direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso)
{
   id = idLuzOpenGL;

   alfa = direccion[0];
   beta = direccion[1];

   posicion[0] = sin((alfa * M_PI) / 180.0);
   posicion[1] = cos((alfa * M_PI) / 180.0) * (-sin((beta * M_PI) / 180.0));
   posicion[2] = cos((alfa * M_PI) / 180.0) * cos((beta * M_PI) / 180.0);
   posicion[3] = 0.0;

   this->colorAmbiente = colorAmbiente;
   this->colorEspecular = colorEspecular;
   this->colorDifuso = colorDifuso;
}

void LuzDireccional::variarAnguloAlfa(float incremento)
{
   alfa = alfa + incremento;
   if (alfa > M_PI * 2.0)
   {
      alfa -= M_PI * 2.0;
   }
   else if (alfa < 0)
   {
      alfa += M_PI * 2.0;
   }
   std::cout << alfa *  180 / M_PI << "º <--- angulo alfa" << std::endl;

   posicion[0] = sin(alfa) * cos(beta) * sqrt(posicion.lengthSq());
   posicion[1] = sin(beta) * sqrt(posicion.lengthSq());
}
void LuzDireccional::variarAnguloBeta(float incremento)
{
   beta = beta + incremento;
   if (beta > M_PI * 2.0)
   {
      beta -= M_PI * 2.0;
   }
   else if (beta < 0)
   {
      beta += M_PI * 2.0;
   }
   beta = (int)(beta + incremento) % 360;

   std::cout << beta * 180 / M_PI  << "<--- angulo beta" << std::endl;

   posicion[0] = sin(alfa) * cos(beta) * sqrt(posicion.lengthSq());
   posicion[1] = sin(beta) * sqrt(posicion.lengthSq());
}