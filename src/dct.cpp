#include <array>
#include <chrono>
#include <iostream>
#include <cmath>

// CONSTANTS
static constexpr double PI{M_PI};

static constexpr std::array<double, 64> cos_part{
    1, 1, 1, 1, 1, 1, 1, 1,
    0.980785, 0.83147, 0.55557, 0.19509, -0.19509, -0.55557, -0.83147, -0.980785,
    0.92388, 0.382683, -0.382683, -0.92388, -0.92388, -0.382683, 0.382683, 0.92388,
    0.83147, -0.19509, -0.980785, -0.55557, 0.55557, 0.980785, 0.19509, -0.83147,
    0.707107, -0.707107, -0.707107, 0.707107, 0.707107, -0.707107, -0.707107, 0.707107,
    0.55557, -0.980785, 0.19509, 0.83147, -0.83147, -0.19509, 0.980785, -0.55557,
    0.382683, -0.92388, 0.92388, -0.382683, -0.382683, 0.92388, -0.92388, 0.382683,
    0.19509, -0.55557, 0.83147, -0.980785, 0.980785, -0.83147, 0.55557, -0.19509};

// DCT
std::array<double, 8> dct_8px(const std::array<double, 8> &_signal)
{
    std::array<double, 8> F;
    double scale;

    for (size_t u = 0; u < 8; ++u)
    {
        scale = (u == 0) ? (std::sqrt(2.0) / 4.0) : 0.5;
        double sum{0.0};

        for (size_t i = 0; i < 8; ++i)
            sum += std::cos(((2 * i + 1) * u * PI) / 16.0) * _signal[i];

        F[u] = scale * sum;
    }
    return F;
}

std::array<double, 8> dct_8px_fast(const std::array<double, 8> &_signal)
{
    std::array<double, 8> F;
    double scale;

    for (size_t u = 0; u < 8; ++u)
    {
        scale = (u == 0) ? (std::sqrt(2.0) / 4.0) : 0.5;
        double sum{0.0};

        for (size_t i = 0; i < 8; ++i)
            sum += cos_part[u * 8 + i] * _signal[i];

        F[u] = scale * sum;
    }
    return F;
}

std::array<double, 8> idct_8px(std::array<double, 8> &_F)
{
    std::array<double, 8> signal;
    double scale;
    for (size_t i = 0; i < 8; ++i)
    {
        double sum{0.0};
        for (size_t u = 0; u < 8; ++u)
        {
            scale = (u == 0) ? (std::sqrt(2.0) / 4.0) : 0.5;
            sum += scale * cos_part[u * 8 + i] * _F[u];
        }
        signal[i] = sum;
    }
    return signal;
}

std::array<double, 8> idct_8px_int(std::array<int, 8> &_F)
{
    std::array<double, 8> signal;
    double scale;
    for (size_t i = 0; i < 8; ++i)
    {
        double sum{0.0};
        for (size_t u = 0; u < 8; ++u)
        {
            scale = (u == 0) ? (std::sqrt(2.0) / 4.0) : 0.5;
            sum += scale * std::cos(((2 * i + 1) * u * PI) / 16.0) * _F[u];
        }
        signal[i] = sum;
    }
    return signal;
}

int main()
{
    // constexpr calculations for cos
    std::cout << "precalculated cos_part:\n";

    for (int u = 0; u < 8; ++u)
    {
        for (int i = 0; i < 8; ++i)
            std::cout << cos_part[u * 8 + i] << ", ";

        std::cout << std::endl;
    }

    // dct & optimized dct

    std::array<double, 8> signal{225.0, 128.0, 32.0, 79.0, 217.0, 198.0, 145.0, 136.0};

    auto start = std::chrono::high_resolution_clock::now();

    // calculate dct
    auto dct = dct_8px(signal);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    // print dct result
    std::cout << "\ndct (took " << duration.count() << " ms):\n";
    for (auto d : dct)
        std::cout << d << ", ";

    std::cout << std::endl;

    //calculate optimized dct
    start = std::chrono::high_resolution_clock::now();
    auto dct_fast = dct_8px_fast(signal);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;

    // print optimized dct result
    std::cout << "\ndct_fast (took " << duration.count() << " ms):\n";
    for (auto d : dct_fast)
        std::cout << d << ", ";

    std::cout << std::endl;

    // print idct result
    std::cout << "\nidct result:\n";
    for (auto d : idct_8px(dct))
        std::cout << d << ", ";

    std::cout << std::endl;

    // print idct result
    std::array<int, 8> iarr;
    for (int i = 0; i < 8; ++i)
        iarr[i] = dct[i];

    std::cout << "\nidct result (int):\n";
    for (auto d : idct_8px_int(iarr))
        std::cout << d << ", ";

    std::cout << std::endl;
}