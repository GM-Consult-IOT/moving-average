/*!
* @file EMA.h
*
* @mainpage Exponentially Weighted Moving Average (EMA) filter.
*
* @section intro_sec_Introduction
*
* Exponentially Weighted Moving Average (EMA) filter used for smoothing data series readings.
* 
* @section author Author
* 
* Gerhard Malan for GM Consult Pty Ltd, based on original work by 
* (jonnieZG)[https://github.com/jonnieZG/EWMA].
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

#ifndef _EMA_H_
#define _EMA_H_

class EMA {
public:
/*
	 * Current data output
	 */
	double output = 0;
	/*
	 * Smoothing factor, in range [0,1]. Higher the value - less smoothing (higher the latest reading impact).
	 */
	double alpha = 0;
		
	/*
	 * Creates a filter without a defined initial output. The first output will be equal to the first input.
	 */
	EMA(double alpha){
		this->alpha = alpha;
	}

	/*
	 * Creates a filter with a defined initial output.
	 */
	EMA(double alpha, double initialOutput){
		this->alpha = alpha;
		this->output = initialOutput;
		this->hasInitial = true;
	}
	void reset(){
		this->hasInitial = false;
	}

	/*
	 * Specifies a reading value.
	 * @returns current output
	 */
	double operator()(double input){
		if (hasInitial) {
			output = alpha * (input - output) + output;
		} else {
			output = input;
			hasInitial = true;
		}
		return output;
	}

private:

	bool hasInitial = false;

};

#endif /* _EMA_H_ */
