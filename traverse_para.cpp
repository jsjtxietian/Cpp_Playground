#include <utility>  
#include <iostream>

template<typename... Pack>
void traverse_para(Pack&&... pack)
{
    ([&](){
        using Arg = Pack;
        auto arg = std::forward<Pack>(pack);
        std::cout << arg << std::endl;
    }(),...);
}

int main()
{
    traverse_para(1,2,"fuck");
    return 0;
}