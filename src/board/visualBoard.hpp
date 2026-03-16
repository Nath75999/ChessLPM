#pragma once

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>


#include <array>

#include "calculBoard.hpp"
#include "pieces.hpp"
#include "../promotion/visualPromotion.hpp"

class VisualBoard : public QWidget{
    
    public:
        VisualBoard(QWidget* origin);


        void loadTextures();


        void mousePressEvent(QMouseEvent* event);

        void mouseMoveEvent(QMouseEvent* event);

        void mouseReleaseEvent(QMouseEvent* event);


        QPoint caseToPixel(int c);

        int pixelToCase(int x, int y);


    public slots:
        void changePMS(bool show, int color); //promotion menu


    protected:
        void paintEvent(QPaintEvent*) override;

    private:
        CalculBoard cboard;

        VisualPromotion* vPromotion;

        QPixmap boardTexture;
        std::array<std::array<QPixmap, 7>, 2> pieceTextures;
        
        int caseSize;
        bool dragging;
        int caseSelected;
        int mouseX;
        int mouseY;
};

