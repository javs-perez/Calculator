//
// Created by xavip on 4/11/2018.
//
#include <functional>
#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <math.h>
#include "Token.h"

#ifndef CALCULATOR_SHUNTINGYARD_H
#define CALCULATOR_SHUNTINGYARD_H

std::deque<Token> exprToTokens(const std::string& expr);
std::ostream& operator<<(std::ostream& os, const Token& token);
std::deque<Token> shuntingYard(const std::deque<Token>& tokens);




#endif //CALCULATOR_SHUNTINGYARD_H
