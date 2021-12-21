#include "cuadro.h"

Cuadro::Cuadro(float lado)
{
   v.resize(4);

   v = {
       {0, 0, 0},
       {lado, 0, 0},
       {0, lado, 0},
       {lado, lado, 0}};

   f = {{0, 1, 3},
        {0, 3, 2}};

   asignarColores();
   calcular_normales();
}