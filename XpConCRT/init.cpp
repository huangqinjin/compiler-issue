#include <iostream>
#include <mutex>

struct Init
{
    Init()
    {
        std::cout << "init ConCRT during DLL loading" << std::endl;
        std::mutex m;
        m.lock();
        m.unlock();
    }
} Init;

extern "C" __declspec(dllexport) void init()
{
    std::cout << "init DLL finished" << std::endl;
}
