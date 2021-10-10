//
// Created by Aeomanate on 07.08.2021.
//

#ifndef LODE_RUNNER_TRAP_HPP
#define LODE_RUNNER_TRAP_HPP

#include "Cell.hpp"

struct Trap: Cell {
    explicit Trap() { SetSpriteByName("brick"); }
    [[nodiscard]] bool IsOccupiable(Coord, Coord) const override;
    [[nodiscard]] bool IsContainTrap() const override;
    
    std::optional<std::unique_ptr<EntityState<Character>>>
    Occupy(Coord this_pos, Coord occupant_pos, Character* player, EntityChecker checker) override;
    
    [[nodiscard]] DrawQueue GetDrawOrder() const override;
};


#endif // LODE_RUNNER_TRAP_HPP
