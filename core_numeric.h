#ifndef UNTITLED20_CORE_NUMERIC_H
#define UNTITLED20_CORE_NUMERIC_H

#include <concepts>
#include <iterator>
#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <vector>

using namespace std;

namespace core_numeric {

    template <typename C>
    concept Iterable = requires(C c) {
        begin(c);
        end(c);
    };

    template <typename T>
    concept Addable = requires(T a, T b) {
        { a + b } -> same_as<T>;
    };

    template <typename T>
    concept Divisible = requires(T a, size_t n) {
        { a / n } -> same_as<T>;
    };
    // TAREA : Crear uno adicional y aplicarlo
    // aca se cumple el primer punto
    template <typename T>
    concept Multipliable = requires(T a, T b) {
        { a * b } -> std::same_as<T>;
    };

    // Concept necesario para la función MAX
    template <typename T>
    concept Comparable = requires(T a, T b) {
        { a < b } -> convertible_to<bool>;
    } && !Iterable<T>;

    template <typename T>
    concept Subtractable = requires(T a, T b) {
        { a - b } -> std::same_as<T>;
    };

    // ==========================================
    // 2. ALGORITMOS CONTENEDORES
    // ==========================================

    // SUM
    template <Iterable C>
        requires Addable<typename C::value_type>
    auto sum(const C& container) {
        typename C::value_type result{};
        for (const auto& value : container) {
            result = result + value;
        }
        return result;
    }

    // MEAN
    template <Iterable C>
        requires Divisible<typename C::value_type>
    auto mean(const C& container) {
        if (container.empty()) return typename C::value_type{};
        return sum(container) / container.size();
    }

    // VARIANCE
    template <Iterable C>
        requires Addable<typename C::value_type> &&
                 Divisible<typename C::value_type> &&
                 Multipliable<typename C::value_type> &&
                 Subtractable<typename C::value_type>
    auto variance(const C& container) {
        if (container.empty()) return typename C::value_type{};

        auto m = mean(container);
        typename C::value_type sum_squared_diff{};

        for (const auto& value : container) {
            auto diff = value - m;
            sum_squared_diff = sum_squared_diff + (diff * diff);
        }

        return sum_squared_diff / container.size();
    }

    template <Iterable C>
        requires Comparable<typename C::value_type>
    auto max(const C& container) {
        if (container.empty()) {
            throw std::invalid_argument("El contenedor no puede estar vacío para calcular el máximo.");
        }

        auto it = std::begin(container);
        typename C::value_type max_val = *it;
        ++it;

        for (; it != std::end(container); ++it) {
            if (max_val < *it) {
                max_val = *it;
            }
        }

        return max_val;
    }

    // TRANSFORM_REDUCE
    // Transforma cada elemento aplicando una función (UnaryOp) y luego los reduce (combina) con otra (BinaryOp)
    template <Iterable C, typename UnaryOp>
        requires Addable<typename C::value_type>
    auto transform_reduce(const C& container, UnaryOp transform) {
        using ResultType = decltype(transform(*std::begin(container)));

        std::vector<ResultType> transformed;
        transformed.reserve(container.size());
        for (const auto& value : container) {
            transformed.push_back(transform(value));
        }

        return mean(transformed);
    }

    // SUM VARIADIC (Fold expression unary left)
    template <typename... Args>
        requires (Addable<Args> && ...)
    auto sum_variadic(Args... args) {
        return (... + args);
    }

    // MEAN VARIADIC (Fold expression + Uso obligatorio de if constexpr)
    template <typename... Args>
        requires (Addable<Args> && ...)
    auto mean_variadic(Args... args) {
        static_assert(sizeof...(args) > 0, "Debe pasar al menos un argumento.");

        using CommonType = std::common_type_t<Args...>;
        auto total = sum_variadic(args...);

        // Se diferencia el comportamiento en tiempo de compilación según el tipo
        if constexpr (std::is_integral_v<CommonType>) {
            return static_cast<double>(total) / sizeof...(args);
        } else {
            return total / static_cast<CommonType>(sizeof...(args));
        }
    }

    // VARIANCE VARIADIC acopado con el multipliable
    template <typename... Args>
        requires (Addable<Args> && ...) && (Multipliable<Args> && ...)
    auto variance_variadic(Args... args) {
        static_assert(sizeof...(args) > 0, "Debe pasar al menos un argumento.");

        auto m = mean_variadic(args...);
        double sum_sq_diff = 0.0;

        // Fold expression con operador coma para calcular diferencias al cuadrado
        ((sum_sq_diff += (args - m) * (args - m)), ...);

        return sum_sq_diff / sizeof...(args);
    }

    // MAX VARIADIC (Fold expression con operador ternario)
    template <typename First, typename... Args>
        requires (Comparable<First> && (Comparable<Args> && ...))
    auto max_variadic(First first, Args... args) {
        using Common = std::common_type_t<First, Args...>;
        Common current_max = static_cast<Common>(first);

        ((current_max = (static_cast<Common>(args) > current_max ? static_cast<Common>(args) : current_max)), ...);

        return current_max;
    }


}

#endif // UNTITLED20_CORE_NUMERIC_H