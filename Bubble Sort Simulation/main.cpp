#include "bib.h"

int main()
{   
    const int width = 800;
    const int height = 500;
    srand(time(NULL));
    RenderWindow window(VideoMode(width, height, 32), "Bubble Sort Simulation");
    window.setVerticalSyncEnabled(true);// It's always a good thing to do
    window.setFramerateLimit(60);
    int shapesY[width/space]; // To make space between them

    for (int i = 0; i < width/space; i++) {
        shapesY[i] = rand() % height + 1;
    }
    printf("Click up to start the sort\n");

    while (window.isOpen())
    {   
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            sortAndDisplay(shapesY, width/space, height, window);
            printf("Sorting Finished\n");
        }
        else {
            window.clear();
            drawShapes(shapesY, width/space, height, window);
            window.display();
        }
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
    }

    return 0;
}