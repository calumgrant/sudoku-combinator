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
}

struct formats {
  const char *row_start, *row_middle, *row_end, *line;
};

struct Table {
  const int N;

  Total totals[10][46];

  int maxTotal() const { return N * (N + 1) / 2; }

  Table(int N) : N(N) {
    for (int cells = 1; cells <= N; ++cells) {
      analyze(cells, N, totals[cells]);
    }
  }

  void display(std::ostream &os, const formats &fmt) const {
    os << "# Killer Sudoku table for N = " << N << std::endl << std::endl;

    os << fmt.row_start;
    os << "Total \\ Size";
    for (int i = 1; i <= N; ++i) {
      os << fmt.row_middle << i;
    }
    os << fmt.row_end << std::endl;

    os << fmt.row_start;
    os << fmt.line;
    for (int i = 1; i <= N; ++i) {
      os << fmt.row_middle << fmt.line;
    }
    os << fmt.row_end << std::endl;

    int mt = maxTotal();
    for (int total = 1; total <= mt; ++total) {
      os << fmt.row_start;
      os << total;
      for (int i = 1; i <= N; ++i) {
        os << fmt.row_middle;
        totals[i][total].display();
      }
      os << fmt.row_end << std::endl;
    }
  }
};

int main() {
  formats fmt = {"| ", " | ", " |", "---"};
  Table(6).display(std::cout, fmt);
  std::cout << std::endl;
  Table(9).display(std::cout, fmt);
}
