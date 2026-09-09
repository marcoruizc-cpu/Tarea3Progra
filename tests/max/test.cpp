#include <iostream>
#include <vector>
#include "core_numeric.h"
#include "../shapes.h"

int main() {
    // ===== Casos que SI compilan =====

    // int y double tienen operator< nativo -> cumplen Comparable.
    std::vector<int> ints{4, 1, 9, 2};
    std::cout << "max(ints) = " << core_numeric::max(ints) << '\n'; // 9

    std::vector<double> doubles{1.0, 2.7, 0.3};
    std::cout << "max(doubles) = " << core_numeric::max(doubles) << '\n'; // 2.7

    // Esfera define operator< comparando por radio -> cumple Comparable.
    std::vector<Esfera> esferas{{1.0}, {5.0}, {3.0}};
    std::cout << "max(esferas) = " << core_numeric::max(esferas) << '\n'; // Esfera(radio=5)

    // ===== Casos que NO compilan =====

    // Vectores3D no define operator< (un vector 3D no tiene un orden
    // natural) -> Comparable<Vectores3D> es falso.
    // std::vector<Vectores3D> vectores{{1, 1, 1}, {2, 2, 2}};
    // core_numeric::max(vectores);

    // Coordenadas tampoco define operator< -> mismo problema.
    // std::vector<Coordenadas> puntos{{1.0, 2.0}, {3.0, 4.0}};
    // core_numeric::max(puntos);

    return 0;
}
