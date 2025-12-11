##  Simple Physics Engine: Rope and Line Interactions

This project implements a basic 2D physics engine in C++ focused on simulating the interactions between **rigid bodies (balls)** and **flexible constraints (ropes and lines)**.

###  Features

* **Particle-Based Simulation:** Treats balls as simple particles for movement and collision calculations.
* **Constraint Resolution:** Utilizes **Sequential Impulse** or **Position-Based Dynamics (PBD)** methods to model ropes and lines as distance constraints between particles. 
* **Collision Detection:** Simple collision handling for ball-to-ball and ball-to-boundary interactions.
* **Integration:** Employs the **Verlet Integration** scheme for stable and efficient time-stepping.
* **C++ Foundation:** Built using standard C++ libraries.

### Getting Started

#### Building

1.  Clone the repository:
    ```bash
    git clone https://github.com/royshohat/physics_engine_cpp.git
    cd physics_engine_cpp
    ```
2.  Compile the source files:
    ```bash
    g++ main.cpp ball.cpp rope.cpp -o physics_engine $(pkg-config --cflags --libs sdl2)
    ```

#### Running the Engine

Execute the compiled binary:
```bash
./physics_engine