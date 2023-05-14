#include <cassert>
#include <string>
#include <tuple>

auto getPerson() {
  const std::string name = "Petia";
  const std::string secondName = "Ivanoff";
  const std::size_t age = 23;
  const std::string department = "Sale";
  return std::make_tuple(name, secondName, age, department);
}

int main(int argc, char* argv[]) {
  std::string name, secondName, department;
  std::size_t age;
  //    custom_tie(name, secondName, age, department) = getPerson();        line
  //    from the execise lines below how code line above should be written to
  //    make code valid
  std::tie(name, secondName, age, department) = getPerson();  //  option #1

  assert(name == "Petia");
  assert(secondName == "Ivanoff");
  assert(age == 23);
  assert(department == "Sale");
  return 0;
}