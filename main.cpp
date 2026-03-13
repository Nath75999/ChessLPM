#include "main.hpp"

#include <QResource>

int main(int argc, char* argv[]){
    Q_INIT_RESOURCE(resources);

    App app(argc, argv);

    return app.run();
}
