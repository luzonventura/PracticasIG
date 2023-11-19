// Nombre: Antonio, Apellidos: Luzón Ventura, Titulación: GIIADE.
// email: luzonventura@correo.ugr.es, DNI o pasaporte: 77448897P

#include "grafo-escena.h"
#include "malla-ind.h"
#include "ig-aux.h"
#include "malla-revol.h"
#include "modelo-jer.h"

using namespace std;
using namespace glm;

CilindroMolino::CilindroMolino(const int num_verts_per, const unsigned nperfiles, float altura, float radio)
{
    vector<vec3> perfil = vector<vec3>();
    for (int i = 0; i < num_verts_per; i++)
    {
        perfil.push_back(vec3(radio, i * (altura / (num_verts_per - 1)), 0.0));
    }
    inicializar(perfil, nperfiles);
}

ConoMolino::ConoMolino(const int num_verts_per, const unsigned nperfiles)
{
    std::vector<glm::vec3> perfil;

    for (int i = 0; i < num_verts_per; i++)
    {
        float altura = i * (1.0 / (num_verts_per - 1));
        perfil.push_back(glm::vec3(1 - altura, altura, 0.0));
    }

    inicializar(perfil, nperfiles);
}

CirculoMolino::CirculoMolino(float radio, const int num_verts)
{
    vertices = vector<vec3>();
    triangulos = vector<uvec3>();
    for (int i = 0; i < num_verts; i++)
    {
        vertices.push_back(vec3(radio * cos(2 * M_PI * i / num_verts), 0.0, radio * sin(2 * M_PI * i / num_verts)));
    }
    for (int i = 0; i < num_verts - 2; i++)
    {
        triangulos.push_back(uvec3(0, i + 1, i + 2));
    }
}

CuboMolino::CuboMolino()
{
    vertices =
        {
            {-1.0, -1.0, -1.0}, // 0
            {-1.0, -1.0, +1.0}, // 1
            {-1.0, +1.0, -1.0}, // 2
            {-1.0, +1.0, +1.0}, // 3
            {+1.0, -1.0, -1.0}, // 4
            {+1.0, -1.0, +1.0}, // 5
            {+1.0, +1.0, -1.0}, // 6
            {+1.0, +1.0, +1.0}, // 7
        };

    triangulos =
        {
            {0, 1, 3}, {0, 3, 2}, // X-
            {4, 7, 5},
            {4, 6, 7}, // X+ (+4)

            {0, 5, 1},
            {0, 4, 5}, // Y-
            {2, 3, 7},
            {2, 7, 6}, // Y+ (+2)

            {0, 6, 4},
            {0, 2, 6}, // Z-
            {1, 5, 7},
            {1, 7, 3} // Z+ (+1)
        };
}

Base::Base()
{
    vertices = {
        {-1.0, 0.0, -1.0},
        {-1.0, 0.0, 1.0},
        {1.0, 0.0, -1.0},
        {1.0, 0.0, 1.0}};

    triangulos = {
        {0, 1, 2}, {1, 2, 3}};
}

