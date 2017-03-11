//
// Created by jackson on 17-3-5.
//

#include "TimeStamp.h"
#include <vector>

using namespace std;
using namespace Mu;
using namespace Base;

void passByValue(Timestamp time)
{
    printf("passByValue: %s\n", time.toString().c_str());
    printf("passByValie: %s\n", time.toFormattedString().c_str());
}

void passByConstReference(const Timestamp &time)
{
    printf("passByConstReference: %s\n", time.toString().c_str());
    printf("passByConstReference: %s\n", time.toFormattedString().c_str());
}

void benchmark()
{
    const int kNumber = 1000 * 1000;
    vector<Timestamp> timeVec;
    timeVec.reserve(kNumber);//先预留kNumber个位置
    for(int i = 0 ;i < kNumber; i ++)
    {
        //插入１００w个now，目的是为了计算gettimeofday的时间
        timeVec.push_back(Timestamp::now());
    }
    //打印第一次插入的时间
    printf("%s\n", timeVec.front().toString().c_str());
    //打印最后一次插入的时间
    printf("%s\n", timeVec.back().toString().c_str());
    //计算时间差
    printf("%f\n", timeDifferent(timeVec.back(), timeVec.front()));

    int increments[100] = {0};
    int64_t start = timeVec.front().microSecondsSinceEpoch();
    for(int i = 1; i < kNumber; i ++)
    {
        int64_t next = timeVec[i].microSecondsSinceEpoch();
        int64_t diff = next - start;
        start = next;
        if(diff < 0)
        {
            printf("reverse!");
        }//时间差小于１００
        else if(diff < 100)
        {
            ++ increments[diff];
        }//时间差大于１００
        else
        {
            printf("big gap %d\n", static_cast<int>(diff));
        }
    }

    for(int i = 0; i < 100; ++i)
    {
        printf("%2d: %d\n", i, increments[i]);
    }
}

int main()
{
    //构造一个时间戳对象，拷贝构造
    Timestamp now(Timestamp::now());
    printf("%s\n", now.toString().c_str());
    printf("%s\n", now.toFormattedString().c_str());
    //经过测试可以知道，传值和引用对时间戳的效率没有影响，时间戳的复制是通过寄存器进行的
    passByValue(now);
    passByConstReference(now);
    benchmark();
}