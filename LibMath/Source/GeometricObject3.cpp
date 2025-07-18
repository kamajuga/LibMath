#include "LibMath/GeometricObject3.h"
#include "LibMath/Matrix4Vector4Operation.h"

#pragma region Point 3D

LibMath::Geometry3D::Point::Point(const float x, const float y, const float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

LibMath::Geometry3D::Point::Point(const Point& other)
{
	m_x = other.m_x;
	m_y = other.m_y;
	m_z = other.m_z;
}

LibMath::Geometry3D::Point::Point(LibMath::Vector3 const& vec)
{
	m_x = vec.m_x;
	m_y = vec.m_y;
	m_z = vec.m_z;
}

LibMath::Geometry3D::Point& LibMath::Geometry3D::Point::operator=(const Point& other)
{
	m_x = other.m_x;
	m_y = other.m_y;
	m_z = other.m_z;

	return *this;
}

LibMath::Vector3 LibMath::Geometry3D::Point::toVector3(void) const
{
	return  LibMath::Vector3(m_x, m_y, m_z);
}

void LibMath::Geometry3D::Point::update(LibMath::Matrix4& transMat)
{
	LibMath::Vector4 vecPoint(toVector3());

	LibMath::Vector4 transformedPoint = transMat * vecPoint;

	m_x = transformedPoint.m_x;
	m_y = transformedPoint.m_y;
	m_z = transformedPoint.m_z;
}

float LibMath::Geometry3D::Point::getDistanceSquared(const Point& other) const
{
	float dx = m_x - other.m_x;
	float dy = m_y - other.m_y;
	float dz = m_z - other.m_z;

	return dx * dx + dy * dy + dz * dz;
}

float LibMath::Geometry3D::Point::getDistance(const Point& other) const
{
	return std::sqrt(getDistanceSquared(other));
}

LibMath::Vector3 LibMath::Geometry3D::Point::operator-(const Point& point) const
{
	return LibMath::Vector3(m_x - point.m_x, m_y - point.m_y, m_z - point.m_z);
}

#pragma endregion All functions Point 3D 

#pragma region Line 3D
LibMath::Geometry3D::Line::Line(const Point& point, const Vector3& dir)
{
	m_origin = point;
	m_direction = dir;
	m_direction.normalize();

	
}

LibMath::Geometry3D::Line::Line(const Point& pointStart, const Point& pointEnd)
{
	m_origin = pointStart;

	LibMath::Vector3 lineVec(pointEnd - pointStart);

	m_length = lineVec.magnitude();

	m_direction = lineVec;
	m_direction.normalize();

	
}

LibMath::Geometry3D::Line::Line(const Point& point, const Vector3& dir, const float& scalair)
{
	m_origin = point;
	m_direction = dir;
	m_direction.normalize();
	m_length = scalair;
}

LibMath::Geometry3D::Line::Line(const Line& other)
{
	m_origin = other.m_origin;
	m_direction = other.m_direction;
	m_length = other.m_length;
}

LibMath::Geometry3D::Line& LibMath::Geometry3D::Line::operator=(const Line& other)
{
	m_origin = other.m_origin;
	m_direction = other.m_direction;

	return *this;
}

LibMath::Geometry3D::Line LibMath::Geometry3D::Line::operator*(const float& scalair)
{
	Line line = *this;

	line.m_length *= scalair;
	return line;
}

void LibMath::Geometry3D::Line::update(LibMath::Matrix4& transMat)
{
	LibMath::Vector4 vecPoint(m_origin.toVector3());

	LibMath::Vector4 transformedPoint = transMat * vecPoint;

	m_origin.m_x = transformedPoint.m_x;
	m_origin.m_y = transformedPoint.m_y;
	m_origin.m_z = transformedPoint.m_z;
}

#pragma endregion All functions Line 3D

#pragma region Plan 3D
LibMath::Geometry3D::Plan::Plan(const Vector3& normal, const float& distance)
{
	m_normal = normal;
	m_distance = distance;
	m_normal.normalize();
	
}

LibMath::Geometry3D::Plan::Plan(const Plan& other)
{
	m_normal = other.m_normal;
	m_distance = other.m_distance;

}

LibMath::Geometry3D::Plan& LibMath::Geometry3D::Plan::operator=(const Plan& other)
{
	m_normal = other.m_normal;
	m_distance = other.m_distance;

	return *this;
}
#pragma endregion All functions Plan 3D

#pragma region AABB 3D

LibMath::Geometry3D::AABB::AABB(const Point& center, const float& width, const float& height, const float& depth)
{
	m_center = center;
	m_width = width;
	m_height = height;
	m_depth = depth;
}

LibMath::Geometry3D::AABB::AABB(const AABB& other)
{
	m_center = other.m_center;
	m_width = other.m_width;
	m_height = other.m_height;
	m_depth = other.m_depth;
}

LibMath::Geometry3D::AABB& LibMath::Geometry3D::AABB::operator=(const AABB& other)
{
	m_center = other.m_center;
	m_width = other.m_width;
	m_height = other.m_height;
	m_depth = other.m_depth;

	return *this;
}

void LibMath::Geometry3D::AABB::update(LibMath::Matrix4& transMat)
{
	LibMath::Vector4 vecPoint(m_center.toVector3());

	LibMath::Vector4 transformedPoint = transMat * vecPoint;

	m_center.m_x = transformedPoint.m_x;
	m_center.m_y = transformedPoint.m_y;
	m_center.m_z = transformedPoint.m_z;
}

float LibMath::Geometry3D::AABB::extentX(void) const
{
	return m_width / 2.f;
}

float LibMath::Geometry3D::AABB::extentY(void) const
{
	return m_height / 2.f;
}

float LibMath::Geometry3D::AABB::extentZ(void) const
{
	return m_depth / 2.f;
}

#pragma endregion All functions AABB

#pragma region OBB 3D

LibMath::Geometry3D::OBB::OBB(const Point& center, const float& width, const float& height, const float& depth, const Radian& rotation)
{
	m_center = center;
	m_width = width;
	m_height = height;
	m_depth = depth;
	m_rotation = rotation;

}

LibMath::Geometry3D::OBB::OBB(const OBB& other)
{
	m_center = other.m_center;
	m_width = other.m_width;
	m_height = other.m_height;
	m_depth = other.m_depth;
	m_rotation = other.m_rotation;
}

void LibMath::Geometry3D::OBB::update(LibMath::Matrix4& transMat)
{
	LibMath::Vector4 vecPoint(m_center.toVector3());

	LibMath::Vector4 transformedPoint = transMat * vecPoint;

	m_center.m_x = transformedPoint.m_x;
	m_center.m_y = transformedPoint.m_y;
	m_center.m_z = transformedPoint.m_z;
}

LibMath::Geometry3D::OBB& LibMath::Geometry3D::OBB::operator=(const OBB& other)
{
	m_center = other.m_center;
	m_width = other.m_width;
	m_height = other.m_height;
	m_depth = other.m_depth;
	m_rotation = other.m_rotation;

	return *this;
}


#pragma endregion All function OBB

#pragma region Sphere 3D

LibMath::Geometry3D::Sphere::Sphere(const Point& center, const float& radius)
{
	m_center = center;
	m_radius = radius;
}

LibMath::Geometry3D::Sphere::Sphere(const Sphere& other)
{
	m_center = other.m_center;
	m_radius = other.m_radius;
}

void LibMath::Geometry3D::Sphere::update(LibMath::Matrix4& transMat)
{
	LibMath::Vector4 vecPoint(m_center.toVector3());

	LibMath::Vector4 transformedPoint = transMat * vecPoint;

	m_center.m_x = transformedPoint.m_x;
	m_center.m_y = transformedPoint.m_y;
	m_center.m_z = transformedPoint.m_z;
}

LibMath::Geometry3D::Sphere& LibMath::Geometry3D::Sphere::operator=(const Sphere& other)
{
	m_center = other.m_center;
	m_radius = other.m_radius;

	return *this;
}

#pragma endregion All function Sphere

#pragma region Capsule3D
LibMath::Geometry3D::Capsule::Capsule(const Point& pointA, const Point& pointB, const float& radius)
{
	m_pointA = pointA;
	m_pointB = pointB;
	m_radius = radius;
}

LibMath::Geometry3D::Capsule::Capsule(const Capsule& other)
{
	m_pointA = other.m_pointA;
	m_pointB = other.m_pointB;
	m_radius = other.m_radius;
}

void LibMath::Geometry3D::Capsule::update(LibMath::Matrix4& transMat)
{
	LibMath::Vector4 vecPointA(m_pointA.toVector3());
	LibMath::Vector4 vecPointB(m_pointB.toVector3());

	LibMath::Vector4 transformedPointA = transMat * vecPointA;
	LibMath::Vector4 transformedPointB = transMat * vecPointB;

	m_pointA.m_x = transformedPointA.m_x;
	m_pointA.m_y = transformedPointA.m_y;
	m_pointA.m_z = transformedPointA.m_z;

	m_pointB.m_x = transformedPointB.m_x;
	m_pointB.m_y = transformedPointB.m_y;
	m_pointB.m_z = transformedPointB.m_z;
}

LibMath::Geometry3D::Capsule& LibMath::Geometry3D::Capsule::operator=(const Capsule& other)
{
	m_pointA = other.m_pointA;
	m_pointB = other.m_pointB;
	m_radius = other.m_radius;

	return *this;
}

#pragma endregion

LibMath::Geometry3D::Point LibMath::Geometry3D::getClosestToAABB(const LibMath::Geometry3D::AABB& aabb, const Point& p)
{
	float aabbMinX = aabb.m_center.m_x - aabb.extentX();
	float aabbMaxX = aabb.m_center.m_x + aabb.extentX();
	float aabbMinY = aabb.m_center.m_y - aabb.extentY();
	float aabbMaxY = aabb.m_center.m_y + aabb.extentY();
	float aabbMinZ = aabb.m_center.m_z - aabb.extentZ();
	float aabbMaxZ = aabb.m_center.m_z + aabb.extentZ();

	float x = std::max(aabbMinX, std::min(p.m_x, aabbMaxX));
	float y = std::max(aabbMinY, std::min(p.m_y, aabbMaxY));
	float z = std::max(aabbMinZ, std::min(p.m_z, aabbMaxZ));
	return Geometry3D::Point(x, y, z);
}

LibMath::Geometry3D::Point LibMath::Geometry3D::getClosestToSegment(const Point& a, const Point& b, const Point& p)
{
	LibMath::Vector3 ab = b.toVector3() - a.toVector3();
	float abLengthSq = ab.dot(ab);

	if (abLengthSq == 0.0f) {
		return a; // Segment is a point, so 'a' is the closest point
	}

	// Project p onto the line containing ab
	float t = (p.toVector3() - a.toVector3()).dot(ab) / abLengthSq;
	t = std::max(0.0f, std::min(t, 1.0f)); // Clamp t to [0, 1] to stay on the segment

	return Geometry3D::Point(a.m_x + t * ab.m_x,
		a.m_y + t * ab.m_y,
		a.m_z + t * ab.m_z);
}
