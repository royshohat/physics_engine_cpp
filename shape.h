//abstract class
class Shape {
protected:
    double x_;
    double y_;
    double vel_x_;
    double vel_y_;
    std::string color_;

public:
    Shape(double x, double y) : x_{x}, y_{y}, color_{"red"} {}

    // move based on velocity
    virtual void setVelo(double velo_x, double velo_y){vel_x_ = velo_x; vel_y_ = velo_y;}
    virtual void moveVelo(float deltaTime){setPos(x_ + deltaTime * vel_x_, 
        y_ + deltaTime * vel_y_);}
    virtual void setPos(double x, double y){x_ = x; y_ = y;}
    virtual void setColor(std::string color){color_ = color;}
    virtual double getX(){return x_;}
    virtual double getY(){return y_;}
    virtual void draw(SDL_Renderer* renderer) const = 0;

};