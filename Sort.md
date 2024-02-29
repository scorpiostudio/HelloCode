# 十大经典排序算法
![](image\SortSummary.png)
- 稳定：如果a=b并且a原本在b前面，排序后a仍然在b前面；
- 不稳定：如果a=b并且a原本在b前面，排序后a可能在b后面；
- 内排序：所有排序操作都在内存中完成；
- 外排序：由于数据太大，因此把数据放在磁盘中，而排序通过磁盘和内存的数据传输才能进行；
- 时间复杂度：算法执行所耗费的时间。
- 空间复杂度：算法执行所耗费的内存空间。
- 选出前n个大的元素应该选择冒泡排序、选择排序、堆排序等每轮能保证选出最大的元素。

## 一、选择排序
### 1、选择排序
- 选择排序(Selection Sort)是一种最简单直观的排序算法。
- 选择排序算法描述：
    - 1、在未排序序列中找到最小(大)元素，存放到排序序列的起始位置。
    - 2、然后再从剩余未排序元素中继续寻找最小(大)元素，然后放到已排序序列的末尾。
    - 3、以此类推，直到所有元素均排序完毕。 

![](image\SelectSort.gif)
-  选择排序的工作原理：每一次从待排序的数据元素中选出最小(或最大)的一个元素，存放在序列的起始位置，直到全部待排序的数据元素排完。每一趟选择出的元素都会放在它的最终位置。
### 2、选择排序实现
```cpp
template <class T>
void Swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
void SelectSort(T array[], int n, bool min2max = true) 
{
    for(int i = 0; i < n; i++) 
    {
        int index = i;
        for(int j = i; j < n; j++) 
        {
            if(min2max ? (array[j] < array[index]) : (array[j] > array[index])) 
            {
                index = j; //更新最小数/最大数的索引
            }
        }
        Swap<T>(array[i], array[index]);
    }
}
```
### 3、选择排序算法分析
- 算法分析：
    - 不稳定排序算法
    - 平均时间复杂度为O(n^2)
    - 最好时间复杂度O(n^2)
    - 最坏时间复杂度O(n^2)
    - 空间复杂度O(1)：需要一个辅助空间
- 选择排序的主要优点与数据移动有关。如果某个元素位于正确的最终位置上，则它不会被移动。选择排序每次交换一对元素，它们当中至少有一个将被移到其最终位置上，因此对n个元素的表进行排序总共进行至多n-1次交换。在所有的完全依靠交换去移动元素的排序方法中，选择排序属于非常好的一种。
- 选择排序的交换操作介于0和(n-1)次之间；选择排序的比较操作为n(n-1)/2次；选择排序的赋值操作介于0和3(n-1)次之间，一次交换会赋值3次。
- 比较次数为O(n^2)，比较次数与关键字的初始状态无关，总比较次数N = (n-1) + (n-2) +…+ 1 = n x (n-1)/2。
- 交换次数为O(n)：最好情况(已经有序)交换0次；最坏情况(逆序)交换n-1次。


## 二、冒泡排序
### 1、冒泡排序
- 冒泡排序是一种简单的排序算法，通过对待排序序列从前向后(从下标较小的元素开始)，依次对相邻两个元素的值进行两两比较，若发现逆序则交换，使值较大/较小的元素逐渐从前移向后部，越大/越小的元素经过交换会慢慢上浮到数列的顶端。
- 冒泡排序算法描述：
    - 1、比较相邻的元素。如果第一个比第二个大/小，就交换两个元素。
    - 2、对每一对相邻元素作比较交换工作，从开始第一对到结尾的最后一对。此时，最后元素必然是最大/最小数。
    - 3、针对所有元素重复上述步骤，除了最后一个。
    - 4、持续对越来越少的元素重复上述步骤，直到没有任何一对数字需要比较。

![](image\BubbleSort.gif)
- 冒泡排序会重复地遍历要排序的数列，一次比较两个元素，如果顺序错误就进行交换。走遍历数列的工作是重复地进行直到没有再需要交换为止。
### 2、冒泡排序实现
```cpp
template <class T>
void Swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
void BubbleSort(T a[], int n, bool min2max = true) 
{
    for(int i = 0; i < n; i++) 
    {
        for(int j = 1; j < n - i; j++) 
        {
            if(min2max ? (a[j - 1] > a[j]) : (a[j - 1] < a[j])) 
            {
                Swap<T>(a[j - 1], a[j]);
            }
        }
    }
}
```

