### 以下用来探讨对 堆排序 的一些理解 仅供参考

```HeapSort```是基于构建大根堆/小根堆的方法来实现对数组的排序,其时间复杂度是$O(n\log n) $

接下来说一说大根堆是什么
>大根堆本质上是一种完全二叉树,这样的性质能够让我们直接用一维数组的方式访问某个节点```arr[i]```,其左节点```arr[2*i]```,右节点```arr[2*i+1]```和其父节点```arr[i/2]```;
但是因为数组一般都是从```arr[0]```开始存储数据,所以我们在数组中使用
```arr[i-1]```,```arr[2*i+1]```,```arr[2*i+2]```和```arr[i/2-1]```来访问节点,其左右子节点和其父节点;

**思路**
为了实现堆排序,我们首先得通过数组```arr```构建出一个大根堆
```cpp
vector<int> arr = {5, 6, 7, 11, 12, 13};
void buildMaxHeap(vector<int>& arr);
void heapify(vector<int>& arr, int n, int i);

void buildMaxHeap(vector<int>& arr)
{
    int n = arr.size();
    for(int i = n/2 -1; i >= 0; i--){
        heapify(arr, n, i);
    }
}

void heapify(vector<int>& arr, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    //判断这个节点的左右子节点的元素是否大于该节点的元素
    //如果是则将最大元素的索引改至左/右节点处的索引
    if(left < n && arr[left] > arr[largest])
        largest = left;
    if(right < n && arr[right] > arr[largerst])
        largest = right;
    
    //如果largest更新过了,则交换该节点和largest处的元素,并继续堆化
    if(largest != i)
    {
        swap(arr[i],arr[largest]);
        heapify(arr,n,largest);
    }
}
```
---
在成功构建了一个大根堆后,此时```arr[0]```一定是最大的元素,但是其后的元素并非都排序好了;
但是因为构建一次大根堆得到的```arr[0]```是最大,我们可以通过不断构建大根堆,并且将得到的最大元素移至末尾,这样就能成功将数组排序

```cpp
void heapSort(vector<int>& arr) 
{ 
    int n = arr.size();
    buildMaxHeap(arr); // 构建最大堆 
    // 逐步将堆顶元素移到数组末尾，并调整堆结构 
    for (int i = n - 1; i >= 0; i--) 
    {   
        swap(arr[0], arr[i]); // 将最大值放到数组末尾 
        heapify(arr, i, 0);// 注意 i是在不断减小的 因为我们一直在把最大值放在数组末尾
    } 
}
```