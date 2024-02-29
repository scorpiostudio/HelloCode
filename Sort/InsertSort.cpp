#include <stdio.h>

template <class T>
void InsertSort(T arr[], int len)
{
    // 检查数据合法性
    if(arr == NULL || len <= 1)
    {
        return;
    }
    for(int i = 1; i < len; i++)
    {
        int tmp = arr[i];
        int j;
        for(j = i-1; j >= 0; j--)
        {
            //如果比tmp大把值往后移动一位
            if(arr[j] > tmp)
            {
               arr[j+1] = arr[j];
            }
            else
            {
               break;
            }
        }
        arr[j+1] = tmp;
    }
}

// 折半插入
template <class T>
void BinaryInsertSort(T arr[], int len)   
{   
    T key;
    int left, right, mid;   
    for(int i = 1; i < len; i++)   
    {   
        key = arr[i];   
        left = 0;   
        right = i - 1;   
        while(left <= right)   
        {   
            mid = (left + right) / 2;   
            if (arr[mid] > key)   
                right = mid - 1;   
            else   
                left = mid + 1;   
        }   

        for(int j = i - 1; j >= left; j--)   
        {   
            arr[j + 1] = arr[j];   
        }   

        arr[left] = key;          
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
    printf("InsertSort: ");
    InsertSort<int>(arr, length);
    for(int i = 0; i < length; i++)
    {
        printf("%d,", arr[i]);
    }
    printf("\n");
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 6;
    arr[3] = 4;
    arr[4] = 5;
    printf("BinaryInsertSort: ");
    BinaryInsertSort<int>(arr, length);
    for(int i = 0; i < length; i++)
    {
        printf("%d,", arr[i]);
    }
    printf("\n");
    return 0;
}