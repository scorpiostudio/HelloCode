#include<stdio.h>
 
template <class T>
int BinarySearch(T a[], int n, T key)
{
    int low = 0;
    int high = n - 1; 
    while(low <= high)
    {
        int mid = (low + high) / 2;
        int midValue = a[mid];
        if(midValue < key)
        {
            low = mid + 1;
        }
        else if(midValue > key)
        {
            high = mid - 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}
 
int main(int argc, char* argv[])
{
    int arr[] = {1, 2, 3, 4, 5};
    int length = sizeof(arr) / sizeof(arr[0]);
    printf("Array Element: ");
    for(int i = 0; i < length; i++)
    {
        printf("%d,", arr[i]);
    }
    printf("\n");
    int Value = 4;
    int pos = BinarySearch<int>(arr, length, Value);
    printf("BinarySearch find Value:%d at pos:%d\n", Value, pos);
    
    return 0;
}