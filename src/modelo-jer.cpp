// Nombre: Antonio, Apellidos: Luzón Ventura, Titulación: GIIADE.
// email: luzonventura@correo.ugr.es, DNI o pasaporte: 77448897P

#include "grafo-escena.h"
#include "malla-ind.h"
#include "ig-aux.h"
#include "malla-revol.h"
#include "modelo-jer.h"

using namespace std;
using namespace glm;

Circulo::Circulo(float radio, const int num_verts)
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

/* SemiCirculo::SemiCirculo(float radio, const int num_verts) {
        vertices = vector<vec3>();
        triangulos = vector<uvec3>();

        // Generar vértices para un semicírculo
        for (int i = 0; i <= num_verts; i++) {
            vertices.push_back(vec3(radio * cos(M_PI * i / num_verts), 0.0, radio * sin(M_PI * i / num_verts)));
        }

        // Generar triángulos para un semicírculo
        for (int i = 0; i < num_verts - 1; i++) {
            triangulos.push_back(uvec3(0, i + 1, i + 2));
        }
    } */

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
    NodoGrafoEscena *puerta = new NodoGrafoEscena();
    NodoGrafoEscena *circulo1 = new NodoGrafoEscena();
    NodoGrafoEscena *circulo2 = new NodoGrafoEscena();

    NodoGrafoEscena *tejado = new NodoGrafoEscena();
    NodoGrafoEscena *cono = new NodoGrafoEscena();
    NodoGrafoEscena *circulotejado = new NodoGrafoEscena();

    NodoGrafoEscena *cuadradoAspas = new NodoGrafoEscena();

    NodoGrafoEscena *conjuntoAspas = new NodoGrafoEscena();
    NodoGrafoEscena *aspas = new NodoGrafoEscena();
    NodoGrafoEscena *aspa1 = new NodoGrafoEscena();
    NodoGrafoEscena *aspa2 = new NodoGrafoEscena();
    NodoGrafoEscena *aspaPrincipal1 = new NodoGrafoEscena();
    NodoGrafoEscena *aspaPrincipal2 = new NodoGrafoEscena();
    NodoGrafoEscena *subAspa11 = new NodoGrafoEscena();
    NodoGrafoEscena *subAspa12 = new NodoGrafoEscena();
    NodoGrafoEscena *subAspa21 = new NodoGrafoEscena();
    NodoGrafoEscena *subAspa22 = new NodoGrafoEscena();

    NodoGrafoEscena *sol = new NodoGrafoEscena();

    NodoGrafoEscena *nubes = new NodoGrafoEscena();
    NodoGrafoEscena *nube1 = new NodoGrafoEscena();
    NodoGrafoEscena *nube2 = new NodoGrafoEscena();
    NodoGrafoEscena *nube3 = new NodoGrafoEscena();

    NodoGrafoEscena *esfera = new NodoGrafoEscena();

    NodoGrafoEscena *base = new NodoGrafoEscena();

    // Materiales y texturas

    unsigned identificador = 0;

    Textura *piedra = new Textura("piedra.jpg");
    Material *materialPiedra = new Material(piedra, 0.3, 0.7, 0.1, 10.0);

    Textura *piedraOscura = new TexturaXY("piedraoscura.jpg");
    TexturaXZ *piedraOscuraXZ = new TexturaXZ("piedraoscura.jpg");
    Material *materialPiedraOscura = new Material(piedraOscura, 0.3, 0.7, 0.1, 10.0);
    Material *materialPiedraOscuraXZ = new Material(piedraOscuraXZ, 0.3, 0.7, 0.1, 10.0);

    Textura *madera = new Textura("text-madera.jpg");
    Material *materialMadera = new Material(madera, 0.25, 0.6, 0.2, 20.0);

    Textura *maderaLaminada = new Textura("textura-lamas-madera.jpg");
    Material *materialMaderaLaminada = new Material(maderaLaminada, 0.2, 0.6, 0.2, 20.0);

    Textura *fuego = new Textura("sol.jpg");
    Material *materialFuego = new Material(fuego, 1.0, 0.0, 1.0, 100.0);

    Textura *pelota = new Textura("pelota.jpg");
    Material *materialPelota = new Material(pelota, 0.3, 0.6, 0.5, 30.0);

    TexturaXZ *cesped = new TexturaXZ("cesped.jpg");
    Material *materialCesped = new Material(cesped, 0.4, 0.7, 0.05, 5.0);

    TexturaXY *telablanca = new TexturaXY("tela-blanca.jpg");
    Material *materialTelaBlanca = new Material(telablanca, 0.4, 0.8, 0.05, 10.0);

    Material *materialBlanco = new Material(0.6, 0.8, 0.1, 5.0);

    // Cuerpo (CilindroMolino1, CilindroMolino2 y cuadrado)
    cuerpo1->ponerNombre("Cuerpo principal del molino");
    cuerpo1->ponerIdentificador(identificador++);
    cuerpo1->agregar(translate(vec3(0.0, 0.3, 0.0)));
    cuerpo1->agregar(materialPiedra);
    cuerpo1->agregar(new CilindroMolino(30, 50, 1.15, 0.8));
    cuerpo1->ponerColor({0.961, 0.816, 0.855});

    cuerpo2->ponerNombre("Cuerpo base del molino");
    cuerpo2->ponerIdentificador(identificador++);
    cuerpo2->agregar(materialPiedraOscuraXY);
    cuerpo2->agregar(new CilindroMolino(30, 50, 0.3, 0.9));
    cuerpo2->ponerColor({0.5, 0.5, 0.5});

    // Tapas
    circulo1->ponerNombre("Tapa inferior del molino");
    circulo1->ponerIdentificador(identificador++);
    circulo1->agregar(materialPiedraOscuraXZ);
    circulo1->agregar(new Circulo(0.905, 30));
    circulo1->ponerColor({0.5, 0.5, 0.5});

    circulo2->ponerNombre("Tapa superior del molino");
    circulo2->ponerIdentificador(identificador++);
    circulo2->agregar(translate(vec3(0.0, 0.3, 0.0)));
    circulo2->agregar(materialPiedraOscuraXZ);
    circulo2->agregar(new Circulo(0.905, 30));
    circulo2->ponerColor({0.5, 0.5, 0.5});

    // Puerta
    unsigned ind_rot_puerta = puerta->agregar(rotate(0.0f, vec3{0.0, 1.0, 0.0}));
    pm_rot_puerta = puerta->leerPtrMatriz(ind_rot_puerta);

    puerta->ponerNombre("Puerta del molino");
    puerta->ponerIdentificador(identificador++);
    puerta->agregar(translate(vec3(-0.8, 0.5, 0.0)));
    puerta->agregar(rotate(float(M_PI / 2), vec3{0.0, 1.0, 0.0}));
    puerta->agregar(scale(vec3(0.1, 0.2, 0.01)));
    puerta->agregar(materialMaderaLaminada);
    puerta->agregar(new Cubo24());
    puerta->ponerColor({0.329, 0.2, 0.071});

    cuerpo->agregar(cuerpo1);
    cuerpo->agregar(cuerpo2);
    cuerpo->agregar(circulo1);
    cuerpo->agregar(circulo2);
    cuerpo->agregar(puerta);

    // Tejado
    cono->ponerNombre("Tejado del molino");
    cono->ponerIdentificador(identificador++);
    cono->agregar(translate(vec3(0.0, 1.35, 0.0)));
    cono->agregar(materialMadera);
    cono->agregar(new ConoMolino(30, 20));
    cono->ponerColor({0.9, 0, 0});

    circulotejado->ponerNombre("Tapa del tejado del molino");
    circulotejado->ponerIdentificador(identificador++);
    circulotejado->agregar(translate(vec3(0.0, 1.35, 0.0)));
    circulotejado->agregar(materialMaderaLaminada);
    circulotejado->agregar(new Circulo(0.998, 30));
    circulotejado->ponerColor({0.9, 0.5, 0.5});

    // CONJUNTO DE ASPAS

    // Cuadrado del conjunto de aspas (podría haber reutilizado
    // el del cuerpo)
    cuadradoAspas->ponerNombre("Cuadrado del conjunto de aspas");
    cuadradoAspas->ponerIdentificador(identificador++);
    cuadradoAspas->agregar(translate(vec3(0.0, 0.8, 0.93)));
    cuadradoAspas->agregar(scale(vec3(0.04, 0.04, 0.04)));
    cuadradoAspas->agregar(materialMaderaLaminada);
    cuadradoAspas->agregar(new Cubo24());
    cuadradoAspas->ponerColor({0.329, 0.2, 0.071});

    // Aspa principal 1
    aspaPrincipal1->ponerNombre("Aspa principal 1");
    aspaPrincipal1->ponerIdentificador(identificador++);
    aspaPrincipal1->agregar(translate(vec3(0.0, 0.82, 1.02)));
    aspaPrincipal1->agregar(scale(vec3(0.04, 0.8, 0.05)));
    aspaPrincipal1->agregar(materialMaderaLaminada);
    aspaPrincipal1->agregar(new Cubo24());
    aspaPrincipal1->ponerColor({0.329, 0.2, 0.071});

    // Subaspa 1.1
    subAspa11->ponerNombre("Subaspa 1.1");
    subAspa11->ponerIdentificador(identificador++);
    subAspa11->agregar(translate(vec3(0.12, 1.34, 1.0)));
    subAspa11->agregar(scale(vec3(0.08, 0.28, 0.0)));
    subAspa11->agregar(materialTelaBlanca);
    subAspa11->agregar(new Cubo24());
    subAspa11->ponerColor({1.0, 1.0, 1.0});

    // Subaspa 1.2
    subAspa12->ponerNombre("Subaspa 1.2");
    subAspa12->ponerIdentificador(identificador++);
    subAspa12->agregar(translate(vec3(-0.12, 0.3, 1.0)));
    subAspa12->agregar(scale(vec3(0.08, 0.28, 0.0)));
    subAspa12->agregar(materialTelaBlanca);
    subAspa12->agregar(new Cubo24());
    subAspa12->ponerColor({1.0, 1.0, 1.0});

    aspa1->agregar(aspaPrincipal1);
    aspa1->agregar(subAspa11);
    aspa1->agregar(subAspa12);

    // Aspa principal 2
    aspaPrincipal2->ponerNombre("Aspa principal 2");
    aspaPrincipal2->ponerIdentificador(identificador++);
    aspaPrincipal2->agregar(rotate(float(M_PI / 2), vec3{0.0, 0.0, 1.0}));
    aspaPrincipal2->agregar(translate(vec3(0.8, 0.02, 1.02)));
    aspaPrincipal2->agregar(scale(vec3(0.04, 0.8, 0.05)));
    aspaPrincipal2->agregar(materialMaderaLaminada);
    aspaPrincipal2->agregar(new Cubo24());
    aspaPrincipal2->ponerColor({0.329, 0.2, 0.071});

    // Subaspa 2.1
    subAspa21->ponerNombre("Subaspa 2.1");
    subAspa21->ponerIdentificador(identificador++);
    subAspa21->agregar(rotate(float(M_PI / 2), vec3{0.0, 0.0, 1.0}));
    subAspa21->agregar(translate(vec3(0.92, 0.54, 1.0)));
    subAspa21->agregar(scale(vec3(0.08, 0.28, 0.0)));
    subAspa21->agregar(materialTelaBlanca);
    subAspa21->agregar(new Cubo24());
    subAspa21->ponerColor({1.0, 1.0, 1.0});

    // Subaspa 2.2
    subAspa22->ponerNombre("Subaspa 2.2");
    subAspa22->ponerIdentificador(identificador++);
    subAspa22->agregar(rotate(float(M_PI / 2), vec3{0.0, 0.0, 1.0}));
    subAspa22->agregar(translate(vec3(0.68, -0.50, 1.0)));
    subAspa22->agregar(scale(vec3(0.08, 0.28, 0.0)));
    subAspa22->agregar(materialTelaBlanca);
    subAspa22->agregar(new Cubo24());
    subAspa22->ponerColor({1.0, 1.0, 1.0});

    aspa2->agregar(aspaPrincipal2);
    aspa2->agregar(subAspa21);
    aspa2->agregar(subAspa22);

    aspas->agregar(aspa1);
    aspas->agregar(aspa2);

    unsigned ind_rot_conjuntoAspas = conjuntoAspas->agregar(rotate(0.0f, vec3{0.0, 1.0, 0.0}));
    pm_rot_aspas = conjuntoAspas->leerPtrMatriz(ind_rot_conjuntoAspas);

    conjuntoAspas->agregar(translate(vec3(0.0, 1.4, 0.8)));
    conjuntoAspas->agregar(rotate(float(M_PI / 2), vec3{-1.0, 0.0, 0.0}));

    conjuntoAspas->agregar(aspas);
    conjuntoAspas->agregar(cuadradoAspas);

    unsigned ind_trans_tejado = tejado->agregar(translate(vec3(0.0, 0.0, 0.0)));
    pm_trans_tejado = tejado->leerPtrMatriz(ind_trans_tejado);

    tejado->agregar(cono);
    tejado->agregar(circulotejado);
    tejado->agregar(conjuntoAspas);

    // Sol
    unsigned ind_rot_sol = sol->agregar(rotate(0.0f, vec3{0.0, 1.0, 0.0}));
    pm_rot_sol = sol->leerPtrMatriz(ind_rot_sol);

    sol->ponerNombre("Sol");
    sol->ponerIdentificador(identificador++);
    sol->agregar(translate(vec3(-2.0, 3.0, -1.0)));
    sol->agregar(scale(vec3(0.5, 0.5, 0.5)));
    sol->agregar(materialFuego);
    sol->agregar(new Esfera(8, 40));
    sol->ponerColor({0.91, 0.839, 0.024});

    unsigned int ind_trans_nubes = nubes->agregar(translate(vec3(0.0, 0.0, 0.0)));
    pm_trans_nubes = nubes->leerPtrMatriz(ind_trans_nubes);

    // Nubes 
    nube1->ponerNombre("Nube 1");
    nube1->ponerIdentificador(identificador++);
    nube1->agregar(translate(vec3(2.0, 2.0, -1.0)));
    nube1->agregar(scale(vec3(1.0, 0.7, 0.4)));
    nube1->agregar(new Esfera(8, 40));
    nube1->ponerColor({0.902, 0.898, 0.886});

    nube2->ponerNombre("Nube 2");
    nube2->ponerIdentificador(identificador++);
    nube2->agregar(translate(vec3(2.8, 2.5, -2.0)));
    nube2->agregar(scale(vec3(1.0, 0.7, 0.4)));
    nube2->agregar(new Esfera(8, 40));
    nube2->ponerColor({0.902, 0.898, 0.886});

    nube3->ponerNombre("Nube 3");
    nube3->ponerIdentificador(identificador++);
    nube3->agregar(translate(vec3(4.5, 2.0, -1.0)));
    nube3->agregar(scale(vec3(1.0, 0.7, 0.4)));
    nube3->agregar(new Esfera(8, 40));
    nube3->ponerColor({0.902, 0.898, 0.886});

    nubes->agregar(scale(vec3(0.7, 0.7, 0.7)));
    nubes->agregar(translate(vec3(0.0, 0.0, -0.5)));
    nubes->agregar(materialBlanco);

    nubes->agregar(nube1);
    nubes->agregar(nube2);
    nubes->agregar(nube3);

    // Esfera
    unsigned int ind_trans_esfera = esfera->agregar(translate(vec3(0.0, 0.0, 0.0)));
    pm_trans_esfera = esfera->leerPtrMatriz(ind_trans_esfera);

    esfera->ponerNombre("Pelota");
    esfera->ponerIdentificador(identificador++);
    esfera->agregar(translate(vec3(0.0, 0.75, 0.0)));
    esfera->agregar(scale(vec3(0.5, 0.5, 0.5)));
    esfera->agregar(materialPelota);
    esfera->agregar(new Esfera(30, 40));
    esfera->ponerColor({0.6, 1.0, 0.7});

    // Base
    base->ponerNombre("Base del molino");
    base->ponerIdentificador(identificador++);
    base->agregar(scale(vec3(4.0, 4.0, 4.0)));
    base->agregar(materialCesped);
    base->agregar(new Base());
    base->ponerColor({0.157, 0.471, 0.024});

    molino->agregar(cuerpo);
    molino->agregar(base);
    molino->agregar(tejado);
    molino->agregar(sol);
    molino->agregar(nubes);
    molino->agregar(esfera);

    agregar(molino);
}

