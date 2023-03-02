#pragma once

#include "utils.h"
#include "math.h"

struct Point {
    int x;
    int y;
    static Point from_string(string str);
    static double get_distance(Point p1, Point p2);
};