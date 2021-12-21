#include "catapulta.h"
#include "material.h"

// *****************************************************************************
//
// Clase Catapulta
//
// *****************************************************************************

Catapulta::Catapulta()
{
   alturaBase = 10;
   maximaAltura = 100;
   rotacion = 0;
   base = new Cubo(1);
   elevador = new Cilindro(6, 6, 1, 1);
   baseRotatoria = new Cilindro(6, 100, 1, 1);
   velocidad = 1.0f;
   velocidadAltura = 1.0f;

   //temporal
   //Obsidian
   Tupla4f mat_ambient = {0.05375f, 0.05f, 0.06625f, 0.82f};
   Tupla4f mat_diffuse = {0.18275f, 0.17f, 0.22525f, 0.82f};
   Tupla4f mat_specular = {0.332741f, 0.328634f, 0.346435f, 0.82f};
   float shine = 38.4f;

   Material *obsidian = new Material(mat_ambient, mat_diffuse, mat_specular, shine);
   base->setMaterial(obsidian);
   elevador->setMaterial(obsidian);
   baseRotatoria->setMaterial(obsidian);

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

   if (alturaBase <= 0)
      alturaBase = 0;
   if (alturaBase >= maximaAltura)
      alturaBase = maximaAltura;
}

void Catapulta::rotacionCatapulta(float incremento)
{
   rotacion += incremento;
   rotacion = fmod(rotacion, 360);
}

void Catapulta::animar()
{
   //para cambiar el sentido
   if (alturaBase <= 0)
      velocidadAltura = velocidadAltura * (-1);
   if (alturaBase >= maximaAltura)
      velocidadAltura = velocidadAltura * (-1);

   alturaCatapulta(velocidadAltura);

   rotacionCatapulta(velocidad);
   cuchara->animar();
}
void Catapulta::modificarVelocidadAnimacionRotacion(float incremento)
{
   velocidad = velocidad * incremento;
}
void Catapulta::modificarVelocidadAnimacionAltura(float incremento)
{

   velocidadAltura = velocidadAltura * incremento;
}

void Catapulta::modificarVelocidadAnimacionCuchara(float incremento)
{
   cuchara->modificarVelocidadAnimacion(incremento);
}

void Catapulta::modificarVelocidad(float incremento)
{
   modificarVelocidadAnimacionAltura(incremento);
   modificarVelocidadAnimacionCuchara(incremento);
   modificarVelocidadAnimacionRotacion(incremento);
}