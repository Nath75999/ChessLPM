#include "calculPromotion.hpp"

void CalculPromotion::promotePawn(QPoint mouseClick, int width, int height){
    int x = mouseClick.x();
    int y = mouseClick.y();

    int piece = EMPTY;

    if (y < x && y < width - x) piece = QUEEN;
    else if (y > x && y > width - x) piece = BISHOP;
    else if (y > x && y < width - x) piece = KNIGHT;
    else piece = ROOK;

    emit this->sendNewPiece(piece);
}
