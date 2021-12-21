#include "cuchara.h"

// *****************************************************************************
//
// Clase cuchara
//
// *****************************************************************************

Cuchara::Cuchara()
{
   rotacionX = 0;
   ejeRotacion = new Cilindro(6, 100, 40, 3, EJEX);
   mastil = new Cilindro(6, 100, 100, 3, EJEZ);
   contraPeso = new Cubo(1);
   cuchara = new Esfera(8, 100, 3);
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

void Cuchara::rotacion(float incremento) //Lo resto por mi modelo
{
   rotacionX -= incremento;
   if (-rotacionX >= 240) //240 es el tope que he estimado
      rotacionX = -240;
   if (rotacionX >= 30) //30 es el otro tope
      rotacionX = 30;
}
