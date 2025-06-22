#ifndef GEOMETRIC_OBJECT3_H
#define	GEOMETRIC_OBJECT3_H

#include "LibMath/Vector/Vector3.h"
#include "LibMath/Matrix/Matrix4.h"

namespace LibMath
{
	namespace Geometry3D
	{
		class Vector3;
		class Object3D
		{
		public:
			virtual ~Object3D() = default;

		};

		// Todo: Implement tests for all the geometric objects
		class Point : public Object3D
		{
		public:
									Point() = default;
									Point(const float x, const float y, const float z);
									Point(const Point& other);
									~Point() = default;

			Point&					operator=(const Point& other);

			operator				LibMath::Vector3(void) const;

			const LibMath::Vector3	toVector3(void) const { return  LibMath::Vector3(m_x, m_y, m_z); };

			float					getDistanceSquared(const Point&) const;
			float					getDistance(const Point&) const;

			LibMath::Vector3					operator-(const Point& point);

			float					m_x = 0.0f;
			float					m_y = 0.0f;
			float					m_z = 0.0f;

		private:
			

		};

		class Line : public Object3D
		{
		public:
			Line() = default;
			Line(const Point& point, const LibMath::Vector3& dir);   // Director vector should be a unit vector
			Line(const Point& point, const LibMath::Vector3& dir, const float& scalair);
			Line(const Line& other);
			~Line() = default;

			Line& operator=(const Line& other);
			Line operator*(const float& scalair);


			Point			m_origin;
			LibMath::Vector3			m_direction;
			float			m_length = 0.f;
		private:

		};

		class Plan : public Object3D
		{
		public:
			Plan() = default;
			Plan(const LibMath::Vector3& normal, const float& distance);
			Plan(const Plan& other);
			~Plan() = default;

			Plan& operator=(const Plan& other);



			LibMath::Vector3			m_normal;
			float			m_distance = 0.f;

		private:
			

		};

		class AABB :public Object3D
		{
		public:
			AABB() = default;
			AABB(const Point& center, const float& width, const float& height, const float& depth);
			AABB(const AABB& other);
			~AABB() = default;

			AABB& operator=(const AABB& other);

			Point& center(void) { return m_center; };
			const Point& center(void) const { return m_center; };

			float			extentX(void) const;
			float			extentY(void) const;
			float			extentZ(void) const;

			Point			m_center;
			float			m_width = 0.f; // length on X axis
			float			m_height = 0.f; // length on Y axis
			float			m_depth = 0.f; // length on Z axis
		private:

			
		};

		class OBB : public Object3D
		{
		public:
			OBB() = default;
			OBB(const Point& center, const float& width, const float& height, const float& m_depth, const Radian& rotation);
			OBB(const OBB& other);
			~OBB() = default;

			OBB& operator=(const OBB& other);

			Point			m_center;
			float			m_width = 0.f;
			float			m_height = 0.f;
			float			m_depth = 0.f;
			LibMath::Radian m_rotation;

		private:
			
		};

		class Sphere : public Object3D
		{
		public:
			Sphere() = default;
			Sphere(const Point& center, const float& radius);
			Sphere(const Sphere& other);
			~Sphere() = default;

			Sphere& operator=(const Sphere& other);

			Point			m_center;
			float			m_radius = 0.f;

		private:
			
		};

		class Capsule :public Object3D
		{
		public:
			Capsule() = default;
			Capsule(const Point& pointA, const Point& pointB, const float& radius);
			Capsule(const Capsule& other);
			~Capsule() = default;

			Capsule& operator=(const Capsule& other);

			Point			m_pointA;
			Point			m_pointB;
			float			m_radius = 0.f;

		private:

		};

		Point			getClosestToAABB(const LibMath::Geometry3D::AABB&, const Point&);
		Point			getClosestToSegment(const Point&, const Point&, const Point&);

	}

}

#endif // !GEOMETRIC_OBJECT3_H
