//
// Created by Aeomanate on 08.08.2021.
//

#ifndef LODE_RUNNER_FIELDPARAMS_HPP
#define LODE_RUNNER_FIELDPARAMS_HPP

#include <queue>

static size_t const ROWS = 13;
static size_t const COLS = 20;

template <size_t ROWS, size_t COLS, class T>
using StaticMatrix = std::array<std::array<T, COLS>, ROWS>;

struct Cell;
using CellStorage = StaticMatrix<ROWS, COLS, std::shared_ptr<Cell>>;

using DrawQueue = std::queue<Cell const*>;

#endif //LODE_RUNNER_FIELDPARAMS_HPP
