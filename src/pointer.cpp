#include <iostream>

int main(void) 
{
  int *p = new int;
  int *n = p;

  *n = 4;
  std::cout << *p << std::endl;

  *p +=6;
  std::cout << *n << std::endl;

  std::cout << n << std::endl;
  
  delete n;

  return 0;
}
