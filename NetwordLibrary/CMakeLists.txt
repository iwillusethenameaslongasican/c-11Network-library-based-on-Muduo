cmake_minimum_required(VERSION 3.6)
project(SimpleNetwordLibrary)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Net/Socket.h Net/Socket.cpp Net/Socketopts.h Net/Socketopts.cpp Net/InetAddress.h Net/InetAddress.cpp Net/Endian.h Base/Types.h Base/StringPiece.h Base/Mutex.h Base/Thread.h Base/Thread.cpp Base/CurrentThread.h Base/testThread.cpp Base/TimeStamp.h Base/TimeStamp.cpp Base/testTimestamp.cpp Base/Condition.h Base/Condition.cpp Base/CountDownLatch.h Base/CountDownLatch.cpp Base/testCondition.cpp Base/BlockingQueue.h Base/BlockingQueueTest.cpp Base/BoundedBlockingQueue.h Base/BoundedBlockingQueueTest.cpp Base/ThreadPool.h Base/ThreadPool.cpp Base/ThreadPoolTest.cpp Base/Logger.h Base/Logger.cpp Base/LogStream.h Base/LogStream.cpp Base/LogTest1.cpp Base/LogTest2.cpp Base/LogFile.h Base/LogFile.cpp Base/FileUtil.h Base/FileUtil.cpp Base/LogFileTest.cpp Base/LogFileTest2.cpp)
add_executable(SimpleNetwordLibrary ${SOURCE_FILES})

set(SOURCE_FILES Base/Thread.h Base/Thread.cpp Base/CurrentThread.h Base/testThread.cpp)
add_executable(testThread ${SOURCE_FILES})
find_package(Threads REQUIRED)
target_link_libraries(testThread Threads::Threads)

set(SOURCE_FILES Base/TimeStamp.h Base/TimeStamp.cpp Base/testTimestamp.cpp)
add_executable(testTimestamp ${SOURCE_FILES} Base/LogFileTest2.cpp)

set(SOURCE_FILES Base/Mutex.h Base/Thread.h Base/Thread.cpp Base/CurrentThread.h Base/Condition.h Base/Condition.cpp Base/CountDownLatch.h Base/CountDownLatch.cpp Base/testCondition.cpp)
add_executable(testCondition ${SOURCE_FILES})
find_package(Threads REQUIRED)
target_link_libraries(testCondition Threads::Threads)

set(SOURCE_FILES Base/Mutex.h Base/Thread.h Base/Thread.cpp Base/CurrentThread.h Base/Condition.h Base/Condition.cpp Base/CountDownLatch.h Base/CountDownLatch.cpp Base/BlockingQueue.h Base/BlockingQueueTest.cpp)
add_executable(BlockingQueue ${SOURCE_FILES} Base/LogFileTest2.cpp)
find_package(Threads REQUIRED)
target_link_libraries(BlockingQueue Threads::Threads)

set(SOURCE_FILES Base/Mutex.h Base/Thread.h Base/Thread.cpp Base/CurrentThread.h Base/Condition.h Base/Condition.cpp Base/CountDownLatch.h Base/CountDownLatch.cpp Base/BoundedBlockingQueue.h Base/BoundedBlockingQueueTest.cpp)
add_executable(BoundedBlockingQueue ${SOURCE_FILES})
find_package(Threads REQUIRED)
target_link_libraries(BoundedBlockingQueue Threads::Threads)

set(SOURCE_FILES Base/Mutex.h Base/Thread.h Base/Thread.cpp Base/CurrentThread.h Base/Condition.h Base/Condition.cpp Base/CountDownLatch.h Base/CountDownLatch.cpp Base/ThreadPool.h Base/ThreadPool.cpp Base/ThreadPoolTest.cpp)
add_executable(ThreadPoolTest ${SOURCE_FILES})
find_package(Threads REQUIRED)
target_link_libraries(ThreadPoolTest Threads::Threads)

set(SOURCE_FILES Base/CurrentThread.h Base/Thread.h Base/Thread.cpp Base/StringPiece.h Base/TimeStamp.h Base/TimeStamp.cpp Base/Logger.h Base/Logger.cpp Base/LogStream.h Base/LogStream.cpp Base/LogTest1.cpp)
add_executable(LogTest1 ${SOURCE_FILES} Base/LogTest2.cpp)
find_package(Threads REQUIRED)
target_link_libraries(LogTest1 Threads::Threads)

set(SOURCE_FILES Base/CurrentThread.h Base/Thread.h Base/Thread.cpp Base/StringPiece.h Base/TimeStamp.h Base/TimeStamp.cpp Base/Logger.h Base/Logger.cpp Base/LogStream.h Base/LogStream.cpp Base/LogTest2.cpp)
add_executable(LogTest2 ${SOURCE_FILES} Base/LogFileTest2.cpp)
find_package(Threads REQUIRED)
target_link_libraries(LogTest2 Threads::Threads)

set(SOURCE_FILES Base/Mutex.h Base/ThreadPool.h Base/ThreadPool.cpp Base/Condition.cpp Base/Condition.h Base/CountDownLatch.cpp Base/CountDownLatch.h Base/CurrentThread.h Base/Thread.h Base/Thread.cpp Base/StringPiece.h Base/TimeStamp.h Base/TimeStamp.cpp Base/Logger.h Base/Logger.cpp Base/LogStream.h Base/LogStream.cpp Base/LogFile.h Base/LogFile.cpp Base/FileUtil.h Base/FileUtil.cpp Base/LogFileTest.cpp)
add_executable(LogFileTest ${SOURCE_FILES})
find_package(Threads REQUIRED)
target_link_libraries(LogFileTest Threads::Threads)

set(SOURCE_FILES Base/Mutex.h Base/ThreadPool.h Base/ThreadPool.cpp Base/Condition.cpp Base/Condition.h Base/CountDownLatch.cpp Base/CountDownLatch.h Base/CurrentThread.h Base/Thread.h Base/Thread.cpp Base/StringPiece.h Base/TimeStamp.h Base/TimeStamp.cpp Base/Logger.h Base/Logger.cpp Base/LogStream.h Base/LogStream.cpp Base/LogFile.h Base/LogFile.cpp Base/FileUtil.h Base/FileUtil.cpp Base/LogFileTest2.cpp)
add_executable(LogFileTest2 ${SOURCE_FILES})
find_package(Threads REQUIRED)
target_link_libraries(LogFileTest2 Threads::Threads)