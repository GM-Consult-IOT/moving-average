#include <type_traits> // std::make_unsigned_t, make_signed_t, is_unsigned
#include <limits>      // std::numeric_limits
#include <cstdint>     // uint_fast16_t

/*!
* @file EMA_TF.h
*
* @mainpage Exponentially Weighted Moving Average (EMA_TF) filter where the weight 
* factor is a power of two.
*
* @section intro_sec_Introduction
*
* Exponentially Weighted Moving Average (EMA_TF) filter where the weight 
* factor is a power of two.
* 
* @section author Author
* 
* Gerhard Malan for GM Consult Pty Ltd, based on original work by 
* (PieterP)[https://github.com/tttapa].
* 
 * @section license License
 * 
 * This library is open-source under the BSD 3-Clause license and 
 * redistribution and use in source and binary forms, with or without 
 * modification, are permitted, provided that the license conditions are met.
 *
 * @brief   Exponential moving average filter.
 * 
 * Fast integer EMA_TF implementation where the weight factor is a power of two.
 * 
 * Difference equation: @f$ y[n] = \alpha·x[n]+(1-\alpha)·y[n-1] @f$
 * where @f$ \alpha = \left(\frac{1}{2}\right)^{K} @f$, @f$ x @f$ is the
 * input sequence, and @f$ y @f$ is the output sequence.
 *
 * [An in-depth explanation of the EMA_TF filter](https://tttapa.github.io/Pages/MathEMA_TFtics/Systems-and-Control-Theory/Digital-filters/Exponential%20Moving%20Average/)
 *
 * @tparam  K
 *          The amount of bits to shift by. This determines the location
 *          of the pole in the EMA_TF transfer function, and therefore the
 *          cut-off frequency.  
 *          The higher this number, the more filtering takes place.  
 *          The pole location is @f$ 1 - 2^{-K} @f$.
 * @tparam  input_t
 *          The integer type to use for the input and output of the filter. 
 *          Can be signed or unsigned.
 * @tparam  state_t
 *          The unsigned integer type to use for the internal state of the
 *          filter. A fixed-point representation with @f$ K @f$ fractional
 *          bits is used, so this type should be at least @f$ M + K @f$ bits
 *          wide, where @f$ M @f$ is the maximum number of bits of the input.
 *
 * Some examples of different combinations of template parameters:
 * 
 * 1. Filtering the result of `analogRead`: analogRead returns an integer
 *    between 0 and 1023, which can be represented using 10 bits, so 
 *    @f$ M = 10 @f$. If `input_t` and `output_t` are both `uint16_t`,
 *    the maximum shift factor `K` is @f$ 16 - M = 6 @f$. If `state_t`
 *    is increased to `uint32_t`, the maximum shift factor `K` is 
 *    @f$ 32 - M = 22 @f$.
 * 2. Filtering a signed integer between -32768 and 32767: this can be 
 *    represented using a 16-bit signed integer, so `input_t` is `int16_t`,
 *    and @f$ M = 16 @f$. (2¹⁵ = 32768)
 *    Let's say the shift factor `K` is 1, then the minimum width of 
 *    `state_t` should be @f$ M + K = 17 @f$ bits, so `uint32_t` would be 
 *    a sensible choice.
 */


#ifndef EMA_TF_TF_H_
#define EMA_TF_TF_H_
template <uint8_t K,
          class input_t = uint_fast16_t,
          class state_t = std::make_unsigned<input_t>>
class EMA_TF {
  public:
    /// Constructor: initialize filter to zero or optional given value.
    EMA_TF(input_t initial = input_t(0))
      : state(zero + (state_t(initial) << K) - initial) {}

    /// Update the filter with the given input and return the filtered output.
    input_t operator()(input_t input) {
      state         += state_t(input);
      state_t output = (state + half) >> K;
      output        -= zero >> K;
      state         -= output;
      return input_t(output);
    }

    constexpr static state_t 
      max_state  = std::numeric_limits<state_t>::max(),
      half_state = max_state / 2 + 1,
      zero       = std::is_unsigned<input_t>::value ? state_t(0) : half_state,
      half       = K > 0 ? state_t(1) << (K - 1) : state_t(0);
  
    static_assert(std::is_unsigned<state_t>::value, 
                  "state type should be unsigned");

    static_assert(max_state >= std::numeric_limits<input_t>::max(),
                  "state type cannot be narrower than input type");               

    /// Verify the input range to make sure it's compatible with the shift
    /// factor and the width of the state type.
    template <class T>
    constexpr static bool supports_range(T min, T max) {
      using sstate_t = std::make_signed_t<state_t>;
      return min <= max &&
             min >= std::numeric_limits<input_t>::min() &&
             max <= std::numeric_limits<input_t>::max() &&
             (std::is_unsigned<input_t>::value
               ? state_t(max) <= (max_state >> K)
               : min >= -sstate_t(max_state >> (K + 1)) - 1 &&  
                 max <= sstate_t(max_state >> (K + 1)));
    }

  private:
    state_t state;
};

#endif