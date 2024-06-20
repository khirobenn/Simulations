#ifndef __BALLS__CLASS__
#define __BALLS__CLASS__

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <deque>

#define WIDTH 800
#define HEIGHT 600
#define dt 0.2 // delta time used in simulation of balls

using namespace sf;


class Ball{
    protected:
        float radius;
        float mass;

        float force_x;
        float force_y;

        float acceleration_x;
        float acceleration_y;

        float current_x; 
        float current_y;

        float previous_x;
        float previous_y;


    public:
        CircleShape shape;
        Color color;

        Ball(float radius, float mass, float current_x, float current_y, float force_x, float force_y, Color color);

        static void collision_effect(Ball* ball1, Ball* ball2, float overlap, Vector2f normal);

        void setCenterPosition(float x, float y);

        void checkBoard();

        void move();
        
        void add_overlap_to_current_position(float dx, float dy);
};

class Particle : public Ball {
    public:
        Particle(float, float, float x, float y, float , float, Color) : Ball(5.0, 1.0, x, y, 0, 0, Color::Blue){};
        void move();
        static void collision_effect(Particle* ball1, Particle* ball2, float overlap, Vector2f normal);
};

#endif