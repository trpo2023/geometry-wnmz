#include "../include/lib.h"

using namespace std;

int main(int argc, char* argv[])
{
    string file_name = argv[1];
    vector<Figure*> figures = read_from_file(file_name);

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
    
    return 0;
}
