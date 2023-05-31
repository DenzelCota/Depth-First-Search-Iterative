#include <iostream>
#include <set>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;

void invertirSubcadena(std::string& cadena, int longitud) {
    std::reverse(cadena.begin(), cadena.begin() + longitud + 1);
}

bool profundidadLimitadaDFS(std::string cadenaActual, std::string cadenaFinal, std::set<std::string>& visitados, int maxProfundidad, int& cuentaNodos, int& profundidadEncontrada) {
    std::stack<std::pair<std::string, int>> pila;
    pila.push(std::make_pair(cadenaActual, 0));

    while(!pila.empty()){
        auto nodo = pila.top();
        pila.pop();

        cadenaActual = nodo.first;
        int profundidad = nodo.second;

        visitados.insert(cadenaActual);
        cuentaNodos++;

        if (cadenaActual == cadenaFinal){
            profundidadEncontrada = profundidad;
            return true;
        }

        if (profundidad == maxProfundidad){
            continue;
        }

        for (int i = 1; i < cadenaActual.size(); i++){
            std::string siguiente = cadenaActual;
            invertirSubcadena(siguiente, i);
            if (visitados.count(siguiente) == 0){
                pila.push(std::make_pair(siguiente, profundidad+1));
            }
        }
    }

    return false;
}

int main(){
    int longitud;
    std::cout << "Ingrese la longitud de la cadena a ordenar (max 26): ";
    std::cin >> longitud;

    std::string abc = "abcdefghijklmnopqrstuvwxyz";
    std::string panqueques = abc.substr(0, longitud);
    std::string panquequesOrdenados = panqueques;

    std::random_shuffle(panqueques.begin(), panqueques.end());

    std::cout << "Panqueques: " << panqueques << std::endl;

    std::set<std::string> visitados;
    int cuentaNodos = 0;
    int maxProfundidad = 30;
    bool encontrado = false;
    int profundidadEncontrada = 0;

    for(int i = maxProfundidad; i >= 0; i--){
        visitados.clear();
        cuentaNodos = 0;
        encontrado = profundidadLimitadaDFS(panqueques, panquequesOrdenados, visitados, i, cuentaNodos, profundidadEncontrada);
        if(encontrado){
            std::cout << "Panqueques ordenados: " << panquequesOrdenados << std::endl;
            std::cout << "Profundidad: " << profundidadEncontrada << std::endl;
            std::cout << "Nodos visitados: " << cuentaNodos << std::endl;
            break;
        }
    }

    if (!encontrado){
        std::cout << "No se encontro una solucion" << std::endl;
    }

    return 0;
}
