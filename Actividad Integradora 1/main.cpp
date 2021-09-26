#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "algoritmos.hpp"
#define N 3

using namespace std;

// Complejidad O(n)
vector<string> leerCodigos(){
    vector<string> codigosMaliciosos;
    ifstream mcode("mcode.txt");
    
    if (mcode.fail()){ // Si fallo, terminar programa
        throw runtime_error("Hubo un Error al cargar el archivo mcode.txt");
    }

    string smcode;
    while (!mcode.eof()){
        mcode >> smcode;
        codigosMaliciosos.push_back(smcode);
    }
    mcode.close();

    return codigosMaliciosos;
}


vector<string> leerTransmisiones(){
    vector<ifstream> ifVTransmissions(N);
    vector<string> sVTransmissions(N);

    for (int i=0; i<N; i++){
        // Leer todo el codigo de cada archivo y ponerlo en sVTransmissions
        ifVTransmissions[i].open("transmission" + to_string(i+1), ios::out);
        if (ifVTransmissions[i].fail()){ // Si falla, terminar el programa
            throw runtime_error("Hubo un Error al cargar el archivo transmission" + to_string(i+1) + ".txt");

        }
        
        sVTransmissions[i].assign(  (istreambuf_iterator<char>(ifVTransmissions[i])),     
                                    (istreambuf_iterator<char>()));

        ifVTransmissions[i].close();
    }

    return sVTransmissions;
}

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
                ifChecking << posMatch[i] << " ";
            }
            ifChecking << endl;
        }
        ifChecking << "--------------" << endl;
    }
    ifChecking << "==============" << endl;
}

void palindromo(ofstream& ifChecking, vector<string> sVTransmissions){
    for (int i = 0; i < N; i++){
        int iPos;
        string sPalindromo;
        algoritmos :: manacher(sVTransmissions[i], sPalindromo, iPos); //ToDo: Hacer que manacher devuelva tambien la posicion del palindromo
        ifChecking << "Transmission" << i+1 << ".txt ==> Posición: " << iPos << endl; 
        ifChecking << sPalindromo << endl;
        ifChecking << "----" << endl;
    }

    ifChecking << "============" << endl;
}
void substring(ofstream& ifChecking, vector<string> sVTransmissions){
    // ToDo: Substring entre los 3 archivos
}


int main(){
    vector<string> codigosMaliciosos;
    vector<string> sVTransmissions(N);
    ofstream ifChecking;
    
    try{
        // Leer mcode.txt
        codigosMaliciosos = leerCodigos();

        // Leer archivos de transmision
        sVTransmissions = leerTransmisiones();

        // Abrir el archivo de Salida
        ifChecking.open("cheking2.txt", ios::in);
        if (ifChecking.fail()){ // Si falla, terminar el programa
            throw runtime_error("Hubo un Error al cargar el archivo cheking.txt");
        }
    }
    catch(const exception& e){
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
    return 0;
}