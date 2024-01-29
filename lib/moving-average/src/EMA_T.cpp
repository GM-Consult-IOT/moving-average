#include <EMA_T.h>


// template <typename T>
// EMA_T<T>::EMA_T(T alpha, unsigned int alphaScale) {
//     init(alpha, alphaScale, 0);
//     this->hasInitial = false;
// };

// template <typename T>
// EMA_T<T>::EMA_T(T alpha, unsigned int alphaScale, T initialOutput) {
//     init(alpha, alphaScale, initialOutput);
// };

// template <typename T>
// void EMA_T<T>::init(T alpha, unsigned int alphaScale, T initialOutput) {
//     this->alpha = alpha;
//     this->alphaScale = alphaScale;
//     this->outputScaled = initialOutput * alphaScale;
//     this->hasInitial = true;
// };

// template <typename T>
// void EMA_T<T>::reset() {
//     this->hasInitial = false;
// };

// template <typename T>
// T EMA_T<T>::filter(T input) {
//     if (hasInitial) {
//         outputScaled = alpha * input + (alphaScale - alpha) * outputScaled / alphaScale;
//     } else {
//         outputScaled = input * alphaScale;
//         hasInitial = true;
//     }
//     return output();
// };

// template <typename T>
// T EMA_T<T>::output() {
//     return (outputScaled + alphaScale / 2) / alphaScale;
// };
