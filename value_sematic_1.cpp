// Guideline 22: Prefer Value Semantics to Reference Semantics

#include <cstdlib>
#include <iostream>
#include <span>
#include <vector>

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
   std::vector<int> v{1, 2, 3, 4};

   std::vector<int> const w{v};
   std::span<int> const s{v};

   // w[2] = 99;  // Compilation error!
   s[2] = 99; // Works!

   // Prints ( 1 2 99 4 );
   print(s);

   v = {5, 6, 7, 8, 9};
   s[2] = 99; // Works!

   // Prints ?
   print(s);

   return EXIT_SUCCESS;
}