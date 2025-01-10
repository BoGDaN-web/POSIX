#include <pthread.h>
#include <iostream>
#include <vector>

// Мьютекс для синхронизации
pthread_mutex_t mutex;

// Общий ресурс
int sharedCounter = 0;

// Функция для потоков
void *incrementCounter(void *arg)
{
    int iterations = *reinterpret_cast<int *>(arg);

    for (int i = 0; i < iterations; ++i)
    {
        pthread_mutex_lock(&mutex); // Блокируем доступ к ресурсу
        ++sharedCounter;
        pthread_mutex_unlock(&mutex); // Разблокируем
    }

    return nullptr;
}

int main()
{
    const int numThreads = 4;
    const int incrementsPerThread = 10000;

    // Инициализация мьютекса
    pthread_mutex_init(&mutex, nullptr);

    // Создаем потоки
    std::vector<pthread_t> threads(numThreads);
    for (int i = 0; i < numThreads; ++i)
    {
        if (pthread_create(&threads[i], nullptr, incrementCounter, (void *)&incrementsPerThread) != 0)
        {
            std::cerr << "Error creating thread " << i << std::endl;
            return 1;
        }
    }

    // Ожидаем завершения потоков
    for (int i = 0; i < numThreads; ++i)
    {
        pthread_join(threads[i], nullptr);
    }

    // Уничтожаем мьютекс
    pthread_mutex_destroy(&mutex);

    std::cout << "Final counter value: " << sharedCounter << std::endl;

    return 0;
}