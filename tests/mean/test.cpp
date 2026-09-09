#include <iostream>
#include <vector>
#include "core_numeric.h"
#include "../shapes.h"

int main() {
    // ===== Casos que SI compilan =====

    // double / size_t -> double (el size_t se convierte a double),
    // entonces Divisible<double> es verdad.
    std::vector<double> doubles{1.0, 2.0, 3.0};
    std::cout << "mean(doubles) = " << core_numeric::mean(doubles) << '\n'; // 2

    // Vectores3D define operator/(Vectores3D, size_t) que devuelve
    // Vectores3D explicitamente, entonces Divisible<Vectores3D> es
    // verdad (aqui no aplican las reglas de conversion de tipos
    // primitivos, es un operador que nosotros definimos).
    std::vector<Vectores3D> vectores{{1, 1, 1}, {3, 3, 3}};
    auto promedio_vectores = core_numeric::mean(vectores);
    std::cout << "mean(vectores) = " << promedio_vectores << '\n'; // (2, 2, 2)

    // ===== Casos que NO compilan =====

    // vector<int>: por el hueco de Divisible<int> explicado arriba,
    // int no cumple Divisible, entonces mean(ints) no tiene ninguna
    // instanciacion valida.
    // std::vector<int> ints{1, 2, 3, 4, 5};
    // core_numeric::mean(ints);

    // Coordenadas no define operator/ en absoluto -> Divisible<Coordenadas>
    // es falso.
    // std::vector<Coordenadas> puntos{{1.0, 2.0}, {3.0, 4.0}};
    // core_numeric::mean(puntos);

    return 0;
}
