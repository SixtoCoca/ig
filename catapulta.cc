#include "catapulta.h"

// *****************************************************************************
//
// Clase Catapulta
//
// *****************************************************************************

Catapulta::Catapulta()
{
   alturaBase = 10;
   rotacion = 0;
   base = new Cubo(1);
   elevador = new Cilindro(6, 6, 1, 1);
   baseRotatoria = new Cilindro(6, 100, 1, 1);

   estructura = new Estructura();
   cuchara = new Cuchara();
}

void Catapulta::draw(bool modo, bool ajedrez, bool alambre, bool solido, bool puntos, bool luz)
{

   //Catapulta
   glPushMatrix();
   {
      //Base Fija
      glPushMatrix();
      {

         //Rectangulo apoyo
         glPushMatrix();
         {
            glScalef(50, 5, 50);
            base->draw(modo, ajedrez, alambre, solido, puntos, luz);
         }
         glPopMatrix();
         //elevador
         glPushMatrix();
         {
            glScalef(4, alturaBase, 4);
            elevador->draw(modo, ajedrez, alambre, solido, puntos, luz);
         }
         glPopMatrix();
      }
      glPopMatrix();
      //Base Movil
      glPushMatrix();
      {
         glTranslatef(0, alturaBase, 0);
         glRotatef(rotacion, 0.0f, 1.0f, 0.0f);
         glPushMatrix();
         {
            glScalef(40, 2, 40);
            baseRotatoria->draw(modo, ajedrez, alambre, solido, puntos, luz);
         }
         glPopMatrix();

         //lanzador
         glPushMatrix();
         {
            glPushMatrix();
            {
               estructura->draw(modo, ajedrez, alambre, solido, puntos, luz);
            }
            glPopMatrix();
            //Cuchara
            glPushMatrix();
            {
               glTranslatef(-20, 50, -20);
               cuchara->draw(modo, ajedrez, alambre, solido, puntos, luz);
            }
            glPopMatrix();
         }
         glPopMatrix();
      }
      glPopMatrix();
   }
   glPopMatrix();
}

void Catapulta::rotacionCuchara(float incremento)
{
   cuchara->rotacion(incremento);
}

void Catapulta::alturaCatapulta(float incremento)
{
   alturaBase += incremento;
}

void Catapulta::rotacionCatapulta(float incremento)
{
   rotacion += incremento;
   rotacion = fmod(rotacion, 360);
}