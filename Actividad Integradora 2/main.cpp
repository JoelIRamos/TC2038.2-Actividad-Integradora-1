#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <float.h>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <fstream>

using namespace std;

#include "Colonia.hpp"
#include "Graph.hpp"
#include "algoritmos.hpp"


int main(){
    // * 1: Leer entrada estandar
    // n = numero de colonias, m = numero de conexiones entre colonias, futuras nuevas colonias que se desean conectar.
    int n, m, q; 
    cin >> n >> m >> q;

    // Vector de colonias
    vector<colonia> colonias(n);

    // Hash de colonias
    unordered_map<string, int> coloniasHash(n);

    // Matriz de adyacencia (con -1 como valor por defecto)
    vector<vector <double> > mapa(n, vector<double>(n, -1));
    
    // Matrices de Adjacencias (con max como valor por defecto): Algoritmos de Floyd
    vector< vector <double> > mat(n, vector<double>(n, DBL_MAX));

    // Matriz de transicion para Algoritmo de Floyd
    vector< vector <int> > p(n, vector<int>(n, -1));

    // Grafo para Kruskal
    Graph g(n,m);

    // 1.1: Leer las colonias
    for (int i = 0; i < n; i++) {
        cin >> colonias[i].nombre >> colonias[i].x >> colonias[i].y >> colonias[i].central;
        coloniasHash[colonias[i].nombre] = i;
    }

    // 1.2: Leer las conexiones
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

        // Guardar la conexion en las matrices
        mapa[ia][ib] = mapa[ib][ia] = c;
        mat[ia][ib] = mat[ib][ia] = c;
        g.addEdge(ia, ib, c);
    }

    // Abir el archivo de salida
    ofstream out("checking2.txt");
    // Si no se pudo abrir el archivo de salida, terminar
    if (out.fail()) {
        cout << "No se pudo abrir el archivo de salida" << endl;
        return 0;
    }

    
    // * 2: Desplegar cuál es la forma óptima de cablear con una nueva fibra óptica conectando colonias de tal forma que se pueda compartir información entre cuales quiera dos colonias en el menor costo pósible
    out << "-------------------" << endl;
    out << "1 – Cableado óptimo de nueva conexión." << endl << endl;

    g.kruskalMST();
    out << g.printEdgesK(colonias, mapa) << endl;
    out << "Costo Total: " << g.costMSTKruskal << endl << endl;

    // * 3 : Problema del viajero del grafo filtrado por colonias no centrales
    out << "-------------------" << endl;
    out << "2 – La ruta óptima." << endl << endl;

    // TODO: Hacer Problema del viajero para colonias no centrales
    // TODO: Insertar la solucuin en out

    out << endl;

    // * 4: Ruta optima para ir de todas las centrales entre si
    out << "-------------------" << endl;
    out << "3 – Caminos más cortos entre centrales." << endl << endl;

    algoritmos :: floyd(mat, p, n, colonias);
    // algoritmos :: print(mat, p, n); // Imprimir para debuggeo
    
    // Imprimir las rutas optimas entre centrales
    for (int i = 0; i < colonias.size()-1; i++){
        if (colonias[i].central){
            for (int j = i+1; j < colonias.size(); j++){
                if (colonias[j].central){
                    algoritmos :: consultas(mat, p, colonias, i, j, out);
                }
            }
        }
        
    }
    out << endl;


    // * 5: Leer y analizar las nuevas colonias
    out << "-------------------" << endl;
    out << "4 – Conexión de nuevas colonias." << endl << endl;
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
        out << nueva.nombre << " debe conectarse con " << coloniaCercana.nombre << endl;
    }
    out << endl;
    out << "-------------------" << endl;
    
    
    // system("pause"); // Pausa para revisar que termino correctamente el programa
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