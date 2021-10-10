//
// Created by Aeomanate on 07.08.2021.
//

#ifndef LODE_RUNNER_EMPTY_HPP
#define LODE_RUNNER_EMPTY_HPP


#include <cassert>
#include "Cell.hpp"
class Character;

struct EmptyCell: Cell {
    explicit EmptyCell() { SetSpriteByName("empty"); }
    
    std::optional<std::unique_ptr<EntityState<Character>>>
    Occupy(Coord this_pos, Coord occupant_pos, Character* character, EntityChecker checker) override;
    [[nodiscard]] bool IsOccupiable(Coord this_pos, Coord from_pos) const override;
    [[nodiscard]] DrawQueue GetDrawOrder() const override;
};


#endif // LODE_RUNNER_EMPTY_HPP
