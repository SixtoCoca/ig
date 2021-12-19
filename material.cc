#include "material.h"

// *****************************************************************************
//
// Clase material (práctica 3)
//
// *****************************************************************************

Material::Material(Tupla4f amb, Tupla4f esp, Tupla4f dif, float bri)
{
   ambiente = amb;
   especular = esp;
   difuso = dif;
   brillo = bri;
}
void Material::aplicar()
{
   glMaterialfv(GL_FRONT,GL_AMBIENT,ambiente);
   glMaterialfv(GL_FRONT,GL_DIFFUSE,especular);
   glMaterialfv(GL_FRONT,GL_SPECULAR,difuso);
   glMaterialf(GL_FRONT,GL_SHININESS,brillo);
}