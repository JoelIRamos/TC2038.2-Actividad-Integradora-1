#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "algoritmos.hpp"
#define N 3

using namespace std;

int main(){
    // Leer mcode.txt
    vector<string> codigosMaliciosos;
    ifstream mcode("mcode.txt");
    
    if (mcode.fail()){ // Si fallo, terminar programa
        cout << "Hubo un Error al cargar el archivo mcode.txt" << endl;
        return 0;
    }

    string smcode;
    while (!mcode.eof()){
        cin >> smcode;
        codigosMaliciosos.push_back(smcode);
    }
    mcode.close();


    // Leer archivos de transmision
    vector<ifstream> ifVTransmissions(N);
    vector<string> sVTransmissions(N);

    for (int i=0; i<N; i++){
        // Leer todo el codigo de cada archivo y ponerlo en sVTransmissions
        ifVTransmissions[i].open("transmission" + to_string(i+1), ios::out);
        if (ifVTransmissions[i].fail()){ // Si falla, terminar el programa
            cout << "Hubo un Error al cargar el archivo transmission" << i+1 << ".txt" << endl;
            return 0;
        }

        /*
        
        ToDo: Ingresar todo el archivo a sVTransmissions[i]
        
        */

        ifVTransmissions[i].close();
    }

    // Abrir el archivo de Salida
    ofstream ifChecking;
    ifChecking.open("cheking2.txt", ios::in);
    if (ifChecking.fail()){ // Si falla, terminar el programa
        cout << "Hubo un Error al cargar el archivo cheking.txt" << endl;
    }

    // *Coincidencias
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
                ifChecking << posMatch[i] << " ";
            }
            ifChecking << endl;
        }
        ifChecking << "--------------" << endl;
    }
    ifChecking << "==============" << endl;



    // *Palindromo más grande
    for (int i = 0; i < N; i++){
        int iPos;
        string sPalindromo;
        algoritmos :: manacher(sVTransmissions[i], sPalindromo, iPos); //ToDo: Hacer que manacher devuelva tambien la posicion del palindromo
        ifChecking << "Transmission" << i+1 << ".txt ==> Posición: " << iPos << endl; 
        ifChecking << sPalindromo << endl;
        ifChecking << "----" << endl;
    }

    ifChecking << "============" << endl;
    

    // *Substring más largo
    // ToDo: Substring entre los 3 archivos?



    // Cerrar el archivo de salida y termina el programa
    ifChecking.close();
    return 0;
}