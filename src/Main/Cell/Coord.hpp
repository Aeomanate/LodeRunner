//
// Created by Aeomanate on 08.08.2021.
//

#ifndef LODE_RUNNER_COORD_HPP
#define LODE_RUNNER_COORD_HPP

#include <string>

struct Coord {
    int x = 0, y = 0;
    inline bool operator==(Coord const& other) const {
        return x == other.x and y == other.y;
    }
    inline bool operator!=(Coord const& other) const {
        return not(*this == other);
    }
    inline Coord operator+(Coord const& other) const {
        return {x + other.x, y + other.y};
    }
    inline Coord& operator+=(Coord const& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    inline Coord operator-() const {
        return { -x, -y };
    }
    inline Coord operator*(Coord const& other) const {
        return { x * other.x, y * other.y };
    }
    inline Coord operator-(Coord const& other) const {
        return {x - other.x, y - other.y };
    }
};

inline std::string directionXName(Coord direction) {
    return direction.x > 0 ? "right" : "left";
}


#endif // LODE_RUNNER_COORD_HPP
