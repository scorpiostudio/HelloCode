#include <stdio.h>

template <class T>
void Swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
void ShellSort(T a[], int n)
{
    int h = 1;
    while(h <= n / 3) 
        h = 3 * h + 1;//初始化间隔h，目的是为了下文的统一
    while(h >= 1)
    {
        for(int i = 0;i < n; ++i)
        {
            for(int j = i; j >= h && a[j] < a[j - h]; j = j - h)
            {
                Swap<T>(a[j], a[j - h]);
            }
        }
        h= h / 3;//减小间距
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
    printf("ShellSort: ");
    ShellSort<int>(arr, length);
    for(int i = 0; i < length; i++)
    {
        printf("%d,", arr[i]);
    }
    printf("\n");
    return 0;
}