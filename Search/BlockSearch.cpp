#include<stdio.h>

// 块结构信息
template <class T>
struct BlockInfo
{
    T key;        // 索引区间的最大键值
    int start;      // 索引区间的起始地址(下标)
    int end;      // 索引区间的结束地址(下标)
};

template <class T>
int BlockSearch(T array[], int arrayLen, BlockInfo<T> blocks[], int indexLen, T key)
{
    int ret = -1;
    // 折半查找索引表，找到关键值所在分块
    int low = 0, high = indexLen - 1;
    int mid = (low + high) / 2;
    while(low < high)
    {
        if(key == blocks[mid].key)
        {
            break;
        }
        else if (key < blocks[mid].key)
        {
            high = mid;
        }
        else
        {
            low = mid + 1;
        }
        mid = (low + high) / 2;
    }

    // 在分块内进行顺序查找
    for(int i = blocks[mid].start; i <= blocks[mid].end; i++)
    {
        if(key == array[i])
        {
            ret = i;
            break;
        }
    }
    return ret;
}

int main()
{
    const int SIZE = 10;
    int data[SIZE] = {3, 2, 1, 0, 5, 4, 9, 8, 7, 6};

    // 建立索引表
    BlockInfo<int> blocks[3];

    // 最大键值 = 3， 起始下标 = 0
    blocks[0].key = 3;
    blocks[0].start = 0;
    blocks[0].end = 3;
    // 最大键值 = 4， 起始下标 = 4
    blocks[1].key = 5;
    blocks[1].start = 4;
    blocks[1].end = 5;
    // 最大键值 = 9， 起始下标 = 6
    blocks[2].key = 9;
    blocks[2].start = 6;
    blocks[2].end = 9;
	
	// 查找 key=8 的下标位置
    int key = 8;
    int pos = BlockSearch<int>(data, SIZE, blocks, 3, key);
    printf("BlockSearch find value:%d, pos:%d\n", key, pos);

    return 0;
}
