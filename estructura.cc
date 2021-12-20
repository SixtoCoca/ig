#include "estructura.h"

// *****************************************************************************
//
// Clase estructura
//
// *****************************************************************************

Estructura::Estructura()
{
   base1 = new Cilindro(6, 100, 50, 5, EJEZ);
   base2 = new Cilindro(6, 100, 50, 5, EJEX);
   poste = new Cilindro(6, 100, 50, 5, EJEY);
   posteDiagonal = new Cilindro(6, 100, 75, 5, EJEY);
}

void Estructura::draw(bool modo, bool ajedrez, bool alambre, bool solido, bool puntos, bool luz)
{

   //Estructura
   glPushMatrix();
   {
      // Base De la estructura
      glPushMatrix();
      {
         glTranslatef(0, 5, 0);
         glPushMatrix();
         {
            glTranslatef(20, 0, -20);
            base1->draw(modo, ajedrez, alambre, solido, puntos, luz);
         }
         glPopMatrix();
         glPushMatrix();
         {
            glTranslatef(-20, 0, -20);
            base1->draw(modo, ajedrez, alambre, solido, puntos, luz);
         }
         glPopMatrix();
         glPushMatrix();
         {
            glTranslatef(-25, 0, -20);
            base2->draw(modo, ajedrez, alambre, solido, puntos, luz);
         }
         glPopMatrix();
         glPushMatrix();
         {
            glTranslatef(-25, 0, 26);
            base2->draw(modo, ajedrez, alambre, solido, puntos, luz);
         }
         glPopMatrix();
      }
      glPopMatrix();

      //Postes Verticales
      glPushMatrix();
      {
         glPushMatrix();
         {
            glTranslatef(20, 0, -20);
            poste->draw(modo, ajedrez, alambre, solido, puntos, luz);
         }
         glPopMatrix();
         glPushMatrix();
         {
            glTranslatef(-20, 0, -20);
            poste->draw(modo, ajedrez, alambre, solido, puntos, luz);
         }
         glPopMatrix();
      }
      glPopMatrix();

      //Postes Diagonales
      glPushMatrix();
      {
         glPushMatrix();
         {
            glTranslatef(20, 0, 30);
            glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);

            posteDiagonal->draw(modo, ajedrez, alambre, solido, puntos, luz);
         }
         glPopMatrix();
         glPushMatrix();
         {
            glTranslatef(-20, 0, 30);
            glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);

            posteDiagonal->draw(modo, ajedrez, alambre, solido, puntos, luz);
         }
         glPopMatrix();
      }
      glPopMatrix();
   }
   glPopMatrix();
}