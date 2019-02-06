/**
--- Day 3: No Matter How You Slice It ---

The Elves managed to locate the chimney-squeeze prototype fabric for Santa's
suit (thanks to someone who helpfully wrote its box IDs on the wall of the
warehouse in the middle of the night). Unfortunately, anomalies are still
affecting them - nobody can even agree on how to cut the fabric.

The whole piece of fabric they're working on is a very large square - at least
1000 inches on each side.

Each Elf has made a claim about which area of fabric would be ideal for Santa's
suit. All claims have an ID and consist of a single rectangle with edges
parallel to the edges of the fabric. Each claim's rectangle is defined as
follows:

    The number of inches between the left edge of the fabric and the left edge
of the rectangle. The number of inches between the top edge of the fabric and
the top edge of the rectangle. The width of the rectangle in inches. The height
of the rectangle in inches.

A claim like #123 @ 3,2: 5x4 means that claim ID 123 specifies a rectangle 3
inches from the left edge, 2 inches from the top edge, 5 inches wide, and 4
inches tall. Visually, it claims the square inches of fabric represented by #
(and ignores the square inches of fabric represented by .) in the diagram below:

...........
...........
...#####...
...#####...
...#####...
...#####...
...........
...........
...........

The problem is that many of the claims overlap, causing two or more claims to
cover part of the same areas. For example, consider the following claims:

#1 @ 1,3: 4x4
#2 @ 3,1: 4x4
#3 @ 5,5: 2x2

Visually, these claim the following areas:

........
...2222.
...2222.
.11XX22.
.11XX22.
.111133.
.111133.
........

The four square inches marked with X are claimed by both 1 and 2. (Claim 3,
while adjacent to the others, does not overlap either of them.)

If the Elves all proceed with their own plans, none of them will have enough
fabric. How many square inches of fabric are within two or more claims?

--- Part Two ---

Amidst the chaos, you notice that exactly one claim doesn't overlap by even a single square inch of fabric with any other claim. If you can somehow draw attention to it, maybe the Elves will be able to make Santa's suit after all!

For example, in the claims above, only claim 3 is intact after all claims are made.

What is the ID of the only claim that doesn't overlap?

*/

#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

struct Rectangle {
  int left;
  int top;
  int width;
  int height;

  Rectangle(int left, int top, int width, int height)
      : left(left), top(top), width(width), height(height) {}
};

Rectangle ParseRectangle(const string& input) {
  auto at = input.find("@");
  auto comma = input.find(",", at);
  auto colon = input.find(":", comma);
  auto x = input.find("x", colon);

  int left = std::stoi(input.substr(at + 2, comma - at - 2));
  int top = std::stoi(input.substr(comma + 1, colon - comma - 1));
  int width = std::stoi(input.substr(colon + 2, x - colon - 2));
  int height = std::stoi(input.substr(x + 1));

  return Rectangle(left, top, width, height);
}


int main() {
  string line;
  vector<Rectangle> rects;

  int max_w = 0, max_h = 0;
  while (std::getline(cin, line)) {
    auto rect = ParseRectangle(line);
    rects.push_back(rect);

    max_w = std::max(max_w, rect.left + rect.width);
    max_h = std::max(max_h, rect.top + rect.height);
  }

  int area_overlap = 0;
  for (int x = 0; x < max_w; ++x) {
    for (int y = 0; y < max_h; ++y) {
      bool in_another = false;
      for (const auto& rect : rects) {
        if (x > rect.left && x <= rect.left + rect.width && y > rect.top && y <= rect.top + rect.height) {
          if (in_another) {
            area_overlap += 1;
            break;
          } else {
            in_another = true;
          }
        }
      }
    }
  }

  cout << "total area overlapped = " << area_overlap << endl;

  return 0;
}