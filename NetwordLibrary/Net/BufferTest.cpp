//
// Created by jackson on 17-3-11.
//

#include "Buffer.h"

using namespace Mu;
using namespace Net;

void test1()
{
    Buffer buffer;
    assert(buffer.readableBytes() == 0);
    assert(buffer.writableBytes() == buffer.kInitialSize);
    assert(buffer.prependableBytes() == buffer.kCheapPrepend);

    const std::string str(200, 'x');
    buffer.append(str);
    assert(buffer.readableBytes() == str.size());
    assert(buffer.writableBytes() == buffer.kInitialSize - str.size());
    assert(buffer.prependableBytes() == buffer.kCheapPrepend);

    const std::string str2 = buffer.retrieveAsString(50);
    assert(str2.size() == 50);
    assert(buffer.readableBytes() == str.size() - str2.size());
    assert(buffer.writableBytes() == buffer.kInitialSize - str.size());
    assert(buffer.prependableBytes() == buffer.kCheapPrepend + str2.size());

    buffer.append(str);
    assert(buffer.readableBytes() == 2*str.size() - str2.size());
    assert(buffer.writableBytes() == buffer.kInitialSize - 2 * str.size());
    assert(buffer.prependableBytes() == buffer.kCheapPrepend + str2.size());

    const std::string str3 = buffer.retrieveAllAsString();
    assert(str3.size() == 350);
    assert(buffer.readableBytes() == 0);
    assert(buffer.writableBytes() == buffer.kInitialSize);
    assert(buffer.prependableBytes() == buffer.kCheapPrepend);
}

void test2()
{
    Buffer buffer;
    buffer.append(std::string(400, 'x'));
    assert(buffer.readableBytes() == 400);
    assert(buffer.writableBytes() == buffer.kInitialSize - 400);
    assert(buffer.prependableBytes() == buffer.kCheapPrepend);

    buffer.retrieve(50);
    assert(buffer.readableBytes() == 350);
    assert(buffer.writableBytes() == buffer.kInitialSize - 400);
    assert(buffer.prependableBytes() == buffer.kCheapPrepend + 50);

    buffer.append(std::string(1000, 'y'));
    assert(buffer.readableBytes() == 1350);
    assert(buffer.writableBytes() == 0);//虽然writableBytes为0，但是因为vector resize了空间　其实还有额外的空间　只是暂时不可用
    assert(buffer.prependableBytes() == buffer.kCheapPrepend + 50);

    buffer.retrieveAll();
    assert(buffer.readableBytes() == 0);
    assert(buffer.writableBytes() == 1400);
    assert(buffer.prependableBytes() == buffer.kCheapPrepend);
}

void test3()
{
    Buffer buffer;
    buffer.append(std::string(2000, 'y'));
    assert(buffer.readableBytes() == 2000);
    assert(buffer.writableBytes() == 0);
    assert(buffer.prependableBytes() == buffer.kCheapPrepend);

    buffer.retrieve(1500);
    assert(buffer.readableBytes() == 500);
    assert(buffer.writableBytes() == 0);
    assert(buffer.prependableBytes() == buffer.kCheapPrepend + 1500);

    buffer.shrink(0);
    assert(buffer.readableBytes() == 500);
    assert(buffer.writableBytes() == buffer.kInitialSize - 500);
    assert(buffer.retrieveAllAsString() == std::string(500, 'y'));
    assert(buffer.prependableBytes() == buffer.kCheapPrepend);
}

void test4()
{
    Buffer buffer;
    buffer.append(std::string(200, 'y'));
    assert(buffer.readableBytes() == 200);
    assert(buffer.writableBytes() == buffer.kInitialSize - 200);
    assert(buffer.prependableBytes() == buffer.kCheapPrepend);

    int x = 0;
    buffer.prepend(&x, sizeof(x));
    assert(buffer.readableBytes() == 204);
    assert(buffer.writableBytes() == buffer.kInitialSize - 200);
    assert(buffer.prependableBytes() == buffer.kCheapPrepend - 4);
}

int main()
{
    test1();
    test2();
    test3();
}