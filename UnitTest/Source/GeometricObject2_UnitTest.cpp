#define	_USE_MATH_DEFINES
#include <cmath>
#include "LibMath/GeometricObject2.h"
#include "LibMath/Collisions.h"


#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>


TEST_CASE("Point", "[.all][geometricObject]")
{
	SECTION("Instantiation")
	{
		//destructor
		{
			LibMath::Geometry2D::Point point;
		}

		//default constructor
		LibMath::Geometry2D::Point p;
		CHECK(p.m_x == 0.0f);
		CHECK(p.m_y == 0.0f);

		// basic constructor
		float x = 60.f;
		float y = 15.f;

		LibMath::Geometry2D::Point a{ x, y };
		CHECK(a.m_x == 60.f);
		CHECK(a.m_y == 15.f);

		// copy constructor
		LibMath::Geometry2D::Point b{ a };
		CHECK(b.m_x == 60.f);
		CHECK(b.m_y == 15.f);

		// assignment operator
		p = a;
		CHECK(p.m_x == x);
		CHECK(p.m_y == y);


		CHECK(sizeof LibMath::Geometry2D::Point == 2 * sizeof(float));

	}

	SECTION("Comparator")
	{
		// compare with self
		LibMath::Geometry2D::Point self{ 60.f, 20.f };
		CHECK(self == self);

		// compare with same
		CHECK(LibMath::Geometry2D::Point{ 60.f, 50.f } == LibMath::Geometry2D::Point{ 60.f, 50.f });

		// compare with different
		CHECK_FALSE(LibMath::Geometry2D::Point{ 90.f, 100.f } == LibMath::Geometry2D::Point(450.f, 100.f));
		CHECK_FALSE(LibMath::Geometry2D::Point{ 10.f, 20.f } == LibMath::Geometry2D::Point{ 10.f, 20.1f });

	}
}

TEST_CASE("Line", "[.all][geometricObject]")
{
	SECTION("Instantiation") 
	{
		// Destructor
		{
			LibMath::Geometry2D::Line temp;
		}

		// Default constructor
		LibMath::Geometry2D::Line lineDefault;
		CHECK(lineDefault.m_p1 == LibMath::Geometry2D::Point());
		CHECK(lineDefault.m_p2 == LibMath::Geometry2D::Point());

		// Parameterized constructor
		LibMath::Geometry2D::Point p1(0.0f, 0.0f);
		LibMath::Geometry2D::Point p2(3.0f, 4.0f);
		LibMath::Geometry2D::Line lineParam(p1, p2);
		CHECK(lineParam.m_p1 == p1);
		CHECK(lineParam.m_p2 == p2);

		// Copy constructor
		LibMath::Geometry2D::Line lineCopy(lineParam);
		CHECK(lineCopy.m_p1 == p1);
		CHECK(lineCopy.m_p2 == p2);

		// Assignment operator
		LibMath::Geometry2D::Line lineAssign;
		lineAssign = lineParam;
		CHECK(lineAssign.m_p1 == p1);
		CHECK(lineAssign.m_p2 == p2);
	}

	SECTION("Accessor")
	{
		float x = 60.f;
		float y = 15.f;
		LibMath::Geometry2D::Point p1(x, y);
		LibMath::Geometry2D::Point p2(x + 10, y - 5);

		LibMath::Geometry2D::Line line{ p1, p2 };

		{
			LibMath::Geometry2D::Line& line2 = line;
			CHECK(line2.m_p1 == p1);
		}

	}

	SECTION("Comparison") 
	{
		LibMath::Geometry2D::Point p1(0.0f, 0.0f);
		LibMath::Geometry2D::Point p2(3.0f, 4.0f);

		LibMath::Geometry2D::Line line1(p1, p2);
		LibMath::Geometry2D::Line line2(p1, p2);
		LibMath::Geometry2D::Line line3(p2, LibMath::Geometry2D::Point(6.0f, 8.0f));

		CHECK(line1 == line2);
		CHECK_FALSE(line1 == line3);
	}

	SECTION("Length and LengthSquared") 
	{
		LibMath::Geometry2D::Point p1(0.0f, 0.0f);
		LibMath::Geometry2D::Point p2(3.0f, 4.0f);
		LibMath::Geometry2D::Line line(p1, p2);

		CHECK(line.lenght() == Catch::Approx(5.0f));
		CHECK(line.lenghtSquare() == Catch::Approx(25.0f));
	}
}

