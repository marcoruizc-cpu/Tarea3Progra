#ifndef UNTITLED20_CORE_NUMERIC_H
#define UNTITLED20_CORE_NUMERIC_H

#include <concepts>
#include <iterator>
#include <cstddef>
#include <algorithm>
#include <stdexcept>
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

    template <typename T>
    concept Multipliable = requires(T a, T b) {
        { a * b } -> std::same_as<T>;
    };

    // Concept necesario para la función MAX
    template <typename T>
    concept Comparable = requires(T a, T b) {
        { a < b } -> convertible_to<bool>;
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
                 Multipliable<typename C::value_type>
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
    template <Iterable C, typename UnaryOp, typename BinaryOp, typename T>
    auto transform_reduce(const C& container, T init, UnaryOp transform, BinaryOp reduce) {
        T result = init;
        for (const auto& value : container) {
            result = reduce(result, transform(value));
        }
        return result;
    }

}

#endif // UNTITLED20_CORE_NUMERIC_H