#include <iostream>
#include <vector>
#include "core_numeric.h"

int main() {
    std::vector<int> ints{1, 2, 3, 4, 5};
    std::vector<double> doubles{1.0, 2.0, 3.0};

    // SUM
    std::cout << "sum(ints) = " << core_numeric::sum(ints) << '\n';
    std::cout << "sum(doubles) = " << core_numeric::sum(doubles) << '\n';

    // MEAN
    std::cout << "mean(doubles) = " << core_numeric::mean(doubles) << '\n';

    // VARIANCE
    std::cout << "variance(doubles) = " << core_numeric::variance(doubles) << '\n';

    // MAX
    std::cout << "max(doubles) = " << core_numeric::max(doubles) << '\n';

    // TRANSFORM_REDUCE (promedio de x^2 sobre doubles, reutilizando mean)
    auto mean_of_squares = core_numeric::transform_reduce(
        doubles,
        [](double x) { return x * x; }
    );
    std::cout << "transform_reduce(doubles, x^2) = " << mean_of_squares << '\n';


    // VARIADIC
    std::cout << "sum_variadic(1,2,33,4) = " << core_numeric::sum_variadic(1, 2, 33, 4) << '\n';
    std::cout << "mean_variadic(0.1,2,3,4) = " << core_numeric::mean_variadic(0.1, 2, 3, 4) << '\n';
    std::cout << "variance_variadic(1,2,3,4) = " << core_numeric::variance_variadic(1, 2, 3, 4) << '\n';
    std::cout << "max_variadic(1,2.7,3,4) = " << core_numeric::max_variadic(1, 2.7, 3, 4) << '\n';

    return 0;
}
