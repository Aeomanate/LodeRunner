//
// Created by Aeomanate on 07.08.2021.
//

#ifndef LODE_RUNNER_CHARACTERIDLE_HPP
#define LODE_RUNNER_CHARACTERIDLE_HPP


#include <Character.hpp>

#include "EntityState.hpp"

class Character;
class CharacterIdle: public EntityState<Character> {
  public:
    explicit CharacterIdle(
        Character* character,
        Coord direction,
        std::string character_name
    );
    
    std::unique_ptr<EntityState<Character>> Update(Coord cur_pos) override;
    
    [[nodiscard]] bool IsIdleState() const override;
    
    [[nodiscard]] Coord CurViewDirection() const override;
    
  private:
    Coord cur_view_direction = {0, 0};
};


#endif // LODE_RUNNER_CHARACTERIDLE_HPP
