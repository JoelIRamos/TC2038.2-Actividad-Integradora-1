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
    
    // Matrix de adyacencia de tamaño m (con valor DBL_MAX como valor por defecto) *Punto 3* 
    vector<vector <int> > matAdj(n*n, vector<int>(n*n, 0));

    // Vector de colonias no centrales
    vector <int> no_centrales;
    
    // Matrices de Adjacencias (con max como valor por defecto): Algoritmos de Floyd
    vector< vector <double> > mat(n, vector<double>(n, DBL_MAX));

    // Matriz de transicion para Algoritmo de Floyd
    vector< vector <int> > p(n, vector<int>(n, -1));

    // Grafo para Kruskal
    Graph g(n,m);

    // 1.1: Leer las colonias
    for (int i = 0; i < n; i++) {
        cin >> colonias[i].nombre >> colonias[i].x >> colonias[i].y >> colonias[i].central;
        if (!colonias[i].central) {
            no_centrales.push_back(i);
        }
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
        matAdj[ia][ib] = matAdj[ib][ia] = (int) c;
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

    // * 3 : Problema del la ruta optima
    out << "-------------------" << endl;
    out << "2 – La ruta óptima." << endl << endl;

    // Vector con las rutas
    vector <string> path;
    // Para utilizarlo con el punto de origen. Nodo hacia donde vamos
    int fin = 0;
    // Score total del viaje
    int current = 0;
    for (int i = 0; i < no_centrales.size(); i++) {
        // Aumentamos en 1 fin para ir al siguiente nodo
        fin++;

        // Ir del nodo final al principio
        if (fin == no_centrales.size()) {
            // Para ir al nodo de partida
            fin = 0;
            // Vamos con la matAdj, el número de nodos, el nodo de partida y el nodo al cuál vamos, colonias y la ruta
            current += algoritmos :: dijks(matAdj, n, no_centrales[i], no_centrales[fin], colonias, path);
        }

        // Ir de un nodo al siguiente en la lista.
        else {
            current += algoritmos :: dijks(matAdj, n, no_centrales[i], no_centrales[fin], colonias, path);
        }
    }
    for (int i = 0; i < path.size(); i++) {
        out << path[i];
        if (!(i == path.size() - 1)) {
            out << " - ";
        }
    }
    out << endl << endl;
    out << "La Ruta Óptima tiene un costo total de: " << current << endl << endl;

    // * 4: Rutas optimas para ir de todas las centrales entre si
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

.\main < in01.txt
*/