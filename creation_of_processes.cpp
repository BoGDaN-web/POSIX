#include <unistd.h>
#include <iostream>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    }

    if (pid == 0)
    {
        // Дочерний процесс
        std::cout << "Child process (PID: " << getpid() << ")" << std::endl;
        execlp("/bin/ls", "ls", "-l", NULL);
        // Если execlp вернулся, значит произошла ошибка
        std::cerr << "Execution failed!" << std::endl;
        return 1;
    }
    else
    {
        // Родительский процесс
        std::cout << "Parent process (PID: " << getpid() << "), waiting for child..." << std::endl;
        wait(NULL); // Ждем завершения дочернего процесса
        std::cout << "Child process finished!" << std::endl;
    }

    return 0;
}