// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and Cur#: http://www.viva64.com
//
// Created by Aeomanate on 06.08.2021.
//

#include "Character.hpp"
#include <TransparentCell.hpp>
#include "Field.hpp"
#include "Trap.hpp"
#include "Ladder.hpp"
#include "Rope.hpp"
#include "Bedrock.hpp"
#include "Gold.hpp"
#include "Empty.hpp"
#include "Cell.hpp"
#include "Brick/Brick.hpp"

Field* g_field = nullptr;

void Field::Init() {
    for(auto& row: cells_storage) {
        for(auto& cell: row) {
            cell = std::make_shared<EmptyCell>();
        }
    }
    g_field = this;
    
    auto [w, h] = cells_storage[0][0]->sprite->GetSizeWH();
    Cell::default_sprite_size = {w, h};
    
    g_transparent_cell = std::make_unique<TransparentCell>();
}

void Field::Load(std::shared_ptr<Character> const& player) {
    std::ifstream in("..\\levels\\1.lvl");
    if(not in) {
        throw std::runtime_error(
            "Load " + std::to_string(cur_level) + ".lvl. Not found."
        );
    }
    
    for(auto& row: cells_storage) {
        for(auto& cell: row) {
            int symbol = ' ';
            
            while(isspace(symbol)) {
                symbol = in.get();
                if(not in) {
                    throw std::runtime_error(
                        "Load " + std::to_string(cur_level) + ".lvl. It ill formed."
                    );
                }
            }
            switch(symbol) {
                case '.': cell->content.reset();                       break;
                case 'H': cell->content = std::make_shared<Ladder>();  break;
                case '-': cell->content = std::make_shared<Rope>();    break;
                case '*': cell->content = std::make_shared<Brick>();   break;
                case '+': cell->content = std::make_shared<Trap>();    break;
                case '#': cell->content = std::make_shared<Bedrock>(); break;
                
                case 'g':
                    cell->content = std::make_shared<Gold>();
                    gold_pieces_on_level += 1;
                    break;
                    
                case 'e': break;
                
                case 'p':
                    if(not player) {
                        throw std::logic_error(
                            "Load " + std::to_string(cur_level) +
                            ".lvl. More than one player or no one player."
                        );
                    }
                    cell->content = player;
                    player->ClearGold();
                    break;
                
                default:
                    throw std::runtime_error(
                        std::string("Load " + std::to_string(cur_level) +
                        ".lvl. Unexpected symbol: ") + (char)symbol
                    );
            }
        }
    }
}

void Field::Update() {
    for(unsigned y = 0; y != cells_storage.size(); ++y) {
        for(unsigned x = 0; x != cells_storage[y].size(); ++x) {
            auto& cell_storage = cells_storage[y][x];
            cell_storage->Update({(int)x, (int)y});
        }
    }
}
void Field::Draw() const {
    drawer.GetCellsDrawOrder(cells_storage);
    drawer.Draw();
}

std::shared_ptr<Cell>& Field::CellAtCoord(Coord coord) {
    return cells_storage.at((size_t)coord.y).at((size_t)coord.x);
}

std::shared_ptr<Cell>&&

Field::ExtractEntity(Coord entity_pos, Cell::EntityChecker check) {
    std::shared_ptr<Cell>* cur_entity = &CellAtCoord(entity_pos);
    
    while(*cur_entity) {
        auto* cs_cur_cell = const_cast<std::shared_ptr<Cell> const*>(cur_entity);
        Cell const* c_cur_entity = cs_cur_cell->get();
        if((c_cur_entity->*check)()) {
            return std::move(*cur_entity);
        }
        cur_entity = &(*cur_entity)->content;
    }
    
    throw std::logic_error("Player not found at his cell");
}
