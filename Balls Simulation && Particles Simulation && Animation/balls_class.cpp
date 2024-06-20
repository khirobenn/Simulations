#include "balls_class.h"

Ball::Ball(float radius, float mass, float current_x, float current_y, float force_x, float force_y, Color color){
    this->radius = radius;
    this->mass = mass;

    this->force_x = force_x;
    this->force_y = force_y;

    this->current_x = current_x;
    this->current_y = current_y;

    this->previous_x = current_x;
    this->previous_y = current_y;

    this->color = color;
    this->shape.setFillColor(this->color);

    this->shape.setRadius(this->radius);
}

void Ball::setCenterPosition(float x, float y){
    this->shape.setPosition(Vector2f(x - this->radius, y - this->radius));
}

void Ball::collision_effect(Ball* ball1, Ball* ball2, float overlap, Vector2f normal){
    ball1->add_overlap_to_current_position(-normal.x*overlap/2, -normal.y*overlap/2);
    ball2->add_overlap_to_current_position(normal.x*overlap/2, normal.y*overlap/2);
}


void Ball::checkBoard(){
    if(this->current_x - this->radius < 0){
        this->current_x = this->radius;
        this->previous_x = this->current_x + this->current_x - this->previous_x;
    }
    else if(this->current_x + this->radius >= WIDTH){
        this->current_x = WIDTH - this->radius;
        this->previous_x = this->current_x + this->current_x - this->previous_x;
    }

    if(this->current_y - this->radius < 0){
        this->current_y = this->radius;
        this->previous_y = this->current_y + this->current_y - this->previous_y;
    }
    else if(this->current_y + this->radius >= HEIGHT){
        this->current_y = HEIGHT - this->radius;
        this->previous_y = this->current_y + this->current_y - this->previous_y;
    }
}

void Ball::move(){
    float tmp_current_x = this->current_x;
    float tmp_current_y = this->current_y;

    this->acceleration_x = force_x/mass;
    this->acceleration_y = force_y/mass;

    this->current_x += this->current_x - this->previous_x + this->acceleration_x * dt * dt;
    this->current_y += this->current_y - this->previous_y + this->acceleration_y * dt *dt;

    this->previous_x = tmp_current_x;
    this->previous_y = tmp_current_y;


    this->setCenterPosition(this->current_x, this->current_y);
}

void Ball::add_overlap_to_current_position(float dx, float dy){
    this->current_x += dx;
    this->current_y += dy;
}

void Particle::move(){
    this->add_overlap_to_current_position(((float)rand()/RAND_MAX)*2 - 1, ((float)rand()/RAND_MAX)*2 - 1);
    this->setCenterPosition(this->current_x, this->current_y);
}

void Particle::collision_effect(Particle* ball1, Particle* ball2, float overlap, Vector2f normal){
    ball1->shape.setFillColor(Color::Red);
    ball2->shape.setFillColor(Color::Red);
}