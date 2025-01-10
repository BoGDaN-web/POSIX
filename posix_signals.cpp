#include <csignal>
#include <iostream>
#include <unistd.h>

void signalHandler(int signum)
{
    std::cout << "Signal " << signum << " received!" << std::endl;
}

int main()
{
    struct sigaction sa;
    sa.sa_handler = signalHandler; // Устанавливаем обработчик
    sa.sa_flags = 0;

    // Перехватываем сигнал SIGINT (Ctrl+C)
    sigaction(SIGINT, &sa, nullptr);

    std::cout << "Press Ctrl+C to send SIGINT..." << std::endl;

    // Бесконечный цикл
    while (true)
    {
        sleep(1); // Ждем 1 секунду
    }

    return 0;
}