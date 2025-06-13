#define	_USE_MATH_DEFINES
#include <cmath>
#include "LibMath/Vector/Vector3.h"
#include "LibMath/GeometricObject3.h"
#include "LibMath/Collisions.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

using namespace LibMath::Geometry3D;

namespace Collision = LibMath::Collisions3D;

TEST_CASE("Point3D", "[.all][geometricObject3D]")
{
    // Destructor
    {
        Point point;
    }

    SECTION("Instantiation") 
    {
        Point p1;  // Default constructor
        REQUIRE(p1.getX() == Catch::Approx(0.f));
        REQUIRE(p1.getY() == Catch::Approx(0.f));
        REQUIRE(p1.getZ() == Catch::Approx(0.f));

        Point p2(1.f, 2.f, 3.f);  // Param constructor
        REQUIRE(p2.getX() == Catch::Approx(1.f));
        REQUIRE(p2.getY() == Catch::Approx(2.f));
        REQUIRE(p2.getZ() == Catch::Approx(3.f));

        Point p3(p2);  // Copy constructor
        REQUIRE(p3.getX() == Catch::Approx(1.f));
        REQUIRE(p3.getY() == Catch::Approx(2.f));
        REQUIRE(p3.getZ() == Catch::Approx(3.f));
    }

    SECTION("Assignment Operator") 
    {
        Point p1(4.f, 5.f, 6.f);
        Point p2;
        p2 = p1;

        REQUIRE(p2.getX() == Catch::Approx(4.f));
        REQUIRE(p2.getY() == Catch::Approx(5.f));
        REQUIRE(p2.getZ() == Catch::Approx(6.f));
    }

    SECTION("Vector Conversion")
    {
        LibMath::Geometry3D::Point point(5.0f, 10.0f, 15.0f);
        LibMath::Vector3 vec = point.toVector3();
        CHECK(vec.getX() == 5.0f);
        CHECK(vec.getY() == 10.0f);
        CHECK(vec.getZ() == 15.0f);
    }

    SECTION("Const Getters") 
    {
        const Point p(10.f, 11.f, 12.f);

        REQUIRE(p.getX() == Catch::Approx(10.f));
        REQUIRE(p.getY() == Catch::Approx(11.f));
        REQUIRE(p.getZ() == Catch::Approx(12.f)); // Attention ici : probable bug !
    }
}

TEST_CASE("Line3D", "[.all][geometricObject3D]")
{
    const Point origin(1.f, 2.f, 3.f);
    const LibMath::Vector3 dir(0.f, 1.f, 0.f); // unitaire supposé


    // Destructor
    {
        Line line;
    }

    SECTION("Constructors") 
    {
        Line l1;
        REQUIRE(l1.getOrigin().getX() == Catch::Approx(0.f));
        REQUIRE(l1.getOrigin().getY() == Catch::Approx(0.f));
        REQUIRE(l1.getOrigin().getZ() == Catch::Approx(0.f));
        REQUIRE(l1.getDirection().getX() == Catch::Approx(0.f));
        REQUIRE(l1.getDirection().getY() == Catch::Approx(0.f));
        REQUIRE(l1.getDirection().getZ()  == Catch::Approx(0.f));

        Line l2(origin, dir);
        REQUIRE(l2.getOrigin().getX() == Catch::Approx(1.f));
        REQUIRE(l2.getOrigin().getY() == Catch::Approx(2.f));
        REQUIRE(l2.getOrigin().getZ() == Catch::Approx(3.f));
        REQUIRE(l2.getDirection().getX() == Catch::Approx(0.f));
        REQUIRE(l2.getDirection().getY() == Catch::Approx(1.f));
        REQUIRE(l2.getDirection().getZ() == Catch::Approx(0.f));

        Line l3(l2); // copy constructor
        REQUIRE(l3.getOrigin().getX() == Catch::Approx(1.f));
        REQUIRE(l3.getOrigin().getY() == Catch::Approx(2.f));
        REQUIRE(l3.getOrigin().getZ() == Catch::Approx(3.f));
        REQUIRE(l3.getDirection().getX() == Catch::Approx(0.f));
        REQUIRE(l3.getDirection().getY() == Catch::Approx(1.f));
        REQUIRE(l3.getDirection().getZ() == Catch::Approx(0.f));
    }

    SECTION("Assignment operator")
    {
        Line l1(origin, dir);
        Line l2;
        l2 = l1;

        REQUIRE(l2.getOrigin().getX() == Catch::Approx(1.f));
        REQUIRE(l2.getOrigin().getY() == Catch::Approx(2.f));
        REQUIRE(l2.getOrigin().getZ() == Catch::Approx(3.f));
        REQUIRE(l2.getDirection().getX() == Catch::Approx(0.f));
        REQUIRE(l2.getDirection().getY() == Catch::Approx(1.f));
        REQUIRE(l2.getDirection().getZ() == Catch::Approx(0.f));
    }
}

TEST_CASE("Plan3D", "[.all][geometricObject3D]") 
{
    const LibMath::Vector3 normal(0.f, 1.f, 0.f);
    const float distance = 5.f;

    SECTION("Default constructor") 
    {
        Plan p;
        REQUIRE(p.normal().getX() == Catch::Approx(0.f));
        REQUIRE(p.normal().getY() == Catch::Approx(0.f));
        REQUIRE(p.normal().getZ() == Catch::Approx(0.f));
        REQUIRE(p.distance() == Catch::Approx(0.f));
    }

    SECTION("Parameterized constructor") 
    {
        Plan p(normal, distance);
        REQUIRE(p.normal().getX() == Catch::Approx(0.f));
        REQUIRE(p.normal().getY() == Catch::Approx(1.f));
        REQUIRE(p.normal().getZ() == Catch::Approx(0.f));
        REQUIRE(p.distance() == Catch::Approx(5.f));
    }

    SECTION("Copy constructor") 
    {
        Plan original(normal, distance);
        Plan copy(original);

        REQUIRE(copy.normal().getX() == Catch::Approx(0.f));
        REQUIRE(copy.normal().getY() == Catch::Approx(1.f));
        REQUIRE(copy.normal().getZ() == Catch::Approx(0.f));
        REQUIRE(copy.distance() == Catch::Approx(5.f));
    }

    SECTION("Assignment operator") 
    {
        Plan p1(normal, distance);
        Plan p2;
        p2 = p1;

        REQUIRE(p2.normal().getX() == Catch::Approx(0.f));
        REQUIRE(p2.normal().getY() == Catch::Approx(1.f));
        REQUIRE(p2.normal().getZ() == Catch::Approx(0.f));
        REQUIRE(p2.distance() == Catch::Approx(5.f));
    }
}

TEST_CASE("AABB3D", "[.all][geometricObject3D]") 
{
    const Point center(1.f, 2.f, 3.f);
    const float width = 4.f;
    const float height = 6.f;
    const float depth = 8.f;

    SECTION("Default constructor") 
    {
        AABB aabb;
        REQUIRE(aabb.center().getX() == Catch::Approx(0.f));
        REQUIRE(aabb.center().getY() == Catch::Approx(0.f));
        REQUIRE(aabb.center().getZ() == Catch::Approx(0.f));
        REQUIRE(aabb.extentX() == Catch::Approx(0.f));
        REQUIRE(aabb.extentY() == Catch::Approx(0.f));
        REQUIRE(aabb.extentZ() == Catch::Approx(0.f));
    }

    SECTION("Parameterized constructor") 
    {
        AABB aabb(center, width, height, depth);
        REQUIRE(aabb.center().getX() == Catch::Approx(1.f));
        REQUIRE(aabb.center().getY() == Catch::Approx(2.f));
        REQUIRE(aabb.center().getZ() == Catch::Approx(3.f));
        REQUIRE(aabb.extentX() == Catch::Approx(width / 2.f));
        REQUIRE(aabb.extentY() == Catch::Approx(height / 2.f));
        REQUIRE(aabb.extentZ() == Catch::Approx(depth / 2.f));
    }

    SECTION("Copy constructor")
    {
        AABB original(center, width, height, depth);
        AABB copy(original);
        REQUIRE(copy.center().getX() == Catch::Approx(1.f));
        REQUIRE(copy.center().getY() == Catch::Approx(2.f));
        REQUIRE(copy.center().getZ() == Catch::Approx(3.f));
        REQUIRE(copy.extentX() == Catch::Approx(width / 2.f));
        REQUIRE(copy.extentY() == Catch::Approx(height / 2.f));
        REQUIRE(copy.extentZ() == Catch::Approx(depth / 2.f));
    }

    SECTION("Assignment operator") 
    {
        AABB a1(center, width, height, depth);
        AABB a2;
        a2 = a1;
        REQUIRE(a2.center().getX() == Catch::Approx(1.f));
        REQUIRE(a2.center().getY() == Catch::Approx(2.f));
        REQUIRE(a2.center().getZ() == Catch::Approx(3.f));
        REQUIRE(a2.extentX() == Catch::Approx(width / 2.f));
        REQUIRE(a2.extentY() == Catch::Approx(height / 2.f));
        REQUIRE(a2.extentZ() == Catch::Approx(depth / 2.f));
    }
}

