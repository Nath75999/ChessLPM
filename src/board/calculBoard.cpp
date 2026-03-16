#include "calculBoard.hpp"

CalculBoard::CalculBoard() : board{0}, isWLRP(true), isWRRP(true), isBLRP(true), isBRRP(true) {
    this->board[0] = 10 * BLACK + ROOK;
    this->board[1] = 10 * BLACK + KNIGHT;
    this->board[2] = 10 * BLACK + BISHOP;
    this->board[3] = 10 * BLACK + QUEEN;
    this->board[4] = 10 * BLACK + KING;
    this->board[5] = 10 * BLACK + BISHOP;
    this->board[6] = 10 * BLACK + KNIGHT;
    this->board[7] = 10 * BLACK + ROOK;

    for (int i = 0; i < 8; i++) this->board[8 + i] = 10 * BLACK + PAWN;

    this->board[56] = 10 * WHITE + ROOK;
    this->board[57] = 10 * WHITE + KNIGHT;
    this->board[58] = 10 * WHITE + BISHOP;
    this->board[59] = 10 * WHITE + QUEEN;
    this->board[60] = 10 * WHITE + KING;
    this->board[61] = 10 * WHITE + BISHOP;
    this->board[62] = 10 * WHITE + KNIGHT;
    this->board[63] = 10 * WHITE + ROOK;

    for (int i = 0; i < 8; i++) this->board[48 + i] = 10 * WHITE + PAWN;
}


std::array<int, 64> CalculBoard::getBoard() const {return this->board;}


std::pair<int, int> CalculBoard::caseToIndex(const std::string& c) {return {c[0] - 'a', 8 - static_cast<int>(c[1])};}

bool CalculBoard::isMovePossible(int currentId, int newId){
    if (newId < 0 || newId >= 64) return false;

    int value = this->board[currentId];
    bool verif = false;

    if(value == EMPTY) return false;

    if(board[newId] != EMPTY && board[newId] / 10 == value / 10) return false;

    switch(value % 10){
        case PAWN:
            return pawnMove(currentId, newId);

        case KNIGHT:
            return knightMove(currentId, newId);

        case BISHOP:
            return slideMove(currentId, newId, bishopDirs, 4);

        case ROOK:
            return slideMove(currentId, newId, rookDirs, 4);

        case QUEEN:
            return slideMove(currentId, newId, queenDirs, 8);

        case KING:
            return kingMove(currentId, newId);

        default:
            return false;
    }
}

void CalculBoard::movePiece(int oldId, int newId){
    int piece = this->board[oldId];

    if (isWLRP && (oldId == 56 || oldId == 60)) isWLRP = false;
    if (isWRRP && (oldId == 63 || oldId == 60)) isWRRP = false;

    if (isBLRP && (oldId == 0 || oldId == 4)) isBLRP = false;
    if (isBRRP && (oldId == 7 || oldId == 4)) isBRRP = false;

    if (piece % 10 == PAWN && piece / 10 == WHITE && newId / 8 == 0) emit setPromotionMenu(true, WHITE);
    if (piece % 10 == PAWN && piece / 10 == BLACK && newId / 8 == 7) emit setPromotionMenu(true, BLACK);

    this->board[oldId] = EMPTY;
    this->board[newId] = piece;
}

void CalculBoard::roque(int king, int ind){
    int rook = king + (ind ? -4 : 3);

    if (king == 60 && (!ind && this->isWRRP || ind && this->isWLRP)){
        this->movePiece(king, king + kingRoque[ind]);
        this->movePiece(rook, rook + rookRoque[ind]);
        return;
    }
    if (king == 4 && (!ind && this->isBRRP || ind && this->isBLRP)){
        this->movePiece(king, king + kingRoque[ind]);
        this->movePiece(rook, rook + rookRoque[ind]);   
    }
}


void CalculBoard::handleMove(int currentId, int newId){
    if (!isMovePossible(currentId, newId) || this->board[currentId] == EMPTY) return;

    this->movePiece(currentId, newId);
}


bool CalculBoard::pawnMove(int currentId, int newId){
    int piece = board[currentId];
    int color = piece / 10;
    int dir = (color == WHITE) ? N : S;

    if (newId == currentId + dir && board[newId] == EMPTY) return true;

    if (color == WHITE){
        if (currentId / 8 == 6 && newId == currentId + 2 * dir && board[currentId + dir] == EMPTY && board[newId] == EMPTY) 
            return true;
    }

    if (color == BLACK){
        if (currentId / 8 == 1 && newId == currentId + 2 * dir && board[currentId + dir] == EMPTY && board[newId] == EMPTY) 
            return true;
    }

    if (currentId % 8 > 0){
        int captureLeft = currentId + dir + W;
        if (newId == captureLeft && this->board[newId] != EMPTY && board[newId] / 10 != color) return true;
    }

    if (currentId % 8 < 7){
        int captureRight = currentId + dir + E;
        if (newId == captureRight && this->board[newId] != EMPTY && board[newId] / 10 != color) return true;
    }

    return false;
}

bool CalculBoard::slideMove(int currentId, int newId, const int dirs[], int dirCount){
    for (int d = 0; d < dirCount; d++){
        int pos = currentId;

        while (true){
            int prevPos = pos;
            pos += dirs[d];

            if (pos < 0 || pos >= 64) break;

            if (dirs[d] == E || dirs[d] == W){
                if (pos / 8 != prevPos / 8) break;
            }

            if (dirs[d] == NE || dirs[d] == NW || dirs[d] == SE || dirs[d] == SW){
                if (abs((pos % 8) - (prevPos % 8)) != 1 || abs((pos / 8) - (prevPos / 8)) != 1) break;
            }

            if (dirs[d] == N || dirs[d] == S){
                if (pos % 8 != prevPos % 8) break;
            }

            if (pos == newId) return true;

            if (this->board[pos] != EMPTY) break;
        }
    }
    return false;
}

bool CalculBoard::knightMove(int currentId, int newId){
    for (int i = 0; i < 8; i++) if (currentId + knightMoves[i] == newId) return true;

    return false;
}

bool CalculBoard::kingMove(int currentId, int newId){
    for (int i = 0; i < 2; i++) if (currentId + kingRoque[i] == newId){
        this->roque(currentId, i);
        return false;
    }
    for (int i = 0; i < 8; i++) if (currentId + kingMoves[i] == newId) return true;

    return false;
}


void CalculBoard::promoteTo(int piece){
     // find pawn to replace when there's a pawn on first or last rank ->promoted
    for (int i = 0; i < 8; i++){
        if (this->board[i] % 10 == PAWN && this->board[i] / 10 == WHITE){
            this->board[i] = 10 * WHITE + piece;
            emit setPromotionMenu(false, -1);
            return;
        }
    }

    for (int i = 7 * 8; i < 64; i++){
        if (this->board[i] % 10 == PAWN && this->board[i] / 10 == BLACK){
            this->board[i] = 10 * BLACK + piece;
            emit setPromotionMenu(false, -1);
            return;
        }
    }
    //error, shouldn't go there
}
