// Nombre: Antonio, Apellidos: Luzón Ventura, Titulación: GIIADE.
// email: luzonventura@correo.ugr.es, DNI o pasaporte: 77448897P
//
// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// **
// ** Mallas indexadas (implementación)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Implementación de las clases
// **    + MallaRevol: malla indexada de triángulos obtenida por
// **      revolución de un perfil (derivada de MallaInd)
// **    + MallaRevolPLY: malla indexada de triángulos, obtenida
// **      por revolución de un perfil leído de un PLY (derivada de MallaRevol)
// **    + algunas clases derivadas de MallaRevol
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#include "ig-aux.h"
#include "lector-ply.h"
#include "malla-revol.h"

using namespace std;

// *****************************************************************************

// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar(
    const std::vector<glm::vec3> &perfil, // tabla de vértices del perfil original
    const unsigned num_copias             // número de copias del perfil
)
{
   using namespace glm;

   // COMPLETAR: práctica 4: creación de las normales y materiales/texturas

   // Lista de vectores para almacenar normales a las aristas.
   std::vector<vec3> normalesAristas;

   // Calcular normales a las aristas.
   for (unsigned i = 0; i < perfil.size() - 1; i++) {
      float diferenciaX = (perfil[i + 1] - perfil[i])[0];
      float diferenciaY = (perfil[i + 1] - perfil[i])[1];
      vec3 normalArista(vec3(diferenciaY, -diferenciaX, 0.0f)); // Rotación de 90 grados en el plano XY.

      // Normalizar si no es el vector cero.
      if (glm::length(normalArista) != 0.0)
         normalArista = glm::normalize(normalArista);
    
      normalesAristas.push_back(normalArista);
   }

   // Lista de vectores para almacenar normales a los vértices.
   std::vector<vec3> normalesVertices;

   normalesVertices.push_back(normalesAristas[0]);
   for (unsigned i = 1; i < perfil.size() - 1; i++) {
      normalesVertices.push_back(glm::normalize(normalesAristas[i - 1] + normalesAristas[i]));
   }

   normalesVertices.push_back(normalesAristas[perfil.size() - 2]);

   // Vectores para almacenar distancias y coordenadas de textura.
   std::vector<float> distancias, coordenadasTextura, sumasParciales;
   float longitudTotal;

   // Calcular distancias entre puntos del perfil.
   for (unsigned i = 0; i < perfil.size() - 1; i++) {
      distancias.push_back(glm::sqrt(glm::length(perfil[i + 1] - perfil[i])));
   }

   sumasParciales.push_back(0.0f);
   for (unsigned i = 1; i < perfil.size(); i++) {
      sumasParciales.push_back(sumasParciales[i - 1] + distancias[i - 1]);
   }

   longitudTotal = sumasParciales[perfil.size() - 1];
   coordenadasTextura.push_back(0.0f);
   for (unsigned i = 1; i < perfil.size(); i++)
      coordenadasTextura.push_back(sumasParciales[i] / longitudTotal);

   // COMPLETAR: práctica 2: implementar algoritmo de creación de malla de revolución
   //
   // Escribir el algoritmo de creación de una malla indexada por revolución de un
   // perfil, según se describe en el guion de prácticas.
   //
   // ...............................

   // Partimos de las tablas de vértices y triángulos vacías
   vertices = std::vector<glm::vec3>();
   triangulos = std::vector<glm::uvec3>();
   unsigned int m = perfil.size();
   unsigned int n = num_copias;

   // Completamos vértices
   for (unsigned int i = 0; i < n; i++)
   {
      for (unsigned int j = 0; j < m; j++)
      {
         // Obtener las coordenadas del punto perfil[j] girado 2pi*i/(n-1) sobre eje Y
         glm::vec3 q, p_j = perfil[j];
         float c = cos(float(2 * M_PI * i) / (n - 1));
         float s = sin(float(2 * M_PI * i) / (n - 1));
         q[0] = c * p_j[0] + s * p_j[2];
         q[1] = p_j[1];
         q[2] = -s * p_j[0] + c * p_j[2];

         vertices.push_back(q);

         // PRACTICA 4
         vec3 normals = vec3(normalesVertices[j][0] * cos((2*M_PI*i)/(n - 1)), normalesVertices[j][1], -normalesVertices[j][0] * sin((2*M_PI*i)/(n - 1)));
         if (length(normals) != 0.0)
            normalize(normals);
         nor_ver.push_back(normals);
         
         cc_tt_ver.push_back({float(i) / (n-1), 1-coordenadasTextura[j]});
      }
   }

   // Completamos triángulos
   for (unsigned int i = 0; i < n - 1; i++)
   {
      for (unsigned int j = 0; j < m - 1; j++)
      {
         unsigned int k = i * m + j;
         triangulos.push_back({k, k + m, k + m + 1});
         triangulos.push_back({k, k + m + 1, k + 1});
      }
   }
}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY(
    const std::string &nombre_arch,
    const unsigned nperfiles)
{
   ponerNombre(std::string("malla por revolución del perfil en '" + nombre_arch + "'"));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
   // ...........................

   std::vector<glm::vec3> perfil;
   LeerVerticesPLY(nombre_arch, perfil);
   inicializar(perfil, nperfiles);
}

// *****************************************************************************
// Clases derivadas de MallaRevol (práctica 2)

// *****************************************************************************
// Cilindro

Cilindro::Cilindro(
    const int num_verts_per,
    const unsigned nperfiles)
{
   ponerNombre(std::string("Cilindro"));

   std::vector<glm::vec3> perfil;

   for (int i = 0; i < num_verts_per; i++)
   {
      float altura = i * (1.0 / (num_verts_per - 1));
      perfil.push_back(glm::vec3(1.0, altura, 0.0));
   }

   inicializar(perfil, nperfiles);

   /* for (unsigned i = 0; i < vertices.size(); i++)
   {
      col_ver.push_back({vertices.at(i).x, vertices.at(i).y, vertices.at(i).z});
   } */
}

// *****************************************************************************
// Cono

Cono::Cono(
    const int num_verts_per,
    const unsigned nperfiles)
{
   ponerNombre(std::string("Cono"));

   std::vector<glm::vec3> perfil;

   for (int i = 0; i < num_verts_per; i++)
   {
      float altura = i * (1.0 / (num_verts_per - 1));
      perfil.push_back(glm::vec3(1.0 - altura, altura, 0.0));
   }

   inicializar(perfil, nperfiles);

   for (unsigned i = 0; i < vertices.size(); i++)
   {
      col_ver.push_back({vertices.at(i).x, vertices.at(i).y, vertices.at(i).z});
   }
}

// *****************************************************************************
// Esfera

Esfera::Esfera(
    const int num_verts_per,
    const unsigned nperfiles)
{
   ponerNombre(std::string("Esfera"));

   std::vector<glm::vec3> perfil;

   for (int i = 0; i < num_verts_per; i++)
   {
      perfil.push_back(glm::vec3(cos(i * (2 * M_PI * 1.0 / (num_verts_per - 1))), sin(i * (2 * M_PI * 1.0 / (num_verts_per - 1))), 0.0));
   }
   inicializar(perfil, nperfiles);
}