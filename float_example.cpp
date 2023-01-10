#include <iostream>
#include <cmath>

// Solve c1∗x − c0 = 0
void InexactRepresentation()
{
    float c0 = 0.01f;
    float c1 = 1.0f;
    float x = c0/c1;
    // .quad   0x3f847ae140000000              # double 0.0099999997764825821
}

float Distance(float x0,float y0, float x1, float y1)
{
    float dx = x1- x0 , dy = y1-y0;
    return sqrt(dx*dx+dy*dy);
}

void IncorrectDistance()
{
    int i1 = (1 << 30);
    float x1 = static_cast<float>(i1);
    float d1 = Distance(0.0f,0.0f,x1,0.0f);

    int i2 = i1 + 64;
    float x2 = static_cast<float>(i2);
    float d2 = Distance(0.0f,0.0f,x2,0.0f);

    int idiff = i2-i1; // 64
    float ddiff = d2-d1; // 0

    std::cout << "idiff: " << idiff << std::endl; 
    std::cout << "ddiff: " << ddiff << std::endl;
}

int main()
{
    IncorrectDistance();
    return 0;
}

