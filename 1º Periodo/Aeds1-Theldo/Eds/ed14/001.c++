#include <iostream>
#include <string>

int getInt() {
    std::string input;
    std::getline(std::cin, input);

    try {
        int value = std::stoi(input);
        return value;
    } catch (const std::invalid_argument& e) {
        return -1;
    } catch (const std::out_of_range& e) {
        return -1;
    }
}

int main() {
    int result = getInt();
    std::cout << "Valor inteiro: " << result;
    return 0;
}

