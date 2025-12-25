#define	_USE_MATH_DEFINES
#define GLM_ENABLE_EXPERIMENTAL
#include <cmath>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/vec2.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_operation.hpp>

#include <iostream>

#include "LibMath/Quaternion.h"
#include "LibMath/Vector/Vector3.h"
#include "LibMath/Matrix/Matrix3.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Quaternion", "[.all][quaternion][Quaternion]")
{
    SECTION("Instantiation")
    {
        SECTION("Constructors")
        {
            // Default constructor
            LibMath::Quaternion empty;
            glm::quat emptyGlm{};

            CHECK(empty.m_w == Catch::Approx(emptyGlm.w));
            CHECK(empty.m_x == Catch::Approx(emptyGlm.x));
            CHECK(empty.m_y == Catch::Approx(emptyGlm.y));
            CHECK(empty.m_z == Catch::Approx(emptyGlm.z));

            // Parameterized constructor (x, y, z, w)
            LibMath::Quaternion param(0.5f, 0.5f, 0.5f, 0.5f);
            glm::quat paramGlm(0.5f, 0.5f, 0.5f, 0.5f); // glm: w, x, y, z

            CHECK(param.m_w == Catch::Approx(paramGlm.w));
            CHECK(param.m_x == Catch::Approx(paramGlm.x));
            CHECK(param.m_y == Catch::Approx(paramGlm.y));
            CHECK(param.m_z == Catch::Approx(paramGlm.z));

            // Copy constructor
            LibMath::Quaternion copy(param);
            CHECK(copy.m_x == param.m_x);
            CHECK(copy.m_y == param.m_y);
            CHECK(copy.m_z == param.m_z);
            CHECK(copy.m_w == param.m_w);

            // Angle-axis constructor
            LibMath::Radian angle(static_cast<float>(M_PI) / 2.0f); // 90 degrees
            LibMath::Vector3 axis(0.0f, 1.0f, 0.0f); // Y-axis
            LibMath::Quaternion angleAxis(angle, axis);

            glm::quat angleAxisGlm = glm::angleAxis(angle.raw(), glm::vec3(0.0f, 1.0f, 0.0f));

            CHECK(angleAxis.m_w == Catch::Approx(angleAxisGlm.w));
            CHECK(angleAxis.m_x == Catch::Approx(angleAxisGlm.x));
            CHECK(angleAxis.m_y == Catch::Approx(angleAxisGlm.y));
            CHECK(angleAxis.m_z == Catch::Approx(angleAxisGlm.z));

            // Euler angles constructor
            LibMath::Radian pitch(static_cast<float>(M_PI) / 4.0f);
            LibMath::Radian yaw(static_cast<float>(M_PI) / 6.0f);
            LibMath::Radian roll(static_cast<float>(M_PI) / 3.0f);
            LibMath::Quaternion euler(pitch, yaw, roll);

            glm::quat eulerGlm(glm::vec3(pitch.raw(), yaw.raw(), roll.raw()));

            CHECK(euler.m_w == Catch::Approx(eulerGlm.w));
            CHECK(euler.m_x == Catch::Approx(eulerGlm.x));
            CHECK(euler.m_y == Catch::Approx(eulerGlm.y));
            CHECK(euler.m_z == Catch::Approx(eulerGlm.z));
        }

        SECTION("Identity Quaternion")
        {
            LibMath::Quaternion identity = LibMath::Quaternion::identity();
            glm::quat identityGlm = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

            CHECK(identity.m_w == Catch::Approx(1.0f));
            CHECK(identity.m_x == Catch::Approx(0.0f));
            CHECK(identity.m_y == Catch::Approx(0.0f));
            CHECK(identity.m_z == Catch::Approx(0.0f));
            CHECK(identity.isUnit());
        }
    }

    SECTION("Accessor")
    {
        LibMath::Quaternion quat(1.0f, 2.0f, 3.0f, 4.0f);

        // Non-const access
        CHECK(quat[0] == Catch::Approx(1.0f)); // x
        CHECK(quat[1] == Catch::Approx(2.0f)); // y
        CHECK(quat[2] == Catch::Approx(3.0f)); // z
        CHECK(quat[3] == Catch::Approx(4.0f)); // w

        // Modify through accessor
        quat[0] = 10.0f;
        CHECK(quat[0] == Catch::Approx(10.0f));
        CHECK(quat.m_x == Catch::Approx(10.0f));

        // Test out of range access
        CHECK_THROWS_AS(quat[4], std::out_of_range);
    }

    SECTION("Quaternion Properties")
    {
        SECTION("Magnitude")
        {
            LibMath::Quaternion quat(1.0f, 2.0f, 3.0f, 4.0f);
            float mag = quat.magnitude();

            glm::quat quatGlm(4.0f, 1.0f, 2.0f, 3.0f);
            float magGlm = glm::length(quatGlm);

            CHECK(mag == Catch::Approx(magGlm));
            CHECK(mag == Catch::Approx(std::sqrt(30.0f)));
        }

        SECTION("Magnitude Square")
        {
            LibMath::Quaternion quat(1.0f, 2.0f, 3.0f, 4.0f);
            float magSq = quat.magnitudeSquare();

            CHECK(magSq == Catch::Approx(30.0f)); // 1^2 + 2^2 + 3^2 + 4^2
        }

        SECTION("Normalize")
        {
            LibMath::Quaternion quat(1.0f, 2.0f, 3.0f, 4.0f);
            quat.normalize();

            glm::quat quatGlm(4.0f, 1.0f, 2.0f, 3.0f);
            quatGlm = glm::normalize(quatGlm);

            CHECK(quat.m_w == Catch::Approx(quatGlm.w));
            CHECK(quat.m_x == Catch::Approx(quatGlm.x));
            CHECK(quat.m_y == Catch::Approx(quatGlm.y));
            CHECK(quat.m_z == Catch::Approx(quatGlm.z));
            CHECK(quat.magnitude() == Catch::Approx(1.0f));
            CHECK(quat.isUnit());
        }

        SECTION("Conjugate")
        {
            LibMath::Quaternion quat(1.0f, 2.0f, 3.0f, 4.0f);
            LibMath::Quaternion conj = quat.conjugate();

            glm::quat quatGlm(4.0f, 1.0f, 2.0f, 3.0f);
            glm::quat conjGlm = glm::conjugate(quatGlm);

            CHECK(conj.m_w == Catch::Approx(conjGlm.w));
            CHECK(conj.m_x == Catch::Approx(conjGlm.x));
            CHECK(conj.m_y == Catch::Approx(conjGlm.y));
            CHECK(conj.m_z == Catch::Approx(conjGlm.z));

            // Conjugate properties: w stays same, xyz negated
            CHECK(conj.m_w == Catch::Approx(quat.m_w));
            CHECK(conj.m_x == Catch::Approx(-quat.m_x));
            CHECK(conj.m_y == Catch::Approx(-quat.m_y));
            CHECK(conj.m_z == Catch::Approx(-quat.m_z));
        }

        SECTION("Inverse")
        {
            LibMath::Quaternion quat(1.0f, 2.0f, 3.0f, 4.0f);
            LibMath::Quaternion inv = quat.inverse();

            glm::quat quatGlm(4.0f, 1.0f, 2.0f, 3.0f);
            glm::quat invGlm = glm::inverse(quatGlm);

            CHECK(inv.m_w == Catch::Approx(invGlm.w));
            CHECK(inv.m_x == Catch::Approx(invGlm.x));
            CHECK(inv.m_y == Catch::Approx(invGlm.y));
            CHECK(inv.m_z == Catch::Approx(invGlm.z));

            // Test property: q * q^-1 = identity
            LibMath::Quaternion product = quat * inv;
            CHECK(product.m_w == Catch::Approx(1.0f));
            CHECK(product.m_x == Catch::Approx(0.0f).margin(0.0001f));
            CHECK(product.m_y == Catch::Approx(0.0f).margin(0.0001f));
            CHECK(product.m_z == Catch::Approx(0.0f).margin(0.0001f));
        }

        SECTION("Is Unit")
        {
            LibMath::Quaternion unit(0.0f, 0.0f, 0.0f, 1.0f);
            CHECK(unit.isUnit());

            LibMath::Quaternion notUnit(1.0f, 2.0f, 3.0f, 4.0f);
            CHECK_FALSE(notUnit.isUnit());

            notUnit.normalize();
            CHECK(notUnit.isUnit());
        }

        SECTION("Angle Between")
        {
            LibMath::Radian angle1(static_cast<float>(M_PI) / 4.0f);
            LibMath::Vector3 axis1(0.0f, 1.0f, 0.0f);
            LibMath::Quaternion quat1(angle1, axis1);

            LibMath::Radian angle2(static_cast<float>(M_PI) / 2.0f);
            LibMath::Vector3 axis2(0.0f, 1.0f, 0.0f);
            LibMath::Quaternion quat2(angle2, axis2);

            LibMath::Radian angleBetween = quat1.angleBetween(quat2);

            glm::quat quat1Glm = glm::angleAxis(angle1.raw(), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::quat quat2Glm = glm::angleAxis(angle2.raw(), glm::vec3(0.0f, 1.0f, 0.0f));
            float angleGlm = glm::angle(glm::inverse(quat1Glm) * quat2Glm);

            CHECK(angleBetween.raw() == Catch::Approx(angleGlm).margin(0.001f));
        }
    }

    SECTION("Rotation Operations")
    {
        SECTION("Rotate Vector")
        {
            // 90 degree rotation around Y-axis
            LibMath::Radian angle(static_cast<float>(M_PI) / 2.0f);
            LibMath::Vector3 axis(0.0f, 1.0f, 0.0f);
            LibMath::Quaternion quat(angle, axis);

            LibMath::Vector3 vec(1.0f, 0.0f, 0.0f);
            LibMath::Vector3 rotated = quat.rotate(vec);

            glm::quat quatGlm = glm::angleAxis(angle.raw(), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::vec3 vecGlm(1.0f, 0.0f, 0.0f);
            glm::vec3 rotatedGlm = quatGlm * vecGlm;

            CHECK(rotated.m_x == Catch::Approx(rotatedGlm.x).margin(0.0001f));
            CHECK(rotated.m_y == Catch::Approx(rotatedGlm.y).margin(0.0001f));
            CHECK(rotated.m_z == Catch::Approx(rotatedGlm.z).margin(0.0001f));
        }

        SECTION("To Matrix")
        {
            LibMath::Radian angle(static_cast<float>(M_PI) / 4.0f);
            LibMath::Vector3 axis(0.0f, 1.0f, 0.0f);
            LibMath::Quaternion quat(angle, axis);

            LibMath::Matrix3 mat = quat.toMatrix();

            glm::quat quatGlm = glm::angleAxis(angle.raw(), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat3 matGlm = glm::mat3_cast(quatGlm);

            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    CHECK(mat[i][j] == Catch::Approx(matGlm[i][j]).margin(0.0001f));
                }
            }
        }
    }

    SECTION("Interpolation")
    {
        SECTION("SLERP - Spherical Linear Interpolation") 
        {
            LibMath::Quaternion qStart = LibMath::Quaternion::identity();

            LibMath::Radian angle(static_cast<float>(M_PI) / 2.0f);
            LibMath::Vector3 axis(0.0f, 1.0f, 0.0f);
            LibMath::Quaternion qEnd(angle, axis);

            // Interpolate at midpoint
            LibMath::Quaternion qMid = LibMath::Quaternion::slerp(qStart, qEnd, 0.5f);

            glm::quat qStartGlm = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
            glm::quat qEndGlm = glm::angleAxis(angle.raw(), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::quat qMidGlm = glm::slerp(qStartGlm, qEndGlm, 0.5f);

            CHECK(qMid.m_w == Catch::Approx(qMidGlm.w).margin(0.001f));
            CHECK(qMid.m_x == Catch::Approx(qMidGlm.x).margin(0.001f));
            CHECK(qMid.m_y == Catch::Approx(qMidGlm.y).margin(0.001f));
            CHECK(qMid.m_z == Catch::Approx(qMidGlm.z).margin(0.001f));

            // Test boundary conditions
            LibMath::Quaternion qStart2 = LibMath::Quaternion::slerp(qStart, qEnd, 0.0f);
            CHECK(qStart2 == qStart);

            LibMath::Quaternion qEnd2 = LibMath::Quaternion::slerp(qStart, qEnd, 1.0f);
            CHECK(qEnd2.m_w == Catch::Approx(qEnd.m_w));
            CHECK(qEnd2.m_x == Catch::Approx(qEnd.m_x));
            CHECK(qEnd2.m_y == Catch::Approx(qEnd.m_y));
            CHECK(qEnd2.m_z == Catch::Approx(qEnd.m_z));
        }

        SECTION("NLERP - Normalized Linear Interpolation")
        {
            LibMath::Quaternion qStart = LibMath::Quaternion::identity();

            LibMath::Radian angle(static_cast<float>(M_PI) / 2.0f);
            LibMath::Vector3 axis(0.0f, 1.0f, 0.0f);
            LibMath::Quaternion qEnd(angle, axis);

            LibMath::Quaternion qMid = LibMath::Quaternion::nlerp(qStart, qEnd, 0.5f);

            // NLERP result should be normalized
            CHECK(qMid.isUnit());

            // Test boundary conditions
            LibMath::Quaternion qStart2 = LibMath::Quaternion::nlerp(qStart, qEnd, 0.0f);
            CHECK(qStart2 == qStart);

            LibMath::Quaternion qEnd2 = LibMath::Quaternion::nlerp(qStart, qEnd, 1.0f);
            CHECK(qEnd2.m_w == Catch::Approx(qEnd.m_w));
            CHECK(qEnd2.m_x == Catch::Approx(qEnd.m_x));
            CHECK(qEnd2.m_y == Catch::Approx(qEnd.m_y));
            CHECK(qEnd2.m_z == Catch::Approx(qEnd.m_z));
        }
    }

    SECTION("Arithmetic Operations")
    {
        SECTION("Quaternion Multiplication")
        {
            LibMath::Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
            LibMath::Quaternion q2(5.0f, 6.0f, 7.0f, 8.0f);

            LibMath::Quaternion product = q1 * q2;

            glm::quat q1Glm(4.0f, 1.0f, 2.0f, 3.0f);
            glm::quat q2Glm(8.0f, 5.0f, 6.0f, 7.0f);
            glm::quat productGlm = q1Glm * q2Glm;

            CHECK(product.m_w == Catch::Approx(productGlm.w));
            CHECK(product.m_x == Catch::Approx(productGlm.x));
            CHECK(product.m_y == Catch::Approx(productGlm.y));
            CHECK(product.m_z == Catch::Approx(productGlm.z));
        }

        SECTION("Quaternion Addition")
        {
            LibMath::Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
            LibMath::Quaternion q2(5.0f, 6.0f, 7.0f, 8.0f);

            LibMath::Quaternion sum = q1 + q2;

            CHECK(sum.m_x == Catch::Approx(6.0f));
            CHECK(sum.m_y == Catch::Approx(8.0f));
            CHECK(sum.m_z == Catch::Approx(10.0f));
            CHECK(sum.m_w == Catch::Approx(12.0f));
        }

        SECTION("Scalar Multiplication")
        {
            LibMath::Quaternion quat(1.0f, 2.0f, 3.0f, 4.0f);
            LibMath::Quaternion scaled = quat * 2.0f;

            CHECK(scaled.m_x == Catch::Approx(2.0f));
            CHECK(scaled.m_y == Catch::Approx(4.0f));
            CHECK(scaled.m_z == Catch::Approx(6.0f));
            CHECK(scaled.m_w == Catch::Approx(8.0f));
        }

        SECTION("Equality Operator")
        {
            LibMath::Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
            LibMath::Quaternion q2(1.0f, 2.0f, 3.0f, 4.0f);
            LibMath::Quaternion q3(5.0f, 6.0f, 7.0f, 8.0f);

            CHECK(q1 == q2);
            CHECK_FALSE(q1 == q3);
        }
    }

    SECTION("Edge Cases")
    {
        SECTION("Zero Quaternion")
        {
            LibMath::Quaternion zero;

            CHECK(zero.m_x == Catch::Approx(0.0f));
            CHECK(zero.m_y == Catch::Approx(0.0f));
            CHECK(zero.m_z == Catch::Approx(0.0f));
            CHECK(zero.m_w == Catch::Approx(0.0f));
            CHECK(zero.magnitude() == Catch::Approx(0.0f));
            CHECK_FALSE(zero.isUnit());
        }

        SECTION("Identity Quaternion Properties")
        {
            LibMath::Quaternion identity = LibMath::Quaternion::identity();

            // Identity has magnitude 1
            CHECK(identity.magnitude() == Catch::Approx(1.0f));
            CHECK(identity.isUnit());

            // Multiplying by identity doesn't change quaternion
            LibMath::Quaternion quat(1.0f, 2.0f, 3.0f, 4.0f);
            LibMath::Quaternion product = quat * identity;

            CHECK(product.m_x == Catch::Approx(quat.m_x));
            CHECK(product.m_y == Catch::Approx(quat.m_y));
            CHECK(product.m_z == Catch::Approx(quat.m_z));
            CHECK(product.m_w == Catch::Approx(quat.m_w));

            // Rotating by identity doesn't change vector
            LibMath::Vector3 vec(1.0f, 2.0f, 3.0f);
            LibMath::Vector3 rotated = identity.rotate(vec);

            CHECK(rotated.m_x == Catch::Approx(vec.m_x));
            CHECK(rotated.m_y == Catch::Approx(vec.m_y));
            CHECK(rotated.m_z == Catch::Approx(vec.m_z));
        }

        SECTION("Normalized Axis for Angle-Axis")
        {
            // Non-normalized axis should still work
            LibMath::Radian angle(static_cast<float>(M_PI) / 4.0f);
            LibMath::Vector3 nonNormalAxis(2.0f, 0.0f, 0.0f);

            CHECK_NOTHROW(LibMath::Quaternion(angle, nonNormalAxis));
        }

        SECTION("Small Angle Rotations")
        {
            LibMath::Radian smallAngle(0.001f);
            LibMath::Vector3 axis(0.0f, 1.0f, 0.0f);
            LibMath::Quaternion quat(smallAngle, axis);

            // Should still be close to identity
            CHECK(quat.m_w == Catch::Approx(1.0f).margin(0.01f));
        }

        SECTION("180 Degree Rotation")
        {
            LibMath::Radian angle(static_cast<float>(M_PI));
            LibMath::Vector3 axis(0.0f, 1.0f, 0.0f);
            LibMath::Quaternion quat(angle, axis);

            glm::quat quatGlm = glm::angleAxis(static_cast<float>(M_PI), glm::vec3(0.0f, 1.0f, 0.0f));

            CHECK(quat.m_w == Catch::Approx(quatGlm.w).margin(0.0001f));
            CHECK(quat.m_x == Catch::Approx(quatGlm.x).margin(0.0001f));
            CHECK(quat.m_y == Catch::Approx(quatGlm.y).margin(0.0001f));
            CHECK(quat.m_z == Catch::Approx(quatGlm.z).margin(0.0001f));
        }

        SECTION("Multiple Rotations Concatenation")
        {
            // Rotate 45 degrees around Y, then 45 degrees around X
            LibMath::Radian angle(static_cast<float>(M_PI) / 4.0f);
            LibMath::Quaternion rotY(angle, LibMath::Vector3(0.0f, 1.0f, 0.0f));
            LibMath::Quaternion rotX(angle, LibMath::Vector3(1.0f, 0.0f, 0.0f));

            LibMath::Quaternion combined = rotY * rotX;

            glm::quat rotYGlm = glm::angleAxis(angle.raw(), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::quat rotXGlm = glm::angleAxis(angle.raw(), glm::vec3(1.0f, 0.0f, 0.0f));
            glm::quat combinedGlm = rotYGlm * rotXGlm;

            CHECK(combined.m_w == Catch::Approx(combinedGlm.w).margin(0.0001f));
            CHECK(combined.m_x == Catch::Approx(combinedGlm.x).margin(0.0001f));
            CHECK(combined.m_y == Catch::Approx(combinedGlm.y).margin(0.0001f));
            CHECK(combined.m_z == Catch::Approx(combinedGlm.z).margin(0.0001f));
        }
    }
}