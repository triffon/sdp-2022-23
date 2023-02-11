#include <iostream>
#include <vector>
#include <unordered_map>

// count different character in word/sentence/string
// "lorem ipsum is simply dummy text of the printing"
// e - 3
// f
// g
// l - 2
void printCharacterOccurences(std::string str)
{
    // with array
    int charOccurencesArray[256] = {0};
    for (char c : str)
    {
        charOccurencesArray[(int)c]++;
    }
    for (int i = 0; i < 256; i++)
    {
        if (charOccurencesArray[i] > 0)
        {
            std::cout << ((char)i) << ": " << charOccurencesArray[i] << std::endl;
        }
    }

    std::cout << "====================================" << std::endl;

    // with map
    std::unordered_map<char, int> charOccurences;
    for (char c : str)
    {
        if (charOccurences.find(c) != charOccurences.end())
        { // element is in the map
            charOccurences[c]++;
        }
        else
        { // element is not in the map
            charOccurences[c] = 1;
        }
    }

    std::unordered_map<char, int>::iterator iter = charOccurences.begin();
    while (iter != charOccurences.end())
    {
        std::pair<char, int> x = *iter;
        std::cout << x.first << ": " << x.second << std::endl;
        iter++;
    }
}

// count words
// lorem ipsum is simply dummy text of the printing and typesetting industry. lorem ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. it has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. it was popularised in the 1960s with the release of letraset sheets containing lorem ipsum passages, and more recently with desktop publishing software like aldus pagemaker including versions of lorem ipsum.

//
// Maps as configuration
//  - day of week names
//  - short day name to long day name
std::string fullDayOfWeek(std::string shortDayOfWeek)
{
    std::unordered_map<std::string, std::string> shortToFullDayOfWeek = {
        {"MON", "MONDAY"},
        {"TUE", "TUESDAY"},
        {"WED", "WEDNESDAY"},
        {"THU", "THURSDAY"},
        {"FRI", "FRIDAY"},
        {"SAT", "SATURDAY"},
        {"SUN", "SUNDAY"},
    };
    return shortToFullDayOfWeek[shortDayOfWeek];
}

// Group by
// [SoldItem]
//      productId, sum(Quantity), SUM(Quantity * UnitPrice)
//      Quantity
//      UnitPrice
//

// Game of life (set, map, array)

int main()
{
    printCharacterOccurences("lorem ipsum is simply dummy text of the printing");
    std::cout << fullDayOfWeek("MON") << std::endl;
    return 0;
}
