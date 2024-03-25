#include <iostream>
#include <thread>

void func(int a){
    while(true)
    {
        std::cout << "Hello World\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
int main()
{
    int a = 0;
    std::thread thread_tmp(func,a);
    std::cout <<"This is a CPP" << std::endl;
    thread_tmp.join();
    return 0;
}