#include <LibMath/Angle.h>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <glm/trigonometric.hpp>

#include <glm/gtc/constants.hpp>

using namespace LibMath::Literal;

constexpr float halfRadianCircle = glm::pi<float>();
constexpr float radianCircle = glm::two_pi<float>();

TEST_CASE("Degree", "[.all][angle]")
{
	using namespace LibMath;

	SECTION("Constructors and Assignment")
	{
		Degree def;
		CHECK(def.raw() == 0.f);

		Degree fromValue{ 90.f };
		CHECK(fromValue.raw() == 90.f);

		Degree copied{ fromValue };
		CHECK(copied.raw() == 90.f);

		Degree assigned;
		assigned = copied;
		CHECK(assigned.raw() == 90.f);

		CHECK(sizeof(Degree) == sizeof(float));
	}

	SECTION("Accessors and Wrapping")
	{
		Degree zero{ 0.f };
		CHECK(zero.degree(false) == 0.f);
		CHECK(zero.degree(true) == 0.f);
		CHECK(zero.radian(false) == Catch::Approx(0.f));
		CHECK(zero.radian(true) == Catch::Approx(0.f));

		Degree angle1{ 360.f };
		CHECK(angle1.degree(false) == 0.f);
		CHECK(angle1.degree(true) == 0.f);

		Degree angle2{ -90.f };
		CHECK(angle2.degree(false) == 270.f);
		CHECK(angle2.degree(true) == -90.f);

		Degree angle3{ 450.f };
		CHECK(angle3.degree(false) == 90.f);
		CHECK(angle3.degree(true) == 90.f);

		Degree angle4{ -450.f };
		CHECK(angle4.degree(false) == 270.f);
		CHECK(angle4.degree(true) == -90.f);
	}

	SECTION("wrap() method modifies internal state")
	{
		Degree a{ 900.f };
		a.wrap(false);
		CHECK(a.raw() == 180.f);

		a = Degree{ 900.f };
		a.wrap(true);
		CHECK(a.raw() == -180.f);

		Degree b{ -1000.f };
		b.wrap(false);
		CHECK(b.raw() == 80.f);

		b = Degree{ -1000.f };
		b.wrap(true);
		CHECK(b.raw() == 80.f); // in [-180, 180[
	}

	SECTION("Arithmetic operators")
	{
		CHECK((Degree{ 30.f } + Degree{ 60.f }).degree() == 90.f);
		CHECK((Degree{ 90.f } - Degree{ 45.f }).degree() == 45.f);
		CHECK((-Degree{ 45.f }).degree() == 315.f);

		CHECK((Degree{ 90.f } *2.f).degree() == 180.f);
		CHECK((Degree{ 90.f } / 3.f).degree() == 30.f);

		Degree d1{ 45.f }; d1 += Degree{ 45.f };
		CHECK(d1.degree() == 90.f);

		Degree d2{ 90.f }; d2 -= Degree{ 30.f };
		CHECK(d2.degree() == 60.f);

		Degree d3{ 90.f }; d3 *= 2.f;
		CHECK(d3.degree() == 180.f);

		Degree d4{ 90.f }; d4 /= 2.f;
		CHECK(d4.degree() == 45.f);
	}

	SECTION("Comparators")
	{
		CHECK(Degree{ 60.f } == Degree{ 60.f });
		CHECK(Degree{ 60.f } == 60.f);
		CHECK(Degree{ 450.f } == Degree{ 90.f });
		CHECK(Degree{ 0.f } == Degree{ 360.f });
		CHECK(Degree{ -180.f } == Degree{ 180.f });
	}

	SECTION("Conversion to Radian")
	{
	
		CHECK(Degree{ 180.f } == Radian{ glm::pi<float>() });

		CHECK_FALSE(Degree{ 90.f } == Radian{ glm::pi<float>() });

	}

	SECTION("Comparison with Radian")
	{
		Radian pi{ glm::pi<float>() };
		CHECK(Degree{ 180.f } == pi);
		CHECK_FALSE(Degree{ 90.f } == pi);
	}

	SECTION("Conversion to Radian (const operator)")
	{
		const Degree deg{ 180.f };
		Radian rad = deg; // conversion implicite
		CHECK(rad.raw() == Catch::Approx(glm::pi<float>()));
	}

	SECTION("User-defined literal _deg")
	{
		auto a = 90_deg;
		CHECK(a.raw() == 90.f);

		auto b = -270_deg;
		CHECK(b.degree(true) == 90.f);
		CHECK(b.degree(false) == 90.f);

		auto c = 1080_deg;
		CHECK(c.degree(false) == 0.f);
		CHECK(c.degree(true) == 0.f);
	}

	SECTION("Edge Cases")
	{
		Degree big{ 100000.f };
		CHECK(big.degree(false) == Catch::Approx(280.f));

		Degree small{ -100000.f };
		CHECK(small.degree(false) == Catch::Approx(80.f));

		Degree nearWrapHigh{ 359.999f };
		CHECK(nearWrapHigh.degree(false) == Catch::Approx(359.999f));
		CHECK(nearWrapHigh.degree(true) == Catch::Approx(-0.001f).margin(0.0001f));

		Degree nearWrapLow{ -0.001f };
		CHECK(nearWrapLow.degree(false) == Catch::Approx(359.999f));
		CHECK(nearWrapLow.degree(true) == Catch::Approx(-0.001f));
	}

	SECTION("User-defined literal")
	{
		auto angle = 90_deg;
		CHECK(angle.raw() == 90.f);

		angle = 370_deg;
		CHECK(angle.degree() == 10.f);

		CHECK(angle == Degree{ 370.f });
	}
}

