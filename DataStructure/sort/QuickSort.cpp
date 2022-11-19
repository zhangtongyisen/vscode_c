//快速排序
#include<iostream>
#include<math.h>
#include<time.h>
#include<stdlib.h>
using namespace std;
//找出分割点
int partition(int array[], int start, int last);

//递归解决各部分排序
void sort(int array[], int start, int last);

//递归快排程序入口
void QuickSort(int array[], int size);
//主程序
int main(int argc, char const *argv[])
{
    /* code */
    //{10,9,8,5,6,7,4,3,2,1}
    int array[10] = {9,10,8,5,6,7,4,3,2,1};
    

    QuickSort(array,10);

    for(auto s:array)
        cout << s << ' ';
    return 0;

}
//找出分割点并分成大小两部分
int partition(int array[], int start, int last){
    // 随机在arr[l...r]的范围中, 选择一个数值作为标定点pivot
    // rand()，该函数只返回一个伪随机数。生成随机数之前必须先调用 srand() 函数。
    //一般方法会直接选取第一个数组元素作为分割点
    srand((unsigned) time(NULL));//这个地方会出现未知异常导致无法递归出结果
    int random = (int)(rand() % (last - start + 1)) + start;
    //cout << random << ' ';
    swap(array[start], array[random]);
    int sign = array[start];
    //cout << sign << endl;
    int j = start;
    for (int i = start + 1; i <= last; i++)
        if (array[i] < sign)
        {
            j++;
            swap(array[j],array[i]);
        }
    swap(array[start], array[j]);

    
    return j;
}
//递归解决各部分排序
void sort(int array[], int start, int last){
    if (start >= last) {
            return;
        }
    int p = partition(array, start, last);

    sort(array, start, p);
    sort(array, p + 1, last);
}
//递归快排程序入口
void QuickSort(int array[], int size){
    sort(array, 0, size - 1);
}