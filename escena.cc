

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
   cubo->setMaterial(oro);
   catapulta = new Catapulta();
   tetraedro = new Tetraedro(100);
   tetraedro->setMaterial(oro);
   esfera = new Esfera(20, 20, 10);
   esfera->setMaterial(cobre);

   cono = new Cono(10, 50, 10, 5, EJEZ);
   cono->setMaterial(oro);
   cilindro = new Cilindro(5.0, 10.0, 10.0, 5, EJEZ);
   cilindro->setMaterial(oro);
   objply = new ObjPLY("plys/ant.ply");
   objply->setMaterial(oro);
   objrevolucion = new ObjRevolucion("plys/peon.ply", 6, 1, 1, EJEY);
   objrevolucion->setMaterial(blanco);
   objrevolucion2 = new ObjRevolucion("plys/peonx.ply", 6, 1, 1, EJEZ);
   objrevolucion2->setMaterial(negro);
   objrevolucion3 = new ObjRevolucion("plys/peonz.ply", 6, 1, 1, EJEZ);
   objrevolucion3->setMaterial(negro);
   // .....

   //luces

   luzPosicional = new LuzPosicional({0, 0, 0}, GL_LIGHT1, {0.6, 0.0, 0.0, 1.0}, {0.6, 0.0, 0.0, 1.0}, {0.6, 0.0, 0.0, 1.0});

   luzDireccional = new LuzDireccional({10, 10, 4}, GL_LIGHT2, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0});
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

   Width = UI_window_width / 10;
   Height = UI_window_height / 10;

   change_projection(float(UI_window_width) / float(UI_window_height));
   glViewport(0, 0, UI_window_width, UI_window_height);
}

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
      luzPosicional->activar();
      luzDireccional->activar();
   }
   else
   {
      glDisable(GL_LIGHTING);
      luzPosicional->desactivar();
      luzDireccional->desactivar();
   }
   switch (objetoMenu)
   {
   case HORMIGA:
      bHormiga = true;
      break;
   case TETRAEDRO:
      bTetraedro = true;
      break;
   case CUBO:
      bCubo = true;
      break;
   case ESFERA:
      bEsfera = true;
      break;
   case PEON:
      bPeon = true;
      break;
   case CONO:
      bCono = true;
      break;
   case CILINDRO:
      bCilindro = true;
      break;
   case NINGUNO:
      bHormiga = false;
      bTetraedro = false;
      bCubo = false;
      bPeon = false;
      bEsfera = false;
      bCono = false;
      bCilindro = false;

      break;
   }

   if (objrevolucion != nullptr && objrevolucion2 != nullptr && bPeon)
   {
      // luzDireccional->variarAnguloAlfa(40*M_PI/180);
      glPushMatrix();
      glTranslatef(150, 0, 0);
      glScalef(30, 30, 30);
      objrevolucion->draw(modoDibujo, ajedrez, alambre, solido, puntos, luz);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(-150, 0, 0);
      glScalef(30, 30, 30);
      objrevolucion2->draw(modoDibujo, ajedrez, alambre, solido, puntos, luz);

      glPopMatrix();
   }
   if (objply != nullptr && bHormiga)
   {
      glPushMatrix();
      glTranslatef(125, 0, -130);
      glScalef(4, 4, 4);
      objply->draw(modoDibujo, ajedrez, alambre, solido, puntos, luz);
      objply->setMaterial(cobre);
      glPopMatrix();
   }
   if (cubo != nullptr && bCubo)
   {
      catapulta->rotacionCuchara(20);
      glPushMatrix();
      glTranslatef(-40, 0, -50);
      cubo->draw(modoDibujo, ajedrez, alambre, solido, puntos, luz);
      glPopMatrix();
   }
   if (tetraedro != nullptr && bTetraedro)
   {
      glPushMatrix();
      catapulta->draw(modoDibujo, ajedrez, alambre, solido, puntos, luz);
      // glTranslatef(0, 0, -200);
      // tetraedro->draw(modoDibujo, ajedrez, alambre, solido, puntos, luz);
      glPopMatrix();
   }
   if (esfera != nullptr && bEsfera)
   {
      catapulta->rotacionCuchara(-20);
      catapulta->alturaCatapulta(2);
      catapulta->rotacionCatapulta(30);

      glPushMatrix();
      glTranslatef(40, 0, -50);

      glScalef(3, 3, 3);
      esfera->draw(modoDibujo, ajedrez, alambre, solido, puntos, luz);
      glPopMatrix();
   }
   if (cono != nullptr && bCono)
   {
      glPushMatrix();
      glTranslatef(180, 0, -60);
      glScalef(5, 5, 5);
      cono->draw(modoDibujo, ajedrez, alambre, solido, puntos, luz);
      glPopMatrix();
   }
   if (cilindro != nullptr && bCilindro)
   {
      glPushMatrix();
      glTranslatef(-80, 0, -110);
      glScalef(5, 5, 5);
      cilindro->draw(modoDibujo, ajedrez, alambre, solido, puntos, luz);
      glPopMatrix();
   }
}

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
         cout << "\t - Pulsa N: Para limpiarlo " << endl;
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

         // COMPLETAR con los diferentes opciones de teclado
      }
      break;
   case SELOBJETO:
      switch (toupper(tecla))
      {
      case 'Q':
         if (modoMenu != NADA)
            modoMenu = NADA;
         break;
      case 'C':
         // ESTAMOS EN MODO SELECCION DE OBJETO
         objetoMenu = CUBO;
         break;
      case 'T':
         // ESTAMOS EN MODO SELECCION DE OBJETO
         objetoMenu = TETRAEDRO;
         break;
      case 'H':
         // ESTAMOS EN MODO SELECCION DE OBJETO
         objetoMenu = HORMIGA;
         break;
      case 'P':
         // ESTAMOS EN MODO SELECCION DE OBJETO
         objetoMenu = PEON;
         break;
      case 'E':
         // ESTAMOS EN MODO SELECCION DE OBJETO
         objetoMenu = ESFERA;
         break;
      case 'O':
         // ESTAMOS EN MODO SELECCION DE OBJETO
         objetoMenu = CONO;
         break;
      case 'I':
         // ESTAMOS EN MODO SELECCION DE OBJETO
         objetoMenu = CILINDRO;
         break;
      case 'N':
         // ESTAMOS EN MODO SELECCION DE OBJETO
         objetoMenu = NINGUNO;
         break;
      }
      break;
   case SELDIBUJADO:
      switch (toupper(tecla))
      {
      case 'Q':
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
         break;
      case 'N':
         // ESTAMOS EN MODO SELECCION DE VISUALIZACION
         visualizacionMenu = LIMPIA;
         break;
      }
      break;
   }

   return salir;
}
//**************************************************************************

void Escena::teclaEspecial(int Tecla1, int x, int y)
{
   switch (Tecla1)
   {
   case GLUT_KEY_LEFT:
      Observer_angle_y--;
      break;
   case GLUT_KEY_RIGHT:
      Observer_angle_y++;
      break;
   case GLUT_KEY_UP:
      Observer_angle_x--;
      break;
   case GLUT_KEY_DOWN:
      Observer_angle_x++;
      break;
   case GLUT_KEY_PAGE_UP:
      Observer_distance *= 1.2;
      break;
   case GLUT_KEY_PAGE_DOWN:
      Observer_distance /= 1.2;
      break;
   }

   //std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection(const float ratio_xy)
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   const float wx = float(Height) * ratio_xy;
   glFrustum(-wx, wx, -Height, Height, Front_plane, Back_plane);
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar(int newWidth, int newHeight)
{
   Width = newWidth / 10;
   Height = newHeight / 10;
   change_projection(float(newHeight) / float(newWidth));
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
   glTranslatef(0.0, 0.0, -Observer_distance);
   glRotatef(Observer_angle_y, 0.0, 1.0, 0.0);
   glRotatef(Observer_angle_x, 1.0, 0.0, 0.0);
}
