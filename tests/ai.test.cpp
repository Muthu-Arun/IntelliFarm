#include <iostream>
#include <run.h>
int main() {
  int diff;
  Ai::initialize();
  std::vector<double> output = Ai::getPrediction({32.58, 31.36, 32.58, 39});
  diff = output[0] - 1010;
  if (diff < 0)
    diff *= -1;
  if (diff < (0.05 * 1010))
    std::cout << "Test Case Passed \n";
  else
    std::cout << "Test Case Failed \n";
}
