//
// Created by Aeomanate on 07.08.2021.
//

#ifndef LODE_RUNNER_GOLD_HPP
#define LODE_RUNNER_GOLD_HPP


#include "Cell.hpp"

struct Gold: Cell {
    explicit Gold() { SetSpriteByName("gold"); }
    [[nodiscard]] bool IsGold() const override;
};

#endif // LODE_RUNNER_GOLD_HPP
