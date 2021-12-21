#ifndef CILINDRO_H_INCLUDED
#define CILINDRO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// CILINDRO
//

class Cilindro : public ObjRevolucion
{
public:
   Cilindro(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio, eje ejeR=EJEY);
   
};

#endif
