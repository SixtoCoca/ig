#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato(bool ajedrez, bool alambre, bool solido, bool puntos, bool luz)
{

   // visualizar la malla usando glDrawElements,
   // habilitar uso de un array de vértices
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
   // indicar el formato y la dirección de memoria del array de
   // vértices (son tuplas de 3 valores float, sin espacio entre ellas)
   glVertexPointer(3, GL_FLOAT, 0, v.data());
   glEnable(GL_CULL_FACE);
   if (luz)
   {
      //Aplicamos el material
      m->aplicar();
      glEnable(GL_NORMALIZE);
      //Habilitar uso de array de normales
      glEnableClientState(GL_NORMAL_ARRAY);

      glNormalPointer(GL_FLOAT, 0, nv.data());
      glPolygonMode(GL_FRONT, GL_FILL);
      glShadeModel(GL_SMOOTH);
      glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, f.data());

      glDisable(GL_NORMALIZE);
      //Desactivo el array de normales
      glDisableClientState(GL_NORMAL_ARRAY);
   }
   else
   {
      if (ajedrez)
      {
         glPolygonMode(GL_FRONT, GL_FILL);

         glColorPointer(3, GL_FLOAT, 0, colorPar.data());
         glDrawElements(GL_TRIANGLES, 3 * caraPar.size(), GL_UNSIGNED_INT, caraPar.data());

         glColorPointer(3, GL_FLOAT, 0, colorImpar.data());
         glDrawElements(GL_TRIANGLES, 3 * caraImpar.size(), GL_UNSIGNED_INT, caraImpar.data());
      }
      else
      {
         if (puntos)
         {
            modoPuntos();
            glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, f.data());
         }
         if (alambre)
         {
            modoAlambre();
            glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, f.data());
         }
         if (solido)
         {
            modoSolido();
            glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, f.data());
         }
      }
   }

   // deshabilitar array de vértices
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(bool ajedrez, bool alambre, bool solido, bool puntos, bool luz)
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   if (id_vbo_ver == 0)
   {
      id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, 3 * v.size() * sizeof(float), v.data());
   }
   if (id_vbo_tri == 0)
   {
      id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3 * f.size() * sizeof(unsigned int), f.data());
   }
   if (id_vbo_color == 0)
   {
      id_vbo_color = CrearVBO(GL_ARRAY_BUFFER, 3 * color.size() * sizeof(float), color.data());
   }
   if (id_vbo_normales == 0)
   {
      id_vbo_normales = CrearVBO(GL_ARRAY_BUFFER, 3 * nv.size() * sizeof(float), nv.data());
   }
   // especificar localización y formato de la tabla de vértices, habilitar tabla
   glEnable(GL_CULL_FACE);
   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver); // activar VBO de vértices
   glVertexPointer(3, GL_FLOAT, 0, 0);        // especifica formato y offset (=0)
   glBindBuffer(GL_ARRAY_BUFFER, 0);          //desactivar VBO de vértices
   glEnableClientState(GL_VERTEX_ARRAY);      // habilitar tabla de vértices

   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_color); // activar VBO de colores
   glBindBuffer(GL_ARRAY_BUFFER, 0);            //desactivar VBO de colores
   glEnableClientState(GL_COLOR_ARRAY);         // habilitar tabla de vértices para el color
   if (luz)
   {
      //Aplicamos el material
      glEnable(GL_NORMALIZE);

      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_normales);
      glNormalPointer(GL_FLOAT, 0, 0);
      glBindBuffer(GL_ARRAY_BUFFER, 0); //desactivar VBO de colores
      glEnableClientState(GL_NORMAL_ARRAY);

      m->aplicar();
      glNormalPointer(GL_FLOAT, 0, nv.data());
      glPolygonMode(GL_FRONT, GL_FILL);
      //Habilitar uso de array de normales

      glShadeModel(GL_SMOOTH);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri); //activar VBO de triángulos

      glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, 0);
      glDisable(GL_NORMALIZE);
      //Desactivo el array de normales
      glDisableClientState(GL_NORMAL_ARRAY);
   }
   else
   {
      if (ajedrez)
      {
         if (id_vbo_tri_par == 0)
         {
            id_vbo_tri_par = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3 * caraPar.size() * sizeof(unsigned int), caraPar.data());
         }
         if (id_vbo_tri_impar == 0)
         {
            id_vbo_tri_impar = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3 * caraImpar.size() * sizeof(unsigned int), caraImpar.data());
         }
         if (id_vbo_color_par == 0)
         {
            id_vbo_color_par = CrearVBO(GL_ARRAY_BUFFER, 3 * colorPar.size() * sizeof(float), colorPar.data());
         }
         if (id_vbo_color_impar == 0)
         {
            id_vbo_color_impar = CrearVBO(GL_ARRAY_BUFFER, 3 * colorImpar.size() * sizeof(float), colorImpar.data());
         }
         glPolygonMode(GL_FRONT, GL_FILL);
         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri_par);
         //glEnableClientState(GL_COLOR_ARRAY);             // habilitar tabla de vértices para el color

         glBindBuffer(GL_ARRAY_BUFFER, id_vbo_color_par); // activar VBO de colores
         glColorPointer(3, GL_FLOAT, 0, 0);
         glBindBuffer(GL_ARRAY_BUFFER, 0);                //desactivar VBO de colores

         glDrawElements(GL_TRIANGLES, 3 * caraPar.size(), GL_UNSIGNED_INT, 0);
         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // desactivar VBO de triángulo

         glBindBuffer(GL_ARRAY_BUFFER, id_vbo_color_impar); // activar VBO de colores

         glColorPointer(3, GL_FLOAT, 0, 0);
         glBindBuffer(GL_ARRAY_BUFFER, 0);                  //desactivar VBO de colores
         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri_impar);
         glDrawElements(GL_TRIANGLES, 3 * caraImpar.size(), GL_UNSIGNED_INT, 0);
         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // desactivar VBO de triángulo
      }
      else
      {
         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri); //activar VBO de triángulos
         if (puntos)
         {
            modoPuntos();
            glDrawElements(GL_TRIANGLES, 3 * f.size(), GL_UNSIGNED_INT, 0);
         }
         if (alambre)
         {
            modoAlambre();
            glDrawElements(GL_TRIANGLES, 3 * f.size(), GL_UNSIGNED_INT, 0);
         }
         if (solido)
         {
            modoSolido();
            glDrawElements(GL_TRIANGLES, 3 * f.size(), GL_UNSIGNED_INT, 0);
         }
      }
   }

   glDisableClientState(GL_COLOR_ARRAY);
   // descativar uso de array de vértices
   glDisableClientState(GL_VERTEX_ARRAY);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // desactivar VBO de triángulo
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(bool modo, bool ajedrez, bool alambre, bool solido, bool puntos, bool luz)
{
   if (modo)
   {
      draw_ModoInmediato(ajedrez, alambre, solido, puntos, luz);
   }
   else
   {
      draw_ModoDiferido(ajedrez, alambre, solido, puntos, luz);
   }
}

