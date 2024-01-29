/*!
* @file EMA.h
*
* @mainpage Simple Moving Average (SMA) filter used for smoothing time-series 
* data.
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

#ifndef _SMA_H_
#define _SMA_H_

#include <stdint.h>

template <uint8_t N, typename T>
class SMA {
  public:
    T operator()(T input) {
        sum -= previousInputs[index];
        sum += input;
        previousInputs[index] = input;
        if (++index == N)
            index = 0;
        #ifdef SMA_DEBUG
          Serial.printf("Input: %f, sum: %f, index: %i\n", 
                        input, sum, index);
          Serial.print("Time series = {");
          for (int i = 0; i<N; i++){
            Serial.printf("%f", previousInputs[i]);
          }
          Serial.println("}");
        #endif //SMA_DEBUG
        return round((sum + (N / 2)) / N);
    }


  private:
    uint16_t index             = 0;
    T previousInputs[N] = {};
    T sum                 = 0;
};

#endif // _SMA_H_