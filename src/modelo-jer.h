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

class ConoMolino : public MallaRevol {
    public:
        ConoMolino(const int num_verts_per, const unsigned nperfiles);
};

class Circulo : public MallaInd {
    public:
    Circulo(float radio, const int num_verts);
};

class CilindroMolino : public MallaRevol {
    public:
        CilindroMolino(const int num_verts_per, const unsigned nperfiles, float altura, float radio);
};

class CuboMolino : public MallaInd {
    public:
    CuboMolino();
};

class Base : public MallaInd {
    public:
    Base();
};

class Molino : public NodoGrafoEscena {
    protected:
        mat4 *pm_rot_aspas = nullptr;
        mat4 *pm_rot_puerta = nullptr;
        mat4 *pm_rot_sol = nullptr;
        mat4 *pm_trans_nubes = nullptr;
        mat4 *pm_trans_tejado = nullptr;
        mat4 *pm_trans_esfera = nullptr;
    public:
        unsigned leerNumParametros() const;
        virtual void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
        Molino();
}; 

#endif