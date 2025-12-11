class Line;
class Shape;

class Ball : public Shape {
    double radius_;
    bool filled_;

public:
    Ball(Vector2 pos, double radius, bool filled)
    : Shape(pos, {0, 0}),  radius_{radius}, filled_ {filled} {}

    Ball(Vector2 pos, double radius)
    : Shape(pos),  radius_{radius}, filled_ {true} {}

    Ball(Vector2 pos, Vector2 velocity, double radius)
    : Shape(pos, velocity),  radius_{radius}, filled_ {true} {}


    void draw(SDL_Renderer* renderer) const override;
    double const getRadius(){return radius_;}
    void setFilled(bool filled) {filled_ = filled;}
    void checkForWindowCollision(int windowHeight, int windowWidth) override;

    void checkForCollisionLine(Line& line) override;
    void checkForCollisionBall(Ball& circle) override;
    void checkForCollision(Shape& shape) override {shape.checkForCollisionBall(*this); }

};
