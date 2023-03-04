#pragma once
#include "figure.h"
#include "point.h"

class Circle : public Figure {
public:
    string name;
    Point center;
    double radius;

    Circle(string& wkt);

    double get_perimeter();
    double get_area();

    bool intersects(const Figure& figure) const override;
   
    virtual bool intersects_with_circle(const Circle& other) const override;
    virtual bool intersects_with_triangle(const Triangle& other) const override;
    string get_name() const override;
};