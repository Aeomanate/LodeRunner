//
// Created by Aeomanate on 09.08.2021.
//

#ifndef LODE_HPP_TRANSPARENTCELL_HPP
#define LODE_HPP_TRANSPARENTCELL_HPP

#include "Cell.hpp"

struct TransparentCell: Cell {
    TransparentCell() { SetSpriteByName("transparent"); }
};

extern std::unique_ptr<TransparentCell> g_transparent_cell;

#endif // LODE_HPP_TRANSPARENTCELL_HPP