TEST_CASE("RectangleAABB", "[.all][geometricObject]") 
{

	SECTION("Instantiation") 
	{
		// Default constructor
		LibMath::Geometry2D::AABB rectDefault;
		CHECK(rectDefault.m_center == LibMath::Geometry2D::Point()); // Default center (0, 0)
		CHECK(rectDefault.extentX() == 0.0f);   // Default width
		CHECK(rectDefault.extentY() == 0.0f);   // Default height

		// Parameterized constructor
		LibMath::Geometry2D::Point center(2.0f, 3.0f);
		float height = 4.0f;
		float width = 6.0f;
		LibMath::Geometry2D::AABB rectParam(center, height, width);
		CHECK(rectParam.m_center == center);
		CHECK(rectParam.extentX() == width / 2.0f); // Half-width
		CHECK(rectParam.extentY() == height / 2.0f); // Half-height

		// Copy constructor
		LibMath::Geometry2D::AABB rectCopy(rectParam);
		CHECK(rectCopy.m_center == center);
		CHECK(rectCopy.extentX() == width / 2.0f);
		CHECK(rectCopy.extentY() == height / 2.0f);

		// Assignment operator
		LibMath::Geometry2D::AABB rectAssign;
		rectAssign = rectParam;
		CHECK(rectAssign.m_center == center);
		CHECK(rectAssign.extentX() == width / 2.0f);
		CHECK(rectAssign.extentY() == height / 2.0f);
	}

	SECTION("Corner Calculations") 
	{
		LibMath::Geometry2D::Point center(2.0f, 3.0f);
		float height = 4.0f;
		float width = 6.0f;
		LibMath::Geometry2D::AABB rect(center, height, width);

		CHECK(rect.getTopRightCorner() == LibMath::Geometry2D::Point(5.0f, 5.0f));
		CHECK(rect.getTopLeftCorner() == LibMath::Geometry2D::Point(-1.0f, 5.0f));
		CHECK(rect.getBottomRightCorner() == LibMath::Geometry2D::Point(5.0f, 1.0f));
		CHECK(rect.getBottomLeftCorner() == LibMath::Geometry2D::Point(-1.0f, 1.0f));
	}
}

TEST_CASE("RectangleOBB", "[.all][geometricObject]") 
{
	SECTION("Instantiation") 
	{
		// Default constructor
		LibMath::Geometry2D::OBB rectDefault;
		CHECK(rectDefault.m_center == LibMath::Geometry2D::Point());
		CHECK(rectDefault.m_height == 0.0f);
		CHECK(rectDefault.m_width == 0.0f);
		CHECK(rectDefault.m_rotation.raw() == 0.0f); // Default rotation is 0 radians

		// Parameterized constructor
		LibMath::Geometry2D::Point center(2.0f, 3.0f);
		float height = 4.0f;
		float width = 6.0f;
		LibMath::Geometry2D::OBB rectParam(center, height, width);
		CHECK(rectParam.m_center == center);
		CHECK(rectParam.m_height == height);
		CHECK(rectParam.m_width == width);
		CHECK(rectParam.m_rotation.raw() == 0.0f);

		// Copy constructor
		LibMath::Geometry2D::OBB rectCopy(rectParam);
		CHECK(rectCopy.m_center == center);
		CHECK(rectCopy.m_height == height);
		CHECK(rectCopy.m_width == width);
		CHECK(rectCopy.m_rotation.raw() == 0.0f);

		// Assignment operator
		LibMath::Geometry2D::OBB rectAssign;
		rectAssign = rectParam;
		CHECK(rectAssign.m_center == center);
		CHECK(rectAssign.m_height == height);
		CHECK(rectAssign.m_width == width);
		CHECK(rectAssign.m_rotation == rectParam.m_rotation);
	}

	SECTION("Corners with Rotation") 
	{
		LibMath::Geometry2D::Point center(0.0f, 0.0f);
		float height = 4.0f;
		float width = 6.0f;
		LibMath::Geometry2D::OBB rect(center, height, width);

		// No rotation
		CHECK(rect.getTopRightCorner() == LibMath::Geometry2D::Point(3.0f, 2.0f));
		CHECK(rect.getTopLeftCorner() == LibMath::Geometry2D::Point(-3.0f, 2.0f));
		CHECK(rect.getBotRightCorner() == LibMath::Geometry2D::Point(3.0f, -2.0f));
		CHECK(rect.getBotLeftCorner() == LibMath::Geometry2D::Point(-3.0f, -2.0f));

		// Rotate 90 degrees (π/2 radians)
		rect.rotate(LibMath::Radian( static_cast<float>(M_PI) / 2));
		CHECK(rect.getTopRightCorner() == LibMath::Geometry2D::Point(-2.0f, 3.0f));
		CHECK(rect.getTopLeftCorner() == LibMath::Geometry2D::Point(-2.0f, -3.0f));
		CHECK(rect.getBotRightCorner() == LibMath::Geometry2D::Point(2.0f, 3.0f));
		CHECK(rect.getBotLeftCorner() == LibMath::Geometry2D::Point(2.0f, -3.0f));
	}

	SECTION("Normal Vector Calculation") 
	{
		LibMath::Geometry2D::Point p1(0.0f, 0.0f);
		LibMath::Geometry2D::Point p2(4.0f, 0.0f);
		LibMath::Vector2 normal = normalVector(p1, p2);
		CHECK(normal == LibMath::Vector2(0.0f, 1.0f)); // Perpendicular to the edge
	}

}

