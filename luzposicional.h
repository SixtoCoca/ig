// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luzdireccional.h

//
// #############################################################################

#ifndef LUZPOSICIONAL_H_INCLUDED
#define LUZPOSICIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"

// *****************************************************************************
//
// Clase luzPosicional (práctica 3)
//
// *****************************************************************************
class LuzPosicional : public Luz
{
public:
   //inicializar la fuente de luz
   LuzPosicional(const Tupla3f &posicion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso);
};

#endif
