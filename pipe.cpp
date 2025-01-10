#include <unistd.h>
#include <iostream>
#include <cstring>
#include <sys/wait.h>

int main()
{
    int pipefd[2]; // Массив для хранения файловых дескрипторов канала
    if (pipe(pipefd) == -1)
    {
        std::cerr << "Pipe creation failed!" << std::endl;
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    }

    if (pid == 0)
    {
        // Дочерний процесс
        close(pipefd[0]); // Закрываем конец для чтения
        const char *message = "Hello from child process!\n";
        write(pipefd[1], message, strlen(message)); // Пишем в канал
        close(pipefd[1]);                           // Закрываем конец для записи
    }
    else
    {
        // Родительский процесс
        close(pipefd[1]); // Закрываем конец для записи
        char buffer[128];
        ssize_t bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1);
        if (bytesRead > 0)
        {
            buffer[bytesRead] = '\0';
            std::cout << "Parent received: " << buffer;
        }
        close(pipefd[0]); // Закрываем конец для чтения
        wait(NULL);       // Ждем завершения дочернего процесса
    }

    return 0;
}