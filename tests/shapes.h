#ifndef TESTS_SHAPES_H
#define TESTS_SHAPES_H

#include <cstddef>
#include <ostream>

// Coordenadas
struct Coordenadas {
    double x{};
    double y{};

    friend Coordenadas operator+(const Coordenadas& a, const Coordenadas& b) {
        return Coordenadas{a.x + b.x, a.y + b.y};
    }

    friend bool operator==(const Coordenadas& a, const Coordenadas& b) {
        return a.x == b.x && a.y == b.y;
    }

    friend std::ostream& operator<<(std::ostream& os, const Coordenadas& c) {
        return os << "(" << c.x << ", " << c.y << ")";
    }
};

// Vectores3D
struct Vectores3D {
    double x{};
    double y{};
    double z{};

    friend Vectores3D operator+(const Vectores3D& a, const Vectores3D& b) {
        return Vectores3D{a.x + b.x, a.y + b.y, a.z + b.z};
    }

    friend Vectores3D operator-(const Vectores3D& a, const Vectores3D& b) {
        return Vectores3D{a.x - b.x, a.y - b.y, a.z - b.z};
    }

    friend Vectores3D operator*(const Vectores3D& a, const Vectores3D& b) {
        return Vectores3D{a.x * b.x, a.y * b.y, a.z * b.z};
    }

    friend Vectores3D operator/(const Vectores3D& v, std::size_t n) {
        return Vectores3D{v.x / n, v.y / n, v.z / n};
    }

    friend bool operator==(const Vectores3D& a, const Vectores3D& b) {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vectores3D& v) {
        return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    }
};

// Esfera
struct Esfera {
    double radio{};

    friend bool operator<(const Esfera& a, const Esfera& b) {
        return a.radio < b.radio;
    }

    friend bool operator==(const Esfera& a, const Esfera& b) {
        return a.radio == b.radio;
    }

    friend std::ostream& operator<<(std::ostream& os, const Esfera& e) {
        return os << "Esfera(radio=" << e.radio << ")";
    }
};

#endif // TESTS_SHAPES_H
