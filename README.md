# ChessLPM



## 📝 Description

ChessLPM is an open-source chess learning and training platform built with the Qt framework, designed to make high-level chess education accessible to everyone. In a landscape where many training tools are gated by subscriptions or usage limits, ChessLPM stands out by offering a completely unrestricted experience—all features are provided entirely free of cost. Whether you are a beginner mastering the basics or an advanced player refining your strategy, ChessLPM provides a robust environment for tactical growth. With the desktop version as its foundation and a mobile release on the horizon, this project aims to become a comprehensive, cross-platform companion for players dedicated to improving their game without financial barriers.

## 📁 Project Structure

```
.
├── CMakeLists.txt
├── images
│   ├── board.png
│   └── pieces
│       ├── bBishop.png
│       ├── bKing.png
│       ├── bKnight.png
│       ├── bPawn.png
│       ├── bQueen.png
│       ├── bRook.png
│       ├── wBishop.png
│       ├── wKing.png
│       ├── wKnight.png
│       ├── wPawn.png
│       ├── wQueen.png
│       └── wRook.png
├── main.cpp
├── main.hpp
├── resources.qrc
└── src
    ├── board
    │   ├── calculBoard.cpp
    │   ├── calculBoard.hpp
    │   ├── piece.hpp
    │   ├── pieces.hpp
    │   ├── visualBoard.cpp
    │   └── visualBoard.hpp
    ├── promotion
    │   ├── calculPromotion.cpp
    │   ├── calculPromotion.hpp
    │   ├── visualPromotion.cpp
    │   └── visualPromotion.hpp
    └── ui
        ├── app.cpp
        └── app.hpp
```

## 👥 Contributing

Contributions are welcome! Here's how you can help:

1. **Fork** the repository
2. **Clone** your fork: `git clone https://github.com/Nath75999/ChessLPM.git`
3. **Create** a new branch: `git checkout -b feature/your-feature`
4. **Commit** your changes: `git commit -am 'Add some feature'`
5. **Push** to your branch: `git push origin feature/your-feature`
6. **Open** a pull request

Please ensure your code follows the project's style guidelines and includes tests where applicable.
