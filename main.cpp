#include <iostream>
#include <chrono>
#include <SDL2/SDL.h>
#include <vector>
#include <memory>

#include "vector2.h"
#include "shape.h"
#include "line.h"
#include "ball.h"
//#include "rectangle.h"

const int WINDOW_WIDTH = 1800;
const int WINDOW_HEIGHT = 800;

#define BALLS_AMOUNT 400

using Clock = std::chrono::steady_clock;

void drawAllObjects(const std::vector<std::unique_ptr<Shape>>& objects, SDL_Renderer* renderer);
void moveObjsToVelocity(const std::vector<std::unique_ptr<Shape>>& objects, float elapsed_time);
void checkForEveryCollision(std::vector<std::unique_ptr<Shape>>& objects);

int main(){

    if (SDL_Init(SDL_INIT_VIDEO) !=0){ // init sdl 
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("window!!", 
                                           SDL_WINDOWPOS_CENTERED, 
                                           SDL_WINDOWPOS_CENTERED, 
                                           WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 


    std::vector<std::unique_ptr<Shape>> objs;
    for(int i=0; i!=(int)std::sqrt(BALLS_AMOUNT); ++i){
        for(int j=0; j!=(int)std::sqrt(BALLS_AMOUNT); ++j){
           objs.push_back(std::make_unique<Ball>(
            Vector2{static_cast<float>(i*20+100+j*2), static_cast<float>(j*20+100)}, 
            Vector2{0, 0}, 
            7
)); 
        }
    }
    //objs[0]->setVelo(Vector2{1040, 350});
    //objs.push_back(std::make_unique<Ball>(Vector2{1500, 500}, 200));


    

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

        drawAllObjects(objs, renderer);

        SDL_RenderPresent(renderer);



        checkForEveryCollision(objs);


        auto elapsed = Clock::now() - start_time;
        auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(elapsed);


        moveObjsToVelocity(objs, elapsed_seconds.count());
        
    }

    
    // cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}

void drawAllObjects(const std::vector<std::unique_ptr<Shape>>& objects, SDL_Renderer* renderer){
    for (const auto& obj : objects){
        obj->draw(renderer);
    }
}
void moveObjsToVelocity(const std::vector<std::unique_ptr<Shape>>& objects, float elapsed_time){
    for (const auto& obj : objects){
        if(!obj->getMoveability()) return;
        obj->setVelo(Vector2{obj->getVelo().x, obj->getVelo().y+100*elapsed_time});
        obj->moveToVelo(elapsed_time);
    }
}

void checkForEveryCollision(std::vector<std::unique_ptr<Shape>>& objects){
    for(auto i=0; i!=objects.size(); ++i){
        if(!objects[i]->getMoveability()) continue;
        objects[i]->checkForWindowCollision(WINDOW_WIDTH, WINDOW_HEIGHT);
        for(auto j=i+1; j!=objects.size(); ++j){
            objects[i]->checkForCollision(*objects[j]);
        }
    }
}
