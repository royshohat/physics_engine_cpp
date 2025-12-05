class Ball : public Shape {
    double radius_;

public:
    Ball(double x, double y, double radius) : Shape(x, y),  radius_{radius} {}
    void draw(SDL_Renderer* renderer) const;
    double const getRadius(){return radius_;}
    void checkForLineCollision(Line line);
    void checkForWindowCollision(int windowHeight, int windowWidth);

};