// -----------------------------------------------------------------------------
// Función para dibujar en modo alambre

void Malla3D::modoAlambre()
{
   glColorPointer(3, GL_FLOAT, 0, colorAlambre.data());
   glPolygonMode(GL_FRONT, GL_LINE);
}

// -----------------------------------------------------------------------------
// Función para dibujar en modo puntos

void Malla3D::modoPuntos()
{
   glColorPointer(3, GL_FLOAT, 0, colorPuntos.data());
   glPolygonMode(GL_FRONT, GL_POINT);
   glPointSize(5);
}
// -----------------------------------------------------------------------------
// Función para dibujar en modo solido
void Malla3D::modoSolido()
{
   glColorPointer(3, GL_FLOAT, 0, color.data());
   glPolygonMode(GL_FRONT, GL_FILL);
}

GLuint Malla3D::CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid *puntero_ram)
{
   GLuint id_vbo;                  // resultado: identificador de VBO
   glGenBuffers(1, &id_vbo);       // crear nuevo VBO, obtener identificador (nunca 0)
   glBindBuffer(tipo_vbo, id_vbo); // activar el VBO usando su identificador

   glBufferData(tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW); // desactivación del VBO(activar 0)
   glBindBuffer(tipo_vbo, 0);                                          // devolver el identificadr resultado
   return id_vbo;
}

void Malla3D::asignarColores()
{

   for (int i = 0; i < v.size(); i++)
      color.push_back({255, 0, 0});
   for (int i = 0; i < v.size(); i++)
      colorAlambre.push_back({255, 255, 0});
   for (int i = 0; i < v.size(); i++)
      colorPuntos.push_back({0, 255, 255});
   for (int i = 0; i < f.size(); i++)
   {
      if (i % 2 == 0)
      { //elegimos cuales son las caras pares e impares
         caraPar.push_back(f[i]);
      }
      else
      {
         caraImpar.push_back(f[i]);
      }
   }
   for (int i = 0; i < v.size(); i++)
   {
      colorPar.push_back({255, 0, 0});
      colorImpar.push_back({255, 255, 0});
   }
}

void Malla3D::calcular_normales()
{
   nv.resize(v.size());

   for (int i = 0; i < v.size(); i++)
   {
      nv[i] = {0, 0, 0};
   }
   //Calculamos primero la normal de la cara, haciendo el producto vectorial de 2 vectores de esta
   Tupla3f alfa, beta, nCara;
   for (int i = 0; i < f.size(); i++)
   {
      alfa = v[f[i][1]] - v[f[i][0]]; //vectores de la cara
      beta = v[f[i][2]] - v[f[i][0]];

      nCara = alfa.cross(beta); //normal de la cara, cross es una funcion de tupla3f para el producto vectorial

      nv[f[i][0]] = nv[f[i][0]] + nCara;
      nv[f[i][1]] = nv[f[i][1]] + nCara;
      nv[f[i][2]] = nv[f[i][2]] + nCara;
   } //Tengo la normal de cada vertice pero sin normalizar

   //Normalizo el vector de normales con nv= mv/|mv|
   for (int i = 0; i < nv.size(); i++)
   { //este chorizo es el modulo, es decir sqrt(x^2+y^2+z^2)
      nv[i] = {
          nv[i][0] / sqrt(nv[i][0] * nv[i][0] + nv[i][1] * nv[i][1] + nv[i][2] * nv[i][2]), //la coordenada x
          nv[i][1] / sqrt(nv[i][0] * nv[i][0] + nv[i][1] * nv[i][1] + nv[i][2] * nv[i][2]), //la coordenada y
          nv[i][2] / sqrt(nv[i][0] * nv[i][0] + nv[i][1] * nv[i][1] + nv[i][2] * nv[i][2]), //la coordenada z
      };
      //std::cout << "| " << nv[i][0] << ", " << nv[i][1] << ", " << nv[i][2] << "|" << " ->   "<< sqrt(nv[i][0] * nv[i][0] + nv[i][1] * nv[i][1] + nv[i][2] * nv[i][2]) << std::endl;
   }
}

void Malla3D::setMaterial(Material *material)
{
   m = material;
}