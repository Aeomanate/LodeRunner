//
// Created by Aeomanate on 06.08.2021.
//

#ifndef LODE_RUNNER_CELL_HPP
#define LODE_RUNNER_CELL_HPP

#include <optional>
#include <string>
#include <unordered_map>
#include <iostream>
#include <memory>

#include "AeoGameFramework.hpp"
#include "FieldParams.hpp"
#include "Coord.hpp"

class Character;
template <class Character>
class EntityState;

struct Cell {
    std::shared_ptr<Cell> content;
    ALSprite* sprite = nullptr;
    void SetSpriteByName(std::string const& name);
    inline static Coord default_sprite_size = Coord{0, 0};
    inline static const Coord& dss = default_sprite_size;
    
    
    [[nodiscard]] virtual bool IsPlayer()     const { return false; }
    [[nodiscard]] virtual bool IsEnemy()      const { return false; }
    [[nodiscard]] virtual bool IsGold()       const { return false; }
    [[nodiscard]] virtual bool IsTrap()       const { return false; }
    [[nodiscard]] virtual bool IsLadder()     const { return false; }
    [[nodiscard]] virtual bool IsBreackable() const { return false; }
    using EntityChecker = bool(Cell::*)() const;
    
    [[nodiscard]] virtual bool IsContainPlayer()     const;
    [[nodiscard]] virtual bool IsContainEnemy()      const;
    [[nodiscard]] virtual bool IsContainTrap()       const;
    [[nodiscard]] virtual bool IsContainLadder()     const;
    [[nodiscard]] virtual bool IsContainRope()       const;
    [[nodiscard]] virtual bool IsContainBreackable() const;
    
    [[nodiscard]] virtual bool IsOccupiable(Coord this_pos, Coord from_pos) const;
    
    // Occupy cell with assign to occupant new state.
    // std::nullopt - not change state.
    // nullptr - wrong state, skip it.
    virtual std::optional<std::unique_ptr<EntityState<Character>>>
    Occupy(Coord cur, Coord occupant, Character* player, EntityChecker checker);
    
    virtual bool TryBreak();
    
    // Recursively update current cell and inner cells.
    virtual void Update(Coord cur_pos);
    
    [[nodiscard]] virtual DrawQueue GetDrawOrder() const;
    
    // x→ y↓ -- Position on g_field around other cells.
    // Recursively draw current cell and inner cells.
    virtual void Draw(Coord cur_pos) const;
    
    virtual void SetStuck();
    
    virtual ~Cell() = default;
    
  protected:
    explicit Cell();
};


#endif // LODE_RUNNER_CELL_HPP
