#include "visualBoard.hpp"

VisualBoard::VisualBoard(QWidget* origin) : QWidget(origin), cboard(), vPromotion(), isGameActive(true),
                                            caseSize(100), dragging(false), caseSelected(-1) {
    this->loadTextures();

    std::array<QPixmap, 8> vPromotionSprites = {pieceTextures[WHITE][QUEEN], 
                                                pieceTextures[WHITE][ROOK],
                                                pieceTextures[WHITE][BISHOP],
                                                pieceTextures[WHITE][KNIGHT],
                                                pieceTextures[BLACK][QUEEN], 
                                                pieceTextures[BLACK][ROOK],
                                                pieceTextures[BLACK][BISHOP],
                                                pieceTextures[BLACK][KNIGHT]};

    this->vPromotion = new VisualPromotion(this, vPromotionSprites);
    this->vPromotion->hide();
    this->vPromotion->raise();
    connect(&cboard, &CalculBoard::setPromotionMenu, this, &VisualBoard::changePMS);

    connect(vPromotion->getCPromotion(), &CalculPromotion::sendNewPiece, &cboard, &CalculBoard::promoteTo);

    connect(&cboard, &CalculBoard::sendEndGame, this, &VisualBoard::recieveEndGame);
}


void VisualBoard::loadTextures(){
    this->boardTexture = QPixmap(":/images/board");

    this->pieceTextures[WHITE][PAWN] = QPixmap(":/images/pieces/wPawn");
    this->pieceTextures[WHITE][KNIGHT] = QPixmap(":/images/pieces/wKnight");
    this->pieceTextures[WHITE][BISHOP] = QPixmap(":/images/pieces/wBishop");
    this->pieceTextures[WHITE][ROOK] = QPixmap(":/images/pieces/wRook");
    this->pieceTextures[WHITE][QUEEN] = QPixmap(":/images/pieces/wQueen");
    this->pieceTextures[WHITE][KING] = QPixmap(":/images/pieces/wKing");

    this->pieceTextures[BLACK][PAWN] = QPixmap(":/images/pieces/bPawn");
    this->pieceTextures[BLACK][KNIGHT] = QPixmap(":/images/pieces/bKnight");
    this->pieceTextures[BLACK][BISHOP] = QPixmap(":/images/pieces/bBishop");
    this->pieceTextures[BLACK][ROOK] = QPixmap(":/images/pieces/bRook");
    this->pieceTextures[BLACK][QUEEN] = QPixmap(":/images/pieces/bQueen");
    this->pieceTextures[BLACK][KING] = QPixmap(":/images/pieces/bKing");
}


void VisualBoard::mousePressEvent(QMouseEvent* event){
    if (this->vPromotion->isVisible()) return;

    this->dragging = true;

    this->caseSelected = this->pixelToCase(event->position().x(), event->position().y());
}

void VisualBoard::mouseMoveEvent(QMouseEvent* event){
    if (this->dragging && !this->vPromotion->isVisible()){
        this->mouseX = event->position().x();
        this->mouseY = event->position().y();
        update();
    }
}

void VisualBoard::mouseReleaseEvent(QMouseEvent* event){
    if (this->vPromotion->isVisible()) return;

    this->dragging = false;

    int newId = this->pixelToCase(event->position().x(), event->position().y());

    this->cboard.handleMove(this->caseSelected, newId);

    update();
}


QPoint VisualBoard::caseToPixel(int c){
    if (c < 0 || c > 63) return {-1, -1};

    int row = c / 8;
    int col = c % 8;
    
    return {col * this->caseSize, row * this->caseSize};
}

int VisualBoard::pixelToCase(int x, int y){
    int col = x / caseSize;
    int row = y / caseSize;

    if (col < 0 || col > 7 || row < 0 || row > 7) return -1;
    return row * 8 + col;
}


void VisualBoard::paintEvent(QPaintEvent*){
    QPainter painter(this);

    if (this->isGameActive){
        painter.drawPixmap(0, 0, 800, 800, boardTexture);

        bool mouseOutsideBoard = (this->mouseX < 0 || this->mouseX > 8 * caseSize ||
                                this->mouseY < 0 || this->mouseY > 8 * caseSize);
        if (mouseOutsideBoard){
            this->dragging = false;
            this->caseSelected = -1;
        }

        std::array<int, 64> board = cboard.getBoard();

        for(int i = 0; i < 64; i++){
            int piece = board[i];
            if (piece == EMPTY) continue;

            int x = i % 8;
            int y = i / 8;

            if (i != this->caseSelected || !this->dragging) 
                painter.drawPixmap(x * caseSize, y * caseSize, caseSize, 
                                caseSize, pieceTextures[piece / 10][piece % 10]);
        }

        if (this->dragging) 
            painter.drawPixmap(this->mouseX - caseSize / 2, this->mouseY - caseSize / 2, this->caseSize, 
                            this->caseSize, this->pieceTextures[board[caseSelected] / 10][board[caseSelected] % 10]);
    }
}


void VisualBoard::changePMS(bool show, int color){
    this->vPromotion->setVisible(show);
    if (show || (color != WHITE && color != BLACK)) this->vPromotion->setColor(color);
}

void VisualBoard::recieveEndGame() {this->isGameActive = false;}
