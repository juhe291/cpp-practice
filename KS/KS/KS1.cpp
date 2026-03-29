///////////////////////////////////////////////
//Function name:get_max
//Describe:利用分治法查找数组中的最大值
//In:int * arr 指向数组的首地址指针变量
//In:int left 数组中中左侧元素的下标
//In:int right 数组中右侧侧元素的下标 例如一个数组4个元素，则左侧下标为0，右侧下标为3
//Out:
//Return: int 数组中的最大值
//Author:Zhang ZT
//Date:2022-12-25
//Modify:
///////////////////////////////////////////////
#include<iostream>
using namespace std;

int get_max(int* arr, int left, int right) {
    if (arr[left] == arr[right]) { return arr[left]; }
    if (right - left == 1) {
        return arr[left] > arr[right] ? arr[left] : arr[right];
    }
    int mid = left + (right - left) / 2;
    int left_max = get_max(arr, left, mid);
    int right_max = get_max(arr, mid+1, right);
    return left_max > right_max ? left_max : right_max;

}

int main() {
    int n = 0;
    cin >> n;
    int* par = new int[n];
    //读取数据
    for (size_t i = 0; i < n; ++i) {
        cin >> par[i];
    }
    int maxvalue = get_max(par, 0, n - 1);
    cout << "maxvalue = " << maxvalue << endl;
    if (par) { delete[] par; par = nullptr; }
    return 0;
}