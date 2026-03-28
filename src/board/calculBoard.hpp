#pragma once

#include <array>
#include <string>
#include <algorithm>

#include <QObject>

#include "pieces.hpp"


class CalculBoard : public QObject{
    Q_OBJECT

    public:
        CalculBoard();


        std::array<int, 64> getBoard() const;


        std::pair<int, int> caseToIndex(const std::string& c) const;


        bool isMovePossible(int currentId, int newId);


        int movePiece(int currentId, int newId);

        int castle(int oldKing, int newKing);


        void handleMove(int currentId, int newId);


        bool pawnMove(int currentId, int newId) const;

        bool slideMove(int currentId, int newId, const int dirs[], int dirCount) const;

        bool knightMove(int currentId, int newId) const;

        bool kingMove(int currentId, int newId);


        bool isCaseAttacked(int idCase, int color) const;

        bool isKingInCheck(int ind) const;

        bool isKingCheckmated(int ind);


        bool hasLegalMoves();


    signals:
        void setPromotionMenu(bool show, int color);

        void sendEndGame();

    public slots:
        void promoteTo(int piece);

    private:
        std::array<int, 64> board;
        int colorPlaying;
        bool isWLCP;
        bool isWRCP;
        bool isBLRP;
        bool isBRRP;
};
