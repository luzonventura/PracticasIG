// Nombre: Antonio, Apellidos: Luzón Ventura, Titulación: GIIADE.
// email: luzonventura@correo.ugr.es, DNI o pasaporte: 77448897P

#ifndef LATAPEONES_H
#define LATAPEONES_H

#include "grafo-escena.h"
#include "malla-revol.h"

class LataPeones : public NodoGrafoEscena {
    public:
        LataPeones();
};

class Lata : public NodoGrafoEscena {
    public:
        Lata(const std::string & textura);
};

class Peon : public NodoGrafoEscena {
    public:
        Peon(int nperfiles);
        bool cuandoClick(const glm::vec3 & centro_wc) override;
    protected:
        glm::mat4* pm_tras = nullptr;
};

class VariasLatasPeones : public LataPeones {
    public:
        VariasLatasPeones();
};

#endif