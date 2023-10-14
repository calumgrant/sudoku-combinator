#include <iostream>

template <typename Fn>
void combine(int *array, int len, int N, Fn fn, int pos = 0) {
  if (pos == len) {
    fn();
  } else {
    int min = pos == 0 ? 1 : array[pos - 1] + 1;
    for (int i = min; i <= N - (len - pos) + 1; ++i) {
      array[pos] = i;
      combine(array, len, N, fn, pos + 1);
    }
  }
}

struct Total {
  int combinations = 0;
  int digits[10] = {0};

  void display() const {
    if (combinations == 1) {
      for (int j = 1; j <= 9; ++j) {
        if (digits[j] > 0)
          std::cout << j;
      }
    } else if (combinations > 1) {
      for (int j = 1; j <= 9; ++j) {
        if (digits[j] == 0)
          std::cout << "-" << j;
        else if (digits[j] == combinations)
          std::cout << "+" << j;
      }
    }
  }
};

void analyze(int cells, int N, Total totals[]) {
  // How many permutations are there over `cells` cells.
  int values[N];

  combine(values, cells, N, [&]() {
    int sum = 0;
    for (int i = 0; i < cells; ++i)
      sum += values[i];
    totals[sum].combinations++;
    for (int i = 0; i < cells; ++i)
      totals[sum].digits[values[i]]++;
  });

  // Dump it

  for (int total = 1; total <= 45; ++total) {
    auto &tot = totals[total];
    std::cout << total << "/" << cells << "  ";
    std::cout << totals[total].combinations << "  ";

    for (int i = 1; i <= 9; ++i) {
      std::cout << tot.digits[i] << " ";
    }

    if (totals[total].combinations) {
      std::cout << total << "/" << cells << "  ";
      std::cout << totals[total].combinations << "  ";
      totals[total].display();
    }
    std::cout << std::endl;
  }
}

struct Table {
  Total totals[10][46];

  Table(int N) {
    for (int cells = 1; cells <= N; ++cells) {
      analyze(cells, N, totals[cells]);
    }
  }
};

void display(int N) {
  std::cout << "N = " << N << std::endl;
  for (int cells = 1; cells <= N; cells++) {
    Total totals[46];
    analyze(cells, N, totals);
  }
}

int main() {
  // Table t6(6);
  Table t9(9);
  // display(6);
  // display(9);
}