### 3、冒泡排序算法分析
- 算法分析：
    - 稳定排序算法
    - 平均时间复杂度为O(n^2)
    - 最好时间复杂度O(n)：最好情况是待排序数组全部有序，此时只需遍历一次
    - 最坏时间复杂度O(n^2)：最坏情况是待排序数组全部反序，内层每次遍历已排序部分
    - 平均空间复杂度O(1)：需要一个辅助空间
- 冒泡排序涉及相邻两两数据的比较，故需要嵌套两层for循环来控制;
- 外层循环n次，内层最多时循环n–1次、最少循环0次，平均循环(n-1)/2，循环体内总的比较交换次数为：n*(n-1) / 2 = (n^2-n)/2。
- 最优的空间复杂度为开始元素已排序，则空间复杂度为0；最差的空间复杂度为开始元素为逆排序，则空间复杂度为O(N);
- 冒泡排序毕竟是一种效率低下的排序方法，在数据规模很小时，可以采用。数据规模比较大时，建议采用其它排序方法。

## 三、插入排序
### 1、直接插入排序
- 插入排序(Insert Sort)是一种简单排序算法。通过构建有序序列，对于未排序数据，在已排序序列中从后向前扫描，找到相应位置并插入。插入排序在从后向前扫描过程中，需要反复把已排序元素逐步向后移位，为最新元素提供插入空间。
- 插入排序算法描述：
    - 1、从第一个元素开始，第一个元素可以认为已经被排序
    - 2、取出下一个元素，在已经排序的元素序列中从后向前扫描
    - 3、如果该元素(已排序)大于新元素，将该元素移到下一位置
    - 4、重复步骤3，直到找到已排序的元素小于或者等于新元素的位置
    - 5、将新元素插入到该位置后
    - 6、重复步骤2-5

![](image\InsertSort.gif)

### 2、直接插入排序实现
```cpp
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
```

### 3、插入排序算法分析
- 直接插入排序算法分析：
    - 稳定排序算法
    - 平均时间复杂度为O(n^2)
    - 最好时间复杂度O(n)：最好情况是待排序数组全部有序，此时只需遍历一次
    - 最坏时间复杂度O(n^2)：最坏情况是待排序数组全部反序，内层每次遍历已排序部分
    - 空间复杂度O(1)：需要一个辅助空间
- 插入排序不适合对大规模数据量进行排序，但如果需要排序数据量很小，例如量级小于千，那么插入排序是一个不错的选择。尤其**当数据基本有序时，采用插入排序可以明显减少数据交换和数据移动次数，进而提升排序效率**。
- 最好情况是全部有序，只需遍历一次，最好的时间复杂度为O(n)；最坏情况全部反序，内层每次遍历已排序部分，最坏时间复杂度为O(n^2)。
- 在待排序的元素序列基本有序的前提下，效率最高的排序方法是插入排序。

### 4、折半插入排序实现
- 由于直接插入排序每次往前插入时，按顺序依次往前查找，数据量较大时，必然比较耗时，效率低。因此，在往前查找合适的插入位置时可以采用二分查找方式，即折半插入。
- 折半插入排序相对直接插入排序而言：平均性能更快，时间复杂度降至O(NlogN)，排序是稳定的，但排序的比较次数与初始序列无关，相比直接插入排序，在速度上有一定提升。
- 折半排序算法描述：
    - 1、从第一个元素开始，第一个元素可以认为已经被排序
    - 2、取出下一个元素，在已经排序的元素序列中二分查找到第一个比它大/小的数的位置
    - 3、将新元素插入到该位置后
    - 4、重复上述两步

```cpp
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
```

- 折半插入排序，是对插入排序算法的一种改进，是稳定的排序算法。由于排序算法过程中不断地依次将元素插入前面已排好序的序列中，因此前半部分为已排好序的数列，可以不用按顺序依次寻找插入点，采用折半查找的方法来加快寻找插入点的速度。
- 折半查找只是减少了比较次数，但元素的移动次数不变。折半插入排序平均时间复杂度为O(n^2)；空间复杂度为O(1)。


## 四、希尔排序
### 1、希尔排序
- 希尔排序是Donald Shell于1959年提出的一种插入排序算法，是对简单插入排序改进的高效版本，称为缩小增量排序。希尔排序与直接插入排序的不同之处在于，希尔排序会优先比较距离较远的元素。
- 希尔排序先将整个待排元素序列分割成若干个子序列(由相隔某个增量的元素组成)分别进行直接插入排序，然后依次缩减增量再进行排序，待整个序列中的元素基本有序(增量足够小)时，再对全体元素进行一次直接插入排序。
- 插入排序算法描述：
    - 1、选择一个增量序列t1，t2，…，tk，其中ti>tj，tk=1。
    - 2、按增量序列个数k，对序列进行k趟排序。
    - 3、每趟排序，根据对应的增量ti，将待排序列分割成若干长度为m 的子序列，分别对各子表进行直插入排序。仅增量因子为1时，整个序列作为一个表来处理，表长度即为整个序列的长度。

