#ifndef __QUAD__
#define __QUAD__

#include <time.h>
#include <cmath>
#include <iostream>
#include "balls_class.h"

using namespace std;


struct RGB{
    int R;
    int G;
    int B;
};

struct Rectangle_collision_check{
    Vector2f center;
    Vector2f half_w_h;
};


#define COLOR_MIN 84




template <class T> class QuadTree {
    private:

        Vector2f center;
        Vector2f half_w_h;

        QuadTree<T> * ne;
        QuadTree<T> * nw;
        QuadTree<T> * se;
        QuadTree<T> * sw;

        bool isDivided;
        int size;

    public:

        deque <T*> array;

        QuadTree(Vector2f center, Vector2f width_and_height, const int size);

        
        bool intersect(T* ball, Vector2f center, Vector2f half_w_h);

        void add_ball(T* ball);

        QuadTree<T> * get_child(int i);
        Vector2f get_center();
        Vector2f get_half_w_h();

        void check_collision_and_update(T* ball1, T* ball2);
        void find_nearest_balls_to_ball(T* ball, struct Rectangle_collision_check &rect, deque <T*> &array);
        void collision_detection(T* ball);

};
template <class T> void draw_quad_tree(RenderWindow &window, QuadTree<T> * quad, Color *colors, int DrawGrid);
template <class T> void draw_all(RenderWindow &window, QuadTree<T> * quad, Color *colors, int DrawGrid);
template <class T> int destroy_quad_tree(QuadTree<T> * quad);

template <class T> void destroy_ball_array(deque <T*> balls, const int size);

void change_color(struct RGB &rgb);

#endif