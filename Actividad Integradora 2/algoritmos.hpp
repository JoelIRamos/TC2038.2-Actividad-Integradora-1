// Archivo para los algoritmos que se usan en el programa
namespace algoritmos {
    // ! Toda libreria que se incluya aquí, debe tambien ser incluida en el main.cpp
    #include <iostream>
    #include <vector>
    #include <string>
    #include <cmath>
    // #include<algorithm>
    
    using namespace std;

    #include "Colonia.hpp"

    double distancia(colonia &c1, colonia &c2) {
        return sqrt((c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y));
    }

    colonia coloniaMinimaDistancia(colonia nueva, vector<colonia> colonias){
        colonia coloniaMinima = colonias[0];
        double distanciaMinima = distancia(nueva, coloniaMinima);
        for (int i = 1; i < colonias.size(); i++){
            double distanciaAuxiliar = distancia(nueva, colonias[i]);
            if (distanciaAuxiliar < distanciaMinima){
                coloniaMinima = colonias[i];
                distanciaMinima = distanciaAuxiliar;
            }
        }
        return coloniaMinima;
    }

    
}