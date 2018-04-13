//
// Created by xavip on 4/11/2018.
//

#include "Token.h"

Token::Token(Token::Type t, const std::string &s, int prec, bool ra)
        : type { t }, str ( s ), precedence { prec }, rightAssociative { ra }
{}

Token::Token(Token::Type type) : type(type) {}