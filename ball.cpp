#include <SDL2/SDL.h>
#include <cmath>
#include <string>

#include "shape.h"
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