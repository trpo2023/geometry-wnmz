#include "./headers/figure.h"
#include "./headers/circle.h"

#include <climits>

bool Figure::intersects(const Figure&) const
{
    return false;
}

double Figure::get_perimeter()
{
    double per = 0;
    for (size_t i = 0; i < this->points.size() - 1; i++) {
        per += Point::get_distance(points[i], points[i + 1]);
    }
    return per;
};

double Figure::get_area()
{
    double area = 0;
    for (size_t i = 0; i < points.size(); i++) {
        size_t j = (i + 1) % points.size();
        area += points[i].x * points[j].y - points[j].x * points[i].y;
    }
    return fabs(area) / 2;
};

void Figure::parse_string(string& text)
{
    this->original_string = text;

    size_t start = text.find("(");
    size_t end = text.find_last_of(")");

    while (text[start] == '(' && text[end] == ')') {
        start++;
        end--;
    };
    // left bracket check
    if (text[start] != '(' && text[end] == ')') {
        print_error(text, start + 2, "'(' expected.");
        return;
    }
    // right bracket check
    if (text[start] == '(' && text[end] != ')') {
        print_error(text, end + 2, "')' expected.");
        return;
    }

    string _tmp_arg = "";
    for (size_t i = start; i <= end + 1; i++) {
        if (text[i] == ',' || i == end + 1) {
            trim_string(_tmp_arg);
            (this->str_args).push_back(_tmp_arg);
            (this->points).push_back(Point::from_string(_tmp_arg));
            _tmp_arg.clear();
            continue;
        }

        _tmp_arg += text[i];
    }

    if (this->str_args.size() != this->type_args.size()) {
        if (!this->is_polygon
            || this->str_args.size() < this->type_args.size()) {
            print_error(
                    text,
                    end,
                    "expected " + to_string(this->type_args.size())
                            + ", but got " + to_string(this->str_args.size())
                            + " arguments!");
            return;
        }
    }
}