//a small C++ program
#include <iostream>
#include <string>

int main()
{
  std::cout << "Enter your age: ";
  int name = 0;
  std::cin >> name;
  std::cout << "Hello, " << name << std::endl;
  std::string str;
  std::cin.clear();
  std::cin >> str;
  std::cout << "the string read is " << str << std::endl;
  return 0;
}
