#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <unordered_map>

using namespace std;

#include "Colonia.hpp"
#include "algoritmos.hpp"


int main(){
    // n = numero de colonias, m = numero de conexiones entre colonias, futuras nuevas colonias que se desean conectar.
    int n, m, q; 
    cin >> n >> m >> q;

    // Vector de colonias
    vector<colonia> colonias(n);
    // Hash de colonias
    unordered_map<string, int> coloniasHash(n);

    // Matriz de Adjacencia
    vector<vector<int>> mapa(n, vector<int>(n, -1));

    // Leer las colonias
    for (int i = 0; i < n; i++) {
        cin >> colonias[i].nombre >> colonias[i].x >> colonias[i].y >> colonias[i].central;
        coloniasHash[colonias[i].nombre] = i;
    }

    // Leer las conexiones
    for (int i = 0; i < m; i++) {
        // Colonias con una conexion
        string a, b;
        // Costo de la conexion
        double c;

        // Leer la conexion
        cin >> a >> b >> c;

        // Buscar el id de las colonias
        int ia = coloniasHash[a];
        int ib = coloniasHash[b];

        // Guardar la conexion en la matriz
        mapa[ia][ib] = c;
        mapa[ib][ia] = c;
    }

    
    // Imprimir las colonias
    cout << "-------------------------" << endl;

    for (int i = 0; i < n; i++){
        cout << i << " -> " << colonias[i].nombre << " " << colonias[i].x << " " << colonias[i].y << " " << colonias[i].central << endl;
    }
    cout << "-------------------------" << endl;
    /**/

    /**/
    // Imrpimir las conexiones en la matriz
    cout << "-------------------------" << endl;

    cout << "   ";
    for (int i = 0; i < n; i++){
        cout << i << "  ";
    }
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int j = 0; j < n; j++) {
            cout << mapa[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-------------------------" << endl;

    // Leer y analizar las nuevas colonias
    for (int i = 0; i < q; i++) {
        // Colonias con una conexion
        string nombre;
        // Costo de la conexion
        int x, y;

        // Leer la conexion
        cin >> nombre >> x >> y;

        // Crear la colonia
        colonia nueva(nombre, x, y, false);

        // Buscar la colonia para conectarla
        colonia coloniaCercana = algoritmos :: coloniaMinimaDistancia(nueva, colonias);
        cout << "Colonia cercana: " << coloniaCercana.nombre << endl;
    }
    
    
    // system("pause");
    return 0;
}


/*
5 8 2
LindaVista 200 120 1
Purisima 150 75 0
Tecnologico -50 20 1
Roma -75 50 0
AltaVista -50 40 0
LindaVista Purisima 48
LindaVista Roma 17
Purisima Tecnologico 40
Purisima Roma 50
Purisima AltaVista 80
Tecnologico Roma 55
Tecnologico AltaVista 15
Roma AltaVista 18
Independencia 180 -15
Roble 45 68


    
    
    

*/