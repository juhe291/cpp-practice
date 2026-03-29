#include<iostream>
using namespace std;

class Time
{
private:
    int Hour, Minute, Second;
    static int count;
public:
    Time(int h = 0, int m = 0, int s = 0);
    Time(Time& t);
    void Change(int h, int m, int s);
    int GetHour();
    int GetMinute();
    int GetSecond();
    void PrintTime();
    ~Time();
    friend void IncreaseOneSecond(Time& t);   //友元函数
};
void f(Time t)
{
    t.PrintTime();
}

int Time::count = 0;
//函数的实现
Time::Time(int h, int m, int s):Hour(h), Minute(m), Second(s){
    count++;
    cout << "Construct" << count << endl;
}
Time::Time(Time& t):Hour(t.Hour), Minute(t.Minute), Second(t.Second) {
    count++;
    cout << "Copy Construct" << count << endl;
}
void Time::Change(int h, int m, int s){
    Hour = h;
    Minute = m;
    Second = s;
}
//获取时分秒
int Time::GetHour() {
    return Hour;
}
int Time::GetMinute() {
    return Minute;
}
int Time::GetSecond() {
    return Second;
}
//打印现在时间
void Time::PrintTime() {
    cout <<  Hour << ":"<<  Minute << ":"<< Second << endl;
}

Time::~Time() {
    cout << count << "Destructor"<< Hour << ":" << Minute << ":" << Second << endl;
    count--;
}

void IncreaseOneSecond(Time& t) {
    t.Second++;
    if (t.Second >= 60)
    {
        t.Second = 0;
        t.Minute++;
        if (t.Minute >= 60)
        {
            t.Minute = 0;
            t.Hour++;
            if (t.Hour >= 24)
            {
                t.Hour = 0;
            }
        }
    }
}

int main()
{
    Time t1;
    Time t2(20);
    Time t3(20, 30);
    Time t4(20, 30, 56);
    f(t4);              //函数f实参为t4
    t1.PrintTime();
    t2.PrintTime();
    t3.PrintTime();
    t4.PrintTime();
    t1.Change(14, 28, 12);
    cout << "ChangeTime" << t1.GetHour() << ":" << t1.GetMinute() << ":" << t1.GetSecond() << endl;
    t4.Change(23, 59, 59);
    cout << "ChangeTime" << t4.GetHour() << ":" << t4.GetMinute() << ":" << t4.GetSecond() << endl;
    IncreaseOneSecond(t4);  //友元函数调用对象t4
    cout << "IncreaseOneSecond" << t4.GetHour() << ":" << t4.GetMinute() << ":" << t4.GetSecond() << endl;
    return 0;
}

