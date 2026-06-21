/*************************************************************
* Author:			Jaden Prante
* Filename:			Lab15.cpp
* Date Created:		Jun 6th 2025
* Modifications:	NA
*
* 
* Lab/Assignment: Lab 15 - Sorting Algorthims
*
* Overview:
* This lab goes over Sorting Algorthims
*
* Input:
* Numbeers for the sorting methods
*
* Output:
* File with these all sorted
**************************************************************/

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include "Array.h"
#include "Exception.h"
#include <vector>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <windows.h>
#include <stdlib.h>
#include <chrono>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::fstream;
using std::ofstream;
using std::stack;
using std::queue;
using std::list;
using std::pair;
using std::string;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::seconds;
using std::chrono::milliseconds;
using std::chrono::time_point;
using std::ios;
using namespace std;

// Stopwatch Function
/*************************************************
* Purpose: timer for sorts
*
* Precondtions: NA
*
* Postconditions: time is calculated
*
**************************************************/
void Stopwatch();

// Function Prototypes
/*************************************************
* Purpose: handles file data
*
* Precondtions: NA
*
* Postconditions: file is outputed
*
**************************************************/
void WriteResultsVector(ofstream& output, vector<int>& data, double elapsedTime);
void WriteResultsArray(ofstream& output, Array<int>& data, double elapsedTime);
void PrintArrayNative(ofstream& output, int* arr, int n, double elapsedTime);
void CopyNativeData(int* arr, int* arr2, int n);

// BruteForce and Flagged BubbleSort Functions
/*************************************************
* Purpose: sorts with bubble, will flag bubble
*
* Precondtions: data
*
* Postconditions: data is sorted
*
**************************************************/
void BubbleSortBruteForceVector(vector<int>& arr);
void BubbleSortBruteForceArray(Array<int> &arr);
void BubbleSortBruteForceNative(int*  arr, int n);
void BubbleSortFlaggedVector(vector<int>& arr);
void BubbleSortFlaggedArray(Array<int>& arr);
void BubbleSortFlaggedNative(int* arr, int n);

// SelectionSort Functions
/*************************************************
* Purpose: sorts with selection
*
* Precondtions: data
*
* Postconditions: data is sorted
*
**************************************************/
void SelectionSortVector(vector<int> &arr);
void SelectionSortArray(Array<int>& arr);
void SelectionSortNative(int* arr, int n);

// InsertionSort Functions
/*************************************************
* Purpose: sorts with insertion
*
* Precondtions: data
*
* Postconditions: data is sorted
*
**************************************************/
void InsertionSortVector(vector<int>& arr);
void InsertionSortArray(Array<int>& arr);
void InsertionSortNative(int* arr, int n);

// ShellSort Functions
/*************************************************
* Purpose: sorts with shell
*
* Precondtions: data
*
* Postconditions: data is sorted
*
**************************************************/
void ShellSortVector(vector<int>& arr);
void ShellSortArray(Array<int>& arr);
void ShellSortNative(int* arr, int n);

// Heap Functions
/*************************************************
* Purpose: helps heap sort
*
* Precondtions: data
*
* Postconditions: heap helper is done
*
**************************************************/
void MoveDownVector(vector<int>& arr, int n, int i);
void MoveDownArray(Array<int>& arr, int n, int i);
void MoveDownNative(int* arr, int n, int i);

// HeapSort Functions
/*************************************************
* Purpose: sorts with heap
*
* Precondtions: data
*
* Postconditions: data is sorted
*
**************************************************/
void HeapSortVector(vector<int>& arr);
void HeapSortArray(Array<int>& arr);
void HeapSortNative(int* arr, int n);

// Merge Functions
/*************************************************
* Purpose: helps with merge
*
* Precondtions: data
*
* Postconditions: merge helper is done
*
**************************************************/
void MergeDownVector(vector<int>& arr, int left, int mid, int right);
void MergeDownArray(Array<int>& arr, int left, int mid, int right);
void MergeDownNative(int* arr, int* temp, int left, int mid, int right);

