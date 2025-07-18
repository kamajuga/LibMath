#include <LibMath/Vector/Vector4.h>
#include <LibMath/Vector/Vector3.h>
#include <LibMath/Vector/Vector2.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/projection.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>

using namespace LibMath::Literal;

#define CHECK_VECTOR2(vector, vectorGlm) CHECK(vector.m_x == Catch::Approx(vectorGlm.x)); CHECK(vector.m_y == Catch::Approx(vectorGlm.y));
#define CHECK_VECTOR3(vector, vectorGlm) CHECK(vector.m_x == Catch::Approx(vectorGlm.x)); CHECK(vector.m_y == Catch::Approx(vectorGlm.y)); CHECK(vector.m_z == Catch::Approx(vectorGlm.z))

TEST_CASE("Vector2", "[.all][vector][Vector2]")
{
	SECTION("Instanciation")
	{
		//destructeur
		{
			[[maybe_unused]] LibMath::Vector2 temp;
		}

		//default constructor
		LibMath::Vector2 vec;
		glm::vec2 vecGlm{};
		CHECK_VECTOR2(vec, vecGlm);

		// basic constructor
		LibMath::Vector2 oneParam{ 2.5f };
		glm::vec2 oneParamGlm{ 2.5f };
		CHECK_VECTOR2(oneParam, oneParamGlm);

		LibMath::Vector2 allParam{ 2.5f, .5f};
		glm::vec2 allParamGlm{ 2.5f, .5f};
		CHECK_VECTOR2(allParam, allParamGlm);

		// copy constructor
		LibMath::Vector2 copy{ allParam };
		glm::vec2 copyGlm{ allParamGlm };
		CHECK_VECTOR2(copy, copyGlm);

		// assignment operator
		vec = allParam;
		vecGlm = allParamGlm;
		CHECK_VECTOR2(vec, vecGlm);

		// OpenGL compatibility
		CHECK(sizeof LibMath::Vector2 == sizeof glm::vec2);
		CHECK(memcmp(&allParam, &allParamGlm, sizeof allParam) == 0);
	}

	SECTION("Accessor") 
	{
		float const x = 2.5f;
		float const y = .5f;
		LibMath::Vector2 vector{ x, y};

		{
			LibMath::Vector2 const& vectorConst = vector;
			CHECK(vectorConst[0] == x);
			CHECK(vectorConst[1] == y);
		}

		{
			vector[0] += 1.f;
			vector[1] += 1.f;
			CHECK(vector[0] == x + 1.f);
			CHECK(vector[1] == y + 1.f);
		}
	}

	SECTION("Comparator")
	{
		// compare with self
		LibMath::Vector2 self{ 2.5f, .5f };
		CHECK(self == self);
		CHECK_FALSE(self != self);

		// compare with same
		CHECK(LibMath::Vector2{ 2.5f, .5f} == LibMath::Vector2{ 2.5f, .5f});
		CHECK_FALSE(LibMath::Vector2{ 2.5f, .5f} != LibMath::Vector2{ 2.5f, .5f});

		// trying to find copy/paste mistake
		LibMath::Vector2 twos{ 2.f, 2.f};
		CHECK_FALSE(LibMath::Vector2{ .5f, 2.f} == twos);
		CHECK_FALSE(LibMath::Vector2{ 2.f, .5f} == twos);
		CHECK(LibMath::Vector2{ .5f, 2.f,} != twos);
		CHECK(LibMath::Vector2{ 2.f, .5f} != twos);
		CHECK_FALSE(twos == LibMath::Vector2{ .5f, 2.f});
		CHECK_FALSE(twos == LibMath::Vector2{ 2.f, .5f});
		CHECK(twos != LibMath::Vector2{ .5f, 2.f});
		CHECK(twos != LibMath::Vector2{ 2.f, .5f});

		CHECK_FALSE(self.isUnit());
		CHECK(LibMath::Vector2{ sqrtf(0.5), sqrtf(0.5)}.isUnit());
	}

	SECTION("Arithmetic")
	{
		LibMath::Vector2 const small{ 2.5f, .5f};
		LibMath::Vector2 const big{ 3.75f, 3.f};

		glm::vec2 const smallGlm{ 2.5f, .5f};
		glm::vec2 const bigGlm{ 3.75f, 3.f};

		SECTION("Addition")
		{
			{
				LibMath::Vector2 sumAssignment = big;
				sumAssignment += small;

				glm::vec2 sumAssignmentGlm = bigGlm;
				sumAssignmentGlm += smallGlm;

				CHECK_VECTOR2(sumAssignment, sumAssignmentGlm);
			}

			{
				LibMath::Vector2 sum = big + small;

				glm::vec2 sumGlm = bigGlm + smallGlm;

				CHECK_VECTOR2(sum, sumGlm);
			}
		}

		SECTION("Opposite")
		{
			LibMath::Vector2 opposite = -LibMath::Vector2{ 3.7f, 3.f};

			glm::vec2 oppositeGlm = -glm::vec2{ 3.7f, 3.f};

			CHECK_VECTOR2(opposite, oppositeGlm);
		}

		SECTION("Substraction")
		{
			{
				LibMath::Vector2 differenceAssignment = big;
				differenceAssignment -= small;

				glm::vec2 differenceAssignmentGlm = bigGlm;
				differenceAssignmentGlm -= smallGlm;

				CHECK_VECTOR2(differenceAssignment, differenceAssignmentGlm);
			}

			{
				LibMath::Vector2 difference = big - small;

				glm::vec2 differenceGlm = bigGlm - smallGlm;

				CHECK_VECTOR2(difference, differenceGlm);
			}
		}

		SECTION("Multiplication")
		{
			{
				LibMath::Vector2 productAssignment = big;
				productAssignment *= small;

				glm::vec2 productAssignmentGlm = bigGlm;
				productAssignmentGlm *= smallGlm;

				CHECK_VECTOR2(productAssignment, productAssignmentGlm);
			}

			{
				LibMath::Vector2 product = big * small;

				glm::vec2 productGlm = bigGlm * smallGlm;

				CHECK_VECTOR2(product, productGlm);
			}

			{
				const float scalar = 2.f;

				{
					LibMath::Vector2 product = small * scalar;
					glm::vec2 productGlm = smallGlm * scalar;

					CHECK_VECTOR2(product, productGlm);
				}

				{
					LibMath::Vector2 productAssignment = small;
					productAssignment *= scalar;

					glm::vec2 productAssignmentGlm = smallGlm;
					productAssignmentGlm *= scalar;

					CHECK_VECTOR2(productAssignment, productAssignmentGlm);
				}
			}
		}

		SECTION("Division")
		{
			{
				LibMath::Vector2 quotientAssignment = big;
				quotientAssignment /= small;

				glm::vec2 quotientAssignmentGlm = bigGlm;
				quotientAssignmentGlm /= smallGlm;

				CHECK_VECTOR2(quotientAssignment, quotientAssignmentGlm);
			}

			{
				LibMath::Vector2 quotient = big / small;

				glm::vec2 quotientGlm = bigGlm / smallGlm;

				CHECK_VECTOR2(quotient, quotientGlm);
			}

			{
				const float scalar = 2.f;

				{
					LibMath::Vector2 quotient = small / scalar;
					glm::vec2 quotientGlm = smallGlm / scalar;

					CHECK_VECTOR2(quotient, quotientGlm);
				}

				{
					LibMath::Vector2 quotientAssignment = small;
					quotientAssignment /= scalar;

					glm::vec2 quotientAssignmentGlm = smallGlm;
					quotientAssignmentGlm /= scalar;

					CHECK_VECTOR2(quotientAssignment, quotientAssignmentGlm);
				}
			}
		}
	}

	SECTION("Functionality")
	{
		LibMath::Vector2 const base{ 2.5f, .5f};
		LibMath::Vector2 const other{ 3.75f, 3.f};

		glm::vec2 const baseGlm{ 2.5f, .5f};
		glm::vec2 const otherGlm{ 3.75f, 3.f};

		SECTION("Angle")
		{

			LibMath::Radian angle = base.angleBetween(other);


			//float angleGlm = glm::angle(glm::normalize(baseGlm), glm::normalize(otherGlm));

			float angleGlm = glm::angle(glm::normalize(baseGlm), glm::normalize(otherGlm));

			CHECK(angle.radian() == Catch::Approx(angleGlm));
		}

		/*SECTION("Cross")
		{
			glm::vec2 vec_test{ 3.4f, 2.f };
			
		}*/

		SECTION("Dot")
		{
			float dot = base.dotProduct(other);

			float dotGlm = glm::dot(baseGlm, otherGlm);

			CHECK(dot == dotGlm);
		}

		SECTION("Distance")
		{
			LibMath::Vector2 vec_distance = other - base;

			{
				
				float distance = vec_distance.magnitude();

				float distanceGlm = glm::distance(baseGlm, otherGlm);

				CHECK(distance == Catch::Approx(distanceGlm));
			}

			{
				float distanceSquare = vec_distance.magnitudeSquare();

				float distanceSquareGlm = glm::distance2(baseGlm, otherGlm);

				CHECK(distanceSquare == Catch::Approx(distanceSquareGlm));
			}
		}

		SECTION("Magnitude")
		{
			{
				float magnitude = base.magnitude();

				float magnitudeGlm = glm::length(baseGlm);

				CHECK(magnitude == Catch::Approx(magnitudeGlm));
			}

			{
				float magnitudeSquare = base.magnitudeSquare();

				float magnitudeSquareGlm = glm::length2(baseGlm);

				CHECK(magnitudeSquare == Catch::Approx(magnitudeSquareGlm));
			}
		}

		SECTION("Normal")
		{
			LibMath::Vector2 normalize = base;
			normalize.normalize();

			glm::vec2 normalizeGlm = glm::normalize(baseGlm);

			CHECK_VECTOR2(normalize, normalizeGlm);
		}

		SECTION("ProjectOnto")
		{
			LibMath::Vector2 project = base;
			project.projectOnto(other);

			glm::vec2 projectGlm = glm::proj(baseGlm, otherGlm);

			CHECK_VECTOR2(project, projectGlm);
		}

		SECTION("ReflectOnto")
		{
			LibMath::Vector2 reflect = base;
			reflect.reflectOnto(other);

			glm::vec2 reflectGlm = glm::reflect(baseGlm, glm::normalize(otherGlm));

			CHECK_VECTOR2(reflect, reflectGlm);
		}
	}
	SECTION("Debug")
	{
#if (defined _DEBUG) || (! defined NDEBUG)
		LibMath::Vector2 vector{ 2.5f, .5f};

		CHECK_THROWS(vector[-1]);
		CHECK_THROWS(vector[3]);
#endif // DEBUG
	}
}


