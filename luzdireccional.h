// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luzdireccional.h

//
// #############################################################################

#ifndef LUZDIRECCIONAL_H_INCLUDED
#define LUZDIRECCIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"

// *****************************************************************************
//
// Clase luzDireccional (práctica 3)
//
// *****************************************************************************
class LuzDireccional : public Luz
{
protected:
   float alfa, beta;

public:
   //inicializar la fuente de luz
   LuzDireccional(const Tupla2f &direccion,GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso);

   //cambiar ángulo
   void variarAnguloAlfa(float incremento);
   void variarAnguloBeta(float incremento);
};

#endif
