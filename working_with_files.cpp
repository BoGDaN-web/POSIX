#include <iostream>    // Для ввода-вывода через std::cout и std::cerr
#include <unistd.h>    // Для системного вызова fork() и getpid()
#include <sys/types.h> // Для определения типа pid_t
#include <sys/wait.h>  // Для wait()

int main()
{
    pid_t pid = fork(); // Создание дочернего процесса

    if (pid == -1)
    {
        // Если fork() возвращает -1, произошла ошибка
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    }
    else if (pid == 0)
    {
        // Код, выполняющийся в дочернем процессе
        std::cout << "Hello from child process! PID: " << getpid() << std::endl;
    }
    else
    {
        // Код, выполняющийся в родительском процессе
        std::cout << "Hello from parent process! PID: " << getpid()
                  << ", Child PID: " << pid << std::endl;

        // Ожидание завершения дочернего процесса
        int status;
        wait(&status); // Родитель ожидает завершения дочернего процесса
        std::cout << "Child process completed with status: " << status << std::endl;
    }

    return 0;
}