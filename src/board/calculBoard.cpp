#include "calculBoard.hpp"

CalculBoard::CalculBoard() : board{0}, colorPlaying(WHITE), isWLCP(true), isWRCP(true), isBLRP(true), isBRRP(true) {
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


std::pair<int, int> CalculBoard::caseToIndex(const std::string& c) const {return {c[0] - 'a', 8 - static_cast<int>(c[1])};}

bool CalculBoard::isMovePossible(int currentId, int newId){
    if (newId < 0 || newId >= 64) return false;

    int value = this->board[currentId];

    if(value == EMPTY) return false;

    if(board[newId] != EMPTY && board[newId] / 10 == value / 10) return false;

    if (value / 10 != this->colorPlaying) return false;

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

int CalculBoard::movePiece(int oldId, int newId){
    if (oldId < 0 || oldId >= 64 || newId < 0 || newId >= 64) return 1;
    
    int piece = this->board[oldId];
    int backupPiece = this->board[newId];

    if (piece % 10 == KING && abs(oldId - newId) == 2) return this->castle(oldId, newId);

    this->board[oldId] = EMPTY;
    this->board[newId] = piece;

    int kingInd = std::distance(this->board.begin(), std::find(this->board.begin(), this->board.end(), 10 * colorPlaying + KING));
    if (isKingInCheck(kingInd)){
        this->board[oldId] = piece;
        this->board[newId] = backupPiece;
        return 1;
    }

    if (isWLCP && (oldId == 56 || oldId == 60)) isWLCP = false;
    if (isWRCP && (oldId == 63 || oldId == 60)) isWRCP = false;

    if (isBLRP && (oldId == 0 || oldId == 4)) isBLRP = false;
    if (isBRRP && (oldId == 7 || oldId == 4)) isBRRP = false;

    if (piece % 10 == PAWN && piece / 10 == WHITE && newId / 8 == 0) emit setPromotionMenu(true, WHITE);
    if (piece % 10 == PAWN && piece / 10 == BLACK && newId / 8 == 7) emit setPromotionMenu(true, BLACK);

    return 0;
}

int CalculBoard::castle(int oldKing, int newKing) {
    int king = board[oldKing];
    int color = king / 10;

    bool isShortCastle = (newKing > oldKing);

    if (!this->isCaseAttacked(newKing, color)){
        if (isShortCastle){
            if (color == WHITE && !isWRCP || color == BLACK && !isBRRP) return 1;

            for (int i = 1; i < 3; i++)
                if (board[oldKing + i] != EMPTY || this->isCaseAttacked(oldKing + i, color)) return 1;

        } 
        else{
            if (color == WHITE && !isWLCP || color == BLACK && !isBLRP) return 1;

            for (int i = 1; i < 4; i++)
                if (board[oldKing - i] != EMPTY || this->isCaseAttacked(oldKing - i, color)) return 1;
        }

        board[oldKing] = EMPTY;
        board[newKing] = king;

        int rookId = isShortCastle ? oldKing + 3 : oldKing - 4;
        board[rookId] = EMPTY;
        board[isShortCastle ? newKing - 1 : newKing + 1] = 10 * color + ROOK;

        if (!color){
            isWLCP = false;
            isWRCP = false;
        } 
        else{
            isBLRP = false;
            isBRRP = false;
        }

        this->colorPlaying = !this->colorPlaying;

        return 0;
    } 
    else return 1;
}


void CalculBoard::handleMove(int currentId, int newId){
    if (!isMovePossible(currentId, newId) || this->board[currentId] == EMPTY) return;

    if (this->movePiece(currentId, newId)) return;

    this->colorPlaying = !this->colorPlaying;

    if (!isKingInCheck() && !hasLegalMoves()){
        emit sendEndGame();
        return;
    }

    if (this->isKingCheckmated()){
        emit sendEndGame();
        return;
    }
}


bool CalculBoard::pawnMove(int currentId, int newId) const {
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

bool CalculBoard::slideMove(int currentId, int newId, const int dirs[], int dirCount) const {
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

bool CalculBoard::knightMove(int currentId, int newId) const {
    int r2 = newId / 8;
    int c2 = newId % 8;

    if (r2 < 0 || r2 >= 8 || c2 < 0 || c2 >= 8) return false;

    int r1 = currentId / 8;
    int c1 = currentId % 8;

    int dr = std::abs(r1 - r2);
    int dc = std::abs(c1 - c2);

    return (dr == 2 && dc == 1) || (dr == 1 && dc == 2);
}

bool CalculBoard::kingMove(int currentId, int newId){
    for (int i = 0; i < 2; i++) 
        if (currentId + kingRoque[i] == newId) return !castle(currentId, newId); //The '!' is very important, or else smothered checkmate won't be detected

    for (int i = 0; i < 8; i++) 
        if (currentId + kingMoves[i] == newId) return true;

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

bool CalculBoard::isCaseAttacked(int idCase, int color) const {
    if (idCase < 0 || idCase >= 64) return false; //error

    int row = idCase / 8;
    int col = idCase % 8;

    // PAWNS
    int pawnDir = (!color) ? -1 : 1;
    int indPawn1 = idCase + 7 * pawnDir;
    int indPawn2 = idCase + 9 * pawnDir;

    if (indPawn1 >= 0 && indPawn1 < 64 && std::abs((indPawn1 % 8) - col) == 1 &&
        board[indPawn1] % 10 == PAWN && board[indPawn1] / 10 != color) return true;
    
    if (indPawn2 >= 0 && indPawn2 < 64 && std::abs((indPawn2 % 8) - col) == 1 &&
        board[indPawn2] % 10 == PAWN && board[indPawn2] / 10 != color) return true;

    // KNIGHTS
    for (int i = 0; i < 8; i++){
        int c = idCase + knightMoves[i];
        if (c >= 0 && c < 64 && std::abs((c % 8) - col) <= 2 && 
            board[c] % 10 == KNIGHT && board[c] / 10 != color) return true;
    }

    // SLIDING PIECES
    for (int i = 0; i < 4; i++){
        // BISHOPS AND QUEENS
        int c = idCase + bishopDirs[i];
        while (c >= 0 && c < 64 && std::abs((c % 8) - col) == std::abs((c / 8) - row)){
            int piece = board[c];
            if (piece != EMPTY) {
                if (piece / 10 != color && (piece % 10 == BISHOP || piece % 10 == QUEEN)) return true;
                break;
            }
            c += bishopDirs[i];
        }

        // ROOKS AND QUEENS
        c = idCase + rookDirs[i];
        while (c >= 0 && c < 64) {
            int piece = board[c];

            int cRow = c / 8;
            int cCol = c % 8;

            if (cRow != row && cCol != col) break;

            if (piece != EMPTY){
                if (piece / 10 != color && (piece % 10 == ROOK || piece % 10 == QUEEN)) return true;
                break;
            }

            c += rookDirs[i];
        }
    }

    //ENEMY KING
    for (int i = 0; i < 8; i++) {
        int c = idCase + kingMoves[i];

        if (c >= 0 && c < 64 && std::abs((c % 8) - col) <= 1 &&
            board[c] % 10 == KING && board[c] / 10 != color) return true;
    }

    return false;
}

bool CalculBoard::isKingInCheck(int ind) const {
    if (ind < 0){
        auto it = std::find(board.begin(), board.end(), 10 * colorPlaying + KING);
        ind = std::distance(board.begin(), it);
    }
    
    if (this->board[ind] % 10 != KING) return false;

    return this->isCaseAttacked(ind, this->board[ind] / 10);
}

bool CalculBoard::isKingCheckmated(){
    auto it = std::find(board.begin(), board.end(), 10 * colorPlaying + KING);

    int kingIndex = std::distance(board.begin(), it);

    if (!this->isKingInCheck(kingIndex)) return false;

    return !this->hasLegalMoves(); 
}


bool CalculBoard::hasLegalMoves(){
    // Check each piece of the current player for legal moves
    for (int from = 0; from < 64; from++){
        if (board[from] == EMPTY || board[from] / 10 != this->colorPlaying) continue;

        // Try all possible destination squares
        for (int to = 0; to < 64; to++){
            if (!isMovePossible(from, to)) continue;

            // Simulate the move
            int captured = board[to];
            int piece = board[from];

            board[to] = piece;
            board[from] = EMPTY;

            // Find the king and check if it's in check after the move
            auto it = std::find(board.begin(), board.end(), 10 * this->colorPlaying + KING);
            int kingIndex = std::distance(board.begin(), it);

            bool kingInCheck = isKingInCheck(kingIndex);

            // Undo the move
            board[from] = piece;
            board[to] = captured;

            // If king is not in check, we found a legal move
            if (!kingInCheck) return true;
        }
    }
    // No legal moves found
    return false;
}
