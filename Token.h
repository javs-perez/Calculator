//
// Created by xavip on 4/11/2018.
//
#include <iostream>

#ifndef CALCULATOR_TOKEN_H
#define CALCULATOR_TOKEN_H


class Token {
public:
    enum Type {
        Unknown = 0,
        Number,
        Operator,
        LeftParen,
        RightParen,
        Space
    };

    Token(Type t, const std::string& s, int prec = -1, bool ra = false);

    Token(Type type);

    Type type { Type::Unknown };
    std::string str {};
    int precedence { -1 };
    bool rightAssociative { false };

};


#endif //CALCULATOR_TOKEN_H
