//
// Created by Aeomanate on 07.08.2021.
//

#ifndef LODE_RUNNER_LADDER_HPP
#define LODE_RUNNER_LADDER_HPP


#include "Cell.hpp"

struct Ladder: Cell {
    explicit Ladder() { SetSpriteByName("ladder"); }
    
    [[nodiscard]] bool IsLadder() const override;
    [[nodiscard]] bool IsContainLadder() const override;
    
    [[nodiscard]] bool IsOccupiable(Coord this_pos, Coord from_pos) const override;
    std::optional<std::unique_ptr<EntityState<Character>>>
    Occupy(Coord this_pos, Coord occupant_pos, Character* character, EntityChecker checker) override;
};


#endif // LODE_RUNNER_LADDER_HPP