![](image\ShellSort.png)

### 2、希尔排序实现
```cpp
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
        for(int i = 0; i < n; ++i)
        {
            for(int j = i; j >= h && a[j] < a[j - h]; j = j - h)
            {
                Swap<T>(a[j], a[j - h]);
            }
        }
        h= h / 3;//减小间距
    }
 }
```

### 3、希尔排序算法分析
- 算法分析：
    - 不稳定排序算法
    - 平均时间复杂度为O(NlogN)
    - 最好时间复杂度O(NlogNlogN)
    - 最坏时间复杂度O(NlogNlogN)
    - 空间复杂度O(1)：需要一个辅助空间

- 希尔排序由于是按照增量排序，步长不同可能元素不一定到其最终位置。

## 五、归并排序
### 1、归并排序
- 归并排序是建立在归并操作上的一种稳定排序算法，是采用分治法(Divide and Conquer)的一个典型应用，分治模式在每一层递归上有三个步骤：
    - 分解(Divide)：将n个元素分成个含n/2个元素的子序列。
    - 解决(Conquer)：用合并排序法对两个子序列递归的排序。
    - 合并(Combine)：合并两个已排序的子序列已得到排序结果。
- 归并排序算法递归实现：
    - 1、把长度为n的输入序列分成两个长度为n/2的子序列；
    - 2、对这两个子序列分别采用归并排序；
    - 3、将两个排序好的子序列合并成一个最终的排序序列。

- 归并排序算法迭代实现：
    - 1、申请空间，使其大小为两个已经排序序列之和，用于存放合并后的序列。
    - 2、设定两个指针，最初位置分别为两个已经排序序列的起始位置。
    - 3、比较两个指针所指向的元素，选择相对小的元素放入到合并空间，并移动指针到下一位置。
    - 4、重复步骤3直到某一指针到达序列尾。
    - 5、将另一序列剩下的所有元素直接复制到合并序列尾。

![](image\MergeSort.gif)

### 2、归并排序实现
- 归并排序的递归实现主要在于递归分治：
    - 递归划分左右两个子序列，函数递归到最深处时，一个数据即为一个子序列然后利用递归回调的特性。
    - 对所有子序列进行归并排序，即可完成整个序列的排序。

![](image\MergeSort-Recursive1.png)
![](image\MergeSort-Recursive2.png)

```cpp
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
```

- 归并排序的非递归实现主要在于子序列区间的划分，若直接对半分，则两个子序列都可能不是有序的：
    - 可以从子序列长度为1开始进行归并，即一个数据为一个子序列。
    - 从而得到区间长度为2的子序列，并对其进行归并，又会得到区间长度为4的有序子序列。
    - 通过一次次扩大有序子序列的长度，并对其进行归并，即可实现原序列的整体有序。

![](image\MergeSort-NoRecursive1.png)
![](image\MergeSort-NoRecursive2.png)
![](image\MergeSort-NoRecursive3.png)

```cpp
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
```

### 3、归并排序算法分析
- 算法分析：
    - 稳定排序算法
    - 平均时间复杂度为O(NlogN)
    - 最好时间复杂度O(NlogN)
    - 最坏时间复杂度O(NlogN)
    - 空间复杂度O(N)

- 归并排序的性能不受输入数据的影响，但表现比选择排序好的多，因为始终都是O(nlogn)的时间复杂度。代价是需要额外的内存空间。
- 归并的空间复杂度就是那个临时的数组和递归时压入栈的数据占用的空间：n + logn，所以空间复杂度为: O(n)。
- m个元素k路归并的归并趟数s=logk(m)

## 六、快速排序
### 1、快速排序
- 快速排序的基本思想：通过一趟排序将待排记录分隔成独立的两部分，其中一部分记录的关键字均比另一部分的关键字小，则可分别对这两部分记录继续进行排序，以达到整个序列有序。
- 快速排序算法描述：
    - 1、从数列中挑出一个元素，称为基准pivot；
    - 2、重新排序数列，所有元素比基准值小的放在基准前面，所有元素比基准值大的放在基准后面(相同的数可以到任一边)。在这个分区退出之后，该基准就处于数列的中间位置。这个称为分区(partition)操作；
    - 3、递归地把小于基准值元素的子数列和大于基准值元素的子数列排序。

