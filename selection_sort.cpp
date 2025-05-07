#include <iostream>
#include <vector>
using namespace std;

// Greedy Selection Sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();

    // Move the boundary of the unsorted subarray
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;

        // Greedy choice: find the minimum element in the unsorted part
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // Swap the found minimum element with the first element of the unsorted part
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

// Utility function to print the array
void printArray(const vector<int>& arr) {
    for (int val : arr)
        cout << val << " ";
    cout << endl;
}

int main() {
    vector<int> data = {64, 25, 12, 22, 11};

    cout << "Original array: ";
    printArray(data);

    selectionSort(data);

    cout << "Sorted array: ";
    printArray(data);

    return 0;
}
