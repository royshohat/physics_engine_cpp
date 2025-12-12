#include <vector>
#include <memory>

struct Vector2;
class Shape;
class Ball;

struct Point { //using the varlet integration points 
    Vector2 pos, oldPos;
    bool locked = false;
};

struct Stick {
    Point* pA;
    Point* pB;
    float length;
};


class Rope {
    std::vector<Point> points;
    std::vector<Stick> sticks;

public:
    Rope(Vector2 startPos, int numSegments, float segmentLength, bool lockLast = false);
    void update(float dt);

    std::vector<Point>& getPoints(){return points; }
    std::vector<Stick>& getSticks(){return sticks; }

    void draw(SDL_Renderer* renderer) const;
    void checkCollisionWithBall(Ball& ball);
    
};
