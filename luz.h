// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luz.h

//
// #############################################################################

#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"
#include "tuplasg.h"

// *****************************************************************************
//
// Clase luz (práctica 3)
//
// *****************************************************************************
class Luz
{
protected:
   Tupla4f colorAmbiente, colorEspecular, colorDifuso,posicion;
   GLenum id;

public:
   void activar();
   void desactivar();
};

#endif
