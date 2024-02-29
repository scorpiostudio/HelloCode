#include <stdio.h>

template <class T>
void Swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

template<typename T>
void QuickSort_Recursive(T arr[], int start, int end) 
{
    if(start >= end) 
        return;
    T mid = arr[end];
    int left = start, right = end - 1;
    while(left < right) 
    {
        while(arr[left] < mid && left < right) 
            left++;
        while(arr[right] >= mid && left < right) 
            right--;
        Swap<T>(arr[left], arr[right]);
    }
    if(arr[left] >= arr[end])
        Swap<T>(arr[left], arr[end]);
    else
        left++;
    QuickSort_Recursive(arr, start, left - 1);
    QuickSort_Recursive(arr, left + 1, end);
}

template<typename T>
void QuickSort(T arr[], int len) 
{
    QuickSort_Recursive(arr, 0, len - 1);
}


int main(int argc, char* argv[])
{
    int arr[] = {8, 4, 3, 1, 6, 9, 5, 7, 2, 0};
    int length = sizeof(arr) / sizeof(arr[0]);
    printf("Array Element: ");
    for(int i = 0; i < length; i++)
    {
        printf("%d,", arr[i]);
    }
    printf("\n");
    printf("QuickSort: ");
    QuickSort<int>(arr, length);
    for(int i = 0; i < length; i++)
    {
        printf("%d,", arr[i]);
    }
    printf("\n");
    return 0;
}