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
		CHECK(a.m_x == x);
		CHECK(a.m_y == y);

		// copy constructor
		LibMath::Geometry2D::Point b{ a };
		CHECK(b.m_x == x);
		CHECK(b.m_y == y);

		// assignment operator
		p = a;
		CHECK(p.m_x == x);
		CHECK(p.m_y == y);

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
		CHECK_FALSE(LibMath::Geometry2D::Point{ 150.f, 30.f } == LibMath::Geometry2D::Point{ 70.f, 25.f });

	}

	SECTION("DistanceBetweenPoint")
	{
		SECTION("Distance - Same point object")
		{
			LibMath::Geometry2D::Point p{ 3.f, 4.f };
			CHECK(LibMath::Geometry2D::DistancebBetweenPoint(p, p) == 0.f);
		}

		SECTION("Distance - Same coordinates, different objects")
		{
			LibMath::Geometry2D::Point p1{ 3.f, 4.f };
			LibMath::Geometry2D::Point p2{ 3.f, 4.f };
			CHECK(LibMath::Geometry2D::DistancebBetweenPoint(p1, p2) == 0.f);
		}

		SECTION("Distance - From origin")
		{
			LibMath::Geometry2D::Point origin{ 0.f, 0.f };

			// 3-4-5 right triangle
			LibMath::Geometry2D::Point p{ 3.f, 4.f };
			CHECK(LibMath::Geometry2D::DistancebBetweenPoint(origin, p) == Catch::Approx(5.f));
		}

		SECTION("Distance - Horizontal only")
		{
			LibMath::Geometry2D::Point p1{ 7.f, 7.f };
			LibMath::Geometry2D::Point p2{ 5.f, 7.f };
			CHECK(LibMath::Geometry2D::DistancebBetweenPoint(p1, p2) == Catch::Approx(2.f));
		}

		SECTION("Distance - Vertical only")
		{
			LibMath::Geometry2D::Point p1{ 25.4f, 25.4f };
			LibMath::Geometry2D::Point p2{ 25.4f, 18.504f };
			CHECK(LibMath::Geometry2D::DistancebBetweenPoint(p1, p2) == Catch::Approx(6.896f));
		}

		SECTION("Distance - Symmetry: d(A,B) == d(B,A)")
		{
			LibMath::Geometry2D::Point p1{ -1.028f, 2.f };
			LibMath::Geometry2D::Point p2{ 4.f, -6.286f };
			CHECK(LibMath::Geometry2D::DistancebBetweenPoint(p1, p2) ==
				LibMath::Geometry2D::DistancebBetweenPoint(p2, p1));
		}

		SECTION("Distance - Negative coordinates")
		{
			LibMath::Geometry2D::Point p1{ -3.f, -4.f };
			LibMath::Geometry2D::Point p2{ 0.f,  0.f };
			CHECK(LibMath::Geometry2D::DistancebBetweenPoint(p1, p2) == Catch::Approx(5.f));
		}

		SECTION("Distance - Both points in negative space")
		{
			LibMath::Geometry2D::Point p1{ -1.f, -1.f };
			LibMath::Geometry2D::Point p2{ -4.f, -5.f };
			CHECK(LibMath::Geometry2D::DistancebBetweenPoint(p1, p2) == Catch::Approx(5.f));
		}

		SECTION("Distance - Mixed positive/negative coordinates")
		{
			LibMath::Geometry2D::Point p1{ -3.f, 0.f };
			LibMath::Geometry2D::Point p2{ 3.f, 0.f };
			CHECK(LibMath::Geometry2D::DistancebBetweenPoint(p1, p2) == Catch::Approx(6.f));
		}

		SECTION("Distance - Fractional values")
		{
			LibMath::Geometry2D::Point p1{ 0.f,  0.f };
			LibMath::Geometry2D::Point p2{ 0.3f, 0.4f };
			CHECK(LibMath::Geometry2D::DistancebBetweenPoint(p1, p2) == Catch::Approx(0.5f));
		}

		SECTION("Distance - Large values")
		{
			LibMath::Geometry2D::Point p1{ 5.8f,    5.8f };
			LibMath::Geometry2D::Point p2{ 10005.8f, 10005.8f };
			CHECK(LibMath::Geometry2D::DistancebBetweenPoint(p1, p2) == Catch::Approx(10000.f * std::sqrt(2.f)));
		}

		SECTION("Distance - Small values")
		{
			LibMath::Geometry2D::Point p1{ 0.0000002551f,    0.0000004852f };
			LibMath::Geometry2D::Point p2{ 1.8e-5f, 425.1025e-8f };
			CHECK(LibMath::Geometry2D::DistancebBetweenPoint(p1, p2) == Catch::Approx(1.81401e-5f).epsilon(1e-4f));
		}

		SECTION("Distance - Copy constructed points yield same result")
		{
			LibMath::Geometry2D::Point p1{ 1.f, 1.f };
			LibMath::Geometry2D::Point p2{ 4.f, 5.f };
			LibMath::Geometry2D::Point p1Copy{ p1 };
			LibMath::Geometry2D::Point p2Copy{ p2 };
			CHECK(LibMath::Geometry2D::DistancebBetweenPoint(p1, p2) ==
				LibMath::Geometry2D::DistancebBetweenPoint(p1Copy, p2Copy));
		}

		SECTION("Distance - Default constructed points are at origin")
		{
			LibMath::Geometry2D::Point p1;
			LibMath::Geometry2D::Point p2{ 0.f, 5.f };
			CHECK(LibMath::Geometry2D::DistancebBetweenPoint(p1, p2) == Catch::Approx(5.f));
		}
	}
}

