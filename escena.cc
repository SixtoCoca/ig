

#include "aux.h" // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
   Front_plane = 50.0;
   Back_plane = 2000.0;
   Observer_distance = 4 * Front_plane;
   Observer_angle_x = 0.0;
   Observer_angle_y = 0.0;

   ejes.changeAxisSize(5000);

   //materiales
   Tupla4f mat_ambient = {0.24725f, 0.1995f, 0.0745f, 1.0f};
   Tupla4f mat_diffuse = {0.75164f, 0.60648f, 0.22648f, 1.0f};
   Tupla4f mat_specular = {0.628281f, 0.555802f, 0.366065f, 1.0f};
   float shine = 51.2f;
   oro = new Material(mat_ambient, mat_diffuse, mat_specular, shine);

   mat_ambient = {0.19125f, 0.0735f, 0.0225f, 1.0f};
   mat_diffuse = {0.7038f, 0.27048f, 0.0828f, 1.0f};
   mat_specular = {0.256777f, 0.137622f, 0.086014f, 1.0f};
   shine = 12.8f;
   cobre = new Material(mat_ambient, mat_diffuse, mat_specular, shine);

   mat_ambient = {0.0f, 0.0f, 0.0f, 1.0f};
   mat_diffuse = {0.0f, 0.0f, 0.0f, 1.0f};
   mat_specular = {1.0f, 1.0f, 1.0f, 1.0f};
   shine = 50.0f;
   negro = new Material(mat_ambient, mat_diffuse, mat_specular, shine);

   mat_ambient = {0.01f, 0.01f, 0.01f, 1.0f};
   mat_diffuse = {1.0f, 1.0f, 1.0f, 1.0f};
   mat_specular = {0.0, 0.0f, 0.0f, 1.0f};
   shine = 10.0f;
   blanco = new Material(mat_ambient, mat_diffuse, mat_specular, shine);

   // crear los objetos de la escena....
   // .......completar: ...
   modoDibujo = false;
   cubo = new Cubo(50);
   Tupla3f c1 = {0.5f, 0, 0.5f};
   cubo->asignarColoresSeleccion(c1);
   cubo->setMaterial(oro);
   cubo->setTextura("texturas/madera.jpg");
   catapulta = new Catapulta();
   Tupla3f c2 = {0.5f, 0.5f, 0};
   catapulta->asignarColoresSeleccion(c2);

   tetraedro = new Tetraedro(100);
   tetraedro->setMaterial(oro);

   esfera = new Esfera(20, 20, 10);
   Tupla3f c3 = {0, 0.5f, 0.5f};
   esfera->asignarColoresSeleccion(c3);
   esfera->setMaterial(cobre);

   suelo = new Cuadro(1);
   suelo->setTextura("texturas/cesped.jpg");
   suelo->setMaterial(blanco);

   cono = new Cono(10, 50, 10, 5, EJEY);
   cono->setMaterial(oro);

   cilindro = new Cilindro(5.0, 10.0, 10.0, 5, EJEY);
   cilindro->setMaterial(oro);

   objply = new ObjPLY("plys/ant.ply");
   objply->setMaterial(oro);

   objrevolucion = new ObjRevolucion("plys/peon.ply", 6, 1, 1, EJEY);
   objrevolucion->setMaterial(blanco);

   objrevolucion2 = new ObjRevolucion("plys/peonx.ply", 6, 1, 1, EJEZ);
   objrevolucion2->setMaterial(cobre);

   // .....

   //luces

   luzPosicional = new LuzPosicional({200, 150, 200}, GL_LIGHT1, {0.6, 0.0, 0.0, 1.0}, {0.6, 0.0, 0.0, 1.0}, {0.6, 0.0, 0.0, 1.0});

   luzDireccional = new LuzDireccional({10, 10, 4}, GL_LIGHT2, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0});

   // camaras
   camaras[0] = new Camara({0, 100, 2000}, {0, 0, 0}, {0, 1, 0}, PERSPECTIVA, 100, 20000);
   camaras[1] = new Camara({0, 200, 300}, {0, 0, 0}, {0, 1, 0}, ORTOGONAL, 100, 3000);
   camaras[2] = new Camara({0, 100, 200}, {0, 0, 0}, {0, 1, 0}, PERSPECTIVA, 100, 3000);
   cam = 0;
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar(int UI_window_width, int UI_window_height)
{
   glClearColor(1.0, 1.0, 1.0, 1.0); // se indica cual sera el color para limpiar la ventana	(r,v,a,al)

   glEnable(GL_DEPTH_TEST); // se habilita el z-bufer
   glEnable(GL_NORMALIZE);

   for (int i = 0; i < 3; i++)
   {
      camaras[i]->nuevoLeft(-UI_window_width / 10);
      camaras[i]->nuevoRight(UI_window_width / 10);
      camaras[i]->nuevoTop(UI_window_height / 10);
      camaras[i]->nuevoBottom(-UI_window_height / 10);
   }

   change_projection();
   change_observer();
   glViewport(0, 0, UI_window_width, UI_window_height);
   menuInicial();
}

