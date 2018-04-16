//
// Created by xavip on 4/15/2018.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <math.h>
#include <tuple>
#include "Token.h"
#include "shuntingyard.h"
#include "calculator.h"


std::tuple<float, bool> calculateResult(std::deque<Token> &queue) {
    std::vector<float> stack;
    bool error = false;

    while(! queue.empty()) {

        const auto token = queue.front();
        queue.pop_front();
        switch (token.type) {
            case Token::Type::Number:
                stack.push_back(std::stof(token.str));
                break;
            case Token::Type::Operator: {
                const auto rhs = stack.back();
                stack.pop_back();
                const auto lhs = stack.back();
                stack.pop_back();

                switch (token.str[0]) {
                    default:
                        printf("Operator error [%s]\n", token.str.c_str());
                        error = true;
                        break;
                    case '^':
                        stack.push_back(static_cast<float>(pow(lhs, rhs)));
                        break;
                    case 'r':
                        stack.push_back(static_cast<float>(pow(rhs, 1.0 / lhs)));
                        break;
                    case '*':
                        stack.push_back(lhs * rhs);
                        break;
                    case '/':
                        stack.push_back(lhs / rhs);
                        break;
                    case '+':
                        stack.push_back(lhs + rhs);
                        break;
                    case '-':
                        stack.push_back(lhs - rhs);
                        break;
                }
            }
                break;
            default:
                printf("Token error\n");
                error = true;
        }
    }
    return std::make_tuple(stack.back(), error);
}