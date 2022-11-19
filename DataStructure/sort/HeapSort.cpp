//堆排序
#include<iostream>
using namespace std;
//维护堆的性质
void Heapify(int arr[], int size, int pos);

//堆排序入口
void HeapSort(int arr[], int size);

//主函数
int main(int argc, char const *argv[])
{
    /* code */
    //{10,9,8,5,6,7,4,3,2,1}
    //{2,3,8,1,4,9,10,7,16,14}
    int array[10] = {2,3,8,1,4,9,10,7,16,14};
    

    HeapSort(array,10);

    for(auto s:array)
        cout << s << ' ';
    return 0;
}
//维护堆的性质
void Heapify(int arr[], int size, int pos){
    //pos其实为父节点的下标
    //若果下标从零开始，则其左孩子下标为pos*2+1，右孩子下标为pos*2+2
    //如果下标从一开始，则左为pos*2，右为pos*2+1
    int l_pos = pos * 2 + 1;//左孩子下标
    int r_pos = pos * 2 + 2;//右孩子下标
    int largest = pos;//父节点下标
    //找到子树最大节点的下标
    if(arr[l_pos]>arr[largest]&&l_pos<size){
        largest = l_pos;
    }
    //注意在这个地方加上else就是错的，比如说已经判断左孩子较大，但右孩子比左孩子更大时不会走右孩子的判断
    if(arr[r_pos]>arr[largest]&&r_pos<size){
        largest = r_pos;
    }
    //如果不满足大（小）顶堆性质，交换元素，递归遍历所有子树。
    if(largest!=pos){
        swap(arr[largest], arr[pos]);
        Heapify(arr, size, largest);
    }
    
}
//堆排序入口
void HeapSort(int arr[], int size){
    //建堆
    int pos;//父节点下标
    //下标（从零开始）为i的节点其父节点为i/2-1
    //从最后一个节点的父节点依次向前寻找
    //调用Heapify函数来维护大（小）顶堆的性质
    for (pos = size / 2 - 1; pos >= 0;pos--){
        Heapify(arr, size, pos);
    }

    //排序
    //堆顶元素与最后一个元素交换位置，重新从堆顶开始维护堆
    for (pos = size - 1; pos >= 0;pos--){
        swap(arr[pos], arr[0]);
        Heapify(arr, pos, 0);
    }
}