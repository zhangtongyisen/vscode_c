//插入排序实现
#include<iostream>
using namespace std;
//插入排序
template<class T>
T InsertionSort(T array,int size){
    for (int i = 0; i < size;i++){
        for (int j = i; j > 0;j--){
            if(array[j]<array[j-1]){
                swap(array[j], array[j - 1]);
            }else break;
        }
    }
    return array;
}
//主函数
int main(int argc, char const *argv[])
{
    /* code */
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

    int* result = InsertionSort(array, size_a);

    while(size_a){
        cout << *result<< ' ';
        result++;
        size_a--;
    }
    delete[] array;
    delete[] result;
    return 0;
}
