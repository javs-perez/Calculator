//
// Created by xavip on 4/15/2018.
//

#include <deque>
#include "Token.h"

#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H


template<class T>
void printQueue(const T& queue);

std::tuple<float, bool> calculateResult(std::deque<Token> &queue);


#endif //CALCULATOR_CALCULATOR_H
