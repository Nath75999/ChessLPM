#pragma once

#include <QObject>
#include <QPoint>

#include "../board/pieces.hpp"

class CalculPromotion : public QObject{
    Q_OBJECT

    public:
        void promotePawn(QPoint mouseClick, int width, int height);

    signals:
        void sendNewPiece(int piece);
    
};
