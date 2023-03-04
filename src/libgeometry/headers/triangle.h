#pragma once

#include "figure.h"

class Triangle : public Figure {
public:
    Triangle(string& wkt);

    bool intersects(const Figure& figure) const override;

    bool intersects_with_circle(const Circle& figure) const override;
    bool intersects_with_triangle(const Triangle& figure) const override;
    string get_name() const override;
};