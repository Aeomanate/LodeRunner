//
// Created by Aeomanate on 06.08.2021.
//

#ifndef LODE_RUNNER_BRICK_HPP
#define LODE_RUNNER_BRICK_HPP

#include <vector>
#include "Cell.hpp"
#include "EntityState.hpp"


class Brick: public Cell {
    friend class BreakingBrick;
    friend class BrokenBrick;
    friend class RecoveringBrick;
    
  public:
    explicit Brick()
    : breaking_state(EmptyState<Brick>::Make())
    { SetSpriteByName("brick"); }
    
    void Update(Coord cur_pos) override;
    
    [[nodiscard]] DrawQueue GetDrawOrder() const override;
    
    bool TryBreak() override;
    
    [[nodiscard]] bool IsOccupiable(Coord, Coord) const override;
    
    std::optional<std::unique_ptr<EntityState<Character>>>
    Occupy(Coord cur_pos, Coord occupant_pos, Character* character, EntityChecker checker) override;
    
  private:
    [[nodiscard]] bool IsBreackable() const override;
    std::unique_ptr<EntityState<Brick>> MakeBreakingState();
    std::unique_ptr<EntityState<Brick>> MakeBrokenState();
    std::unique_ptr<EntityState<Brick>> MakeRecoveringState();
    
  private:
    std::unique_ptr<EntityState<Brick>> breaking_state;
};

#endif // LODE_RUNNER_BRICK_HPP
