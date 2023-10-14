#include <iostream>

/*
    Generate all combinations of 1..N in the array `array` of length `len`.
    `fn` is called for each unique combination.
    The numbers in `array` are in ascending order.
*/
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

  void display(std::ostream &os, int N) const {
    if (combinations == 1) {
      for (int j = 1; j <= N; ++j) {
        if (digits[j] > 0)
          os << j;
      }
    } else if (combinations > 1) {
      for (int j = 1; j <= N; ++j)
        if (digits[j] == combinations)
          os << j;
      os << "\\";
      for (int j = 1; j <= N; ++j)
        if (digits[j] == 0)
          os << j;
    }
  }
};

void constructTotalsForSize(int cells, int N, Total totals[]) {
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
      constructTotalsForSize(cells, N, totals[cells]);
    }
  }

  void display(std::ostream &os, const formats &fmt) const {
    os << "## Killer Sudoku table for N = " << N << std::endl << std::endl;

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
        totals[i][total].display(os, N);
      }
      os << fmt.row_end << std::endl;
    }
  }
};

int main() {
  std::cout << "# Tables for Killer Sudoku and Kakuro\n\n";
  std::cout << "Notation:\n_Total_ gives the sum of the cells in a region.\n";
  std::cout << "_Size_ is the number of cells in the region/row/column.\n";
  std::cout << "_N_ is the number of digits in the puzzle.\n";
  std::cout << "Each cell describes what digits are possible in a cell of a "
               "given size and total.\n";
  std::cout << "When a cell contains just digits, then this is the unique "
               "combination.\n";
  std::cout << "When a cell contains `\\`, then there is more than one "
               "combination. The digits before the `\\` must be present, and "
               "digits after the `\\` must be absent.\n\n";

  formats fmt = {"| ", " | ", " |", "---"};
  Table(4).display(std::cout, fmt);
  std::cout << std::endl;
  Table(6).display(std::cout, fmt);
  std::cout << std::endl;
  Table(9).display(std::cout, fmt);
}
