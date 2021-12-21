#include "textura.h"
#include "jpg_imagen.hpp"
// *****************************************************************************
//
// Clase textura
//
// *****************************************************************************

Textura::Textura(const std::string &archivo)
{

   jpg::Imagen *imagen = new jpg::Imagen(archivo);
   width = imagen->tamX();
   height = imagen->tamY();

   data = imagen->leerPixels();

   textura_id = -1;
}

void Textura::activar()
{

   //Seleccionar el texel
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

   //para obtener interpolación bileneal
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

   if (textura_id == -1)
   {
      glGenTextures(1, &textura_id);
      glBindTexture(GL_TEXTURE_2D, textura_id);

      gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);
   }

   glBindTexture(GL_TEXTURE_2D, textura_id);
}