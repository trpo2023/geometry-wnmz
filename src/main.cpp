#include "../include/circle.h"
#include "../include/figure.h"
#include "../include/triangle.h"

#include "math.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

const vector<string> figure_names = {"circle", "triangle"};

int find_figure(std::string str)
{
    int figure_ind = -1;
    for (size_t i = 0; i < figure_names.size(); i++) {
        if (str.find(figure_names[i]) == 0) {
            figure_ind = i;
            break;
        };
    }
    return figure_ind;
}

vector<Figure*> figures = {};

int main(int argc, char* argv[])
{
    string file_name = argv[1];
    ifstream file;
    int line_number = 1;
    file.open(file_name);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            str_tolower(line);

            int figure_ind = find_figure(line);
            if (figure_ind == -1) {
                print_error(
                        line, 0, "expected 'circle', 'triangle', or 'polygon'");
                return 1;
            }
            string figure_name = figure_names[figure_ind];

            char next_char = line[figure_name.length()];
            if (next_char != '(' && next_char != ' ') {
                print_error(
                        line,
                        figure_name.length(),
                        "expected '(' or ' ' after figure name");
                return 1;
            }

            if (figure_name == "triangle") {
                figures.push_back(new Triangle(line));
            }

            if (figure_name == "circle") {
                figures.push_back(new Circle(line));
            }
            line_number++;
        }

        for (size_t i = 0; i < figures.size(); i++) {
            Figure* figure = figures[i];

            cout << i + 1 << ". " << figure->original_string << endl;
            cout << '\t' << "perimeter = " << figure->get_perimeter() << endl;
            cout << '\t' << "area = " << figure->get_area() << endl;
            cout << '\t' << "intersects: " << endl;
            for (size_t j = 0; j < figures.size(); j++) {
                if (i != j && figures[j]->intersects(*figure)) {
                    cout << "\t\t" << j + 1 << ". " << figures[j]->get_name()
                         << endl;
                }
            }
        }
    }

    return 0;
}