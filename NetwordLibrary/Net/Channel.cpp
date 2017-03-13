//
// Created by jackson on 17-3-11.
//

#include <assert.h>
#include <bits/poll.h>
#include <sstream>
#include "Channel.h"
#include "../Base/Logger.h"

using namespace Mu;
using namespace Net;

//没有事件
const int Channel::kNoneEvent = 0;
//读事件
const int Channel::kWriteEvent = POLLOUT;
//写事件
const int Channel::kReadEvent = POLLIN | POLLPRI;

Channel::~Channel()
{
    assert(!eventHandling_);
    assert(!addedToLoop_);
    if(loop_->isInLoopThread())
    {
        assert(!loop_->hasChannel(this));
    }
}

//把当前的channel绑定到它的由shared_ptr管理的owner对象
//防止owner对象在handleEvent时析构
//tie:把当前channel（事件处理器）依附到某一个对象上
void Channel::tie(const std::shared_ptr<void> &obj)
{
    tie_ = obj;
    tied_ = true;
}

//更新
void Channel::update()
{
    addedToLoop_ = true;
    loop_->updateChannel(this);
}

//从reactor中已出它自己
void Channel::remove()
{
    assert(isNoneEvent());
    addedToLoop_ = false;
    loop_->removeChannel(this);
}

//处理事件
void Channel::handleEvent(Mu::Base::Timestamp receiveTime)
{
    std::shared_ptr<void> gurad;
    //如果channel已经绑定了某个对象
    if(tied_)
    {
        //获得绑定的成员
        gurad = tie_.lock();
        //如果该对象存在
        if(gurad)
        {
            //处理事件
            handleEventWithGuard(receiveTime);
        }
    }
    else
    {
        handleEventWithGuard(receiveTime);
    }
}
//POLLIN 	普通或优先级带数据可读
//POLLRDNORM 	普通数据可读
//POLLRDBAND 	优先级带数据可读
//POLLPRI 	高优先级数据可读
//POLLOUT 	普通数据可写
//POLLWRNORM 	普通数据可写
//POLLWRBAND 	优先级带数据可写
//POLLERR 	发生错误
//POLLHUP 	发生挂起
//POLLNVAL 	描述字不是一个打开的文件
//注意：后三个只能作为描述字的返回结果存储在revents中，而不能作为测试条件用于events中。
////处理事件，根据poll返回的活动事件回调设置的各个回调函数
void Channel::handleEventWithGuard(Mu::Base::Timestamp receiveTime)
{
    eventHandling_ = true;
    LOG_TRACE << reventToString();

    //对方套接字关闭
    if((revents_ & POLLHUP) && !(revents_ & POLLIN))
    {
        if(logHug_)
        {
            LOG_WARN << "fd = " << fd_ << " Channel::handleEvent() PollHup";
        }

        if(closeCallback_)
        {
            closeCallback_();
        }
    }
    //描述字不是一个打开的文件
    if((revents_ & POLLNVAL))
    {
        LOG_WARN << "fd = " << fd_ << " Channel::handleEvent() PollNval";
    }
    //出错
    if((revents_ & POLLERR) & (revents_ & POLLNVAL))
    {
        if(errorCallback_)
        {
            errorCallback_();
        }
    }

    //可读
    if(revents_ & (POLLIN | POLLPRI | POLLHUP))
    {
        if(readCallback_)
        {
            readCallback_(receiveTime);
        }
    }
    //可写
    if(revents_ & (POLLOUT))
    {
        if(writeCallback_)
        {
            writeCallback_();
        }
    }

    eventHandling_ = false;
}

//把事件转换成字符串
std::string Channel::eventsToString(int fd, int event)
{
    std::ostringstream oss;
    oss << fd << ": ";
    if(event & POLLIN)
    {
        oss << "IN ";
    }
    if(event & POLLOUT)
    {
        oss << "OUT ";
    }
    if(event & POLLPRI)
    {
        oss << "PRI ";
    }
    if(event & POLLHUP)
    {
        oss << "HUP ";
    }
    if(event & POLLERR)
    {
        oss << "ERR ";
    }
    if(event & POLLNVAL)
    {
        oss << "NVAL ";
    }
    return oss.str().c_str();
}

std::string Channel::eventToString()
{
    return eventsToString(fd_, events_);
}

std::string Channel::reventToString()
{
    return eventsToString(fd_, revents_);
}