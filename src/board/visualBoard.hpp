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
    Q_OBJECT
    
    public:
        VisualBoard(QWidget* origin);


        void loadTextures();


        void mousePressEvent(QMouseEvent* event);

        void mouseMoveEvent(QMouseEvent* event);

        void mouseReleaseEvent(QMouseEvent* event);


        QPoint caseToPixel(int c);

        int pixelToCase(int x, int y);


        void calculBoardPGN() const;

        void calculBoardBack();

        void calculBoardNext();


    public slots:
        void changePMS(bool show, int color); //promotion menu

        void recieveEndGame(); //checkmate occured;


    protected:
        void paintEvent(QPaintEvent*) override;

    private:
        VisualPromotion* vPromotion;
        CalculBoard cboard;
        QPixmap boardTexture;
        std::array<std::array<QPixmap, 7>, 2> pieceTextures;
        
        bool isGameActive;
        int caseSize;
        bool dragging;
        int caseSelected;
        int mouseX;
        int mouseY;
};