TEST_CASE("Radian", "[.all][angle]")
{
	using namespace LibMath;

	SECTION("Instantiation")
	{
		{
			[[maybe_unused]] Radian temp;
		}

		Radian empty;
		CHECK(empty.raw() == 0.f);

		float value = 1.2f;
		Radian angle{ value };
		CHECK(angle.raw() == value);

		Radian copy{ angle };
		CHECK(copy.raw() == value);

		empty = angle;
		CHECK(empty.raw() == value);

		Radian literal = 1.2_rad;
		CHECK(literal.raw() == value);
		literal = 1_rad;
		CHECK(literal.raw() == 1.f);

		CHECK(sizeof Radian == sizeof(float));
	}

	SECTION("Accessors")
	{
		Radian zero;
		CHECK(zero.degree(true) == 0.f);
		CHECK(zero.degree(false) == 0.f);
		CHECK(zero.radian(true) == 0.f);
		CHECK(zero.radian(false) == 0.f);

		Radian oneRadian{ 1.2f };
		CHECK(oneRadian.degree(true) == Catch::Approx(glm::degrees(1.2f)));
		CHECK(oneRadian.degree(false) == Catch::Approx(glm::degrees(1.2f)));
		CHECK(oneRadian.radian(true) == 1.2f);
		CHECK(oneRadian.radian(false) == 1.2f);

		{
			const float wrapRadian = 5.8f - radianCircle;
			Radian six{ 5.8f };
			CHECK(six.degree(true) == Catch::Approx(glm::degrees(wrapRadian)));
			CHECK(six.degree(false) == Catch::Approx(glm::degrees(5.8f)));
			CHECK(six.radian(true) == Catch::Approx(wrapRadian));
			CHECK(six.radian(false) == 5.8f);
		}

		{
			const float wrapRadian = radianCircle - 1.2f;
			Radian minusOne{ -1.2f };
			CHECK(minusOne.degree(true) == Catch::Approx(glm::degrees(-1.2f)));
			CHECK(minusOne.degree(false) == Catch::Approx(glm::degrees(wrapRadian)));
			CHECK(minusOne.radian(true) == -1.2f);
			CHECK(minusOne.radian(false) == Catch::Approx(wrapRadian));
		}

		{
			const float wrap = 15.f - 2.f * radianCircle;
			Radian fifteen{ 15.f };
			CHECK(fifteen.radian(true) == Catch::Approx(wrap));
			CHECK(fifteen.radian(false) == Catch::Approx(wrap));
			CHECK(fifteen.degree(true) == Catch::Approx(glm::degrees(wrap)));
			CHECK(fifteen.degree(false) == Catch::Approx(glm::degrees(wrap)));
		}

		{
			const float wrap = -15.f + 3.f * radianCircle;
			const float wrapMod = -15.f + 2.f * radianCircle;
			Radian minusFifteen{ -15.f };
			CHECK(minusFifteen.radian(true) == Catch::Approx(wrapMod));
			CHECK(minusFifteen.radian(false) == Catch::Approx(wrap));
			CHECK(minusFifteen.degree(true) == Catch::Approx(glm::degrees(wrapMod)));
			CHECK(minusFifteen.degree(false) == Catch::Approx(glm::degrees(wrap)));
		}
	}

	SECTION("Edge Wrapping Values")
	{
		const float pi = glm::pi<float>();
		const float twoPi = glm::two_pi<float>();

		CHECK(Radian{ twoPi }.radian(false) == Catch::Approx(0.f));
		CHECK(Radian{ -twoPi }.radian(false) == Catch::Approx(0.f));

		CHECK(Radian{ pi } == Radian{ -pi });

		CHECK(Radian{ pi - 0.0001f }.radian(true) == Catch::Approx(pi - 0.0001f));
		CHECK(Radian{ pi + 0.0001f }.radian(true) == Catch::Approx(-pi + 0.0001f).margin(0.0002f));

		CHECK(Radian{ -pi - 0.0001f }.radian(true) == Catch::Approx(pi - 0.0001f).margin(0.0002f));
	}

	SECTION("Comparator")
	{
		Radian self{ 1.2f };
		CHECK(self == self);
		CHECK(Radian{ 1.2f } == Radian{ 1.2f });
		CHECK(Radian{ 1.2f } == Radian{ 1.2f + radianCircle });
		CHECK(Radian{ 0.f } == Radian{ radianCircle });
		CHECK(Radian{ -halfRadianCircle } == Radian{ halfRadianCircle });
	}

	SECTION("Comparison with Degree")
	{
		CHECK(Radian{ glm::radians(90.f) } == Degree{ 90.f });
		CHECK_FALSE(Radian{ glm::radians(45.f) } == Degree{ 90.f });
	}

	SECTION("Arithmetic")
	{
		Radian sum = Radian(0.75f) + Radian(0.5f);
		CHECK(sum.radian() == 1.25f);

		Radian acc(0.75f);
		acc += Radian(0.5f);
		CHECK(acc.radian() == 1.25f);

		Radian neg = -Radian(0.75f);
		CHECK(neg.radian() == -0.75f);

		Radian diff = Radian(0.75f) - Radian(0.5f);
		CHECK(diff.radian() == 0.25f);

		Radian acc2(0.75f);
		acc2 -= Radian(0.5f);
		CHECK(acc2.radian() == 0.25f);

		Radian prod = Radian(0.75f) * 10.f;
		CHECK(prod.radian() == 7.5f - radianCircle);

		Radian prod2(0.75f);
		prod2 *= 10.f;
		CHECK(prod2.radian() == 7.5f - radianCircle);

		Radian quot = Radian(0.75f) / 4.f;
		CHECK(quot.radian() == 0.1875f);

		Radian quot2(0.75f);
		quot2 /= 4.f;
		CHECK(quot2.radian() == 0.1875f);
	}

	SECTION("Functionality")
	{
		Radian wrapAngle{ halfRadianCircle * 5.f };
		wrapAngle.wrap(false);
		CHECK(wrapAngle.raw() == Catch::Approx(halfRadianCircle));

		Radian wrapEdge{ radianCircle };
		wrapEdge.wrap(false);
		CHECK(wrapEdge.raw() == 0.f);

		wrapEdge = Radian{ halfRadianCircle };
		wrapEdge.wrap(true);
		CHECK(wrapEdge.raw() == Catch::Approx(-halfRadianCircle));
	}

	SECTION("Conversion from Degree and to Degree")
	{
		Radian rad{ Degree{ 60.f } };
		CHECK(rad.raw() == Catch::Approx(glm::radians(60.f)));

		Degree deg{ Radian{ 1.2f } };
		CHECK(deg.raw() == Catch::Approx(glm::degrees(1.2f)));
	}

	SECTION("Const Conversion to Degree")
	{
		const Radian rad{ glm::half_pi<float>() }; // π/2
		Degree deg = rad; // conversion implicite
		CHECK(deg.raw() == Catch::Approx(90.f));
	}

	SECTION("User-defined literal _rad")
	{
		auto a = 1.570796_rad;
		CHECK(a.raw() == Catch::Approx(glm::half_pi<float>()));

		auto b = 6_rad;
		CHECK(b.raw() == 6.f);

		auto wrapped = 7_rad;
		CHECK(wrapped.radian(true) == Catch::Approx(7.f - glm::two_pi<float>()));
	}
}