TEST_CASE("Vector3", "[.all][vector][Vector3]")
{
	SECTION("Instantiation")
	{
		// destructor
		{
			[[maybe_unused]] LibMath::Vector3 temp;
		}

		// default constructor
		LibMath::Vector3 empty;
		glm::vec3 emptyGlm{};
		CHECK_VECTOR3(empty, emptyGlm);

		// basic constructor
		LibMath::Vector3 oneParam{ 2.5f };
		glm::vec3 oneParamGlm{ 2.5f };
		CHECK_VECTOR3(oneParam, oneParamGlm);

		LibMath::Vector3 allParam{ 2.5f, .5f, 2.f };
		glm::vec3 allParamGlm{ 2.5f, .5f, 2.f };
		CHECK_VECTOR3(allParam, allParamGlm);

		// copy constructor
		LibMath::Vector3 copy{ allParam };
		glm::vec3 copyGlm{ allParamGlm };
		CHECK_VECTOR3(copy, copyGlm);

		// assignment operator
		empty = allParam;
		emptyGlm = allParamGlm;
		CHECK_VECTOR3(empty, emptyGlm);

		// OpenGL compatibility
		CHECK(sizeof LibMath::Vector3 == sizeof glm::vec3);
		CHECK(memcmp(&allParam, &allParamGlm, sizeof allParam) == 0);
	}

	SECTION("Accessor")
	{
		float const x = 2.5f;
		float const y = .5f;
		float const z = 2.f;
		LibMath::Vector3 vector{ x, y, z };

		{
			LibMath::Vector3 const& vectorConst = vector;
			CHECK(vectorConst[0] == x);
			CHECK(vectorConst[1] == y);
			CHECK(vectorConst[2] == z);
		}

		{
			vector[0] += 1.f;
			vector[1] += 1.f;
			vector[2] += 1.f;
			CHECK(vector[0] == x + 1.f);
			CHECK(vector[1] == y + 1.f);
			CHECK(vector[2] == z + 1.f);
		}
	}

	SECTION("Comparator")
	{
		// compare with self
		LibMath::Vector3 self{ 2.5f, .5f, 2.f };
		CHECK(self == self);
		CHECK_FALSE(self != self);

		// compare with same
		CHECK(LibMath::Vector3{ 2.5f, .5f, 2.f } == LibMath::Vector3{ 2.5f, .5f, 2.f });
		CHECK_FALSE(LibMath::Vector3{ 2.5f, .5f, 2.f } != LibMath::Vector3{ 2.5f, .5f, 2.f });

		// trying to find copy/paste mistake
		LibMath::Vector3 twos{ 2.f, 2.f, 2.f };
		CHECK_FALSE(LibMath::Vector3{ .5f, 2.f, 2.f } == twos);
		CHECK_FALSE(LibMath::Vector3{ 2.f, .5f, 2.f } == twos);
		CHECK_FALSE(LibMath::Vector3{ 2.f, 2.f, .5f } == twos);
		CHECK(LibMath::Vector3{ .5f, 2.f, 2.f } != twos);
		CHECK(LibMath::Vector3{ 2.f, .5f, 2.f } != twos);
		CHECK(LibMath::Vector3{ 2.f, 2.f, .5f } != twos);
		CHECK_FALSE(twos == LibMath::Vector3{ .5f, 2.f, 2.f });
		CHECK_FALSE(twos == LibMath::Vector3{ 2.f, .5f, 2.f });
		CHECK_FALSE(twos == LibMath::Vector3{ 2.f, 2.f, .5f });
		CHECK(twos != LibMath::Vector3{ .5f, 2.f, 2.f });
		CHECK(twos != LibMath::Vector3{ 2.f, .5f, 2.f });
		CHECK(twos != LibMath::Vector3{ 2.f, 2.f, .5f });

		// testing comparaision fonctionnality
		LibMath::Vector3 small{ 2.5f, .5f, 2.f };
		LibMath::Vector3 big{ 3.75f, 3.f, .75f };

		CHECK(big.isLongerThan(small));
		CHECK_FALSE(small.isLongerThan(big));

		CHECK(small.isShorterThan(big));
		CHECK_FALSE(big.isShorterThan(small));

		CHECK_FALSE(big.isLongerThan(big));
		CHECK_FALSE(big.isShorterThan(big));

		CHECK_FALSE(self.isUnitVector());
		CHECK(LibMath::Vector3{ 0.771516740f, 0.154303357f, 0.617213428f }.isUnitVector());
	}

	SECTION("Constant")
	{
		CHECK_VECTOR3(LibMath::Vector3::back(), glm::vec3(0.f, 0.f, -1.f));

		CHECK_VECTOR3(LibMath::Vector3::down(), glm::vec3(0.f, -1.f, 0.f));

		CHECK_VECTOR3(LibMath::Vector3::front(), glm::vec3(0.f, 0.f, 1.f));

		CHECK_VECTOR3(LibMath::Vector3::left(), glm::vec3(-1.f, 0.f, 0.f));

		CHECK_VECTOR3(LibMath::Vector3::one(), glm::vec3(1.f, 1.f, 1.f));

		CHECK_VECTOR3(LibMath::Vector3::right(), glm::vec3(1.f, 0.f, 0.f));

		CHECK_VECTOR3(LibMath::Vector3::up(), glm::vec3(0.f, 1.f, 0.f));

		CHECK_VECTOR3(LibMath::Vector3::zero(), glm::vec3(0.f, 0.f, 0.f));
	}

	SECTION("Arithmetic")
	{
		LibMath::Vector3 const small{ 2.5f, .5f, 2.f };
		LibMath::Vector3 const big{ 3.75f, 3.f, .75f };

		glm::vec3 const smallGlm{ 2.5f, .5f, 2.f };
		glm::vec3 const bigGlm{ 3.75f, 3.f, .75f };

		SECTION("Addition")
		{
			{
				LibMath::Vector3 sumAssignment = big;
				sumAssignment += small;

				glm::vec3 sumAssignmentGlm = bigGlm;
				sumAssignmentGlm += smallGlm;

				CHECK_VECTOR3(sumAssignment, sumAssignmentGlm);
			}

			{
				LibMath::Vector3 sum = big + small;

				glm::vec3 sumGlm = bigGlm + smallGlm;

				CHECK_VECTOR3(sum, sumGlm);
			}
		}

		SECTION("Opposite")
		{
			LibMath::Vector3 opposite = -LibMath::Vector3{ 3.7f, 3.f, .7f };

			glm::vec3 oppositeGlm = -glm::vec3{ 3.7f, 3.f, .7f };

			CHECK_VECTOR3(opposite, oppositeGlm);
		}

		SECTION("Substraction")
		{
			{
				LibMath::Vector3 differenceAssignment = big;
				differenceAssignment -= small;

				glm::vec3 differenceAssignmentGlm = bigGlm;
				differenceAssignmentGlm -= smallGlm;

				CHECK_VECTOR3(differenceAssignment, differenceAssignmentGlm);
			}

			{
				LibMath::Vector3 difference = big - small;

				glm::vec3 differenceGlm = bigGlm - smallGlm;

				CHECK_VECTOR3(difference, differenceGlm);
			}
		}

		SECTION("Multiplication")
		{
			{
				LibMath::Vector3 productAssignment = big;
				productAssignment *= small;

				glm::vec3 productAssignmentGlm = bigGlm;
				productAssignmentGlm *= smallGlm;

				CHECK_VECTOR3(productAssignment, productAssignmentGlm);
			}

			{
				LibMath::Vector3 product = big * small;

				glm::vec3 productGlm = bigGlm * smallGlm;

				CHECK_VECTOR3(product, productGlm);
			}

			{
				const float scalar = 2.f;

				{
					LibMath::Vector3 product = small * scalar;
					glm::vec3 productGlm = smallGlm * scalar;

					CHECK_VECTOR3(product, productGlm);
				}

				{
					LibMath::Vector3 productAssignment = small;
					productAssignment *= scalar;

					glm::vec3 productAssignmentGlm = smallGlm;
					productAssignmentGlm *= scalar;

					CHECK_VECTOR3(productAssignment, productAssignmentGlm);
				}
			}
		}

		SECTION("Division")
		{
			{
				LibMath::Vector3 quotientAssignment = big;
				quotientAssignment /= small;

				glm::vec3 quotientAssignmentGlm = bigGlm;
				quotientAssignmentGlm /= smallGlm;

				CHECK_VECTOR3(quotientAssignment, quotientAssignmentGlm);
			}

			{
				LibMath::Vector3 quotient = big / small;

				glm::vec3 quotientGlm = bigGlm / smallGlm;

				CHECK_VECTOR3(quotient, quotientGlm);
			}

			{
				const float scalar = 2.f;

				{
					LibMath::Vector3 quotient = small / scalar;
					glm::vec3 quotientGlm = smallGlm / scalar;

					CHECK_VECTOR3(quotient, quotientGlm);
				}

				{
					LibMath::Vector3 quotientAssignment = small;
					quotientAssignment /= scalar;

					glm::vec3 quotientAssignmentGlm = smallGlm;
					quotientAssignmentGlm /= scalar;

					CHECK_VECTOR3(quotientAssignment, quotientAssignmentGlm);
				}
			}
		}
	}

	SECTION("Transformation")
	{
		LibMath::Vector3 const origin{ 2.5f, .5f, 2.f };
		LibMath::Vector3 const transformation{ -2.f, 0.f, 1.25f };

		glm::vec4 const originGlm{ 2.5f, .5f, 2.f, 1.f };
		glm::vec3 const transformationGlm{ -2.f, 0.f, 1.25f };

		SECTION("Translation")
		{
			LibMath::Vector3 translate = origin;
			translate.translate(transformation);

			glm::vec4 translateGlm = glm::translate(transformationGlm) * originGlm;

			CHECK_VECTOR3(translate, translateGlm);
		}

		SECTION("Scale")
		{
			LibMath::Vector3 scale = origin;
			scale.scale(transformation);

			glm::vec4 scaleGlm = glm::scale(transformationGlm) * originGlm;

			CHECK_VECTOR3(scale, scaleGlm);
		}

		SECTION("Rotation")
		{
			SECTION("Euler Angle")
			{
				LibMath::Vector3 rotate = origin;
				rotate.rotate(LibMath::Radian{ transformation.m_x }, LibMath::Radian{ transformation.m_y }, LibMath::Radian{ transformation.m_z});


				glm::vec4 rotateGlm = glm::orientate4(transformationGlm) * originGlm;

				std::cout << "My Rotation: (" << rotate.m_x << ", " << rotate.m_y << ", " << rotate.m_z << ")\n";
				std::cout << "GLM Rotation: (" << rotateGlm.x << ", " << rotateGlm.y << ", " << rotateGlm.z << ")\n";


				CHECK_VECTOR3(rotate, rotateGlm);
			}

			SECTION("Axis")
			{
				LibMath::Vector3 rotate = origin;
				rotate.rotate(-3_rad, transformation);

				glm::vec4 rotateGlm = glm::rotate(-3.f, transformationGlm) * originGlm;

				CHECK_VECTOR3(rotate, rotateGlm);
			}

			SECTION("Quaternion")
			{
				// todo
			}
		}
	}

	SECTION("Functionality")
	{
		LibMath::Vector3 const base{ 2.5f, .5f, 2.f };
		LibMath::Vector3 const other{ 3.75f, 3.f, .75f };

		glm::vec3 const baseGlm{ 2.5f, .5f, 2.f };
		glm::vec3 const otherGlm{ 3.75f, 3.f, .75f };

		SECTION("Angle")
		{
			LibMath::Radian angle = base.angleFrom(other);

			float angleGlm = glm::angle(glm::normalize(baseGlm), glm::normalize(otherGlm));

			CHECK(angle.radian() == Catch::Approx(angleGlm));
		}

		SECTION("Cross")
		{
			LibMath::Vector3 cross = base.cross(other);

			glm::vec3 crossGlm = glm::cross(baseGlm, otherGlm);

			CHECK_VECTOR3(cross, crossGlm);
		}

		SECTION("Dot")
		{
			float dot = base.dot(other);

			float dotGlm = glm::dot(baseGlm, otherGlm);

			CHECK(dot == dotGlm);
		}

		SECTION("Distance")
		{
			{
				float distance = base.distanceFrom(other);

				float distanceGlm = glm::distance(baseGlm, otherGlm);

				CHECK(distance == Catch::Approx(distanceGlm));
			}

			{
				float distanceSquare = base.distanceSquaredFrom(other);

				float distanceSquareGlm = glm::distance2(baseGlm, otherGlm);

				CHECK(distanceSquare == Catch::Approx(distanceSquareGlm));
			}

			{
				float distance2D = base.distance2DFrom(other);

				float distance2DGlm = glm::distance(glm::vec2(baseGlm), glm::vec2(otherGlm));

				CHECK(distance2D == Catch::Approx(distance2DGlm));
			}

			{
				float distance2DSquare = base.distance2DSquaredFrom(other);

				float distance2DSquareGlm = glm::distance2(glm::vec2(baseGlm), glm::vec2(otherGlm));

				CHECK(distance2DSquare == Catch::Approx(distance2DSquareGlm));
			}
		}

		SECTION("Magnitude")
		{
			{
				float magnitude = base.magnitude();

				float magnitudeGlm = glm::length(baseGlm);

				CHECK(magnitude == Catch::Approx(magnitudeGlm));
			}

			{
				float magnitudeSquare = base.magnitudeSquared();

				float magnitudeSquareGlm = glm::length2(baseGlm);

				CHECK(magnitudeSquare == Catch::Approx(magnitudeSquareGlm));
			}
		}

		SECTION("Normal")
		{
			LibMath::Vector3 normalize = base;
			normalize.normalize();

			glm::vec3 normalizeGlm = glm::normalize(baseGlm);

			CHECK_VECTOR3(normalize, normalizeGlm);
		}

		SECTION("ProjectOnto")
		{
			LibMath::Vector3 project = base;
			project.projectOnto(other);

			glm::vec3 projectGlm = glm::proj(baseGlm, otherGlm);

			CHECK_VECTOR3(project, projectGlm);
		}

		SECTION("ReflectOnto")
		{
			LibMath::Vector3 reflect = base;
			reflect.reflectOnto(other);

			glm::vec3 reflectGlm = glm::reflect(baseGlm, glm::normalize(otherGlm));

			CHECK_VECTOR3(reflect, reflectGlm);
		}
	}

	SECTION("Extra")
	{
		LibMath::Vector3 const input{ 2.5f, -.5f, 2.f };
		{
			std::stringstream buffer;
			buffer << input;
			CHECK(buffer.str() == "{2.5,-0.5,2}");

			buffer << " extra";

			LibMath::Vector3 output;
			buffer >> output;
			CHECK(output == input);

			std::string extra;
			buffer >> extra;
			CHECK(extra == "extra");
		}

		{
			CHECK(input.string() == "{2.5,-0.5,2}");

			CHECK(input.stringLong() == "Vector3{ x:2.5, y:-0.5, z:2 }");
		}
	}

	SECTION("Debug")
	{
#if (defined _DEBUG) || (! defined NDEBUG)
		LibMath::Vector3 vector{ 2.5f, .5f, 2.f };

		CHECK_THROWS(vector[-1]);
		CHECK_THROWS(vector[3]);
#endif // DEBUG
	}
}

