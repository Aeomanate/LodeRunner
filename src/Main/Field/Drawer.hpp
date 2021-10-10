//
// Created by Aeomanate on 08.08.2021.
//

#ifndef LODE_RUNNER_DRAWER_HPP
#define LODE_RUNNER_DRAWER_HPP


#include <queue>
#include <memory>

#include "FieldParams.hpp"

void additionAssign(DrawQueue& a, DrawQueue b);

class Drawer {
  public:
    void GetCellsDrawOrder(CellStorage const& cells_storage);
    
    void Draw();
    
  private:
    StaticMatrix<ROWS, COLS, DrawQueue> draw_matrix;
};


#endif // LODE_RUNNER_DRAWER_HPP
