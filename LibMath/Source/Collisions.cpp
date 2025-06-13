#include "LibMath/Collisions.h"
#include "LibMath/Arithmetic.h"

#pragma region Sphere Collision 3D
bool LibMath::Collisions3D::checkCollision(const Geometry3D::Sphere& sphere1, const Geometry3D::Sphere& sphere2)
{
	// Distance between the center of the two sphere
	float distance = sqrtf(powf(sphere1.center().getX() - sphere2.center().getX(), 2) +
		powf(sphere1.center().getY() - sphere2.center().getY(), 2) +
		powf(sphere1.center().getZ() - sphere2.center().getZ(), 2));

	// Check if the distance is less than the sum of the radius of the two spheres
	if (distance <= (sphere1.radius() + sphere2.radius()))
		return true;

	// No collision
	return false;
}

bool LibMath::Collisions3D::checkCollision(const Geometry3D::Sphere& sphere, const Geometry3D::Point& point)
{
	// Distance between the center of the sphere and the point
	float distance = sqrtf(powf(sphere.center().getX() - point.getX(), 2) +
		powf(sphere.center().getY() - point.getY(), 2) +
		powf(sphere.center().getZ() - point.getZ(), 2));

	// Check if the distance is less than the radius of the sphere
	if (distance <= sphere.radius())
		return true;

	// No collision
	return false;
}

bool LibMath::Collisions3D::checkCollision(const Geometry3D::Sphere& sphere, const Geometry3D::Line& line)
{
	Vector3 lineToSphere = sphere.center().toVector3() - line.getOrigin().toVector3();
	Vector3 lineDirection = line.getDirection();
	lineDirection.normalize();

	Vector3 center = sphere.center().toVector3();

	// Calculate the discriminant

	float d = lineToSphere.dot(lineDirection); 
	
	float c = lineToSphere.dot(lineToSphere) - (sphere.radius() * sphere.radius());

	float discriminant = d * d - c;

	// Check if the discriminant is less than 0
	if (discriminant < 0)
		// No collision
		return false;

	float t1 = d - sqrt(discriminant);  // First intersection point
	float t2 = d + sqrt(discriminant);  // Second intersection point

	// At least one of the intersection points must be >= 0 (positive direction)
	return (t1 >= 0.0f || t2 >= 0.0f);
}

bool LibMath::Collisions3D::checkCollision(const Geometry3D::Sphere& sphere, const Geometry3D::Plan& plan)
{
	Vector3 planNormal = plan.normal();
	float planDistance = plan.distance();

	planNormal.normalize();

	// Calculate the distance between the center of the sphere and the plan

	// Find a point on the plan
	// Let a point of coordinate = (0, 0, z) z = -d/nz
	float z = - planDistance / planNormal.getZ();
	Vector3 pointOnPlan(0, 0, z);

	// Calculate the distancec from the sphere center to plan 
	Vector3 sphereCenter = sphere.center().toVector3();
	float distance = std::abs(planNormal.dot(sphereCenter) + planDistance);

	// Check if the distance is less than the radius of the sphere
	if (distance <= sphere.radius())
		return true;

	// No collision
	return false;
}

#pragma endregion All functions Sphere 3D

#pragma region Plan Collision 3D

bool LibMath::Collisions3D::checkCollision(const Geometry3D::Plan& plan1, const Geometry3D::Plan& plan2)
{
	Vector3 plan1Normal = plan1.normal();
	Vector3 plan2Normal = plan2.normal();

	Vector3 crossProduct = plan1Normal.cross(plan2Normal);

	// Check if the two plans are parallel
	if (crossProduct.magnitude() == 0.f)
	{
		// Check if the two plans are overlapping
		if (std::abs(plan1.distance()) - std::abs(plan2.distance()) == 0)
			return true;
		else
			return false;
	}	

	// Collision
	return true;
}

bool LibMath::Collisions3D::checkCollision(const Geometry3D::Plan& plan, const Geometry3D::Line& line)
{
	Vector3 planNormal = plan.normal();

	
	// Calculate the dot product between the plan normal and the line direction

	float dotProduct = planNormal.dot(line.getDirection());

	// Check if the dot product is equal to 0
	if (dotProduct == 0.f)
	{
		return checkCollision(plan, line.getOrigin());
		// The line is parallel to the plan

	}
	 
	return true;
}