//**************************************************************************
//
// Iniciar los objetos de la escena inicial
//
//**************************************************************************
void Escena::pintarObjetos()
{
   if (suelo != nullptr && bSuelo)
   {
      glPushMatrix();
      glTranslatef(-1000, 0, 1000);
      glRotatef(-90, 1, 0, 0);
      glScalef(2000, 2000, 2000);
      suelo->draw(modoDibujo, ajedrez, alambre, solido, puntos, luz, false, false);
      glPopMatrix();
   }
   if (cubo != nullptr && bCubo)
   {
      glPushMatrix();
      glTranslatef(-100, 25, 0);
      if (visualizacionMenu == LIMPIA)
         cubo->draw(modoDibujo, ajedrez, alambre, solido, puntos, luz, false, false);
      else
         cubo->draw(modoDibujo, ajedrez, alambre, solido, puntos, luz, false, true);

      glPopMatrix();
   }
   if (objrevolucion != nullptr && bPeon)
   {
      glPushMatrix();
      glTranslatef(150, 40, 0);
      glScalef(30, 30, 30);
      objrevolucion->pintarConTapas(modoDibujo, ajedrez, alambre, solido, puntos, luz, tapas, false);
      glPopMatrix();
   }
   if (objply != nullptr && bHormiga)
   {
      glPushMatrix();
      glTranslatef(125, 40, -130);
      glScalef(4, 4, 4);
      objply->draw(modoDibujo, ajedrez, alambre, solido, puntos, luz, false, false);
      objply->setMaterial(cobre);
      glPopMatrix();
   }
   if (tetraedro != nullptr && bTetraedro)
   {
      glPushMatrix();
      glTranslatef(0, 40, -200);
      tetraedro->draw(modoDibujo, ajedrez, alambre, solido, puntos, luz, false, false);
      glPopMatrix();
   }
   if (esfera != nullptr && bEsfera)
   {

      glPushMatrix();
      glTranslatef(50, 40, -70);

      glScalef(3, 3, 3);
      if (visualizacionMenu == LIMPIA)
         esfera->draw(modoDibujo, ajedrez, alambre, solido, puntos, luz, false, false);

      else
         esfera->draw(modoDibujo, ajedrez, alambre, solido, puntos, luz, false, true);

      glPopMatrix();
   }
   if (cono != nullptr && bCono)
   {
      glPushMatrix();
      glTranslatef(180, 0, -60);
      glScalef(5, 5, 5);
      cono->draw(modoDibujo, ajedrez, alambre, solido, puntos, luz, false, false);
      glPopMatrix();
   }
   if (cilindro != nullptr && bCilindro)
   {
      glPushMatrix();
      glTranslatef(-80, 0, -110);
      glScalef(5, 5, 5);
      cilindro->draw(modoDibujo, ajedrez, alambre, solido, puntos, luz, false, false);
      glPopMatrix();
   }
   if (catapulta != nullptr && bCatapulta)
   {
      glPushMatrix();
      if (visualizacionMenu == LIMPIA)
         catapulta->draw(modoDibujo, ajedrez, alambre, solido, puntos, luz, false, false);

      else
         catapulta->draw(modoDibujo, ajedrez, alambre, solido, puntos, luz, false, true);

      glPopMatrix();
   }
}
//**************************************************************************

