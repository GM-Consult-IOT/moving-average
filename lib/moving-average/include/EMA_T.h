#ifndef EMA_T_H_
#define EMA_T_H_

/*!
 * @file EMA_T.h
*
* @mainpage Exponentially Weighted Moving Average (EWMA) filter for integer data.
*
* @section intro_sec_Introduction
*
* Exponentially Weighted Moving Average (EWMA) filter used for smoothing data series 
* readings. Allows restriction to only one specific data type, such as uint32_t. Avoiding 
* floating point arithmetics can significantly decrease code footprint, especially in embeded 
* devices.
* 
* @section author Author
* 
* Gerhard Malan for GM Consult Pty Ltd
* 
 * @section license License
 * 
 * This library is open-source under the BSD 3-Clause license and 
 * redistribution and use in source and binary forms, with or without 
 * modification, are permitted, provided that the license conditions are met.
 * 
 * Filter template that allows restriction to only one specific data type, such as uint32_t. Avoiding floating point arithmetics 
 * can significantly decrease code footprint, especially in embeded devices, such as Arduino or STM32.
 * 
 * If you want to create a filter for integers, with an alpha value of 0.03, you will just do the following:
 *
 *    EMA_T <int> filter(3, 100)
 * 
 */
template <typename T>
class EMA_T {
public:
    /*
    * Creates a filter with a defined initial output.
    */
    EMA_T(T alpha, unsigned int alphaScale);
    /*
    * Creates a filter with a defined initial output.
    */
    EMA_T(T alpha, unsigned int alphaScale, T initialOutput);

    void reset();

    T output();

    /*
    * Specifies a reading value.
    * @returns current output
    */
    T filter(T input);

private:

    void init(T alpha, unsigned int alphaScale, T initialOutput);

    /*
     * Smoothing factor, in range [0,alphaScale]. Higher the value - less smoothing (higher the latest reading impact).
     */
    T alpha;
    T outputScaled;
    unsigned int alphaScale;
    bool hasInitial;
};

#endif /* EMA_T_H_ */
