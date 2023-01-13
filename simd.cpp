#include <xmmintrin.h>
#include <emmintrin.h>

// Computing a dot product of 4-tuples using SSE2.
__m128 Dot(__m128 const v0, __m128 const v1)
{
    __m128 t0 = _mm_mul_ps(v0, v1);
    __m128 t1 = _mm_shuffle_ps(t0,t0,_MM_SHUFFLE(2,3,0,1));
    __m128 t2 = _mm_add_ps(t0,t1);
    __m128 t3 = _mm_shuffle_ps(t2,t2,_MM_SHUFFLE(0,0,2,2));
    __m128 dotSplat = _mm_add_ps(t2,t3);
    return dotSplat;
    // float dot = dotSplat.m128_f32[0];
}
