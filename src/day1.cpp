#include <iostream>
#include <string>
#include <unordered_set>
#include <optional>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::unordered_set;
using std::vector;
using std::optional;


int main(int argc, char* argv[]) {
  int frequency = 0;
  int delta = 0;
  vector<int> deltas;
  unordered_set<int> set;
  optional<int> first_dup;

  set.insert(frequency);
  while (cin >> delta) {
    frequency += delta;
    deltas.push_back(delta);
    if (!first_dup.has_value()) {
      if (set.find(frequency) != set.end()) {
        first_dup = frequency;
      }
    }
    set.insert(frequency);
  }

  cout << "Final Frequency: " << frequency << endl;

  while (!first_dup.has_value()) {
    for (auto delta : deltas) {
      frequency += delta;
      if (set.find(frequency) != set.end()) {
        first_dup = frequency;
        break;
      }
    } 
  }

  cout << "First Dup Frequency: " << *first_dup << endl;
}
