#include "EMA.h"

EMA::EMA(double alpha) {
	this->alpha = alpha;
}

EMA::EMA(double alpha, double initialOutput) {
	this->alpha = alpha;
	this->output = initialOutput;
	this->hasInitial = true;
}

void EMA::reset() {
	this->hasInitial = false;
}

double EMA::filter(double input) {
	if (hasInitial) {
		output = alpha * (input - output) + output;
	} else {
		output = input;
		hasInitial = true;
	}
	return output;
}
