// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: material.h

//
// #############################################################################

#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "aux.h"
#include "tuplasg.h"

// *****************************************************************************
//
// Clase Material (práctica 3)
//
// *****************************************************************************
class Material
{
private:
   Tupla4f ambiente, especular, difuso;
   float brillo;

public:
   Material(Tupla4f ambiente, Tupla4f especular, Tupla4f difuso, float brillo);
   void aplicar();
};

#endif