// MergeSort Functions
/*************************************************
* Purpose: sorts with merge
*
* Precondtions: data
*
* Postconditions: data is sorted
*
**************************************************/
void MergeSortVector(vector<int>& arr, int left, int right);
void MergeSortArray(Array<int>& arr, int left, int right);
void MergeSortNative(int* arr, int* temp, int left, int right);
void MergeSortVector2(vector<int>& arr, int n);
void MergeSortArray2(Array<int>& arr, int n);
void MergeSortNative2(int* arr, int n);

// QuickSort Functions
/*************************************************
* Purpose: sorts with recursive quick
*
* Precondtions: data
*
* Postconditions: data is sorted
*
**************************************************/
void QuickSortVector(vector<int>& arr, int low, int high);
void QuickSortArray(Array<int>& arr, int low, int high);
void QuickSortNative(int* arr, int low, int high);

// RadixSort Functions
/*************************************************
* Purpose: sorts with radix
*
* Precondtions: data
*
* Postconditions: data is sorted
*
**************************************************/
void RadixSortVector(vector<int>& arr);
void RadixSortArray(Array<int>& arr);
void RadixSortNative(int* arr, int n);

// ShakerSort Functions
/*************************************************
* Purpose: sorts with shaker
*
* Precondtions: data
*
* Postconditions: data is sorted
*
**************************************************/
void ShakerSortVector(vector<int>& arr);
void ShakerSortArray(Array<int>& arr);
void ShakerSortNative(int* arr, int n);

// Iterative QuickSort Functions
/*************************************************
* Purpose: sorts with iterative quick
*
* Precondtions: data
*
* Postconditions: data is sorted
*
**************************************************/
void QuickSortIterativeVector(vector<int>& arr);
void QuickSortIterativeArray(Array<int>& arr);
void QuickSortIterativeNative(int* arr, int n);

double timeLapse = 0;

