#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <climits>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

vector<string> strings_a, strings_b;
vector<int> cost_insert(26);
vector<int> cost_delete(26);
vector<vector<int>> cost_replace(26, vector<int>(26));
vector<vector<int>> cost_transpose(26, vector<int>(26));

void cargar_strings(){
    ifstream arch_string_a("cadenas1.txt");
    ifstream arch_string_b("cadenas2.txt");
    string line;

    getline(arch_string_a, line);
    stringstream ss_str_a(line);
    string str_a;
    while (ss_str_a >> str_a){
        strings_a.push_back(str_a);
    }

    getline(arch_string_b, line);
    stringstream ss_str_b(line);
    string str_b;
    while (ss_str_b >> str_b){
        strings_b.push_back(str_b);
    }
}

void cargar_costos(){
    ifstream arch_insert("cost_insert.txt");
    ifstream arch_delete("cost_delete.txt");
    ifstream arch_replace("cost_replace.txt");
    ifstream arch_transpose("cost_transpose.txt");

    if (!arch_insert || !arch_delete || !arch_replace || !arch_transpose){
        cout << "Error al abrir uno o más archivos de costos" << endl;
        exit(1);
    }

    string linea;
    getline(arch_insert, linea);
    stringstream ss_insert(linea);
    int costo;
    int pos = 0;
    while (ss_insert >> costo) {
        cost_insert[pos++] = costo;
    }

    getline(arch_delete, linea);
    stringstream ss_delete(linea);
    pos = 0;
    while (ss_delete >> costo){
        cost_delete[pos++] = costo;
    }

    for (int i = 0; i < 26; ++i){
        getline(arch_replace, linea);
        stringstream ss_replace(linea);
        for (int j = 0; j < 26; ++j){
            ss_replace >> costo;
            cost_replace[i][j] = costo;
        }
    }

    for (int i = 0; i < 26; ++i){
        getline(arch_transpose, linea);
        stringstream ss_transpose(linea);
        for (int j = 0; j < 26; ++j) {
            ss_transpose >> costo;
            cost_transpose[i][j] = costo;
        }
    }

    arch_insert.close();
    arch_delete.close();
    arch_replace.close();
    arch_transpose.close();
}

int costo_ins(int pos){
    return cost_insert[pos];
}

int costo_del(int pos){
    return cost_delete[pos];
}

int costo_sub(int pos1, int pos2){
    return cost_replace[pos1][pos2];
}

int costo_trans(int pos1, int pos2){
    return cost_transpose[pos1][pos2];
}

int fuerza_bruta(string a, string b, int i, int j){
    if (i == 0){
        int costo_minimo = 0;
        for (int k = 0; k < j; k++){
            costo_minimo += costo_ins(b[k] - 'a');
        }
        return costo_minimo;
    }

    if (j == 0){
        int costo_minimo = 0;
        for (int k = 0; k < i; k++){
            costo_minimo += costo_del(a[k] - 'a');
        }
        return costo_minimo;
    }

    int insertar = costo_ins(b[j-1] - 'a') + fuerza_bruta(a, b, i, j-1);
    int eliminar = costo_del(a[i-1] - 'a') + fuerza_bruta(a, b, i-1, j);
    int sustituir = (a[i-1] != b[j-1]) 
                    ? costo_sub(a[i-1] - 'a', b[j-1] - 'a') + fuerza_bruta(a, b, i-1, j-1)
                    : fuerza_bruta(a, b, i-1, j-1);

    int transponer = INT_MAX;
    if (i > 1 && j > 1 && a[i-1] == b[j-2] && a[i-2] == b[j-1]){
        transponer = costo_trans(a[i-2] - 'a', a[i-1] - 'a') + fuerza_bruta(a, b, i-2, j-2);
    }

    return min({insertar, eliminar, sustituir, transponer});
}

int prog_dinamica(string a, string b){
    int n = a.length();
    int m = b.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    dp[0][0] = 0;
    if (n == 0){
        for (int j = 1; j <= m; j++){
            dp[0][j] = dp[0][j-1] + min(costo_ins(b[j-1] - 'a'),costo_del(b[j-1] - 'a'));
        }
    } else if (m == 0){
        for (int i = 1; i <= n; i++){
            dp[i][0] = dp[i-1][0] + min(costo_ins(a[i-1] - 'a'),costo_del(a[i-1] - 'a'));
        }
    }
    for (int j = 1; j <= m; j++){
        dp[0][j] = dp[0][j-1] + costo_ins(b[j-1] - 'a');
    }

    for (int i = 1; i <= n; i++){
        dp[i][0] = dp[i-1][0] + costo_del(a[i-1] - 'a');
    }

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            dp[i][j] = min({
                dp[i-1][j] + costo_del(a[i-1] - 'a'),
                dp[i][j-1] + costo_ins(b[j-1] - 'a'),
                dp[i-1][j-1] + (a[i-1] == b[j-1] ? 0 : costo_sub(a[i-1] - 'a', b[j-1] - 'a')),
                (i > 1 && j > 1 && a[i-1] == b[j-2] && a[i-2] == b[j-1]) 
                    ? dp[i-2][j-2] + costo_trans(a[i-2] - 'a', a[i-1] - 'a')
                    : INT_MAX
            });
        }
    }

    return dp[n][m];
}

void ejecutar_algoritmos(string a, string b){
    auto start = chrono::high_resolution_clock::now();
    cout << "Fuerza Bruta: " << fuerza_bruta(a, b, a.length(), b.length()) << endl;
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);  // Usamos nanosegundos
    cout << "Tiempo promedio de ejecución (Fuerza Bruta): " << duration.count() << " ns" << endl;

    start = chrono::high_resolution_clock::now();
    cout << "DP: " << prog_dinamica(a, b) << endl;
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);  // Usamos nanosegundos
    cout << "Tiempo promedio de ejecución (DP): " << duration.count()  << " ns" << endl;
}

int main(){
    cargar_costos();
    cargar_strings();
    cout << "----- Cadenas vacías -----" << endl;
    for (int j = 0; j < 5; j++){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 19);
        int numero_aleatorio = dis(gen);
        string a = "";
        string b = strings_b[numero_aleatorio];
        ejecutar_algoritmos(a, b);
    }
    for (int j = 0; j < 5; j++){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 19);
        int numero_aleatorio = dis(gen);
        string a = strings_a[numero_aleatorio];
        string b = "";
        ejecutar_algoritmos(a, b);
    }
    cout << "----- Cadenas aleatoriamente distintas entre sí -----" << endl;
    for (int i = 0; i < 20; i++){
        if (i == 10){
            cout << "----- Cadenas similares -----" << endl;
        }
        string a = strings_a[i];
        string b = strings_b[i];
        ejecutar_algoritmos(a, b);
    }

    return 0;
}
