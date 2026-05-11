#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class DynamicStack {
        private:
                vector<char> stackData;

        public:
                void push(char val) {
                        stackData.push_back(val);
                }

                void pop() {
                        if (!isEmpty()) {
                                stackData.pop_back();
                        }
                }

                char peek() const {
                        if (!isEmpty()) {
                                return stackData.back();
                        }
                        return '\0';
                }

                bool isEmpty() const {
                        return stackData.empty();
                }

                string reverseWords(string sentence) {
                        string result = "";
                        stringstream ss(sentence);
                        string word;

                        while (ss >> word) {
                                for (char ch : word) {
                                        push(ch);
                                }

                                while (!isEmpty()) {
                                        result += peek();
                                        pop();
                                }

                                result += " ";
                        }

                        if (!result.empty()) {
                                result.pop_back();
                        }

                        return result;
                }
};

int main() {
        DynamicStack myStack;
        string input;

        cout << "Enter a sentence: ";
        getline(cin, input);

        string reversed = myStack.reverseWords(input);

        cout << "Processed Sentence: " << reversed << endl;

        return 0;
}
