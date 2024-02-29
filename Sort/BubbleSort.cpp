#include <stdio.h>

template <class T>
void Swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
void BubbleSort(T a[], int n, bool min2max = true) 
{
    for(int i = 0; i < n; i++) 
    {
        for(int j = 1; j < n - i; j++) 
        {
            if(min2max ? (a[j - 1] > a[j]) : (a[j - 1] < a[j])) 
            {
                Swap<T>(a[j - 1], a[j]);
            }
        }
    }
}


int main(int argc, char* argv[])
{
    int arr[] = {1, 2, 10, 4, 5};
    int length = sizeof(arr) / sizeof(arr[0]);
    printf("Array Element: ");
    for(int i = 0; i < length; i++)
    {
        printf("%d,", arr[i]);
    }
    printf("\n");
    printf("BubbleSort: ");
    BubbleSort<int>(arr, length);
    for(int i = 0; i < length; i++)
    {
        printf("%d,", arr[i]);
    }
    printf("\n");
    return 0;
}