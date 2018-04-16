//
// Created by xavip on 4/15/2018.
//

#include "CalculatorTests.h"
#include "shuntingyard.h"
#include "calculator.h"

template<class T>
int printResults(std::string expr, float expected_result, T value);

float runTest(std::string expr);

int CalculatorTests::test0() {
    std::string expr = "10 - (8/2)";
    int expected_result = 6;
    float value = runTest(expr);

    return printResults(expr, expected_result, value);
};

int CalculatorTests::test1() {
    std::string expr = "2 * (10-6)";
    int expected_result = 8;
    float value = runTest(expr);

    return printResults(expr, expected_result, value);
};

int CalculatorTests::test2() {
    std::string expr = "8 + 4 * ( 9 - 6)";
    int expected_result = 20;
    float value = runTest(expr);

    return printResults(expr, expected_result, value);
};

int CalculatorTests::testingNoParens() {
    std::string expr = "1 / 6 + 5 / 6";
    int expected_result = 1;
    float value = runTest(expr);

    return printResults(expr, expected_result, value);
};

int CalculatorTests::testingWoSpaces() {
    std::string expr = "5*(3-2)";
    int expected_result = 5;
    float value = runTest(expr);

    return printResults(expr, expected_result, value);
};

int CalculatorTests::test5() {
    std::string expr = "12/2+3/2";
    float expected_result = 7.5;
    float value = runTest(expr);

    return printResults(expr, expected_result, value);
};

int CalculatorTests::testingExponents() {
    std::string expr = "12/2+3^2";
    float expected_result = 15;
    float value = runTest(expr);

    return printResults(expr, expected_result, value);
};

int CalculatorTests::testingSquareRoot() {
    std::string expr = "(7*5)+2rt9";
    float expected_result = 38;
    float value = runTest(expr);

    return printResults(expr, expected_result, value);
}

int CalculatorTests::testingFloatingNums() {
    std::string expr = "12.5 * 2 - (8.4/2)";
    float expected_result = 20.8;
    float value = runTest(expr);

    return printResults(expr, expected_result, value);
};


template<class T>
int printResults(std::string expr, float expected_result, T value) {
    printf("Expression: ");
    std::cout << expr << "\n";
    printf("Expected result: %.2f\n", expected_result);
    printf("Calculated result: %.2f\n", value);
    if (value == expected_result) {
        printf("Test Result: SUCCESS!\n\n");
        return 0;
    } else {
        printf("Test Result: FAILURE\n\n");
        return 1;
    }
}

float runTest(std::string expr) {
    const auto tokens = exprToTokens(expr);
    auto shunting_yard_result = shuntingYard(tokens);
    auto queue = std::get<0>(shunting_yard_result);
    auto result = calculateResult(queue);
    auto value = std::get<0>(result);
    return value;
}

void CalculatorTests::run() {
    int failures = 0;

    failures += CalculatorTests::test0();
    failures += CalculatorTests::test1();
    failures += CalculatorTests::test2();
    failures += CalculatorTests::testingNoParens();
    failures += CalculatorTests::testingWoSpaces();
    failures += CalculatorTests::test5();
    failures += CalculatorTests::testingExponents();
    failures += CalculatorTests::testingSquareRoot();
    failures += CalculatorTests::testingFloatingNums();

    printf("There were %d failures.\n", failures);
    if (failures > 0) {
        printf("Some tests are failing!\n");
    } else {
        printf("Congratulations, all tests are passing!\n");
    }
}


