#include<stdio.h>
 
template <class T>
int SeqSearch(T a[], int n, T key)
{
    int index = -1;
    for(int i = 0; i < n; i++)
    {
        if(key == a[i])
        {
            index = i;
            break;
        }
    }
    return index;
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
    int pos = SeqSearch<int>(arr, length, Value);
    printf("SeqSearch find Value:%d at pos:%d\n", Value, pos);

    return 0;
}