Molino::Molino()
{
    ponerNombre("molino");

    NodoGrafoEscena *molino = new NodoGrafoEscena();

    NodoGrafoEscena *cuerpo = new NodoGrafoEscena();
    NodoGrafoEscena *cuerpo1 = new NodoGrafoEscena();
    NodoGrafoEscena *cuerpo2 = new NodoGrafoEscena();
    NodoGrafoEscena *cuadradoCuerpo = new NodoGrafoEscena();
    NodoGrafoEscena *puerta = new NodoGrafoEscena();

    NodoGrafoEscena *tejado = new NodoGrafoEscena();

    NodoGrafoEscena *circulos = new NodoGrafoEscena();
    NodoGrafoEscena *circulo1 = new NodoGrafoEscena();
    NodoGrafoEscena *circulo2 = new NodoGrafoEscena();
    NodoGrafoEscena *circulo3 = new NodoGrafoEscena();

    NodoGrafoEscena *cuadradoAspas = new NodoGrafoEscena();

    NodoGrafoEscena *conjuntoAspas = new NodoGrafoEscena();
    NodoGrafoEscena *aspas = new NodoGrafoEscena();
    NodoGrafoEscena *aspa1 = new NodoGrafoEscena();
    NodoGrafoEscena *aspa2 = new NodoGrafoEscena();
    NodoGrafoEscena *aspaPrincipal = new NodoGrafoEscena();
    NodoGrafoEscena *subAspa11 = new NodoGrafoEscena();
    NodoGrafoEscena *subAspa12 = new NodoGrafoEscena();

    NodoGrafoEscena *sol = new NodoGrafoEscena();

    NodoGrafoEscena *nubes = new NodoGrafoEscena();
    NodoGrafoEscena *nube1 = new NodoGrafoEscena();
    NodoGrafoEscena *nube2 = new NodoGrafoEscena();
    NodoGrafoEscena *nube3 = new NodoGrafoEscena();

    // Cuerpo (Cilindro1, cilindro2 y cuadrado)
    cuerpo1->agregar(translate(vec3(0.0, 0.3, 0.0)));
    cuerpo1->agregar(new CilindroMolino(30, 50, 1.15, 0.8));
    cuerpo1->ponerColor({0.961, 0.816, 0.855});

    cuerpo2->agregar(new CilindroMolino(30, 50, 0.3, 0.9));
    cuerpo2->ponerColor({0.5, 0.5, 0.5});

    cuadradoCuerpo->agregar(translate(vec3(0.0, 0.8, 0.8)));
    cuadradoCuerpo->agregar(scale(vec3(0.1, 0.1, 0.1)));
    cuadradoCuerpo->agregar(new CuboMolino());
    cuadradoCuerpo->ponerColor({0.961, 0.816, 0.855});

    // Puerta
    unsigned ind_rot_puerta = puerta->agregar(rotate(0.0f, vec3{0.0, 1.0, 0.0}));
    pm_rot_puerta = puerta->leerPtrMatriz(ind_rot_puerta);

    puerta->agregar(translate(vec3(-0.8, 0.5, 0.0)));
    puerta->agregar(rotate(float(M_PI / 2), vec3{0.0, 1.0, 0.0}));
    puerta->agregar(scale(vec3(0.1, 0.2, 0.01)));
    puerta->agregar(new CuboMolino());
    puerta->ponerColor({0.329, 0.2, 0.071});

    cuerpo->agregar(puerta);
    cuerpo->agregar(cuadradoCuerpo);
    cuerpo->agregar(cuerpo1);
    cuerpo->agregar(cuerpo2);

    // Tejado
    tejado->agregar(translate(vec3(0.0, 1.35, 0.0)));
    tejado->agregar(new ConoMolino(30, 20));
    tejado->ponerColor({0.5, 0.5, 0.5});

    NodoGrafoEscena *base = new NodoGrafoEscena();
    base->agregar(scale(vec3(4.0, 4.0, 4.0)));
    base->ponerColor({0.157, 0.471, 0.024});
    base->agregar(new Base());

    // Tapas
    circulo1->agregar(new CirculoMolino(0.905, 30));
    circulo1->ponerColor({0.5, 0.5, 0.5});

    circulo2->agregar(translate(vec3(0.0, 0.3, 0.0)));
    circulo2->agregar(new CirculoMolino(0.905, 30));
    circulo2->ponerColor({0.5, 0.5, 0.5});

    circulo3->agregar(translate(vec3(0.0, 1.35, 0.0)));
    circulo3->agregar(new CirculoMolino(0.998, 30));
    circulo3->ponerColor({0.5, 0.5, 0.5});

    circulos->agregar(circulo1);
    circulos->agregar(circulo2);
    circulos->agregar(circulo3);

    cuerpo->agregar(circulos);

    // Cuadrado del conjunto de aspas (podría haber reutilizado
    // el del cuerpo)
    cuadradoAspas->agregar(translate(vec3(0.0, 0.8, 0.93)));
    cuadradoAspas->agregar(scale(vec3(0.04, 0.04, 0.04)));
    cuadradoAspas->agregar(new CuboMolino());
    cuadradoAspas->ponerColor({0.329, 0.2, 0.071});

    // Aspa principal 1
    aspaPrincipal->agregar(translate(vec3(0.0, 0.82, 1.02)));
    aspaPrincipal->agregar(scale(vec3(0.04, 0.8, 0.05)));
    aspaPrincipal->agregar(new CuboMolino());
    aspaPrincipal->ponerColor({0.329, 0.2, 0.071});
    aspa1->agregar(aspaPrincipal);

    // Subaspa 1
    subAspa11->agregar(translate(vec3(0.12, 1.34, 1.0)));
    subAspa11->agregar(scale(vec3(0.08, 0.28, 0.0)));
    subAspa11->agregar(new CuboMolino());
    subAspa11->ponerColor({1.0, 1.0, 1.0});
    aspa1->agregar(subAspa11);

    // Subaspa 2
    subAspa12->agregar(translate(vec3(-0.12, 0.3, 1.0)));
    subAspa12->agregar(scale(vec3(0.08, 0.28, 0.0)));
    subAspa12->agregar(new CuboMolino());
    subAspa12->ponerColor({1.0, 1.0, 1.0});
    aspa1->agregar(subAspa12);

    aspas->agregar(aspa1);

    // Aspa 2
    aspa2->agregar(rotate(float(M_PI / 2), vec3{0.0, 0.0, 1.0}));
    aspa2->agregar(translate(vec3(0.8, -0.8, 0.0)));
    aspa2->agregar(aspa1);

    aspas->agregar(aspa2);

    // Sol
    unsigned ind_rot_sol = sol->agregar(translate(vec3(0.0, 0.0, 0.0)));
    pm_rot_sol = sol->leerPtrMatriz(ind_rot_sol);

    sol->agregar(translate(vec3(-2.0, 2.5, -1.0)));
    sol->agregar(scale(vec3(0.5, 0.5, 0.5)));
    sol->agregar(new Esfera(8, 40));
    sol->ponerColor({0.91, 0.839, 0.024});

    unsigned int ind_rot_nubes = nubes->agregar(translate(vec3(0.0, 0.0, 0.0)));
    pm_rot_nubes = nubes->leerPtrMatriz(ind_rot_nubes);

    // Nubes
    nubes->agregar(scale(vec3(0.7, 0.7, 0.7)));
    nubes->agregar(translate(vec3(0.0, 0.0, -0.5)));

    nube1->agregar(translate(vec3(2.0, 2.0, -1.0)));
    nube1->agregar(scale(vec3(1.0, 0.7, 0.4)));
    nube1->agregar(new Esfera(8, 40));
    nube1->ponerColor({0.902, 0.898, 0.886});

    nube2->agregar(translate(vec3(0.8, 0.5, -1.0)));
    nube2->agregar(nube1);

    nube3->agregar(translate(vec3(2.5, 0, 0)));
    nube3->agregar(nube1);

    nubes->agregar(nube1);
    nubes->agregar(nube2);
    nubes->agregar(nube3);

    unsigned ind_rot_conjuntoAspas = conjuntoAspas->agregar(rotate(0.0f, vec3{0.0, 0.0, 1.0}));
    pm_rot_aspas = conjuntoAspas->leerPtrMatriz(ind_rot_conjuntoAspas);

    conjuntoAspas->agregar(aspas);
    conjuntoAspas->agregar(cuadradoAspas);

    molino->agregar(cuerpo);
    molino->agregar(base);
    molino->agregar(tejado);
    molino->agregar(conjuntoAspas);
    molino->agregar(sol);
    molino->agregar(nubes);

    agregar(molino);
}

