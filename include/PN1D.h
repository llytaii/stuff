#pragma once

#include <cmath>
#include <vector>
#include <tuple>

#include "RNG.h"

class PN1D // 1D Perlin Noise f�r Signale [0,1]
{
public:
	PN1D(int _octave_count);
	std::vector<float> PN(std::vector<float> _ts);
	float PN(float _t, float _p = 0.5); // PN(t) mit Persistenz p
	float O(float _t, float _rank);
	float S(float _t); // S(t) S-Kurven-Funktion zur Interpolation der Tupel (tj, sj)
private:
	// 1: Oktave, 2: Tupel der Oktave, 3: Tupel
	std::vector<std::vector<std::pair<float, float>>> m_s_t_tuples;
	int m_octave_count;
};

std::vector<float> PN1D::PN(std::vector<float> _ts)
{
	std::vector<float> out;
	for (auto& f : _ts)
		out.push_back(PN(f));
	return out;
}

PN1D::PN1D(int _octave_count) : m_octave_count{ _octave_count }
{
	for (int i{ 0 }; i < _octave_count; ++i)
	{
		int n = pow(2, i) + 1;
		std::vector<std::pair<float, float>> tmp;
		for (int j{ 0 }; j < n; ++j)
		{
			float s = RNG::uniform_value_float(0.0f, 1.0f);
			float t = (j) * (1.0f / (n - 1));
			tmp.push_back(std::pair<float,float>(s, t));
		}
		m_s_t_tuples.push_back(tmp);
	}
}

float PN1D::PN(float _t, float _p)
{
	float sum{};
	for (int i{ 0 }; i < m_octave_count; ++i)
	{
		sum += O(_t, i) * powf(_p, i + 1);
	}
	return sum;
}

float PN1D::O(float _t, float _rank)
{
	if (_t < 0 || _t > 1)
		return -1;

	int index;
	for (int i{ 0 }; i < m_s_t_tuples[_rank].size(); ++i)
	{
		if (_t >= m_s_t_tuples[_rank][i].second && _t <= m_s_t_tuples[_rank][i + 1].second)
		{
			index = i;
			break;
		}
	}

	auto& p0 = m_s_t_tuples[_rank][index];
	auto& p1 = m_s_t_tuples[_rank][index + 1];

	return p0.first + (p1.first - p0.first) * S((_t - p0.second) / (p1.second - p0.second));
}

float PN1D::S(float _t)
{
	return powf(_t, 3) * (10 + _t * (-15 + 6 * _t));
}
