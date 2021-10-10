//
// Created by Aeomanate on 08.08.2021.
//

#ifndef LODE_RUNNER_ENTITYSTATE_HPP
#define LODE_RUNNER_ENTITYSTATE_HPP

#include <memory>

#include "AeoGameFramework.hpp"
#include "Coord.hpp"
#include "Sprites.hpp"
#include "RingBuffer.hpp"
#include "Rand.hpp"

template <class Entity>
class EntityState {
  public:
    explicit EntityState(Entity* entity, std::string entity_name)
    : entity(entity)
    , entity_name(std::move(entity_name))
    { }
    
    virtual ~EntityState() = default;
    virtual std::unique_ptr<EntityState> Update(Coord cur_pos) = 0;
    [[nodiscard]] virtual bool IsEmptyState() const { return false; }
    [[nodiscard]] virtual bool IsFallState() const { return false; }
    [[nodiscard]] virtual bool IsOnRopeState() const { return false; }
    [[nodiscard]] virtual bool IsOnLadderState() const { return false; }
    [[nodiscard]] virtual bool IsIdleState() const { return false; }
    [[nodiscard]] virtual bool IsFiringState() const { return false; }
    [[nodiscard]] virtual bool IsLoseState() const { return false; }
    [[nodiscard]] virtual bool IsStuckState() const { return false; }
    
    [[nodiscard]] virtual Coord CurViewDirection() const { return {0, 0}; }
    
  protected:
    Entity* entity;
    std::string entity_name;
};

template <class Entity>
class EmptyState: public EntityState<Entity> {
  public:
    EmptyState(): EntityState<Entity>(nullptr, "") { }
    static std::unique_ptr<EmptyState<Entity>> Make() {
        return std::make_unique<EmptyState<Entity>>();
    }
    
    std::unique_ptr<EntityState<Entity>> Update(Coord) override {
        return nullptr;
    }
    [[nodiscard]] bool IsEmptyState() const override {
        return true;
    }
    
  private:
};



#endif // LODE_RUNNER_ENTITYSTATE_HPP
