//abstract class
class Line;
class Ball;

class Shape {
protected:
    Vector2 pos_;
    Vector2 velocity_;
    std::string color_; // mess with the color later
    bool moveable_;

public:
    Shape(Vector2 pos) : pos_{pos} , velocity_{0, 0}, color_{"red"}, moveable_{false} {}
    Shape(Vector2 pos, Vector2 velocity) : pos_{pos} , velocity_{velocity}, color_{"red"}, moveable_{true} {}
    virtual ~Shape() = default;

    // move based on velocity
    virtual void setVelo(const Vector2& velocity){velocity_ = velocity;}
    virtual void setPos(const Vector2& pos){pos_ = pos;}
    virtual void moveToVelo(float deltaTime){pos_ += velocity_*deltaTime;}
    virtual void setColor(std::string color){color_ = color;}
    virtual void setColor(bool moveable){moveable_ = moveable;}
    virtual Vector2 const getPos(){return pos_;}
    virtual Vector2 const getVelo(){return velocity_;}
    virtual bool const getMoveability(){return moveable_;}

    virtual void draw(SDL_Renderer* renderer) const = 0;

    virtual void checkForWindowCollision(int, int){};
    virtual void checkForCollisionLine(Line& line) = 0;
    virtual void checkForCollisionBall(Ball& ball) = 0;
    virtual void checkForCollision(Shape& shape) = 0;

};