TEST_CASE("Circle2", "[.all][geometricObject]")
{
	SECTION("Instantiation") 
	{
		// Default constructor
		LibMath::Geometry2D::Circle circleDefault;
		CHECK(circleDefault.m_center == LibMath::Geometry2D::Point()); // Default center is (0, 0)
		CHECK(circleDefault.m_radius == 0.0f);    // Default radius is 0

		// Parameterized constructor
		LibMath::Geometry2D::Point center(2.0f, 3.0f);
		float radius = 5.0f;
		LibMath::Geometry2D::Circle circleParam(center, radius);
		CHECK(circleParam.m_center == center);
		CHECK(circleParam.m_radius == radius);

		// Copy constructor
		LibMath::Geometry2D::Circle circleCopy(circleParam);
		CHECK(circleCopy.m_center == center);
		CHECK(circleCopy.m_radius == radius);

		// Assignment operator
		LibMath::Geometry2D::Circle circleAssign;
		circleAssign = circleParam;
		CHECK(circleAssign.m_center == center);
		CHECK(circleAssign.m_radius == radius);
	}

	SECTION("Perimeter and Area") {
		LibMath::Geometry2D::Point center(0.0f, 0.0f);
		float radius = 5.0f;
		LibMath::Geometry2D::Circle circle(center, radius);

		float expectedPerimeter = 2 * static_cast<float>(M_PI) * radius;
		float expectedArea = static_cast<float>(M_PI) * radius * radius;

		CHECK(circle.perimeter() == Catch::Approx(expectedPerimeter));
		CHECK(circle.area() == Catch::Approx(expectedArea));
	}
}

