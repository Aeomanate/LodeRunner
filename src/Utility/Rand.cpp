// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 04.10.2021.
//

#include "Rand.hpp"

int randInt(int a, int b) {
    static std::mt19937 generator((unsigned)std::chrono::system_clock::now().time_since_epoch().count());
    return std::uniform_int_distribution<int>(a, b)(generator);
}
