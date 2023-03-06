#include "./headers/parser.h"
#include "./headers/circle.h"
#include "./headers/figure.h"
#include "./headers/triangle.h"

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

vector<Figure*> read_from_file(const string& file_name)
{
    vector<Figure*> figures;
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
                return figures;
            }
            string figure_name = figure_names[figure_ind];

            char next_char = line[figure_name.length()];
            if (next_char != '(' && next_char != ' ') {
                print_error(
                        line,
                        figure_name.length(),
                        "expected '(' or ' ' after figure name");
                return figures;
            }

            if (figure_name == "triangle") {
                figures.push_back(new Triangle(line));
            }

            if (figure_name == "circle") {
                figures.push_back(new Circle(line));
            }
            line_number++;
        }
    }

    return figures;
}