bool LibMath::Collisions3D::checkCollision(const Geometry3D::Plan& plan, const Geometry3D::Point& point)
{
	Vector3 planNormal = plan.normal();

	planNormal.normalize();

	float distance = planNormal.dot(point.toVector3()) - plan.distance();

	return distance == 0.f;
}
#pragma endregion All functions Plan 3D

#pragma region Capsule Collision 3D

bool LibMath::Collisions3D::checkCollision(const Geometry3D::Capsule& capsule, const Geometry3D::Point& point)
{
	// Calculate the vector from point A to point B of the capsule's central axis
	LibMath::Vector3 capsuleAxisDirection(capsule.m_pointB.toVector3() - capsule.m_pointA.toVector3());

	// Calculate the vector from point A to the test point
	LibMath::Vector3 pointToAxisStart(point.toVector3() - capsule.m_pointA.toVector3());

	// Project the point onto the capsule's central axis using dot product
	float projectionParameter = pointToAxisStart.dot(capsuleAxisDirection) / capsuleAxisDirection.magnitudeSquared();

	// Clamp t to [0,1] to ensure the projection stays within the capsule's cylinder part
	projectionParameter = LibMath::clamp(projectionParameter, 0.f, 1.f);

	// Calculate the closest point on the capsule's central axis to our test point
	// This is the projected point using the clamped parametric value
	Geometry3D::Point closestPointOnAxis(capsule.m_pointA.getX() + (projectionParameter * capsuleAxisDirection.getX()),
		capsule.m_pointA.getY() + (projectionParameter * capsuleAxisDirection.getY()),
		capsule.m_pointA.getZ() + (projectionParameter * capsuleAxisDirection.getZ()));

	// Calculate the distance from the test point to the closest point on the capsule's axis
	float distanceToAxis = (point.toVector3() - closestPointOnAxis.toVector3()).magnitude();

	// Check if the distance is within the capsule's radius
	if (distanceToAxis <= capsule.m_radius)
	{
		return true;  // Point is inside or on the capsule
	}
	return false;     // Point is outside the capsule
}

bool LibMath::Collisions3D::checkCollision(const Geometry3D::Capsule& capsule, const Geometry3D::Line& line)
{
	LibMath::Vector3 normalizedLineDirection = line.m_direction;
	normalizedLineDirection.normalize();

	// Vector from line origin to capsule start point
	LibMath::Vector3 lineOriginToCapsuleStart = line.m_origin.toVector3() - capsule.m_pointA.toVector3();

	// Capsule central axis vector
	LibMath::Vector3 capsuleCentralAxis = capsule.m_pointB.toVector3() - capsule.m_pointA.toVector3();

	// Quadratic equation coefficients for distance²(t) between line and capsule axis
	// The distance function is: distance²(t) = quadraticCoeffA * t² + quadraticCoeffB * t + quadraticCoeffC
	float lineDotLine = normalizedLineDirection.dot(normalizedLineDirection);
	float lineDotAxis = normalizedLineDirection.dot(capsuleCentralAxis);
	float axisMagnitudeSquared = capsuleCentralAxis.magnitudeSquared();

	float quadraticCoeffA = lineDotLine - (lineDotAxis * lineDotAxis) / axisMagnitudeSquared;

	float originDotLine = lineOriginToCapsuleStart.dot(normalizedLineDirection);
	float originDotAxis = lineOriginToCapsuleStart.dot(capsuleCentralAxis);

	float quadraticCoeffB = 2.0f * (originDotLine - (originDotAxis * lineDotAxis) / axisMagnitudeSquared);

	float quadraticCoeffC = lineOriginToCapsuleStart.dot(lineOriginToCapsuleStart) -
		(originDotAxis * originDotAxis) / axisMagnitudeSquared;

	// If quadraticCoeffA is nearly zero, the line is parallel to the capsule axis
	if (LibMath::almostEqual(fabs(quadraticCoeffA), 0)) {
		// For parallel case, calculate perpendicular distance from line to axis
		LibMath::Vector3 perpendicularVector = lineOriginToCapsuleStart - 
			capsuleCentralAxis * (originDotAxis / axisMagnitudeSquared);
		float perpendicularDistance = perpendicularVector.magnitude();

		if (perpendicularDistance <= capsule.m_radius) {
			// Check if line actually intersects the finite capsule segment in positive direction
			float lineParameterAtOriginProjection = -originDotLine;
			float lineParameterAtEndProjection = lineParameterAtOriginProjection +
				(capsuleCentralAxis.magnitude() * lineDotAxis) / capsuleCentralAxis.magnitude();

			if (lineParameterAtEndProjection >= 0.0f &&
				(lineParameterAtOriginProjection <= 0.0f || lineParameterAtOriginProjection >= 0.0f)) {
				return true;
			}
		}
	}
	else {
		// Find the line parameter t where distance to capsule axis is minimum
		float lineParameterAtMinDistance = -quadraticCoeffB / (2.0f * quadraticCoeffA);

		// Check if this minimum distance point is in the positive direction of the line
		if (lineParameterAtMinDistance >= 0.0f) {
			float minimumDistanceSquared = quadraticCoeffC - (quadraticCoeffB * quadraticCoeffB) / (4.0f * quadraticCoeffA);

			if (minimumDistanceSquared <= capsule.m_radius * capsule.m_radius) {
				return true;
			}
		}
	}

	// If no collision with cylindrical part, check spherical end caps
	Geometry3D::Sphere sphericalEndCapA(capsule.m_pointA, capsule.m_radius);
	if (checkCollision(sphericalEndCapA, line))
		return true;

	Geometry3D::Sphere sphericalEndCapB(capsule.m_pointB, capsule.m_radius);
	return checkCollision(sphericalEndCapB, line);
}

