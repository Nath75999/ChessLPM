#include "app.hpp"

App::App(int argc, char* argv[]) : app(argc, argv), window(new QWidget()), vboard(new VisualBoard(window)) {
    init();
}


void App::init(){
    window->resize(1000, 1000);
    window->setWindowTitle("Chess LPM");

    QGridLayout* grid = new QGridLayout(window); //will be automatically deleted since its parent is window, a QWidget.
    grid->addWidget(vboard, 0, 0, 4, 4); 

        QPushButton* back = new QPushButton(QString::fromStdString("◄"));
        QPushButton* next = new QPushButton(QString::fromStdString("►"));
        QPushButton* pgn = new QPushButton(QString::fromStdString("Save PGN"));

        QPushButton::connect(pgn, &QPushButton::clicked, [this]() {vboard->calculBoardPGN();});
        QPushButton::connect(back, &QPushButton::clicked, [this]() {vboard->calculBoardBack();});
        QPushButton::connect(next, &QPushButton::clicked, [this]() {vboard->calculBoardNext();});

        buttons.push_back(back);
        buttons.push_back(next);
        buttons.push_back(pgn);

        grid->addWidget(back, 3, 0, 1, 1);
        grid->addWidget(next, 3, 2, 1, 1);
        grid->addWidget(pgn, 3, 1, 1, 1);

    window->setStyleSheet(R"(
                          QPushButton {
                              background-color: #2e63cc;
                              border: 2px solid #2d196f;
                              border-radius: 15px;
                              font-size: 75px;
                          }
                          QPushButton:hover {
                              background-color: #3453ff;
                          }
                          QPushButton:pressed {
                              background-color: #1f329d;
                          }
                          )");
}
        

int App::run(){
    window->show();
    
    return app.exec();
}
