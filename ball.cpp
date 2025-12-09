#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
#include <string>

#include "vector2.h"
#include "shape.h"
//#include "line.h"
#include "ball.h"
//#include "rectangle.h"

// Standalone Dot Product
double dot(const Vector2& a, const Vector2& b) {
    return a.x * b.x + a.y * b.y;
}

// Standalone Normalization (returns unit vector)
Vector2 normalize(const Vector2& v) {
    double mag = std::sqrt(v.magnitudeSq());
    return {v.x / mag, v.y / mag};
}

void Ball::draw(SDL_Renderer* renderer) const{
    if (filled_){
        for(int i=-radius_; i!=radius_; i+=1){
            // calculation the y for the x
            double x_val = std::round(std::sqrt(radius_*radius_ - i*i));

            for (int j=-x_val; j!=x_val; ++j){
                SDL_RenderDrawPoint(renderer, j+pos_.x, i+pos_.y);
                SDL_RenderDrawPoint(renderer, j+pos_.x, i+pos_.y);
            }

        }
    }
    else{
        // after multiple tries this was the simplest
        // and one of the best preformence wise
        
        // the problem was that some x's had multiple y's cause there ints 
        // so  just ran on both 

        for(double i=-radius_; i<=radius_; i+=1){
            // calculaiton the y for the x and the x for the y
            double y_val = std::round(std::sqrt(radius_*radius_ - i*i));
            double x_val = std::round(std::sqrt(radius_*radius_ - i*i));
            SDL_RenderDrawPoint(renderer, i+pos_.x, y_val+pos_.y);
            SDL_RenderDrawPoint(renderer, i+pos_.x, -y_val+pos_.y);

            SDL_RenderDrawPoint(renderer, x_val+pos_.x, i+pos_.y);
            SDL_RenderDrawPoint(renderer, -x_val+pos_.x, i+pos_.y);
        }
    }
}

//void Ball::checkForCollision(double m, double b, bool skip){
        //// fnding the distance between the center of the ball to the lne
        //double d = std::abs(-m * pos_.x + pos_.y - b) / 
                            //std::sqrt(m*m + 1);

        ////std::cout << '(' << ", " << b << ')' << std::endl;

        //if (d <= radius_ || skip) {


            //// finding the normal
            //double Nx = m/std::sqrt(m*m + 1);
            //double Ny = -1/std::sqrt(m*m + 1);

            //// finding the penetration amount 

            ////double pen =  - d;


            ////x_ += Nx * pen;
            ////y_ += Ny * pen;
            ////std::cout << "x_: " << x_ << std::endl;
            ////std::cout << "y_: " << y_ << std::endl;
            ////std::cout << "pen: " << pen << std::endl;
            ////std::cout << "Nx: " << Nx << std::endl;
            ////std::cout << "Ny: " << Ny << std::endl;



            //// calc the dot product
            //double dotProduct = vel_x_ * Nx
                              //+ vel_y_ * Ny;

            //vel_x_ = vel_x_ - 2*dotProduct*Nx;
            //vel_y_ = vel_y_ - 2*dotProduct*Ny;
        //}
//}

//void Ball::checkForCollision(Line line){
    //// calculate the dstance between the ball and the line
    
//}

void Ball::checkForWindowCollision(int windowHeight, int windowWidth){
    if(pos_.x > windowWidth - radius_){
        if (velocity_.x > 0) velocity_.x *= -1;        
    }
    if(pos_.x < radius_){
        if (velocity_.x < 0) velocity_.x *= -1;        
    }
    if(pos_.y > windowHeight - radius_){
        if (velocity_.y < 0) velocity_.y *= -1;        
    }
    if(pos_.y < radius_){
        if (velocity_.y > 0) velocity_.y *= -1;        
    }


    if(pos_.y>windowHeight - radius_ || pos_.y < radius_)
        velocity_.y *= -1;        
    
}


void Ball::checkForCollision(Ball& other_ball){
    // calculate the dstance between both centers
    double d = std::sqrt((other_ball.getPos().x - pos_.x) * (other_ball.getPos().x - pos_.x)
                        + (other_ball.getPos().y - pos_.y) * (other_ball.getPos().y - pos_.y));


    //if((d >= other_ball.getRadius() - radius_ && d <= other_ball.getRadius() + radius_)
        //|| d <= other_ball.getRadius() + radius_ && d >= other_ball.getRadius() - radius_ ){

    if(d >= other_ball.getRadius() - radius_ && d <= other_ball.getRadius() + radius_){
        
        Vector2 normal = pos_ - other_ball.getPos();

        Vector2 n_hat = normalize(normal);

        // pos correction
        auto radii_dif = radius_ + other_ball.getRadius() - d;
        
        Vector2 correc = n_hat * (radii_dif/2);
        pos_ += correc;

        Vector2 otherCorrec = other_ball.getPos() - correc;
        other_ball.setPos(other_ball.getPos() - correc);



        // resolution

        double v1n_scalar = dot(velocity_, n_hat);
        double v2n_scalar = dot(other_ball.getVelo(), n_hat); 

        Vector2 v1n = n_hat * v1n_scalar;
        Vector2 v2n = n_hat * v2n_scalar ;
        
        Vector2 v1t = velocity_ - v1n;
        Vector2 v2t = other_ball.getVelo() - v2n;

        velocity_ = v2n + v1t; 
        auto other_velocity = v1n + v2t;

        other_ball.setVelo(other_velocity);
    }
}
//void Ball::checkForCollision(Rectangle rect){
    //// TODO: complete this func
    //return;
//}