bool LibMath::Collisions3D::checkCollision(const Geometry3D::Capsule& capsule, const Geometry3D::AABB& aabb)
{
	// Find the closest point on the capsule's segment to the AABB's center
	Geometry3D::Point segmentPointToConsider = getClosestToSegment(capsule.m_pointA, capsule.m_pointB, aabb.center());

	// Find the closest point on the AABB to that segment point
	Geometry3D::Point aabbClosestPoint = getClosestToAABB(aabb, segmentPointToConsider);

	// Find the closest point on the segment to the AABB's closest point
	Geometry3D::Point finalSegmentClosestPoint = getClosestToSegment(capsule.m_pointA, capsule.m_pointB, aabbClosestPoint);

	// Calculate the squared distance between these two final closest points
	float distanceSquared = finalSegmentClosestPoint.getDistanceSquared(aabbClosestPoint);

	// Return true if the squared distance is less than or equal to the capsule's squared radius
	return distanceSquared <= (capsule.m_radius * capsule.m_radius);
}

bool LibMath::Collisions3D::checkCollision(const Geometry3D::Capsule& capsule1, const Geometry3D::Capsule& capsule2)
{
	// First check: Test if capsule endpoints are inside the other capsule's cylindrical body
	// This catches cases where one capsule penetrates the side of another
	if (checkCollision(capsule1, capsule2.m_pointA) || checkCollision(capsule1, capsule2.m_pointB) ||
		checkCollision(capsule2, capsule1.m_pointA) || checkCollision(capsule2, capsule1.m_pointB))
	{
		return true;
	}

	// Second check: Test collision between the spherical end caps
	// Create spheres at each capsule endpoint with the capsule's radius
	Geometry3D::Sphere firstEndCapSphere1(capsule1.m_pointA, capsule1.m_radius);
	Geometry3D::Sphere secondEndCapSphere1(capsule1.m_pointB, capsule1.m_radius);
	Geometry3D::Sphere firstEndCapSphere2(capsule2.m_pointA, capsule2.m_radius);
	Geometry3D::Sphere secondEndCapSphere2(capsule2.m_pointB, capsule2.m_radius);

	// Test all combinations of end cap sphere collisions
	if (checkCollision(firstEndCapSphere1, firstEndCapSphere2) ||
		checkCollision(firstEndCapSphere1, secondEndCapSphere2) ||
		checkCollision(secondEndCapSphere1, firstEndCapSphere2) ||
		checkCollision(secondEndCapSphere1, secondEndCapSphere2))
	{
		return true;
	}

	// Third check: Calculate minimum distance between the central line segments
	// This is the core collision test - handles cases where capsules cross or run parallel

	// Get the direction vectors (axes) of both capsules
	Vector3 axis1 = capsule1.m_pointB.toVector3() - capsule1.m_pointA.toVector3();
	Vector3 axis2 = capsule2.m_pointB.toVector3() - capsule2.m_pointA.toVector3();
	Vector3 w = capsule1.m_pointA.toVector3() - capsule2.m_pointA.toVector3();

	// Compute dot products for the closest point algorithm
	float a = axis1.dot(axis1);  // Length squared of axis1
	float b = axis1.dot(axis2);  // Dot product of both axes (measures parallelism)
	float c = axis2.dot(axis2);  // Length squared of axis2
	float d = axis1.dot(w);      // Projection of offset vector onto axis1
	float e = axis2.dot(w);      // Projection of offset vector onto axis2

	float denominator = a * c - b * b;  // Determinant
	float s, t;  // Parameters for closest points on each line segment

	// Handle parallel or nearly parallel segments
	if (denominator < 1e-6f)
	{
		s = 0.0f;  // Use start of first segment
		t = (b > c ? d / b : e / c);  // Find closest point on second segment
	}
	else
	{
		// Segments are not parallel - solve for closest approach points
		s = (b * e - c * d) / denominator;
		t = (a * e - b * d) / denominator;
	}

	// Clamp parameters to [0,1] to ensure points lie on the finite line segments
	s = LibMath::clamp(s, 0.0f, 1.0f);
	t = LibMath::clamp(t, 0.0f, 1.0f);

	// Calculate the actual closest points on both capsule axes
	Vector3 closestPoint1 = capsule1.m_pointA.toVector3() + axis1 * s;
	Vector3 closestPoint2 = capsule2.m_pointA.toVector3() + axis2 * t;

	// Measure distance between the closest points
	float distance = (closestPoint1 - closestPoint2).magnitude();

	// Collision occurs if the distance is within the combined radii of both capsules
	return distance <= (capsule1.m_radius + capsule2.m_radius);

}

