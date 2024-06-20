#include "bib.h"

void drawShapes(int shapesY[], const int width, const int height, RenderWindow& window) {
    for (int i = 0; i < width; i++) {
        RectangleShape shape;
        shape.setSize(Vector2f(1, shapesY[i]));
        shape.setPosition(space*i, height - shapesY[i]);
        shape.setFillColor(Color(230, 230, 255, 230));
        window.draw(shape);
    }
}

void sortAndDisplay(int shapesY[], const int width, const int height, RenderWindow& window) {
    for (int i = 0; i < width; i++) {
        window.clear();
        for (int j = 1; j < width - i; j++) {
            if (shapesY[j - 1] > shapesY[j]) {

                int tmp = shapesY[j];
                shapesY[j] = shapesY[j - 1];
                shapesY[j - 1] = tmp;

            }
        }
        drawShapes(shapesY, width, height, window);
        window.display();
    }
}