//**************************************************************************
void Escena::pintarObjetosSeleccion()
{
   if (cubo != nullptr && bCubo)
   {
      glPushMatrix();
      glTranslatef(-100, 25, 0);
      cubo->draw(modoDibujo, false, false, false, false, false, true, false);

      glPopMatrix();
   }
   if (esfera != nullptr && bEsfera)
   {

      glPushMatrix();
      glTranslatef(50, 40, -70);

      glScalef(3, 3, 3);
      esfera->draw(modoDibujo, false, false, false, false, false, true, false);
      glPopMatrix();
   }
   if (catapulta != nullptr && bCatapulta)
   {
      glPushMatrix();
      catapulta->draw(modoDibujo, false, false, false, false, false, true, false);
      glPopMatrix();
   }
}
//**************************************************************************
// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla
   change_observer();
   glDisable(GL_LIGHTING);
   ejes.draw();

   // COMPLETAR
   //   Dibujar los diferentes elementos de la escena
   // Habrá que tener en esta primera práctica una variable que indique qué objeto se ha de visualizar
   // y hacer
   // cubo.draw()
   // o
   // tetraedro.draw()
   // cubo->draw(false);
   //tetraedro->draw(false);
   //GLfloat lmodel_ambient[] = {1.0, 1.0, 1.0, 1.0};
   //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
   switch (dibujoMenu)
   {
   case INMEDIATO:
      modoDibujo = true;
      break;
   case DIFERIDO:
      modoDibujo = false;
      break;
   }
   switch (visualizacionMenu)
   {
   case AJEDREZ:
      ajedrez = true;
      luz = false;
      break;
   case PUNTOS:
      puntos = true;
      luz = false;
      break;
   case LUZ:
      luz = true;
      break;
   case ALAMBRE:
      alambre = true;
      luz = false;
      break;
   case SOLIDO:
      solido = true;
      luz = false;
      break;
   case LIMPIA:
      solido = false;
      alambre = false;
      puntos = false;
      ajedrez = false;
      luz = false;
      break;
   }
   if (luz)
   {
      glEnable(GL_LIGHTING);
      glPushMatrix();
      if (bLuzDireccional)
         luzDireccional->activar();
      glRotatef(luzAnimada, 0.0f, 1.0f, 1.0f);
      if (bLuzPosicional)
         luzPosicional->activar();
      glPopMatrix();
   }
   else
   {
      glDisable(GL_LIGHTING);
      luzPosicional->desactivar();
      luzDireccional->desactivar();
   }

   pintarObjetos();
}

//**************************************************************************
//
// Muestra el menu inical
//
//**************************************************************************

