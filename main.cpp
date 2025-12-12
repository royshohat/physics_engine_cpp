#include <iostream>
#include <chrono>
#include <SDL2/SDL.h>
#include <vector>
#include <memory>

#include "vector2.h"
#include "shape.h"
#include "line.h"
#include "ball.h"
#include "rope.h"

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;

#define BALLS_AMOUNT 25

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

    Rope rope(Vector2{100, 500}, 50, 15.0f, true);
    
    for (auto i=0; i!=std::sqrt(BALLS_AMOUNT); ++i){
        for (auto j=0; j!=std::sqrt(BALLS_AMOUNT); ++j){

            objs.push_back(std::make_unique<Ball>(Vector2{static_cast<double>(200+i*40), static_cast<double>(100+j*40)}, Vector2{50, 0}, 20));
        }
    }

    //objs.push_back(std::make_unique<Line>(Vector2{0, WINDOW_HEIGHT/2}, Vector2{WINDOW_WIDTH/2, WINDOW_HEIGHT}));
    //objs.push_back(std::make_unique<Line>(Vector2{WINDOW_WIDTH, WINDOW_HEIGHT/2}, Vector2{WINDOW_WIDTH/2, WINDOW_HEIGHT}));


    

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
        rope.draw(renderer);

        SDL_RenderPresent(renderer);



        auto elapsed = Clock::now() - start_time;
        auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(elapsed);

        
        // this makes even faster/smaller balls not to tunnel through walls/other balls

        const int SUB_STEPS = 4;
        double step_dt = elapsed_seconds.count() / SUB_STEPS;
        
        
        for (int s = 0; s != SUB_STEPS; ++s){
            moveObjsToVelocity(objs, static_cast<float>(step_dt));
            checkForEveryCollision(objs);

            rope.update(step_dt);
            for (auto& obj : objs) {
                Ball* ball = dynamic_cast<Ball*>(obj.get());
                if (!ball) continue; 
                rope.checkCollisionWithBall(*ball);
            }
        }
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
        if(!obj->getMoveability()) continue;
        obj->setVelo(Vector2{obj->getVelo().x, obj->getVelo().y+100*elapsed_time});
        obj->moveToVelo(elapsed_time);
    }
}

void checkForEveryCollision(std::vector<std::unique_ptr<Shape>>& objects){
    for(auto i=0; i!=objects.size(); ++i){
        if(!objects[i]->getMoveability()) continue;
        objects[i]->checkForWindowCollision(WINDOW_WIDTH, WINDOW_HEIGHT);
        for(auto j=i+1; j!=objects.size(); ++j){
            objects[j]->checkForCollision(*objects[i]);
        }
    }
}
