#include "circle_equation.h"

Circle_Equation::Circle_Equation(float radius, float dx, Vector2f center, const int size, const int mode){
    // the mode is used to make a rotation simple or an infinity rotation
    this->mode = mode;
    this->radius = radius;
    this->dx = dx;
    this->center = center;
    this->direction_to_change_center = 1;
    this->to_change_center = 0;
    this->x = 0;
    this->set_y();
    this->max_size_of_balls = size;
    this->rgb = (struct RGB) {.R = 255, .G = COLOR_MIN, .B = rand()%(255-COLOR_MIN) + COLOR_MIN};
}


// After changing x, we set y 
void Circle_Equation::set_y(){
    float y = sqrt(this->radius*this->radius - this->x*this->x);
    if((this->dx > 0 && this->direction_to_change_center > 0) || (this->dx < 0 && this->direction_to_change_center < 0)) this->y = y;
    else this->y = -y;
}

// adding new ball to the balls array
void Circle_Equation::add_new_ball(){
    Ball *ball = new Ball(MOUSE_BALL_RADIUS, 1.0, -1, -1, 0.0, 0.0, Color::Blue);
    ball->setCenterPosition(this->center.x + this->x, this->center.y + this->y);
    if(this->x + this->center.x >= this->center.x + this->radius || this->x + this->center.x <= this->center.x - this->radius){
        if(this->mode != 0)
            this->to_change_center++;
        if(this->to_change_center == 2){
            this->to_change_center = 0;
            this->x = this->direction_to_change_center*this->radius;
            this->direction_to_change_center = -this->direction_to_change_center;
            this->center.x += this->direction_to_change_center*2*this->radius;
        }else
            this->dx = -this->dx; 
        
    }
    this->x += this->dx;
    this->set_y();

    this->balls.push_back(ball);
}

// we check the size of balls array, if it is greater than the max_size we delete the first element
void Circle_Equation::check_size_of_balls(){
    if(this->balls.size() > this->max_size_of_balls){
        delete this->balls[0];
        this->balls.pop_front();
    }
}


// we draw the balls in the array
void Circle_Equation::draw(RenderWindow &window){
    change_color(this->rgb);
    for(int i=0; i<this->balls.size(); i++){
        this->balls[i]->shape.setFillColor(Color(this->rgb.R, this->rgb.G , this->rgb.B , 255 - (this->balls.size() - i)*30));
        window.draw(this->balls[i]->shape);
    }
}

void Circle_Equation::play(){
    this->add_new_ball();
    this->check_size_of_balls();
}