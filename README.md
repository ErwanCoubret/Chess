# ♟️👑 Chess Game in C++

Made by [***COUBRET Erwan***](https://github.com/ErwanCoubret)

[![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://www.cplusplus.com/)

## ✍️ Description

This is a simple 2-players chess game written in C++ for a Engineering course at [*Télécom Physique Strasbourg*](https://www.telecom-physique.fr/).

[![Chess Game](pictures/image.png)]

## 📚 How to play

The game is played in the terminal. The game begin directly after launching it (see **🔩 Commands** section)

Your turn is indicated and you can move the pieces by typing the coordinates of the piece you want to move and the coordinates of the destination square. You can have more details by typing `/help` in the terminal.

## 🔩 Commands

You can run the `makefile` in the root directory to easily do the base commands.

### 🕹️ Build & Run the game
```
make run
```

### 📜 Show documentation

Run the following command
```
make doc
```

and then go to `documentation/index.html` to see the generated documentation.

### 🤖 Level tests

All tests provided by the teacher are in the `tests/data` directory. The provided code has no problem with them.

**Individual tests** (`<number>` from `1` to `4` for the different levels)
```
make test_`<number>`
```

**All tests**
```
make tests
```

### 🧹 Clean
```
make clean
```

## 🌳 Project Structure And Files

```bash
< Project >
     | 
     |-- core/                    # Contains the logic of the game & structures  
     |    |-- board.cpp, board.h  # Contains the board structure and functions
     |    |-- interface.cpp, interface.h # Contains the interface functions for printing
     |    |-- pieces.cpp, pieces.h # Contains the pieces structure and functions
     | 
     |-- pictures/                # Contains the images used in the README
     |
     |-- src/
     |    |-- echecs.cpp          # Main file of the project              
     |          
     |-- tests/                    # Contains the tests for the different levels
     |    |-- data/                # Contains the datasets for the tests given by the teacher
     |    |-- perso/               # Contains tests made by me
     |    |-- test-level.sh        # Script to run the tests for the different levels
     |
     |-- makefile                 # Makefile to compile & run the project
     |     
     |-- ************************************************************************
```

## 💭 Feedbacks on the project

- This project was a **good opportunity to learn C++** and the logic of a chess game, I always thought that a day I would do it and it was a good opportunity to do it. It was a fun project to do even if it was a bit long to debug. I tried to make a good architecture of the project and I think I did it well.

- My main problems was due to the forgotten of the update of position of pieces (with setPosition()) like **90%** of my debugging time was due to this problem. It blocked me for a long time and I was a bit frustrated to not see it before. Like many of my problems could be solved by changing one or two lines.