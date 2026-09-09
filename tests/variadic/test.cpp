#include <iostream>
#include "core_numeric.h"

int main() {
    // ===== Casos que SI compilan =====

    // sum_variadic: todos los Args son int, y cada uno cumple Addable.
    std::cout << "sum_variadic(1,2,33,4) = "
               << core_numeric::sum_variadic(1, 2, 33, 4) << '\n'; // 40

    // mean_variadic: mezcla double e int. A diferencia de mean(), esta
    // version NO usa el concept Divisible en absoluto: solo exige
    // Addable, y hace la division a mano con if constexpr, por eso no
    // hereda el hueco de Divisible<int> que vimos en mean().
    std::cout << "mean_variadic(0.1,2,3,4) = "
               << core_numeric::mean_variadic(0.1, 2, 3, 4) << '\n'; // 2.275

    // mean_variadic con solo enteros: entra por la rama
    // if constexpr (std::is_integral_v<CommonType>), que castea a
    // double antes de dividir.
    std::cout << "mean_variadic(1,2,3,4) [rama entera] = "
               << core_numeric::mean_variadic(1, 2, 3, 4) << '\n'; // 2.5

    // variance_variadic: exige Addable y Multipliable en cada Args.
    std::cout << "variance_variadic(1,2,3,4) = "
               << core_numeric::variance_variadic(1, 2, 3, 4) << '\n'; // 1.25

    // max_variadic: exige Comparable en cada Args, mezcla int y double.
    std::cout << "max_variadic(1,2.7,3,4) = "
               << core_numeric::max_variadic(1, 2.7, 3, 4) << '\n'; // 4

    // ===== Casos que NO compilan =====

    // Mismo ejemplo del enunciado (pagina 3): const char* no cumple
    // Addable porque "a + b" entre dos punteros no es una operacion
    // valida en C++ (sumar dos punteros no tiene sentido, solo
    // puntero + entero) -> Addable<const char*> es falso.
    // core_numeric::sum_variadic("Hola", "Mundo");

    // mean_variadic exige Addable en cada Args -> mismo problema con
    // punteros a char.
    // core_numeric::mean_variadic("Hola", "Mundo");

    return 0;
}
