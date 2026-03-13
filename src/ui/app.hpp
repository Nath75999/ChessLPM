#pragma once

#include <QApplication>
#include <QGridLayout>

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
};
