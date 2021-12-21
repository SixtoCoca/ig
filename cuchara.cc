#include "cuchara.h"
#include "material.h"
// *****************************************************************************
//
// Clase cuchara
//
// *****************************************************************************

Cuchara::Cuchara()
{
   rotacionX = 0;
   velocidad=1.0f;
   ejeRotacion = new Cilindro(6, 100, 40, 3, EJEX);
   mastil = new Cilindro(6, 100, 100, 3, EJEZ);
   contraPeso = new Cubo(1);
   cuchara = new Esfera(8, 100, 3);

   //temporal
   //Jade
   Tupla4f mat_ambient = {0.135f, 0.2225f, 0.1575f, 0.95f};
   Tupla4f mat_diffuse = {0.54f, 0.89f, 0.63f, 0.95f};
   Tupla4f mat_specular = {0.316228f, 0.316228f, 0.316228f, 0.95f};
   float shine = 12.8f;

   Material *jade = new Material(mat_ambient, mat_diffuse, mat_specular, shine);
   contraPeso->setMaterial(jade);
   mastil->setMaterial(jade);
   cuchara->setMaterial(jade);
   ejeRotacion->setMaterial(jade);
}

void Cuchara::draw(bool modo, bool ajedrez, bool alambre, bool solido, bool puntos, bool luz)
{
   //Cuchara

   glPushMatrix();
   {
      glRotatef(rotacionX, 1.0f, 0.0f, 0.0f);
      glPushMatrix();
      {
         ejeRotacion->draw(modo, ajedrez, alambre, solido, puntos, luz);
      }
      glPopMatrix();

      //brazo de lanzamiento
      glPushMatrix();
      {
         //mastil

         glPushMatrix();
         {
            glTranslatef(20, 0, -25);

            mastil->draw(modo, ajedrez, alambre, solido, puntos, luz);
         }
         glPopMatrix();
         //contrapeso
         glPushMatrix();
         {
            glTranslatef(20, 0, -25);
            glScalef(20, 20, 20);

            contraPeso->draw(modo, ajedrez, alambre, solido, puntos, luz);
         }
         glPopMatrix();
         //cuchara
         glPushMatrix();
         {
            glTranslatef(20, 0, 80);
            glScalef(3, 3, 3);

            cuchara->draw(modo, ajedrez, alambre, solido, puntos, luz);
         }
         glPopMatrix();
      }
      glPopMatrix();
   }
   glPopMatrix();
}

void Cuchara::rotacion(float incremento) //Lo resto por mi modelo para los topes
{
   rotacionX -= incremento;
   if (-rotacionX >= 240) //240 es el tope que he estimado
      rotacionX = -240;
   if (rotacionX >= 30) //30 es el otro tope
      rotacionX = 30;
}

void Cuchara::animar()
{
   //Para que cambie de sentido
   if (-rotacionX >= 240) //240 es el tope que he estimado
      velocidad = velocidad * (-1);
   if (rotacionX >= 30) //30 es el otro tope
      velocidad = velocidad * (-1);

   rotacion(velocidad);
}

void Cuchara::modificarVelocidadAnimacion(float incremento)
{
   velocidad = velocidad * incremento;
}