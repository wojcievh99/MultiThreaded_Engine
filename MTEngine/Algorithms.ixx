export module Algorithms;

import Globals;

std::string operatorOrder = "-+/*^";
std::set<char> opt{ '+', '-', '*', '/', '^' };

export float compute(std::string formula, float x) {
    std::vector<float> digits; std::vector<char> operators;

    std::string subStr = "";
    for (size_t i = 0; i < formula.size(); i++) {
        if (!opt.contains(formula[i])) {
            if (formula[i] != 'x')
                subStr += formula[i];
            else
                subStr += std::to_string(x);
        }
        else {
            if (!subStr.empty())
                digits.push_back(std::stof(subStr));
            operators.push_back(formula[i]);
            subStr = "";
        }
    }
    digits.push_back(std::stof(subStr));

    for (size_t i = operatorOrder.size(); i--;) {
        for (size_t o = 0; o < operators.size(); o++) {
            if (operators[o] == operatorOrder[i]) {

                float result = 0;
                switch (operators[o])
                {
                case '^':
                    result = pow(digits[o], digits[o + 1]);
                    digits.erase(digits.begin() + o); digits.erase(digits.begin() + o);
                    operators.erase(operators.begin() + o);
                    digits.emplace(digits.begin() + o, result);
                    break;
                case '*':
                    result = digits[o] * digits[o + 1];
                    digits.erase(digits.begin() + o); digits.erase(digits.begin() + o);
                    operators.erase(operators.begin() + o);
                    digits.emplace(digits.begin() + o, result);
                    break;
                case '/':
                    result = digits[o] / digits[o + 1];
                    digits.erase(digits.begin() + o); digits.erase(digits.begin() + o);
                    operators.erase(operators.begin() + o);
                    digits.emplace(digits.begin() + o, result);
                    break;
                case '+':
                    result = digits[o] + digits[o + 1];
                    digits.erase(digits.begin() + o); digits.erase(digits.begin() + o);
                    operators.erase(operators.begin() + o);
                    digits.emplace(digits.begin() + o, result);
                    break;
                case '-':
                    if (digits.size() > 1) {
                        result = digits[o] - digits[o + 1];
                        digits.erase(digits.begin() + o); digits.erase(digits.begin() + o);
                        operators.erase(operators.begin() + o);
                    }
                    else {
                        result = digits[o] * -1;
                        digits.erase(digits.begin() + o);
                        operators.erase(operators.begin() + o);
                    }
                    digits.emplace(digits.begin() + o, result);
                    break;
                default:
                    break;
                }
            }
        }
    }

    return digits[0];
}