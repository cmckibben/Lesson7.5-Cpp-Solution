#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>



using namespace std;
#define RUNS 1000000
#define SIZE 1000
#define REPEATS 100
#define FILENAME "runtimes.csv"


class Timer
{
public:
    Timer() : beg_(clock_::now()) {}
    void reset() { beg_ = clock_::now(); }
    uint64_t elapsed() const {
        return std::chrono::duration_cast<std::chrono::nanoseconds>
                (clock_::now() - beg_).count(); }

private:
    typedef std::chrono::high_resolution_clock clock_;
    //typedef std::chrono::duration<double, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;
};

/**
 * @return returns the index of the element numToFind in array array.
 * -1 if element not found.
 * @param array array, sorted or not, containing integers
 * @param numToFind integer to find in array
 * @precondition none
 * @postcondition index of numToFind has been returned. -1 has been
 * returned if element not found.
 */
int linearSearch(int *array, int arraysize, int numToFind){
        for(int i = 0; i< arraysize; i++)
            if(array[i]==numToFind) return i;

        return -1;
}

/**
 * @return returns the index of the element numToFind in array array.
 * -1 if element not found.
 * @param array array, sorted or not, containing integers
 * @param numToFind integer to find in array
 * @precondition none
 * @postcondition index of numToFind has been returned. -1 has been
 * returned if element not found.
 */
int binarySearch(int *array, int arraysize, int numToFind){
        int left = 0;
        int right = arraysize-1;
        int middle = 0;

        while(left <= right) {
            middle = (left + right)/2;
            if(numToFind < array[middle])
                right = middle - 1;
            else if( numToFind > array[middle])
                left = middle + 1;
            else return middle;
        }


        return -1;
    }

int main() {
    int testarray[] = {1,2,3,4,5,6,7,8};
    cout << linearSearch(testarray,8, 96) << endl;
    cout << binarySearch(testarray,8, 96) << endl;
//No reason to change anything below this line, but feel free to browse


    cout << "Number of trials: " << RUNS <<endl;
    //unsorted array to search
    int unsortedArray[SIZE];
    for (int i = 0; i < SIZE; i++)
        unsortedArray[i] = (int) ((rand() * 99) + 1);

    int sortedArray[SIZE];
    for (int i = 0; i < SIZE; i++)
        sortedArray[i] = i;
    //for timing
    Timer tmr;
    vector<uint64_t> linearSearchRunTimesSorted;
    vector<uint64_t> binarySearchRunTimesSorted;
    vector<uint64_t> linearSearchRunTimesUnsorted;
    uint64_t counter = 0;
    int average = 0;

    for (int i = 0; i < RUNS; i++) {
        tmr.reset();
        for(int j =0; j < REPEATS; j++) linearSearch(unsortedArray,SIZE, SIZE + 1);
        linearSearchRunTimesUnsorted.push_back(tmr.elapsed()/REPEATS);
    }
    counter = 0;
    for (long value : linearSearchRunTimesUnsorted) {
        counter += value;
    }
    average = (int) (counter / RUNS);
    cout <<"\tLinear Search average runtime for unsorted array: " << average << " nanoseconds" <<endl;

    for (int i = 0; i < RUNS; i++) {
        tmr.reset();
        for(int j =0; j < REPEATS; j++) linearSearch(sortedArray, SIZE, SIZE + 1);
        linearSearchRunTimesSorted.push_back(tmr.elapsed()/REPEATS);
    }
    counter = 0;
    for (long value : linearSearchRunTimesSorted) {
        counter += value;
    }
    average = (int) (counter / RUNS);
    cout << "\tLinear Search average runtime for sorted array:   " << average << " nanoseconds" <<endl;


    for (int i = 0; i < RUNS; i++) {
        tmr.reset();
        for(int j =0; j < REPEATS; j++) binarySearch(sortedArray, SIZE, SIZE + 1);
        binarySearchRunTimesSorted.push_back(tmr.elapsed()/REPEATS);
    }

    counter = 0;
    for (long value : binarySearchRunTimesSorted) {
        counter += value;
    }
    average = (int) (counter / RUNS);
    cout << "\tBinary Search average runtime for sorted array:   " << average << " nanoseconds" << endl;


    //Write out the arrays to a csv for later analysis
    ofstream csv(FILENAME);
    csv << "\"Run\",\"C++ Linear Search Sorted\",\"C++ Linear Search Unsorted\",\"C++ Binary Search Sorted\"\n";
    for (int i = 0; i < RUNS; i++) {
        csv << i << ",";
        csv << linearSearchRunTimesSorted.at(i) << ",";
        csv << linearSearchRunTimesUnsorted.at(i) << ",";
        csv << binarySearchRunTimesSorted.at(i);
        csv << "\n";
    }
    csv.close();
}


