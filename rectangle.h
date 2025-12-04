class Rectangle : public Shape {
    double width_;
    double height_;
    SDL_Rect rect_;

public:
    Rectangle(double x, double y, double width, double height) : 
    Shape(x, y), width_{width}, height_ {height}, rect_{(x,y,width,height)}{}

    const SDL_Rect& getSDLRect() const{
        return rect_; 
    }
    void setPos(double x, double y) override{
        Shape::setPos(x, y);
        rect_.x = x;
        rect_.y = y;
    }
    void draw (SDL_Renderer* renderer) const {
        SDL_RenderFillRect(renderer, &rect_);}
    

};