TEST_CASE("OBB3D", "[.all][geometricObject3D]") 
{
    const Point center(1.f, 2.f, 3.f);
    const float width = 4.f;
    const float height = 6.f;
    const float depth = 8.f;
    const LibMath::Radian rotation(1.5f); // 1.5 radians

    SECTION("Default constructor") 
    {
        OBB obb;
        REQUIRE(obb.rotation().raw() == Catch::Approx(0.f));
    }

    SECTION("Parameterized constructor") {
        OBB obb(center, width, height, depth, rotation);
        REQUIRE(obb.rotation().raw() == Catch::Approx(1.5f));
    }

    SECTION("Copy constructor") {
        OBB original(center, width, height, depth, rotation);
        OBB copy(original);
        REQUIRE(copy.rotation().raw() == Catch::Approx(1.5f));
    }

    SECTION("Assignment operator") {
        OBB obb1(center, width, height, depth, rotation);
        OBB obb2;
        obb2 = obb1;
        REQUIRE(obb2.rotation().raw() == Catch::Approx(1.5f));
    }
}

TEST_CASE("Sphere3D", "[.all][geometricObject3D]") {
    const Point center(1.f, 2.f, 3.f);
    const float radius = 5.f;

    SECTION("Default constructor") {
        Sphere s;
        REQUIRE(s.radius() == Catch::Approx(0.f));
        REQUIRE(s.center().getX() == Catch::Approx(0.f));
        REQUIRE(s.center().getY() == Catch::Approx(0.f));
        REQUIRE(s.center().getZ() == Catch::Approx(0.f));
    }

    SECTION("Parameterized constructor") {
        Sphere s(center, radius);
        REQUIRE(s.radius() == Catch::Approx(5.f));
        REQUIRE(s.center().getX() == Catch::Approx(1.f));
        REQUIRE(s.center().getY() == Catch::Approx(2.f));
        REQUIRE(s.center().getZ() == Catch::Approx(3.f));
    }

    SECTION("Copy constructor") {
        Sphere s1(center, radius);
        Sphere s2(s1);
        REQUIRE(s2.radius() == Catch::Approx(5.f));
        REQUIRE(s2.center().getX() == Catch::Approx(1.f));
        REQUIRE(s2.center().getY() == Catch::Approx(2.f));
        REQUIRE(s2.center().getZ() == Catch::Approx(3.f));
    }

    SECTION("Assignment operator") {
        Sphere s1(center, radius);
        Sphere s2;
        s2 = s1;
        REQUIRE(s2.radius() == Catch::Approx(5.f));
        REQUIRE(s2.center().getX() == Catch::Approx(1.f));
        REQUIRE(s2.center().getY() == Catch::Approx(2.f));
        REQUIRE(s2.center().getZ() == Catch::Approx(3.f));
    }
}

TEST_CASE("Capsule3D", "[.all][geometricObject3D]") {
    const Point a(1.f, 2.f, 3.f);
    const Point b(4.f, 5.f, 6.f);
    const float radius = 2.f;

    SECTION("Default constructor") {
        Capsule c;
        REQUIRE(c.m_radius == Catch::Approx(0.f));
        REQUIRE(c.m_pointA.getX() == Catch::Approx(0.f));
        REQUIRE(c.m_pointA.getY() == Catch::Approx(0.f));
        REQUIRE(c.m_pointA.getZ() == Catch::Approx(0.f));

        REQUIRE(c.m_pointB.getX() == Catch::Approx(0.f));
        REQUIRE(c.m_pointB.getY() == Catch::Approx(0.f));
        REQUIRE(c.m_pointB.getZ() == Catch::Approx(0.f));
    }

    SECTION("Parameterized constructor") {
        Capsule c(a, b, radius);
        REQUIRE(c.m_radius == Catch::Approx(2.f));
        REQUIRE(c.m_pointA.getX() == Catch::Approx(1.f));
        REQUIRE(c.m_pointA.getY() == Catch::Approx(2.f));
        REQUIRE(c.m_pointA.getZ() == Catch::Approx(3.f));

        REQUIRE(c.m_pointB.getX() == Catch::Approx(4.f));
        REQUIRE(c.m_pointB.getY() == Catch::Approx(5.f));
        REQUIRE(c.m_pointB.getZ() == Catch::Approx(6.f));
    }

    SECTION("Copy constructor") {
        Capsule c1(a, b, radius);
        Capsule c2(c1);
        REQUIRE(c2.m_radius == Catch::Approx(2.f));
        REQUIRE(c2.m_pointA.getX() == Catch::Approx(1.f));
        REQUIRE(c2.m_pointB.getZ() == Catch::Approx(6.f));
    }

    SECTION("Assignment operator") {
        Capsule c1(a, b, radius);
        Capsule c2;
        c2 = c1;
        REQUIRE(c2.m_radius == Catch::Approx(2.f));
        REQUIRE(c2.m_pointA.getY() == Catch::Approx(2.f));
        REQUIRE(c2.m_pointB.getX() == Catch::Approx(4.f));
    }
}

