#include <iostream>
#include <chrono>
#include <SDL2/SDL.h>
#include <vector>
#include <memory>

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



    std::vector<std::unique_ptr<Shape>> objects;
    objects.push_back(std::make_unique<Ball>(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 250, false));
    for(int i=0; i!=5; ++i){
        for(int j=0; j!=5; j++){
            objects.push_back(std::make_unique<Ball>(250+i*30, 250+j*30, 10));
            objects[i*5 + j+1]->setVelo(25, 25);
            
        }
    }


    

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


        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
        objects[0]->draw(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
        for(int i=1; i!=26; ++i){
            objects[i]->draw(renderer);
        }


        SDL_RenderPresent(renderer);



        for(int i=1; i!=26; ++i){
            objects[i]->setVelo(objects[i]->getVeloX(), objects[i]->getVeloY()+1); // move based on delta time

            for(int j=0; j!=26; ++j){
                if(j==i) continue;
                objects[i]->checkForCollision(static_cast<Ball*>(objects[j].get()));
            }
        }


        auto elapsed = Clock::now() - start_time;
        auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(elapsed);

        for(int i=1; i!=26; ++i){
            objects[i]->moveToVelo(elapsed_seconds.count()); // move based on delta time
        }
    }

    
    // cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}

