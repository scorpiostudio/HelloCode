#include <stdio.h>
#include <string.h>


// 取整数value的第i位数
int GetDigit(int value, int i) 
{
	while(i > 1)
	{
		value /= 10;
		i--;
	}
	return value % 10;
}

// 获取整数的位数
int GetFigure(int value)
{
    int ret = 1;
    while(value = value / 10)
	{
		ret++;
	}
    return ret;
}

int GetMax(int arr[], int len)
{
    int max = arr[0];
    for(int i = 1; i < len; i++)
    {
        if(max < arr[i])
        {
            max = arr[i];
        }
    }
    return max;
}

// 基数排序
void RadixSort(int arr[], int len)
{
    int max = GetMax(arr, len);
    int D = GetFigure(max);
    int i, j, k, l, digit;
    int helper[10][10];   // 分配数组
    // 遍历
    for(int i = 1; i <= D; i++)
    {
        memset(helper, 0, sizeof(helper));
        // 将每个数据的第i位数分配到allot数组中
        for(int j = 0; j < len; j++)
        {
            // 获取当前数据 arr[j] 的 第i位数
            int digit = GetDigit(arr[j], i);  
            k = 0;
            // 查找插入的位置
            while(helper[digit][k])
            {
                k++;
            }
            // 将arr[j]添加到分配数组allot的第digit行的末尾
            helper[digit][k] = arr[j];
        }
        // 将分配数组的数据收集到原数组中
        l = 0;
        for(j = 0; j < 10; j++)
        {
            k = 0;
            // 获取数组allot的每一行的数据到原数组中
            while(helper[j][k])
            {
                arr[l++] = helper[j][k++];
            }
        }
    }
}

int main(int argc, char* argv[])
{
    int arr[] = {52, 200, 4, 1034, 17, 3319, 8324, 33112, 603, 8};
    int length = sizeof(arr) / sizeof(arr[0]);
    printf("Array Element: ");
    for(int i = 0; i < length; i++)
    {
        printf("%d,", arr[i]);
    }
    printf("\n");
    printf("RadixSort: ");
    RadixSort(arr, length);
    for(int i = 0; i < length; i++)
    {
        printf("%d,", arr[i]);
    }
    printf("\n");

    return 0;
}
