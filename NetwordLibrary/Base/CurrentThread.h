//
// Created by jackson on 17-3-4.
//

#ifndef SIMPLENETWORDLIBRARY_CURRENTTHREAD_H
#define SIMPLENETWORDLIBRARY_CURRENTTHREAD_H

#include <cstring>

namespace Mu
{
namespace Base
{
    namespace CurrentThread
    {
//    extern可以置于变量或者函数前，以标示变量或者函数的定义在别的文件中，
// 提示编译器遇到此变量和函数时在其他模块中寻找其定义。
        extern __thread int t_cachedTid;
        extern __thread char t_tidString[32];;
        extern __thread const char *t_threadName;
        //缓存线程的tid
        void cacheTid();//在Thread中定义
        bool isMainThread();

        inline int tid()
        {
            if(t_cachedTid == 0)//还没有被缓存过　进行缓存
            {
                cacheTid();
            }
            return t_cachedTid;//返回被缓存的tid
        }

        inline const char * tidString()
        {
            return t_tidString;//返回tid的字符串表示
        }
        inline const char * tidName()
        {
            return t_threadName;//返回线程的名字
        }


    }
}
}

#endif //SIMPLENETWORDLIBRARY_CURRENTTHREAD_H