![](image\QuickSort.gif)

### 2、快速排序实现
```cpp
template <class T>
void Swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

template<typename T>
void QuickSort_Recursive(T arr[], int start, int end) 
{
    if(start >= end) 
        return;
    T mid = arr[end];
    int left = start, right = end - 1;
    while(left < right) 
    {
        while(arr[left] < mid && left < right) 
            left++;
        while(arr[right] >= mid && left < right) 
            right--;
        Swap<T>(arr[left], arr[right]);
    }
    if(arr[left] >= arr[end])
        Swap<T>(arr[left], arr[end]);
    else
        left++;
    QuickSort_Recursive(arr, start, left - 1);
    QuickSort_Recursive(arr, left + 1, end);
}

template<typename T>
void QuickSort(T arr[], int len) 
{
    QuickSort_Recursive(arr, 0, len - 1);
}
```

### 3、快速排序算法分析
- 算法分析：
    - 不稳定排序算法
    - 平均时间复杂度为O(NlogN)
    - 最好时间复杂度O(NlogN)
    - 最坏时间复杂度O(N^2)
    - 空间复杂度O(logN)：递归栈

- 递归是一种使用相同的方法，通过解决问题的子集以达到解决整个问题的方法，是一种使用有限代码解决无限计算的方法。

## 七、堆排序
### 1、堆排序
- 堆排序(Heapsort)是指利用堆数据结构设计的一种排序算法。堆积是一个近似完全二叉树的结构，并同时满足堆积的性质：即子结点的键值或索引总是小于或者大于它的父节点。
- 堆中每一个节点的值都必须大于等于或小于等于其左右子节点的值。
- 大顶堆是每个节点都大于等于其子树节点的堆，根是最大值，用于升序排序。
- 小顶堆是每个节点都小于等于其子树节点的堆，根是最小值，用于降序排序。

- 堆排序其实也是一种选择排序，是一种树形选择排序。只不过直接选择排序中，为了从R[1…n]中选择最大记录，需比较n-1次，然后从R[1…n-2]中选择最大记录需比较n-2次。事实上这n-2次比较中有很多已经在前面的n-1次比较中已经做过，而树形选择排序恰好利用树形的特点保存了部分前面的比较结果，因此可以减少比较次数。对于n个关键字序列，最坏情况下每个节点需比较log2(n)次，因此其最坏情况下时间复杂度为nlogn。堆排序为不稳定排序，不适合记录较少的排序。

- 堆排序算法描述：
    - 1、首先将待排序的数组构造成一个大根堆，此时，整个数组的最大值就是堆结构的顶端
    - 2、将顶端的数与末尾的数交换，此时，末尾的数为最大值，剩余待排序数组个数为n-1
    - 3、将剩余的n-1个数再构造成大根堆，再将顶端数与n-1位置的数交换，如此反复执行，便能得到有序数组

![](image\HeapSort.gif)

### 2、堆排序实现
```cpp
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
```

### 3、堆排序算法分析
- 算法分析：
    - 不稳定排序算法
    - 平均时间复杂度为O(NlogN)
    - 最好时间复杂度O(NlogN)
    - 最坏时间复杂度O(NlogN)
    - 空间复杂度O(1)：需要一个辅助空间

- 堆是实现优先级队列最直接、最高效的方法。因为，堆和优先级队列非常相似，一个堆就可以看作一个优先级队列。往优先级队列中插入一个元素，就相当于往堆中插入一个元素；从优先级队列中取出优先级最高的元素，就相当于取出堆顶元素（大顶堆--最大值；小顶堆--最小值）
- 堆排序包括建堆和排序两个操作，建堆过程的时间复杂度是O(n)，排序过程的时间复杂度是O(nlogn)，所以堆排序整体的时间复杂度是O(nlogn)。
- 排序不需要占用额外的空间，只需要交换元素的需要一个临时变量，所以堆排序的空间复杂度为O(1)。
-  堆排序如果要求升序则建立大顶堆，降序则建立小顶堆，堆顶元素为最大或者最小的元素，将堆顶元素与最后一个位置的元素交换，再将剩余元素还原成大小顶堆，每一趟都会选出一个未排序中的最大或者最小值放到最终位置。
- 插入建堆的时间复杂度是O(NlogN)，筛选法建堆的时间复杂度是O(N)。

