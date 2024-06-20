#include "quad.h"

template <class T>
QuadTree <T> ::QuadTree(Vector2f center, Vector2f width_and_height, const int size){
    this->center.x = center.x;
    this->center.y = center.y;
    this->half_w_h.x = width_and_height.x;
    this->half_w_h.y = width_and_height.y;

    this->ne = NULL;
    this->nw = NULL;
    this->se = NULL;
    this->sw = NULL;


    this->isDivided = false;
    this->size = size;
}

// check if a ball is inside a quad tree
template <class T>
bool QuadTree <T> ::intersect(T* ball, Vector2f center, Vector2f half_w_h){
    Vector2f ball_position = ball->shape.getPosition();
    return !(ball_position.x >= center.x + half_w_h.x 
    || ball_position.x <= center.x - half_w_h.x
    || ball_position.y >= center.y + half_w_h.y 
    || ball_position.y <= center.y - half_w_h.y);
}

// adds a ball to a quad tree or in his childs if it's full
template <class T>
void QuadTree <T> ::add_ball(T* ball){
    if(this->array.size() < size && this->intersect(ball, this->center, this->half_w_h)){this->array.push_back(ball); return;}
    else if(!this->intersect(ball, this->center, this->half_w_h)) return ;
    else if (!this->isDivided){

        this->ne = new QuadTree(Vector2f(this->center.x + this->half_w_h.x/2, this->center.y - this->half_w_h.y/2), Vector2f(this->half_w_h.x/2, this->half_w_h.y/2), this->size);

        this->nw = new QuadTree(Vector2f(this->center.x - this->half_w_h.x/2, this->center.y - this->half_w_h.y/2), Vector2f(this->half_w_h.x/2, this->half_w_h.y/2), this->size);

        this->se = new QuadTree(Vector2f(this->center.x + this->half_w_h.x/2, this->center.y + this->half_w_h.y/2), Vector2f(this->half_w_h.x/2, this->half_w_h.y/2), this->size);

        this->sw = new QuadTree(Vector2f(this->center.x - this->half_w_h.x/2, this->center.y + this->half_w_h.y/2), Vector2f(this->half_w_h.x/2, this->half_w_h.y/2), this->size);

        this->isDivided = true;
    }

    this->ne->add_ball(ball);
    this->nw->add_ball(ball);
    this->se->add_ball(ball);
    this->sw->add_ball(ball);
}


template <class T>
QuadTree<T> * QuadTree <T> ::get_child(int i){
    if(i == 1) return this->ne;
    if(i == 2) return this->nw;
    if(i == 3) return this->se;
    if(i == 4) return this->sw;
    return NULL;
}

template <class T>
Vector2f QuadTree <T> ::get_center(){ return this->center;}

template <class T>
Vector2f QuadTree <T> ::get_half_w_h(){ return this->half_w_h;}


// check collision between two balls; if they collide we move through the normal vector by overlap/2
template <class T> void QuadTree <T> ::check_collision_and_update(T* ball1, T* ball2){
    const float spaceBetween = 0;

    Vector2f pos_a = ball1->shape.getPosition();
    Vector2f pos_b = ball2->shape.getPosition();

    pos_a.x += ball1->shape.getRadius();
    pos_a.y += ball1->shape.getRadius();

    pos_b.x += ball2->shape.getRadius();
    pos_b.y += ball2->shape.getRadius();

    if ((pos_a.x - pos_b.x)*(pos_a.x - pos_b.x) + (pos_a.y - pos_b.y)*(pos_a.y - pos_b.y) <= (ball1->shape.getRadius() + ball2->shape.getRadius() + spaceBetween) * (ball1->shape.getRadius() + ball2->shape.getRadius() + spaceBetween)){
        float overlap = ball1->shape.getRadius() + ball2->shape.getRadius() + spaceBetween - sqrt((pos_a.x - pos_b.x)*(pos_a.x - pos_b.x) + (pos_a.y - pos_b.y)*(pos_a.y - pos_b.y));

        Vector2f normal;

        normal.x = pos_b.x - pos_a.x;
        normal.y = pos_b.y - pos_a.y;


        if(normal.x < 0) normal.x = -1;
        else if(normal.x > 0) normal.x = 1;
        else normal.x = 0;

        if(normal.y < 0) normal.y = -1;
        else if(normal.y > 0) normal.y = 1;
        else normal.y = 0;

        T::collision_effect(ball1, ball2, overlap, Vector2f(normal.x, normal.y));
    }
}

// find nearest balls to ball and add them to the array 
template <class T>
void QuadTree <T> ::find_nearest_balls_to_ball(T* ball, struct Rectangle_collision_check & rect , deque <T*> &array){

    if(this->center.x + this->half_w_h.x < rect.center.x - rect.half_w_h.x
    || this->center.x - this->half_w_h.x > rect.center.x + rect.half_w_h.x
    || this->center.y + this->half_w_h.y < rect.center.y - rect.half_w_h.y
    || this->center.y - this->half_w_h.y > rect.center.y + rect.half_w_h.y) 
        return;

    for(int i = 0; i < this->array.size(); i++){
        if(this->array[i] != ball && this->intersect(this->array[i], rect.center, rect.half_w_h)){ 
            array.push_back(this->array[i]);
        }
    }

    if(this->isDivided){
        this->ne->find_nearest_balls_to_ball(ball, rect, array);
        this->nw->find_nearest_balls_to_ball(ball, rect, array);
        this->se->find_nearest_balls_to_ball(ball, rect, array);
        this->sw->find_nearest_balls_to_ball(ball, rect, array);
    }
}


