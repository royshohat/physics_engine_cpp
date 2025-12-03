class Rectangle : public Shape {
    double wigth_;
    double hight_;

public:
    Rectangle(double x, double y, double wigth, double hight) : 
    Shape(x, y), wigth_{wigth}, hight_ {hight} {};
};