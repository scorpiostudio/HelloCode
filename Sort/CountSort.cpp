#include <stdio.h>

template <class T>
void CountSort(T arr[], int len) 
{
    // 1 查找数列的最大值与最小值，并算出差值d
    int max = arr[0];
    int min = arr[0];
    for(int i = 1; i < len; i++) 
    {
        if (arr[i] > max) 
        {
            max = arr[i];
        }
        if(arr[i] < min) 
        {
            min = arr[i];
        }
    }
    int d = max - min + 1;
    // 2 创建基于差值长度的统计数组并统计填充对应元素个数
    int* countArray = new int[d];
    for(int i = 0; i < len; i++) 
    {
        countArray[arr[i] - min]++;
    }
    // 3 遍历统计数组，输出结果到原始数组
    int j = 0;
    for(int i = 0; i < d; i++) 
    {
        while(countArray[i] > 0)
        {
            arr[j++] = min + i;
            countArray[i]--;
        }
    }

    delete [] countArray;
    countArray = NULL;
}


int main(int argc, char* argv[])
{
    int arr[] = {10, 12, 15, 14, 15, 11, 15, 11};
    int length = sizeof(arr) / sizeof(arr[0]);
    printf("Array Element: ");
    for(int i = 0; i < length; i++)
    {
        printf("%d,", arr[i]);
    }
    printf("\n");
    printf("CountSort: ");
    CountSort<int>(arr, length);
    for(int i = 0; i < length; i++)
    {
        printf("%d,", arr[i]);
    }
    printf("\n");
    return 0;
}
