// https://github.com/xtensor-stack/xsimd

#include <xmmintrin.h>
#include <emmintrin.h>

// Computing a dot product of 4-tuples using SSE2.
__m128 Dot(__m128 const v0, __m128 const v1)
{
    __m128 t0 = _mm_mul_ps(v0, v1);
    __m128 t1 = _mm_shuffle_ps(t0, t0, _MM_SHUFFLE(2, 3, 0, 1));
    __m128 t2 = _mm_add_ps(t0, t1);
    __m128 t3 = _mm_shuffle_ps(t2, t2, _MM_SHUFFLE(0, 0, 2, 2));
    __m128 dotSplat = _mm_add_ps(t2, t3);
    return dotSplat;
    // float dot = dotSplat.m128_f32[0];
    // extract a component will break the SIMD pipeline
}

// computing the minimum components of two 4-tuples
// select than branch
__m128 mm_min_ps()
{
    __m128 v0 = _mm_setr_ps(1.0f, 3.0f, 5.0f, 6.0f);
    __m128 v1 = _mm_setr_ps(2.0f, 1.0f, 5.0f, 7.0f);
    __m128 c = _mm_cmplt_ps(v0, v1);
    __m128 minV0V1 = _mm_or_ps(_mm_and_ps(c, v0), _mm_andnot_ps(c, v1));
    // minV0V1 = (1.0f,1.0f,5.0f,6.0f);
}

// where cmp is intended to be a result from a comparison, and v0 and v1 are
// the inputs whose components are to be selected. In most cases, cmp has com-
// ponents that are either 0xFFFFFFFF or 0x00000000, but the function is more
// general in that cmp can have any bit patterns of interest.
__m128 Select(__m128 cmp, __m128 v0 , __m128 v1)
{
    return _mm_or_ps(_mm_and_ps(cmp, v0), _mm_andnot_ps(cmp, v1));
}

// The problem is that the SIMD register which stores length must have a com-
// ponent extracted and copied to a CPU register, and then the comparison is
// computed on the CPU. Transfers between CPU and SIMD registers will slow
// you down.
__m128 NormalizeWithBreak(__m128 const v)
{
    // (sqrLength，sqrLength , sqrLength，sqrLength )
    __m128 sqrLength = Dot(v, v);
    // (length ，length ，length ，length )
    __m128 length = _mm_sqrt_ps(sqrLength);
    if (length.m128_f32[0] > 0.0f)
    { // Divide by the length to normalize.
        __m128 normalized = _mm_div_ps(v, length);
        return normalized;
    }
    else
        // If length is zero， v = (0,0,0,0).
        return v;
}

__m128 Normalize(__m128 const v)
// (sqrLength，sqrLength，sqrLength，sqrLength)
{
    __m128 sqrLength = Dot(v, v);
    // (length ，length ，length ，length)
    __m128 length = _mm_sqrt_ps(sqrLength);
    // Divide by length to normalize; potentially produces a divide by zero .
    __m128 normalized = _mm_div_ps(v, length);
    // Set to zero when the original length is zero
    __m128 zero = _mm_setzero_ps(); // = (0.0f， 0.0f，0.0f，0.0f)
    __m128 mask = _mm_cmpneq_ps(zero, length);
    normalized = _mm_and_ps(mask, normalized);
    return normalized;
}
