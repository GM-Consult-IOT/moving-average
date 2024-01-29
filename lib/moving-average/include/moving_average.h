/*!
* @file moving_average.h
*
* @mainpage Collection of moving average filters used for smoothing time-series 
* data.
*
* @section intro_sec_Introduction
*
* Collection of moving average filters used for smoothing time-series 
* data.
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


#ifndef _MOVING_AVERAGE_H_
#define _MOVING_AVERAGE_H_
#include "EMA.h"
#include "EMA_T.h"
#include "SMA.h"
#include "SMA_T.h"
#endif //_MOVING_AVERAGE_H_