// 22: Prefer Value Semantics to Reference Semantics

#include <cstdlib>
#include <iostream>
#include <span>
#include <vector>
#include <algorithm>

void print(std::span<int> s)
{
   std::cout << " (";
   for (int i : s)
   {
      std::cout << ' ' << i;
   }
   std::cout << " )\n";
}

int main()
{
   std::vector<int> vec{1, -3, 27, 42, 4, -8, 22, 42, 37, 4, 18, 9};

   auto const pos = std::max_element(begin(vec), end(vec));

   vec.erase(std::remove(begin(vec), end(vec), *pos), end(vec));

   print(vec);

   return EXIT_SUCCESS;
}