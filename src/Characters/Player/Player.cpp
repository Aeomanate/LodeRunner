// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and Cur#: http://www.viva64.com
//
// Created by Aeomanate on 06.08.2021.
//

#include "Player.hpp"
#include "EntityState.hpp"
#include "PlayerStateFactory.hpp"

Player::Player() {
    state_factory = std::make_unique<PlayerStateFactory>(this);
    entity_state = state_factory->MakeIdle({-1, 0});
}

void Player::Update(Coord cur_pos) {
    std::unique_ptr<EntityState<Character>> new_state;
    while(true) {
        // New state may instantly switch self to other state.
        // Then we wait until new state will have normally updated
        // that's mean it return nullptr (the current state is executing,
        // and it must not interrupt by switching states)
        new_state = entity_state->Update(cur_pos);
        if(new_state == nullptr) break;
        entity_state = std::move(new_state);
    }
    move_state.Update(cur_pos);
}
void Player::Draw(Coord cur_pos) const { move_state.Draw(cur_pos); }

int Player::Lives() const { return lives; }

bool Player::IsContainPlayer() const { return true; }
bool Player::IsPlayer() const { return true; }
void Player::ClearGold() { gold_pieces = 0; }
void Player::AddGold() { gold_pieces += 1; }
int Player::DecLife() { return lives -= 1; }

