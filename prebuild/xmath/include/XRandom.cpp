﻿#include "XRandom.h"
#include "XConstant.h"
#include <cmath>

using namespace xmath;
using namespace xmath::random;

constexpr uint64_t MaxIntFromDouble = 9007199254740992;//2^53
constexpr double NormalFactor = 1.71552776992141359296;//4*e^(-0.5)/sqrt(2)
constexpr double log4 = 1.3862943611198906188;
constexpr double SG_MAGICCONST = 1.0 + 1.504077396776274073373;
constexpr double _e = 2.71828182845904523536028;

int64_t Random::range(uint64_t start)
{
	return below(start);
}

int64_t Random::range(int64_t start, int64_t stop, int64_t step)
{
	if (start == stop)return start;//empty range
	const auto width = stop - start;
	if (step == 1 && width > 0)
		return start + below(width);
	if (step == 1 || step == 0)return start;//empty range
	const int64_t n = step > 0 ? double(width + step - 1) / step : double(width + step + 1) / step;
	if (n <= 0)return start;//empty range
	return start + double(step) * below(n);
}

uint64_t Random::below(uint64_t n)
{
	if (n > MaxIntFromDouble || n == 0)
		return _rand()*n;
	const auto rem = MaxIntFromDouble % n;
	const auto limit = double(MaxIntFromDouble - rem) / MaxIntFromDouble;
	auto r = _rand();
	while (r >= limit)
		r = _rand();
	return uint64_t(r*MaxIntFromDouble) % n;
}

double Random::uniform(double a, double b)
{
	return a + (b - a) * _rand();
}

double Random::triangular()
{
	return triangular(0.0, 1.0);
}

double Random::triangular(double low, double high)
{
	const auto u = _rand();
	if (u > 0.5)
		return high + (low - high)*std::sqrt((1 - u)*0.5);
	return low + (high - low)*sqrt(u*0.5);
}

double Random::triangular(double low, double high, double mode)
{
	const auto div = high - low;
	if (div == 0.0)
		return low;
	const auto c = (mode - low) / div;
	const auto u = _rand();
	if (u > c)
		return high + (low - high)*std::sqrt((1 - u)*(1 - c));
	return low + (high - low)*sqrt(u*c);
}

double Random::normal(double mu, double sigma)
{
	double z;
	while (true)
	{
		const double u1 = _rand();
		const double u2 = _rand();
		z = NormalFactor * (u1 - 0.5) / u2;
		if (z * z / 4 <= -std::log(u2))
			break;
	}
	return mu + z * sigma;
}

double Random::log_norml(double mu, double sigma)
{
	return std::exp(normal(mu, sigma));
}

double Random::expo(double lambda)
{
	if (lambda == 0.0)return 0.0;
	return -std::log(1 - _rand()) / lambda;
}

double Random::vonMises(double mu, double kappa)
{
	if (kappa <= 1e-6)
		return pix2 * _rand();
	const auto s = 0.5 / kappa;
	const auto r = s + std::sqrt(1 + s * s);
	double z;
	while (true)
	{
		const double u1 = _rand();
		z = std::cos(pi*u1);
		const double d = z / (r + z);
		const double u2 = _rand();
		if (u2 < 1 - d * d || u2 <= (1 - d)*std::exp(d))
			break;
	}
	const auto q = 1.0 / r;
	const auto f = (q + z) / (1 + q * z);
	if (_rand() > 0.5)
		return (mu + std::acos(f))*pix2;
	else
		return (mu - std::acos(f))*pix2;
}

double Random::gamma(double alpha, double beta)
{
	if (alpha <= 0.0 || beta <= 0.0)return 0.0;
	if (alpha > 1.0)
	{
		const auto ainv = std::sqrt(2 * alpha - 1);
		const auto bbb = alpha - log4;
		const auto ccc = alpha + ainv;
		double u1, u2, v, x, z, r;
		while (true)
		{
			u1 = _rand();
			while (u1 < 1e-7 || u1>1 - 1e-7)
				u1 = _rand();
			u2 = 1 - _rand();
			v = std::log(u1 / (1.0 - u1)) / ainv;
			x = alpha * std::exp(v);
			z = u1 * u1*u2;
			r = bbb + ccc * v - x;
			if (r + SG_MAGICCONST - 4.5*z >= 0.0 || r >= std::log(z))
				return x * beta;
		}
	}
	else if (alpha == 1.0)
	{
		auto u = _rand();
		while (u <= 1e-7)
			u = _rand();
		return -std::log(u)*beta;
	}
	else
	{
		double x;
		while (true)
		{
			const auto u = _rand();
			const auto b = (_e + alpha) / _e;
			const auto p = b * u;
			if (p <= 1.0)
				x = std::pow(p, 1.0 / alpha);
			else
				x = -std::log((b - p) / alpha);
			const auto u1 = _rand();
			if (p > 1.0)
			{
				if (u1 <= std::pow(x, alpha - 1.0))
					break;
			}
			else if (u1 <= std::exp(-x))
				break;
		}
		return x * beta;
	}
}

double Random::gauss(double mu, double sigma)
{
	double z;
	if (!has_gauss_next)
	{
		const auto x2pi = pix2 * _rand();
		const auto g2rad = std::sqrt(-2.0*std::log(1.0 - _rand()));
		z = std::cos(x2pi)*g2rad;
		_gauss_next = std::sin(x2pi)*g2rad;
		has_gauss_next = true;
	}
	else
	{
		z = _gauss_next;
		has_gauss_next = false;
	}
	return mu + z * sigma;
}

double Random::beta(double alpha, double beta)
{
	const auto y = gamma(alpha, 1.0);
	if (y == 0.0)
		return 0.0;
	else
		return y / (y + gamma(beta, 1.0));
}

double Random::pareto(double alpha)
{
	return 1.0 / std::pow(1.0 - _rand(), 1.0 / alpha);
}

double Random::weibull(double alpha, double beta)
{
	return alpha * std::pow(-std::log(_rand()), 1.0 / beta);
}
