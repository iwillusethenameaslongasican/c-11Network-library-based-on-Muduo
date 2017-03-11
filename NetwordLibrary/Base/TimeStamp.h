//
// Created by jackson on 17-3-4.
//

#ifndef SIMPLENETWORDLIBRARY_TIMESTAMP_H
#define SIMPLENETWORDLIBRARY_TIMESTAMP_H


#include <stdint-gcc.h>
#include <algorithm>

namespace Mu
{
namespace Base
{
    //时间起时点是１970 1月1日０：０：０
    //Timestamp类是可以复制的，而且最好用过传值复制，因为内核使用寄存器来进行传值
    class Timestamp
    {
    public:
        static const int kMicroSecondsPerSecond = 1000 * 1000;

        Timestamp(): microSecondsSinceEpoch_(0){}

        explicit Timestamp(int64_t microSeconds):microSecondsSinceEpoch_(microSeconds){}
        //两个时间戳进行交换
        void swap(Timestamp &other)
        {
            std::swap(microSecondsSinceEpoch_, other.microSecondsSinceEpoch_);
        }

        int64_t microSecondsSinceEpoch() const
        {
            return microSecondsSinceEpoch_;
        }

        std::string toString() const;
        //返回规范的表示当前时间的字符串
        std::string toFormattedString() const;
        //当前时间戳时候有效
        bool valid() const
        {
            return microSecondsSinceEpoch_ > 0;
        }
        //类型转换
        time_t secondsSinceEpoch() const
        {
            return static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);
        }
        //返回当前时间
        static Timestamp now();
        //获取一个失效的时间　(其实就是获取一个默认构造的Timestamp对象）看第一个构造函数
        static Timestamp invalid();

    private:
        int64_t microSecondsSinceEpoch_;
    };

    inline bool operator==(Timestamp t1, Timestamp t2)
    {
        return (t1.microSecondsSinceEpoch() == t2.microSecondsSinceEpoch());
    }

    inline bool operator<(Timestamp t1, Timestamp t2)
    {
        return (t1.microSecondsSinceEpoch() < t2.microSecondsSinceEpoch());
    }

    //计算两个时间戳的时间差
    inline double timeDifferent(Timestamp t1, Timestamp t2)
    {
        int64_t diff = t1.microSecondsSinceEpoch() - t2.microSecondsSinceEpoch();
        //转化为秒数
        return static_cast<double>(diff) / Timestamp::kMicroSecondsPerSecond;
    }

    //在当前时间基础上增加多少秒
    inline Timestamp addTime(Timestamp time, double second)
    {
        //先把秒转化为微秒
        int64_t delta = static_cast<int64_t>(second * Timestamp::kMicroSecondsPerSecond);
    }
}
}

#endif //SIMPLENETWORDLIBRARY_TIMESTAMP_H
