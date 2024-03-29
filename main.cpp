/*互斥量*/

#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

std::mutex mtx1;
std::mutex mtx2;
int globalVariable = 0;

 void task1()
 {
    for(int i = 0; i < 100000; i++)
    {
        std::lock_guard<std::mutex> lock1(mtx1,std::adopt_lock);    //lock_guard 和 lock搭配使用时必须添加 std::adopt_lock参数
        std::lock_guard<std::mutex> lock2(mtx2,std::adopt_lock);
        std::lock(mtx1,mtx2);

        globalVariable ++;
        globalVariable --;
//        std::this_thread::sleep_for(std::chrono::milliseconds(50));

    }
 }

 void task2()
 {
    for(int i = 0; i < 100000; i++)
    {
        std::lock_guard<std::mutex> lock2(mtx2,std::adopt_lock);
        std::lock_guard<std::mutex> lock1(mtx1,std::adopt_lock);
        std::lock(mtx1,mtx2);
        globalVariable ++;
        globalVariable --;

    }
 }
int main()
{
    std::thread t1(task1);
    std::thread t2(task2);
    t1.join();
    t2.join();
    std::cout << globalVariable << std::endl;
    return 0;
}