#include<iostream>
#include<vector>

void merge(std::vector<int>& arr, size_t start, size_t middle, size_t end) {
    std::vector<int> leftPart, rightPart;
    size_t leftPartSize = middle - start + 1;
    size_t rightPartSize = end - middle;
    int i, j, k;

    for(i = 0; i < leftPartSize; i++) {
        leftPart.push_back(arr[start + i]);
    }

    for(j = 0; j < rightPartSize; j++) {
        rightPart.push_back(arr[middle + 1 + j]);
    }

    i = 0, j = 0, k = start;

    while(i < leftPartSize && j < rightPartSize) {
        if(leftPart[i] < rightPart[j]) {
            arr[k] = leftPart[i++];
        } else {
            arr[k] = rightPart[j++];
        }
        k++;
    }

    while(i < leftPartSize) {
        arr[k++] = leftPart[i++];
    }

    while(j < rightPartSize) {
        arr[k++] = rightPart[j++];
    }
}

void mergeSplitSort(std::vector<int>& arr, size_t start, size_t end) {
    if( start >= end) {
        return;
    }
    size_t middle = (end + start) / 2;
    mergeSplitSort(arr, start, middle);
    mergeSplitSort(arr, middle + 1, end);
    merge(arr, start, middle, end);
}

void mergeSort(std::vector<int>& arr) {
    mergeSplitSort(arr, 0, arr.size()-1);
}

int main() {
    std::vector<int> A = { 1,10,15,2,23,45, 3, 21 };
    mergeSort(A);
    for(int element: A) {
        std::cout << element << ' ';
    }
    return 0;
}