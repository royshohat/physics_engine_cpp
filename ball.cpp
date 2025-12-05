#include <SDL2/SDL.h>
#include <cmath>
#include <string>

#include "shape.h"
#include "line.h"
#include "ball.h"


void Ball::draw(SDL_Renderer* renderer) const{
    if (filled_){
        for(int i=-radius_; i!=radius_; i+=1){
            // calculation the y for the x
            double x_val = std::round(std::sqrt(radius_*radius_ - i*i));

            for (int j=-x_val; j!=x_val; ++j){
                SDL_RenderDrawPoint(renderer, j+x_, i+y_);
                SDL_RenderDrawPoint(renderer, j+x_, i+y_);
            }

        }
    }
    else{
        // after mutiple tries this was the simplest
        // and one of the best preformence wise
        
        // the problem was that some x's had multiple y's cause there ints 
        // so i just ran on both 

        for(double i=-radius_; i<=radius_; i+=1){
            // calculation the y for the x and the x for the y
            double y_val = std::round(std::sqrt(radius_*radius_ - i*i));
            double x_val = std::round(std::sqrt(radius_*radius_ - i*i));
            SDL_RenderDrawPoint(renderer, i+x_, y_val+y_);
            SDL_RenderDrawPoint(renderer, i+x_, -y_val+y_);

            SDL_RenderDrawPoint(renderer, x_val+x_, i+y_);
            SDL_RenderDrawPoint(renderer, -x_val+x_, i+y_);
        }
    }
}

void Ball::checkForLineCollision(double m, double b, bool skip){
        // finding the distance between the center of the ball to the lne
        double d = std::abs(-m * x_ + y_ - b) / 
                            std::sqrt(m*m + 1);

        if (d <= radius_ || skip) {
            // finding the normal
            double Nx = m/std::sqrt(m*m + 1);
            double Ny = -1/std::sqrt(m*m + 1);

            // calc the dot product
            double dotProduct = vel_x_ * Nx
                              + vel_y_ * Ny;

            vel_x_ = vel_x_ - 2*dotProduct*Nx;
            vel_y_ = vel_y_ - 2*dotProduct*Ny;
        }
}

void Ball::checkForLineCollision(Line line){
        // calculate the distance between the ball and the line
        double m = (line.getY()-line.getY2()) / (line.getX() - line.getX2());
        double b = line.getY() - m*line.getX();
        this->checkForLineCollision(m, b, false);
}

void Ball::checkForWindowCollision(int windowHeight, int windowWidth){
    if(x_>windowWidth - radius_ || x_ < radius_)
        vel_x_ = -vel_x_;
    
    if(y_>windowHeight - radius_ || y_ < radius_)
        vel_y_ = -vel_y_;
    
}


void Ball::checkForInsideCircleCollision(Ball circle){
    // calculate the distance between both centers
    double d = std::sqrt((circle.getX() - x_) * (circle.getX() - x_)
                        + (circle.getY() - y_) * (circle.getY() - y_));
    if(d >= circle.getRadius() - radius_){
         double m = (circle.getY() - y_) / (circle.getX() - x_);
         double b = y_ - m*x_;
         double firstPart = std::sqrt((1+m*m)*circle.getRadius()*circle.getRadius() - b*b);

         if (x_ < circle.getX()) firstPart = -firstPart;
         
        double x = (-m * b + firstPart) / (1+m*m);
        double y = m*x + b;

        double derivativeM = -1/m; 
        double derivativeB = y - derivativeM*x;
        this->checkForLineCollision(derivativeM, derivativeB, true);

    }
}