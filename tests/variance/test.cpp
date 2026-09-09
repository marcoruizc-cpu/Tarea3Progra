// test.cpp - core_numeric::variance
//
// variance() esta restringida con Addable + Divisible + Multipliable
// + Subtractable, y reutiliza mean(). El concept Subtractable se
// agrego especificamente porque el cuerpo de variance() usa el
// operador "-" (value - m) para las diferencias al cuadrado, y
// ningun otro concept lo garantizaba: antes de agregarlo, un tipo sin
// operator- pasaba el "requires" y fallaba mas adentro, con un error
// de plantilla mucho menos claro que un rechazo limpio por concept.

#include <iostream>
#include <cstddef>
#include <vector>
#include "core_numeric.h"
#include "../shapes.h"

// Tipo pensado a proposito para exponer ese hueco: cumple Addable,
// Divisible y Multipliable, pero NO define operator-.
struct SinResta {
    double valor{};

    friend SinResta operator+(const SinResta& a, const SinResta& b) {
        return SinResta{a.valor + b.valor};
    }

    friend SinResta operator*(const SinResta& a, const SinResta& b) {
        return SinResta{a.valor * b.valor};
    }

    friend SinResta operator/(const SinResta& a, std::size_t n) {
        return SinResta{a.valor / static_cast<double>(n)};
    }
};

int main() {
    // ===== Casos que SI compilan =====

    // double cumple Addable, Divisible y Multipliable.
    std::vector<double> doubles{1.0, 2.0, 3.0};
    std::cout << "variance(doubles) = " << core_numeric::variance(doubles) << '\n'; // 0.666667

    // Vectores3D cumple los tres concepts (ver shapes.h) y SI define
    // operator-, entonces variance(vectores) compila y calcula la
    // varianza componente a componente.
    std::vector<Vectores3D> vectores{{0, 0, 0}, {2, 4, 6}, {4, 8, 12}};
    std::cout << "variance(vectores) = " << core_numeric::variance(vectores) << '\n';

    // ===== Casos que NO compilan =====

    // vector<int>: falla por el mismo hueco de Divisible<int> que en
    // mean() (int / size_t no da int).
    // std::vector<int> ints{1, 2, 3, 4, 5};
    // core_numeric::variance(ints);

    // Coordenadas no cumple Divisible ni Multipliable (no define
    // operator/ ni operator*) -> el "requires" de variance() la
    // rechaza directamente, antes de llegar al cuerpo.
    // std::vector<Coordenadas> puntos{{1.0, 2.0}, {3.0, 4.0}};
    // core_numeric::variance(puntos);

    // SinResta cumple Addable + Divisible + Multipliable, pero NO
    // define operator- -> Subtractable<SinResta> es falso, y ahora el
    // "requires" de la firma de variance() la rechaza de entrada,
    // antes de llegar al cuerpo (a diferencia de antes de agregar
    // Subtractable, cuando el error salia mas adentro).
    // std::vector<SinResta> datos{{1.0}, {2.0}, {3.0}};
    // core_numeric::variance(datos);

    return 0;
}
