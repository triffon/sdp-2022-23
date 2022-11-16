#include <iostream>
#include <vector>
#include "stack/lstack.hpp"
#include "queue/squeue.hpp"
#include "list/llist.hpp"
#include <iostream>
#include <vector>

/*
    # Coding Kata
    Exercise: find the longest string
    Write a function that takes in an array/list of strings and then return the longest one

    eg: longest(["the","quick","brown", "fox", "ate", "my", "chickens"])
    should output
    [chickens]
    If there are multiple longest strings then return them all.

    eg:
    longest(["once", "upon", "a" "time"])
    should output
    [once, upon, time]
*/
std::vector<std::string> longestWords(std::vector<std::string> words)
{
    std::vector<std::string> res;
    for (std::string word : words)
    {
        if (res.empty() || res[0].size() == word.size())
        {
            res.push_back(word);
        }
        else if (res[0].size() < word.size())
        {
            res.clear();
            res.push_back(word);
        }
    }
    return res;
}

/*
    # 739. Daily Temperatures
    https://leetcode.com/problems/daily-temperatures/
    vector<int> dailyTemperatures(vector<int>& temperatures);

    Problem:
    Given a list of daily temperatures, produce a list that, for each day in the input, tells you how many days you would have to wait until a warmer temperature. If there is no future day for which this is possible, put 0 instead.
    For example, given the list temperatures = [73, 74, 75, 71, 69, 72, 76, 73], your output should be [1, 1, 4, 2, 1, 1, 0, 0].
    Note: The length of temperatures will be in the range [1, 30000]. Each temperature will be an integer in the range [30, 100].
*/
std::vector<int> dailyTemperatures(const std::vector<int> &temperatures)
{
    LinkedStack<int> resultInReverse;
    LinkedStack<int> maxes;
    for (int i = temperatures.size() - 1; i >= 0; i--)
    {
        while (!maxes.empty() && temperatures[maxes.peek()] < temperatures[i])
        {
            maxes.pop();
        }
        if (maxes.empty())
        {
            resultInReverse.push(0);
            maxes.push(i);
        }
        else if (temperatures[maxes.peek()] >= temperatures[i])
        {
            resultInReverse.push(maxes.peek() - i);
            maxes.push(i);
        }
    }

    std::vector<int> res;
    while (!resultInReverse.empty())
    {
        res.push_back(resultInReverse.pop());
    }
    return res;
}

/*
    # 2327. Number of People Aware of a Secret
    https://leetcode.com/problems/number-of-people-aware-of-a-secret/
    int peopleAwareOfSecret(int n, int delay, int forget);

    On day 1, one person discovers a secret.
    You are given an integer delay, which means that each person will share the secret with a new person every day, starting from delay days after discovering the secret. You are also given an integer forget, which means that each person will forget the secret forget days after discovering it. A person cannot share the secret on the same day they forgot it, or on any day afterwards.

    Given an integer n, return the number of people who know the secret at the end of day n.
    Since the answer may be very large, return it modulo 109 + 7.

    Example 1:
    Input: n = 6, delay = 2, forget = 4
    Output: 5

    Explanation:
    Day 1: Suppose the first person is named A. (1 person)
    Day 2: A is the only person who knows the secret. (1 person)
    Day 3: A shares the secret with a new person, B. (2 people)
    Day 4: A shares the secret with a new person, C. (3 people)
    Day 5: A forgets the secret, and B shares the secret with a new person, D. (3 people)
    Day 6: B shares the secret with E, and C shares the secret with F. (5 people)

    Example 2:
    Input: n = 4, delay = 1, forget = 3
    Output: 6

    Explanation:
    Day 1: The first person is named A. (1 person)
    Day 2: A shares the secret with B. (2 people)
    Day 3: A and B share the secret with 2 new people, C and D. (4 people)
    Day 4: A forgets the secret. B, C, and D share the secret with 3 new people. (6 people)


    Constraints:
        2 <= n <= 1000
        1 <= delay < forget <= n
*/

template <typename T>
int size(StaticQueue<T> q)
{
    int count = 0;
    while (!q.empty())
    {
        q.dequeue();
        count++;
    }
    return count;
}

int peopleAwareOfSecret(int days, int delay, int forget)
{
    StaticQueue<std::pair<int, int>> ppl;
    ppl.enqueue(std::pair<int, int>(delay, forget));

    for (int day = 1; day < days; day++)
    {
        StaticQueue<std::pair<int, int>> nextDayPpl;
        while (!ppl.empty())
        {
            std::pair<int, int> p = ppl.dequeue();
            p.first--;
            p.second--;

            if (p.second <= 0)
            {
                continue;
            }
            nextDayPpl.enqueue(p);
            if (p.first <= 0)
            {
                nextDayPpl.enqueue(std::pair<int, int>(delay, forget));
            }
        }
        ppl = nextDayPpl;
    }
    return size(ppl);
}

struct SecretSpread
{
    int delay;
    int forget;
    int numberOfPeople;

    void aDayHasPassed()
    {
        delay--;
        forget--;
    }

    bool hasForgottenSecret()
    {
        return forget <= 0;
    }

    bool willShareSecret()
    {
        return delay <= 0;
    }
};

int peopleAwareOfSecretv2(int days, int delay, int forget)
{
    StaticQueue<SecretSpread> ppl;
    ppl.enqueue(SecretSpread({delay, forget, 1}));

    for (int day = 1; day < days; day++)
    {
        StaticQueue<SecretSpread> nextDayPpl;
        SecretSpread newSecretSpread = {delay, forget, 0};
        while (!ppl.empty())
        {
            SecretSpread p = ppl.dequeue();
            p.aDayHasPassed();

            if (p.hasForgottenSecret())
            {
                continue;
            }
            nextDayPpl.enqueue(p);
            if (p.willShareSecret())
            {
                newSecretSpread.numberOfPeople += p.numberOfPeople;
            }
        }
        if (newSecretSpread.numberOfPeople > 0)
        {
            nextDayPpl.enqueue(newSecretSpread);
        }
        ppl = nextDayPpl;
    }
    int numberOfPeople = 0;
    while (!ppl.empty())
    {
        numberOfPeople += ppl.dequeue().numberOfPeople;
    }
    return numberOfPeople;
}

template <typename T>
void print(const std::vector<T> &v)
{
    for (T s : v)
    {
        std::cout << s << " ";
    }
    std::cout << std::endl;
}

int main()
{
    // once upon a time --> "once", "upon", "a", "time"
    // select the space
    // ctrl+d x3
    // left arrow
    // ctrl+shift+left
    // "
    // right arrow
    // ,

    // print(longestWords({"the", "quick", "brown", "fox", "ate", "my", "chickens"}));
    // print(longestWords({"once", "upon", "a", "time"}));

    // std::cout << "5 == " << peopleAwareOfSecret(6, 2, 4) << " v2: " << peopleAwareOfSecretv2(6, 2, 4) << std::endl;
    // std::cout << "6 == " << peopleAwareOfSecret(4, 1, 3) << " v2: " << peopleAwareOfSecretv2(4, 1, 3) << std::endl;

    // std::cout << "Expecting to be equal to:" << std::endl;
    // print<int>({1, 1, 4, 2, 1, 1, 0, 0});
    // print(dailyTemperatures({73, 74, 75, 71, 69, 72, 76, 73}));
    return 0;
}
