#define _USE_MATH_DEFINES
#include <cmath>
#include "LibMath/Angle.h"
#include "LibMath/Arithmetic.h"
#include <iostream>

#pragma region Degreee 
LibMath::Degree::Degree()
{
	m_value = 0.0f;
}

LibMath::Degree::Degree(float value)
{
	m_value = value;
}

LibMath::Degree::Degree(Degree const& other)
{
	m_value = other.m_value;
}

LibMath::Degree::operator LibMath::Radian() const
{
	return Radian(m_value * static_cast<float>(M_PI) / 180.0f);
}

LibMath::Degree& LibMath::Degree::operator+=(Degree other)
{
	m_value += other.m_value;

	return *this;
}

LibMath::Degree& LibMath::Degree::operator-=(Degree other)
{
	m_value -= other.m_value;

	return *this;
}

LibMath::Degree& LibMath::Degree::operator*=(float value)
{
	m_value *= value;

	return *this;
}

LibMath::Degree& LibMath::Degree::operator/=(float value)
{
	m_value /= value;

	return *this;
}

void LibMath::Degree::wrap(bool _wrap)
{
	if (_wrap)
	{
		m_value = LibMath::wrap(m_value, -180.0f, 180.0f);
	}
	else
	{
		m_value = LibMath::wrap(m_value, 0.0f, 360.0f);
	}
}

float LibMath::Degree::degree(bool _deg) const
{

	return _deg ? LibMath::wrap(m_value, -180.0f, 180.0f) : LibMath::wrap(m_value, 0.0f, 360.0f);
}

float LibMath::Degree::radian(bool _rad) const
{
	float temp = m_value;
	temp = (static_cast<float>(M_PI) * temp) / 180.0f;

	return _rad ? LibMath::wrap(temp, -static_cast<float>(M_PI), static_cast<float>(M_PI)) : LibMath::wrap(temp, 0.0f, 2 * static_cast<float>(M_PI));
}

float LibMath::Degree::raw() const
{
	return m_value;
}

bool LibMath::operator==(Degree _deg1, Degree _deg2)
{
	// _deg2 = _deg1 + 360 * rotation_ratio 
	float value1 = _deg1.m_value;
	float value2 = _deg2.m_value;

	if (value1 > value2)
	{
		float temp = value1;
		value1 = value2;
		value2 = temp;
	}

	float rotation_ratio  = (value2 - value1) / 360.f;

	float decimal_part = modf(rotation_ratio , &rotation_ratio );

	return LibMath::almostEqual(decimal_part, 0);
}

bool LibMath::operator==(Degree _deg, float _val)
{
	return _deg.m_value == _val;
}

bool LibMath::operator==(Degree _deg, Radian const& _rad)
{
	float temp_rad = (_deg.m_value * static_cast<float>(M_PI)) / 180.f;

	return LibMath::almostEqual(_rad.raw(), temp_rad);
}

LibMath::Degree LibMath::operator-(Degree _deg)
{
	return Degree(-_deg.m_value);
}

LibMath::Degree LibMath::operator+(Degree _deg1, Degree _deg2)
{
	return Degree(_deg1.m_value + _deg2.m_value);
}

LibMath::Degree LibMath::operator-(Degree _deg1, Degree _deg2)
{
	return Degree(_deg1.m_value - _deg2.m_value);
}

LibMath::Degree LibMath::operator*(Degree _deg, float _val)
{
	return Degree(_deg.m_value * _val);
}

LibMath::Degree LibMath::operator/(Degree _deg, float _val)
{
	if (LibMath::almostEqual(_val, 0))
	{
		throw std::runtime_error("Division by zero");
	}

	return Degree(_deg.m_value / _val);
}

LibMath::Degree LibMath::Literal::operator""_deg(long double _val)
{
	return LibMath::Degree((float)_val);
}

LibMath::Degree LibMath::Literal::operator""_deg(unsigned long long int _val)
{
	return LibMath::Degree((float)_val);
}

