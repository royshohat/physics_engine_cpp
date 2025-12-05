class Ball : public Shape {
    double radius_;
    bool filled_;

public:
    Ball(double x, double y, double radius, bool filled)
    : Shape(x, y),  radius_{radius}, filled_ {filled} {}

    Ball(double x, double y, double radius)
    : Shape(x, y),  radius_{radius}, filled_ {true} {}

    void draw(SDL_Renderer* renderer) const;
    double const getRadius(){return radius_;}
    void setFilled(bool filled) {filled_ = filled;}
    void checkForLineCollision(Line line);
    void checkForLineCollision(double m, double b, bool skip);
    void checkForCircleCollision(Ball circle);
    void checkForWindowCollision(int windowHeight, int windowWidth);

};
