#include <iostream>

template <typename Fn>
void combine(int *array, int len, int N, Fn fn, int pos = 0) {
  if (pos == len) {
    fn();
  } else {
    int min = pos == 0 ? 1 : array[pos - 1] + 1;
    for (int i = min; i <= N - (len-pos)+1; ++i) {
      array[pos] = i;
      combine(array, len, N, fn, pos + 1);
    }
  }
}

struct Total {
  int combinations = 0;
  int digits[10] = {0};
};

void analyze(int cells, int N) {
  // How many permutations are there over `cells` cells.
  int values[N];
  Total totals[46];

  combine(values, cells, N, [&]() {
    int sum = 0;
    for (int i = 0; i < cells; ++i)
      sum += values[i];
    totals[sum].combinations++;
    for (int i = 0; i < cells; ++i)
      totals[sum].digits[values[i]]++;
  });

  for (int total = 0; total <= 45; ++total) {
    if (totals[total].combinations == 1) {
      std::cout << total << "/" << cells << "  " /* "/" << N << */;
      for (int j = 1; j <= N; ++j) {
        if (totals[total].digits[j] > 0)
          std::cout << j;
      }
      std::cout << std::endl;
    } else if (totals[total].combinations > 1) {
      std::cout << total << "/" << cells << "  " /* "/" << N << */;
      for (int j = 1; j <= N; ++j) {
        if (totals[total].digits[j] == 0)
          std::cout << "-" << j;
        if (totals[total].digits[j] == totals[total].combinations)
          std::cout << "+" << j;
      }
      std::cout << std::endl;
    }
  }
}

void display(int N) {
  std::cout << "N = " << N << std::endl;
  for (int cells = 1; cells <= N; cells++)
    analyze(cells, N);
}

int main() {
  display(6);
  display(9);
}
