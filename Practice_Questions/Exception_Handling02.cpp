#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cassert>

class SafeVector {
private:
    std::vector<int> data;

public:
    // Constructor to initialize with some values
    SafeVector(std::initializer_list<int> list) : data(list) {}

    int at(size_t i) {
        if (i >= data.size()) {
            // Building a descriptive message with the bad index and current size
            std::string msg = "Index Out of Range: Requested " + std::to_string(i) + 
                              ", but Vector size is " + std::to_string(data.size());
            
            throw std::out_of_range(msg);
        }
        return data[i];
    }

    size_t size() const { return data.size(); }
};

// Simple unit test function
void runUnitTest() {
    SafeVector sv = {10, 20, 30}; // Size is 3 (indices 0, 1, 2)
    
    try {
        std::cout << "Testing valid index 1: " << sv.at(1) << std::endl;
        
        std::cout << "Testing invalid index 5..." << std::endl;
        sv.at(5); // This should throw
        
        // If we reach this line, the test failed
        std::cerr << "Unit Test Failed: No exception thrown!" << std::endl;
    } 
    catch (const std::out_of_range& e) {
        std::string message = e.what();
        std::cout << "Caught expected error: " << message << std::endl;

        // Verifying the message contains the expected values
        if (message.find("5") != std::string::npos && message.find("3") != std::string::npos) {
            std::cout << "Unit Test Passed: Message contains correct data." << std::endl;
        } else {
            std::cout << "Unit Test Failed: Message missing index or size info." << std::endl;
        }
    }
}

int main() {
    runUnitTest();
    return 0;
}