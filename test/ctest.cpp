#include <ctest.h>
#include <figure.h>
#include <parser.h>

#include <string>
#include <vector>

CTEST(ctest, CHECK_SIZE) {
  vector<Figure *> figures = read_from_file("geometry.txt");
  ASSERT_EQUAL(3, (int)(figures.size()));
}

CTEST(ctest, CHECK_DATA) {
  vector<string> expected = {"triangle", "circle", "triangle"};
  vector<Figure *> figures = read_from_file("geometry.txt");

  for (size_t i = 0; i < figures.size(); i++) {
    ASSERT_STR(expected[i].c_str(), figures[i]->get_name().c_str());
  }
}