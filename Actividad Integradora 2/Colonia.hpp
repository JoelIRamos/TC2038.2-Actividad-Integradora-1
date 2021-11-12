// #pragma once
#ifndef COLONIA_HPP
#define COLONIA_HPP

#include <string>
using namespace std;

// Estructura de datos para representar una colonia
struct colonia {
    string nombre; // Nombre de la colonia
    double x, y; // Posicion en el mapa
    bool central; // Si es una colonia central
    colonia() {
        nombre = "";
        x = 0.0;
        y = 0.0;
        central = false;
    }
    colonia(string nombre, double x, double y, bool central) {
        this->nombre = nombre;
        this->x = x;
        this->y = y;
    }
};

#endif