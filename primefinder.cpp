#include "primefinder.h"
#include <cmath>

PrimeFinder::PrimeFinder(int start, int end)
    : start_(start), end_(end), isRunning_(true)
{

}

//Function to check if a number is prime
bool isPrime(int n)
{
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    int maxDivisor = static_cast<int>(std::sqrt(n)) + 1;
    for (int d = 3; d <= maxDivisor; d += 2)
    {
        if (n % d == 0) return false;
    }
    return true;
}

void PrimeFinder::run()
{
    for (int num = start_; num < end_; ++num)
    {
        if (!isRunning_) break;
        if (isPrime(num))
        {
            emit primeFound(num);
        }
    }
    emit finished();
}

void PrimeFinder::stop()
{
    QMutexLocker locker(&mutex_);
    isRunning_ = false;
}