TEST_CASE("Sphere Collisions", "[.all][Collision3D][sphere]")
{
    SECTION("Sphere-Sphere Collision")
    {
        // Non-overlapping spheres
        Sphere sphere1({ 0.0f, 0.0f, 0.0f }, 5.0f);
        Sphere sphere2({ 20.0f, 20.0f, 20.0f }, 5.0f);
        CHECK_FALSE(Collision::checkCollision(sphere1, sphere2));
        

        // Touching spheres (externally)
        Sphere sphere3({ 0.0f, 0.0f, 0.0f }, 5.0f);
        Sphere sphere4({ 10.0f, 0.0f, 0.0f }, 5.0f);
        CHECK(Collision::checkCollision(sphere3, sphere4));

        // Overlapping spheres
        Sphere sphere5({ 0.0f, 0.0f, 0.0f }, 5.0f);
        Sphere sphere6({ 3.0f, 0.0f, 0.0f }, 3.0f);
        CHECK(Collision::checkCollision(sphere5, sphere6));

        // One sphere contained within another
        Sphere sphereLarge({ 0.0f, 0.0f, 0.0f }, 10.0f);
        Sphere sphereSmall({ 2.0f, 2.0f, 2.0f }, 1.0f);
        CHECK(Collision::checkCollision(sphereLarge, sphereSmall));

        // Identical spheres
        Sphere sphereA({ 5.0f, 5.0f, 5.0f }, 3.0f);
        Sphere sphereB({ 5.0f, 5.0f, 5.0f }, 3.0f);
        CHECK(Collision::checkCollision(sphereA, sphereB));
    }

    SECTION("Sphere-Point Collision")
    {
        Sphere sphere({ 0.0f, 0.0f, 0.0f }, 5.0f);

        // Point inside the sphere
        Point pointInside({ 2.0f, 2.0f, 2.0f });
        CHECK(Collision::checkCollision(sphere, pointInside));

        // Point on the surface of the sphere
        Point pointSurface({ 5.0f, 0.0f, 0.0f });
        CHECK(Collision::checkCollision(sphere, pointSurface));

        // Point outside the sphere
        Point pointOutside({ 10.0f, 10.0f, 10.0f });
        CHECK_FALSE(Collision::checkCollision(sphere, pointOutside));

        // Point at the center of the sphere
        Point pointCenter({ 0.0f, 0.0f, 0.0f });
        CHECK(Collision::checkCollision(sphere, pointCenter));

        // Point very close but outside
        Point pointClose({ 5.1f, 0.0f, 0.0f });
        CHECK_FALSE(Collision::checkCollision(sphere, pointClose));
    }

    SECTION("Sphere-Line Collision")
    {
        Sphere sphere({ 0.0f, 0.0f, 0.0f }, 5.0f);

        // Line passing through the center
        Line lineThrough({ -10.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
        CHECK(Collision::checkCollision(sphere, lineThrough));

        // Line tangent to the sphere
        Line lineTangent({ -10.0f, 5.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
        CHECK(Collision::checkCollision(sphere, lineTangent));

        // Line missing the sphere
        Line lineMissing({ -10.0f, 10.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
        CHECK_FALSE(Collision::checkCollision(sphere, lineMissing));

        // Line entirely inside the sphere
        Line lineInside({ -2.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
        CHECK(Collision::checkCollision(sphere, lineInside));

        // Diagonal line intersecting
        Line lineDiagonal({ -10.0f, -10.0f, -10.0f }, { 1.0f, 1.0f, 1.0f });
        CHECK(Collision::checkCollision(sphere, lineDiagonal));
    }

    SECTION("Sphere-Plan Collision")
    {
        Sphere sphere({ 0.0f, 0.0f, 0.0f }, 5.0f);

        // Plan cutting through the sphere
        Plan planCutting({ 0.0f, 1.0f, 0.0f }, 2.0f); // y = 2
        CHECK(Collision::checkCollision(sphere, planCutting));

        // Plan tangent to the sphere
        Plan planTangent({ 0.0f, 1.0f, 0.0f }, 5.0f); // y = 5
        CHECK(Collision::checkCollision(sphere, planTangent));

        // Plan not touching the sphere
        Plan planDistant({ 0.0f, 1.0f, 0.0f }, 10.0f); // y = 10
        CHECK_FALSE(Collision::checkCollision(sphere, planDistant));

        // Plan passing through the center
        Plan planCenter({ 1.0f, 0.0f, 0.0f }, 0.0f); // x = 0
        CHECK(Collision::checkCollision(sphere, planCenter));

        // Diagonal plan
        Plan planDiagonal({ 1.0f, 1.0f, 1.0f }, 3.0f);
        CHECK(Collision::checkCollision(sphere, planDiagonal));
    }
}

TEST_CASE("Plan Collisions", "[.all][Collision3D][plan]")
{
    SECTION("Plan-Plan Collision")
    {
        // Parallel plans (same normal, different distances)
        Plan plan1({ 0.0f, 1.0f, 0.0f }, 5.0f);  // y = 5
        Plan plan2({ 0.0f, 1.0f, 0.0f }, 10.0f); // y = 10
        CHECK_FALSE(Collision::checkCollision(plan1, plan2));

        // Identical plans
        Plan plan3({ 0.0f, 1.0f, 0.0f }, 5.0f);
        Plan plan4({ 0.0f, 1.0f, 0.0f }, 5.0f);
        CHECK(Collision::checkCollision(plan3, plan4));

        // Intersecting plans (different normals)
        Plan planXY({ 0.0f, 0.0f, 1.0f }, 0.0f); // z = 0
        Plan planYZ({ 1.0f, 0.0f, 0.0f }, 0.0f); // x = 0
        CHECK(Collision::checkCollision(planXY, planYZ));

        // Perpendicular plans
        Plan planHorizontal({ 0.0f, 1.0f, 0.0f }, 0.0f); // y = 0
        Plan planVertical({ 1.0f, 0.0f, 0.0f }, 0.0f);   // x = 0
        CHECK(Collision::checkCollision(planHorizontal, planVertical));

        // Plans with opposite normals but same plane
        Plan plan5({ 0.0f, 1.0f, 0.0f }, 5.0f);
        Plan plan6({ 0.0f, -1.0f, 0.0f }, -5.0f);
        CHECK(Collision::checkCollision(plan5, plan6));
    }

    SECTION("Plan-Line Collision")
    {
        Plan plan({ 0.0f, 1.0f, 0.0f }, 5.0f); // y = 5

        // Line contained in the plan
        Line lineInPlan({ 0.0f, 5.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
        CHECK(Collision::checkCollision(plan, lineInPlan));

        // Line crossing the plan
        Line lineCrossing({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
        CHECK(Collision::checkCollision(plan, lineCrossing));

        // Line parallel to the plan (above)
        Line lineParallelAbove({ 0.0f, 10.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
        CHECK_FALSE(Collision::checkCollision(plan, lineParallelAbove));

        // Line parallel to the plan (below)
        Line lineParallelBelow({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
        CHECK_FALSE(Collision::checkCollision(plan, lineParallelBelow));

        // Line touching the plan at one point
        Line lineTouching({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
        CHECK(Collision::checkCollision(plan, lineTouching));
    }
}

TEST_CASE("Capsule Collisions", "[.all][Collision3D][capsule]")
{

    SECTION("Capsule-Point Collision")
    {
        // Vertical capsule from (0,-3,0) to (0,3,0) with radius 2
        Capsule capsule({ 0.0f, -3.0f, 0.0f }, { 0.0f, 3.0f, 0.0f }, 2.0f);

        // Point inside the cylindrical part
        Point pointCylinder({ 1.0f, 0.0f, 0.0f });
        CHECK(Collision::checkCollision(capsule, pointCylinder));

        // Point inside the top hemisphere
        Point pointTopSphere({ 0.0f, 4.0f, 0.0f });
        CHECK(Collision::checkCollision(capsule, pointTopSphere));

        // Point inside the bottom hemisphere
        Point pointBottomSphere({ 0.0f, -4.0f, 0.0f });
        CHECK(Collision::checkCollision(capsule, pointBottomSphere));

        // Point on the surface of the cylinder
        Point pointSurface({ 2.0f, 0.0f, 0.0f });
        CHECK(Collision::checkCollision(capsule, pointSurface));

        // Point outside the capsule
        Point pointOutside({ 5.0f, 0.0f, 0.0f });
        CHECK_FALSE(Collision::checkCollision(capsule, pointOutside));

        // Point at the exact tip of the capsule
        Point pointTip({ 0.0f, 5.0f, 0.0f });
        CHECK(Collision::checkCollision(capsule, pointTip));

        // Point just outside the tip
        Point pointOutsideTip({ 0.0f, 5.1f, 0.0f });
        CHECK_FALSE(Collision::checkCollision(capsule, pointOutsideTip));
    }

    SECTION("Capsule-Line Collision")
    {
        // Horizontal capsule from (-3,0,0) to (3,0,0) with radius 1
        Capsule capsuleH({ -3.0f, 0.0f, 0.0f }, { 3.0f, 0.0f, 0.0f }, 1.0f);

        // Line passing through the center horizontally
        Line lineHorizontal({ -5.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
        CHECK(Collision::checkCollision(capsuleH, lineHorizontal));

        // Line passing through vertically
        Line lineVertical({ 0.0f, -5.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
        CHECK(Collision::checkCollision(capsuleH, lineVertical));

        // Line tangent to the cylindrical part
        Line lineTangentCylinder({ -5.0f, 1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
        CHECK(Collision::checkCollision(capsuleH, lineTangentCylinder));

        // Line hitting one of the spherical ends
        Line lineToEnd({ 3.0f, -2.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
        CHECK(Collision::checkCollision(capsuleH, lineToEnd));

        // Line missing the capsule entirely
        Line lineMissing({ -5.0f, 3.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
        CHECK_FALSE(Collision::checkCollision(capsuleH, lineMissing));

        // Line entirely inside the capsule
        Line lineInside({ -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
        CHECK(Collision::checkCollision(capsuleH, lineInside));

        // Diagonal line intersecting
        Line lineDiagonal({ -5.0f, -5.0f, 0.0f }, { 1.0f, 1.0f, 0.0f });
        CHECK(Collision::checkCollision(capsuleH, lineDiagonal));
    }

    SECTION("Edge Cases for Capsule")
    {
        // Zero-length capsule (essentially a sphere)
        Capsule sphereCapsule({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 3.0f);
        Point pointInSphere({ 2.0f, 0.0f, 0.0f });
        CHECK(Collision::checkCollision(sphereCapsule, pointInSphere));

        // Very long thin capsule
        Capsule thinCapsule({ -100.0f, 0.0f, 0.0f }, { 100.0f, 0.0f, 0.0f }, 0.1f);
        Point pointOnThin({ 50.0f, 0.05f, 0.0f });
        CHECK(Collision::checkCollision(thinCapsule, pointOnThin));

        // Capsule with very large radius
        Capsule fatCapsule({ 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 50.0f);
        Point pointInFat({ 30.0f, 0.0f, 0.0f });
        CHECK(Collision::checkCollision(fatCapsule, pointInFat));
    }

    SECTION("Basic Capsule-AABB Collision")
    {
        // Vertical capsule from (0,-2,0) to (0,2,0) with radius 1
        Capsule capsule({ 0.0f, -2.0f, 0.0f }, { 0.0f, 2.0f, 0.0f }, 1.0f);

        // AABB centered at origin with extent 1
        AABB aabb({ 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f);
        CHECK(Collision::checkCollision(capsule, aabb));

        // AABB touching the cylindrical part
        AABB aabbTouchingCylinder({ 1.25f, 0.0f, 0.0f }, 0.5f, 0.5f, 0.5f);
        CHECK(Collision::checkCollision(capsule, aabbTouchingCylinder));

        // AABB touching the top spherical part
        AABB aabbTouchingTop({ 0.0f, 2.5f, 0.0f }, 0.5f, 0.5f, 0.5f);
        CHECK(Collision::checkCollision(capsule, aabbTouchingTop));

        // AABB touching the bottom spherical part
        AABB aabbTouchingBottom({ 0.0f, -2.5f, 0.0f }, 0.5f, 0.5f, 0.5f);
        CHECK(Collision::checkCollision(capsule, aabbTouchingBottom));

        // AABB clearly outside
        AABB aabbOutside({ 5.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f);
        CHECK_FALSE(Collision::checkCollision(capsule, aabbOutside));
    }

    SECTION("Capsule-AABB Edge Cases")
    {
        // Horizontal capsule
        Capsule capsuleH({ -3.0f, 0.0f, 0.0f }, { 3.0f, 0.0f, 0.0f }, 1.0f);

        // AABB at the exact edge of capsule radius
        AABB aabbEdge({ 0.0f, 1.0f, 0.0f }, 0.1f, 0.1f, 0.1f);
        CHECK(Collision::checkCollision(capsuleH, aabbEdge));

        // AABB just outside the radius
        AABB aabbJustOutside({ 0.0f, 1.2f, 0.0f }, 0.1f, 0.1f, 0.1f);
        CHECK_FALSE(Collision::checkCollision(capsuleH, aabbJustOutside));

        // Large AABB encompassing the entire capsule
        AABB aabbLarge({ 0.0f, 0.0f, 0.0f }, 10.0f, 10.0f, 10.0f);
        CHECK(Collision::checkCollision(capsuleH, aabbLarge));

        // Very small AABB inside capsule
        AABB aabbSmall({ 0.0f, 0.0f, 0.0f }, 0.1f, 0.1f, 0.1f);
        CHECK(Collision::checkCollision(capsuleH, aabbSmall));
    }

    SECTION("Capsule-AABB 3D Cases")
    {
        // Diagonal capsule in 3D space
        Capsule capsule3D({ -2.0f, -2.0f, -2.0f }, { 2.0f, 2.0f, 2.0f }, 1.0f);

        // AABB intersecting the diagonal
        AABB aabb3D({ 0.0f, 0.0f, 0.0f }, 0.5f, 0.5f, 0.5f);
        CHECK(Collision::checkCollision(capsule3D, aabb3D));

        // AABB offset in Z direction
        AABB aabbZ({ 0.0f, 0.0f, 3.0f }, 1.0f, 1.0f, 1.0f);
        CHECK_FALSE(Collision::checkCollision(capsule3D, aabbZ));
    }

    SECTION("Capsule-Capsule Collision")
    {
        SECTION("Basic Capsule-Capsule Collision")
        {
            // Parallel capsules, same axis, overlapping
            Capsule capsule1({ 0.0f, -2.0f, 0.0f }, { 0.0f, 2.0f, 0.0f }, 1.0f);
            Capsule capsule2({ 0.0f, -1.0f, 0.0f }, { 0.0f, 3.0f, 0.0f }, 1.0f);
            CHECK(Collision::checkCollision(capsule1, capsule2));

            // Parallel capsules, same axis, touching end-to-end
            Capsule capsule3({ 0.0f, -2.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 1.0f);
            Capsule capsule4({ 0.0f, 0.0f, 0.0f }, { 0.0f, 2.0f, 0.0f }, 1.0f);
            CHECK(Collision::checkCollision(capsule3, capsule4));

            // Parallel capsules, same axis, separated
            Capsule capsule5({ 0.0f, -3.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, 0.9f);
            Capsule capsule6({ 0.0f, 1.0f, 0.0f }, { 0.0f, 3.0f, 0.0f }, 0.9f);
            CHECK_FALSE(Collision::checkCollision(capsule5, capsule6));

            // Identical capsules
            Capsule capsuleA({ 1.0f, 1.0f, 1.0f }, { 3.0f, 3.0f, 3.0f }, 2.0f);
            Capsule capsuleB({ 1.0f, 1.0f, 1.0f }, { 3.0f, 3.0f, 3.0f }, 2.0f);
            CHECK(Collision::checkCollision(capsuleA, capsuleB));
        }

        SECTION("Perpendicular Capsules")
        {
            // Perpendicular capsules intersecting at center
            Capsule capsuleVertical({ 0.0f, -2.0f, 0.0f }, { 0.0f, 2.0f, 0.0f }, 1.0f);
            Capsule capsuleHorizontal({ -2.0f, 0.0f, 0.0f }, { 2.0f, 0.0f, 0.0f }, 1.0f);
            CHECK(Collision::checkCollision(capsuleVertical, capsuleHorizontal));

            // Perpendicular capsules, cylinder touching sphere end
            Capsule capsuleV({ 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 0.5f);
            Capsule capsuleH({ -2.0f, 1.2f, 0.0f }, { 2.0f, 1.2f, 0.0f }, 0.5f);
            CHECK(Collision::checkCollision(capsuleV, capsuleH));

            // Perpendicular capsules, just missing
            Capsule capsuleV2({ 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 0.2f);
            Capsule capsuleH2({ -2.0f, 1.5f, 0.0f }, { 2.0f, 1.5f, 0.0f }, 0.2f);
            CHECK_FALSE(Collision::checkCollision(capsuleV2, capsuleH2));
        }

        SECTION("Diagonal and 3D Capsules")
        {
            // Diagonal capsules intersecting
            Capsule capsule1({ -2.0f, -2.0f, -2.0f }, { 2.0f, 2.0f, 2.0f }, 1.0f);
            Capsule capsule2({ -2.0f, 2.0f, -2.0f }, { 2.0f, -2.0f, 2.0f }, 1.0f);
            CHECK(Collision::checkCollision(capsule1, capsule2));

            // Parallel diagonal capsules, offset and overlapping
            Capsule capsule3({ -3.0f, -3.0f, -3.0f }, { 3.0f, 3.0f, 3.0f }, 1.0f);
            Capsule capsule4({ -2.0f, -2.0f, -1.0f }, { 4.0f, 4.0f, 5.0f }, 1.0f);
            CHECK(Collision::checkCollision(capsule3, capsule4));

            // Parallel diagonal capsules, separated
            Capsule capsule5({ -2.0f, -2.0f, -2.0f }, { 0.0f, 0.0f, 0.0f }, 0.5f);
            Capsule capsule6({ 3.0f, 3.0f, 3.0f }, { 5.0f, 5.0f, 5.0f }, 0.5f);
            CHECK_FALSE(Collision::checkCollision(capsule5, capsule6));
        }

        SECTION("Capsule-Capsule Edge Cases")
        {
            // One capsule much larger than the other
            Capsule capsuleLarge({ -5.0f, -5.0f, -5.0f }, { 5.0f, 5.0f, 5.0f }, 3.0f);
            Capsule capsuleSmall({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, 0.5f);
            CHECK(Collision::checkCollision(capsuleLarge, capsuleSmall));

            // Zero-length capsules (spheres)
            Capsule sphere1({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 2.0f);
            Capsule sphere2({ 3.0f, 0.0f, 0.0f }, { 3.0f, 0.0f, 0.0f }, 2.0f);
            CHECK(Collision::checkCollision(sphere1, sphere2));

            // Very thin capsules
            Capsule thinCapsule1({ -10.0f, 0.0f, 0.0f }, { 10.0f, 0.0f, 0.0f }, 0.1f);
            Capsule thinCapsule2({ 0.0f, -10.0f, 0.0f }, { 0.0f, 10.0f, 0.0f }, 0.1f);
            CHECK(Collision::checkCollision(thinCapsule1, thinCapsule2));

            // Capsules with spherical ends touching
            Capsule capsuleLeft({ -3.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, 1.0f);
            Capsule capsuleRight({ 1.0f, 0.0f, 0.0f }, { 3.0f, 0.0f, 0.0f }, 1.0f);
            CHECK(Collision::checkCollision(capsuleLeft, capsuleRight));
        }

        SECTION("Capsule-Capsule Symmetry")
        {
            // Test symmetry of collision detection
            Capsule capsule1({ 1.0f, 2.0f, 3.0f }, { 4.0f, 5.0f, 6.0f }, 1.5f);
            Capsule capsule2({ 2.0f, 3.0f, 4.0f }, { 5.0f, 6.0f, 7.0f }, 1.0f);

            bool result1 = Collision::checkCollision(capsule1, capsule2);
            bool result2 = Collision::checkCollision(capsule2, capsule1);
            CHECK(result1 == result2);
        }
    }

    SECTION("Capsule-Plan Collision")
    {
        SECTION("Basic Capsule-Plan Collision")
        {
            // Vertical capsule intersecting horizontal plan
            Capsule capsule({ 0.0f, -2.0f, 0.0f }, { 0.0f, 2.0f, 0.0f }, 1.0f);
            Plan plan({ 0.0f, 1.0f, 0.0f }, 1.0f); // y = 1
            CHECK(Collision::checkCollision(capsule, plan));

            // Capsule completely above plan
            Capsule capsuleAbove({ 0.0f, 3.0f, 0.0f }, { 0.0f, 5.0f, 0.0f }, 1.0f);
            Plan planBelow({ 0.0f, 1.0f, 0.0f }, 1.5f); // y = 1.5
            CHECK_FALSE(Collision::checkCollision(capsuleAbove, planBelow));

            // Capsule completely below plan
            Capsule capsuleBelow({ 0.0f, -5.0f, 0.0f }, { 0.0f, -3.0f, 0.0f }, 1.0f);
            Plan planAbove({ 0.0f, 1.0f, 0.0f }, -1.5f); // y = -1.5
            CHECK_FALSE(Collision::checkCollision(capsuleBelow, planAbove));

            // Capsule tangent to plan
            Capsule capsuleTangent({ 0.0f, 1.0f, 0.0f }, { 0.0f, 3.0f, 0.0f }, 1.0f);
            Plan planTangent({ 0.0f, 1.0f, 0.0f }, 0.0f); // y = 0
            CHECK(Collision::checkCollision(capsuleTangent, planTangent));
        }

        SECTION("Capsule-Plan Different Orientations")
        {
            // Horizontal capsule with vertical plan
            Capsule capsuleH({ -2.0f, 0.0f, 0.0f }, { 2.0f, 0.0f, 0.0f }, 1.0f);
            Plan planV({ 1.0f, 0.0f, 0.0f }, 1.5f); // x = 1.5
            CHECK(Collision::checkCollision(capsuleH, planV));

            // Diagonal capsule with diagonal plan
            Capsule capsuleDiag({ -2.0f, -2.0f, -2.0f }, { 2.0f, 2.0f, 2.0f }, 1.0f);
            Plan planDiag({ 1.0f, 1.0f, 1.0f }, 2.0f);
            CHECK(Collision::checkCollision(capsuleDiag, planDiag));

            // Capsule parallel to plan
            Capsule capsuleParallel({ -2.0f, 1.0f, 0.0f }, { 2.0f, 1.0f, 0.0f }, 0.5f);
            Plan planParallel({ 0.0f, 1.0f, 0.0f }, 0.4f); // y = 0.4
            CHECK_FALSE(Collision::checkCollision(capsuleParallel, planParallel));

            // Z-oriented capsule with XY plan
            Capsule capsuleZ({ 0.0f, 0.0f, -3.0f }, { 0.0f, 0.0f, 3.0f }, 1.0f);
            Plan planXY({ 0.0f, 0.0f, 1.0f }, 2.0f); // z = 2
            CHECK(Collision::checkCollision(capsuleZ, planXY));
        }

        SECTION("Capsule-Plan Edge Cases")
        {
            // Very thin capsule crossing plan
            Capsule thinCapsule({ -5.0f, 0.0f, 0.0f }, { 5.0f, 0.0f, 0.0f }, 0.01f);
            Plan plan({ 0.0f, 1.0f, 0.0f }, 0.005f); // y = 0.005
            CHECK(Collision::checkCollision(thinCapsule, plan));

            // Zero-length capsule (sphere) with plan
            Capsule sphereCapsule({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 2.0f);
            Plan planSphere({ 0.0f, 1.0f, 0.0f }, 1.5f); // y = 1.5
            CHECK(Collision::checkCollision(sphereCapsule, planSphere));

            // Capsule endpoint exactly on plan
            Capsule capsuleOnPlan({ 0.0f, -2.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 1.0f);
            Plan planExact({ 0.0f, 1.0f, 0.0f }, -1.0f); // y = -1
            CHECK(Collision::checkCollision(capsuleOnPlan, planExact));

            // Very large capsule with plan
            Capsule hugeCapsule({ -100.0f, 0.0f, 0.0f }, { 100.0f, 0.0f, 0.0f }, 50.0f);
            Plan smallPlan({ 0.0f, 1.0f, 0.0f }, 25.0f); // y = 25
            CHECK(Collision::checkCollision(hugeCapsule, smallPlan));
        }

        SECTION("Capsule-Plan Boundary Tests")
        {
            Capsule capsule({ 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 1.0f);

            // Plan just touching the spherical end
            Plan planTouchTop({ 0.0f, 1.0f, 0.0f }, 2.0f); // y = 2 (touches sphere at y = 1 + radius)
            CHECK(Collision::checkCollision(capsule, planTouchTop));

            // Plan just missing the spherical end
            Plan planMissTop({ 0.0f, 1.0f, 0.0f }, 2.1f); // y = 2.1
            CHECK_FALSE(Collision::checkCollision(capsule, planMissTop));

            // Plan cutting through cylindrical part
            Plan planCylinder({ 0.0f, 1.0f, 0.0f }, 0.5f); // y = 0.5
            CHECK(Collision::checkCollision(capsule, planCylinder));

            // Multiple plan orientations
            Plan planX({ 1.0f, 0.0f, 0.0f }, 0.8f); // x = 0.8
            CHECK(Collision::checkCollision(capsule, planX));

            Plan planZ({ 0.0f, 0.0f, 1.0f }, 0.8f); // z = 0.8
            CHECK(Collision::checkCollision(capsule, planZ));
        }
    }

    SECTION("Capsule-Sphere Collision")
    {
        SECTION("Basic Capsule-Sphere Collision")
        {
            // Sphere intersecting capsule's cylindrical part
            Capsule capsule({ 0.0f, -2.0f, 0.0f }, { 0.0f, 2.0f, 0.0f }, 1.0f);
            Sphere sphere({ 2.0f, 0.0f, 0.0f }, 1.5f);
            CHECK(Collision::checkCollision(capsule, sphere));

            // Sphere intersecting capsule's spherical end
            Sphere sphereTop({ 0.0f, 4.0f, 0.0f }, 1.5f);
            CHECK(Collision::checkCollision(capsule, sphereTop));

            // Sphere completely inside capsule
            Sphere sphereInside({ 0.0f, 0.0f, 0.0f }, 0.5f);
            CHECK(Collision::checkCollision(capsule, sphereInside));

            // Sphere completely outside capsule
            Sphere sphereOutside({ 5.0f, 5.0f, 5.0f }, 1.0f);
            CHECK_FALSE(Collision::checkCollision(capsule, sphereOutside));

            // Sphere touching capsule externally
            Sphere sphereTouching({ 3.0f, 0.0f, 0.0f }, 2.0f);
            CHECK(Collision::checkCollision(capsule, sphereTouching));
        }

        SECTION("Capsule-Sphere Different Positions")
        {
            // Horizontal capsule
            Capsule capsuleH({ -3.0f, 0.0f, 0.0f }, { 3.0f, 0.0f, 0.0f }, 1.0f);

            // Sphere above cylindrical part
            Sphere sphereAbove({ 0.0f, 2.0f, 0.0f }, 1.2f);
            CHECK(Collision::checkCollision(capsuleH, sphereAbove));

            // Sphere below cylindrical part
            Sphere sphereBelow({ 0.0f, -2.0f, 0.0f }, 1.2f);
            CHECK(Collision::checkCollision(capsuleH, sphereBelow));

            // Sphere at one end of capsule
            Sphere sphereEnd({ -4.0f, 0.0f, 0.0f }, 1.5f);
            CHECK(Collision::checkCollision(capsuleH, sphereEnd));

            // Sphere in front/back of capsule (Z direction)
            Sphere sphereFront({ 0.0f, 0.0f, 2.0f }, 1.2f);
            CHECK(Collision::checkCollision(capsuleH, sphereFront));

            // Sphere far away
            Sphere sphereFar({ 0.0f, 5.0f, 0.0f }, 1.0f);
            CHECK_FALSE(Collision::checkCollision(capsuleH, sphereFar));
        }

        SECTION("Capsule-Sphere Edge Cases")
        {
            // Zero-length capsule (sphere) with sphere
            Capsule sphereCapsule({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 2.0f);
            Sphere sphere({ 3.0f, 0.0f, 0.0f }, 1.5f);
            CHECK(Collision::checkCollision(sphereCapsule, sphere));

            // Very thin capsule with large sphere
            Capsule thinCapsule({ -10.0f, 0.0f, 0.0f }, { 10.0f, 0.0f, 0.0f }, 0.1f);
            Sphere largeSphere({ 0.0f, 0.0f, 0.0f }, 5.0f);
            CHECK(Collision::checkCollision(thinCapsule, largeSphere));

            // Very small sphere with large capsule
            Capsule largeCapsule({ -5.0f, -5.0f, -5.0f }, { 5.0f, 5.0f, 5.0f }, 3.0f);
            Sphere smallSphere({ 0.0f, 0.0f, 0.0f }, 0.1f);
            CHECK(Collision::checkCollision(largeCapsule, smallSphere));

            // Identical sphere and capsule radius, endpoints coinciding
            Capsule capsulePoint({ 2.0f, 2.0f, 2.0f }, { 2.0f, 2.0f, 2.0f }, 1.5f);
            Sphere spherePoint({ 2.0f, 2.0f, 2.0f }, 1.5f);
            CHECK(Collision::checkCollision(capsulePoint, spherePoint));
        }

        SECTION("Capsule-Sphere Precision Cases")
        {
            Capsule capsule({ 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 1.0f);

            // Sphere exactly touching cylindrical surface
            Sphere sphereTouchSide({ 2.0f, 0.0f, 0.0f }, 1.0f);
            CHECK(Collision::checkCollision(capsule, sphereTouchSide));

            // Sphere just inside touching distance
            Sphere sphereJustInside({ 1.9f, 0.0f, 0.0f }, 1.0f);
            CHECK(Collision::checkCollision(capsule, sphereJustInside));

            // Sphere just outside touching distance
            Sphere sphereJustOutside({ 2.1f, 0.0f, 0.0f }, 1.0f);
            CHECK_FALSE(Collision::checkCollision(capsule, sphereJustOutside));

            // Sphere touching spherical end exactly
            Sphere sphereTouchEnd({ 0.0f, 3.0f, 0.0f }, 1.0f);
            CHECK(Collision::checkCollision(capsule, sphereTouchEnd));

            // Sphere just missing spherical end
            Sphere sphereMissEnd({ 0.0f, 3.1f, 0.0f }, 1.0f);
            CHECK_FALSE(Collision::checkCollision(capsule, sphereMissEnd));
        }

        SECTION("Capsule-Sphere 3D Diagonal Cases")
        {
            // Diagonal capsule in 3D
            Capsule capsuleDiag({ -2.0f, -2.0f, -2.0f }, { 2.0f, 2.0f, 2.0f }, 1.0f);

            // Sphere intersecting diagonal capsule
            Sphere sphereDiag({ 0.0f, 0.0f, 3.0f }, 1.5f);
            CHECK(Collision::checkCollision(capsuleDiag, sphereDiag));

            // Sphere parallel to diagonal capsule
            Sphere sphereParallel({ 1.0f, 1.0f, 0.0f }, 1.0f);
            CHECK(Collision::checkCollision(capsuleDiag, sphereParallel));

            // Sphere offset from diagonal capsule
            Sphere sphereOffset({ 3.0f, -1.0f, 1.0f }, 1.0f);
            CHECK_FALSE(Collision::checkCollision(capsuleDiag, sphereOffset));

            // Sphere far from diagonal capsule
            Sphere sphereFarDiag({ 10.0f, -10.0f, 5.0f }, 2.0f);
            CHECK_FALSE(Collision::checkCollision(capsuleDiag, sphereFarDiag));
        }
    }
}

TEST_CASE("Advanced Collision Scenarios", "[.all][Collision3D][advanced]")
{
    SECTION("Multiple Object Interactions")
    {
        Sphere centralSphere({ 0.0f, 0.0f, 0.0f }, 5.0f);

        // Array of points around the sphere
        Point points[] = {
            {3.0f, 0.0f, 0.0f},    // Inside
            {7.0f, 0.0f, 0.0f},    // Outside
            {0.0f, 5.0f, 0.0f},    // On surface
            {3.5f, 3.5f, 0.0f},    // Inside
            {10.0f, 10.0f, 10.0f}  // Far outside
        };

        bool expected[] = { true, false, true, true, false };

        for (int i = 0; i < 5; ++i) {
            CHECK(Collision::checkCollision(centralSphere, points[i]) == expected[i]);
        }
    }

    SECTION("Precision Edge Cases")
    {
        // Very small sphere
        Sphere microSphere({ 0.0f, 0.0f, 0.0f }, 0.001f);
        Point microPoint({ 0.0005f, 0.0f, 0.0f });
        CHECK(Collision::checkCollision(microSphere, microPoint));

        // Very large sphere
        Sphere megaSphere({ 0.0f, 0.0f, 0.0f }, 1000000.0f);
        Point megaPoint({ 500000.0f, 0.0f, 0.0f });
        CHECK(Collision::checkCollision(megaSphere, megaPoint));
    }

    SECTION("Boundary Conditions")
    {
        Sphere sphere({ 0.0f, 0.0f, 0.0f }, 5.0f);

        // Points exactly on the boundary
        Point boundaryPoints[] = {
            {5.0f, 0.0f, 0.0f},
            {0.0f, 5.0f, 0.0f},
            {0.0f, 0.0f, 5.0f},
            {-5.0f, 0.0f, 0.0f},
            {0.0f, -5.0f, 0.0f},
            {0.0f, 0.0f, -5.0f}
        };

        for (const auto& point : boundaryPoints) {
            CHECK(Collision::checkCollision(sphere, point));
        }
    }
}

TEST_CASE("AABB Collisions", "[.all][Collision3D][aabb]")
{
    SECTION("AABB-Line Collision")
    {
        SECTION("Basic AABB-Line Collision")
        {
            // Unit AABB centered at origin
            AABB aabb({ 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f);

            // Line passing through center
            Line lineCenter({ -2.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, 4.0f);
            CHECK(Collision::checkCollision(aabb, lineCenter));

            // Line hitting corner
            Line lineCorner({ -2.0f, -2.0f, -2.0f }, { 1.0f, 1.0f, 1.0f }, 6.0f);
            CHECK(Collision::checkCollision(aabb, lineCorner));

            // Line hitting face
            Line lineFace({ 0.0f, 0.0f, -2.0f }, { 0.0f, 0.0f, 1.0f }, 4.0f);
            CHECK(Collision::checkCollision(aabb, lineFace));

            Line lineTopEdge({ -1.0f, 0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f }, 2.0f);
            CHECK(Collision::checkCollision(aabb, lineTopEdge));

            // Test 2: Ligne qui touche le bord inférieur (Y = -0.5)  
            Line lineBottomEdge({ -1.0f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f }, 2.0f);
            CHECK(Collision::checkCollision(aabb, lineBottomEdge));

            // Test 3: Ligne qui touche le bord droit (X = 0.5)
            Line lineRightEdge({ 0.5f, -1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 2.0f);
            CHECK(Collision::checkCollision(aabb, lineRightEdge));

            // Test 4: Ligne qui touche le bord gauche (X = -0.5)
            Line lineLeftEdge({ -0.5f, -1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 2.0f);
            CHECK(Collision::checkCollision(aabb, lineLeftEdge));

            // Test 5: Ligne qui touche une arête (intersection de deux faces)
            Line lineCornerEdge({ -1.0f, 0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f }, 2.0f);
            CHECK(Collision::checkCollision(aabb, lineCornerEdge));

            // Line missing the AABB
            Line lineMiss({ -2.0f, 2.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, 4.0f);
            CHECK_FALSE(Collision::checkCollision(aabb, lineMiss));
        }

        SECTION("AABB-Line Edge Cases")
        {
            AABB aabb({ 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f);

            // Line starting inside AABB
            Line lineInside({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, 2.0f);
            CHECK(Collision::checkCollision(aabb, lineInside));

            // Line ending exactly at AABB boundary
            Line lineToEdge({ -2.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, 1.5f);
            CHECK(Collision::checkCollision(aabb, lineToEdge));

            // Line too short to reach AABB
            Line lineShort({ -2.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, 0.5f);
            CHECK_FALSE(Collision::checkCollision(aabb, lineShort));

            // Line parallel to AABB face but missing
            Line lineParallelMiss({ -2.0f, 1.1f, 0.0f }, { 1.0f, 0.0f, 0.0f }, 4.0f);
            CHECK_FALSE(Collision::checkCollision(aabb, lineParallelMiss));

            // Line tangent to AABB corner
            Line lineTangent({ -2.0f, 0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f }, 4.0f);
            CHECK(Collision::checkCollision(aabb, lineTangent));
        }

        SECTION("AABB-Line with Different Directions")
        {
            AABB aabb({ 5.0f, 3.0f, -2.0f }, 2.0f, 1.0f, 3.0f);

            // Line in X direction
            Line lineX({ 0.0f, 3.0f, -2.0f }, { 1.0f, 0.0f, 0.0f }, 10.0f);
            CHECK(Collision::checkCollision(aabb, lineX));

            // Line in Y direction
            Line lineY({ 5.0f, 0.0f, -2.0f }, { 0.0f, 1.0f, 0.0f }, 10.0f);
            CHECK(Collision::checkCollision(aabb, lineY));

            // Line in Z direction
            Line lineZ({ 5.0f, 3.0f, -10.0f }, { 0.0f, 0.0f, 1.0f }, 20.0f);
            CHECK(Collision::checkCollision(aabb, lineZ));

            // Diagonal line missing
            Line lineDiagMiss({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, 3.0f);
            CHECK_FALSE(Collision::checkCollision(aabb, lineDiagMiss));
        }

        SECTION("AABB-Line Zero Direction Components")
        {
            AABB aabb({ 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f);

            // Line with zero X component
            Line lineZeroX({ 0.0f, -2.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 4.0f);
            CHECK(Collision::checkCollision(aabb, lineZeroX));

            // Line with zero Y component
            Line lineZeroY({ -2.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, 4.0f);
            CHECK(Collision::checkCollision(aabb, lineZeroY));

            // Line with zero Z component
            Line lineZeroZ({ 0.0f, 0.0f, -2.0f }, { 0.0f, 0.0f, 1.0f }, 4.0f);
            CHECK(Collision::checkCollision(aabb, lineZeroZ));
        }
    }

    SECTION("AABB - AABB")
    {
        SECTION("Basic AABB-AABB Collision")
        {
            // Two unit AABBs at origin (extent = 0.5, so they span from -0.5 to +0.5)
            AABB aabb1({ 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f);
            AABB aabb2({ 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f);
            CHECK(Collision::checkCollision(aabb1, aabb2));

            // Overlapping AABBs
            AABB aabbOverlap({ 0.5f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f);
            CHECK(Collision::checkCollision(aabb1, aabbOverlap));

            // Touching AABBs (sharing a face) - aabb1 spans [-0.5,0.5], aabbTouching spans [0.5,1.5]
            AABB aabbTouching({ 1.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f);
            CHECK(Collision::checkCollision(aabb1, aabbTouching));

            // Separated AABBs - gap between them
            AABB aabbSeparated({ 1.5f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f);
            CHECK_FALSE(Collision::checkCollision(aabb1, aabbSeparated));
        }

        SECTION("AABB-AABB Different Sizes")
        {
            // Small AABB inside large AABB (large: extent=2.5, small: extent=0.5)
            AABB aabbLarge({ 0.0f, 0.0f, 0.0f }, 5.0f, 5.0f, 5.0f);
            AABB aabbSmall({ 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f);
            CHECK(Collision::checkCollision(aabbLarge, aabbSmall));

            // Large AABB partially overlapping small AABB
            // Large spans [-2.5,2.5], small at x=2.0 spans [1.5,2.5] - they overlap
            AABB aabbSmallOffset({ 2.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f);
            CHECK(Collision::checkCollision(aabbLarge, aabbSmallOffset));

            // Large AABB not overlapping small AABB
            // Large spans [-2.5,2.5], small at x=3.0 spans [2.5,3.5] - just touching
            AABB aabbSmallTouching({ 3.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f);
            CHECK(Collision::checkCollision(aabbLarge, aabbSmallTouching));

            // Large AABB truly not overlapping small AABB
            AABB aabbSmallFar({ 4.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f);
            CHECK_FALSE(Collision::checkCollision(aabbLarge, aabbSmallFar));
        }

        SECTION("AABB-AABB Edge Cases")
        {
            AABB aabb1({ 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f);

            // AABBs touching at corner - aabb1 spans [-0.5,0.5], aabbCorner spans [0.5,1.5]
            AABB aabbCorner({ 1.0f, 1.0f, 1.0f }, 1.0f, 1.0f, 1.0f);
            CHECK(Collision::checkCollision(aabb1, aabbCorner));

            // AABBs touching at edge
            AABB aabbEdge({ 1.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f);
            CHECK(Collision::checkCollision(aabb1, aabbEdge));

            // AABBs almost touching (very small gap)
            AABB aabbAlmost({ 1.01f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f);
            CHECK_FALSE(Collision::checkCollision(aabb1, aabbAlmost));

            // AABBs with different aspect ratios
            AABB aabbThin({ 0.0f, 0.0f, 0.0f }, 0.1f, 5.0f, 0.1f);
            AABB aabbFlat({ 0.0f, 0.0f, 0.0f }, 5.0f, 0.1f, 5.0f);
            CHECK(Collision::checkCollision(aabbThin, aabbFlat));
        }

        SECTION("AABB-AABB 3D Positioning")
        {
            // AABBs overlapping only in XY plane
            // aabb1 spans [-0.5,0.5] in Z, aabb2 at z=1.5 spans [1.0,2.0] in Z - no overlap in Z
            AABB aabb1({ 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f);
            AABB aabb2({ 0.5f, 0.5f, 1.5f }, 1.0f, 1.0f, 1.0f);
            CHECK_FALSE(Collision::checkCollision(aabb1, aabb2));

            // AABBs overlapping in all three dimensions
            AABB aabb3({ 0.5f, 0.5f, 0.5f }, 1.0f, 1.0f, 1.0f);
            CHECK(Collision::checkCollision(aabb1, aabb3));

            // AABBs in opposite corners of 3D space
            AABB aabbNeg({ -5.0f, -5.0f, -5.0f }, 1.0f, 1.0f, 1.0f);
            AABB aabbPos({ 5.0f, 5.0f, 5.0f }, 1.0f, 1.0f, 1.0f);
            CHECK_FALSE(Collision::checkCollision(aabbNeg, aabbPos));

            // Very large AABBs that should overlap despite distance
            // Large1 at (-2,-2,-2) with extent=5 spans [-7,3] in each axis
            // Large2 at (2,2,2) with extent=5 spans [-3,7] in each axis - they overlap
            AABB aabbLarge1({ -2.0f, -2.0f, -2.0f }, 10.0f, 10.0f, 10.0f);
            AABB aabbLarge2({ 2.0f, 2.0f, 2.0f }, 10.0f, 10.0f, 10.0f);
            CHECK(Collision::checkCollision(aabbLarge1, aabbLarge2));
        }

        SECTION("AABB-AABB Symmetry Test")
        {
            // Test that collision detection is symmetric
            AABB aabb1({ 1.0f, 2.0f, 3.0f }, 1.5f, 2.5f, 0.5f);
            AABB aabb2({ 2.0f, 1.0f, 3.2f }, 2.0f, 1.0f, 1.0f);
            bool result1 = Collision::checkCollision(aabb1, aabb2);
            bool result2 = Collision::checkCollision(aabb2, aabb1);
            CHECK(result1 == result2);

            // Another symmetry test with non-overlapping AABBs
            // aabb3 spans [-0.5,0.5], aabb4 at (2.5,2.5,2.5) spans [2.0,3.0] - no overlap
            AABB aabb3({ 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f);
            AABB aabb4({ 2.5f, 2.5f, 2.5f }, 1.0f, 1.0f, 1.0f);
            bool result3 = Collision::checkCollision(aabb3, aabb4);
            bool result4 = Collision::checkCollision(aabb4, aabb3);
            CHECK(result3 == result4);
            CHECK_FALSE(result3); // Should be false since they don't overlap
        }
    }

    //SECTION("AABB-Point")
    //{
    //    SECTION("Basic AABB-Point Collision")
    //    {
    //        // Unit AABB centered at origin (spans from -0.5 to +0.5 in each axis)
    //        AABB aabb({ 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f);

    //        // Point at center
    //        Point pointCenter({ 0.0f, 0.0f, 0.0f });
    //        CHECK(Collision::checkCollision(aabb, pointCenter));

    //        // Point inside AABB
    //        Point pointInside({ 0.25f, -0.25f, 0.3f });
    //        CHECK(Collision::checkCollision(aabb, pointInside));

    //        // Point on the surface (face center)
    //        Point pointOnFace({ 0.5f, 0.0f, 0.0f });
    //        CHECK(Collision::checkCollision(aabb, pointOnFace));

    //        // Point on edge
    //        Point pointOnEdge({ 0.5f, 0.5f, 0.0f });
    //        CHECK(Collision::checkCollision(aabb, pointOnEdge));

    //        // Point on corner
    //        Point pointOnCorner({ 0.5f, 0.5f, 0.5f });
    //        CHECK(Collision::checkCollision(aabb, pointOnCorner));

    //        // Point outside AABB
    //        Point pointOutside({ 1.0f, 0.0f, 0.0f });
    //        CHECK_FALSE(Collision::checkCollision(aabb, pointOutside));

    //        // Point clearly outside
    //        Point pointFarOutside({ 5.0f, 5.0f, 5.0f });
    //        CHECK_FALSE(Collision::checkCollision(aabb, pointFarOutside));
    //    }

    //    SECTION("AABB-Point Edge Cases")
    //    {
    //        AABB aabb({ 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f);

    //        // Points exactly on each face
    //        Point pointRightFace({ 0.5f, 0.0f, 0.0f });
    //        CHECK(Collision::checkCollision(aabb, pointRightFace));

    //        Point pointLeftFace({ -0.5f, 0.0f, 0.0f });
    //        CHECK(Collision::checkCollision(aabb, pointLeftFace));

    //        Point pointTopFace({ 0.0f, 0.5f, 0.0f });
    //        CHECK(Collision::checkCollision(aabb, pointTopFace));

    //        Point pointBottomFace({ 0.0f, -0.5f, 0.0f });
    //        CHECK(Collision::checkCollision(aabb, pointBottomFace));

    //        Point pointFrontFace({ 0.0f, 0.0f, 0.5f });
    //        CHECK(Collision::checkCollision(aabb, pointFrontFace));

    //        Point pointBackFace({ 0.0f, 0.0f, -0.5f });
    //        CHECK(Collision::checkCollision(aabb, pointBackFace));

    //        // Points just outside each face
    //        Point pointJustOutsideRight({ 0.51f, 0.0f, 0.0f });
    //        CHECK_FALSE(Collision::checkCollision(aabb, pointJustOutsideRight));

    //        Point pointJustOutsideLeft({ -0.51f, 0.0f, 0.0f });
    //        CHECK_FALSE(Collision::checkCollision(aabb, pointJustOutsideLeft));

    //        Point pointJustOutsideTop({ 0.0f, 0.51f, 0.0f });
    //        CHECK_FALSE(Collision::checkCollision(aabb, pointJustOutsideTop));
    //    }

    //    SECTION("AABB-Point with Different AABB Sizes")
    //    {
    //        // Large AABB
    //        AABB aabbLarge({ 0.0f, 0.0f, 0.0f }, 10.0f, 10.0f, 10.0f);
    //        Point pointInLarge({ 3.0f, -3.0f, 4.0f });
    //        CHECK(Collision::checkCollision(aabbLarge, pointInLarge));

    //        Point pointOnLargeBoundary({ 5.0f, 0.0f, 0.0f });
    //        CHECK(Collision::checkCollision(aabbLarge, pointOnLargeBoundary));

    //        Point pointOutsideLarge({ 6.0f, 0.0f, 0.0f });
    //        CHECK_FALSE(Collision::checkCollision(aabbLarge, pointOutsideLarge));

    //        // Small AABB
    //        AABB aabbSmall({ 0.0f, 0.0f, 0.0f }, 0.2f, 0.2f, 0.2f);
    //        Point pointInSmall({ 0.05f, -0.05f, 0.08f });
    //        CHECK(Collision::checkCollision(aabbSmall, pointInSmall));

    //        Point pointOutsideSmall({ 0.15f, 0.0f, 0.0f });
    //        CHECK_FALSE(Collision::checkCollision(aabbSmall, pointOutsideSmall));
    //    }

    //    SECTION("AABB-Point with Non-Centered AABB")
    //    {
    //        // AABB not centered at origin
    //        AABB aabbOffset({ 5.0f, -3.0f, 2.0f }, 2.0f, 4.0f, 1.0f);
    //        // This AABB spans: X[4,6], Y[-5,-1], Z[1.5,2.5]

    //        // Point inside offset AABB
    //        Point pointInsideOffset({ 5.5f, -2.0f, 2.0f });
    //        CHECK(Collision::checkCollision(aabbOffset, pointInsideOffset));

    //        // Point on boundary of offset AABB
    //        Point pointOnOffsetBoundary({ 6.0f, -3.0f, 1.5f });
    //        CHECK(Collision::checkCollision(aabbOffset, pointOnOffsetBoundary));

    //        // Point outside offset AABB
    //        Point pointOutsideOffset({ 7.0f, -2.0f, 2.0f });
    //        CHECK_FALSE(Collision::checkCollision(aabbOffset, pointOutsideOffset));

    //        Point pointOutsideOffsetY({ 5.0f, 0.0f, 2.0f });
    //        CHECK_FALSE(Collision::checkCollision(aabbOffset, pointOutsideOffsetY));
    //    }

    //    SECTION("AABB-Point Precision Cases")
    //    {
    //        // Very small AABB
    //        AABB aabbMicro({ 0.0f, 0.0f, 0.0f }, 0.001f, 0.001f, 0.001f);
    //        Point pointInMicro({ 0.0002f, 0.0f, 0.0f });
    //        CHECK(Collision::checkCollision(aabbMicro, pointInMicro));

    //        Point pointOutMicro({ 0.001f, 0.0f, 0.0f });
    //        CHECK_FALSE(Collision::checkCollision(aabbMicro, pointOutMicro));

    //        // Very large AABB
    //        AABB aabbMega({ 0.0f, 0.0f, 0.0f }, 1000000.0f, 1000000.0f, 1000000.0f);
    //        Point pointInMega({ 400000.0f, -300000.0f, 200000.0f });
    //        CHECK(Collision::checkCollision(aabbMega, pointInMega));
    //    }

    //}

    //SECTION("AABB-Sphere")
    //{
    //    SECTION("Basic AABB-Sphere Collision")
    //    {
    //        // Unit AABB centered at origin (spans from -0.5 to +0.5 in each axis)
    //        AABB aabb({ 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f);

    //        // Sphere centered at origin, smaller than AABB
    //        Sphere sphereInside({ 0.0f, 0.0f, 0.0f }, 0.3f);
    //        CHECK(Collision::checkCollision(aabb, sphereInside));

    //        // Sphere centered at origin, larger than AABB (encompasses it)
    //        Sphere sphereEncompassing({ 0.0f, 0.0f, 0.0f }, 2.0f);
    //        CHECK(Collision::checkCollision(aabb, sphereEncompassing));

    //        // Sphere intersecting AABB from outside
    //        Sphere sphereIntersecting({ 1.0f, 0.0f, 0.0f }, 0.8f);
    //        CHECK(Collision::checkCollision(aabb, sphereIntersecting));

    //        // Sphere touching AABB externally
    //        Sphere sphereTouching({ 1.0f, 0.0f, 0.0f }, 0.5f);
    //        CHECK(Collision::checkCollision(aabb, sphereTouching));

    //        // Sphere completely outside AABB
    //        Sphere sphereOutside({ 2.0f, 0.0f, 0.0f }, 0.5f);
    //        CHECK_FALSE(Collision::checkCollision(aabb, sphereOutside));

    //        // Sphere far outside AABB
    //        Sphere sphereFarOutside({ 10.0f, 10.0f, 10.0f }, 1.0f);
    //        CHECK_FALSE(Collision::checkCollision(aabb, sphereFarOutside));
    //    }

    //    SECTION("AABB-Sphere Edge Cases")
    //    {
    //        AABB aabb({ 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f);

    //        // Sphere touching each face of AABB
    //        Sphere sphereTouchingRight({ 1.0f, 0.0f, 0.0f }, 0.5f);
    //        CHECK(Collision::checkCollision(aabb, sphereTouchingRight));

    //        Sphere sphereTouchingLeft({ -1.0f, 0.0f, 0.0f }, 0.5f);
    //        CHECK(Collision::checkCollision(aabb, sphereTouchingLeft));

    //        Sphere sphereTouchingTop({ 0.0f, 1.0f, 0.0f }, 0.5f);
    //        CHECK(Collision::checkCollision(aabb, sphereTouchingTop));

    //        Sphere sphereTouchingBottom({ 0.0f, -1.0f, 0.0f }, 0.5f);
    //        CHECK(Collision::checkCollision(aabb, sphereTouchingBottom));

    //        // Sphere just barely touching corner
    //        Sphere sphereTouchingCorner({ 1.0f, 1.0f, 1.0f }, std::sqrt(3.0f) * 0.5f);
    //        CHECK(Collision::checkCollision(aabb, sphereTouchingCorner));

    //        // Sphere just missing corner
    //        Sphere sphereMissingCorner({ 1.0f, 1.0f, 1.0f }, std::sqrt(3.0f) * 0.5f - 0.01f);
    //        CHECK_FALSE(Collision::checkCollision(aabb, sphereMissingCorner));

    //        // Very small sphere on AABB edge
    //        Sphere sphereSmallOnEdge({ 0.5f, 0.5f, 0.0f }, 0.01f);
    //        CHECK(Collision::checkCollision(aabb, sphereSmallOnEdge));
    //    }

    //    SECTION("AABB-Sphere with Different Sizes")
    //    {
    //        // Large AABB with various sphere sizes
    //        AABB aabbLarge({ 0.0f, 0.0f, 0.0f }, 10.0f, 10.0f, 10.0f);

    //        // Small sphere inside large AABB
    //        Sphere sphereSmallInside({ 2.0f, -2.0f, 3.0f }, 1.0f);
    //        CHECK(Collision::checkCollision(aabbLarge, sphereSmallInside));

    //        // Medium sphere intersecting large AABB boundary
    //        Sphere sphereMediumIntersecting({ 6.0f, 0.0f, 0.0f }, 2.0f);
    //        CHECK(Collision::checkCollision(aabbLarge, sphereMediumIntersecting));

    //        // Large sphere encompassing large AABB
    //        Sphere sphereLargeEncompassing({ 0.0f, 0.0f, 0.0f }, 15.0f);
    //        CHECK(Collision::checkCollision(aabbLarge, sphereLargeEncompassing));

    //        // Small AABB with various sphere sizes
    //        AABB aabbSmall({ 0.0f, 0.0f, 0.0f }, 0.5f, 0.5f, 0.5f);

    //        // Tiny sphere inside small AABB
    //        Sphere sphereTinyInside({ 0.1f, 0.1f, 0.1f }, 0.1f);
    //        CHECK(Collision::checkCollision(aabbSmall, sphereTinyInside));

    //        // Large sphere encompassing small AABB
    //        Sphere sphereLargeWithSmallAABB({ 0.0f, 0.0f, 0.0f }, 2.0f);
    //        CHECK(Collision::checkCollision(aabbSmall, sphereLargeWithSmallAABB));
    //    }

    //    SECTION("AABB-Sphere with Non-Centered Positions")
    //    {
    //        // Offset AABB
    //        AABB aabbOffset({ 5.0f, -3.0f, 2.0f }, 2.0f, 4.0f, 1.0f);
    //        // This AABB spans: X[4,6], Y[-5,-1], Z[1.5,2.5]

    //        // Sphere inside offset AABB
    //        Sphere sphereInsideOffset({ 5.0f, -3.0f, 2.0f }, 0.8f);
    //        CHECK(Collision::checkCollision(aabbOffset, sphereInsideOffset));

    //        // Sphere intersecting offset AABB from side
    //        Sphere sphereIntersectingOffset({ 7.0f, -3.0f, 2.0f }, 1.5f);
    //        CHECK(Collision::checkCollision(aabbOffset, sphereIntersectingOffset));

    //        // Sphere touching offset AABB corner
    //        Sphere sphereTouchingOffsetCorner({ 7.0f, 0.0f, 3.0f }, std::sqrt(3.0f));
    //        CHECK(Collision::checkCollision(aabbOffset, sphereTouchingOffsetCorner));

    //        // Sphere outside offset AABB
    //        Sphere sphereOutsideOffset({ 10.0f, -3.0f, 2.0f }, 1.0f);
    //        CHECK_FALSE(Collision::checkCollision(aabbOffset, sphereOutsideOffset));
    //    }

    //    SECTION("AABB-Sphere Corner and Edge Cases")
    //    {
    //        AABB aabb({ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f);

    //        // Sphere at each corner of AABB
    //        float cornerDistance = std::sqrt(3.0f); // Distance from center to corner

    //        // Sphere touching corner from outside
    //        Sphere sphereCorner1({ cornerDistance + 0.5f, cornerDistance + 0.5f, cornerDistance + 0.5f }, 0.5f);
    //        CHECK(Collision::checkCollision(aabb, sphereCorner1));

    //        // Sphere just missing corner
    //        Sphere sphereMissCorner({ cornerDistance + 1.0f, cornerDistance + 1.0f, cornerDistance + 1.0f }, 0.5f);
    //        CHECK_FALSE(Collision::checkCollision(aabb, sphereMissCorner));

    //        // Sphere intersecting edge
    //        Sphere sphereEdge({ 1.5f, 1.0f, 0.0f }, 0.8f);
    //        CHECK(Collision::checkCollision(aabb, sphereEdge));

    //        // Sphere touching face center
    //        Sphere sphereFaceCenter({ 1.5f, 0.0f, 0.0f }, 0.5f);
    //        CHECK(Collision::checkCollision(aabb, sphereFaceCenter));
    //    }

    //    SECTION("AABB-Sphere Precision Cases")
    //    {
    //        // Very small AABB and sphere
    //        AABB aabbMicro({ 0.0f, 0.0f, 0.0f }, 0.002f, 0.002f, 0.002f);
    //        Sphere sphereMicro({ 0.0f, 0.0f, 0.0f }, 0.0005f);
    //        CHECK(Collision::checkCollision(aabbMicro, sphereMicro));

    //        // Very large AABB and sphere
    //        AABB aabbMega({ 0.0f, 0.0f, 0.0f }, 1000000.0f, 1000000.0f, 1000000.0f);
    //        Sphere sphereMega({ 800000.0f, 0.0f, 0.0f }, 300000.0f);
    //        CHECK(Collision::checkCollision(aabbMega, sphereMega));

    //        // Floating point precision edge case
    //        AABB aabbPrecision({ 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f);
    //        Sphere spherePrecision({ 1.0000001f, 0.0f, 0.0f }, 0.5f);
    //        CHECK(Collision::checkCollision(aabbPrecision, spherePrecision));
    //    }

    //    SECTION("AABB-Sphere Asymmetric AABB")
    //    {
    //        // AABB with different dimensions in each axis
    //        AABB aabbAsymmetric({ 0.0f, 0.0f, 0.0f }, 4.0f, 1.0f, 2.0f);
    //        // Spans: X[-2,2], Y[-0.5,0.5], Z[-1,1]

    //        // Sphere intersecting along longest axis
    //        Sphere sphereLongAxis({ 3.0f, 0.0f, 0.0f }, 1.5f);
    //        CHECK(Collision::checkCollision(aabbAsymmetric, sphereLongAxis));

    //        // Sphere intersecting along shortest axis
    //        Sphere sphereShortAxis({ 0.0f, 1.0f, 0.0f }, 0.8f);
    //        CHECK(Collision::checkCollision(aabbAsymmetric, sphereShortAxis));

    //        // Sphere missing due to asymmetry
    //        Sphere sphereMissAsymmetric({ 0.0f, 2.0f, 0.0f }, 1.0f);
    //        CHECK_FALSE(Collision::checkCollision(aabbAsymmetric, sphereMissAsymmetric));

    //        // Sphere encompassing asymmetric AABB
    //        Sphere sphereEncompassAsymmetric({ 0.0f, 0.0f, 0.0f }, 5.0f);
    //        CHECK(Collision::checkCollision(aabbAsymmetric, sphereEncompassAsymmetric));
    //    }
    //}
}
