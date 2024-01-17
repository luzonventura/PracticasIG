// Nombre: Antonio, Apellidos: Luzón Ventura, Titulación: GIIADE.
// email: luzonventura@correo.ugr.es, DNI o pasaporte: 77448897P

#include "latapeones.h"

using namespace std;
using namespace glm;

Peon::Peon(int nperfiles) : MallaRevolPLY("peon.ply", nperfiles) {}

Lata::Lata(const std::string & textura) {
    NodoGrafoEscena* actual = new NodoGrafoEscena();

    unsigned identTapa = 0;
    unsigned identBase = 1;
    unsigned identCara = 2;

    Textura* texturalata = new Textura(textura);
    Material* materialLata = new Material(texturalata, 0.75, 0.65, 0.25, 50.0);
    Material* materialBases = new Material(0.35, 0.45, 0.25, 50.0);

    NodoGrafoEscena* base = new NodoGrafoEscena();
    NodoGrafoEscena* cara = new NodoGrafoEscena();
    NodoGrafoEscena* tapa = new NodoGrafoEscena();

    base->agregar(materialBases);
    base->agregar(new MallaRevolPLY("lata-pinf.ply", 32));
    tapa->agregar(materialBases);
    tapa->agregar(new MallaRevolPLY("lata-psup.ply", 32));

    cara->agregar(materialLata);
    cara->agregar(new MallaRevolPLY("lata-pcue.ply", 32));

    actual->agregar(base);
    actual->agregar(cara);
    actual->agregar(tapa);

    agregar(actual);
}

LataPeones::LataPeones() {
    NodoGrafoEscena* actual = new NodoGrafoEscena();

    unsigned identPeonMadera = 0;
    unsigned identPeonBlanco = 1;
    unsigned identPeonNegro = 2;
    unsigned identLataCoke = 3;
    unsigned identLataPepsi = 4;
    unsigned identLataSprite = 5;

    TexturaXY* texturaXY_madera = new TexturaXY("text-madera.jpg");
    Material* materialPeonMadera = new Material(texturaXY_madera, 0.5, 0.6, 0.5, 50.0);
    Material* materialPeonBlanco = new Material(0.5, 0.2, 0.5, 5.0);
    Material* materialPeonNegro = new Material(0.01, 0.2, 0.5, 50.0);

    NodoGrafoEscena* LataCoke = new NodoGrafoEscena();
    NodoGrafoEscena* LataPepsi = new NodoGrafoEscena();
    NodoGrafoEscena* LataSprite = new NodoGrafoEscena();

    NodoGrafoEscena* peonMadera = new NodoGrafoEscena();
    NodoGrafoEscena* peonNegro = new NodoGrafoEscena();
    NodoGrafoEscena* peonBlanco = new NodoGrafoEscena();

    LataCoke->agregar(new Lata("lata-coke.jpg")); 

    LataPepsi->agregar(translate(vec3(vec3(0.6, 0.0, 0.0))));
    LataPepsi->agregar(new Lata("lata-pepsi.jpg"));

    LataSprite->agregar(translate(vec3(vec3(1.2, 0.0, 0.0))));
    LataSprite->agregar(new Lata("lata-sprite.jpg"));

    peonMadera->agregar(translate(vec3(0.0, 0.4, 0.7)));
    peonMadera->agregar(scale(vec3(0.25, 0.25, 0.25)));
    peonMadera->agregar(materialPeonMadera);
    peonMadera->agregar(new Peon(32));

    peonNegro->agregar(translate(vec3(0.6, 0.4, 0.7)));
    peonNegro->agregar(scale(vec3(0.25, 0.25, 0.25)));
    peonNegro->agregar(materialPeonNegro);
    peonNegro->agregar(new Peon(32));

    peonBlanco->agregar(translate(vec3(1.2, 0.4, 0.7)));
    peonBlanco->agregar(scale(vec3(0.25, 0.25, 0.25)));
    peonBlanco->agregar(materialPeonBlanco);
    peonBlanco->agregar(new Peon(32));

    actual->agregar(LataCoke);
    actual->agregar(LataPepsi);
    actual->agregar(LataSprite);

    actual->agregar(peonMadera);
    actual->agregar(peonBlanco);
    actual->agregar(peonNegro);

    agregar(actual);
}