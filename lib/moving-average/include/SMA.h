/*!
* @file EMA.h
*
* @mainpage Simple Moving Average (SMA) filter used for smoothing time-series 
* integer data.
*
* @section intro_sec_Introduction
*
* Simple Moving Average (SMA) filter used for smoothing time-series 
* integer data.
* 
* @section author Author
* 
* Gerhard Malan for GM Consult Pty Ltd, based on original work by 
* (jonnieZG)[https://tttapa.github.io/Pages/Mathematics/Systems-and-Control-Theory/Digital-filters/Simple%20Moving%20Average/C++Implementation.html].
* 
 * @section license License
 * 
 * This library is open-source under the BSD 3-Clause license and 
 * redistribution and use in source and binary forms, with or without 
 * modification, are permitted, provided that the license conditions are met.
 * 
 * EMA Filter - Exponentially Weighted Moving Average filter used for smoothing data series readings.
 *
 *     output = alpha * reading + (1 - alpha) * lastOutput
 *
 * Where:
 *  -   alpha = factor greater than 0 and less or equal to 1
 *  -   reading = current input value
 *  -   lastOutput = last filter output value
 *  -   output = filter output value after the last reading
 *
 */

#ifndef _SMA_T_H_
#define _SMA_T_H_

#include <stdint.h>

template <uint8_t N, class input_t = uint16_t, class sum_t = uint32_t>
class SMA_T {
  public:
    input_t operator()(input_t input) {
        sum -= previousInputs[index];
        sum += input;
        previousInputs[index] = input;
        if (++index == N)
            index = 0;
        return (sum + (N / 2)) / N;
    }

    static_assert(
        sum_t(0) < sum_t(-1),  // Check that `sum_t` is an unsigned type
        "Error: sum data type should be an unsigned integer, otherwise, "
        "the rounding operation in the return statement is invalid.");

  private:
    uint8_t index             = 0;
    input_t previousInputs[N] = {};
    sum_t sum                 = 0;
};

#endif // _SMA_T_H_