int main(int argc, char* argv[]) 
{   
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    static ofstream outFile("results.txt");
    int n = atoi(argv[1]);
    srand(time(0));
    int* array = new int[n];
    int* tempArray = new int[n];
    Array<int> theArray(n);
    Array<int> theArrayTemp(n);
    vector<int> arrayV;
    vector<int> temp;
    for (int i = 0; i < n; i++)
    {
        int value = rand() % n;
        array[i] = value;
        theArray[i] = value;
        arrayV.push_back(value);
    }

    // Brute Force Bubble
    temp = arrayV;
    Stopwatch();
    BubbleSortBruteForceVector(temp);
    Stopwatch();
    outFile << "Bubble Sort Brute Force (vector)";
    WriteResultsVector(outFile, temp, timeLapse);
    outFile << endl;

    theArrayTemp = theArray;
    Stopwatch();
    BubbleSortBruteForceArray(theArrayTemp);
    Stopwatch();
    outFile << "Bubble Sort Brute Force (array)";
    WriteResultsArray(outFile, theArrayTemp, timeLapse);
    outFile << endl;

    CopyNativeData(tempArray, array, n);
    Stopwatch();
    BubbleSortBruteForceNative(tempArray, n);
    Stopwatch();
    outFile << "Bubble Sort Brute Force (native)";
    PrintArrayNative(outFile, tempArray, n, timeLapse);
    outFile << endl;

    // Flagged Bubble
    temp = arrayV;
    Stopwatch();
    BubbleSortFlaggedVector(temp);
    Stopwatch();
    outFile << "Bubble Sort Flagged (vector)";
    WriteResultsVector(outFile, temp, timeLapse);
    outFile << endl;

    theArrayTemp = theArray;
    Stopwatch();
    BubbleSortFlaggedArray(theArrayTemp);
    Stopwatch();
    outFile << "Bubble Sort Flagged (array)";
    WriteResultsArray(outFile, theArrayTemp, timeLapse);
    outFile << endl;

    CopyNativeData(tempArray, array, n);
    Stopwatch();
    BubbleSortFlaggedNative(tempArray, n);
    Stopwatch();
    outFile << "Bubble Sort Flagged (native)";
    PrintArrayNative(outFile, tempArray, n, timeLapse);
    outFile << endl;

    // Selection
    temp = arrayV;
    Stopwatch();
    SelectionSortVector(temp);
    Stopwatch();
    outFile << "Selection Sort (vector)";
    WriteResultsVector(outFile, temp, timeLapse);
    outFile << endl;

    theArrayTemp = theArray;
    Stopwatch();
    SelectionSortArray(theArrayTemp);
    Stopwatch();
    outFile << "Selection Sort (array)";
    WriteResultsArray(outFile, theArrayTemp, timeLapse);
    outFile << endl;

    CopyNativeData(tempArray, array, n);
    Stopwatch();
    SelectionSortNative(tempArray, n);
    Stopwatch();
    outFile << "Selection Sort (native)";
    PrintArrayNative(outFile, tempArray, n, timeLapse);
    outFile << endl;

    // Insertion
    temp = arrayV;
    Stopwatch();
    InsertionSortVector(temp);
    Stopwatch();
    outFile << "Insertion Sort (vector)";
    WriteResultsVector(outFile, temp, timeLapse);
    outFile << endl;

    theArrayTemp = theArray;
    Stopwatch();
    InsertionSortArray(theArrayTemp);
    Stopwatch();
    outFile << "Insertion Sort (array)";
    WriteResultsArray(outFile, theArrayTemp, timeLapse);
    outFile << endl;

    CopyNativeData(tempArray, array, n);
    Stopwatch();
    InsertionSortNative(tempArray, n);
    Stopwatch();
    outFile << "Insertion Sort (native)";
    PrintArrayNative(outFile, tempArray, n, timeLapse);
    outFile << endl;

    // Shell
    temp = arrayV;
    Stopwatch();
    ShellSortVector(temp);
    Stopwatch();
    outFile << "Shell Sort (vector)";
    WriteResultsVector(outFile, temp, timeLapse);
    outFile << endl;

    theArrayTemp = theArray;
    Stopwatch();
    ShellSortArray(theArrayTemp);
    Stopwatch();
    outFile << "Shell Sort (array)";
    WriteResultsArray(outFile, theArrayTemp, timeLapse);
    outFile << endl;

    CopyNativeData(tempArray, array, n);
    Stopwatch();
    ShellSortNative(tempArray, n);
    Stopwatch();
    outFile << "Shell Sort (native)";
    PrintArrayNative(outFile, tempArray, n, timeLapse);
    outFile << endl;

    // Heap
    temp = arrayV;
    Stopwatch();
    HeapSortVector(temp);
    Stopwatch();
    outFile << "Heap Sort (vector)";
    WriteResultsVector(outFile, temp, timeLapse);
    outFile << endl;

    theArrayTemp = theArray;
    Stopwatch();
    HeapSortArray(theArrayTemp);
    Stopwatch();
    outFile << "Heap Sort (array)";
    WriteResultsArray(outFile, theArrayTemp, timeLapse);
    outFile << endl;

    CopyNativeData(tempArray, array, n);
    Stopwatch();
    HeapSortNative(tempArray, n);
    Stopwatch();
    outFile << "Heap Sort (native)";
    PrintArrayNative(outFile, tempArray, n, timeLapse);
    outFile << endl;

    // Merge
    temp = arrayV;
    Stopwatch();
    MergeSortVector2(temp, n);
    Stopwatch();
    outFile << "Merge Sort (vector)";
    WriteResultsVector(outFile, temp, timeLapse);
    outFile << endl;

    theArrayTemp = theArray;
    Stopwatch();
    MergeSortArray2(theArrayTemp, n);
    Stopwatch();
    outFile << "Merge Sort (array)";
    WriteResultsArray(outFile, theArrayTemp, timeLapse);
    outFile << endl;

    CopyNativeData(tempArray, array, n);
    Stopwatch();
    MergeSortNative2(tempArray, n);
    Stopwatch();
    outFile << "Merge Sort (native)";
    PrintArrayNative(outFile, tempArray, n, timeLapse);
    outFile << endl;

    // Quick
    temp = arrayV;
    Stopwatch();
    QuickSortVector(temp, 0, temp.size() - 1);
    Stopwatch();
    outFile << "Quick Sort (vector)";
    WriteResultsVector(outFile, temp, timeLapse);
    outFile << endl;

    theArrayTemp = theArray;
    Stopwatch();
    QuickSortArray(theArrayTemp, 0, n - 1);
    Stopwatch();
    outFile << "Quick Sort (array)";
    WriteResultsArray(outFile, theArrayTemp, timeLapse);
    outFile << endl;

    CopyNativeData(tempArray, array, n);
    Stopwatch();
    QuickSortNative(tempArray, 0, n - 1);
    Stopwatch();
    outFile << "Quick Sort (native)";
    PrintArrayNative(outFile, tempArray, n, timeLapse);
    outFile << endl;

    // Radix
    temp = arrayV;
    Stopwatch();
    RadixSortVector(temp);
    Stopwatch();
    outFile << "Radix Sort (vector)";
    WriteResultsVector(outFile, temp, timeLapse);
    outFile << endl;

    theArrayTemp = theArray;
    Stopwatch();
    RadixSortArray(theArrayTemp);
    Stopwatch();
    outFile << "Radix Sort (array)";
    WriteResultsArray(outFile, theArrayTemp, timeLapse);
    outFile << endl;

    CopyNativeData(tempArray, array, n);
    Stopwatch();
    RadixSortNative(tempArray, n);
    Stopwatch();
    outFile << "Radix Sort (native)";
    PrintArrayNative(outFile, tempArray, n, timeLapse);
    outFile << endl;

    // Shaker
    temp = arrayV;
    Stopwatch();
    ShakerSortVector(temp);
    Stopwatch();
    outFile << "Shaker Sort (vector)";
    WriteResultsVector(outFile, temp, timeLapse);
    outFile << endl;

    theArrayTemp = theArray;
    Stopwatch();
    ShakerSortArray(theArrayTemp);
    Stopwatch();
    outFile << "Shaker Sort (array)";
    WriteResultsArray(outFile, theArrayTemp, timeLapse);
    outFile << endl;

    CopyNativeData(tempArray, array, n);
    Stopwatch();
    ShakerSortNative(tempArray, n);
    Stopwatch();
    outFile << "Shaker Sort (native)";
    PrintArrayNative(outFile, tempArray, n, timeLapse);
    outFile << endl;

    // Iterative Quick
    temp = arrayV;
    Stopwatch();
    QuickSortIterativeVector(temp);
    Stopwatch();
    outFile << "Iterative Quick Sort (vector)";
    WriteResultsVector(outFile, temp, timeLapse);
    outFile << endl;

    theArrayTemp = theArray;
    Stopwatch();
    QuickSortIterativeArray(theArrayTemp);
    Stopwatch();
    outFile << "Iterative Quick Sort (array)";
    WriteResultsArray(outFile, theArrayTemp, timeLapse);
    outFile << endl;

    CopyNativeData(tempArray, array, n);
    Stopwatch();
    QuickSortIterativeNative(tempArray, n);
    Stopwatch();
    outFile << "Iterative Quick Sort (native)";
    PrintArrayNative(outFile, tempArray, n, timeLapse);
    outFile << endl;    
    delete[] array;
    delete[] tempArray;
}