#pragma endregion All functions for Degrees

#pragma region Radian
LibMath::Radian::Radian()
{
	m_value = 0.0f;
}

LibMath::Radian::Radian(float _val)
{
	m_value = _val;
}

LibMath::Radian::Radian(Radian const& other)
{
	m_value = other.m_value;
}

LibMath::Radian::operator LibMath::Degree() const
{
	return Degree((m_value * 180.0f) / static_cast<float>(M_PI));
}

LibMath::Radian& LibMath::Radian::operator+=(Radian other)
{
	m_value += other.m_value;

	return *this;
}

LibMath::Radian& LibMath::Radian::operator-=(Radian other)
{
	m_value -= other.m_value;

	return *this;
}

LibMath::Radian& LibMath::Radian::operator*=(float _val)
{
	m_value *= _val;

	return *this;
}

LibMath::Radian& LibMath::Radian::operator/=(float _val)
{
	m_value /= _val;

	return *this;
}

void LibMath::Radian::wrap(bool _wrap)
{
	if (_wrap)
	{
		m_value = LibMath::wrap(m_value, -static_cast<float>(M_PI), static_cast<float>(M_PI));
	}
	else
	{
		m_value = LibMath::wrap(m_value, 0.0f, 2 * static_cast<float>(M_PI));
	}
}

float LibMath::Radian::degree(bool _deg) const
{
	float temp = m_value;

	temp = (180.0f * temp) / static_cast<float>(M_PI);

	return _deg ? LibMath::wrap(temp, -180.0f, 180.0f) : LibMath::wrap(temp, 0.0f, 360.0f);
}

float LibMath::Radian::radian(bool _rad) const
{
	return _rad ? LibMath::wrap(m_value, -static_cast<float>(M_PI), static_cast<float>(M_PI)) : LibMath::wrap(m_value, 0.0f, 2 * static_cast<float>(M_PI));
}

float LibMath::Radian::raw() const
{
	return m_value;
}

bool LibMath::operator==(Radian _rad1, Radian _rad2)
{
	float value1 = _rad1.m_value;
	float value2 = _rad2.m_value;

	if (value1 > value2)
	{
		float temp = value1;
		value1 = value2;
		value2 = temp;
	}

	float rotation_ratio  = (value2 - value1) / static_cast<float>(2 * M_PI);

	float decimal_part = modf(rotation_ratio , &rotation_ratio );

	return LibMath::almostEqual(decimal_part, 0);
}

bool LibMath::operator==(Radian _rad, float _val)
{
	return _rad.m_value == _val;
}

bool LibMath::operator==(Radian _rad, Degree const& _deg)
{
	float temp_deg = (_rad.m_value * 180.0f) / static_cast<float>(M_PI);

	return LibMath::almostEqual(_deg.raw(), temp_deg);
}

LibMath::Radian LibMath::operator-(Radian _rad)
{
	return Radian(-_rad.m_value);
}

LibMath::Radian LibMath::operator+(Radian _rad1, Radian _rad2)
{
	return Radian(_rad1.m_value + _rad2.m_value);
}

LibMath::Radian LibMath::operator-(Radian _rad1, Radian _rad2)
{
	return Radian(_rad1.m_value - _rad2.m_value);
}

LibMath::Radian LibMath::operator*(Radian _rad1, float _val)
{
	return Radian(_rad1.m_value * _val);
}

LibMath::Radian LibMath::operator/(Radian _rad1, float _val)
{
	if (LibMath::almostEqual(_val, 0))
	{
		throw std::runtime_error("Division by zero");
	}
	return Radian(_rad1.m_value / _val);
}

LibMath::Radian LibMath::Literal::operator""_rad(long double _val)
{
	return LibMath::Radian(static_cast<float>( _val));
}

LibMath::Radian LibMath::Literal::operator""_rad(unsigned long long int _val)
{
	return LibMath::Radian(static_cast<float>(_val));
}

#pragma endregion All function for Radian