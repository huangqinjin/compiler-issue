#include <iostream>
#include <mutex>

extern "C" __declspec(dllimport) void init();

int main(int argc, char* argv[])
{
    if (argc > 1 && argv[1][0] == '1')
    {
        std::cout << "init ConCRT in main()" << std::endl;
        std::mutex m;
        m.lock();
        m.unlock();
    }

    init();

    std::cout << "end" << std::endl;
}
