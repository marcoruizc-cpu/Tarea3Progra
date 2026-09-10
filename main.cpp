#include <iostream>
#include <vector>
#include "core_numeric.h"

int main() {
    std::vector<int> muestra_enteros{1, 2, 3, 4, 5};
    std::vector<double> datos{1.0, 2.0, 3.0, 4.0, 5.0};

    // SUM
    std::cout << "sum(muestra_enteros) = " << core_numeric::sum(muestra_enteros) << '\n';
    std::cout << "sum(datos) = " << core_numeric::sum(datos) << '\n';

    // MEAN
    std::cout << "mean(datos) = " << core_numeric::mean(datos) << '\n';

    // VARIANCE
    std::cout << "variance(datos) = " << core_numeric::variance(datos) << '\n';

    // MAX
    std::cout << "max(datos) = " << core_numeric::max(datos) << '\n';

    // TRANSFORM_REDUCE (promedio de x^2 sobre doubles, reutilizando mean)
    auto mean_of_squares = core_numeric::transform_reduce(
        datos,
        [](double x) { return x * x; }
    );
    std::cout << "transform_reduce(datos, x^2) = " << mean_of_squares << '\n';

    // VARIADIC
    std::cout << "sum_variadic(1,2,33,4) = " << core_numeric::sum_variadic(1, 2, 33, 4) << '\n';
    std::cout << "mean_variadic(0.1,2,3,4) = " << core_numeric::mean_variadic(0.1, 2, 3, 4) << '\n';
    std::cout << "variance_variadic(1,2,3,4) = " << core_numeric::variance_variadic(1, 2, 3, 4) << '\n';
    std::cout << "max_variadic(1,2.7,3,4) = " << core_numeric::max_variadic(1, 2.7, 3, 4) << '\n';

    return 0;
}