TEST_CASE("Line2D Collisions", "[.all][Collision2D][Line2D]")
{
	SECTION("Collision with Point")
	{
		LibMath::Geometry2D::Point p1(0.0f, 0.0f);
		LibMath::Geometry2D::Point p2(4.0f, 4.0f);
		LibMath::Geometry2D::Point pointOnLine(2.0f, 2.0f);
		LibMath::Geometry2D::Point pointOffLine(3.0f, 2.0f);

		LibMath::Geometry2D::Line line(p1, p2);

		CHECK(LibMath::Collision2D::checkCollisionLinePoint(line, pointOnLine));
		CHECK_FALSE(LibMath::Collision2D::checkCollisionLinePoint(line, pointOffLine));
	}

	SECTION("Collision with Line")
	{
		{
			LibMath::Geometry2D::Point p1(0.0f, 0.0f);
			LibMath::Geometry2D::Point p2(4.0f, 4.0f);
			LibMath::Geometry2D::Point p3(0.0f, 4.0f);
			LibMath::Geometry2D::Point p4(4.0f, 0.0f);

			LibMath::Geometry2D::Line line1(p1, p2);
			LibMath::Geometry2D::Line line2(p3, p4); // Intersecting line
			LibMath::Geometry2D::Line line3(LibMath::Geometry2D::Point(5.0f, 5.0f), LibMath::Geometry2D::Point(6.0f, 6.0f)); // Non-intersecting line

			CHECK(LibMath::Collision2D::checkCollisionLineLine(line1, line2));
			CHECK_FALSE(LibMath::Collision2D::checkCollisionLineLine(line1, line3));
		}

		{
			LibMath::Geometry2D::Point p1(0.0f, 0.0f);
			LibMath::Geometry2D::Point p2(4.0f, 0.0f);
			LibMath::Geometry2D::Point p3(0.0f, 2.0f);
			LibMath::Geometry2D::Point p4(4.0f, 2.0f);

			LibMath::Geometry2D::Line line1(p1, p2); // Horizontal line at y=0
			LibMath::Geometry2D::Line line2(p3, p4); // Horizontal line at y=2

			CHECK_FALSE(LibMath::Collision2D::checkCollisionLineLine(line1, line2)); // Parallel, no intersection
		}

		{
			LibMath::Geometry2D::Point p1(0.0f, 0.0f);
			LibMath::Geometry2D::Point p2(4.0f, 4.0f);
			LibMath::Geometry2D::Point p3(4.0f, 4.0f);
			LibMath::Geometry2D::Point p4(8.0f, 8.0f);

			LibMath::Geometry2D::Line line1(p1, p2);
			LibMath::Geometry2D::Line line2(p3, p4);

			CHECK(LibMath::Collision2D::checkCollisionLineLine(line1, line2)); // Lines touch at (4, 4)
		}

		{
			LibMath::Geometry2D::Point p1(0.0f, 0.0f);
			LibMath::Geometry2D::Point p2(4.0f, 4.0f);
			LibMath::Geometry2D::Point p3(0.0f, 4.0f);
			LibMath::Geometry2D::Point p4(4.0f, 0.0f);

			LibMath::Geometry2D::Line line1(p1, p2);
			LibMath::Geometry2D::Line line2(p3, p4);

			CHECK(LibMath::Collision2D::checkCollisionLineLine(line1, line2)); // Intersect at (2, 2)
		}

		{
			LibMath::Geometry2D::Point p1(0.0f, 0.0f);
			LibMath::Geometry2D::Point p2(2.0f, 2.0f);
			LibMath::Geometry2D::Point p3(3.0f, 0.0f);
			LibMath::Geometry2D::Point p4(5.0f, 2.0f);

			LibMath::Geometry2D::Line line1(p1, p2);
			LibMath::Geometry2D::Line line2(p3, p4);

			CHECK_FALSE(LibMath::Collision2D::checkCollisionLineLine(line1, line2)); // Skew lines do not intersect
		}
	}
}

