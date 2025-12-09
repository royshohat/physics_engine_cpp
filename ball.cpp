#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
#include <string>

#include "vector2.h"
#include "shape.h"
#include "line.h"
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


void Ball::checkForCollisionLine(Line& line){
    //calculate the dstance between the ball and the line
    Vector2 centToPos = pos_ - line.getPos();
    Vector2 Pos2ToPos = line.getPos2() - line.getPos();

    double d = std::abs(centToPos.x * Pos2ToPos.y - centToPos.y * Pos2ToPos.x)/std::sqrt(Pos2ToPos.magnitudeSq());
    
    if (d>radius_) return;

    Vector2 normal{-Pos2ToPos.y, Pos2ToPos.x};
    //Vector2 normal(Pos2ToPos.y, -Pos2ToPos.x);

    normal = normalize(normal);
    velocity_ = velocity_ - normal*normal*velocity_*2;

    
}

void Ball::checkForWindowCollision(int windowWidth, int windowHeight){
    if(pos_.x > windowWidth - radius_){
        if (velocity_.x > 0) velocity_.x *= -0.4;        
    }
    if(pos_.x < radius_){
        if (velocity_.x < 0) velocity_.x *= -0.4;        
    }
    if(pos_.y > windowHeight - radius_){
        if (velocity_.y > 0) velocity_.y *= -0.4;        
    }
    if(pos_.y < radius_){
        if (velocity_.y < 0) velocity_.y *= -0.4;        
    }


    //if(pos_.y>windowHeight - radius_ || pos_.y < radius_)
        //velocity_.y *= -1;        
    
}


void Ball::checkForCollisionBall(Ball& other_ball){
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
        if(!other_ball.getMoveability()){
            pos_ += correc*2;
            return;
        }
        pos_ += correc; 
        Vector2 otherCorrec = other_ball.getPos() - correc;
        //if(other_ball.getMoveability()) other_ball.setPos(other_ball.getPos() - correc);
        other_ball.setPos(other_ball.getPos() - correc);


        // resolution

        double v1n_scalar = dot(velocity_, n_hat);
        double v2n_scalar = dot(other_ball.getVelo(), n_hat); 

        Vector2 v1n = n_hat * v1n_scalar;
        Vector2 v2n = n_hat * v2n_scalar ;
        
        Vector2 v1t = velocity_ - v1n;
        Vector2 v2t = other_ball.getVelo() - v2n;

        velocity_ = v2n + v1t; 
        if(!other_ball.getMoveability()) return;
        auto other_velocity = v1n + v2t;

        other_ball.setVelo(other_velocity);
    }
}
//void Ball::checkForCollision(Rectangle rect){
    //// TODO: complete this func
    //return;
//}
