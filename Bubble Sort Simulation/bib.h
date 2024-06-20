#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <SFML/Window/Keyboard.hpp>

using namespace sf;
using namespace std;

#define space 6

#pragma once
void drawShapes(int shapesY[], const int width, const int height, RenderWindow& window);
void sortAndDisplay(int shapesY[], const int width, const int height, RenderWindow& window);