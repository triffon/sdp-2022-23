#include <iostream>
#include <stack>
using std::cin, std::cout, std::endl, std::stack;

// функция за обръщане на стек
void reverse_stack(stack<int>& s) {
    stack<int> buffer;

    while(!s.empty()) {
        buffer.push(s.top());
        s.pop();
    }

    s = buffer;
}

// функция, отсяваща оцелелите цветя на поредния ден
// връща True, ако има убито цвете, и False в противен случай
bool kill_plants(stack<int>& flowers) {
    bool there_is_killed_plant = false;

    stack<int> next_day;
    while(!flowers.empty()) {
        int x = flowers.top();
        flowers.pop();

        // ако цветето е последно или не е с повече пестициди от съседа си отляво,
        // то го добавяме в стека
        if(flowers.empty() || x <= flowers.top()) {
            next_day.push(x);
        } 
        // в противен случай, цветето умира
        else there_is_killed_plant = true;
    }

    // цветята, останали за следващия ден, се присвояват в обратен ред на работния стек
    reverse_stack(next_day);
    flowers = next_day;

    return there_is_killed_plant;
}


int main()
{
    stack<int> flowers;
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        flowers.push(x);
    }

    int day = 0;
    while(kill_plants(flowers)) day++;

    cout << day << endl;

    return 0;
}