void Stopwatch()
{
    static bool time = false;
    static time_point<high_resolution_clock> start, stop;
    if (!time)
    {
        start = high_resolution_clock::now();
        time = true;
    }
    else
    {
        stop = high_resolution_clock::now();
        timeLapse = duration_cast<milliseconds>(stop - start).count() / 1000.0;
        // cout << timeLapse << "S\t\t";
        time = false;
    }
}

void WriteResultsVector(ofstream& output, vector<int>& data, double elapsedTime)
{
    output << " took " << elapsedTime << " seconds.\n";
    for (int i = 0; i < data.size(); i += 1000)
    {
        output << data[i] << " ";
    }
    output << "\n\n";
}

void WriteResultsArray(ofstream& output, Array<int>& data, double elapsedTime)
{

    output << " took " << elapsedTime << " seconds.\n";
    for (int i = 0; i < data.GetLength(); i += 1000) 
    {
        output << data[i] << " ";
    }
    output << "\n\n";
}

void PrintArrayNative(ofstream& output, int* arr, int n, double elapsedTime)
{
    output << " took " << elapsedTime << " seconds.\n";
    for (int i = 0; i < n; i += 1000)
    {
        output << arr[i] << " ";
    }
    output << "\n\n";
}

void CopyNativeData(int* arr, int* arr2, int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = arr2[i];
    }
}

