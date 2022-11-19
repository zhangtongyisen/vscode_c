//计数排序
#include<iostream>
using namespace std;
//计数排序
void CountSort(int arr[], int size);

//主函数
int main(int argc, char const *argv[])
{
   //{10,9,8,5,6,7,4,3,2,1}
    int array[10] = {9,10,8,5,6,7,4,3,2,1};
    

    CountSort(array, 10);

    for(auto s:array)
        cout << s << ' ';
    return 0;
}
//计数排序
void CountSort(int arr[], int size){
    //长度小于3，本身就是有序的
    if (size<3)
        return ;
    //寻找最大元素，分配一个max+1的计数数组
    int max = arr[0];
    for (int i = 1; i < size; i++)
    {
        /* code */
        if(max<arr[i])
            max = arr[i];
    }
    //在动态数组建立时是未进行初始化的，需要加（）默认初始化元素为0.不加就为任意值
    int *countArr = new int[max+1]();
    //计数每个元素出现次数。下标代表元素，值代表出现次数
    for (int i = 0; i < size; i++)
    {
        /* code */
        countArr[arr[i]]++;
    }
    //计算累积数组，维持排序稳定性。确定元素最终位置，注意此时数组长度变了
    for (int i = 1; i < max+1; i++)
    {
        /* code */
        countArr[i] += countArr[i - 1];
    }
    //建立最终结果数组
    int *output = new int[size]();
    for (int i = 0; i < size; i++)
    {
        /* code */
        //countArr[arr[i]]-1代表了要存入结果数组的下标，从零开始所以要减一。
        int pos = countArr[arr[i]] - 1;
        output[pos] = arr[i];
        countArr[arr[i]]--;
    }
    //结果复制回原数组
    for (int i = 0; i < size; i++)
    {
        /* code */
        arr[i] = output[i];
    }
    
}
