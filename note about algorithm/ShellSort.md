### 以下用来探讨对 希尔排序 的一些理解 仅供参考

```Shell Sort```是基于选择排序的改进版本,其通过将数组分成多个小段,其中各个小段间隔```gap```,并对每个小段内部进行直接选择排序,然后逐渐减少```gap```的值,直到```gap == 1```时,此时数组就是一整个小段,并对整个数组进行选择排序;
这种分段进行排序的方法,时间复杂度 $ O(n\log n)$ 小于直接进行选择排序的时间复杂度 $O(n^2)$

**思路**
```cpp
void swap(vector<int>&arr,int a1,int a2)
{
    int temp = arr[a1];
    arr[a1] = arr[a2];
    arr[a2] = temp;
}
int main()
{
    vector<int>arr = {64, 34, 25, 12, 22, 11, 90};
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {  //间隔为gap,且gap不断减小
        for (int i = gap; i < n; ++i) {  //从每个小段的最后一个元素开始
            int temp = arr[i];
            int j = i;
            for (; j >= gap && arr[j - gap] > temp; j -= gap) {  //逐渐向前比较排序
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

```
