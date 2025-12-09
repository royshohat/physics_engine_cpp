struct Vector2 {
    double x, y;

    double magnitudeSq() const {return x*x + y*y;}

    // Subtraction
    Vector2 operator-(const Vector2& other) const { return {x - other.x, y - other.y}; }
    Vector2 operator-(double scalar) const { return {x - scalar, y - scalar};}

    // Addition
    Vector2 operator+(const Vector2& other) const { return {x + other.x, y + other.y}; }

    // Scalar multiplication 
    Vector2 operator*(double scalar) const { return {x * scalar, y * scalar}; }

    // vector mutiplication
    Vector2 operator*(const Vector2& other) { return {x * other.x, y * other.y}; }
    

    void operator+=(const Vector2& other) { x += other.x; y += other.y; }
    void operator-=(const Vector2& other) { x -= other.x; y -= other.y; }


};