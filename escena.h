#ifndef _ESCENA_H
#define _ESCENA_H

#include "aux.h"
#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "esfera.h"
#include "cono.h"
#include "cuadro.h"
#include "cilindro.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "material.h"
#include "catapulta.h"
#include "luz.h"
#include "luzposicional.h"
#include "luzdireccional.h"
#include "camara.h"

typedef enum
{
    NADA,
    SELOBJETO,
    SELVISUALIZACION,
    SELDIBUJADO,
    LUCES,
    GRADOLIBERTAD,
    ANIMACION,
    CAMARAS
} menu;
typedef enum
{
    NINGUNO,
    TETRAEDRO,
    CUBO,
    HORMIGA,
    ESFERA,
    CONO,
    CILINDRO,
    PEON
} objeto;
typedef enum
{
    INMEDIATO,
    DIFERIDO
} dibujo;
typedef enum
{
    AJEDREZ,
    ALAMBRE,
    SOLIDO,
    PUNTOS,
    LUZ,
    LIMPIA
} visualizacion;
class Escena
{

private:
    // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)

    // variables que definen la posicion de la camara en coordenadas polares
    GLfloat Observer_distance;
    GLfloat Observer_angle_x;
    GLfloat Observer_angle_y;

    // variables que controlan la ventana y la transformacion de perspectiva
    GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
    void change_projection();
    void change_observer();

    void clear_window();

    menu modoMenu = NADA;
    objeto objetoMenu;
    dibujo dibujoMenu = DIFERIDO;
    visualizacion visualizacionMenu = SOLIDO;
    bool modoDibujo;                            // Inmediato o diferido
    bool ajedrez, solido, puntos, alambre, luz; //modo de visualización
    bool tapas = true;
    bool bAnimacion = false, bLuzSituacional = false;
    bool bLuzDireccional = true, bLuzPosicional = true;
    bool bCubo = true, bSuelo = true, bTetraedro = true, bPeonTapa = true, bPeon = true, bHormiga = true, bEsfera = true, bCono = true, bCilindro = true, bCatapulta = true;
    float luzAnimada = 0.0f;
    //modo de visualización
    // Objetos de la escena
    Ejes ejes;

    //objetos
    Cubo *cubo = nullptr;                    // es importante inicializarlo a 'nullptr'
    Tetraedro *tetraedro = nullptr;          // es importante inicializarlo a 'nullptr'
    Esfera *esfera = nullptr;                // es importante inicializarlo a 'nullptr'
    Cono *cono = nullptr;                    // es importante inicializarlo a 'nullptr'
    Cilindro *cilindro = nullptr;            // es importante inicializarlo a 'nullptr'
    Malla3D *malla = nullptr;                // es importante inicializarlo a 'nullptr'
    ObjPLY *objply = nullptr;                // es importante inicializarlo a 'nullptr'
    ObjRevolucion *objrevolucion = nullptr;  // es importante inicializarlo a 'nullptr'
    ObjRevolucion *objrevolucion2 = nullptr; // es importante inicializarlo a 'nullptr'
    ObjRevolucion *objrevolucion3 = nullptr; // es importante inicializarlo a 'nullptr'
    Catapulta *catapulta = nullptr;          // es importante inicializarlo a 'nullptr'
    Cuadro *suelo = nullptr;                 // es importante inicializarlo a 'nullptr'

    //Luces
    LuzPosicional *luzPosicional = nullptr;
    LuzDireccional *luzDireccional = nullptr;
    //Materiales
    Material *oro = nullptr;
    Material *cobre = nullptr;
    Material *blanco = nullptr;
    Material *negro = nullptr;

    //Camaras
    Camara *camaras[3];
    int cam;


public:
    Escena();
    void inicializar(int UI_window_width, int UI_window_height);
    void redimensionar(int newWidth, int newHeight);
    void menuInicial();
    void pintarObjetos();
    void animacion();
    // Dibujar
    void dibujar();
    void cambiaCamara(int n);

    // Interacción con la escena
    bool teclaPulsada(unsigned char Tecla1, int x, int y);
    void teclaEspecial(int Tecla1, int x, int y);
};
#endif
