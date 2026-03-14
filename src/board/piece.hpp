#pragma once

enum Color{
    WHITE, BLACK
};

enum Piece{
    EMPTY, PAWN, KNIGHT, 
    BISHOP, ROOK, QUEEN, KING
};

enum Move{
    N = -8,
    NE = -7,
    E = 1,
    SE = 9,
    S = 8,
    SW = 7,
    W = -1,
    NW = -9
};

const int knightMoves[8] = {
    N + NE,
    N + NW,
    E + NE,
    E + SE,
    S + SE,
    S + SW,
    W + SW,
    W + NW
};

const int kingMoves[8] = {
    N, S, E, W,
    NE, NW, SE, SW
};

const int kingRoque[2] = {
    2 * E,
    2 * W
};

const int rookRoque[2] = {
    2 * W,
    3 * E
};

const int bishopDirs[4] = {
    NE, NW, SE, SW
};

const int rookDirs[4] = {
    N, S, E, W
};

const int queenDirs[8] = {
    N, S, E, W,
    NE, NW, SE, SW
};
