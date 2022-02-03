#include "estructura.h"
#include "material.h"
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
   //temporal
   //Jade

   Tupla4f mat_ambient = {0.1745f, 0.01175f, 0.01175f, 0.55f};
   Tupla4f mat_diffuse = {0.61424f, 0.04136f, 0.04136f, 0.55f};
   Tupla4f mat_specular = {0.727811f, 0.626959f, 0.626959f, 0.55f};
   float shine = 76.8f;

   Material *ruby = new Material(mat_ambient, mat_diffuse, mat_specular, shine);
   base1->setMaterial(ruby);
   base2->setMaterial(ruby);
   poste->setMaterial(ruby);
   posteDiagonal->setMaterial(ruby);
}

void Estructura::draw(bool modo, bool ajedrez, bool alambre, bool solido, bool puntos, bool luz, bool seleccionado, bool seleccionable)
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
            base1->draw(modo, ajedrez, alambre, solido, puntos, luz, seleccionado,seleccionable);
         }
         glPopMatrix();
         glPushMatrix();
         {
            glTranslatef(-20, 0, -20);
            base1->draw(modo, ajedrez, alambre, solido, puntos, luz, seleccionado,seleccionable);
         }
         glPopMatrix();
         glPushMatrix();
         {
            glTranslatef(-25, 0, -20);
            base2->draw(modo, ajedrez, alambre, solido, puntos, luz, seleccionado,seleccionable);
         }
         glPopMatrix();
         glPushMatrix();
         {
            glTranslatef(-25, 0, 20);
            base2->draw(modo, ajedrez, alambre, solido, puntos, luz, seleccionado,seleccionable);
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
            poste->draw(modo, ajedrez, alambre, solido, puntos, luz, seleccionado,seleccionable);
         }
         glPopMatrix();
         glPushMatrix();
         {
            glTranslatef(-20, 0, -20);
            poste->draw(modo, ajedrez, alambre, solido, puntos, luz, seleccionado,seleccionable);
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

            posteDiagonal->draw(modo, ajedrez, alambre, solido, puntos, luz, seleccionado,seleccionable);
         }
         glPopMatrix();
         glPushMatrix();
         {
            glTranslatef(-20, 0, 30);
            glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);

            posteDiagonal->draw(modo, ajedrez, alambre, solido, puntos, luz, seleccionado,seleccionable);
         }
         glPopMatrix();
      }
      glPopMatrix();
   }
   glPopMatrix();
}

void Estructura::asignarColoresSeleccion(Tupla3f c)
{
   base1->asignarColoresSeleccion(c);
   base2->asignarColoresSeleccion(c);
   poste->asignarColoresSeleccion(c);
   posteDiagonal->asignarColoresSeleccion(c);
}