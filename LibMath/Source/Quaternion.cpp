#include "LibMath/Quaternion.h"
#include "LibMath/Angle/Radian.h"
#include "LibMath/Trigonometry.h"
#include "LibMath/Arithmetic.h"
#include "LibMath/Vector/Vector3.h"
#include "LibMath/Matrix/Matrix3.h"

LibMath::Quaternion::Quaternion(float x, float y, float z, float w)
{
	m_w = w;

	m_x = x;
	m_y = y;
	m_z = z;
}

LibMath::Quaternion::Quaternion(Quaternion const& other)
{
	if (other == *this)
		return;

	m_x = other.m_x;
	m_y = other.m_y;
	m_z = other.m_z;
	m_w = other.m_w;
}

LibMath::Quaternion::Quaternion(Radian rad, Vector3 vec)
{
	Vector3 normalizedVec = vec;
	normalizedVec.normalize();

	Radian halfRad = Radian(rad.raw() / 2);

	m_w = normalizedVec.magnitude() * cos(halfRad);

	Vector3 ImVetor = vec * sin(halfRad);

	m_x = ImVetor.m_x;
	m_y = ImVetor.m_y;
	m_z = ImVetor.m_z;
}

LibMath::Quaternion::Quaternion(Vector3 vec)
{
	m_x = vec.m_x;
	m_y = vec.m_y;
	m_z = vec.m_z;
	m_w = 0.f;
}

LibMath::Quaternion::Quaternion(Radian rad_x, Radian rad_y, Radian rad_z)
{
	// XYZ rotation
	Quaternion pitch = Quaternion(rad_x, Vector3::right());
	Quaternion roll = Quaternion(rad_y, Vector3::up());
	Quaternion yaw = Quaternion(rad_z, Vector3::front());

	Quaternion result = yaw * roll * pitch;

	m_x = result.m_x;
	m_y = result.m_y;
	m_z = result.m_z;
	m_w = result.m_w;
}

