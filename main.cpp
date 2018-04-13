#include <functional>
#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <math.h>
#include "Token.h"
#include "shuntingyard.h"

template<class T>
void printQueue(const T& queue);

int main() {
    std::string expr;
    std::cout << ">";
    std::getline(std::cin, expr);

    const auto tokens = exprToTokens(expr);
    auto queue = shuntingYard(tokens);
    std::vector<float> stack;

    while(! queue.empty()) {
        std::string op;

        const auto token = queue.front();
        queue.pop_front();
        switch(token.type) {
            case Token::Type::Number:
                stack.push_back(std::stoi(token.str));
                op = "Push " + token.str;
                break;
            case Token::Type::Operator: {
                const auto rhs = stack.back();
                stack.pop_back();
                const auto lhs = stack.back();
                stack.pop_back();

                switch(token.str[0]) {
                    default:
                        printf("Operator error [%s]\n", token.str.c_str());
                        exit(0);
                    case '^':
                        stack.push_back(static_cast<float>(pow(lhs, rhs)));
                        break;
                    case 'r':
                        stack.push_back(static_cast<float>(pow(rhs, 1.0/lhs)));
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
                op = "Push " + std::to_string(lhs) + " " + token.str + " " + std::to_string(rhs);
            }
            break;
            default:
                printf("Token error\n");
                exit(0);
        }
    }

    printf("\n result = %f\n", stack.back());

    return 0;
}

template<class T>
void printQueue(const T &queue) {
    std::ostringstream ossQueue;
    for(const auto& t : queue) {
        ossQueue << " " << t;
    }

    printf("%s\n", ossQueue.str().c_str());
}