unsigned Molino::leerNumParametros() const
{
    return 4;
}

void Molino::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{
    assert(iParam < leerNumParametros());
    switch (iParam)
    {
    // Rotación aspas
    case 0:
        *pm_rot_aspas = glm::translate(glm::mat4(1.0f), vec3(0, 0.8, 0.93)) * glm::rotate(-t_sec, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::translate(glm::mat4(1.0f), -vec3(0, 0.8, 0.93));
        break;
    // Rotación puerta
    case 1:
        // Máximo angulo para rotar la puerta (nos quedamos con el valor absoluto
        // y los hacemos negativos para que se abra hacia fuera)
        float angle;
        angle = -abs((sin(t_sec) * M_PI / 2));
        *pm_rot_puerta = glm::translate(glm::mat4(1.0f), vec3(-0.8, 0.5, -0.1)) * glm::rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), -vec3(-0.8, 0.5, -0.1));
        break;
    // Rotación nubes
    case 2:
        *pm_rot_nubes = translate(vec3{0.0, 0.5 * sin(2 * M_PI * t_sec / 3), 0.0});
        break;
    // Rotación sol
    case 3:
        *pm_rot_sol = translate(vec3{0.0, -3.5 * sin(2 * M_PI * t_sec / 20), 0.0});
        break;
    }
}