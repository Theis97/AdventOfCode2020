#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Utilities/StringUtils.h"

const bool partTwo = true;

long long Evaluate(const std::string& expression, int start, int end) {
    long long accumulator = -1;
    char operation = 0;

    for (int i = start; i < end; i++) {
        char c = expression[i];
        if (c == '(') {
            int closeParenLoc = i + 1;
            int otherParenCount = 0;
            while (closeParenLoc < expression.length()) {
                if (expression[closeParenLoc] == ')') {
                    if (otherParenCount == 0) {
                        break;
                    }
                    else {
                        otherParenCount--;
                    }
                }
                if (expression[closeParenLoc] == '(') {
                    otherParenCount++;
                }
                closeParenLoc++;
            }
            long long value = Evaluate(expression, i + 1, closeParenLoc);
            if (accumulator == -1) {
                accumulator = value;
            }
            else {
                accumulator = operation == '+' ? accumulator + value : accumulator * value;
            }
            i = closeParenLoc;
        }
        else if (c == '+' || c == '*') {
            operation = c;
            if (partTwo && c == '*') {
                return abs(accumulator * Evaluate(expression, i + 1, end));
            }
        }
        else {
            int value = c - '0';
            if (accumulator == -1) {
                accumulator = value;
            }
            else {
                accumulator = operation == '+' ? accumulator + value : accumulator * value;
            }
        }
    }
    return accumulator;
}

int main() {
    std::ifstream inputFile;
    inputFile.open("day18.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return 0;
    }

    long long sum = 0;

    std::string line;
    while (std::getline(inputFile, line)) {
        // Remove spaces
        std::vector<std::string> tokens = TokenizeString(line, ' ');
        std::string problem = "";
        for (auto &t : tokens) {
            problem += t;
        }

        long long answer = Evaluate(problem, 0, problem.length());
        sum += answer;
        std::cout << answer << "\n";
    }

    std::cout << "Sum of all answers: " << sum << "\n";
}