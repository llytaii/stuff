#pragma once

#include <random>


class RNG
{
public:
	static float uniform_value_float(float _from, float _to)
	{
		std::uniform_real_distribution<float> dist{ _from, _to };
		return dist(m_rng);
	}
	static int uniform_value_int(int _from, int _to)
	{
		std::uniform_int_distribution<int> dist{ _from, _to };
		return dist(m_rng);
	}

	static float normal_value_float(float _mean, float _stddev = 1.0f)
	{
		std::normal_distribution<float> dist{ _mean, _stddev };
		return dist(m_rng);
	}
	static int normal_value_int(float _mean, float _stddev)
	{
		std::normal_distribution<float> dist{ _mean, _stddev };
		return std::round(dist(m_rng));
	}

	static std::random_device m_rd;
	static std::mt19937 m_rng;
};

inline std::random_device RNG::m_rd;
inline std::mt19937 RNG::m_rng{ RNG::m_rd() };
