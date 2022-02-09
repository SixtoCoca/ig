// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "ply_reader.h"

typedef enum
{
    EJEX,
    EJEY,
    EJEZ
} eje;
// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class ObjRevolucion : public Malla3D
{
public:
    ObjRevolucion();
    ObjRevolucion(const std::string &archivo, int num_instancias, bool tapa_sup = true, bool tapa_inf = true, eje ejeR = EJEY);
    ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup = true, bool tapa_inf = true, eje ejeR = EJEY);
    void pintarConTapas(bool modo, bool ajedrez, bool alambre, bool solido, bool puntos, bool luz, bool tapas,bool seleccionado);

protected:
    std::vector<Tupla3f> perfil;
    eje ejeRevolucion = EJEY;
    int numInstancias,tamSinTapas,tamConTapas;
    Tupla3f verticeTapaSuperior = {1, 1, 1}; //Lo inicializo a 1,1,1 porque este nunca puede ser el vertice de una tapa
    Tupla3f verticeTapaInferior = {1, 1, 1}; // que venga del perfil
    void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_sup, bool tapa_inf);

private:
    std::vector<Tupla3f> sentido(std::vector<Tupla3f> perfil_original);
    Tupla3f tieneVerticeSuperior(std::vector<Tupla3f> perfil_original);
    Tupla3f tieneVerticeInferior(std::vector<Tupla3f> perfil_original);
    void crearTapaSuperior(int num_instancias, bool tapa_sup);
    void crearTapaInferior(int num_instancias, bool tapa_inf);
    // void asignarPuntosTextura() override;
};

#endif
