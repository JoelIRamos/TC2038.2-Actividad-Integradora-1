namespace algoritmos{
    #include<vector>
    #include<string>
    using namespace std;

// ToDo: Complejidad
    vector<int> lps(string patron){
        int n = patron.length();
        vector<int> lpsv(n,0);
        int j=0, i=1;
        while (i<n){
            if (patron[i] == patron[j]){
                lpsv[i] = j+1;
                j++;
                i++;
            } else {
                if (j==0){
                    lpsv[i] = 0;
                    i++;
                } else {
                    j = lpsv[j-1];
                }
            }
        }
        return lpsv;
    }

// ToDo: Complejidad
    vector<int> kmp(string texto, string patron){
        vector<int> posMatch;
        vector<int> lpsv = lps(patron);
        int j = 0; //indice donde voy en el patron
        int i = 0; // indice donde voy en el texto
        int n = texto.length();
        int m = patron.length();
        if (n < m) {
            return posMatch;
        }
        while (i<n) {
            if (texto[i] == patron[j]){
                i++;
                j++;
                if (j == m) {
                    posMatch.push_back(i-m);
                    j = lpsv[j-1];
                } 
            } else {
                if (j==0) {
                    i++;
                } else {
                    j = lpsv[j-1];
                }
            }
        }
        return posMatch;
    }

    // ToDo: Complejidad
    string manacher(string texto, string& palindromo, int& posicion){
        string T = "";
        int n=texto.length();
        for (int i=0; i<n; i++){
            T += "|";
            T += texto[i];
        }
        T += "|";
        n = T.length();
        vector<int> L(n);
        L[0] = 0;
        L[1] = 1;
        int maxLong=0, maxCentro=0;
        bool exp;
        for (int c=1, li=0, ri=2; ri<n; ri++){
            li = c-(ri-c);
            exp = false;
            if (c-maxLong <= ri && ri >= c+maxLong){
                if (L[li] < (c+L[c]-ri)){
                    L[ri] = L[li];
                }
                else if(L[li] == (c + L[c]) - ri && (c + L[c]) == 2*n){
                    L[ri] = L[li];
                }
                else if(L[li] == (c + L[c]) - ri && (c + L[c]) < 2*n){
                    L[ri] = L[li];
                    exp = true;
                }
                else if(L[li] > (c + L[c]) - ri && (c + L[c]) < 2*n){
                    L[ri] = (c+L[c]) - ri;
                    exp = true;
                }
            }
            else{
                L[ri] = 0;
                exp = true;
            }
            if (exp){
                while((ri + L[ri] < n) && (ri - L[ri] > 0) && (T[ri - L[ri] - 1] == T[ri + L[ri] + 1])){
                    L[ri]++;
                }
            }
            c = ri;
            if (L[ri] > maxLong){
                maxLong = L[ri];
                maxCentro = ri;
            }
        }
        int inicio = (maxCentro-maxLong)/2;
        string salida = "";
        for (int i=inicio; i<(inicio+maxLong); i++){
            salida += texto[i];
        }
        // return salida;
    }

// ToDo: Complejidad
    void longestSubString(string str1,string str2, string& subSTR){
        int iN1 = str1.length();
        int iN2 = str2.length();
        int iMax = 0;
        vector <int> iAux(iN2);
        vector <string> sAux(iN2);
        vector<vector <int> > iLCS (iN1, iAux);
        vector<vector <string> > sLCS (iN1, sAux);

        // Primer Columna
        for (int i=0; i<iN1; i++){
            if (str1[i] == str2[0]){
                iLCS[i][0] = 1;
                iMax = 1;
                
                sLCS[i][0] += str1[i];
                subSTR = str1[i];
            } else {
                iLCS[i][0] = 0;
                sLCS[i][0] = "";
            }
        }

        // Primer Renglon
        for (int j=0; j<iN2; j++){
            if (str2[j] == str1[0]){
                iLCS[0][j] = 1;
                iMax = 1;

                sLCS[0][j] += str2[j];
                subSTR = str2[j];
            } else {
                iLCS[0][j] = 0;
                sLCS[0][j] = "";
            }
        }

        // Resto de la matriz
        for (int i=1; i<iN1; i++){
            for (int j=1; j<iN2; j++){
                if (str1[i] == str2[j]){
                    iLCS[i][j] = iLCS[i-1][j-1] + 1;
                    sLCS[i][j] = sLCS[i-1][j-1] + str1[i];
                    if (iLCS[i][j] > iMax) {
                        iMax = iLCS[i][j];
                        subSTR = sLCS[i][j];
                    }
                } else {
                    iLCS[i][j] = 0;
                    sLCS[i][j] = "";
                }
            }
        }
    }

}