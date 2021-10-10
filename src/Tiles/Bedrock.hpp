//
// Created by Aeomanate on 07.08.2021.
//

#ifndef LODE_RUNNER_BEDROCK_HPP
#define LODE_RUNNER_BEDROCK_HPP


#include "Cell.hpp"

struct Bedrock: Cell {
    explicit Bedrock() { SetSpriteByName("bedrock"); }
    [[nodiscard]] bool IsOccupiable(Coord, Coord) const override;
};


#endif // LODE_RUNNER_BEDROCK_HPP
