#pragma once

#include "point.h"
#include <vector>

enum ArgType { POINT, NUMBER };

class Circle;
class Triangle;

class Figure {
public:
    vector<int> type_args;
    vector<string> str_args;
    vector<Point> points;

    bool is_polygon = false;

    int radius = 0;
    string original_string;

    virtual bool intersects(const Figure&) const = 0;

    virtual void parse_string(string&);
    virtual double get_perimeter();
    virtual double get_area();

    virtual string get_name() const = 0;

protected:
    virtual bool intersects_with_circle(const Circle&) const
    {
        return false;
    }
    virtual bool intersects_with_triangle(const Triangle&) const
    {
        return false;
    }
};
