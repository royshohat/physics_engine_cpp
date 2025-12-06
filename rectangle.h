class Line;
class Shape;
class Ball;
class Rectangle : public Shape {
    double width_;
    double height_;
    SDL_Rect rect_;

public:
Rectangle(double x, double y, double width, double height)
    : Shape{x, y},
      width_{width},
      height_{height},
      rect_{static_cast<int>(x),
            static_cast<int>(y),
            static_cast<int>(width),
            static_cast<int>(height)}
{}

    const SDL_Rect& getSDLRect() const{
        return rect_; 
    }
    void setPos(double x, double y) override{
        Shape::setPos(x, y);
        rect_.x = x;
        rect_.y = y;
    }
    void draw (SDL_Renderer* renderer) const override  {
        SDL_RenderFillRect(renderer, &rect_);}

    void checkForCollision (Line line) override;
    void checkForCollision(double m, double b, bool skip) override;
    void checkForCollision(Rectangle rect) override; 
    void checkForCollision(Ball circle) override;

};