#include <vector>
#include <iostream>

int main(void)
{
  std::vector<std::string> vecky;

  vecky.emplace_back("Bitch");
  vecky.push_back(" Please");
  vecky.emplace_back(", Get Off My Back");

  for (int i = 0; i < vecky.size(); i++) {
    std::cout << vecky[i] << " Fuck it, yeah" << std::endl;
  }

  return 0;
}
