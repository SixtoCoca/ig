#include "camara.h"

Camara::Camara(const Tupla3f &eye, const Tupla3f &at, const Tupla3f &up, const tipoCamara tipo, const float near, const float far, const float l, const float r, const float t, const float b)
{
   this->eye = eye;
   this->at = at;
   this->up = up;
   this->tipo = tipo;
   this->near = near;
   this->far = far;
   this->left = l;
   this->right = r;
   this->bottom = b;
   this->top = t;
}

void Camara::rotarXExaminar(float angulo)
{
   //restamos at para poder modificar solo eye
   Tupla3f centro = eye - at;

   centro[1] = cos(angulo) * centro[1] - sin(angulo) * centro[2];
   centro[2] = sin(angulo) * centro[1] + sin(angulo) * centro[2];
   centro = centro.normalized() * sqrt(centro.lengthSq()); //Centro Normalizado por el modulo

   //añadimos el at que hemos quitador anteriormente
   eye = centro + at;
}

void Camara::rotarYExaminar(float angulo)
{
   //restamos at para poder modificar solo eye
   Tupla3f centro = eye - at;

   centro[0] = cos(angulo) * centro[0] + sin(angulo) * centro[2];
   centro[2] = -sin(angulo) * centro[0] + cos(angulo) * centro[2];
   centro = centro.normalized() * sqrt(centro.lengthSq()); //Centro Normalizado por el modulo

   //añadimos el at que hemos quitador anteriormente
   eye = centro + at;
}

void Camara::rotarZExaminar(float angulo)
{
   //restamos at para poder modificar solo eye
   Tupla3f centro = eye - at;

   centro[0] = cos(angulo) * centro[0] - sin(angulo) * centro[1];
   centro[1] = sin(angulo) * centro[0] + cos(angulo) * centro[1];
   centro = centro.normalized() * sqrt(centro.lengthSq()); //Centro Normalizado por el modulo

   //añadimos el at que hemos quitador anteriormente
   eye = centro + at;
}

void Camara::rotarXFirstPerson(float angulo)
{
   //restamos eye para poder modificar solo at
   Tupla3f centro = at - eye;

   centro[1] = cos(angulo) * centro[1] - sin(angulo) * centro[2];
   centro[2] = sin(angulo) * centro[1] + sin(angulo) * centro[2];
   centro = centro.normalized() * sqrt(centro.lengthSq()); //Centro Normalizado por el modulo

   //añadimos el eye que hemos quitador anteriormente
   at = centro + eye;
}

void Camara::rotarYFirstPerson(float angulo)
{
   //restamos eye para poder modificar solo at
   Tupla3f centro = at - eye;

   centro[0] = cos(angulo) * centro[0] + sin(angulo) * centro[2];
   centro[2] = -sin(angulo) * centro[0] + cos(angulo) * centro[2];
   centro = centro.normalized() * sqrt(centro.lengthSq()); //Centro Normalizado por el modulo

   //añadimos el eye que hemos quitador anteriormente
   at = centro + eye;
}

void Camara::rotarZFirstPerson(float angulo)
{
   //restamos eye para poder modificar solo at
   Tupla3f centro = at - eye;

   centro[0] = cos(angulo) * centro[0] - sin(angulo) * centro[1];
   centro[1] = sin(angulo) * centro[0] + cos(angulo) * centro[1];
   centro = centro.normalized() * sqrt(centro.lengthSq()); //Centro Normalizado por el modulo

   //añadimos el eye que hemos quitador anteriormente
   at = centro + eye;
}

void Camara::mover(float x, float y, float z)
{
   eye[0] += x;
   eye[1] += y;
   eye[2] += z;

   at[0] += x;
   at[1] += y;
   at[2] += z;
}

void Camara::zoom(float factor)
{
   left *= factor;
   right *= factor;
   bottom *= factor;
   top *= factor;
}

void Camara::setObserver()
{
   gluLookAt(eye[0], eye[1], eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);
}

void Camara::setProyeccion()
{
   std::cout << "todos los parametros de la camara:" << left << " " << right << " " << bottom << " " << top << " " << near << " " << far;
   if (tipo == ORTOGONAL)
      glOrtho(left, right, bottom, top, near, far);
   else
      glFrustum(left, right, bottom, top, near, far);
}

void Camara::nuevoLeft(float l){
   left = l;
}

void Camara::nuevoRight(float r){
   right = r;
}

void Camara::nuevoTop(float t){
   top = t;
}

void Camara::nuevoBottom(float b){
   bottom = b;
}