bool LibMath::Collisions3D::checkCollision(const Geometry3D::Capsule& capsule, const Geometry3D::Plan& plan)
{
	LibMath::Vector3 pointA = capsule.m_pointA.toVector3();
	LibMath::Vector3 pointB = capsule.m_pointB.toVector3();

	float distanceToPlaneA = pointA.dot(plan.m_normal) + plan.m_distance;
	float distanceToPlaneB = pointB.dot(plan.m_normal) + plan.m_distance;

	float minDistance;

	if ((distanceToPlaneA >= 0 && distanceToPlaneB >= 0) || (distanceToPlaneA <= 0 && distanceToPlaneB <= 0))
	{
		minDistance = std::min(std::abs(distanceToPlaneA), std::abs(distanceToPlaneB));
	}
	else 
	{
		minDistance = 0.0f;
	}

	return minDistance <= capsule.m_radius;
}

bool LibMath::Collisions3D::checkCollision(const Geometry3D::Capsule& capsule, const Geometry3D::Sphere& sphere)
{
	LibMath::Vector3 capsuleAxis = capsule.m_pointB.toVector3() - capsule.m_pointA.toVector3();
	LibMath::Vector3 capsulePointAToSphereCenter = sphere.m_center.toVector3() - capsule.m_pointA.toVector3();

	float projection = capsulePointAToSphereCenter.dot(capsuleAxis) / capsuleAxis.dot(capsuleAxis);

	float clampedProjection = LibMath::clamp(projection, 0, 1);

	LibMath::Vector3 closestPoint = capsule.m_pointA.toVector3() + (capsuleAxis * clampedProjection);

	LibMath::Vector3 shortestDistanceVector = closestPoint - sphere.m_center.toVector3();

	float shortestDistance = shortestDistanceVector.magnitude();

	return shortestDistance <= sphere.m_radius + capsule.m_radius;
}

#pragma endregion 

