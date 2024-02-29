#include <stdio.h>

template <class T>
void Swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
void SelectSort(T array[], int n, bool min2max = true) 
{
    for(int i = 0; i < n; i++) 
    {
        int index = i;
        for(int j = i; j < n; j++) 
        {
            if(min2max ? (array[j] < array[index]) : (array[j] > array[index])) 
            {
                index = j; //更新最小数/最大数的索引
            }
        }
        Swap<T>(array[i], array[index]);
    }
}

int main(int argc, char* argv[])
{
    int arr[] = {1, 2, 6, 4, 5};
    int length = sizeof(arr) / sizeof(arr[0]);
    printf("Array Element: ");
    for(int i = 0; i < length; i++)
    {
        printf("%d,", arr[i]);
    }
    printf("\n");
    printf("SelectSort: ");
    SelectSort<int>(arr, length);
    for(int i = 0; i < length; i++)
    {
        printf("%d,", arr[i]);
    }
    printf("\n");
    return 0;
}