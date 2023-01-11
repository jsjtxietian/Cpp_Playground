#include <iostream>
#include <cmath>
#include <cstdint>

typedef union
{
    uint32_t encoding;
    float number;
} binary32;

void decodefloat32(binary32 x)
{
    uint32_t s = (0x80000000 & x.encoding) >> 31; // sign
    uint32_t e = (0x7f800000 & x.encoding) >> 23; // biased exponent
    uint32_t t = (0x007fffff & x.encoding) >> 31; // trailing significand

    if (e == 0)
    {
        if (t == 0) // zeros
        {
            // x = (−1)^ s * 0 //allows for +0 and -0
        }
        else // subnormal numbers
        {
            // x = (−1)^s * 0.t * 2^{−126}
        }
    }
    else if (e < 255) // normal numbers
    {
        // x = (−1)^s * 1.t * 2^{e−127}
    }
    else // special numbers
    {
        if (t == 0)
        {
            // x = (−1)ˆ^s * infinity
        }
        else
        {
            // not a number
            if (t & 0x00400000)
            {
                // x = quiet NaN
            }
            else
            {
                // x = signaling NaN
            }
            // payload = t & 0x003fffff
        }
    }
}

// Solve c1∗x − c0 = 0
void InexactRepresentation()
{
    float c0 = 0.01f;
    float c1 = 1.0f;
    float x = c0 / c1;
    // .quad   0x3f847ae140000000              # double 0.0099999997764825821
}

float Distance(float x0, float y0, float x1, float y1)
{
    float dx = x1 - x0, dy = y1 - y0;
    return sqrt(dx * dx + dy * dy);
}

void IncorrectDistance()
{
    int i1 = (1 << 30);
    float x1 = static_cast<float>(i1);
    float d1 = Distance(0.0f, 0.0f, x1, 0.0f);

    int i2 = i1 + 64;
    float x2 = static_cast<float>(i2);
    float d2 = Distance(0.0f, 0.0f, x2, 0.0f);

    int idiff = i2 - i1;   // 64
    float ddiff = d2 - d1; // 0

    std::cout << "idiff: " << idiff << std::endl;
    std::cout << "ddiff: " << ddiff << std::endl;
}

int main()
{
    IncorrectDistance();
    return 0;
}
