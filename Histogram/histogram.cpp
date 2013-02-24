#include "histogram.hpp"
#include <iostream>
#include <sstream>

Histogram::Histogram (int low, int high)
  : lowerbound(low), upperbound(high) {
  size_t size = high - low + 1;
  if (size < 1) {
    throw Bad_Range();
  }
  numbers = new int[size];
  for (int i = 0; i < size; i++) {
    numbers[i] = 0;
  }
}

Histogram& Histogram::increment(int n) {
  if (n < lowerbound || n > upperbound) {
    throw Out_Of_Range();
  }
  *(numbers + n - lowerbound) += 1;
  return *this;
}

std::string Histogram::string_rep() {
  size_t size = upperbound - lowerbound + 1;
  std::ostringstream ss;
  for (int i = 0; i < size; i++) {
    ss << i << " : " << numbers[i] << "\n";
  }
  return ss.str();
}

Histogram::~Histogram() {
  delete[] numbers;
}

int main() {
  Histogram myhist(2, 4);
  myhist.increment(3);
  myhist.increment(4);
  myhist.increment(2);
  myhist.increment(2);
  std::cout << myhist.string_rep() << "\n";

  return 0;
}
