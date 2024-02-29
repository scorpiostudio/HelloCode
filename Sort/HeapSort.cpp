#include <stdio.h>

template <class T>
void Swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

// 最大堆调整
template <class T>
void Heapify(T arr[], int len, int k)
{
    if(k < len)
    {
        int root = k;           // 根结点
        int lchild = 2*k + 1;   // 左孩子结点
        int rchild = 2*k + 2;   // 右孩子结点
        // 查找左右孩子结点中的最大结点
        if(lchild < len && arr[root] < arr[lchild])
        {
            root = lchild; 
        }
        if(rchild < len && arr[root] < arr[rchild])
        {
            root = rchild;
        }
        
        // 交换最大结点到根结点
        if(root != k)
        {
            Swap(arr[root], arr[k]);
            // 每次交换都可能影响到对应孩子结点子树的顺序
            // 所以需要对交换后的孩子结点子树进行最大堆调整
            Heapify<T>(arr, len, root);
        }
    }
}

// 创建最大堆
template <class T>
void CreateHeap(T arr[], int len)
{
    // 最后一个结点下标
    int last = len - 1;   
    // 最后一个结点的父结点下标      
    int parent = (last - 1) / 2;
    // 从最后一个结点的父结点到根结点，依次进行最大堆调整
    for(int i = parent; i >= 0; i--)
    {
        Heapify<T>(arr, len, i);
    }
}

// 堆排序
template <class T>
void HeapSort(T arr[], int len)
{
    // 创建最大堆并进行最大堆调整
    CreateHeap<T>(arr, len);
    // 依次取出根结点（最大值）
    for(int i = len - 1; i >= 0; i--)
    {
        // 将最大堆的根结点（最大值）换到最后一个结点
        Swap<T>(arr[i], arr[0]);
        // 交换后二叉树的根结点发生了改变，故还需对根结点做最大堆调整（已交换的末尾结点不参与调整）
        // 而此时根结点小于所有父结点，因而在调整时只需考虑最大孩子的分支即可
        Heapify<T>(arr, i, 0); 
    }   
}

int main()
{
    int data[] = {8, 4, 3, 1, 6, 9, 5, 7, 2, 0};
    int length = sizeof(data) / sizeof(data[0]);
    printf("Array Element: ");
    for(int i = 0; i < length; i++)
    {
        printf("%d,", data[i]);
    }
    printf("\n");
    printf("HeapSort: ");
    HeapSort<int>(data, length);
    for (int i = 0; i < length; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
    return 0;
}
