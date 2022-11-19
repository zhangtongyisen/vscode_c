//简单选择排序的算法实现
#include<iostream>
using namespace std;
//选择排序
template <class T>
T SelectionSort(T array,int size){
    
    for (int i = 0; i < size; i++)
    {
        /* code */
        
        for (int j = i+1; j < size; j++)
        {
            /* code */
            if(array[i]>array[j]){
                swap(array[i], array[j]);
            }
        }
        
    }
    return array;
}
//主函数
int main(int argc, char const *argv[]){
    //10
    int size;
    cout << "请输入数组大小：";
    cin >> size;
    int size_a = size;
    //{10,9,8,5,6,7,4,3,2,1}
    cout << "请输入数组：";
    int* array = new int[size];
    do
    {
        /* code */
        size--;
        
        cin >> array[size];
        cin.get();
    } while (size);

    int* result = SelectionSort(array, size_a);
    while (size_a)//条件有问题
    {
        /* code */
        cout << *result << ' ';
        size_a--;
        result++;
    }
    delete[] array;
    delete[] result;
    return 0;
}
