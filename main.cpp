#include <iostream>
#include <chrono>
#include <thread>

#include "shape.h"
#include "rectangle.h"

using Clock = std::chrono::steady_clock;

int main(){
    Rectangle re(10, 10, 30, 30);
    re.setVelo(5, 5); // pixel/s

    while(1){
        auto start_time = Clock::now();

        std::chrono::milliseconds duration(30);

        std::this_thread::sleep_for(duration);




        auto elapsed = Clock::now() - start_time;
        auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(elapsed);

        re.moveVelo(elapsed_seconds.count());
        std::cout << '(' << re.getX() << ", " << re.getY() << ')' << std::endl;
        //std::cout << elapsed_seconds.count() << std::endl;        

    }

    return 0;

}