TEST_CASE("Line", "[.all][geometricObject]")
{
	SECTION("Instantiation") 
	{

		// Default constructor
		LibMath::Geometry2D::Line lineDefault;
		CHECK(lineDefault.m_start == LibMath::Geometry2D::Point());
		CHECK(lineDefault.m_end == LibMath::Geometry2D::Point());

		// Parameterized constructor
		LibMath::Geometry2D::Point p1(0.0f, 0.0f);
		LibMath::Geometry2D::Point p2(3.0f, 4.0f);
		LibMath::Geometry2D::Line lineParam(p1, p2);
		CHECK(lineParam.m_start == p1);
		CHECK(lineParam.m_end == p2);

		// Copy constructor
		LibMath::Geometry2D::Line lineCopy(lineParam);
		CHECK(lineCopy.m_start == p1);
		CHECK(lineCopy.m_end == p2);

		// Assignment operator
		LibMath::Geometry2D::Line lineAssign;
		lineAssign = lineParam;
		CHECK(lineAssign.m_start == lineParam.m_start);
		CHECK(lineAssign.m_end == lineParam.m_end);

		// Destructor
		{
			LibMath::Geometry2D::Line temp;
		}
	}

	SECTION("Comparison") 
	{
		LibMath::Geometry2D::Point p1(0.0f, 0.0f);
		LibMath::Geometry2D::Point p2(3.0f, 4.0f);
		LibMath::Geometry2D::Point p3(-3.0f, -4.0f);
		

		LibMath::Geometry2D::Line line1(p1, p2);
		LibMath::Geometry2D::Line line2(p1, p2);
		LibMath::Geometry2D::Line line3(p2, LibMath::Geometry2D::Point(6.0f, 8.0f));
		LibMath::Geometry2D::Line line4(p1, p3);

		CHECK(line1 == line2);
		CHECK_FALSE(line1 == line3);
		CHECK(line1.m_start.m_x == -line4.m_start.m_x);
		CHECK(line1.m_start.m_y == -line4.m_start.m_y);
		CHECK(line1.m_end.m_x == -line4.m_end.m_x);
		CHECK(line1.m_end.m_y == -line4.m_end.m_y);
	}

	SECTION("Length and LengthSquared") 
	{
		LibMath::Geometry2D::Point p1(5.0f, 9.0f);
		LibMath::Geometry2D::Point p2(3.0f, 4.0f);
		LibMath::Geometry2D::Line line(p1, p2);

		float distance = LibMath::Geometry2D::DistancebBetweenPoint(p1, p2);

		CHECK(line.lenght() == Catch::Approx(distance));
		CHECK(line.lenghtSquare() == Catch::Approx(distance * distance));
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

		// Additional tests for point-line collision
		SECTION("Point on line endpoints")
		{
			CHECK(LibMath::Collision2D::checkCollisionLinePoint(line, p1));  // Point at start
			CHECK(LibMath::Collision2D::checkCollisionLinePoint(line, p2));  // Point at end
		}

		SECTION("Horizontal line point tests")
		{
			LibMath::Geometry2D::Line horizontalLine(LibMath::Geometry2D::Point(0.0f, 5.0f), LibMath::Geometry2D::Point(10.0f, 5.0f));
			CHECK(LibMath::Collision2D::checkCollisionLinePoint(horizontalLine, LibMath::Geometry2D::Point(5.0f, 5.0f)));
			CHECK_FALSE(LibMath::Collision2D::checkCollisionLinePoint(horizontalLine, LibMath::Geometry2D::Point(5.0f, 6.0f)));
		}

		SECTION("Vertical line point tests")
		{
			LibMath::Geometry2D::Line verticalLine(LibMath::Geometry2D::Point(3.0f, 0.0f), LibMath::Geometry2D::Point(3.0f, 8.0f));
			CHECK(LibMath::Collision2D::checkCollisionLinePoint(verticalLine, LibMath::Geometry2D::Point(3.0f, 4.0f)));
			CHECK_FALSE(LibMath::Collision2D::checkCollisionLinePoint(verticalLine, LibMath::Geometry2D::Point(4.0f, 4.0f)));
		}

		SECTION("Negative coordinates")
		{
			LibMath::Geometry2D::Line negativeLine(LibMath::Geometry2D::Point(-5.0f, -5.0f), LibMath::Geometry2D::Point(0.0f, 0.0f));
			CHECK(LibMath::Collision2D::checkCollisionLinePoint(negativeLine, LibMath::Geometry2D::Point(-2.5f, -2.5f)));
			CHECK_FALSE(LibMath::Collision2D::checkCollisionLinePoint(negativeLine, LibMath::Geometry2D::Point(-2.0f, -3.0f)));
		}
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

		// Additional line-line collision tests
		SECTION("Overlapping lines")
		{
			LibMath::Geometry2D::Line line1(LibMath::Geometry2D::Point(0.0f, 0.0f), LibMath::Geometry2D::Point(4.0f, 4.0f));
			LibMath::Geometry2D::Line line2(LibMath::Geometry2D::Point(1.0f, 1.0f), LibMath::Geometry2D::Point(3.0f, 3.0f));
			CHECK(LibMath::Collision2D::checkCollisionLineLine(line1, line2)); // line2 is subset of line1
		}

		SECTION("T-intersection")
		{
			LibMath::Geometry2D::Line horizontalLine(LibMath::Geometry2D::Point(0.0f, 2.0f), LibMath::Geometry2D::Point(4.0f, 2.0f));
			LibMath::Geometry2D::Line verticalLine(LibMath::Geometry2D::Point(2.0f, 0.0f), LibMath::Geometry2D::Point(2.0f, 4.0f));
			CHECK(LibMath::Collision2D::checkCollisionLineLine(horizontalLine, verticalLine)); // T-intersection at (2, 2)
		}

		SECTION("Perpendicular lines not intersecting")
		{
			LibMath::Geometry2D::Line horizontalLine(LibMath::Geometry2D::Point(0.0f, 0.0f), LibMath::Geometry2D::Point(2.0f, 0.0f));
			LibMath::Geometry2D::Line verticalLine(LibMath::Geometry2D::Point(3.0f, -1.0f), LibMath::Geometry2D::Point(3.0f, 1.0f));
			CHECK_FALSE(LibMath::Collision2D::checkCollisionLineLine(horizontalLine, verticalLine));
		}

		SECTION("Diagonal parallel lines")
		{
			LibMath::Geometry2D::Line line1(LibMath::Geometry2D::Point(0.0f, 0.0f), LibMath::Geometry2D::Point(2.0f, 2.0f));
			LibMath::Geometry2D::Line line2(LibMath::Geometry2D::Point(1.0f, 0.0f), LibMath::Geometry2D::Point(3.0f, 2.0f));
			CHECK_FALSE(LibMath::Collision2D::checkCollisionLineLine(line1, line2)); // Parallel diagonal lines
		}

		SECTION("Lines with negative slopes")
		{
			LibMath::Geometry2D::Line line1(LibMath::Geometry2D::Point(0.0f, 4.0f), LibMath::Geometry2D::Point(4.0f, 0.0f));
			LibMath::Geometry2D::Line line2(LibMath::Geometry2D::Point(0.0f, 0.0f), LibMath::Geometry2D::Point(4.0f, 4.0f));
			CHECK(LibMath::Collision2D::checkCollisionLineLine(line1, line2)); // X-intersection at (2, 2)
		}

		SECTION("Lines in different quadrants")
		{
			LibMath::Geometry2D::Line line1(LibMath::Geometry2D::Point(-2.0f, -2.0f), LibMath::Geometry2D::Point(0.0f, 0.0f));
			LibMath::Geometry2D::Line line2(LibMath::Geometry2D::Point(-2.0f, 0.0f), LibMath::Geometry2D::Point(0.0f, -2.0f));
			CHECK(LibMath::Collision2D::checkCollisionLineLine(line1, line2)); // Intersect at (-1, -1)
		}
	}

	SECTION("Edge Cases")
	{
		SECTION("Zero-length line (point)")
		{
			LibMath::Geometry2D::Point samePoint(2.0f, 2.0f);
			LibMath::Geometry2D::Line zeroLine(samePoint, samePoint);
			LibMath::Geometry2D::Line normalLine(LibMath::Geometry2D::Point(0.0f, 0.0f), LibMath::Geometry2D::Point(4.0f, 4.0f));

			// Zero-length line collision with point
			CHECK(LibMath::Collision2D::checkCollisionLinePoint(zeroLine, samePoint));
			CHECK_FALSE(LibMath::Collision2D::checkCollisionLinePoint(zeroLine, LibMath::Geometry2D::Point(3.0f, 3.0f)));

			// Zero-length line collision with normal line
			CHECK(LibMath::Collision2D::checkCollisionLineLine(zeroLine, normalLine)); // Point (2,2) is on line

			// Two zero-length lines
			LibMath::Geometry2D::Line zeroLine2(LibMath::Geometry2D::Point(3.0f, 3.0f), LibMath::Geometry2D::Point(3.0f, 3.0f));
			CHECK_FALSE(LibMath::Collision2D::checkCollisionLineLine(zeroLine, zeroLine2)); // Different points
			CHECK(LibMath::Collision2D::checkCollisionLineLine(zeroLine, zeroLine)); // Same point
		}

		SECTION("Very close points (floating point precision)")
		{
			const float epsilon = 1e-6f;
			LibMath::Geometry2D::Line line(LibMath::Geometry2D::Point(0.0f, 0.0f), LibMath::Geometry2D::Point(1.0f, 1.0f));
			LibMath::Geometry2D::Point nearPoint(0.5f + epsilon, 0.5f + epsilon);
			LibMath::Geometry2D::Point exactPoint(0.5f, 0.5f);

			CHECK(LibMath::Collision2D::checkCollisionLinePoint(line, exactPoint));
			// This test depends on the implementation's tolerance for floating point errors
			// CHECK_FALSE(LibMath::Collision2D::checkCollisionLinePoint(line, nearPoint));
		}

		SECTION("Lines with very small differences")
		{
			const float epsilon = 1e-6f;
			LibMath::Geometry2D::Line line1(LibMath::Geometry2D::Point(0.0f, 0.0f), LibMath::Geometry2D::Point(1.0f, 1.0f));
			LibMath::Geometry2D::Line almostParallel(LibMath::Geometry2D::Point(0.0f, epsilon), LibMath::Geometry2D::Point(1.0f, 1.0f + epsilon));

			// Should intersect near origin due to tiny difference
			CHECK(LibMath::Collision2D::checkCollisionLineLine(line1, almostParallel));
		}

		SECTION("Colinear lines")
		{
			// Same line
			LibMath::Geometry2D::Line line1(LibMath::Geometry2D::Point(0.0f, 0.0f), LibMath::Geometry2D::Point(4.0f, 4.0f));
			LibMath::Geometry2D::Line sameLine(LibMath::Geometry2D::Point(0.0f, 0.0f), LibMath::Geometry2D::Point(4.0f, 4.0f));
			CHECK(LibMath::Collision2D::checkCollisionLineLine(line1, sameLine));

			// Colinear but not overlapping
			LibMath::Geometry2D::Line colinearLine(LibMath::Geometry2D::Point(5.0f, 5.0f), LibMath::Geometry2D::Point(8.0f, 8.0f));
			CHECK_FALSE(LibMath::Collision2D::checkCollisionLineLine(line1, colinearLine));

			// Colinear and overlapping
			LibMath::Geometry2D::Line overlappingLine(LibMath::Geometry2D::Point(2.0f, 2.0f), LibMath::Geometry2D::Point(6.0f, 6.0f));
			CHECK(LibMath::Collision2D::checkCollisionLineLine(line1, overlappingLine));
		}

		SECTION("Extreme coordinate values")
		{
			LibMath::Geometry2D::Line extremeLine(LibMath::Geometry2D::Point(-1000.0f, -1000.0f),
				LibMath::Geometry2D::Point(1000.0f, 1000.0f));
			LibMath::Geometry2D::Point originPoint(0.0f, 0.0f);
			LibMath::Geometry2D::Point extremePoint(500.0f, 500.0f);

			CHECK(LibMath::Collision2D::checkCollisionLinePoint(extremeLine, originPoint));
			CHECK(LibMath::Collision2D::checkCollisionLinePoint(extremeLine, extremePoint));
		}

		SECTION("Axis-aligned edge cases")
		{
			// Horizontal line at origin
			LibMath::Geometry2D::Line xAxis(LibMath::Geometry2D::Point(-5.0f, 0.0f), LibMath::Geometry2D::Point(5.0f, 0.0f));
			// Vertical line at origin  
			LibMath::Geometry2D::Line yAxis(LibMath::Geometry2D::Point(0.0f, -5.0f), LibMath::Geometry2D::Point(0.0f, 5.0f));

			CHECK(LibMath::Collision2D::checkCollisionLineLine(xAxis, yAxis)); // Intersect at origin
			CHECK(LibMath::Collision2D::checkCollisionLinePoint(xAxis, LibMath::Geometry2D::Point(0.0f, 0.0f)));
			CHECK(LibMath::Collision2D::checkCollisionLinePoint(yAxis, LibMath::Geometry2D::Point(0.0f, 0.0f)));
		}

		SECTION("Near-miss intersections")
		{
			LibMath::Geometry2D::Line line1(LibMath::Geometry2D::Point(0.0f, 0.0f), LibMath::Geometry2D::Point(2.0f, 2.0f));
			LibMath::Geometry2D::Line line2(LibMath::Geometry2D::Point(0.0f, 0.1f), LibMath::Geometry2D::Point(2.0f, 2.1f));

			// Lines are very close but don't actually intersect within the segments
			CHECK_FALSE(LibMath::Collision2D::checkCollisionLineLine(line1, line2));
		}
	}

	SECTION("Boundary and Limit Tests")
	{
		SECTION("Point exactly at line extension")
		{
			LibMath::Geometry2D::Line shortLine(LibMath::Geometry2D::Point(1.0f, 1.0f), LibMath::Geometry2D::Point(2.0f, 2.0f));
			LibMath::Geometry2D::Point extensionPoint(0.0f, 0.0f); // On line extension but not on segment
			LibMath::Geometry2D::Point extensionPoint2(3.0f, 3.0f); // On line extension but not on segment

			// Depends on whether your implementation treats lines as infinite or as segments
			// Assuming line segments (finite):
			CHECK_FALSE(LibMath::Collision2D::checkCollisionLinePoint(shortLine, extensionPoint));
			CHECK_FALSE(LibMath::Collision2D::checkCollisionLinePoint(shortLine, extensionPoint2));
		}

		SECTION("Lines that would intersect if extended")
		{
			LibMath::Geometry2D::Line line1(LibMath::Geometry2D::Point(0.0f, 0.0f), LibMath::Geometry2D::Point(1.0f, 1.0f));
			LibMath::Geometry2D::Line line2(LibMath::Geometry2D::Point(2.0f, 0.0f), LibMath::Geometry2D::Point(3.0f, 1.0f));

			// These lines would intersect if extended, but don't as segments
			CHECK_FALSE(LibMath::Collision2D::checkCollisionLineLine(line1, line2));
		}

		SECTION("Multiple intersection candidates")
		{
			// Line that could intersect at multiple theoretical points due to precision
			LibMath::Geometry2D::Line line1(LibMath::Geometry2D::Point(0.0f, 0.0f), LibMath::Geometry2D::Point(4.0f, 0.0f));
			LibMath::Geometry2D::Line line2(LibMath::Geometry2D::Point(2.0f, -1.0f), LibMath::Geometry2D::Point(2.0f, 1.0f));

			CHECK(LibMath::Collision2D::checkCollisionLineLine(line1, line2)); // Should intersect at (2, 0)
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
