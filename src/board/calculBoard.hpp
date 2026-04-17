#pragma once

#include <array>
#include <string>
#include <algorithm>
#include <fstream>

#include <QObject>

#include "pieces.hpp"
#include "../tree/tree.hpp"


class CalculBoard : public QObject{
    Q_OBJECT

    public:
        CalculBoard();


        std::array<int, 64> getBoard() const;


        std::string indexToCase(int ind) const;

        std::string moveToPGN(int from, int to, bool hasCaptured, bool hasCheck, bool hasMate, int promotionPiece = 0, int piece = 1);


        bool isMovePossible(int currentId, int newId);


        int movePiece(int currentId, int newId);

        int castle(int oldKing, int newKing);


        void handleMove(int currentId, int newId);


        bool pawnMove(int currentId, int newId);

        bool slideMove(int currentId, int newId, const int dirs[], int dirCount) const;

        bool knightMove(int currentId, int newId) const;

        bool kingMove(int currentId, int newId);


        bool isCaseAttacked(int idCase, int color) const;

        bool isKingInCheck(int ind = -1) const;

        bool isKingCheckmated();


        bool hasLegalMoves();


        std::vector<int> getAmbiguousPieces(int from, int to, int piece);

        std::string getDisambiguation(int from, int to, int piece);


        void writePGN() const;

        void treeBack();

        void treeNext();


    signals:
        void setPromotionMenu(bool show, int color);

        void sendEndGame();

    public slots:
        void promoteTo(int piece);

    private:
        Tree tree;
        Tree* currentTree;
        
        std::array<int, 64> board;
        int colorPlaying;
        int indEnPassant;
        bool isWLCP;
        bool isWRCP;
        bool isBLRP;
        bool isBRRP;
};
