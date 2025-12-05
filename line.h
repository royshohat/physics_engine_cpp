class Line : public Shape {
    double x2_;
    double y2_;

public:
    Line(int x1, int y1, int x2, int y2) : Shape(x1, y1), x2_{x2}, y2_{y2} {}

    void draw (SDL_Renderer* renderer) const {
        SDL_RenderDrawLine(renderer, x_, y_, x2_, y2_);}
    double getX2(){return x2_;}
    double getY2(){return y2_;}
};