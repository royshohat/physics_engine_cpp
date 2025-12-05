#include <iostream>
#include <chrono>
#include <SDL2/SDL.h>

#include "shape.h"
#include "line.h"
#include "ball.h"
#include "rectangle.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

using Clock = std::chrono::steady_clock;

int main(){

    if (SDL_Init(SDL_INIT_VIDEO) !=0){ // init sdl 
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("window!!", 
                                           SDL_WINDOWPOS_CENTERED, 
                                           SDL_WINDOWPOS_CENTERED, 
                                           WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 

    //Rectangle re(10, 10, 30, 30);
    //re.setVelo(25, 25); // pixel/s

    Ball ball(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 30);
    ball.setVelo(30, 0);

    //Line line(300, 800, 800, 300);

    Ball circle(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 250, false);

    bool running = true;
    SDL_Event event;

    while(running){
        auto start_time = Clock::now();

        while (SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
        SDL_RenderClear(renderer);

        // draw the ball
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
        ball.draw(renderer);

        // draw a line
        //SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); 
        //line.draw(renderer);

        // draw a circle
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
        circle.draw(renderer);
        


        SDL_RenderPresent(renderer);




        auto elapsed = Clock::now() - start_time;
        auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(elapsed);

        ball.moveToVelo(elapsed_seconds.count()); // move based on delta time
        ball.setVelo(ball.getVeloX(), ball.getVeloY()+1);

        //ball.checkForLineCollision(line);
        ball.checkForWindowCollision(WINDOW_WIDTH, WINDOW_HEIGHT);
        ball.checkForInsideCircleCollision(circle);

    }

    // cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}