float LibMath::Quaternion::magnitude() const
{
	return LibMath::squareRoot(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
}

float LibMath::Quaternion::magnitudeSquare() const
{
	return m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w;
}

void LibMath::Quaternion::normalize() 
{
	float mag = magnitude();

	if (LibMath::almostEqual(0.f, mag))
	{
		throw(std::runtime_error("Can't normalize zero vector"));
	}

	m_x /= mag;
	m_y /= mag;
	m_z /= mag;
	m_w /= mag;
}

LibMath::Quaternion LibMath::Quaternion::conjugate(void) const
{
	return Quaternion(-m_x, -m_y, -m_z, m_w);
}

LibMath::Quaternion LibMath::Quaternion::inverse(void) const
{
	Quaternion conj = conjugate();
	float magSquare = magnitudeSquare();

	if (LibMath::almostEqual(magSquare, 1.f))
	{
		return conj;
	}

	return Quaternion(conj.m_x / magSquare, conj.m_y / magSquare, conj.m_z / magSquare, conj.m_w / magSquare);
}

LibMath::Radian LibMath::Quaternion::angleBetween(Quaternion const& other) const
{
	float dot = m_x * other.m_x + m_y * other.m_y + m_z * other.m_z + m_w * other.m_w;

	float magSquare1 = magnitudeSquare();
	float magSquare2 = other.magnitudeSquare();

	float cos = dot / LibMath::squareRoot(magSquare1 * magSquare2);

	return LibMath::acos(cos) * 2;
}

LibMath::Vector3 LibMath::Quaternion::rotate(Vector3 const& vec) const
{
	Quaternion point = Quaternion(vec);
	Quaternion result = *this * point * inverse();

	return Vector3(result.m_x, result.m_y, result.m_z);
}

LibMath::Matrix3 LibMath::Quaternion::toMatrix(void)
{
	float m00 = 1 - 2 * (m_y * m_y + m_z * m_z);
	float m01 = 2 * (m_w * m_z + m_x * m_y);
	float m02 = 2 * (m_x * m_z - m_w * m_y);

	float m10 = 2 * (m_x * m_y - m_w * m_z);
	float m11 = 1 - 2 * (m_x * m_x + m_z * m_z);
	float m12 = 2 * (m_w * m_x + m_y * m_z);

	float m20 = 2 * (m_w * m_y + m_x * m_z);
	float m21 = 2 * (m_y * m_z - m_w * m_x);
	float m22 = 1 - 2 * (m_x * m_x + m_y * m_y);

	return LibMath::Matrix3(
		m00, m01, m02,
		m10, m11, m12,
		m20, m21, m22
		);
}

bool LibMath::Quaternion::isUnit() const
{
	return LibMath::almostEqual(magnitude(), 1.f);
}

LibMath::Radian LibMath::Quaternion::angleBetween(Quaternion const& qStart, Quaternion const& qEnd)
{
	float dot = qStart.m_x * qEnd.m_x + qStart.m_y * qEnd.m_y + qStart.m_z * qEnd.m_z + qStart.m_w * qEnd.m_w;

	float magSquare1 = qStart.magnitudeSquare();
	float magSquare2 = qEnd.magnitudeSquare();

	float cos = dot / LibMath::squareRoot(magSquare1 * magSquare2);

	return LibMath::acos(cos);
}

LibMath::Quaternion LibMath::Quaternion::identity()
{
	return Quaternion(0, 0, 0, 1);
}

LibMath::Quaternion LibMath::Quaternion::slerp(Quaternion const& qStart, Quaternion const& qEnd, float t)
{
	Quaternion unitQStart = qStart;
	unitQStart.normalize();

	Quaternion unitQEnd = qEnd;
	unitQEnd.normalize();

	float cosTheta = qStart.m_x * qEnd.m_x + qStart.m_y * qEnd.m_y + qStart.m_z * qEnd.m_z + qStart.m_w * qEnd.m_w;

	if (cosTheta < 0)
	{
		// Angle is greater then 90deg
		unitQEnd = unitQEnd.conjugate();
		unitQEnd.m_w = -unitQEnd.m_w;
		cosTheta = -cosTheta;
	}

	if (cosTheta > 0.9995f) {
		return nlerp(qStart, qEnd, t);
	}
	Radian angleBetween = LibMath::acos(cosTheta);

	float sinTheta = sin(angleBetween);

	// Handle very small angles (fall back to linear interpolation)
	// Avoid division by zero

	float SsinTheta = sin(angleBetween * (1 - t));
	float EsinTheta = sin(angleBetween * t);

	Quaternion StartQuat = unitQStart * (SsinTheta / sinTheta);
	Quaternion EndQuat = unitQEnd * (EsinTheta / sinTheta);

	return StartQuat + EndQuat;
}

LibMath::Quaternion LibMath::Quaternion::nlerp(Quaternion const& qStart, Quaternion const& qEnd, float t)
{
	Quaternion unitQStart = qStart;
	unitQStart.normalize();

	Quaternion unitQEnd = qEnd;
	unitQEnd.normalize();

	Quaternion StartQuat = unitQStart * (1 - t);
	Quaternion EndQuat = unitQEnd * t;

	Quaternion result = (StartQuat + EndQuat);
	result.normalize();

	return result;
}

float& LibMath::Quaternion::operator[](unsigned int index)
{
	switch (index)
	{
	case 0:
		return m_x;

	case 1:
		return m_y;

	case 2:
		return m_z;

	case 3:
		return m_w;

	default:

		throw(std::out_of_range("Index out of range"));

		break;
	}
}

float LibMath::Quaternion::operator[](unsigned int index) const
{
	switch (index)
	{
	case 0:
		return m_x;

	case 1:
		return m_y;

	case 2:
		return m_z;

	case 3:
		return m_w;

	default:

		throw(std::out_of_range("Index out of range"));

		break;
	}
}

LibMath::Quaternion LibMath::operator*(Quaternion const& q1, Quaternion const& q2)
{
	Vector3 v1 = Vector3(q1.m_x, q1.m_y, q1.m_z);
	Vector3 v2 = Vector3(q2.m_x, q2.m_y, q2.m_z);

	float dot = v1.dot(v2);
	Vector3 cross = v1.cross(v2);

	float RealPart = q1.m_w * q2.m_w - dot;

	Vector3 ImPart = v2 * q1.m_w + v1 * q2.m_w + cross;

	return Quaternion(ImPart.m_x, ImPart.m_y, ImPart.m_z, RealPart);
}

bool LibMath::operator==(Quaternion const& q1, Quaternion const& q2)
{
	return (q1.m_x == q2.m_x) && (q1.m_y == q2.m_y) && (q1.m_z == q2.m_z) && (q1.m_w == q2.m_w );
}

LibMath::Quaternion LibMath::operator+(Quaternion const& q1, Quaternion const& q2)
{
	return Quaternion(q1.m_x + q2.m_x, q1.m_y + q2.m_y, q1.m_z + q2.m_z, q1.m_w + q2.m_w);
}

LibMath::Quaternion LibMath::operator*(Quaternion const& q, float const& scalair)
{

	return Quaternion(q.m_x * scalair, q.m_y * scalair, q.m_z * scalair, q.m_w * scalair);
}
