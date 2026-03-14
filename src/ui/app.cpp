#include "app.hpp"

App::App(int argc, char* argv[]) : app(argc, argv), window(new QWidget()), vboard(new VisualBoard(window)){
    init();
}


void App::init(){
    window->resize(1000, 1000);
    window->setWindowTitle("Chess LPM");

    QGridLayout* grid = new QGridLayout(window); //will be automatically deleted since its parent is window, a QWidget.
    grid->addWidget(vboard, 0, 1); 
}
        

int App::run(){
    window->show();
    
    return app.exec();
}
