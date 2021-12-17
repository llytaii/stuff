#include <array>
#include <chrono>
#include <cmath>
#include <iostream>

uint64_t fib_rec(int _n);
uint64_t fib_itr(int _n);
uint64_t fib_itr_f(int _n);
uint64_t fib_f(int _n);

int main()
{
    for(int n = 0; n < 100; ++n)
    {
        uint64_t tmp;
        auto start = std::chrono::high_resolution_clock::now();
        //tmp = fib_rec(n);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        //std::cout << "fib_rec(" << n << "): " << tmp << " took: " << duration.count() << " ms" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        tmp = fib_itr_f(n);
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        std::cout << "fib_itr(" << n << "): " << tmp << " took: " << duration.count() << " ms" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        tmp = fib_f(n);
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        std::cout << "fib_f(" << n << "): " << tmp << " took: " << duration.count() << " ms" << std::endl;
    }
}

uint64_t fib_rec(int _n)
{
    if(_n > 1) return fib_rec(_n - 1) + fib_rec(_n - 2);
    else return (_n == 1) ? 1 : 0;
}

uint64_t fib_itr(int _n)
{
    if(_n < 2)
        return (_n == 1) ? 1 : 0;

    int f0 = 0;
    int f1 = 1;
    int fn = 0;

    for(int i = 1; i < _n; ++i)
    {
        fn = f1 + f0;
        f0 = f1;
        f1 = fn;
    }
    return fn;
}

inline uint64_t fib_itr_f(int _n) // n = 0/1 not supported
{
    int f0 = 0;
    int f1 = 1;
    int fn = 0;

    for(int i = 1; i < _n; ++i)
    {
        fn = f1 + f0;
        f0 = f1;
        f1 = fn;
    }
    return fn;
}

inline uint64_t fib_f(int _n) // accurate until n = 46, faster than itr from n = 40.. pretty useless. 
{
    float s5 = sqrtf(5);
    return (1 / s5) * ( powf((1 + s5) / 2, _n) - powf((1 - s5) / 2, _n) );
}