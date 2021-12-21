// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: textura.h

//
// #############################################################################

#ifndef TEXTURA_H_INCLUDED
#define TEXTURA_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
// Clase textura
//
// *****************************************************************************
class Textura
{
private:
   GLuint textura_id;
   unsigned char *data;
   int width, height;
   

public:
   Textura(const std::string &archivo);
   void activar();
};

#endif
