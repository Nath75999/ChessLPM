#include "tree.hpp"

Tree::Tree(const std::string& move, Tree* parent, std::vector<std::unique_ptr<Tree>> lines) 
    : move(move), parent(parent) {
        if (!lines.empty()){
            mainLine = std::move(lines[0]);
            mainLine->parent = this;
            this->mainLine = std::move(lines[0]);
            lines.erase(lines.begin());

            for (auto& line : lines){
                line->parent = this;
                this->variants.push_back(std::move(line));
            }
        }
}


std::unique_ptr<Tree> Tree::clone() const {
    auto copy = std::make_unique<Tree>(move);

    if (mainLine){
        auto child = mainLine->clone();
        child->parent = copy.get();
        copy->mainLine = std::move(child);
    }

    for (const auto& variant : variants){
        auto v = variant->clone();
        v->parent = copy.get();
        copy->variants.push_back(std::move(v));
    }

    return copy;
}


Tree* Tree::previous() {return parent;}

Tree* Tree::next() {return getLine();}


void Tree::addMainLine(const Tree& line){
    if (mainLine) return;

    auto copy = line.clone();
    copy->parent = this;
    mainLine = std::move(copy);
}

void Tree::addMainline(const std::string& line) {addMainLine(Tree(line));}

void Tree::addLine(const Tree& variant){
    if (!mainLine){
        addMainLine(variant);
        return;
    }
    auto copy = variant.clone();
    copy->parent = this;

    variants.push_back(std::move(copy));
}

void Tree::deleteLine(int nbLine){
    if (nbLine == 0){
        auto toDelete = std::move(mainLine);

        if (variants.empty()) return;
        addMainLine(*variants[0]->clone());
    }
    if (nbLine >= variants.size()) return;

    variants.erase(variants.begin() + nbLine - 1);
}


void Tree::setMove(const std::string& move) {this->move = move;}

std::string Tree::getMove() const {return this->move;}

Tree* Tree::getLine(int nbLine) const {
    if (nbLine == 0) return mainLine.get();
    if (nbLine - 1>= variants.size()) return nullptr;
    
    return variants[nbLine - 1].get();
}


void Tree::writeData(std::ofstream& game, int nbCoup, bool isWhite, bool isVariant) const {
    if (!game.is_open()){
        std::cout << "ERROR WHEN OPENING GAME FILE\n";
        return;
    }

    if (move == "") return;

    if (isWhite){
        if (isVariant) game << nbCoup << "...";
        else game << nbCoup << ".";
    }
    if (!isWhite && isVariant) game<< "..";

    game<< " " << move << " ";

    for (auto& variant : variants){
        if (variant){
            game<< "(";
            variant->writeData(game, nbCoup, isWhite, true);
            game<< ") ";
        }
    }

    if (mainLine){
        if (isWhite) ++nbCoup;
        mainLine->writeData(game, nbCoup, !isWhite, false);
    } 
}
