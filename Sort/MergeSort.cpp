#include <stdio.h>

template <typename T>
void Merge(T src[], T helper[], int begin, int mid, int end, bool min2max = true)
{
    int i = begin;
    int j = mid + 1;
    int k = begin;
    while((i <= mid) && (j <= end))
    {
        if(min2max ? (src[i] < src[j]) : (src[i] > src[j]))
        {
            helper[k++] = src[i++];
        }
        else
        {
            helper[k++] = src[j++];
        }
    }
    while(i <= mid)
    {
        helper[k++] = src[i++];
    }
    while(j <= end)
    {
        helper[k++] = src[j++];
    }

    //拷贝辅助空间的结果到源序列空间
    for(i = begin; i <= end; i++)
    {
        src[i] = helper[i];
    }
}
 
template <typename T>
void MergeSort(T src[], T helper[], int begin, int end, bool min2max = true)
{
    if(begin < end)
    {
        int mid = (begin + end) / 2;
        //左边路进行归并排序
        MergeSort(src, helper, begin, mid, min2max);
        //右边路进行归并排序
        MergeSort(src, helper, mid + 1, end, min2max);
        //二路归并排序
        Merge(src, helper, begin, mid, end, min2max);
    }
}
 

template <typename T>
void MergeSort(T* array, int len, bool min2max=true)
{
    // 辅助空间申请
    T* helper = new T[len];
    if(helper != NULL)
    {
        MergeSort(array, helper, 0, len-1, min2max);
    }
    delete [] helper;
}


template <typename T>
void MergeSort_NoRecursive(T* array, int len)
{
    int i, j, k;
    // 临时数组，用于归并子序列
    int helper[len];
    // 左区间的起点、终点下标
    int L_start = 0, L_end = 0;
    // 右区间的起点、终点下标
    int R_start = 0, R_end = 0;

    // 区间长度 i，两倍递增
    for(i = 1; i < len; i *= 2)
    {
        // 根据区间长度划分多个左右两个区间
        for (L_start = 0; L_start < len - i; L_start = R_end + 1)
        {
            // 确定左右两个区间各自的起点、终点下标
            L_end = L_start + i - 1;
            R_start = L_end + 1;
            R_end = R_start + i - 1;
            
            // 右区间可能会超出数组长度
            if (R_end >= len)
            {
                R_end = len - 1;
            }

            // 临时数组下标
            j = 0;
            // 按大小顺序收集左右两个区间子序列的数据到临时数组中
            while(L_start <= L_end && R_start <= R_end)
            {
                // 比较左右区间内数据的大小
                if (array[L_start] < array[R_start])
                {
                    helper[j++] = array[L_start++];
                }
                else
                {
                    helper[j++] = array[R_start++];
                }
            }

            // 收集两个区间子序列中可能剩余的数据
            while(L_start <= L_end)
            {
                helper[j++] = array[L_start++];
            }
            while(R_start <= R_end)
            {
                helper[j++] = array[R_start++];
            }

            // 最后将排序好的数据重新录入原数组中
            while(j > 0)
            {
                array[--R_start] = helper[--j];
            }
        }
    } 
}


int main()
{
    int arr[] = {5, 3, 7, 1, 9, 2, 0, 4, 8, 6};
    int length = sizeof(arr) / sizeof(arr[0]);
    printf("Array Element: ");
    for(int i = 0; i < length; i++)
    {
        printf("%d,", arr[i]);
    }
    printf("\n");
    printf("MergeSort: ");
    MergeSort<int>(arr, length);
    for(int i = 0; i < length; i++)
    {
        printf("%d,", arr[i]);
    }
    printf("\n");
    return 0;
}
