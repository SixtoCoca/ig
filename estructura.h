// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: estructura.h

//
// #############################################################################

#ifndef ESTRUCTURA_H_INCLUDED
#define ESTRUCTURA_H_INCLUDED

#include "malla.h"
#include "cilindro.h"

// *****************************************************************************
// Objeto jerarquico de la práctica, la estructura de la catapulta
// 


class Estructura
{
private:
   Cilindro *base1 = nullptr,*base2 = nullptr;
   Cilindro *poste = nullptr, *posteDiagonal = nullptr;

public:
   Estructura();
   void draw(bool modo, bool ajedrez, bool alambre, bool solido, bool puntos, bool luz,bool seleccionado, bool seleccionable);
   void asignarColoresSeleccion(Tupla3f c);
};

#endif