// we find nearest balls to ball and check for everyone of them if they collide with ball
template <class T>
void QuadTree <T> ::collision_detection(T* ball){

    struct Rectangle_collision_check rect;

    rect.center = Vector2f(ball->shape.getPosition().x + ball->shape.getRadius(), ball->shape.getPosition().y + ball->shape.getRadius());
    rect.half_w_h = Vector2f(3*ball->shape.getRadius() + 0.5, 3*ball->shape.getRadius() + 0.5);

    deque <T*> balls_collided_with;

    this->find_nearest_balls_to_ball(ball, rect, balls_collided_with);

    for(int i = 0; i < balls_collided_with.size(); i++){
        this->check_collision_and_update(ball, balls_collided_with[i]);
    }
}

// we draw balls (we draw grid if (DrawGrid == 2))
template <class T> void draw_quad_tree(RenderWindow &window, QuadTree<T> * quad, Color *colors, int DrawGrid){
    if(quad == NULL) return;

    if(DrawGrid == 2){
        RectangleShape shape;
        Vector2f center = quad->get_center();
        Vector2f half_w_h = quad->get_half_w_h();
        shape.setSize(Vector2f (2* half_w_h.x, 2* half_w_h.y));
        shape.setPosition(Vector2f(center.x - half_w_h.x, center.y - half_w_h.y));
        shape.setFillColor(Color::Transparent);
        shape.setOutlineColor(Color::Green);
        shape.setOutlineThickness(0.5);
        window.draw(shape);
    }
    
    for(int i=0; i < quad->array.size(); i++){
        window.draw(quad->array[i]->shape);
    }

    draw_quad_tree(window, quad->get_child(1), colors, DrawGrid);
    draw_quad_tree(window, quad->get_child(2), colors, DrawGrid);
    draw_quad_tree(window, quad->get_child(3), colors, DrawGrid);
    draw_quad_tree(window, quad->get_child(4), colors, DrawGrid);
}


template <class T> void draw_all(RenderWindow &window, QuadTree<T> * quad, Color *colors, int DrawGrid){
    draw_quad_tree(window, quad, colors, DrawGrid);
}

template <class T> int destroy_quad_tree(QuadTree<T> * quad){
    if(quad == NULL){
        delete quad;
        return 0;
    }
    int n1 = destroy_quad_tree(quad->get_child(1));
    int n2 = destroy_quad_tree(quad->get_child(2));
    int n3 = destroy_quad_tree(quad->get_child(3));
    int n4 = destroy_quad_tree(quad->get_child(4));

    delete quad;

    return 1 + n1 + n2 + n3 + n4; // number of quad_tree nodes
}

template <class T> void destroy_ball_array(deque <T*> balls, const int size){
    for(int i = 0; i < size; i++){
        delete balls[i];
    }
}


void change_color(struct RGB &rgb){
    if(rgb.R == 255 && rgb.G == COLOR_MIN && rgb.B < 255){
        rgb.B++;
    }
    else if(rgb.R > COLOR_MIN && rgb.B == 255 && rgb.G == COLOR_MIN )
    {
        rgb.R--;
    }
    else if(rgb.R == COLOR_MIN && rgb.B == 255 && rgb.G < 255)
    {
        rgb.G++;
    }
    else if(rgb.R == COLOR_MIN && rgb.G == 255 && rgb.B > COLOR_MIN){
        rgb.B--;
    }
    else if(rgb.R < 255 && rgb.G == 255 && rgb.B == COLOR_MIN){
        rgb.R++;
    }
    else if(rgb.R == 255 && rgb.B == COLOR_MIN && rgb.G > COLOR_MIN){
        rgb.G--;
    }
}

// To avoid link problem with template classes and functions
template class QuadTree<Ball>;
template class QuadTree<Particle>;

template void draw_quad_tree<Ball>(RenderWindow &window, QuadTree<Ball> * quad, Color *colors, int DrawGrid);
template void draw_quad_tree<Particle>(RenderWindow &window, QuadTree<Particle> * quad, Color *colors, int DrawGrid);

template void draw_all<Ball>(RenderWindow &window, QuadTree<Ball> * quad, Color *colors, int DrawGrid);
template void draw_all<Particle>(RenderWindow &window, QuadTree<Particle> * quad, Color *colors, int DrawGrid);

template int destroy_quad_tree<Ball>(QuadTree<Ball> * quad);
template int destroy_quad_tree<Particle>(QuadTree<Particle> * quad);

template void destroy_ball_array<Ball>(deque <Ball*> balls, const int size);
template void destroy_ball_array<Particle>(deque <Particle*> balls, const int size);