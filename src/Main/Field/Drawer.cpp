// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 08.08.2021.
//

#include "Drawer.hpp"
#include "Cell.hpp"

void additionAssign(DrawQueue& a, DrawQueue b) {
    while(not b.empty()) {
        a.push(b.front());
        b.pop();
    }
}

void Drawer::GetCellsDrawOrder(CellStorage const& cells_storage) {
    for(unsigned y = 0; y != cells_storage.size(); ++y) {
        for(unsigned x = 0; x != cells_storage[0].size(); ++x) {
            draw_matrix[y][x] = cells_storage[y][x]->GetDrawOrder();
        }
    }
}

void Drawer::Draw() {
    bool is_need_draw_next_layer = false;
    do {
        is_need_draw_next_layer = false;
        for(unsigned y = 0; y != draw_matrix.size(); ++y) {
            for(unsigned x = 0; x != draw_matrix[0].size(); ++x) {
                if(not draw_matrix[y][x].empty()) {
                    draw_matrix[y][x].front()->Draw({(int)x, (int)y});
                    draw_matrix[y][x].pop();
                    if(not draw_matrix[y][x].empty()) {
                        is_need_draw_next_layer = true;
                    }
                }
            }
        }
    } while(is_need_draw_next_layer);
}
