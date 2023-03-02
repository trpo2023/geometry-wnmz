#include "../include/utils.h"
#include "../include/point.h"

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

enum ArgType { POINT, NUMBER };

const vector<string> figure_names = {"circle", "triangle"};
const map<const string, const vector<ArgType>> figure_args = {{
        {"circle", {POINT, NUMBER}},
        {"triangle", {POINT, POINT, POINT, POINT}},
}};

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

int main(int argc, char* argv[])
{
    if (argc != 2) {
        cout << "ERROR: First argument should be filename." << endl;
        return 1;
    }

    string file_name = argv[1];
    ifstream file;
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
            const string figure_name = figure_names[figure_ind];
            const vector<ArgType> args = figure_args.at(figure_name);
            vector<Point> points = {};
            vector<double> number_args = {};

            size_t start = line.find("(");
            size_t end = line.find_last_of(")");

            while (line[start] == '(' && line[end] == ')') {
                start++;
                end--;
            };
            // left bracket check
            if (line[start] != '(' && line[end] == ')') {
                print_error(line, start + 2, "'(' expected.");
                return 1;
            }
            // right bracket check
            if (line[start] == '(' && line[end] != ')') {
                print_error(line, end + 2, "')' expected.");
                return 1;
            }

            string tmp_arg = "";
            int arg_num = 0;
            double radius = 0;
            for (size_t i = start; i <= end + 1; i++) {
                if (line[i] == ',' || i == end + 1) {
                    trim_string(tmp_arg);
                    if (args[arg_num] == POINT) {
                        points.push_back(Point::from_string(tmp_arg));
                    }

                    if (args[arg_num] == NUMBER) {
                        number_args.push_back(stod(tmp_arg));
                        if (figure_name == "circle") {
                            radius = stod(tmp_arg);
                        }
                    }

                    arg_num++;
                    tmp_arg.clear();
                    continue;
                }

                tmp_arg += line[i];
            }

            if (points.size() + number_args.size()
                != figure_args.at(figure_name).size()) {
                print_error(
                        line,
                        end,
                        "expected "
                                + to_string(figure_args.at(figure_name).size())
                                + ", but got " + to_string(points.size())
                                + " arguments!");
                return 1;
            }

            cout << figure_name << " ( ";
            for (Point p : points) {
                cout << p.x << " " << p.y << " ";
            }
            if (figure_name == "circle") {
                cout << radius << " ";
            }
            cout << ")" << endl;
        }
        return 0;
    }
};