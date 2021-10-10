// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and Cur#: http://www.viva64.com
//
// Created by Aeomanate on 06.08.2021.
//

#include "Cell.hpp"
#include "Drawer.hpp"
#include "Sprites.hpp"
#include "EntityState.hpp"

void Cell::SetSpriteByName(std::string const& name) {
    sprite = &Sprites::smap[name];
}

bool Cell::IsContainPlayer()     const { return content and content->IsContainPlayer();     }
bool Cell::IsContainEnemy()      const { return content and content->IsContainEnemy();      }
bool Cell::IsContainTrap()       const { return content and content->IsContainTrap();       }
bool Cell::IsContainLadder()     const { return content and content->IsContainLadder();     }
bool Cell::IsContainRope()       const { return content and content->IsContainRope();       }
bool Cell::IsContainBreackable() const { return content and content->IsContainBreackable(); }
bool Cell::TryBreak()                  { return content and content->TryBreak();            }
void Cell::SetStuck() { }
bool Cell::IsOccupiable(Coord this_pos, Coord from_pos) const {
    return not content or content->IsOccupiable(this_pos, from_pos);
}

void Cell::Update(Coord cur_pos) {
    if(content) content->Update(cur_pos);
}

void Cell::Draw(Coord cur_pos) const {
    Coord draw_pos = cur_pos * dss;
    sprite->Draw(draw_pos.x, draw_pos.y);
}

DrawQueue Cell::GetDrawOrder() const {
    DrawQueue draw_queue;
    draw_queue.push(this);
    if(content) additionAssign(draw_queue, content->GetDrawOrder());
    return draw_queue;
}


Cell::Cell() {
    if(not sprite) SetSpriteByName("no_sprite");
}

std::optional<std::unique_ptr<EntityState<Character>>> Cell::Occupy(
    Coord cur,
    Coord occupant,
    Character* player,
    Cell::EntityChecker checker
)
{
    return nullptr;
}


