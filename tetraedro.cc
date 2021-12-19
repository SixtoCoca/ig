#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro(float tam)
{

   // inicializar la tabla de vértices
   v={
      {-tam/2, -tam/2, -tam/2},  //0
      {0, -tam/2, tam/2},  //1
      {tam/2, -tam/2, -tam/2},  //2
      {0, tam/2, 0},  //3

   };
    
   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   f= {
      {0,1,3},
      {1,2,3},
      {2,0,3},
      {0,2,1},
   };

   asignarColores();
   calcular_normales();
}
