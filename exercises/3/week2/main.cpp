#include <vector>
#include <iostream>

bool areMatrixesSameSize(const std::vector<std::vector<int>>& a, const std::vector<std::vector<int>>& b) {
    if (a.size() != b.size()) {
        return false;
    }
    return a[0].size() != b[0].size();
}

bool isMatrix(const std::vector<std::vector<int>>& a) {
    if (0 == a.size()) {
        return true;
    }
    const int expectedSize = a[0].size();
    for (int i = 1; i < a.size(); i++) {
        if (a[i].size() != expectedSize) {
            return false;
        }
    }
    return true;
}

bool hasValidSize(const std::vector<std::vector<int>>& a, const std::vector<std::vector<int>>& b) {
    return isMatrix(a) && isMatrix(b) && areMatrixesSameSize(a, b);
}

std::vector<std::vector<int>> sumMatrix(
    const std::vector<std::vector<int>>& a, 
    const std::vector<std::vector<int>>& b) {
    if (!hasValidSize(a, b)) {
        throw std::invalid_argument("");
    }

    std::vector<std::vector<int>> result;
    // for (std::vector<std::vector<int>>::const_iterator ita = a.cbegin(), itb = b.cbegin();
    //         ita != a.cend(); ita++, itb++) {
    //     std::vector<int> row;
    //     for (std::vector<int>::const_iterator ja = (*ita).cbegin(), jb = (*itb).cbegin();
    //         ja != (*ita).cend(); ja++, jb++) {
    //             row.push_back(*ja + *jb);
    //     }
    //     result.push_back(row);
    // }
    
    const int rowSize = a.size();
    const int colSize = a[0].size();

    for (int i = 0; i < rowSize; i++) {
        std::vector<int> row;
        for (int j = 0; j < colSize; j++) {
            // row.push_back(a[i][j] + b[i][j]);
            row.push_back(a.at(i).at(j) + b.at(i).at(j));
        }
        result.push_back(row);
    }
    return result;
}


// a        b
// (1 0)   (10 20)   (11 20)
// (2 5) + (22 55) = (24 60)

int main() {
    // https://cplusplus.com/reference/vector/vector/
    // https://en.cppreference.com/w/cpp/container/vector
    std::vector<int> ints;
    ints.push_back(5);
    ints.push_back(6);
    ints.push_back(7);
    ints.push_back(8);
    ints.push_back(9);

    std::cout << "1: ===================" << std::endl;

    for (int i = 0; i < ints.size(); i++) {
        std::cout << ints[i] << std::endl;
    }

    std::cout << "2: ===================" << std::endl;

    for (int i = 0; i < ints.size(); i++) {
        std::cout << ints.at(i) << std::endl;
    }

    std::cout << "3: ===================" << std::endl;
    std::vector<int>::iterator it = ints.begin();
    while (it != ints.end()) {
        std::cout << *it << std::endl;
        it++;
    }
    
    ints.insert(ints.begin() + 3, 123);

    std::cout << "4: ===================" << std::endl;
    for (std::vector<int>::iterator it = ints.begin(); 
        it != ints.end(); it++) {
        *it *= 10;
        std::cout << *it << std::endl;
    }

    // PLEEEEEASE, don't do that
    // std::cout << "4.1: ===================" << std::endl;
    // for (std::vector<int>::iterator it = ints.end(); 
    //     it != ints.begin(); it--) {
    //     std::cout << *(it-1) << std::endl;
    // }

    std::cout << "5: ===================" << std::endl;
    for (std::vector<int>::reverse_iterator it = ints.rbegin(); 
        it != ints.rend(); it++) {
        *it *= 20;
        std::cout << *it << std::endl;
    }

    std::cout << "6: ===================" << std::endl;
    for (std::vector<int>::const_iterator it = ints.cbegin(); 
        it != ints.cend(); it++) {
        std::cout << *it << std::endl;
    }

   std::cout << "7: ===================" << std::endl;
    for (std::vector<int>::const_reverse_iterator it = ints.crbegin(); 
        it != ints.crend(); it++) {
        std::cout << *it << std::endl;
    }

    // for (auto it = ints.begin(); 
    //     it != ints.end(); it++) {
    //     std::cout << *it << std::endl;
    // }

    

    // ints[4] = 10000;
    // std::cout << ints[4] << std::endl;
    // std::cout << ints.size() << std::endl;
    // ints[10] = 13131;
    // std::cout << ints[10] << std::endl;
    // std::cout << ints.size() << std::endl;
    // std::cout << ints.capacity() << std::endl;

    // ints.pop_back();
    // std::cout << ints.size() << std::endl;
    // std::cout << ints.at(10) << std::endl;




    // std::vector<std::vector<int>> ints2;

    return 0;
}
