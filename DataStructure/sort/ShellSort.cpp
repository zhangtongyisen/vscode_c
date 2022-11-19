//希尔排序的实现
#include<iostream>
using namespace std;
//希尔排序
template<class T>
T ShellSort(T array,int size){
    int spilt = size / 2;
    while(spilt){
        for (int i = 0; i < size;i+=spilt){
            for (int j = i; j > 0;j-=spilt){
                if(array[j]<array[j-spilt]){
                    swap(array[j], array[j - spilt]);
                }
            }
        }
        spilt /= 2;
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

    int* result = ShellSort(array, size_a);

    while(size_a){
        cout << *result<< ' ';
        result++;
        size_a--;
    }
    delete[] array;
    delete[] result;
    return 0;
}