## 八、计数排序
### 1、计数排序
- 计数排序(Counting Sort)是一种稳定的排序算法，利用一个额外的统计数组C，其中第i个元素是待排序数组A中值等于i的元素的个数，然后根据数组C来将A中的元素排到正确的位置。
- 计数排序的核心在于将输入的数据值转化为键存储在额外开辟的数组空间中。 作为一种线性时间复杂度的排序，计数排序要求输入的数据必须是有确定范围的整数。
- 计数排序算法描述：
    - 1、找出待排序的数组中最大和最小的元素。
    - 2、统计数组中每个值为i的元素出现的次数，存入数组C的第i项。
    - 3、遍历统计数组C，将数组C中索引值的个数平移至数组A。

![](image\CountSort.gif)

### 2、计数排序实现
```cpp
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
        int count = countArray[i];
        while(count > 0)
        {
            arr[j++] = min + i;
            count--;
        }
    }

    delete [] countArray;
    countArray = NULL;
}
```

### 3、计数排序算法分析
- 算法分析：
    - 稳定排序算法
    - 平均时间复杂度为O(n+k)
    - 最好时间复杂度O(n+k)
    - 最坏时间复杂度O(n+k)
    - 空间复杂度O(k)：

- 计数排序的局限性如下：
    - 当数据最大值和最小值差距过大时不适用于计数排序，因此计数排序只适用于元素值较为集中的情况。
    - 计数只能对整数进行排序。当数列元素不是整数时，并不适用于计数排序。


## 九、桶排序
### 1、桶排序
- 桶排序(Bucket Sort)是计数排序的升级版，利用函数映射关系将数组元素划分到不同的桶中，将不同桶中元素进行排序然后拼接。
假设待排序的数组a中共有N个整数，并且已知数组a中数据的范围[0, MAX)。在桶排序时，创建容量为MAX的桶数组r，并将桶数组元素都初始化为0；将容量为MAX的桶数组中的每一个单元都看作一个桶。

- 桶排序算法描述：
    - 设置桶大小BucketSize，确定每个桶能放置多少个不同数值，相同值可以放置多个；
    - 遍历输入数据，根据某种函数映射关系将数据放到不同桶中；
    - 对每个非空的桶进行排序，可以使用其它排序方法，也可以递归使用桶排序；
    - 从非空的桶里把排好序的数据拼接起来。
![](image\BucketSort.gif)
### 2、桶排序实现
```cpp
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
```

### 3、桶排序算法分析
- 算法分析：
    - 稳定排序算法
    - 平均时间复杂度为O(n+k)
    - 最好时间复杂度O(n+k)
    - 最坏时间复杂度O(n^2)
    - 空间复杂度O(n+k)：
- 桶排序适合用于待排序数据分布比较均匀的情况，如果数据分布不均匀，可能会导致某些桶中的数据量过大，从而影响排序效果。

## 十、基数排序
### 1、基数排序
- 基数排序是对桶排序的升级版，从低位开始将待排序的数按照低位的值放到相应的编号为0~9的桶中。等到低位排完得到一个子序列，再将子序列按照次低位的大小进入相应的桶中，一直排到最高位为止，数组排序完成。

- 基数排序算法描述：
    - 取得数组中的最大数并取得位数；
    - 对数位较短的数进行前面补零；
    - 从个位开始分配，根据位值(0-9)分别放在(0-9)号桶中；
    - 收集数据放在(0-9)号桶中的数据按顺序放到数组中；
    - 重复3~4过程，直到最高位，即可完成排序。

![](image\RadixSort.gif)
- 基数排序的原理：将整数按位数切割成不同的数字，然后按每个位数分别比较。基数排序的方式可以采用LSD(Least significant digital)或MSD(Most significant digital)，LSD先从低位开始进行排序，在每个关键字上，可采用桶排序;MSD先从高位开始进行排序，在每个关键字上，可采用计数排序。
### 2、基数排序实现
```cpp
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
```

### 3、基数排序算法分析
- 算法分析：
    - 稳定排序算法
    - 平均时间复杂度为O(n*k)
    - 最好时间复杂度O(n*k)：
    - 最坏时间复杂度O(n*k)：
    - 空间复杂度O(n+k)：
- 基数排序是经典的空间换时间的方式，占用内存很大, 当对海量数据排序时，容易造成OutOfMemoryError。
- 有负数的数组，不能使用基数排序来进行排序, 如果要支持负数，需要添加绝对值并反转。


- 源码：https://github.com/scorpiostudio/HelloCode
- 参考资料：
    - https://www.cnblogs.com/guoyaohua/p/8600214.html
    - https://blog.csdn.net/qq_44625774/category_10109833.html
