class Line;
class Rectangle;
class Shape;

class Ball : public Shape {
    double radius_;
    bool filled_;

public:
    Ball(double x, double y, double radius, bool filled)
    : Shape(x, y),  radius_{radius}, filled_ {filled} {}

    Ball(double x, double y, double radius)
    : Shape(x, y),  radius_{radius}, filled_ {true} {}

    void draw(SDL_Renderer* renderer) const override;
    double const getRadius(){return radius_;}
    void setFilled(bool filled) {filled_ = filled;}
    void checkForCollision (Line line) override;
    void checkForCollision(double m, double b, bool skip) override;
    void checkForCollision(Rectangle rect) override;
    void checkForCollision(Ball circle) override;
    void checkForWindowCollision(int windowHeight, int windowWidth);

};
