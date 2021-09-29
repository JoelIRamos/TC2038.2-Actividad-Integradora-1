namespace algoritmos{
    #include<vector>
    #include <algorithm>
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
    void manacher(string texto, string& palindromo, int& posicion){
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

        palindromo = salida;
        posicion = inicio;
    }

// ToDo: Complejidad: O(m*n)
    void longestSubString(string str1,string str2, string& subSTR){
        int m = 1000;
        int n = 1000;
        int maxlen = 0;         // stores the max length of LCS
        int endingIndex = m;    // stores the ending index of LCS in `X`
    
        int lookup[m + 1][n + 1];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                lookup[i][j] = 0;
            }
        }
    
        // fill the lookup table in a bottom-up manner
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                // if the current character of `X` and `Y` matches
                if (str1[i - 1] == str2[j - 1]) {
                    lookup[i][j] = lookup[i - 1][j - 1] + 1;

                    if (lookup[i][j] > maxlen) {
                        maxlen = lookup[i][j];
                        endingIndex = i;
                    }
                }
            }
        }
    
        subSTR = str1.substr(endingIndex - maxlen, maxlen);
    }

}