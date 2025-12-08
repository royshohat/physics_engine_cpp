#include <iostream>
#include <chrono>
#include <SDL2/SDL.h>
#include <vector>
#include <memory>

#include "vector2.h"
#include "shape.h"
//#include "line.h"
#include "ball.h"
//#include "rectangle.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

#define BALLS_AMOUNT 36 

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



    //std::vector<std::unique_ptr<Shape>> objects;
    //objects.push_back(std::make_unique<Ball>(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 250, false));
    //for(int i=0; i!=2; ++i){
        //for(int j=0; j!=2; j++){
            //objects.push_back(std::make_unique<Ball>(250+i*30, 250+j*30, 10));
            //objects[i*2 + j+1]->setVelo(25, 25);
            
        //}
    //}

    std::vector<std::unique_ptr<Ball>> objs;
    for(int i=0; i!=(int)std::sqrt(BALLS_AMOUNT); ++i){
        for(int j=0; j!=(int)std::sqrt(BALLS_AMOUNT); ++j){
           objs.push_back(std::make_unique<Ball>(
            Vector2{static_cast<float>(i*30+30), static_cast<float>(j*30+30)}, 
            Vector2{480, 690}, 
            10
)); 
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



        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 

        for(auto i=0; i!=BALLS_AMOUNT; ++i){
            objs[i]->draw(renderer);
        }

        SDL_RenderPresent(renderer);



        //for(int i=1; i!=5; ++i){
            //objects[i]->setVelo(objects[i]->getVeloX(), objects[i]->getVeloY()+1); // move based on delta time

            //for(int j=0; j!=5; ++j){
                //if(j==i) continue;
                //objects[i]->checkForCollision(static_cast<Ball*>(objects[j].get()));
            //}
        //}

        for(auto i=0; i!=BALLS_AMOUNT-1; ++i){
            objs[i]->checkForWindowCollision(WINDOW_WIDTH, WINDOW_HEIGHT);
            for(auto j=i+1; j!=BALLS_AMOUNT; ++j){
                objs[i]->checkForCollision(*objs[j]);
            }
        }



        auto elapsed = Clock::now() - start_time;
        auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(elapsed);



        for(auto i=0; i!=BALLS_AMOUNT; ++i){
            objs[i]->moveToVelo(elapsed_seconds.count());
        }
        
        //ball1.moveToVelo(elapsed_seconds.count());
        //ball2.moveToVelo(elapsed_seconds.count());
        //for(int i=1; i!=5; ++i){
            //objects[i]->moveToVelo(elapsed_seconds.count()); // move based on delta time
        //}
    }

    
    // cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}

