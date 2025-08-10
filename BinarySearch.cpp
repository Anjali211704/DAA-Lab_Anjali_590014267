#include <iostream>
#include <vector>
#include <chrono> // for measuring execution time
using namespace std;
using namespace chrono;

// 🔍 Binary Search function using low and high
int binarySearch(const vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;

    // Loop until the search space is exhausted
    while (low <= high) {
        int mid = low + (high - low) / 2; // avoid overflow

        // Check if middle element is the target
        if (arr[mid] == target) return mid;

        // If target is greater, ignore left half
        else if (arr[mid] < target) low = mid + 1;

        // If target is smaller, ignore right half
        else high = mid - 1;
    }

    return -1; // target not found
}

// 🧪 Function to run a test case and measure time
void runTest(const vector<int>& arr, int target, const string& caseType) {
    // Start timing
    auto start = high_resolution_clock::now();

    // Run Binary Search
    int result = binarySearch(arr, target);

    // End timing
    auto end = high_resolution_clock::now();

    // Calculate duration in nanoseconds
    auto time = duration_cast<nanoseconds>(end - start).count();

    // Print test case details
    cout << caseType << " | Size: " << arr.size()
         << " | Target: " << target
         << " | Found at: " << result
         << " | Time (ns): " << time << endl;
}

int main() {
    //Best-case scenarios: target is in the middle
    runTest({1, 2, 3, 4, 5}, 3, "Best");               // middle element
    runTest({10, 20, 30, 40, 50, 60}, 30, "Best");     // middle of even-sized array
    runTest({-10, -5, 0, 5, 10}, 0, "Best");           // negative values
    runTest({1}, 1, "Best");                           // single-element array
    runTest({}, 1, "Best");                            // empty array

    // Worst-case scenarios: target not found or at edges
    runTest({1, 2, 3, 4, 5}, 6, "Worst");              // target not in array
    runTest({1, 2, 3, 4, 5}, 1, "Worst");              // target at beginning
    runTest({1, 2, 3, 4, 5}, 5, "Worst");              // target at end
    runTest({-10, -5, 0, 5, 10}, -15, "Worst");        // target less than min
    runTest({1}, 2, "Worst");                          // single-element, target absent

    // Average-case scenarios: target in random positions
    runTest({1, 2, 3, 4, 5}, 2, "Average");            // near beginning
    runTest({10, 20, 30, 40, 50}, 40, "Average");      // near end
    runTest({-10, -5, 0, 5, 10}, 5, "Average");        // positive target
    runTest({1, 2, 2, 2, 3}, 2, "Average");            // duplicates
    runTest({100, 200, 300, 400, 500}, 300, "Average");// large values

    return 0;
}