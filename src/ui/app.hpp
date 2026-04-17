#pragma once

#include <vector>

#include <QApplication>
#include <QGridLayout>
#include <QPushButton>

#include "../board/visualBoard.hpp"

class App{
    public:
        App(int argc, char* argv[]);


        void init();


        int run();


    private:
        QApplication app;
        QWidget* window;
        VisualBoard* vboard;
        std::vector<QPushButton*> buttons;
};
