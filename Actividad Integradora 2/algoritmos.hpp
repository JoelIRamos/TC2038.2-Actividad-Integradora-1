// Archivo para los algoritmos que se usan en el programa
namespace algoritmos {
    // ! Toda libreria que se incluya aquí, debe tambien ser incluida en el main.cpp
    #include <iostream>
    #include <vector>
    #include <string>
    #include <cmath>
    #include <float.h>
    #include <unordered_map>
    #include <algorithm>
    #include <unordered_set>
    #include <fstream>
    
    using namespace std;

    #include "Colonia.hpp"

    // * Funciones para el inciso 5

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

    // * Funciones para el inciso 4

    // Complejidad: O(n^3)
    void floyd(vector< vector <double> >& mat, vector< vector <int> >& p, int n, vector<colonia> colonias){
        for (int k = 0; k < n; k++){
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    if (mat[i][k] != DBL_MAX && mat[k][j] != DBL_MAX && mat[i][k]+mat[k][j] < mat[i][j]){
                        mat[i][j] = mat[i][k]+mat[k][j];
                        p[i][j] = k;
                    }
                }
            }
        }
    }

    void checarTrayectoria(vector< vector <int> >& p, int a, int b, vector<colonia> colonias, ofstream& out){
        if (p[a][b] != -1){
            checarTrayectoria(p, a, p[a][b], colonias, out);
            out << colonias[(p[a][b])].nombre << "-";
            checarTrayectoria(p, p[a][b], b, colonias, out);
        }
    }

    void consultas(vector< vector <double> >& mat, vector< vector <int> >& p, vector<colonia> colonias, int n, ofstream& out){
        int a = 0, b = n-1;
        // out << n << endl;
        // return;
        if (mat[a][b] == DBL_MAX){
            out << "no path" << endl;
        } else {
            out << "Costo: " << mat[a][b] << "\nPath: " << colonias[a].nombre << "-";
            checarTrayectoria(p, a, b, colonias, out);
            out << colonias[b].nombre << endl << endl;
        }
    }

    void print(vector< vector <double> >& mat, vector< vector <int> >& p, int n){
        cout << "matriz de costos" << endl;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (mat[i][j] == DBL_MAX){
                    cout << "INF\t";
                } else {
                    cout << mat[i][j] << "\t";
                }
            }
            cout << endl;
        }

        cout << "matriz de trajectoria" << endl;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                cout << p[i][j] << "\t";
            }
            cout << endl;
        }
    }

}
