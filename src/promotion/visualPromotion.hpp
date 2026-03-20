#pragma once

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>

#include "calculPromotion.hpp"

class VisualPromotion : public QWidget{
    public:
        VisualPromotion(QWidget* parent = nullptr, const std::array<QPixmap, 8>& sprites = {}, int x = 0, int y = 0, int w = 800, int h = 800);

        void setColor(int color);

        CalculPromotion* getCPromotion();

    protected:
        void paintEvent(QPaintEvent*) override;
        void mousePressEvent(QMouseEvent* event) override;

    private:
        CalculPromotion cPromotion;
        std::array<QPixmap, 8> sprites;
        int x;
        int y;
        int w;
        int h;
        int color;

};
