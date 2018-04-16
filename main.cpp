#include <functional>
#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <math.h>
#include "shuntingyard.h"
#include "calculator.h"
#include "CalculatorTests.h"


int main() {
    std::string expr;
    std::string run_tests;
    std::string go_again = "n";
    bool error;

    printf("==================================\n");
    printf("Welcome to the Calculator Program!\n");
    printf("==================================\n");

    printf("Would you like to run the tests before calculating? y/n\n");
    std::getline(std::cin, run_tests);
    if (run_tests == "y" || run_tests == "Y"){
        printf("Running calculator tests:\n\n");
        CalculatorTests::run();
    }

    do {
        printf("\n\nPlease enter the expression you would like to calculate:\n");
        printf("> ");

        std::getline(std::cin, expr);
        std::cout << expr;

        const auto tokens = exprToTokens(expr);
        auto shunting_yard_result = shuntingYard(tokens);
        auto queue = std::get<0>(shunting_yard_result);
        error = std::get<1>(shunting_yard_result);
        if (error == true){
            printf("There was an error with your expression. Please try again.\n");
            continue;
        }

        auto result = calculateResult(queue);
        auto value = std::get<0>(result);
        error = std::get<1>(result);

        if (error == false) {
            printf("\n result = %.2f\n", value);
            printf("Would you like to calculate a new expression? y/n\n");
            std::getline(std::cin, go_again);
        } else {
            printf("There was an error with your expression. Please try again.\n");
        }
    } while(error == true || go_again == "y" || go_again == "Y");

    return 0;
}

