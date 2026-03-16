# UTILISATION:

#NOTES: Penser a mettre les images dans resources.qrc, et a les référencer avec le préfixe ":/images/..." dans le code.

# COMPILATION

    # A la racine du projet:

        # 1 - En une ligne:

            # rm -rf build; cmake -B build -S .; cmake --build build; ./build/ChessLPM

        # 2 - En plusieurs étapes:
            # rm -rf build (si nécessaire)

            # cmake -B build -S .

            # cmake --build build

            # Exécution:

            # cd build

            # ./ChessLPM


cmake_minimum_required(VERSION 3.20...3.30)

project(ChessLPM LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_standard_project_setup()

# Sources récursives
file(GLOB_RECURSE SOURCES
    src/*.cpp
    ui/*.cpp
)

# Traitement EXPLICITE des ressources
qt_add_resources(RESOURCES_SOURCES resources.qrc)

qt_add_executable(ChessLPM
    main.cpp
    ${SOURCES}
    ${RESOURCES_SOURCES}
)

target_include_directories(ChessLPM PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/board
    ${CMAKE_CURRENT_SOURCE_DIR}/src/board/pieces
    ${CMAKE_CURRENT_SOURCE_DIR}/ui
)

target_link_libraries(ChessLPM PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

# Copie images (pour debug si besoin)
add_custom_command(TARGET ChessLPM POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/images
        $<TARGET_FILE_DIR:ChessLPM>/images
)
