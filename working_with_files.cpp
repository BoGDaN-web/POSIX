#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

int main() {
    const char* filename = "example.txt";

    // Открываем файл для чтения
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        std::cerr << "Error opening file: " << strerror(errno) << std::endl;
        return 1;
    }

    char buffer[128];
    ssize_t bytesRead;

    // Читаем содержимое файла
    while ((bytesRead = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytesRead] = '\0'; // Завершаем строку
        std::cout << buffer;
    }

    if (bytesRead < 0) {
        std::cerr << "Error reading file: " << strerror(errno) << std::endl;
    }

    // Закрываем файл
    close(fd);

    return 0;
}
