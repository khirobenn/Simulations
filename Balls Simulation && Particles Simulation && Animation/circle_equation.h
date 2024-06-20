#ifndef __CIRCLE__EQUATION__
#define __CIRCLE__EQUATION__

#include "quad.h"

#define MOUSE_BALL_RADIUS 20.0f

class Circle_Equation{
    private:
        float radius; // radius of the circle
        float x; // x of a point in the circle
        float y; // y of a point in the circle
        float dx; // We don't need dy
        Vector2f center; // Center of the circle

        int mode;

        int to_change_center;
        int direction_to_change_center;

        deque <Ball *> balls;
        int max_size_of_balls;

        Vector2f distance_between_new_and_previous;

        struct RGB rgb;


        void set_y();
        void add_new_ball();
        void check_size_of_balls();

    public:

        Circle_Equation(float radius, float dx, Vector2f center, const int size, const int mode);
        void play();
        void draw(RenderWindow &window);

};

#endif