TEST_CASE("AABB2D Collisions", "[.all][Collision2D][AABB2D]")
{
	SECTION("Collision with RectangleAABB")
	{
		// Non-overlapping rectangles
		LibMath::Geometry2D::AABB rect1(LibMath::Geometry2D::Point(0.0f, 0.0f), 4.0f, 4.0f);
		LibMath::Geometry2D::AABB rect2(LibMath::Geometry2D::Point(10.0f, 10.0f), 4.0f, 4.0f);
		CHECK_FALSE(LibMath::Collision2D::checkCollisionAABBAABB(rect1, rect2));

		// Overlapping rectangles
		LibMath::Geometry2D::AABB rect3(LibMath::Geometry2D::Point(2.0f, 2.0f), 4.0f, 4.0f);
		CHECK(LibMath::Collision2D::checkCollisionAABBAABB(rect1, rect3));

		// Touching rectangles (edges touch)
		LibMath::Geometry2D::AABB rect4(LibMath::Geometry2D::Point(4.0f, 0.0f), 4.0f, 4.0f);
		CHECK(LibMath::Collision2D::checkCollisionAABBAABB(rect1, rect4));
	}

	SECTION("Collision with Line2")
	{
		LibMath::Geometry2D::AABB rect(LibMath::Geometry2D::Point(0.0f, 0.0f), 4.0f, 4.0f);

		// Line inside the rectangle
		LibMath::Geometry2D::Line line1(LibMath::Geometry2D::Point(-1.0f, 0.0f), LibMath::Geometry2D::Point(1.0f, 0.0f));
		CHECK(LibMath::Collision2D::checkCollisionAABBLine(rect, line1));

		// Line intersecting the rectangle
		LibMath::Geometry2D::Line line2(LibMath::Geometry2D::Point(-3.0f, 0.0f), LibMath::Geometry2D::Point(3.0f, 0.0f));
		CHECK(LibMath::Collision2D::checkCollisionAABBLine(rect, line2));

		// Line outside the rectangle
		LibMath::Geometry2D::Line line3(LibMath::Geometry2D::Point(5.0f, 5.0f), LibMath::Geometry2D::Point(6.0f, 6.0f));
		CHECK_FALSE(LibMath::Collision2D::checkCollisionAABBLine(rect, line3));
	}

	SECTION("Collision with Point2")
	{
		LibMath::Geometry2D::AABB rect(LibMath::Geometry2D::Point(0.0f, 0.0f), 4.0f, 4.0f);

		// Point inside the rectangle
		LibMath::Geometry2D::Point point1(1.0f, 1.0f);
		CHECK(LibMath::Collision2D::checkCollisionAABBPoint(rect, point1));

		// Point on the edge of the rectangle
		LibMath::Geometry2D::Point point2(2.0f, 0.0f);
		CHECK(LibMath::Collision2D::checkCollisionAABBPoint(rect, point2));

		// Point outside the rectangle
		LibMath::Geometry2D::Point point3(5.0f, 5.0f);
		CHECK_FALSE(LibMath::Collision2D::checkCollisionAABBPoint(rect, point3));
	}

	SECTION("Edge Cases")
	{
		// Rectangle with zero width and height
		LibMath::Geometry2D::AABB rectZero(LibMath::Geometry2D::Point(0.0f, 0.0f), 0.0f, 0.0f);
		LibMath::Geometry2D::Point pointZero(0.0f, 0.0f);
		CHECK(LibMath::Collision2D::checkCollisionAABBPoint(rectZero, pointZero)); // Point exactly at the center

		LibMath::Geometry2D::Line lineZero(LibMath::Geometry2D::Point(-1.0f, 0.0f), LibMath::Geometry2D::Point(1.0f, 0.0f));
		CHECK(LibMath::Collision2D::checkCollisionAABBLine(rectZero, lineZero)); // Line outside a zero-size rectangle
	}
}

TEST_CASE("OBB2D Collisions", "[.all][Collision2D][OBB2D]")
{
	SECTION("Collision Detection with RectangleOBB")
	{
		// Non-overlapping rectangles
		LibMath::Geometry2D::OBB rect1(LibMath::Geometry2D::Point(0.0f, 0.0f), 4.0f, 4.0f);
		LibMath::Geometry2D::OBB rect2(LibMath::Geometry2D::Point(10.0f, 10.0f), 4.0f, 4.0f);
		CHECK_FALSE(LibMath::Collision2D::checkCollisionOBBOBB(rect1, rect2));

		// Overlapping rectangles (no rotation)
		LibMath::Geometry2D::OBB rect3(LibMath::Geometry2D::Point(2.0f, 2.0f), 4.0f, 4.0f);
		CHECK(LibMath::Collision2D::checkCollisionOBBOBB(rect1, rect3));

		// Overlapping rectangles with rotation
		LibMath::Geometry2D::OBB rect4(LibMath::Geometry2D::Point(2.0f, 2.0f), 4.0f, 4.0f);
		rect4.rotate(LibMath::Radian(static_cast<float>(M_PI) / 4)); // Rotate 45 degrees
		CHECK(LibMath::Collision2D::checkCollisionOBBOBB(rect1, rect4));

		// Edge-touching rectangles
		LibMath::Geometry2D::OBB rect5(LibMath::Geometry2D::Point(4.0f, 0.0f), 4.0f, 4.0f);
		CHECK(LibMath::Collision2D::checkCollisionOBBOBB(rect1, rect5));
	}

	SECTION("Collision Detection Edge Cases") {
		// Completely overlapping rectangles
		LibMath::Geometry2D::OBB rect1(LibMath::Geometry2D::Point(0.0f, 0.0f), 4.0f, 4.0f);
		LibMath::Geometry2D::OBB rect2(LibMath::Geometry2D::Point(0.0f, 0.0f), 4.0f, 4.0f);
		CHECK(LibMath::Collision2D::checkCollisionOBBOBB(rect1, rect2));

		// Rectangles with one edge overlapping
		LibMath::Geometry2D::OBB rect3(LibMath::Geometry2D::Point(2.0f, 0.0f), 4.0f, 4.0f);
		CHECK(LibMath::Collision2D::checkCollisionOBBOBB(rect1, rect3));

		// Rectangles far apart
		LibMath::Geometry2D::OBB rect4(LibMath::Geometry2D::Point(100.0f, 100.0f), 4.0f, 4.0f);
		CHECK_FALSE(LibMath::Collision2D::checkCollisionOBBOBB(rect1, rect4));
	}
}

