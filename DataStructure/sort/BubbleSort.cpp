//冒泡排序的简单实现
#include<iostream>
using namespace std;
//冒泡排序
template<class T> 
T BubbleSort(T array,int size){
    for (int i = 0; i < size-1;i++){
        for (int j = 0; j < size-1;j++){
            if(array[j]>array[j+1]){
                swap(array[j], array[j+1]);
            }
        }
    }
        
    return array;
}
//主函数
int main(int argc, char const *argv[]){
    int size;
    cout << "请输入大小：";
    cin >> size;
    int size_a = size;
    cout << "请输入数组：";
    //{10,9,8,5,6,7,4,3,2,1}
    int *array = new int[size_a];
    do
    {
        /* code */
        size--;
        cin >> array[size];
        cin.get();
    } while (size);

    int* result = BubbleSort(array, size_a);

    while(size_a){
        cout << *result<< ' ';
        result++;
        size_a--;
    }
    delete[] array;
    delete[] result;
    
    return 0;
}