#include "./headers/triangle.h"
#include "./headers/circle.h"
#include "./headers/figure.h"

Triangle::Triangle(string& wkt)
{
    this->type_args = {POINT, POINT, POINT, POINT};
    this->parse_string(wkt);

    this->get_area();
    this->get_perimeter();
}

string Triangle::get_name() const
{
    return "triangle";
}

bool Triangle::intersects(const Figure& other) const
{
    const Triangle* other_triangle = dynamic_cast<const Triangle*>(&other);
    if (other_triangle) {
        return intersects_with_triangle(*other_triangle);
    }

    const Circle* other_circle = dynamic_cast<const Circle*>(&other);
    if (other_circle) {
        return intersects_with_circle(*other_circle);
    }

    return false;
}

bool Triangle::intersects_with_circle(const Circle& other) const
{
    return other.intersects_with_triangle(*this);
}

bool Triangle::intersects_with_triangle(const Triangle& other) const
{
    return false;
}