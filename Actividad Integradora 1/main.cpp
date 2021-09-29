#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include "algoritmos.hpp"
#define N 3

using namespace std;

// Funcion para leer el archivo mcode.txt y regresar un vector con los strings
// Complejidad O(n)
vector<string> leerCodigos(){
    vector<string> codigosMaliciosos;
    ifstream mcode("mcode.txt");
    
    if (mcode.fail()){ // Si fallo, lanzar una exepción
        throw runtime_error("Hubo un Error al cargar el archivo mcode.txt");
    }

    string smcode;
    while (!mcode.eof()){ // Mientras todavia haya codigos
        mcode >> smcode;
        codigosMaliciosos.push_back(smcode);
    }
    mcode.close();

    return codigosMaliciosos;
}

// Funcion para leer los archivos de transmisiones y regresar un vector con los textos
// Complejidad: O(1)  - (dado que N es constante de valor 3)
vector<string> leerTransmisiones(){
    vector<string> sVTransmissions(N);

    for (int i=0; i<N; i++){
        ifstream ifTransmissions;

        // Abrir el archivo de transmission(1, 2, ... N).txt
        ifTransmissions.open("transmission" + to_string(i+1) + ".txt", ios::out);
        if (ifTransmissions.fail()){ // Si falla, lanzar exepcion
            throw runtime_error("Hubo un Error al cargar el archivo transmission" + to_string(i+1) + ".txt");

        }
        // Leer todo el codigo del archivo y ponerlo en sVTransmissions[i]
        sVTransmissions[i].assign(  (istreambuf_iterator<char>(ifTransmissions)),     
                                    (istreambuf_iterator<char>()));

        ifTransmissions.close();
    }

    return sVTransmissions;
}

// Funcion para buscar todas las coincidencias de los archivos de transmision
// Complejidad: O()
void coincidencias(ofstream& ifChecking, vector<string> codigosMaliciosos, vector<string> sVTransmissions){
    // Para cada codigo
    for (int i = 0; i < codigosMaliciosos.size(); i++){
        ifChecking << "Código : " << codigosMaliciosos[i] << endl;

        // Para cada archivo de transmision
        for (int j = 0; j < N; j++){

            // Encontrar las coincidencias
            vector<int> posMatch = algoritmos :: kmp(sVTransmissions[j], codigosMaliciosos[i]);

            // Imprimirlas en el achivo 
            ifChecking << "Transmission" << j+1 << ".txt ==> " << posMatch.size() << " veces" << endl;
            for (int k=0; k<posMatch.size(); k++){
                ifChecking << posMatch[k] << " ";
            }
            ifChecking << endl;
        }
        ifChecking << "--------------" << endl;
    }
    ifChecking << "==============" << endl;
}

// Funcion para buscar el palindromo mas grande de cada archivo de transmision
// Complejidad: O()
void palindromo(ofstream& ifChecking, vector<string> sVTransmissions){
    // Para cada archivo de transmision
    for (int i = 0; i < N; i++){
        int iPos;
        string sPalindromo;

        // Encontrar el palindromo
        algoritmos :: manacher(sVTransmissions[i], sPalindromo, iPos);

        // Imprimirla en el archivo
        ifChecking << "Transmission" << i+1 << ".txt ==> Posición: " << iPos << endl; 
        ifChecking << sPalindromo << endl;
        ifChecking << "----" << endl;
    }

    ifChecking << "============" << endl;
}

// Funcion para encontrar el substring más largo de todos los archivos
// Complejidad: O(N)
void substring(ofstream& ifChecking, vector<string> sVTransmissions){
    // ToDo: Substring entre los 3 archivos
    vector<string> lcs(3);
    algoritmos :: longestSubString(sVTransmissions[0], sVTransmissions[1], lcs[0]);
    algoritmos :: longestSubString(sVTransmissions[0], sVTransmissions[2], lcs[1]);
    algoritmos :: longestSubString(sVTransmissions[1], sVTransmissions[2], lcs[2]);

    int max_index;
    if (lcs[0].length() > lcs[1].length()) {
        max_index = 0;
    }
    else if (lcs[0].length() > lcs[2].length()) {
        max_index = 0;
    }
    else if (lcs[1].length() > lcs[2].length()) {
        max_index = 1;
    }
    else {
        max_index = 2;
    }
    ifChecking << "Substring más largo: " << lcs[max_index] << endl;
}


int main(){
    cout << "Running " << endl;
    vector<string> codigosMaliciosos;
    vector<string> sVTransmissions(N);
    ofstream ifChecking;
    
    try{
        // Leer mcode.txt
        codigosMaliciosos = leerCodigos();

        // Leer archivos de transmision
        sVTransmissions = leerTransmisiones();

        // Abrir el archivo de Salida
        ifChecking.open("checking.txt", ios::in);
        if (ifChecking.fail()){ // Si falla, terminar el programa
            throw runtime_error("Hubo un Error al cargar el archivo checking.txt");
        }
    } catch(const exception& e){ // Si hubo un fallo, terminar el programa
        cout << e.what() << endl;
        return 0;
    }
    
    // *Coincidencias
    coincidencias(ifChecking, codigosMaliciosos, sVTransmissions);
    
    // *Palindromo más grande
    palindromo(ifChecking, sVTransmissions);
    
    // *Substring más largo
    substring(ifChecking, sVTransmissions);

    // Cerrar el archivo de salida y termina el programa
    ifChecking.close();

    cout << "Close " << endl;
    return 0;
}