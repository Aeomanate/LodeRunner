//
// Created by Aeomanate on 06.08.2021.
//

#ifndef LODE_RUNNER_FIELD_HPP
#define LODE_RUNNER_FIELD_HPP

#include <fstream>
#include <queue>
#include "Coord.hpp"
#include "Drawer.hpp"
#include "FieldParams.hpp"
#include "Cell.hpp"

class Character;
struct Field {
    CellStorage cells_storage;
    mutable Drawer drawer;
    unsigned gold_pieces_on_level = 0;
    inline static unsigned cur_level = 1;
    
    void Init();
    
    // Format: 20x13 symbols
    // .   - free space
    // H   - ladder
    // -   - rope
    // *   - brick
    // +   - trap
    // #   - bedrock
    // g   - gold
    // e   - enemy
    // p   - player
    void Load(std::shared_ptr<Character> const& player);
    void Update();
    void Draw() const;
    
    std::shared_ptr<Cell>& CellAtCoord(Coord coord);
    
    std::shared_ptr<Cell>&& ExtractEntity(Coord entity_pos, Cell::EntityChecker check);
    
    static bool IsInField(Coord next_pos) {
        return 0 <= next_pos.x and next_pos.x < (int)COLS and
               0 <= next_pos.y and next_pos.y < (int)ROWS;
    }
};

extern Field* g_field;


#endif // LODE_RUNNER_FIELD_HPP
