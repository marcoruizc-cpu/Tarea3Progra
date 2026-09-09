#include <iostream>
#include <string>
#include <vector>
#include "core_numeric.h"
#include "../shapes.h"

int main() {
    // ===== Casos que SI compilan =====

    // int cumple Addable: {a + b} -> same_as<int> es verdad.
    std::vector<int> ints{1, 2, 3, 4, 5};
    std::cout << "sum(ints) = " << core_numeric::sum(ints) << '\n'; // 15

    // double cumple Addable igual que int.
    std::vector<double> doubles{1.5, 2.5, 3.0};
    std::cout << "sum(doubles) = " << core_numeric::sum(doubles) << '\n'; // 7

    // std::string tambien cumple Addable: string + string -> string
    // (a diferencia de const char*, que es el ejemplo del enunciado
    // que SI falla, ver mas abajo).
    std::vector<std::string> palabras{"Pro", "gra", "ma", "cion"};
    std::cout << "sum(palabras) = " << core_numeric::sum(palabras) << '\n'; // "Programacion"

    // Clase propia Coordenadas: define operator+, entonces cumple
    // Addable<Coordenadas>.
    std::vector<Coordenadas> puntos{{1.0, 2.0}, {3.0, 4.0}};
    auto suma_puntos = core_numeric::sum(puntos);
    std::cout << "sum(puntos) = " << suma_puntos << '\n'; // (4, 6)

    // ===== Casos que NO compilan =====

    // Esfera no define operator+ en absoluto, entonces la expresion
    // {a + b} dentro del concept Addable ni siquiera es valida ->
    // Addable<Esfera> es falso -> el compilador rechaza la llamada
    // porque no existe ninguna instanciacion de sum() que la acepte
    // (error de "no matching function", detectado por el concept, no
    // dentro del cuerpo de la funcion).
    // std::vector<Esfera> esferas{{1.0}, {2.0}, {3.0}};
    // core_numeric::sum(esferas);

    // Un int suelto (no un contenedor) no cumple Iterable: no tiene
    // begin()/end().
    // int x = 5;
    // core_numeric::sum(x);

    return 0;
}
