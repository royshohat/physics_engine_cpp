class Line;
class Rectangle;
class Shape;

class Ball : public Shape {
    double radius_;
    bool filled_;

public:
    Ball(Vector2 pos, double radius, bool filled)
    : Shape(pos, {0, 0}),  radius_{radius}, filled_ {filled} {}

    Ball(Vector2 pos, double radius)
    : Shape(pos, {0, 0}),  radius_{radius}, filled_ {true} {}

    Ball(Vector2 pos, Vector2 velocity, double radius)
    : Shape(pos, velocity),  radius_{radius}, filled_ {true} {}


    void draw(SDL_Renderer* renderer) const override;
    double const getRadius(){return radius_;}
    void setFilled(bool filled) {filled_ = filled;}
    //void checkForCollision (Line line) override;
    //void checkForCollision(double m, double b, bool skip) override;
    //void checkForCollision(Rectangle rect) override;
    void checkForCollision(Ball& circle) override;
    void checkForWindowCollision(int windowHeight, int windowWidth);

};
