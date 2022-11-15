#include <iostream>
#include <stack>
#include <string>
using std::cin, std::cout, std::endl, std::stack, std::string;

// проверка дали скобата е отворена
bool is_open(const char bracket) {
    return bracket == '(' || bracket == '[' || bracket == '{';
}

// проверка дали отварящата и затварящата скоба съвпадат
bool is_pair(const char open, const char close) {
    return (open == '(' && close == ')') || 
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

// проверка дали дадена поредица скоби е балансирана
bool check_sequence(const string& sequence) {
    stack<char> open_brackets;

    for(int i = 0; i < sequence.size(); i++) {
        char bracket = sequence[i];
        
        // ако скобата е отваряща, отива на върха на стека
        if(is_open(bracket)) open_brackets.push(bracket);
        // ако скобата е затваряща и съвпада с тази от върха на стека,
        // върхът на стека бива премахнат
        else if(is_pair(open_brackets.top(), bracket)) {
            open_brackets.pop();
        } else return false;    // ако скобите не съвпадат, цялата редица е небалансирана
    }

    // ако стекът е празен, редицата е балансирана
    return open_brackets.empty();
}

int main()
{
    string sequence;
    cin >> sequence;
    cout << (check_sequence(sequence) ? "Yes" : "No") << endl;

    return 0;
}