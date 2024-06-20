#include "main_functions.h"

// 1st function for balls simulation
template <class T>
void Balls_Physic_Simulation(RenderWindow &window, int DrawGrid){
    deque < T *> objects;
    int to_detect_mouse_click = 20;
    float radius_of_the_ball = 10.0;

    while(window.isOpen()){

        printf("\e[1;1H\e[2J");
        cout << "Use left click of the mouse to add a ball in the screen." << endl;
        cout << "There is " << objects.size() << " objects" << endl;

        // Creating quad tree to detect all collisions
        QuadTree<T> * quad = new QuadTree<T>(Vector2f((float)(WIDTH)/2, (float)(HEIGHT)/2), Vector2f((float)(WIDTH)/2, (float)(HEIGHT)/2), 4);
        
        // adding balls to the quad tree, checking collisions, checking board and moving them
        for(int i = 0; i<objects.size(); i++){
            objects[i]->shape.setFillColor(objects[i]->color);
            quad->add_ball(objects[i]);
            quad->collision_detection(objects[i]);
            objects[i]->checkBoard();
            objects[i]->move();
        }

        // if mouse left click, we add a ball that have a center of the mouse coordinates
        if(Mouse::isButtonPressed(Mouse::Left) && to_detect_mouse_click >= 20){
            Vector2i mouse_position = Mouse::getPosition(window);
            if(mouse_position.x <= WIDTH - radius_of_the_ball && mouse_position.x >= radius_of_the_ball && mouse_position.y <= HEIGHT - radius_of_the_ball && mouse_position.y >= radius_of_the_ball){
                int r = 0, g = 0, b = 0;
                while(r <= 10 && g <= 0 && b <= 0){
                    r = rand()%255;
                    g = rand()%255;
                    b = rand()%255;
                }
                T * ball = new T(radius_of_the_ball, 1.0, (float)mouse_position.x, (float)mouse_position.y, 0.0, 1.0, Color(r, g, b));
                ball->setCenterPosition((float)mouse_position.x, (float)mouse_position.y);
                quad->add_ball(ball);
                objects.push_back(ball);
            }
            to_detect_mouse_click = 0;
        }
        Event event;
        
        while(window.pollEvent(event)){

            if(event.type == Event::Closed){
                window.close();
            }
        }
        
        window.clear();
        // drawing the balls who are in the quad tree
        draw_quad_tree<T>(window, quad, NULL, DrawGrid);
        window.display();
        destroy_quad_tree<T>(quad); // destroying quad tree, because every loop it changes
        to_detect_mouse_click++;
    }
    destroy_ball_array<T>(objects, objects.size()); // destroying all the balls we added
}


//---------------------------------------------------------

// Second function for rotation and infinity symbol
void Rotation(RenderWindow &window, int mode){
    Circle_Equation* circle = new Circle_Equation(50.0, 2, Vector2f((float)WIDTH/2, (float)HEIGHT/2), 6, mode);

    while(window.isOpen()){
        circle->play();
        
        Event event;
        
        while(window.pollEvent(event)){

            if(event.type == Event::Closed){
                window.close();
            }
        }
        
        window.clear();
        circle->draw(window);
        window.display();
    }
}

template void Balls_Physic_Simulation<Ball>(RenderWindow &window, int DrawGrid);
template void Balls_Physic_Simulation<Particle>(RenderWindow &window, int DrawGrid);