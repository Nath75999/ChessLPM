#include "visualPromotion.hpp"

VisualPromotion::VisualPromotion(QWidget* parent, const std::array<QPixmap, 8>& sprites, int x, int y, int w, int h) : 
								 QWidget(parent), sprites(sprites), x(x), y(y), w(w), h(h) {
	this->setGeometry(x, y, w, h);
}

void VisualPromotion::setColor(int color) {this->color = color;}


CalculPromotion* VisualPromotion::getCPromotion() {return &this->cPromotion;}

void VisualPromotion::mousePressEvent(QMouseEvent* event){
	this->cPromotion.promotePawn(QPoint({static_cast<int>(event->position().x()), 
										 static_cast<int>(event->position().y())}), 
										this->width(), this->height());
}


void VisualPromotion::paintEvent(QPaintEvent*){
        QPainter painter(this);

        painter.setPen(QPen(Qt::black, 10));
        painter.setBrush(Qt::white);

		QRect rect = this->rect();

        painter.drawRect(rect);
		painter.drawLines(QList{QPoint{x, y}, QPoint{x + w, y + h}, QPoint{x + w, y}, QPoint{x, y + h}});

		const std::array<int, 4> coefs = {2, 3, 2, 1};

		for (int i = 0; i < 4; i++)
			painter.drawPixmap(coefs[i] * rect.width() / 4 - 250 / 2, 
							   coefs[3 - i] * rect.height() / 4 - 250 / 2, 
							   250, 250, sprites[color * 4 + i]);
}
