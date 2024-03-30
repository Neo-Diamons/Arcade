# Arcade
<img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" />

## Description

Arcade is a gaming platform: a program that lets the user choose a game to play and keeps a register of player scores.

To be able to deal with the elements of your gaming plate-form at run-time, your graphics libraries and your games must be implemented as dynamic libraries, loaded at run-time.

Each GUI available for the program must be used as a shared library that will be loaded and used dynamically by the main program.

## Usage

```bash
./arcade [path_to_graphical_library]
```

## Requirements
- g++
- make
- ncurses
- SDL2
- SDL2_ttf
- SDL2_image
- SFML

## Installation

```bash
make
```

## Documentation

[Documentation](https://neo-diamons.github.io/Arcade/) generated with Doxygen.

Or generate it yourself with the following command:

```bash
make doc
```

## Authors

- [**Neo-Diamons**](https://github.com/Neo-Diamons)
- [**Philip.J-Fry**](https://github.com/fry56)
- [**Morgan L**](https://github.com/mlargeot)

Architecture (inside the [include](/include) folder) made with

- [**ValentinPeron**](https://github.com/ValentinPeron)
- [**AugustinBst**](https://github.com/AugustinBst)
- [**Leaallain**](https://github.com/Leaallain)
