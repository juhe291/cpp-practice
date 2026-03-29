#include <iostream>
#include <cstdlib>

using namespace std;

//////////////////////////////////////////////////
//function name:merge_array
//describe:合并两个有序（升序）的数组（int[]）,合并后的数组存放到第三个数组中，并保持第三个数组有序（升序）。
//class name:
//In:int * pa 第1个数组的指针
//In:size_t numa 第1个数组的元素个数
//In:int * pb 第2个数组的指针
//In:size_t numb 第2个数组的元素个数
//In/Out:int * pDes 合并后的数组指针
//Return:void
//Author:Zhang.Z.T
//Date:12/16/2024
//////////////////////////////////////////////////
void merge_array(int* pa, size_t numa, int* pb, size_t numb, int* pDes) {
    if (!pa || !pb) { return; }// 如果有任何一个数组指针为空，则返回
    if (!pDes) { pDes = new int[numa + numb]; }
    int* p1 = pa; int* p2 = pb; int* pd = pDes;
    int* pe1 = pa + numa; int* pe2 = pb + numb;//超尾位置
    //有任何一个数组没有到头的情况下，需要进行合并
    while (p1 != pe1 || p2 != pe2) {
        if (p1 != pe1 && p2 != pe2) {
            if (*p1 <= *p2) {
                *pd = *p1;
                p1++;
                ++pd;
            }
            else if (*p1 >= *p2) {
                *pd = *p2;
                p2++;
                ++pd;
            }
        }
        else {
            if (p1 == pe1) {
                *pd = *p2;
                p2++;
                ++pd;
            }
            else if (p2 == pe2) {
                *pd = *p1;
                p1++;
                ++pd;
            }
        }
    }
}

//显示一个int数组的所有元素，中间用空格间隔，最后输出一个换行
void display(int* parray, int n, char ch) {
    for (int i = 0; i < n; ++i) {
        cout << *(parray++) << ch;
    }
    cout << endl;
}

int main()
{
    int num1(0), num2(0);
    int* p1 = nullptr;
    int* p2 = nullptr;

    cin >> num1;
    p1 = new int[num1];
    for (int i = 0; i < num1; ++i) {
        cin >> p1[i];
    }

    cin >> num2;
    p2 = new int[num2];
    for (int i = 0; i < num2; ++i) {
        cin >> p2[i];
    }

    int nums = num1 + num2;
    int* pdes = new int[nums];

    merge_array(p1, num1, p2, num2, pdes);
    display(pdes, nums, ' ');

    return 0;
}