TEST_CASE("Vector4", "[.all][vector][Vector4]")
{
	SECTION("Constructors")
	{
		// Default constructor
		LibMath::Vector4 empty;
		CHECK(empty.m_x == 0.0f);
		CHECK(empty.m_y == 0.0f);
		CHECK(empty.m_z == 0.0f);
		CHECK(empty.m_k == 0.0f);

		// Single-value constructor
		LibMath::Vector4 singleParam(2.5f);
		CHECK(singleParam.m_x == 2.5f);
		CHECK(singleParam.m_y == 2.5f);
		CHECK(singleParam.m_z == 2.5f);
		CHECK(singleParam.m_k == 2.5f);

		// Parameterized constructor
		LibMath::Vector4 allParams(1.0f, 2.0f, 3.0f, 4.0f);
		CHECK(allParams.m_x == 1.0f);
		CHECK(allParams.m_y == 2.0f);
		CHECK(allParams.m_z == 3.0f);
		CHECK(allParams.m_k == 4.0f);

		// Copy constructor
		LibMath::Vector4 copy(allParams);
		CHECK(copy.m_x == 1.0f);
		CHECK(copy.m_y == 2.0f);
		CHECK(copy.m_z == 3.0f);
		CHECK(copy.m_k == 4.0f);

		// Vector3 + float constructor
		LibMath::Vector3 v3{ 1.f, 2.f, 3.f };
		LibMath::Vector4 fromV3{ v3, 4.f };
		CHECK(fromV3.m_x == 1.f);
		CHECK(fromV3.m_y == 2.f);
		CHECK(fromV3.m_z == 3.f);
		CHECK(fromV3.m_k == 4.f);
	}

	SECTION("Assignment Operator")
	{
		LibMath::Vector4 original(1.0f, 2.0f, 3.0f, 4.0f);
		LibMath::Vector4 assigned = original;

		CHECK(assigned.m_x == 1.0f);
		CHECK(assigned.m_y == 2.0f);
		CHECK(assigned.m_z == 3.0f);
		CHECK(assigned.m_k == 4.0f);
	}

	SECTION("Element Access (operator[])")
	{
		LibMath::Vector4 vec(1.0f, 2.0f, 3.0f, 4.0f);

		// Non-const access
		vec[0] = 5.0f;
		CHECK(vec[0] == 5.0f);
		CHECK(vec[1] == 2.0f);
		CHECK(vec[2] == 3.0f);
		CHECK(vec[3] == 4.0f);

		// Const access
		const LibMath::Vector4 constVec(1.0f, 2.0f, 3.0f, 4.0f);
		CHECK(constVec[0] == 1.0f);
		CHECK(constVec[1] == 2.0f);
		CHECK(constVec[2] == 3.0f);
		CHECK(constVec[3] == 4.0f);

		// Out-of-bounds access (if applicable)
#ifdef _DEBUG
		CHECK_THROWS(vec[-1]);
		CHECK_THROWS(vec[4]);
#endif
	}

	SECTION("Unit Vector Check (isUnit)")
	{
		LibMath::Vector4 unitVec(1.0f, 0.0f, 0.0f, 0.0f);
		CHECK(unitVec.isUnit());

		LibMath::Vector4 nonUnitVec(1.0f, 1.0f, 1.0f, 1.0f);
		CHECK_FALSE(nonUnitVec.isUnit());
	}

	SECTION("Dot Product (dotProduct)")
	{
		LibMath::Vector4 vec1(1.0f, 2.0f, 3.0f, 4.0f);
		LibMath::Vector4 vec2(2.0f, 3.0f, 4.0f, 5.0f);

		float dot = vec1.dotProduct(vec2);
		CHECK(dot == (1.0f * 2.0f + 2.0f * 3.0f + 3.0f * 4.0f + 4.0f * 5.0f));
	}

	SECTION("Magnitude (magnitude and magnitudeSquare)")
	{
		LibMath::Vector4 vec(1.0f, 2.0f, 3.0f, 4.0f);

		float magSquared = vec.magnitudeSquare();
		CHECK(magSquared == (1.0f * 1.0f + 2.0f * 2.0f + 3.0f * 3.0f + 4.0f * 4.0f));

		float mag = vec.magnitude();
		CHECK(mag == Catch::Approx(std::sqrt(magSquared)));
	}

	SECTION("Homogenize")
	{
		LibMath::Vector4 vec(2.0f, 4.0f, 6.0f, 2.0f);
		vec.homogenize();

		CHECK(vec.m_x == 1.0f);
		CHECK(vec.m_y == 2.0f);
		CHECK(vec.m_z == 3.0f);
		CHECK(vec.m_k == 1.0f);
	}

	SECTION("Equality Operator (operator==)")
	{
		LibMath::Vector4 vec1(1.0f, 2.0f, 3.0f, 4.0f);
		LibMath::Vector4 vec2(1.0f, 2.0f, 3.0f, 4.0f);
		LibMath::Vector4 vec3(2.0f, 3.0f, 4.0f, 5.0f);

		CHECK(vec1 == vec2);
		CHECK_FALSE(vec1 == vec3);
	}

	SECTION("Negation Operator (operator-)")
	{
		LibMath::Vector4 vec(1.0f, 2.0f, 3.0f, 4.0f);
		LibMath::Vector4 negated = -vec;

		CHECK(negated.m_x == -1.0f);
		CHECK(negated.m_y == -2.0f);
		CHECK(negated.m_z == -3.0f);
		CHECK(negated.m_k == -4.0f);
	}

	SECTION("Addition Operator (operator+)")
	{
		LibMath::Vector4 vec1(1.0f, 2.0f, 3.0f, 4.0f);
		LibMath::Vector4 vec2(2.0f, 3.0f, 4.0f, 5.0f);
		LibMath::Vector4 result = vec1 + vec2;

		CHECK(result.m_x == 3.0f);
		CHECK(result.m_y == 5.0f);
		CHECK(result.m_z == 7.0f);
		CHECK(result.m_k == 9.0f);
	}

	SECTION("Subtraction Operator (operator-)")
	{
		LibMath::Vector4 vec1(1.0f, 2.0f, 3.0f, 4.0f);
		LibMath::Vector4 vec2(2.0f, 3.0f, 4.0f, 5.0f);
		LibMath::Vector4 result = vec1 - vec2;

		CHECK(result.m_x == -1.0f);
		CHECK(result.m_y == -1.0f);
		CHECK(result.m_z == -1.0f);
		CHECK(result.m_k == -1.0f);
	}

	SECTION("Scalar Multiplication (operator*)")
	{
		LibMath::Vector4 vec(1.0f, 2.0f, 3.0f, 4.0f);
		LibMath::Vector4 result = vec * 2.0f;

		CHECK(result.m_x == 2.0f);
		CHECK(result.m_y == 4.0f);
		CHECK(result.m_z == 6.0f);
		CHECK(result.m_k == 8.0f);
	}

	SECTION("Scalar Division (operator/)")
	{
		LibMath::Vector4 vec(2.0f, 4.0f, 6.0f, 8.0f);
		LibMath::Vector4 result = vec / 2.0f;

		CHECK(result.m_x == 1.0f);
		CHECK(result.m_y == 2.0f);
		CHECK(result.m_z == 3.0f);
		CHECK(result.m_k == 4.0f);

		// Division by zero (if applicable)
#ifdef _DEBUG
		CHECK_THROWS(vec / 0.0f);
#endif
	}
}