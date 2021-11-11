#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

// Estructura de datos para representar una colonia
struct colonia {
    string nombre; // Nombre de la colonia
    int x, y; // Posicion en el mapa
    bool central; // Si es una colonia central
};


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
        int c;

        // Leer la conexion
        cin >> a >> b >> c;

        // Buscar el id de las colonias
        int ia = coloniasHash[a];
        int ib = coloniasHash[b];

        // Guardar la conexion en la matriz
        mapa[ia][ib] = c;
        mapa[ib][ia] = c;
    }

    /*
    // Imprimir lo leido
    cout << "-------------------------" << endl;

    for (int i = 0; i < n; i++){
        cout << i << " -> " << colonias[i].nombre << " " << colonias[i].x << " " << colonias[i].y << " " << colonias[i].central << endl;
    }
    */

    /*
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
    */
    
    system("pause");
    return 0;
}


/*



    
    
    

*/