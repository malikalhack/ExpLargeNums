//(base^exponent) % divider

#include <iostream>
#include <vector>
#include <functional>

void test(
    std::function <uint16_t(uint16_t, uint16_t, uint16_t)>,
    uint16_t, uint16_t, uint16_t, uint16_t
);
uint16_t calculate(uint16_t, uint16_t, uint16_t);
std::function <uint16_t(uint16_t, uint16_t, uint16_t)> test_function = &calculate;

int main() {
    test(test_function, 2,     5,   100,     7);
    test(test_function, 4,     3,    90,     5);
    test(test_function, 0,     5,   100,     1);
    test(test_function, 0,     5,   100,     5);
    test(test_function, 0,     0,   100,     7);
    test(test_function, 1,     5,     0,     7);
    test(test_function, 0,     5,   100,     0);
    test(test_function, 3, 32767, 32767,     5);
    test(test_function, 1, 65535, 65535, 65534);
    getchar();
    return 0;
}

void test(
    
    std::function <uint16_t(uint16_t, uint16_t, uint16_t)> func,
    uint16_t expected_result,
    uint16_t base,
    uint16_t exponent,
    uint16_t divider
) {
    static uint16_t counter = 0;
    std::cout << "Started test #" << ++counter << std::endl;
#ifdef _DEBUG
    std::cout << "--------------------------------------------------\n";
#endif
    uint16_t result = func(base, exponent, divider);
#ifdef _DEBUG
    std::cout << "--------------------------------------------------\n";
#endif
    if (result == expected_result) {
        std::cout << "TEST PASSED" << std::endl;
    }
    else {
        std::cout << "TEST FAILED" << std::endl;
        std::cout << "Actual result is " << result << std::endl;
    }
    std::cout << std::endl;
}

uint16_t calculate(uint16_t base, uint16_t exponent, uint16_t mod) {
    uint16_t result = 0u;
    if (mod) {
        if (base && mod != 1) {
            result = 1u;
            if (exponent) {
                uint8_t n = 0u; //max value is 16
                uint16_t temp = exponent;
                uint32_t temp_result;
                while (temp) {
                    temp >>= 1u;
                    n++;
                }
#ifdef _DEBUG
                std::cout << "Number of elements is " << +n << std::endl;
#endif // _DEBUG

                std::vector<uint32_t> computation_array(n, 0);
                computation_array.at(0) = (uint32_t)base;
                if (base != mod) {
                    for (size_t it = 1; it < computation_array.size(); it++) {
                        temp_result = computation_array.at(it - 1);
                        computation_array.at(it) = (temp_result * temp_result) % mod;
                    }
                }
#ifdef _DEBUG
                for (auto it : computation_array) { std::cout << it << "  "; }
                std::cout << std::endl;
#endif // _DEBUG

                temp = exponent;
                temp_result = 1;
                for (auto it : computation_array) {
                    if (temp & 0x01) {
                        temp_result *= it;
                    }
                    temp >>= 1;
                }
#ifdef _DEBUG
                std::cout << "Intermediate result is " << temp_result << std::endl;
#endif // _DEBUG

                result = temp_result % mod;
            }
        }
    }
    else {
        std::cout << "ATTENTION! Division by zero" << std::endl;
    }
    return result;
}