void BubbleSortBruteForceVector(vector<int> &arr)
{
    for (size_t i = 0; i < arr.size(); i++) 
    {
        for (size_t j = 0; j < arr.size() - 1; j++) 
        {
            if (arr[j] > arr[j + 1]) 
            {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}


void BubbleSortBruteForceArray(Array<int> &arr)
{
    int n = arr.GetLength();
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n - 1; j++) 
        {
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}


void BubbleSortBruteForceNative(int* arr, int n)
{
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n - 1; j++) 
        {
            if (arr[j] > arr[j + 1]) 
            {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void BubbleSortFlaggedVector(vector<int> &arr)
{
    bool swapped = false;
    for (size_t i = 0; i < arr.size(); i++) 
    {
        for (size_t j = 0; j < arr.size() - i - 1; j++) 
        {
            if (arr[j] > arr[j + 1]) 
            {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
        {
            throw Exception("Data is not sorted");
        }
    }
}


void BubbleSortFlaggedArray(Array<int> &arr)
{
    bool sorted = false;
    int n = arr.GetLength();
    int i = 0;
    while (i < n && sorted == false)
    {
        sorted = true;
        for (int j = 0; j < n - i - 1; j++)
        {
             if (arr[j] > arr[j + 1])
             {
                std::swap(arr[j], arr[j + 1]);
                sorted = false;
             }
        }
        i++;
    }
}

void BubbleSortFlaggedNative(int* arr, int n)
{
    bool swapped = false;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1]) 
            {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
    }
}

void SelectionSortVector(vector<int>& arr)
{
    for (size_t i = 0; i < arr.size() - 1; i++) 
    {
        size_t minIndex = i;  
        for (size_t j = i + 1; j < arr.size(); j++) 
        {
            if (arr[j] < arr[minIndex]) 
            {
                minIndex = j;  
            }
        }
        std::swap(arr[i], arr[minIndex]);
    }
}

void SelectionSortArray(Array<int>& arr)
{
    int n = arr.GetLength();
    for (int i = 0; i < n - 1; i++) 
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) 
        {
            if (arr[j] < arr[minIndex]) 
            {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
    }
}


void SelectionSortNative(int* arr, int n)
{
    for (int i = 0; i < n - 1; i++) 
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) 
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
    }
}


void InsertionSortVector(vector<int>& arr)
{
    for (size_t i = 1; i < arr.size(); i++) 
    {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) 
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void InsertionSortArray(Array<int>& arr)
{
    int n = arr.GetLength();
    for (int i = 1; i < n; i++)
    {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) 
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}


void InsertionSortNative(int* arr, int n)
{
    for (int i = 1; i < n; i++) 
    {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) 
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void ShellSortVector(vector<int>& arr)
{
    for (int gap = arr.size() / 2; gap > 0; gap /= 2) 
    {
        for (size_t i = gap; i < arr.size(); i++) 
        {
            int temp = arr[i], j = i;
            while (j >= gap && arr[j - gap] > temp) 
            {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}


void ShellSortArray(Array<int>& arr)
{
    int n = arr.GetLength();
    for (int gap = n / 2; gap > 0; gap /= 2) 
    {
        for (int i = gap; i < n; i++) 
        {
            int temp = arr[i], j = i;
            while (j >= gap && arr[j - gap] > temp)
            {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}


void ShellSortNative(int* arr, int n) {
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++) 
        {
            int temp = arr[i], j = i;
            while (j >= gap && arr[j - gap] > temp) 
            {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

void MoveDownVector(vector<int>& arr, int n, int i)
{
    int largest = i;        
    int left = 2 * i + 1;   
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) 
    {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) 
    {
        largest = right;
    }
    if (largest != i) 
    {
        std::swap(arr[i], arr[largest]);
        MoveDownVector(arr, n, largest);
    }
}


void MoveDownArray(Array<int>& arr, int n, int i)
{
    int largest = i;        
    int left = 2 * i + 1;   
    int right = 2 * i + 2;  
    if (left < n && arr[left] > arr[largest]) 
    {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) 
    {
        largest = right;
    }
    if (largest != i) 
    {
        std::swap(arr[i], arr[largest]);
        MoveDownArray(arr, n, largest);
    }
}

void MoveDownNative(int* arr, int n, int i)
{
    int largest = i;        
    int left = 2 * i + 1;   
    int right = 2 * i + 2;  
    if (left < n && arr[left] > arr[largest]) 
    {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) 
    {
        largest = right;
    }
    if (largest != i)
    {
        std::swap(arr[i], arr[largest]);
        MoveDownNative(arr, n, largest); 
    }
}


void HeapSortVector(vector<int>& arr)
{
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) 
    {
        MoveDownVector(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]); 
        MoveDownVector(arr, i, 0);
    }
}


void HeapSortArray(Array<int>& arr)
{
    int n = arr.GetLength();
    for (int i = n / 2 - 1; i >= 0; i--) 
    {
        MoveDownArray(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--)
    {
        std::swap(arr[0], arr[i]); 
        MoveDownArray(arr, i, 0); 
    }
}

void HeapSortNative(int* arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--) 
    {
        MoveDownNative(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) 
    {
        std::swap(arr[0], arr[i]); 
        MoveDownNative(arr, i, 0);
    }
}

void MergeDownVector(vector<int>& arr, int left, int mid, int right)
{
    vector<int> temp;  
    int i = left;
    int j = mid + 1;
    while (i <= mid && j <= right) 
    {
        if (arr[i] <= arr[j]) 
        {
            temp.push_back(arr[i++]);
        }
        else {
            temp.push_back(arr[j++]);
        }
    }
    while (i <= mid) 
    {
        temp.push_back(arr[i++]);
    }
    while (j <= right)
    {
        temp.push_back(arr[j++]);
    }
    for (size_t k = 0; k < temp.size(); ++k) 
    {
        arr[left + k] = temp[k];
    }
}

void MergeDownArray(Array<int>& arr, int left, int mid, int right)
{
    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    Array<int> leftArr(leftSize);
    Array<int> rightArr(rightSize);
    for (int i = 0; i < leftSize; i++)
    {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < rightSize; i++) 
    {
        rightArr[i] = arr[mid + 1 + i];
    }
    int i = 0, j = 0, k = left;
    while (i < leftSize && j < rightSize) 
    {
        if (leftArr[i] <= rightArr[j]) 
        {
            arr[k] = leftArr[i];
            i++;
        }
        else 
        {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    while (i < leftSize) 
    {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    while (j < rightSize) 
    {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

}

void MergeDownNative(int* arr, int* temp, int left, int right, int right_end) {
    int left_end = right - 1;
    int temp_pos = left;
    int num_elements = right_end - left + 1;

    while (left <= left_end && right <= right_end) 
    {
        if (arr[left] <= arr[right]) 
        {
            temp[temp_pos++] = arr[left++];
        }
        else
        {
            temp[temp_pos++] = arr[right++];
        }
    }
    while (left <= left_end) {
        temp[temp_pos++] = arr[left++];
    }
    while (right <= right_end) 
    {
        temp[temp_pos++] = arr[right++];
    }
    for (int i = 0; i < num_elements; i++) 
    {
        arr[right_end - i] = temp[right_end - i];
    }
}


void MergeSortVector(vector<int>& arr, int left, int right) 
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        MergeSortVector(arr, left, mid);
        MergeSortVector(arr, mid + 1, right);
        MergeDownVector(arr, left, mid, right);
    }
}

void MergeSortArray(Array<int>& arr, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        MergeSortArray(arr, left, mid);
        MergeSortArray(arr, mid + 1, right);
        MergeDownArray(arr, left, mid, right);
    }
}

void MergeSortNative(int* arr, int* temp, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        MergeSortNative(arr, temp, left, mid);
        MergeSortNative(arr, temp, mid + 1, right);
        MergeDownNative(arr, temp, left, mid + 1, right);
    }
}

void MergeSortVector2(vector<int>& arr, int n)
{
    vector<int> temp(n);
    MergeSortVector(arr, 0, n - 1);
}

void MergeSortArray2(Array<int>& arr, int n)
{
    Array<int> temp(n);
    MergeSortArray(arr, 0, n - 1);
}

void MergeSortNative2(int* arr, int n)
{
    int* temp = new int[n];
    MergeSortNative(arr, temp, 0, n - 1);
    delete[] temp;
}

void QuickSortVector(vector<int>& arr, int low, int high)
{
    if (low < high)
    {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) 
        {
            if (arr[j] <= pivot)
            {
                std::swap(arr[++i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        int pivotIndex = i + 1;
        QuickSortVector(arr, low, pivotIndex - 1);
        QuickSortVector(arr, pivotIndex + 1, high);
    }
}

void QuickSortArray(Array<int>& arr, int low, int high)
{
    if (low < high)
    {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++)
        {
            if (arr[j] <= pivot)
            {
                std::swap(arr[++i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        int pivotIndex = i + 1;
        QuickSortArray(arr, low, pivotIndex - 1);
        QuickSortArray(arr, pivotIndex + 1, high);
    }
}


void QuickSortNative(int* arr, int low, int high) {
    if (low < high)
    {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) 
        {
            if (arr[j] <= pivot) 
            {
                std::swap(arr[++i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        int pivotIndex = i + 1;
        QuickSortNative(arr, low, pivotIndex - 1);
        QuickSortNative(arr, pivotIndex + 1, high);
    }
}

void RadixSortVector(vector<int>& arr)
{ 
    int maxElement = arr[0];
    for (int num : arr) 
    {
        if (num > maxElement) 
        {
            maxElement = num;
        }
    }
    int exp = 1;
    vector<int> output(arr.size());
    while (maxElement / exp > 0) 
    {
        vector<int> count(10, 0);
        for (int num : arr) 
        {
            count[(num / exp) % 10]++;
        }
        for (size_t i = 1; i < 10; i++) 
        {
            count[i] += count[i - 1];
        }
        for (int i = arr.size() - 1; i >= 0; i--) 
        {
            int digit = (arr[i] / exp) % 10;
            output[--count[digit]] = arr[i];
        }
        arr = output;
        exp *= 10;
    }
}

void RadixSortArray(Array<int>& arr)
{
    int n = arr.GetLength();
    int maxElement = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > maxElement) 
        {
            maxElement = arr[i];
        }
    }
    for (int exp = 1; maxElement / exp > 0; exp *= 10) 
    {
        Array<int> output(n);
        int count[10] = { 0 };
        for (int i = 0; i < n; i++)
        {
            count[(arr[i] / exp) % 10]++;
        }
        for (int i = 1; i < 10; i++) 
        {
            count[i] += count[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) 
        {
            int digit = (arr[i] / exp) % 10;
            output[--count[digit]] = arr[i];
        }
        for (int i = 0; i < n; i++) 
        {
            arr[i] = output[i];
        }
    }
}


void RadixSortNative(int* arr, int n)
{ 
    int maxElement = arr[0];  
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > maxElement)
        {
            maxElement = arr[i];
        }
    }
    int* output = new int[n]; 
    int* count = new int[10]; 
    for (int exp = 1; maxElement / exp > 0; exp *= 10)
    {
        for (int i = 0; i < 10; i++)
        {
            count[i] = 0;
        }

        for (int i = 0; i < n; i++)
        {
            count[(arr[i] / exp) % 10]++;
        }

        for (int i = 1; i < 10; i++)
        {
            count[i] += count[i - 1];
        }
        for (int i = n - 1; i >= 0; i--)
        {
            int digit = (arr[i] / exp) % 10;
            output[--count[digit]] = arr[i];
        }
        for (int i = 0; i < n; i++)
        {
            arr[i] = output[i];
        }
    }
    delete[] output;
    delete[] count;
}

void ShakerSortVector(vector<int>& arr)
{
    bool swapped = true;
    size_t start = 0;
    size_t end = arr.size() - 1;
    while (swapped) 
    {
        swapped = false;
        for (size_t i = start; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        end--;
        swapped = (swapped || start < end);
        for (size_t i = end; i > start; i--) 
        {
            if (arr[i] < arr[i - 1]) 
            {
                std::swap(arr[i], arr[i - 1]);
                swapped = true;
            }
        }
        start++;
    }
}


void ShakerSortArray(Array<int>& arr)
{
    int start = 0; 
    int end = arr.GetLength() - 1;
    bool swapped = true;
    while (swapped)
    {
        swapped = false;
        for (int i = start; i < end; i++) 
        {
            if (arr[i] > arr[i + 1]) 
            {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        end--;
        for (int i = end; i > start; i--)
        {
            if (arr[i] < arr[i - 1])
            {
                std::swap(arr[i], arr[i - 1]);
                swapped = true;
            }
        }
        start++;
    }
}

void ShakerSortNative(int* arr, int n)
{
    int start = 0, end = n - 1;
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int i = start; i < end; i++) 
        {
            if (arr[i] > arr[i + 1]) 
            { 
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        end--;
        for (int i = end; i > start; i--)
        {
            if (arr[i] < arr[i - 1])
            {
                std::swap(arr[i], arr[i - 1]);
                swapped = true;
            }
        }
        start++;
    }
}

void QuickSortIterativeVector(vector<int>& arr)
{
    stack<pair<int, int>> stk;
    stk.push({ 0, arr.size() - 1 });
    while (!stk.empty()) 
    {
        int low = stk.top().first;
        int high = stk.top().second;
        stk.pop();
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) 
        {
            if (arr[j] <= pivot) 
            {
                std::swap(arr[++i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        int pivotIndex = i + 1;
        if (pivotIndex - 1 > low) 
        {
            stk.push({ low, pivotIndex - 1 });
        }
        if (pivotIndex + 1 < high) 
        {
            stk.push({ pivotIndex + 1, high });
        }
    }
}

void QuickSortIterativeArray(Array<int>& arr) {
    int n = arr.GetLength();
    stack<pair<int, int>> stk;
    stk.push({ 0, n - 1 });
    while (!stk.empty()) {
        int low = stk.top().first;
        int high = stk.top().second;
        stk.pop();
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) 
        {
            if (arr[j] <= pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        int pivotIndex = i + 1;
        if (pivotIndex - 1 > low) 
        {
            stk.push({ low, pivotIndex - 1 });
        }
        if (pivotIndex + 1 < high) 
        {
            stk.push({ pivotIndex + 1, high });
        }
    }
}


void QuickSortIterativeNative(int* arr, int n)
{
    stack<pair<int, int>> stk;
    stk.push({ 0, n - 1 });
    while (!stk.empty()) {
        int low = stk.top().first;
        int high = stk.top().second;
        stk.pop();
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) 
        {
            if (arr[j] <= pivot) 
            {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        int pivotIndex = i + 1;
        if (pivotIndex - 1 > low) 
        {
            stk.push({ low, pivotIndex - 1 });
        }
        if (pivotIndex + 1 < high) 
        {
            stk.push({ pivotIndex + 1, high });
        }
    }
}