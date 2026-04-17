#pragma once

#include <vector>
#include <memory>
#include <fstream>
#include <iostream>

class Tree{
    public:
        Tree(const std::string& move = "", Tree* parent = nullptr, std::vector<std::unique_ptr<Tree>> lines = {});


        std::unique_ptr<Tree> clone() const;


        Tree* previous();

        Tree* next();


        void addMainLine(const Tree& line);

        void addMainline(const std::string& line);

        void addLine(const Tree& variant);

        void deleteLine(int nbLine);


        void setMove(const std::string& move);

        std::string getMove() const;

        Tree* getLine(int nbLine = 0) const;

        void writeData(std::ofstream& game, int nbCoup = 1, bool isWhite = true, bool isVariant = false) const;

    private:
        std::string move;

        Tree* parent;
        std::unique_ptr<Tree> mainLine;
        std::vector<std::unique_ptr<Tree>> variants;
};
