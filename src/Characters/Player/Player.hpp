//
// Created by Aeomanate on 06.08.2021.
//

#ifndef LODE_RUNNER_PLAYER_HPP
#define LODE_RUNNER_PLAYER_HPP

#include "Character.hpp"

class Player: public Character {
  public:
    Player();
    
    void Update(Coord cur_pos) override;
    void Draw(Coord cur_pos) const override;
    
    [[nodiscard]] int Lives() const;
    
    [[nodiscard]] bool IsContainPlayer() const override;
    [[nodiscard]] bool IsPlayer() const override;
    
    void ClearGold() override;
    void AddGold() override;
    int DecLife() override;
    
  private:
    int lives = 5;
    int gold_pieces = 0;
};

#endif // LODE_RUNNER_PLAYER_HPP
