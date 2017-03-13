//
// Created by jackson on 17-3-11.
//

#ifndef SIMPLENETWORDLIBRARY_CHANNEL_H
#define SIMPLENETWORDLIBRARY_CHANNEL_H

#include <memory>
#include "../Base/TimeStamp.h"

namespace Mu{
namespace Net{

    class EventLoop;
    //事件处理器　对一个套接字（也可以是其他类型的描述符进行包装）进行包装
    //但是Channel不拥有这个描述符　也就是它不负责这个描述符的生命期
    //Channel一般不由用户直接使用，而是一般使用更高层的封装，例如Tcpconnection
    //Channel的owner负责Channel的生命期，同时也管理套接字（描述符）的生命期
    class Channel
    {
    public:
        typedef std::function<void()> EventCallback;
        typedef std::function<void(Mu::Base::Timestamp)> ReadEventCallback;
        //禁止复制
        Channel(const Channel &channel) = delete;
        Channel& operator=(const Channel &channel) = delete;

        //构造函数
        Channel(EventLoop *loop, int fd):
                loop_(loop),
                fd_(fd),
                events_(0),
                revents_(0),
                index_(-1),
                tied_(false),
                logHug_(true),
                eventHandling_(false),
                addedToLoop_(false)
        {}
        ~Channel();
        //处理事件
        void handleEvent(Mu::Base::Timestamp receiveTime);
        //设置回调函数
        void setReadCallback(const ReadEventCallback&& readCallback)
        {
            readCallback_ = std::move(readCallback);
        }
        void setWriteCallback(const EventCallback&& writeCallback)
        {
            writeCallback_ = std::move(writeCallback);
        }
        void setCloseCallback(const EventCallback&& closeCallback)
        {
            closeCallback_ = std::move(closeCallback);
        }
        void setErrorCallback(const EventCallback&& errorCallback)
        {
            errorCallback_ = std::move(errorCallback);
        }
        //返回文件描述符
        int fd() const
        {
            return fd_;
        }
        //返回事件
        int events() const
        {
            return events_;
        }
        //设置事件
        void set_revent(int revent)
        {
            revents_ = revent;
        }
        //判断是否有事件
        bool isNoneEvent() const
        {
            return events_ == kNoneEvent;
        }
        //启动写
        void enableWrite()
        {
            events_ |= kWriteEvent;
            update();
        }
        //启动读
        void enableRead()
        {
            events_ |= kReadEvent;
            update();
        }
        //禁止写
        void disableWrite()
        {
            events_ &= ~kWriteEvent;
            update();
        }
        //禁止读
        void disableRead()
        {
            events_ &= ~kReadEvent;
            update();
        }
        //禁止所有
        void disableAll()
        {
            events_ = kNoneEvent;
            update();
        }
        //判断是否在写
        bool isWriting() const
        {
            return (events_ & kWriteEvent);
        }
        //返回索引
        int index() const
        {
            return index_;
        }
        //设置索引
        void set_index(int index)
        {
            index_ = index;
        }
        //把当前的chanel绑定到它的由shared_ptr管理的owner对象
        //防止owner对象在handleEvent时析构
        //tie:把当前channel（事件处理器）依附到某一个对象上
        void tie(const std::shared_ptr<void> &);

        //用于调试　把事件转换成字符串
        std::string eventToString();
        std::string reventToString();
        //不记录pollhup事件(POLLHUP 	对方描述符挂起)
        void doNotLogHup()
        {
            logHug_ = false;
        }

        //返回所属的时间循环
        EventLoop * ownerLoop()
        {
            return loop_;
        }
        //从事件循环对象中把中间删除
        void remove();

    private:
        static std::string eventsToString(int fd, int event);

        //更新
        void update();

        //处理事件
        void handleEventWithGuard(Mu::Base::Timestamp receiveTime);

        //没事件
        static const int kNoneEvent;
        //读事件
        static const int kWriteEvent;
        //写事件
        static const int kReadEvent;

        //所属的事件循环
        EventLoop *loop_;
        //文件描述符 注意：Channel负责它的生命期　它的生命期由Channle的Owner复制
        const int fd_;
        //当前的事件
        int events_;
        //epoll返回时的活动事件
        int revents_;
        //索引　被Poller使用　表示在poll的事件数组中的序号　epoll中的状态
        int index_;

        //用于把直接依附到某一个对象上
        // tie()的作用是防止Channel::handleEvent() 运行期间其 owner 对象析构，导致 Channel 本身被销毁
        std::weak_ptr<void> tie_;
        bool tied_;
        //是否记录pollhup事件(POLLHUP 	对方描述符挂起)
        bool logHug_;

        //是否正在处理事件
        bool eventHandling_;

        //是否已经被添加到事件队列
        bool addedToLoop_;

        //读事件的回调
        ReadEventCallback readCallback_;
        //写事件的回调
        EventCallback writeCallback_;
        //关闭事件的回调
        EventCallback closeCallback_;
        //错误事件的回调
        EventCallback errorCallback_;
    };
}
}

#endif //SIMPLENETWORDLIBRARY_CHANNEL_H
