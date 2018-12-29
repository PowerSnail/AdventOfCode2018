#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int IDCheckSum(vector<string>& ids) {
  int counts[256]{0};
  int n_twice = 0, n_thrice = 0;
  for (auto& id : ids) {
    for (auto c : id) {
      counts[int(c)] += 1;
    }
    int has_twice = 0, has_thrice = 0;
    for (auto& n : counts) {
      if (n == 2) {
        has_twice = 1;
      } else if (n == 3) {
        has_thrice = 1;
      }
      n = 0;
    }
    n_twice += has_twice;
    n_thrice += has_thrice;
  }
  return n_twice * n_thrice;
}

int CompareExcept(string& a, string& b, int ignore_id, int str_length) {
  for (int j = 0; j < str_length; ++j) {
    if (ignore_id == j || a[j] == b[j]) {
      continue;
    } else {
      return a[j] < b[j];
    }
  }
  return 0;
}

string CommonLetters(vector<string>& ids) {
  const int str_length = ids[0].length();
  for (int i = 0; i < str_length; ++i) {
    std::sort(ids.begin(), ids.end(), [i, str_length](auto& a, auto& b) {
      return CompareExcept(a, b, i, str_length);
    });
    for (int j = 0; j < ids.size() - 1; ++j) {
      if (CompareExcept(ids[j], ids[j + 1], i, str_length) == 0) {
        return string(ids[j]).erase(i, 1);
      }
    }
  }
  return "NOT FOUND!";
}

int main(int argc, char* argv[]) {
  vector<string> ids;
  string line;
  while (cin >> line) {
    ids.push_back(string(line));
  }
  int checksum = IDCheckSum(ids);
  cout << "Checksum = " << checksum << endl;

  auto common_letter = CommonLetters(ids);
  cout << "CommonLetters = " << common_letter << endl;
}