unsigned Molino::leerNumParametros() const
{
    return 6;
}

void Molino::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{
    assert(iParam < leerNumParametros());
    switch (iParam)
    {
    // Rotación aspas
    case 0:
        *pm_rot_aspas = glm::rotate(-t_sec * 5.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        break;
    // Rotación puerta
    case 1:
        // Máximo angulo para rotar la puerta (nos quedamos con el valor absoluto
        // y los hacemos negativos para que se abra hacia fuera)
        float angle;
        angle = -abs((sin(t_sec) * M_PI / 2));
        *pm_rot_puerta = glm::translate(glm::mat4(1.0f), vec3(-0.8, 0.5, -0.1)) * glm::rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), -vec3(-0.8, 0.5, -0.1));
        break;
    // Translación nubes
    case 2:
        *pm_trans_nubes = translate(vec3{0.0, 0.5 * sin(2 * M_PI * t_sec / 3), 0.0});
        break;
    // Translación sol
    case 3:
        *pm_rot_sol = rotate(t_sec / 2, vec3{0.0, 1.0, 0.0});
        break;
    // Translación tejado
    case 4:
        *pm_trans_tejado = translate(vec3{0.0, 1.5 * abs(sin(2 * M_PI * t_sec / 20)), 0.0});
        break;
    case 5:
        *pm_trans_esfera = translate(vec3{0.0, 1.30 * abs(sin(2 * M_PI * t_sec / 20)), 0.0});
        break;
    }
}