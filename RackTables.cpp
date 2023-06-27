#include <iostream>
#include <string>
#include <vector>
#include <regex>

bool isValidQuery(const std::string& query) {
    std::stack<char> brackets;
    bool isValid = true;
    bool lastOp = true;
    bool containsOp = false;

    for (char c : query) {
        if (c == '{' || c == '[' || c == '(') {
            brackets.push(c);
            lastOp = c != '(';
        } else if (c == '}' || c == ']' || c == ')') {
            if (brackets.empty() || 
                (c == '}' && brackets.top() != '{') || 
                (c == ']' && brackets.top() != '[') || 
                (c == ')' && brackets.top() != '(')) {
                isValid = false;
                break;
            }
            brackets.pop();
            lastOp = false;
        } else if (std::isalpha(c)) {
            if (!lastOp) {
                isValid = false;
                break;
            }
            lastOp = false;
        } else if (!std::isspace(c)) {
            containsOp = true;
            if (lastOp) {
                isValid = false;
                break;
            }
            lastOp = true;
        }
    }

    if (!brackets.empty() || lastOp || !containsOp) {
        isValid = false;
    }

    return isValid;
}

int main() {
    int n;
    std::cin >> n;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<std::string> results;
    for (int i = 0; i < n; ++i) {
        std::string query;
        std::getline(std::cin, query);
        results.push_back(isValidQuery(query) ? "valid" : "invalid");
    }

    for (const std::string& result : results) {
        std::cout << result << '\n';
    }

    return 0;
}
