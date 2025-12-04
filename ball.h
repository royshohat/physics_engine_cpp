class Ball : public Shape {
    double radius_;

public:
    Ball(double x, double y, double radius) : Shape(x, y),  radius_{radius} {}
    void draw(SDL_Renderer* renderer) const;

};
