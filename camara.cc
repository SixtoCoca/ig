#include "camara.h"

Camara::Camara(const Tupla3f &eye, const Tupla3f &at, const Tupla3f &up, const tipoCamara tipo, const float near, const float far)
{
   this->eye = eye;
   this->at = at;
   this->up = up;
   this->tipo = tipo;
   this->near = near;
   this->far = far;

   objeto = CAMNINGUNO;
}

void Camara::rotarXExaminar(float angulo)
{
   //restamos at para poder modificar solo eye
   Tupla3f centro = eye - at;

   centro[1] = cos(angulo) * centro[1] - sin(angulo) * centro[2];
   centro[2] = sin(angulo) * centro[1] + cos(angulo) * centro[2];
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
   centro[2] = sin(angulo) * centro[1] + cos(angulo) * centro[2];
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

void Camara::girarFirstPerson(float x, float y)
{
   rotarXFirstPerson(-y * (M_PI / 180));
   rotarYFirstPerson(-x * (M_PI / 180));
}

void Camara::girarExaminar(float x, float y)
{
   rotarXExaminar(y * (M_PI / 180));
   rotarYExaminar(x * (M_PI / 180));
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
   // std::cout << "todos los parametros de la camara:" << left << " " << right << " " << bottom << " " << top << " " << near << " " << far;
   if (tipo == ORTOGONAL)
      glOrtho(left, right, bottom, top, near, far);
   else
      glFrustum(left, right, bottom, top, near, far);
}

void Camara::nuevoLeft(float l)
{
   left = l;
}

void Camara::nuevoRight(float r)
{
   right = r;
}

void Camara::nuevoTop(float t)
{
   top = t;
}

void Camara::nuevoBottom(float b)
{
   bottom = b;
}

float Camara::getBottom()
{
   return bottom;
}

float Camara::getTop()
{
   return top;
}

objetos Camara::getObjeto()
{
   return objeto;
}
void Camara::setObjeto(objetos o)
{
   objeto = o;
}

void Camara::setAt(float x, float y, float z)
{
   at[0] = x;
   at[1] = y;
   at[2] = z;
}