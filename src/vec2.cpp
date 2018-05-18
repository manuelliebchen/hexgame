#include "vec2.h"

vec2::vec2() : x(0), y(0){};

vec2::vec2(float _x, float _y) : x(_x), y(_y){};

vec2::vec2(const vec2& othre) : x(othre.x), y(othre.y){};

vec2 vec2::operator=(const vec2& rhs)
{
    x = rhs.x;
    y = rhs.y;
    return (*this);
};

vec2::~vec2(){};

vec2 vec2::operator+(const vec2& rhs) const
{
    return vec2(x + rhs.x, y + rhs.y);
};

vec2 vec2::operator+=(const vec2& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
};

vec2 vec2::operator-(const vec2& rhs) const
{
    return vec2(x - rhs.x, y - rhs.y);
};

vec2 vec2::operator-=(const vec2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
};

vec2 vec2::operator*(float rhs) const
{
    return vec2(x * rhs, y * rhs);
};

vec2 vec2::operator*=(float rhs)
{
    x *= rhs;
    y *= rhs;
    return *this;
};

vec2::operator float() const
{
    return sqrtf(x * x + y * y);
};

float vec2::lengthSquared() const
{
    return x * x + y * y;
};

vec2 vec2::normalize()
{
    float lenght = (float)(*this);
    x /= lenght;
    y /= lenght;
    return *this;
};

vec2 vec2::normalized() const
{
    float lenght = (float)(*this);
    return vec2(x / lenght, y / lenght);
};

float vec2::dot(const vec2& lhs, const vec2& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
};

std::ostream& operator<<(std::ostream& os, const vec2& vec)
{
    os << std::string("vec2: x=") << std::to_string(vec.x) << std::string(" y=")
       << std::to_string(vec.y);
    return os;
}
