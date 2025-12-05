#include <SDL2/SDL.h>
#include <cmath>
#include <string>

#include "shape.h"
#include "line.h"
#include "ball.h"


void Ball::draw(SDL_Renderer* renderer) const{
    for(int i=-radius_; i!=radius_; i+=1){
            // calculation the y for the x
            double x_val = std::round(std::sqrt(radius_*radius_ - i*i));

            for (int j=-x_val; j!=x_val; ++j){
                SDL_RenderDrawPoint(renderer, j+x_, i+y_);
                SDL_RenderDrawPoint(renderer, j+x_, i+y_);
            }

        }
}


void Ball::checkForLineCollision(Line line){
        // calculate the distance between the ball and the line
        double m = (line.getY()-line.getY2()) / (line.getX() - line.getX2());
        double b = line.getY() - m*line.getX();

        // finding the distance between the center of the ball to the lne
        double d = std::abs(-m * x_ + y_ - b) / 
                            std::sqrt(m*m + 1);

        if (d <= radius_) {
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

void Ball::checkForWindowCollision(int windowHeight, int windowWidth){
    if(x_>windowWidth - radius_ || x_ < radius_)
        vel_x_ = -vel_x_;
    
    if(y_>windowHeight - radius_ || y_ < radius_)
        vel_y_ = -vel_y_;
    
}