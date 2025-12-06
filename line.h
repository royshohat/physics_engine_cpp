class Shape;
class Rectangle;
class Ball;

class Line : public Shape {
    double x2_;
    double y2_;

public:
    Line(double x1, double y1, double x2, double y2) : Shape(x1, y1), x2_{x2}, y2_{y2} {}

    void draw (SDL_Renderer* renderer) const override {
        SDL_RenderDrawLine(renderer, x_, y_, x2_, y2_);}
    double getX2(){return x2_;}
    double getY2(){return y2_;}
    
    void checkForCollision (Line line) override;
    void checkForCollision(double m, double b, bool skip) override;
    void checkForCollision(Rectangle rect) override; 
    void checkForCollision(Ball circle) override;
};