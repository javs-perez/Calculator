//
// Created by xavip on 4/11/2018.
//

#include <functional>
#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <tuple>
#include <math.h>
#include "Token.h"
#include "shuntingyard.h"


std::deque<Token> exprToTokens(const std::string &expr) {
    std::deque<Token> tokens;

    for(const auto* p = expr.c_str(); *p; ++p) {
        if(isdigit(*p)) {
            const auto* b = p;
            for(; isdigit(*p); ++p) {
                ;
            }
            const auto s = std::string(b, p);
            tokens.push_back(Token { Token::Type::Number, s });
            --p;
        } else {
            Token::Type t = Token::Type::Unknown;
            int pr = -1;            // precedence
            bool ra = false;        // rightAssociative
            switch(*p) {
                default:                                    break;
                case '(':   t = Token::Type::LeftParen;     break;
                case ')':   t = Token::Type::RightParen;    break;
                case '^':   t = Token::Type::Operator;      pr = 4; ra = true;  break;
                case '*':   t = Token::Type::Operator;      pr = 3; break;
                case '/':   t = Token::Type::Operator;      pr = 3; break;
                case '+':   t = Token::Type::Operator;      pr = 2; break;
                case '-':   t = Token::Type::Operator;      pr = 2; break;
                case 'r':   t = Token::Type::Operator;      pr = 4; ra = true; break;
                case 't':   t = Token::Type::Space;         break;
                case ' ':   t = Token::Type::Space;         break;
            }
            auto tokenStr = std::string(1, *p);
            if(tokenStr == "r") {
                tokens.push_back(Token {t, "rt", pr, ra});
            } else {
                tokens.push_back(Token {t,tokenStr, pr, ra});
            }
        }
    }

    return tokens;
}

std::tuple<std::deque<Token>, bool> shuntingYard(const std::deque<Token> &tokens) {
    std::deque<Token> queue;
    std::vector<Token> stack;
    bool error = false;

    // While there are tokens to be read:
    for(auto token : tokens) {
        // Read a token
        switch(token.type) {
            case Token::Type::Number:
                // If the token is a number, then add it to the output queue
                queue.push_back(token);
                break;

            case Token::Type::Operator:
            {
                // If the token is operator, o1, then:
                const auto o1 = token;

                // while there is an operator token,
                while(!stack.empty()) {
                    // o2, at the top of stack, and
                    const auto o2 = stack.back();

                    // either o1 is left-associative and its precedence is
                    // *less than or equal* to that of o2,
                    // or o1 if right associative, and has precedence
                    // *less than* that of o2,
                    if((! o1.rightAssociative && o1.precedence <= o2.precedence)
                       ||  (  o1.rightAssociative && o1.precedence <  o2.precedence)) {
                        // then pop o2 off the stack,
                        stack.pop_back();
                        // onto the output queue;
                        queue.push_back(o2);

                        continue;
                    }

                    // @@ otherwise, exit.
                    break;
                }

                // push o1 onto the stack.
                stack.push_back(o1);
            }
                break;

            case Token::Type::LeftParen:
                // If token is left parenthesis, then push it onto the stack
                stack.push_back(token);
                break;

            case Token::Type::RightParen:
                // If token is right parenthesis:
            {
                bool match = false;
                while(! stack.empty()) {
                    // Until the token at the top of the stack
                    // is a left parenthesis,
                    const auto tos = stack.back();
                    if(tos.type != Token::Type::LeftParen) {
                        // pop operators off the stack
                        stack.pop_back();
                        // onto the output queue.
                        queue.push_back(tos);
                    }

                    // Pop the left parenthesis from the stack,
                    // but not onto the output queue.
                    stack.pop_back();
                    match = true;
                    break;
                }

                if(!match && stack.empty()) {
                    // If the stack runs out without finding a left parenthesis,
                    // then there are mismatched parentheses.
                    printf("RightParen error (%s)\n", token.str.c_str());
                    error = true;
                }
            }
                break;
            case Token::Type::Space:
                break;
            default:
                printf("\nThere was an error with your input (%s)\n", token.str.c_str());
                error = true;
        }

//        debugReport(token, queue, stack);
    }

    // When there are no more tokens to read:
    //   While there are still operator tokens in the stack:
    while(! stack.empty()) {
        // If the operator token on the top of the stack is a parenthesis,
        // then there are mismatched parentheses.
        if(stack.back().type == Token::Type::LeftParen) {
            printf("Mismatched parentheses error\n");
            error = true;
        }

        // Pop the operator onto the output queue.
        queue.push_back(std::move(stack.back()));
        stack.pop_back();
    }

    // return queue and error if there were any
    return std::make_tuple(queue, error);
}

std::ostream &operator<<(std::ostream &os, const Token &token) {
    os << token.str;
    return os;
}

