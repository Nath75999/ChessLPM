#pragma once

#include <array>
#include <string>

#include "piece.hpp"


class CalculBoard{
    public:
        CalculBoard();


        std::array<int, 64> getBoard() const;


        std::pair<int, int> caseToIndex(const std::string& c);


        virtual bool isMovePossible(int currentId, int newId);


        void movePiece(int currentId, int newId);

        void roque(int king, int ind);


        void handleMove(int currentId, int newId);


        bool pawnMove(int currentId, int newId);

        bool slideMove(int currentId, int newId, const int dirs[], int dirCount);

        bool knightMove(int currentId, int newId);

        bool kingMove(int currentId, int newId);


    private:
        std::array<int, 64> board;
        bool isWLRP;
        bool isWRRP;
        bool isBLRP;
        bool isBRRP;
};
