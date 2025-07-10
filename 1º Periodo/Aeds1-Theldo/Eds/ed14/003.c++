#include <iostream>
#include <string>
#include <algorithm>

bool getBoolean() {
    std::string input;
    std::getline(std::cin, input);

    std::transform(input.begin(), input.end(), input.begin(), ::toupper);

    if (input == "TRUE" || input == "T" || input == "1") {
        return true;
    } else if (input == "FALSE" || input == "F" || input == "0") {
        return false;
    } else {
        return false;
    }
}

int main() {
    bool result = getBoolean();
    std::cout << "Valor lógico: " << std::boolalpha << result << std::endl;
    return 0;
}
