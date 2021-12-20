// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Catapulta.h

//
// #############################################################################

#ifndef CATAPULTA_H_INCLUDED
#define CATAPULTA_H_INCLUDED

#include "malla.h"
#include "cubo.h"
#include "cilindro.h"
#include "esfera.h"
#include "estructura.h"
#include "cuchara.h"

// *****************************************************************************
// Objeto jerarquico de la práctica, una catapulta con 3 grados de libertad
// -El primero la accion de la catapulta al lanzar algo
// -El segundo la base puede rotar la catapulta
// -El tercero la base puede elevar y bajar la altura

class Catapulta
{
private:
   float alturaBase;
   float rotacion;
   Cubo *base = nullptr;
   Cilindro *elevador = nullptr, *baseRotatoria = nullptr;

   Estructura *estructura = nullptr;
   Cuchara *cuchara = nullptr;

public:
   Catapulta();
   void draw(bool modo, bool ajedrez, bool alambre, bool solido, bool puntos, bool luz);

   void rotacionCuchara(float angulo);
   void rotacionCatapulta(float angulo);
   void alturaCatapulta(float altura);
};

#endif