void Escena::animacion()
{
   if (bLuzSituacional)
   {
      luzAnimada = luzAnimada + 1;
      luzAnimada = fmod(luzAnimada, 360);
   }
   if (bAnimacion)
   {
      catapulta->animar();
   }
}
//**************************************************************************
//
// Muestra el menu inical
//
//**************************************************************************
void Escena::menuInicial()
{
   using namespace std;
   cout << endl;
   cout << "Estos son los menus disponibles: " << endl;
   cout << "\t - Pulsa O: Menu selección de objeto " << endl;
   cout << "\t - Pulsa V: Menu de visualización " << endl;
   cout << "\t - Pulsa D: Modo dibujado " << endl;
   cout << "\t - Pulsa A: Animación automática" << endl;
   cout << "\t - Pulsa M: Mover Manualmente los grados de libertad" << endl;
   cout << "\t - Pulsa C: Menu de camaras" << endl;
}
//**************************************************************************

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada(unsigned char tecla, int x, int y)
{
   using namespace std;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir = false;
   switch (modoMenu)
   {
   case NADA:
      switch (toupper(tecla))
      {
      case 'Q':
         salir = true;
         break;
      case 'O':
         // ESTAMOS EN MODO SELECCION DE OBJETO
         modoMenu = SELOBJETO;
         cout << "Estas en el menu seleccion de objeto estas son las opciones: " << endl;
         cout << "\t - Pulsa C: Para dibujar el cubo " << endl;
         cout << "\t - Pulsa T: Para dibujar el tetraedro " << endl;
         cout << "\t - Pulsa H: Para dibujar la hormiga " << endl;
         cout << "\t - Pulsa P: Para dibujar la peon " << endl;
         cout << "\t - Pulsa E: Para dibujar la esfera " << endl;
         cout << "\t - Pulsa O: Para dibujar la cono " << endl;
         cout << "\t - Pulsa I: Para dibujar la cilindro " << endl;
         cout << "\t - Pulsa S: Para dibujar el suelo " << endl;
         cout << "\t - Pulsa J: Para dibujar el modelo jerarquico(catapulta) " << endl;
         cout << "\t - Pulsa Q: Para salir del menu " << endl;

         break;
      case 'V':
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu = SELVISUALIZACION;
         cout << "Estas en el menu seleccion de visualizacion estas son las opciones: " << endl;
         cout << "\t - Pulsa Z: Para dibujar modo ajedrez " << endl;
         cout << "\t - Pulsa A: Para dibujar modo alambre " << endl;
         cout << "\t - Pulsa P: Para dibujar modo puntos " << endl;
         cout << "\t - Pulsa S: Para dibujar modo solido " << endl;
         cout << "\t - Pulsa I: Para activar modo iluminacion " << endl;
         cout << "\t - Pulsa T: Para quitar las tapas " << endl;
         cout << "\t - Pulsa N: Para limpiar los modos " << endl;
         cout << "\t - Pulsa Q: Para salir del menu " << endl;
         break;
      case 'D':
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu = SELDIBUJADO;
         cout << "Estas en el menu de dibujado: " << endl;
         cout << "\t - Pulsa I: Para dibujar en modo inmediato " << endl;
         cout << "\t - Pulsa D: Para dibujar en modo diferido " << endl;
         cout << "\t - Pulsa Q: Para salir del menu " << endl;
         break;
      case 'M':
         modoMenu = GRADOLIBERTAD;
         cout << "Estas en el menu para mover el grado de libertad: " << endl;
         cout << "\t - Pulsa W: Para aumentar la altura de la catapulta" << endl;
         cout << "\t - Pulsa E: Para disminuir la altura de la catapulta" << endl;
         cout << "\t - Pulsa S: Para rotar la catapulta " << endl;
         cout << "\t - Pulsa D: Para rotar(otro lado) la catapulta " << endl;
         cout << "\t - Pulsa X: Para lanzar la cuchara " << endl;
         cout << "\t - Pulsa C: Para recoger la cuchara " << endl;
         cout << "\t - Pulsa Q: Para salir del menu " << endl;

         break;
      case 'A':
         modoMenu = ANIMACION;
         bAnimacion = true;
         cout << "Estas en el menu de animación: " << endl;
         cout << "\t - Pulsa W: Para aumentar la velocidad de altura de la catapulta" << endl;
         cout << "\t - Pulsa E: Para disminuir la velocidad de altura de la catapulta" << endl;
         cout << "\t - Pulsa S: Para aumentar la velocidad de rotar la catapulta " << endl;
         cout << "\t - Pulsa D: Para disminuir la velocidad de rotar la catapulta " << endl;
         cout << "\t - Pulsa X: Para aumentar la velocidad de lanzar la cuchara " << endl;
         cout << "\t - Pulsa C: Para disminuir la velocidad de recoger la cuchara " << endl;
         cout << "\t - Pulsa R: Para aumentar todas las velocidades" << endl;
         cout << "\t - Pulsa T: Para disminuir todas las velocidades " << endl;
         cout << "\t - Pulsa Q: Para salir del menu " << endl;

         break;

      case 'C':
         modoMenu = CAMARAS;
         cout << "Estas en el menu de camaras: " << endl;
         cout << "\t - Pulsa Q: Para salir del menu " << endl;
         cout << "\t - Pulsa 1: Para seleccionar la cámara 1 " << endl;
         cout << "\t - Pulsa 2: Para seleccionar la cámara 2 " << endl;
         cout << "\t - Pulsa 3: Para seleccionar la cámara 3 " << endl;

         break;

         // COMPLETAR con los diferentes opciones de teclado
      }
      break;
   case SELOBJETO:
      switch (toupper(tecla))
      {
      case 'Q':
         menuInicial();
         if (modoMenu != NADA)
            modoMenu = NADA;
         break;
      case 'C':
         // ESTAMOS EN MODO SELECCION DE OBJETO
         if (bCubo)
            bCubo = false;
         else
            bCubo = true;
         break;
      case 'T':
         // ESTAMOS EN MODO SELECCION DE OBJETO
         if (bTetraedro)
            bTetraedro = false;
         else
            bTetraedro = true;
         break;
      case 'H':
         // ESTAMOS EN MODO SELECCION DE OBJETO
         if (bHormiga)
            bHormiga = false;
         else
            bHormiga = true;
         break;
      case 'P':
         // ESTAMOS EN MODO SELECCION DE OBJETO
         if (bPeon)
            bPeon = false;
         else
            bPeon = true;
         break;
      case 'E':
         // ESTAMOS EN MODO SELECCION DE OBJETO
         if (bEsfera)
            bEsfera = false;
         else
            bEsfera = true;
         break;
      case 'O':
         // ESTAMOS EN MODO SELECCION DE OBJETO
         if (bCono)
            bCono = false;
         else
            bCono = true;
         break;
      case 'I':
         // ESTAMOS EN MODO SELECCION DE OBJETO
         if (bCilindro)
            bCilindro = false;
         else
            bCilindro = true;
         break;
      case 'S':
         // ESTAMOS EN MODO SELECCION DE OBJETO
         if (bSuelo)
            bSuelo = false;
         else
            bSuelo = true;
         break;
      case 'J':
         // ESTAMOS EN MODO SELECCION DE OBJETO
         if (bCatapulta)
            bCatapulta = false;
         else
            bCatapulta = true;
         break;
      }
      break;
   case SELDIBUJADO:
      switch (toupper(tecla))
      {
      case 'Q':
         menuInicial();
         if (modoMenu != NADA)
            modoMenu = NADA;
         break;
      case 'I':
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         dibujoMenu = INMEDIATO;

         break;
      case 'D':
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         dibujoMenu = DIFERIDO;

         break;
      }
      break;
   case SELVISUALIZACION:
      switch (toupper(tecla))
      {
      case 'Q':
         menuInicial();
         if (modoMenu != NADA)
            modoMenu = NADA;
         break;
      case 'Z':
         // ESTAMOS EN MODO SELECCION DE VISUALIZACION
         visualizacionMenu = AJEDREZ;
         break;
      case 'A':
         // ESTAMOS EN MODO SELECCION DE VISUALIZACION
         visualizacionMenu = ALAMBRE;
         break;
      case 'P':
         // ESTAMOS EN MODO SELECCION DE VISUALIZACION
         visualizacionMenu = PUNTOS;
         break;
      case 'S':
         // ESTAMOS EN MODO SELECCION DE VISUALIZACION
         visualizacionMenu = SOLIDO;
         break;
      case 'I':
         // ESTAMOS EN MODO SELECCION DE VISUALIZACION
         visualizacionMenu = LUZ;
         modoMenu = LUCES;
         cout << "Estas en el menu de iluminación: " << endl;
         cout << "\t - Pulsa 1: Para activar/desactivar la luz direccional" << endl;
         cout << "\t - Pulsa 2: Para activar/desactivar la luz posicional" << endl;
         cout << "\t - Pulsa W: Para incrementar angulo alfa " << endl;
         cout << "\t - Pulsa E: Para decrementar el angulo alfa " << endl;
         cout << "\t - Pulsa S: Para incrementar el angulo beta " << endl;
         cout << "\t - Pulsa D: Para decrementar el angulo beta " << endl;
         cout << "\t - Pulsa P: Para animar la luz puntual " << endl;
         cout << "\t - Pulsa Q: Para salir del menu " << endl;
         break;
      case 'N':
         // ESTAMOS EN MODO SELECCION DE VISUALIZACION
         visualizacionMenu = LIMPIA;
         break;
      case 'T':
         // ESTAMOS EN MODO SELECCION DE VISUALIZACION
         if (tapas)
            tapas = false;
         else
            tapas = true;
         break;
      }
      break;
   case LUCES:
      switch (toupper(tecla))
      {
      case 'Q':
         menuInicial();
         bLuzSituacional = false;

         if (modoMenu != NADA)
            modoMenu = NADA;
         break;
      case 'P':
         if (bLuzSituacional)
            bLuzSituacional = false;
         else
            bLuzSituacional = true;
         break;
      case 'W':
         luzDireccional->variarAnguloAlfa(1);
         break;
      case 'E':
         luzDireccional->variarAnguloAlfa(-1);
         break;
      case 'S':
         luzDireccional->variarAnguloBeta(1);
         break;
      case 'D':
         luzDireccional->variarAnguloBeta(-1);
         break;
      case '1':
         if (bLuzDireccional)
         {
            bLuzDireccional = false;
            luzDireccional->desactivar();
         }
         else
         {
            bLuzDireccional = true;
            luzDireccional->activar();
         }

         break;
      case '2':
         if (bLuzPosicional)
         {
            bLuzPosicional = false;
            luzPosicional->desactivar();
         }
         else
         {
            bLuzPosicional = true;
            luzPosicional->activar();
         }
         break;
      }
      break;
      break;
   case GRADOLIBERTAD:
      switch (toupper(tecla))
      {
      case 'Q':
         menuInicial();
         if (modoMenu != NADA)
            modoMenu = NADA;
         break;
      case 'W':
         catapulta->alturaCatapulta(0.1);
         break;
      case 'E':
         catapulta->alturaCatapulta(-0.1);

         break;
      case 'S':
         catapulta->rotacionCatapulta(10);
         break;
      case 'D':
         catapulta->rotacionCatapulta(-10);
         break;
      case 'X':
         catapulta->rotacionCuchara(10);
         break;
      case 'C':
         catapulta->rotacionCuchara(-10);
         break;
      }
      break;
   case ANIMACION:
      switch (toupper(tecla))
      {
      case 'Q':
         bAnimacion = false;
         menuInicial();
         if (modoMenu != NADA)
            modoMenu = NADA;
         break;
      case 'W':
         catapulta->modificarVelocidadAnimacionAltura(1.1);
         break;
      case 'E':
         catapulta->modificarVelocidadAnimacionAltura(0.9);

         break;
      case 'S':
         catapulta->modificarVelocidadAnimacionRotacion(1.1);
         break;
      case 'D':
         catapulta->modificarVelocidadAnimacionRotacion(0.9);
         break;
      case 'X':
         catapulta->modificarVelocidadAnimacionCuchara(1.1);
         break;
      case 'C':
         catapulta->modificarVelocidadAnimacionCuchara(0.9);
         break;
      case 'R':
         catapulta->modificarVelocidad(1.1);
         break;
      case 'T':
         catapulta->modificarVelocidad(0.9);
         break;
      }
      break;
   case CAMARAS:
      switch (toupper(tecla))
      {
      case 'Q':
         menuInicial();
         if (modoMenu != NADA)
            modoMenu = NADA;
         break;
      case '1':
         cambiaCamara(0);
         break;
      case '2':
         cambiaCamara(1);
         break;
      case '3':
         cambiaCamara(2);
         break;
      }

      break;
   }

   return salir;
}

