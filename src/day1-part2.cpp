#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <vector>
#include <utils.h>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::min;
using std::min_element;
using std::sort;
using std::stable_sort;
using std::vector;


int PositiveMod(int divident, int divisor) {
  int result = divident % divisor;
  if (result < 0) {
    return divisor + result;
  } else {
    return result;
  }
}


int FindDup() {
  vector<int> frequencies;
  map<int, int> original_pos;
  int d, f = 0;
  while (cin >> d) {
    frequencies.push_back(f);
    if (original_pos.find(f) != original_pos.end()) {
      return f;
    }
    original_pos[f] = frequencies.size();
    f += d;
  }
  cout << frequencies;
  cout << "Shift = " << f << endl;

  if (f == 0) {
    return 0;
  }

  if (f > 0) {
    sort(frequencies.begin(), frequencies.end());
  } else {
    sort(frequencies.rbegin(), frequencies.rend());
  }
  cout << frequencies;

  stable_sort(frequencies.begin(), frequencies.end(),
              [f](int a, int b) { return PositiveMod(a, f) < PositiveMod(b, f); });
  cout << frequencies;

  for (auto c : frequencies) {
    cout << c << " % " << f << " = " << PositiveMod(c, f) << endl;
  }

  long min_diff = INT_MAX;
  int first_dup_frequency = 0;
  int first_dup_base = 0;
  for (auto prev = frequencies.begin(), curr = prev + 1;
       curr != frequencies.end(); prev += 1, curr += 1) {
    cout << "DEBUG: " << *prev << " -> " << *curr << endl;
    if (PositiveMod(*curr, f) != PositiveMod(*prev, f)) {
      cout << "  " << "Not same mod. " << endl;
      continue;
    }
    int diff = *curr - *prev;
    cout << "  " << "diff = " << diff << endl;
    if (diff < min_diff) {
      min_diff = diff;
      first_dup_frequency = *curr;
      first_dup_base = *prev;
    } else if (diff == min_diff && original_pos[*prev] < original_pos[first_dup_base]) {
      first_dup_frequency = *curr;
      first_dup_base = *prev;
    }
  }
  return first_dup_frequency;
}

int main(int argc, char* argv[]) {
  auto result = FindDup();
  cout << "First Duplicated Frequency: " << result << endl;
}
