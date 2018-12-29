#ifndef SNAIL_UTILS_H
#define SNAIL_UTILS_H
#include <iostream>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& out, std::vector<T>& v) {
  for (auto& e : v) {
    out << e << ", ";
  }
  out << std::endl;
  return out;
}

#endif  // SNAIL_UTILS_H