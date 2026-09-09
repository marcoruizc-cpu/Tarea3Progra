#include <iostream>
#include <vector>
#include "core_numeric.h"
#include "../shapes.h"

int main() {
    // ---------- Casos que SI compilan ----------

    // doubles + lambda que devuelve double: Addable<double> es
    // verdad, y ResultType (double) cumple Divisible -> mean()
    // interno funciona.
    std::vector<double> doubles{1.0, 2.0, 3.0};
    auto media_cuadrados = core_numeric::transform_reduce(
        doubles, [](double x) { return x * x; });
    std::cout << "transform_reduce(doubles, x^2) = " << media_cuadrados << '\n'; // 4.66667

    // vector<int> + lambda que devuelve double explicitamente: aqui
    // Addable<int> (el value_type del contenedor de ENTRADA) es
    // verdad, y como la lambda castea a double, ResultType es double
    // (que SI cumple Divisible), evitando el hueco de Divisible<int>.
    std::vector<int> ints{1, 2, 3, 4};
    auto media_cuadrados_ints = core_numeric::transform_reduce(
        ints, [](int x) { return static_cast<double>(x * x); });
    std::cout << "transform_reduce(ints, x^2 a double) = " << media_cuadrados_ints << '\n';

    // ===== Casos que NO compilan =====

    // Esfera no define operator+ -> Addable<Esfera> es falso -> el
    // "requires" de la firma de transform_reduce la rechaza de
    // entrada, antes de mirar la lambda.
    // std::vector<Esfera> esferas{{1.0}, {2.0}};
    // core_numeric::transform_reduce(esferas, [](Esfera e) { return e.radio; });

    // vector<int> + lambda que devuelve int (sin castear a double):
    // el "requires Addable<int>" de la firma SI se cumple (para el
    // contenedor de entrada), pero adentro, ResultType termina siendo
    // int, y mean(vector<int>) exige Divisible<int>, que es FALSO
    // (ver la explicacion en tests/mean/test.cpp sobre int/size_t).
    // El error aparece dentro del cuerpo de transform_reduce, no en
    // su propia firma -> mismo hueco de diseño que en variance().
    // std::vector<int> ints2{1, 2, 3, 4};
    // core_numeric::transform_reduce(ints2, [](int x) { return x * x; });

    return 0;
}