bool LibMath::Collisions3D::checkCollision(const Geometry3D::AABB& aabb, const Geometry3D::Line& line)
{
	// Tolerance for floating-point comparisons
	const float EPSILON = 1e-6f;

	// Extract line properties
	LibMath::Vector3 origin = line.getOrigin().toVector3();
	LibMath::Vector3 direction = line.getDirection();
	float maxLength = line.m_length;

	// Calculate AABB bounds
	LibMath::Vector3 min(
		aabb.center().getX() - aabb.extentX(),
		aabb.center().getY() - aabb.extentY(),
		aabb.center().getZ() - aabb.extentZ()
	);
	LibMath::Vector3 max(
		aabb.center().getX() + aabb.extentX(),
		aabb.center().getY() + aabb.extentY(),
		aabb.center().getZ() + aabb.extentZ()
	);

	// Arrays to store intersection parameters for each axis
	float tMin[3], tMax[3];

	// Convert vectors to arrays for loop processing (X=0, Y=1, Z=2)
	float originArray[3] = { origin.getX(), origin.getY(), origin.getZ() };
	float directionArray[3] = { direction.getX(), direction.getY(), direction.getZ() };
	float minArray[3] = { min.getX(), min.getY(), min.getZ() };
	float maxArray[3] = { max.getX(), max.getY(), max.getZ() };

	// Process each axis (X, Y, Z)
	for (int i = 0; i < 3; ++i)
	{
		if (directionArray[i] == 0.0f)
		{
			// Line is parallel to this axis - check if origin is within AABB bounds
			if (originArray[i] < minArray[i] - EPSILON || originArray[i] > maxArray[i] + EPSILON)
				return false; // Line is outside AABB on this axis

			// Line is within bounds - intersection spans entire line
			tMin[i] = -std::numeric_limits<float>::infinity();
			tMax[i] = std::numeric_limits<float>::infinity();
		}
		else
		{
			// Calculate intersection parameters for both AABB planes on this axis
			float invDir = 1.0f / directionArray[i];
			float t1 = (minArray[i] - originArray[i]) * invDir;
			float t2 = (maxArray[i] - originArray[i]) * invDir;

			// Store min and max intersection parameters
			tMin[i] = std::min(t1, t2);
			tMax[i] = std::max(t1, t2);
		}
	}

	// Find overall intersection interval
	float tEnter = std::max({ tMin[0], tMin[1], tMin[2] }); // Latest entry point
	float tExit = std::min({ tMax[0], tMax[1], tMax[2] });   // Earliest exit point

	// Check if intersection exists and is within line segment bounds
	return tEnter <= tExit + EPSILON && tExit >= -EPSILON && tEnter <= maxLength + EPSILON;
}

bool LibMath::Collisions3D::checkCollision(const Geometry3D::AABB& aabb1, const Geometry3D::AABB& aabb2)
{
	// Check if the AABBs overlap on all axes
	return (aabb1.center().getX() - aabb1.extentX() <= aabb2.center().getX() + aabb2.extentX() &&
		aabb1.center().getX() + aabb1.extentX() >= aabb2.center().getX() - aabb2.extentX() &&
		aabb1.center().getY() - aabb1.extentY() <= aabb2.center().getY() + aabb2.extentY() &&
		aabb1.center().getY() + aabb1.extentY() >= aabb2.center().getY() - aabb2.extentY() &&
		aabb1.center().getZ() - aabb1.extentZ() <= aabb2.center().getZ() + aabb2.extentZ() &&
		aabb1.center().getZ() + aabb1.extentZ() >= aabb2.center().getZ() - aabb2.extentZ());
}

bool LibMath::Collisions3D::checkCollision(const Geometry3D::AABB& aabb, const Geometry3D::Point& point)
{
	return (aabb.center().getX() - aabb.extentX() <= point.getX() &&
		aabb.center().getX() + aabb.extentX() >= point.getX() &&
		aabb.center().getY() - aabb.extentY() <= point.getY() &&
		aabb.center().getY() + aabb.extentY() >= point.getY() &&
		aabb.center().getZ() - aabb.extentZ() <= point.getZ() &&
		aabb.center().getZ() + aabb.extentZ() >= point.getZ());
}

bool LibMath::Collisions3D::checkCollision(const Geometry3D::AABB& aabb, const Geometry3D::Sphere& sphere)
{
	Geometry3D::Point closestPoint = Geometry3D::getClosestToAABB(aabb, sphere.m_center);

	LibMath::Vector3 shortestDistanceVector = closestPoint.toVector3() - sphere.m_center.toVector3();

	float shortestDistance = shortestDistanceVector.magnitudeSquared();


	return shortestDistance <= sphere.m_radius * sphere.m_radius;
}
