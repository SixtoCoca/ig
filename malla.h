// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"
#include "textura.h"
// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
public:
   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(bool ajedrez, bool alambre, bool solido, bool puntos, bool luz, bool seleccion, bool seleccionable);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(bool ajedrez, bool alambre, bool solido, bool puntos, bool luz, bool seleccion, bool seleccionable);

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(bool modo, bool ajedrez, bool alambre, bool solido, bool puntos, bool luz, bool seleccion, bool seleccionable);

   // función para dibujar en modo puntos
   void modoPuntos();

   // función para dibujar en modo alambre
   void modoAlambre();

   // función para dibujar en modo solido
   void modoSolido();

   // función para dibujar en modo ajedrez
   void modoAjedrez();

   void modoSeleccion();
   void modoSeleccionable();
   void modoSeleccionado();

   void setMaterial(Material *mat);

   void setTextura(const std::string &archivo);
   void asignarColoresSeleccion(Tupla3f c); //para asignarlos colores de la seleccion
   void asignarColoresPuntosSeleccionables(); //para asignarlos colores de la seleccion
   void asignarColoresPuntosSeleccionados(); //para asignarlos colores de la seleccion

protected:
   void calcular_normales(); // calcula tabla de normales de vértices (práctica 3)
   void asignarColores();    //para asignarlos colores en los constructores de los objetos

   std::vector<Tupla3f> v;  // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f;  // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3f> nv; // vector de normales
   std::vector<Tupla3f> color, colorAlambre, colorPuntos, colorSeleccion, colorSeleccionable;
   std::vector<Tupla3i> caraPar, caraImpar;   //Contendran las caras pares e impares
   std::vector<Tupla3f> colorPar, colorImpar; //Contendran los colores de las caras pares e impares
   Material *m;

   int tam;
   int instancias;
   Textura *t = nullptr;
   std::vector<Tupla2f> ct;
   GLuint id_vbo_ver = 0, id_vbo_tri = 0, id_vbo_color = 0, id_vbo_color_par = 0, id_vbo_color_impar = 0, id_vbo_tri_par = 0, id_vbo_tri_impar = 0, id_vbo_normales = 0;
   GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid *puntero_ram);
};

#endif
