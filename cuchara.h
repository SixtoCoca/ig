// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: base.h

//
// #############################################################################

#ifndef CUCHARA_H_INCLUDED
#define CUCHARA_H_INCLUDED

#include "malla.h"
#include "cubo.h"
#include "cilindro.h"
#include "esfera.h"

// *****************************************************************************
// Objeto jerarquico de la práctica, la cuchara de la catapulta
// 


class Cuchara
{
private:
   float rotacionX;
   Cilindro *ejeRotacion = nullptr, *mastil = nullptr;
   Cubo *contraPeso = nullptr;
   Esfera *cuchara = nullptr;
public:
   Cuchara();
   void draw(bool modo, bool ajedrez, bool alambre, bool solido, bool puntos, bool luz);
   void rotacion(float angulo);

};

#endif
