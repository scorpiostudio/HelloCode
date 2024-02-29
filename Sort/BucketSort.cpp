#include <stdio.h>
 
template <class T>
void BucketSort(T arr[], int n)
{
    // 查找最大值
    T max = arr[0];
    for(int i = 1; i < n; i++)
    {
        if(max < arr[i])
        {
            max = arr[i];
        }
    }
    // 创建桶数组
    T* buckets = new T[max + 1];
 
    // 初始化桶数组
    for(int i = 0; i <= max; i++)
    {
        buckets[i] = 0;
    }
 
    // 将元素放入对应的桶中
    for(int i = 0; i < n; i++)
    {
        buckets[arr[i]]++;
    }
 
    // 从桶中取出元素并排序
    int index = 0;
    for(int i = 0; i <= max; i++)
    {
        while(buckets[i] > 0)
        {
            arr[index++] = i;
            buckets[i]--;
        }
    }
    delete [] buckets;
    buckets = NULL;
}
 
int main(int argc, char* argv[])
{
    int arr[] = {1, 7, 2, 5, 6, 9, 3, 4, 5};
    int length = sizeof(arr) / sizeof(arr[0]);
    printf("Array Element: ");
    for(int i = 0; i < length; i++)
    {
        printf("%d,", arr[i]);
    }
    printf("\n");
    printf("BucketSort: ");
    BucketSort<int>(arr, length);
    for(int i = 0; i < length; i++)
    {
        printf("%d,", arr[i]);
    }
    printf("\n");
    return 0;
}