// Nombre: Antonio, Apellidos: Luzón Ventura, Titulación: GIIADE.
// email: luzonventura@correo.ugr.es, DNI o pasaporte: 77448897P

#ifndef MODELO_JER_HPP
#define MODELO_JER_HPP

#include "grafo-escena.h"
#include "malla-ind.h"
#include "ig-aux.h"
#include "malla-revol.h"

using namespace std;
using namespace glm;

class Molino : public NodoGrafoEscena {
    protected:
        mat4 *pm_rot_aspas = nullptr;
        mat4 *pm_rot_puerta = nullptr;
        mat4 *pm_rot_nubes = nullptr;
        mat4 *pm_rot_sol = nullptr;
    public:
        unsigned leerNumParametros() const;
        virtual void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
        Molino();
};

class CilindroMolino : public MallaRevol {
    public:
        CilindroMolino(const int num_verts_per, const unsigned nperfiles, float altura, float radio);
};

class ConoMolino : public MallaRevol {
    public:
        ConoMolino(const int num_verts_per, const unsigned nperfiles);
};

class CirculoMolino : public MallaInd {
    public:
        CirculoMolino(float radio, const int num_verts);
};

class CuboMolino : public MallaInd {
    public:
    CuboMolino();
};

class Base : public MallaInd {
    public:
    Base();
};

#endif