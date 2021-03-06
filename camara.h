// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: camara.h

//
// #############################################################################

#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"
#include "tuplasg.h"

typedef enum
{
   ORTOGONAL,
   PERSPECTIVA
} tipoCamara;

typedef enum
{
   CAMCATAPULTA,
   CAMESFERA,
   CAMCUBO,
   CAMNINGUNO
} objetos;
// *****************************************************************************
//
// Clase camara (práctica 3)
//
// *****************************************************************************
class Camara
{
private:
   Tupla3f eye, at, up;
   tipoCamara tipo;
   objetos objeto;
   float left, right, bottom, top, near, far;

public:
   Camara(const Tupla3f &eye, const Tupla3f &at, const Tupla3f &up, const tipoCamara tipo, const float near, const float far);

   void rotarXExaminar(float angulo);
   void rotarYExaminar(float angulo);
   void rotarZExaminar(float angulo);
   void rotarXFirstPerson(float angulo);
   void rotarYFirstPerson(float angulo);
   void rotarZFirstPerson(float angulo);

   void mover(float x, float y, float z);
   void girarFirstPerson(float x, float y);
   void girarExaminar(float x, float y);

   void zoom(float factor);
   void setObserver();
   void setProyeccion();
   void nuevoLeft(float l);
   void nuevoRight(float r);
   void nuevoBottom(float b);
   void nuevoTop(float t);
   float getBottom();
   float getTop();
   objetos getObjeto();
   void setObjeto(objetos o);
   void setAt(float x, float y, float z);
};

#endif
