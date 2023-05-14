#include <algorithm>
#include <iostream>
#include <vector>

#include "pretty.h"

// Motivation
struct Lookup {
  explicit Lookup(int v) : m_value{v} {}

  void operator()(int entry) {
    if (entry == m_value) {
      std::cout << "Found!"
                << "\tm_value = " << m_value << std::endl;
    } else {
      std::cout << "No found for entry = : " << entry << std::endl;
    }
  }

 private:
  int m_value;
};

void lookupAndPrint(const std::vector<int> &values, int v) {
  std::for_each(values.begin(), values.end(), Lookup{v});
}

struct Closure {
  explicit Closure(int z_) : z(z_){};
  int operator()(int a, int b) { return z + a + b; }
  int z;
};

// Basic
void example_1() {
  Closure cl(101);
  std::cout << cl(1, 2) << std::endl;
}

// Easy
//	Similar to 1, but a little bit shorter version
// void example_2() { std::cout << Closure(112)(1, 2) << std::endl; }
//	another implementation - similar to example 1
void example_2() {
  Closure cl3(112);
  std::cout << cl3(1, 2) << std::endl;
}

//	used in examples 3, 4
struct Closure2 {
  explicit Closure2(int z_) : z(z_){};
  int operator()(int a, int b) { return z + a + b; }
  int z;
};

// Middle
void example_3() {
  // [z=100] - capture with initialize (since C++14)
  auto closure = [z = 130](int a, int b) { return z + a + b; };
  std::cout << closure(1, 2) << std::endl;

  // __func__ is an implicitly declared identifier that expands to a character
  // array variable containing the function name when it is used inside of a
  // function. It was added to C in C99. From C99 §6.4.2.2/1:
  //     The identifier __func__ is implicitly declared by the translator as if,
  //     immediately following the opening brace of each function definition,
  //     the declaration static const char __func__[] = "function-name";
  //     appeared, where function-name is the name of the lexically-enclosing
  //     function. This name is the unadorned name of the function.
  // __PRETTY_FUNCTION__ is a gcc extension that is mostly the same as
  // __FUNCTION__, except that for C++ functions it contains the "pretty" name
  // of the function including the signature of the function.
  auto closure2 = [](int a, int b, int c) {
    std::cout << __PRETTY_FUNCTION__ << '\t';
    return a + b + c;
  };
  std::cout << closure2(140, 2, 3) << std::endl;
  std::cout << closure2(1, 2, 3) << std::endl;

  // lambda expression
  // [z=100](int a, int b) { return z + a + b; };

  // f - closure
  // auto f = [z=100](int a, int b) { return z + a + b; };

  // closure class
  // class lambda_x123dalsd033j1230a;
}

// Hard
void example_4() {
  std::cout << [z = 160](int a, int b) { return z + a + b; }(1, 2) << std::endl;

  std::vector<int> values = {0, 1, 2, 3, 3, 3, 4, 5, 6};
  std::for_each(values.begin(), values.end(), [value = 3](int entry) {
    if (entry == value) {
      std::cout << "Found!\t"
                << "value = " << value << std::endl;
    }
  });

  int value = 5;
  std::for_each(values.begin(), values.end(), [value](int entry) {
    if (entry == value) {
      std::cout << "Found!\t"
                << "value = " << value << std::endl;
    }
  });

  auto closure = [z = 100](int a, int b) mutable -> int {
    z = 150;
    std::cout << "Sum a + b + z = " << a + b + z << std::endl;
    return a + b + z;
  };
  closure(1, 2);

  auto closure2 = [z = 200](int a, int b) mutable -> decltype(a + b) {
    z = 250;
    std::cout << "Sum a + b + z = " << a + b + z << std::endl;
    return a + b + z;
  };
  closure2(2, 3);
  closure2(0, 0);

  auto closure3 = [](auto a, auto b) { return a + b; };
  std::cout << closure3(1.5, 2.7) << std::endl;

  std::cout << "value = " << value << std::endl;
  auto closure4 = [&value]() { value = 100; };
  closure4();
  std::cout << "value = " << value << std::endl;
}

int main() {
  std::cout << "\nLookup example:\n";
  std::vector<int> values = {0, 1, 2, 3, 3, 3, 4, 5, 6};
  lookupAndPrint(values, 2);

  std::cout << "\nExample_1():\n";
  example_1();

  std::cout << "\nExample_2():\n";
  example_2();

  std::cout << "\nExample_3():\n";
  example_3();

  std::cout << "\nExample_4():\n";
  example_4();

  return 0;
}