void Escena::teclaEspecial(int Tecla1, int x, int y)
{
   switch (Tecla1)
   {
   case GLUT_KEY_LEFT:
      camaras[cam]->rotarYExaminar(-1 * (M_PI / 180));
      break;
   case GLUT_KEY_RIGHT:
      camaras[cam]->rotarYExaminar(1 * (M_PI / 180));

      break;
   case GLUT_KEY_UP:
      camaras[cam]->rotarXExaminar(-1 * (M_PI / 180));

      break;
   case GLUT_KEY_DOWN:
      camaras[cam]->rotarXExaminar(1 * (M_PI / 180));

      break;
   case GLUT_KEY_PAGE_UP:
      camaras[cam]->zoom(0.9);
      break;
   case GLUT_KEY_PAGE_DOWN:
      camaras[cam]->zoom(1.1);
      break;
   }
   change_projection();
   //std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection()
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   camaras[cam]->setProyeccion();
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar(int newWidth, int newHeight)
{

   float factor = (float)newWidth / (float)newHeight;

   for (int i = 0; i < 3; i++)
   {
      camaras[i]->nuevoRight(camaras[i]->getTop() * factor);
      camaras[i]->nuevoLeft(camaras[i]->getBottom() * factor);
   }
   change_projection();
   glViewport(0, 0, newWidth, newHeight);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   camaras[cam]->setObserver();
}

//**************************************************************************
// Funcion para cambiar la camara
//***************************************************************************

void Escena::cambiaCamara(int n)
{
   cam = n;
   change_observer();
   change_projection();
}

//**************************************************************************
// Funcion para controlar con el raton
//***************************************************************************

void Escena::clickRaton(int boton, int estado, int x, int y)
{
   xant = x;
   yant = y;
   switch (boton)
   {
   case GLUT_RIGHT_BUTTON:
      if (estado == GLUT_DOWN)
      {
         if (camaras[cam]->getObjeto() == CAMNINGUNO)
            estadoRaton = MOVIENDO_CAMARA_FIRSTPERSON;
         else
            estadoRaton = MOVIENDO_CAMARA_EXAMINAR;
      }
      else
      {
         estadoRaton = QUIETA;
      }
      break;
   case GLUT_LEFT_BUTTON:
      if (estado == GLUT_UP)
      {
         //se crea la escena "para seleccionar"
         dibujaSeleccion();
         //se lee el pixel del evento del raton
         clickObjeto(x, y);
      }
      break;
   case 3: //Rueda del raton hacia arriba
      camaras[cam]->zoom(0.9);
      break;
   case 4: //Rueda del raton hacia abajo
      camaras[cam]->zoom(1.1);
      break;
   }
   change_projection();
}

void Escena::ratonMovido(int x, int y)
{
   if (estadoRaton == MOVIENDO_CAMARA_EXAMINAR)
   {
      camaras[cam]->girarExaminar(x - xant, y - yant);
      xant = x;
      yant = y;
   }
   else if (estadoRaton == MOVIENDO_CAMARA_FIRSTPERSON)
   {
      camaras[cam]->girarFirstPerson(x - xant, y - yant);
      xant = x;
      yant = y;
   }
}

void Escena::dibujaSeleccion()
{
   //Desactivar el degradado, luego se vuelve a reactivar
   glDisable(GL_DITHER);
   glDisable(GL_LIGHTING);
   glDisable(GL_TEXTURE);

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla
   glPolygonMode(GL_FRONT, GL_FILL);

   change_observer();

   pintarObjetosSeleccion();

   glEnable(GL_DITHER);
   glEnable(GL_LIGHTING);
   glEnable(GL_TEXTURE);
}

//process pick
void Escena::clickObjeto(int x, int y)
{
   glDisable(GL_DITHER);
   glDisable(GL_LIGHTING);
   glDisable(GL_TEXTURE);

   GLint viewport[4];
   GLubyte pixel[3];

   glGetIntegerv(GL_VIEWPORT, viewport);

   glReadPixels(x, viewport[3] - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, (void *)pixel);

   Tupla3i pixelClickado = {pixel[0], pixel[1], pixel[2]};

   std::cout << "prueba " << pixelClickado[0] << " " << pixelClickado[1] << " " << pixelClickado[2] << " xx" << std::endl;

   Tupla3i cubo = {127, 0, 127};
   Tupla3i catapulta = {127, 127, 0};
   Tupla3i esfera = {0, 127, 127};

   if (pixelClickado[0] == cubo[0] && pixelClickado[1] == cubo[1] && pixelClickado[2] == cubo[2])
   {
      // camaras[cam]->mover
      std::cout << " esto es el cubo bro " << std::endl;
      camaras[cam]->setObjeto(CAMCUBO);
      camaras[cam]->setAt(-100,25,0);
   }
   else if (pixelClickado[0] == catapulta[0] && pixelClickado[1] == catapulta[1] && pixelClickado[2] == catapulta[2])
   {
      std::cout <<" esto es la catapulta bro " << std::endl;
      camaras[cam]->setObjeto(CAMCATAPULTA);
      camaras[cam]->setAt(0,50,0);
   }
   else if (pixelClickado[0] == esfera[0] && pixelClickado[1] == esfera[1] && pixelClickado[2] == esfera[2])
   {
      camaras[cam]->setObjeto(CAMESFERA);
      std::cout <<" esto es la esfera bro " << std::endl;
      camaras[cam]->setAt(50,40,-70);
   }else{
      camaras[cam]->setObjeto(CAMNINGUNO);

   }
   glEnable(GL_DITHER);
   glEnable(GL_LIGHTING);
   glEnable(GL_TEXTURE);
}