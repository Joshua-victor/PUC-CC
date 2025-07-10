#include <iostream>
#include <string>

double getDouble() {
    std::string input;
    std::getline(std::cin, input);

    try {
        double value = std::stod(input);
        return value;
    } catch (const std::invalid_argument& e) {
        return 0.0;
    } catch (const std::out_of_range& e) {
        return 0.0;
    }
}

int main() {
    double result = getDouble();
    std::cout << "Valor real: " << result << std::endl;
    return 0;
}