TEST_CASE("OBB2D Collisions", "[.all][Collision2D][Circle2D]")
{
	SECTION("Collision with Circle2") {
		LibMath::Geometry2D::Circle circle1(LibMath::Geometry2D::Point(0.0f, 0.0f), 5.0f);

		// No overlap
		LibMath::Geometry2D::Circle circle2(LibMath::Geometry2D::Point(20.0f, 20.0f), 5.0f);
		CHECK_FALSE(LibMath::Collision2D::checkCollisionCircleCircle(circle1, circle2));

		// Touching externally
		LibMath::Geometry2D::Circle circle3(LibMath::Geometry2D::Point(10.0f, 0.0f), 5.0f);
		CHECK(LibMath::Collision2D::checkCollisionCircleCircle(circle1, circle3));

		// Overlapping
		LibMath::Geometry2D::Circle circle4(LibMath::Geometry2D::Point(3.0f, 0.0f), 5.0f);
		CHECK(LibMath::Collision2D::checkCollisionCircleCircle(circle1, circle4));

		// Contained within
		LibMath::Geometry2D::Circle circle5(LibMath::Geometry2D::Point(1.0f, 1.0f), 1.0f);
		CHECK(LibMath::Collision2D::checkCollisionCircleCircle(circle1, circle5));
	}

	SECTION("Collision with Line2") {
		LibMath::Geometry2D::Circle circle(LibMath::Geometry2D::Point(0.0f, 0.0f), 5.0f);

		// Line completely outside the circle
		LibMath::Geometry2D::Line line1(LibMath::Geometry2D::Point(10.0f, 10.0f), LibMath::Geometry2D::Point(20.0f, 20.0f));
		CHECK_FALSE(LibMath::Collision2D::checkCollisionCircleLine(circle, line1));

		// Line intersecting the circle
		LibMath::Geometry2D::Line line2(LibMath::Geometry2D::Point(-10.0f, 0.0f), LibMath::Geometry2D::Point(10.0f, 0.0f));
		CHECK(LibMath::Collision2D::checkCollisionCircleLine(circle, line2));

		// Line tangential to the circle
		LibMath::Geometry2D::Line line3(LibMath::Geometry2D::Point(0.0f, 5.0f), LibMath::Geometry2D::Point(5.0f, 5.0f));
		CHECK(LibMath::Collision2D::checkCollisionCircleLine(circle, line3));

		// Line completely inside the circle
		LibMath::Geometry2D::Line line4(LibMath::Geometry2D::Point(-2.0f, 0.0f), LibMath::Geometry2D::Point(2.0f, 0.0f));
		CHECK(LibMath::Collision2D::checkCollisionCircleLine(circle, line4));
	}

	SECTION("Collision with Point2") {
		LibMath::Geometry2D::Circle circle(LibMath::Geometry2D::Point(0.0f, 0.0f), 5.0f);

		// Point inside the circle
		LibMath::Geometry2D::Point point1(2.0f, 2.0f);
		CHECK(LibMath::Collision2D::checkCollisionCirclePoint(circle, point1));

		// Point on the boundary of the circle
		LibMath::Geometry2D::Point point2(5.0f, 0.0f);
		CHECK(LibMath::Collision2D::checkCollisionCirclePoint(circle, point2));

		// Point outside the circle
		LibMath::Geometry2D::Point point3(10.0f, 10.0f);
		CHECK_FALSE(LibMath::Collision2D::checkCollisionCirclePoint(circle, point3));
	}
}
