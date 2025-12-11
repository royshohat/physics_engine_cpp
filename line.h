class Shape;
class Ball;

class Line : public Shape {
protected:
    Vector2 pos2_; 

public:
    Line(Vector2 pos, Vector2 pos2) : Shape(pos), pos2_{pos2} {}

    void draw (SDL_Renderer* renderer) const override {
        SDL_RenderDrawLine(renderer, pos_.x, pos_.y, pos2_.x, pos2_.y);}

    Vector2 getPos2(){return pos2_;}
    void setPos2(Vector2 pos2){pos2_ = pos2;}

    
    void checkForCollisionLine(Line& line) override {};
    void checkForCollisionBall(Ball& circle) override {};
    void checkForCollision(Shape& shape) override {shape.checkForCollisionLine(*this); }
};