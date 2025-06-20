#define	_USE_MATH_DEFINES
#define GLM_ENABLE_EXPERIMENTAL
#include <cmath>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/vec2.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_operation.hpp>

#include <iostream>

#include "LibMath/Matrix/Matrix2.h"
#include "LibMath/Matrix/Matrix3.h"
#include "LibMath/Matrix/Matrix4.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#define CHECK_MATRIX2(matrix , matrixGlm)do { \
  for ( int i = 0 ; i < 2 ; i ++ ) {       \
      for ( int j = 0 ; j < 2 ; j ++ )     \
        CHECK(matrix[i][j] == matrixGlm[i][j]) ;\
  }                                         \
} while ( 0 )

#define CHECK_MATRIX3(matrix , matrixGlm)do { \
  for ( int i = 0 ; i < 3 ; i ++ ) {       \
      for ( int j = 0 ; j < 3 ; j ++ ){     \
        CHECK(matrix[i][j] == Catch::Approx(matrixGlm[i][j])) ;\
      }\
  }                                         \
} while ( 0 )

#define CHECK_MATRIX4(matrix , matrixGlm)do { \
  for ( int i = 0 ; i < 4 ; i ++ ) {       \
      for ( int j = 0 ; j < 4 ; j ++ ){     \
        CHECK(matrix[i][j] == Catch::Approx(matrixGlm[i][j])) ;\
      }\
  }                                         \
} while ( 0 )

TEST_CASE("Matrix2Dx2", "[.all][matrix][Matrix2D]") {
    SECTION("Instantiation") {
        // Default constructor
        LibMath::Matrix2Dx2 matDefault;

        glm::mat2 matGlm{};
        CHECK_MATRIX2(matDefault, matGlm); // All elements should be 0.0f

        // Diagonal constructor
        LibMath::Matrix2Dx2 matDiagonal(2.0f); // Sets diagonal elements to 2.0, others to 0.0
        glm::mat2 matGlmDiagonal{ 2.0f };

        CHECK_MATRIX2(matDiagonal, matGlmDiagonal);

        // Full initialization constructor
        LibMath::Matrix2Dx2 matFull(1.0f, 2.0f, 3.0f, 4.0f);
        glm::mat2 matGlmFull(1.0f, 2.0f, 3.0f, 4.0f);

        CHECK_MATRIX2(matFull, matGlmFull);

        // Copy constructor
        LibMath::Matrix2Dx2 matCopy(matFull);
        CHECK(matCopy == matFull);

        // Assignment operator
        LibMath::Matrix2Dx2 matAssign;
        matAssign = matFull;
        CHECK(matAssign == matFull);
    }

    SECTION("Accessors") {
        LibMath::Matrix2Dx2 mat(1.0f, 2.0f, 3.0f, 4.0f);
        glm::mat2 matGlm(1.0f, 2.0f, 3.0f, 4.0f);

        CHECK(mat[0][0] == 1.0f);
        CHECK(mat[0][1] == 2.0f);
        CHECK(mat[1][0] == 3.0f);
        CHECK(mat[1][1] == 4.0f);
 

    }

    SECTION("Arithmetic") {
        LibMath::Matrix2Dx2 m1(1.0f, 2.0f, 3.0f, 4.0f);
        LibMath::Matrix2Dx2 m2(2.0f, 0.0f, 1.0f, 3.0f);

        glm::mat2 m1Glm(1.0f, 2.0f, 3.0f, 4.0f);
        glm::mat2 m2Glm(2.0f, 0.0f, 1.0f, 3.0f);

        // Addition
        LibMath::Matrix2Dx2 sum = m1 + m2;
        glm::mat2 sumGlm = m1Glm + m2Glm;

        CHECK_MATRIX2(sum, sumGlm);

        // Scalar Multiplication
        LibMath::Matrix2Dx2 scaled = m1 * 2.0f;
        glm::mat2 scaledGlm = m1Glm * 2.f;

        CHECK_MATRIX2(scaled, scaledGlm);

        // Matrix Multiplication
        LibMath::Matrix2Dx2 product = m1 * m2;
        glm::mat2 productGlm = m1Glm * m2Glm;

        CHECK_MATRIX2(product, productGlm);

        // Vector Multiplication
        LibMath::Vector2 vec(1.0f, 2.0f);
        glm::vec2 vecGlm(1.0f, 2.0f);

        LibMath::Vector2 result = m1 * vec;
        glm::vec2 resultGlm = m1Glm * vecGlm;

        CHECK(result.m_x == Catch::Approx(resultGlm.x)); // 1*1 + 2*2
        CHECK(result.m_y == Catch::Approx(resultGlm.y)); // 3*1 + 4*2
    }

    SECTION("Matrix Properties") {
        LibMath::Matrix2Dx2 mat(1.0f, 2.0f, 3.0f, 4.0f);
        glm::mat2 matGlm(1.0f, 2.0f, 3.0f, 4.0f);

        // Determinant
        float determinant = mat.determinant();
        float determinantGlm = glm::determinant(matGlm);

        CHECK(determinant == Catch::Approx(determinantGlm)); // 1*4 - 2*3 = -2

        // Transpose
        LibMath::Matrix2Dx2 transpose = mat.transpose();
        glm::mat2 transposeGlm = glm::transpose(matGlm);

        CHECK_MATRIX2(transpose, transposeGlm);

        // Adjugate
        LibMath::Matrix2Dx2 ajdugate = mat.adjugate();
        glm::mat2 adjugateGlm = glm::adjugate(matGlm);

        CHECK_MATRIX2(ajdugate, adjugateGlm);
       

        // Inverse (if determinant != 0)
        LibMath::Matrix2Dx2 inverse = mat.inverse();
        glm::mat2 inverseGlm = glm::inverse(matGlm);

        CHECK_MATRIX2(inverse, inverseGlm);
    }

    SECTION("Transformation") {
        // Identity Matrix
        LibMath::Matrix2Dx2 identity = LibMath::Matrix2Dx2().identity();
        glm::mat2 identityGlm{ 1.f };

        CHECK_MATRIX2(identity, identityGlm);

        //CHECK(identity == LibMath::Matrix2Dx2(1.0f, 0.0f, 0.0f, 1.0f));

        // Rotation Matrix
        LibMath::Radian rad(static_cast<float>(M_PI) / 2); // 90 degrees
        LibMath::Matrix2Dx2 rotation = LibMath::Matrix2Dx2().createRotation(rad);

        glm::mat3 identity3Glm{ 1.f };
        glm::mat3 rotationGlm = glm::rotate(identity3Glm, static_cast<float>(M_PI) / 2);


        // Expected matrix: (column-major)
        // [ 0, 1]
        // [-1, 0]

        CHECK_MATRIX2(rotation, rotationGlm);
        



        // Scaling Matrix
        LibMath::Vector2 vec(1.0f, 0.0f);
        LibMath::Vector2 scale(2.0f, 3.0f);

        LibMath::Matrix2Dx2 scaling = LibMath::Matrix2Dx2().createScale(scale);
        LibMath::Vector2 scaledVec = scaling * vec;

        glm::vec2 vecGlm{ 1.f, 0.f };
        glm::vec2 scaleGlm{ 2.f, 3.f };

        glm::mat3 scalingGlm = glm::scale(identity3Glm, scaleGlm);
        glm::vec2 scaledVecGlm = scaleGlm * vecGlm;
        
        CHECK(scaledVec.m_x == scaledVecGlm.x);
        CHECK(scaledVec.m_y == scaledVecGlm.y);
    }

    SECTION("Edge Cases") {
        // index out of range
        LibMath::Matrix2Dx2 zeroMatrix(1.0f, 2.0f, 3.0f, 4.0f);
        //CHECK_THROWS_AS(zeroMatrix[0][2], std::out_of_range);
        CHECK_THROWS_AS(zeroMatrix[3][1], std::out_of_range);

    }
}

TEST_CASE("Matrix2Dx3", "[.all][matrix][Matrix2D]") 
{

    SECTION("Instantiation") 
    {
        // Default constructor
        LibMath::Matrix2Dx3 matDefault;
        glm::mat3 glmDefault{};

        CHECK_MATRIX3(matDefault, glmDefault); // All elements should be 0


        // Diagonal constructor
        LibMath::Matrix2Dx3 matDiagonal(1.0f); // Diagonal elements set to 1
        glm::mat3 glmDiagonal{ 1.f };

        CHECK_MATRIX3(matDiagonal, glmDiagonal);

        // Full initialization constructor
        LibMath::Matrix2Dx3 matFull(1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f);

        glm::mat3 glmFull(1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f);

        CHECK_MATRIX3(matFull, glmFull);

        // Copy constructor
        LibMath::Matrix2Dx3 matCopy(matFull);
        glm::mat3 glmCopy(glmFull);

        CHECK_MATRIX3(matCopy, glmCopy);

        // Assignment operator
        LibMath::Matrix2Dx3 matAssign;
        matAssign = matFull;

        glm::mat3 glmAssign;
        glmAssign = glmFull;
        
        CHECK_MATRIX3(matAssign, glmAssign);
    }

    SECTION("Accessors") 
    {
        LibMath::Matrix2Dx3 mat(1.0f, 2.0f, 3.0f,
            4.0f, 5.0f, 6.0f,
            7.0f, 8.0f, 9.0f);

        // Row-wise access
        CHECK(mat[0][0] == 1.0f);
        CHECK(mat[0][1] == 2.0f);
        CHECK(mat[0][2] == 3.0f);

        CHECK(mat[1][0] == 4.0f);
        CHECK(mat[1][1] == 5.0f);
        CHECK(mat[1][2] == 6.0f);

        CHECK(mat[2][0] == 7.0f);
        CHECK(mat[2][1] == 8.0f);
        CHECK(mat[2][2] == 9.0f);

        mat[0][0] = 10.f;

        CHECK(mat[0][0] == 10.f);
    }

    SECTION("Arithmetic")
    {
        SECTION("Matrix Addition") 
        {

            LibMath::Matrix2Dx3 m1(1.0f, 2.0f, 3.0f,
                4.0f, 5.0f, 6.0f,
                7.0f, 8.0f, 9.0f);
            LibMath::Matrix2Dx3 m2(9.0f, 8.0f, 7.0f, 
                6.0f, 5.0f, 4.0f,
                3.0f, 2.0f, 1.0f);

            glm::mat3 m1Glm(1.0f, 2.0f, 3.0f, 
                4.0f, 5.0f, 6.0f,
                7.0f, 8.0f, 9.0f);

            glm::mat3 m2Glm(9.0f, 8.0f, 7.0f, 
                6.0f, 5.0f, 4.0f,
                3.0f, 2.0f, 1.0f); 

            LibMath::Matrix2Dx3 sum = m1 + m2;
            glm::mat3 glmSum = m1Glm + m2Glm;

            CHECK_MATRIX3(sum, glmSum);
        }

        SECTION("Matrix Multiplication") {

            LibMath::Matrix2Dx3 m1(1.0f, 2.0f, 3.0f,
                4.0f, 5.0f, 6.0f,
                7.0f, 8.0f, 9.0f);

            LibMath::Matrix2Dx3 m2(9.0f, 8.0f, 7.0f, 
                6.0f, 5.0f, 4.0f,
                3.0f, 2.0f, 1.0f);

            glm::mat3 m1Glm(1.0f, 2.0f, 3.0f, 
                4.0f, 5.0f, 6.0f,
                7.0f, 8.0f, 9.0f);

            glm::mat3 m2Glm(9.0f, 8.0f, 7.0f, 
                6.0f, 5.0f, 4.0f,
                3.0f, 2.0f, 1.0f);


            LibMath::Matrix2Dx3 product = m1 * m2;

            glm::mat3 glmProduct = m1Glm * m2Glm;

            CHECK_MATRIX3(product, glmProduct);
        }

    }
    
    SECTION("Transformation") 
    {
        // Identity Matrix
        LibMath::Matrix2Dx3 identity = LibMath::Matrix2Dx3().identity();
        glm::mat3 glmIdentity{ 1.f };
        CHECK_MATRIX3(identity, glmIdentity);

        {
            // Translation
            LibMath::Vector2 translation(2.0f, 3.0f);
            LibMath::Matrix2Dx3 translationMatrix = LibMath::Matrix2Dx3().createTranslation(translation);

            glm::vec2 glmTranslation(2.f, 3.f);
            glm::mat3 glmTranslationMatrix = glm::translate(glmIdentity, glmTranslation);

            CHECK_MATRIX3(translationMatrix, glmTranslationMatrix);

            // Rotation (90 degrees)
            LibMath::Radian rad(static_cast<float>(M_PI) / 2);
            LibMath::Matrix2Dx3 rotationMatrix = LibMath::Matrix2Dx3().createRotation(LibMath::Geometry2D::Point(0.0f, 0.0f), rad);

            glm::mat3 glmRotationMatrix = glm::rotate(glmIdentity, static_cast<float>(M_PI) / 2);

            CHECK_MATRIX3(rotationMatrix, glmRotationMatrix);

            // Scaling
            LibMath::Vector2 scale(2.0f, 3.0f);
            LibMath::Matrix2Dx3 scaleMatrix = LibMath::Matrix2Dx3().createScale(scale);

            glm::vec2 glmScale(2.f, 3.f);
            glm::mat3 glmScaleMatrix = glm::scale(glmIdentity, glmScale);

            CHECK_MATRIX3(scaleMatrix, glmScaleMatrix);
        }
      

        {
            // Transform
            LibMath::Vector2 t{ 0.f, 0.f }; // No translation
            LibMath::Radian r{ 0.f };         // No rotation
            LibMath::Vector2 s{ 1.f, 1.f };      // No scaling

            glm::vec2 tGlm(0.f, 0.f);
            glm::vec2 sGlm(1.f, 1.f);

            glm::mat3 glmTranslate = glm::translate(glmIdentity, tGlm);
            glm::mat3 glmRotate = glm::rotate(glmIdentity, 0.f);
            glm::mat3 glmScale = glm::scale(glmIdentity, sGlm);

            glm::mat3 glmTransform = glmRotate * glmScale * glmTranslate;

            // Call the function
            LibMath::Matrix2Dx3 result = LibMath::Matrix2Dx3().createTransform(t, r, s);

            // Compare the result with the expected matrix
            CHECK_MATRIX3(result, glmTransform);
        }

        {
            LibMath::Vector2 t(-5.0f, 4.0f); // Translation
            LibMath::Radian r(static_cast<float>(M_PI) / 2); // 90 degrees
            LibMath::Vector2 s(0.5f, 2.0f); // Scaling by 0.5 in X, 2 in Y

            LibMath::Matrix2Dx3 transform = LibMath::Matrix2Dx3().createTransform(t, r, s);

            glm::vec2 tGlm(-5.f, 4.f);
            float rGlm = static_cast<float>(M_PI) /2;
            glm::vec2 sGlm(0.5f, 2.f);

            glm::mat3 glmTranslate = glm::translate(glmIdentity, tGlm);
            glm::mat3 glmRotate = glm::rotate(glmTranslate, rGlm);
            glm::mat3 glmScale = glm::scale(glmRotate, sGlm);

 

            CHECK_MATRIX3(transform, glmScale);
        }
    }

    SECTION("Edge Cases") 
    {
        LibMath::Matrix2Dx3 mat(1.0f, 2.0f, 3.0f, 4.0f, 5.f, 1.f, 5.f, 4.f, 5.f);

        // Out-of-bounds access should throw
        CHECK_THROWS_AS(mat[0][3], std::out_of_range);
        CHECK_THROWS_AS(mat[3][0], std::out_of_range);

    }
    
}

TEST_CASE("Matrix3Dx3", "[.all][matrix][Matrix3D]")
{
    SECTION("Instantiation")
    {
        SECTION("Constructors")
        {
            // Default constructor
            LibMath::Matrix3Dx3 empty;
            glm::mat3 emptyGlm{};

            CHECK_MATRIX3(empty, emptyGlm);

            // Diagonal constructor
            LibMath::Matrix3Dx3 diagonal(2.0f);
            glm::mat3 diagonalGlm{ 2.f };

            CHECK_MATRIX3(diagonal, diagonalGlm);

            // Parameterized constructor
            LibMath::Matrix3Dx3 param(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
            glm::mat3 paramGlm(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

            CHECK_MATRIX3(param, paramGlm);


            // Copy constructor
            LibMath::Matrix3Dx3 copy(param);
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    CHECK(copy[i][j] == param[i][j]);
                }
            }
            glm::mat3 copyGlm(paramGlm);

            CHECK_MATRIX3(copy, copyGlm); // check similarity with glm
        }

        SECTION("Assignment Operator")
        {
            LibMath::Matrix3Dx3 original(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
            LibMath::Matrix3Dx3 assigned = original;

            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    CHECK(assigned[i][j] == original[i][j]);
                }
            }

            glm::mat3 originalGlm(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
            glm::mat3 assignedGlm = originalGlm;

            CHECK_MATRIX3(assigned, assignedGlm);
        }
    }

    SECTION("Accessors")
    {
        LibMath::Matrix3Dx3 mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

        // Non-const access
        mat[0][0] = 10.0f;
        CHECK(mat[0][0] == 10.0f);

        // Const access (if applicable)
        LibMath::Matrix3Dx3 const constMat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
        CHECK(constMat[0][0] == 1.0f);
    }

    SECTION("Matrix Properties")
    {
        SECTION("Transpose")
        {
            LibMath::Matrix3Dx3 mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
            LibMath::Matrix3Dx3 transposed = mat.transpose();

            glm::mat3 matGlm(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
            glm::mat3 transposedGlm = glm::transpose(matGlm);

            CHECK_MATRIX3(transposed, transposedGlm);
            
        }

        SECTION("Determinant")
        {
            LibMath::Matrix3Dx3 mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
            float det = mat.determinant();

            glm::mat3 matGlm(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
            float detGlm = glm::determinant(matGlm);

            // Expected determinant: 0 (since the matrix is singular)
            CHECK(det == detGlm);
        }

        SECTION("Minors")
        {
            LibMath::Matrix3Dx3 mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
            LibMath::Matrix3Dx3 minors = mat.minors();

            glm::mat3 matGlm(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
            glm::mat3 minorsGlm{};

            // Compute minors
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    // Create a 2x2 submatrix by excluding the i-th row and j-th column
                    glm::mat2 submatrix;
                    int sub_i = 0;
                    for (int row = 0; row < 3; ++row) {
                        if (row == i) continue; // Skip the i-th row
                        int sub_j = 0;
                        for (int col = 0; col < 3; ++col) {
                            if (col == j) continue; // Skip the j-th column
                            submatrix[sub_i][sub_j] = matGlm[row][col];
                            sub_j++;
                        }
                        sub_i++;
                    }

                    // Compute the determinant of the 2x2 submatrix
                    minorsGlm[i][j] = glm::determinant(submatrix);
                }
            }

            CHECK_MATRIX3(minors, minorsGlm);
        }

        SECTION("Cofactors")
        {
            LibMath::Matrix3Dx3 mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
            LibMath::Matrix3Dx3 cofactors = mat.cofators();
            
            glm::mat3 matGlm(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
            glm::mat3 cofactorsGlm{ };

            // Compute cofactors
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    // Create a 2x2 submatrix by excluding the i-th row and j-th column
                    glm::mat2 submatrix;
                    int sub_i = 0;
                    for (int row = 0; row < 3; ++row) {
                        if (row == i) continue; // Skip the i-th row
                        int sub_j = 0;
                        for (int col = 0; col < 3; ++col) {
                            if (col == j) continue; // Skip the j-th column
                            submatrix[sub_i][sub_j] = matGlm[col][row];
                            sub_j++;
                        }
                        sub_i++;
                    }

                    // Compute the minor (determinant of the 2x2 submatrix)
                    float minor = glm::determinant(submatrix);

                    // Apply the cofactor sign rule: (-1)^(i+j)
                    float sign = ((i + j) % 2 == 0) ? 1.0f : -1.0f;
                    cofactorsGlm[j][i] = sign * minor;
                }
            }

            CHECK_MATRIX3(cofactors, cofactorsGlm);

        }

        SECTION("Adjugate")
        {
            LibMath::Matrix3Dx3 mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
            LibMath::Matrix3Dx3 adjugate = mat.adjugate();

            glm::mat3 matGlm(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
            glm::mat3 cofactorsGlm{ };

            // Compute cofactors
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    // Create a 2x2 submatrix by excluding the i-th row and j-th column
                    glm::mat2 submatrix;
                    int sub_i = 0;
                    for (int row = 0; row < 3; ++row) {
                        if (row == i) continue; // Skip the i-th row
                        int sub_j = 0;
                        for (int col = 0; col < 3; ++col) {
                            if (col == j) continue; // Skip the j-th column
                            submatrix[sub_i][sub_j] = matGlm[col][row];
                            sub_j++;
                        }
                        sub_i++;
                    }

                    // Compute the minor (determinant of the 2x2 submatrix)
                    float minor = glm::determinant(submatrix);

                    // Apply the cofactor sign rule: (-1)^(i+j)
                    float sign = ((i + j) % 2 == 0) ? 1.0f : -1.0f;
                    cofactorsGlm[j][i] = sign * minor;
                }
            }
            glm::mat3 adjugateGlm = glm::transpose(cofactorsGlm);

            CHECK_MATRIX3(adjugate, adjugateGlm);
            
        }

        SECTION("Inverse")
        {
            LibMath::Matrix3Dx3 mat(1.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.8f, 0.0f, 0.0f, 1.0f); // Identity matrix
            LibMath::Matrix3Dx3 inverse = mat.inverse();

            glm::mat3 matGlm(1.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.8f, 0.0f, 0.0f, 1.0f);
            glm::mat3 inverseGlm = glm::inverse(matGlm);

            CHECK_MATRIX3(inverse, inverseGlm);
        }
    }

    SECTION("Transformation")
    {
        SECTION("Identity")
        {

            LibMath::Matrix3Dx3 identity = LibMath::Matrix3Dx3::identity();
            glm::mat3 identityGlm{ 1.f };

            CHECK_MATRIX3(identity, identityGlm);
        }
        SECTION("Create Transform")
        {
            LibMath::Vector2 translate(2.0f, 3.0f);
            LibMath::Radian rotation(static_cast<float>(M_PI) / 2.0f); // 90 degrees
            LibMath::Vector2 scale(2.0f, 3.0f);

            LibMath::Matrix3Dx3 transform = LibMath::Matrix3Dx3::createTransform(translate, rotation, scale);


            glm::mat3 glmIdentity{ 1.f };
            glm::vec2 translateGlm(2.f, 3.f);
            float rotationGlm = rotation.raw();
            glm::vec2 scaleGlm(2.f, 3.f);

            glm::mat3 glmTranslate = glm::translate(glmIdentity, translateGlm);
            glm::mat3 glmRotate = glm::rotate(glmTranslate, rotationGlm);
            glm::mat3 glmScale = glm::scale(glmRotate, scaleGlm);

            CHECK_MATRIX3(transform, glmScale);
        }

        SECTION("Create Rotation")
        {
            LibMath::Radian angle(static_cast<float>(M_PI) / 2.0f); // 90 degrees

            LibMath::Matrix3Dx3 def;

            LibMath::Matrix3Dx3 rotX = def.createRotationX(angle);
            LibMath::Matrix3Dx3 rotY = def.createRotationY(angle);
            LibMath::Matrix3Dx3 rotZ = def.createRotationZ(angle);
            
            glm::mat3 glmRotX = glm::mat3(glm::rotate(glm::mat4(1.f), angle.raw(), glm::vec3(1.f, 0.f, 0.f)));
            glm::mat3 glmRotY = glm::mat3(glm::rotate(glm::mat4(1.f), angle.raw(), glm::vec3(0.f, 1.f, 0.f)));
            glm::mat3 glmRotZ = glm::mat3(glm::rotate(glm::mat4(1.f), angle.raw(), glm::vec3(0.f, 0.f, 1.f)));


  
            CHECK_MATRIX3(rotX, glmRotX);
            CHECK_MATRIX3(rotY, glmRotY);
            CHECK_MATRIX3(rotZ, glmRotZ);
        }

        SECTION("Create Scale")
        {
            LibMath::Vector3 scale(2.0f, 3.0f, 4.0f);

            LibMath::Matrix3Dx3 def;

            LibMath::Matrix3Dx3 scaleMat = def.createScale(scale);

            glm::vec3 scaleGlm(2.f, 3.f, 4.f);

            glm::mat3 scaledGlm = glm::mat3(glm::scale(glm::mat4(1.f), scaleGlm));

            CHECK_MATRIX3(scaleMat, scaledGlm);
        }

    }
  
    SECTION("Arithmetic")
    {
        LibMath::Matrix3Dx3 mat1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
        LibMath::Matrix3Dx3 mat2(9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);

        glm::mat3 mat1Glm(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
        glm::mat3 mat2Glm(9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);


        // Addition
        LibMath::Matrix3Dx3 sum = mat1 + mat2;
        glm::mat3 sumGlm = mat1Glm + mat2Glm;

        CHECK_MATRIX3(sum, sumGlm);

        // Scalar multiplication
        LibMath::Matrix3Dx3 scaled = mat1 * 2.0f;
        glm::mat3 scaledGlm = mat1Glm * 2.f;

        CHECK_MATRIX3(scaled, scaledGlm);

        // Matrix multiplication
        LibMath::Matrix3Dx3 product = mat1 * mat2;
        glm::mat3 productGlm = mat1Glm * mat2Glm;

        CHECK_MATRIX3(product, productGlm);

        // Vector multiplication
        LibMath::Vector3 vec(1.0f, 2.0f, 3.0f);
        LibMath::Vector3 result = mat1 * vec;

        glm::vec3 vecGlm(1.f, 2.f, 3.f);
        glm::vec3 resultGlm = mat1Glm * vecGlm;

        CHECK(result.m_x == resultGlm.x);
        CHECK(result.m_y == resultGlm.y);
        CHECK(result.m_z == resultGlm.z);
    }

    SECTION("Edge Cases")
    {
        LibMath::Matrix3Dx3 mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

        // Out-of-bounds access (if applicable)
        CHECK_THROWS(mat[3][0]); // Row out of range
        CHECK_THROWS(mat[0][3]); // Column out of range
    }
}

TEST_CASE("Matrix4", "[.all][matrix][Matrix4]")
{
    SECTION("Instantiation")
    {
        SECTION("Constructors")
        {
            // Default constructor
            LibMath::Matrix4 empty;
            glm::mat4 emptyGlm{};

            CHECK_MATRIX4(empty, emptyGlm);

            // Diagonal constructor
            LibMath::Matrix4 diagonal(2.0f);
            glm::mat4 diagonalGlm(2.f);

            CHECK_MATRIX4(diagonal, diagonalGlm);

            // Parameterized constructor
            LibMath::Matrix4 param(
                1.0f, 2.0f, 3.0f, 4.0f,
                5.0f, 6.0f, 7.0f, 8.0f,
                9.0f, 10.0f, 11.0f, 12.0f,
                13.0f, 14.0f, 15.0f, 16.0f
            );
            
            glm::mat4 paramGlm(
                1.0f, 2.0f, 3.0f, 4.0f,
                5.0f, 6.0f, 7.0f, 8.0f,
                9.0f, 10.0f, 11.0f, 12.0f,
                13.0f, 14.0f, 15.0f, 16.0f
            );

            CHECK_MATRIX4(param, paramGlm);

            // Copy constructor
            LibMath::Matrix4 copy(param);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    CHECK(copy[i][j] == param[i][j]);
                }
            }

            glm::mat4 copyGlm(paramGlm); 

            CHECK_MATRIX4(copy, copyGlm); // Check similarity with glm
        }

        SECTION("Assignment Operator")
        {
            LibMath::Matrix4 original(
                1.0f, 2.0f, 3.0f, 4.0f,
                5.0f, 6.0f, 7.0f, 8.0f,
                9.0f, 10.0f, 11.0f, 12.0f,
                13.0f, 14.0f, 15.0f, 16.0f
            );
            LibMath::Matrix4 assigned = original;

            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    CHECK(assigned[i][j] == original[i][j]);
                }
            }

            glm::mat4 originalGlm(
                1.0f, 2.0f, 3.0f, 4.0f,
                5.0f, 6.0f, 7.0f, 8.0f,
                9.0f, 10.0f, 11.0f, 12.0f,
                13.0f, 14.0f, 15.0f, 16.0f
            );

            glm::mat4 assignedGlm = originalGlm;

            CHECK_MATRIX4(assigned, assignedGlm);
        }
    }

    SECTION("Accessor")
    {
        LibMath::Matrix4 mat(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        );

        // Non-const access
        mat[0][0] = 10.0f;
        CHECK(mat[0][0] == 10.0f);

    }

    SECTION("Matrix Properties")
    {
        SECTION("Transpose")
        {
            LibMath::Matrix4 mat(
                1.0f, 2.0f, 3.0f, 4.0f,
                5.0f, 6.0f, 7.0f, 8.0f,
                9.0f, 10.0f, 11.0f, 12.0f,
                13.0f, 14.0f, 15.0f, 16.0f
            );

            glm::mat4 matGlm( 
                1.0f, 2.0f, 3.0f, 4.0f,
                5.0f, 6.0f, 7.0f, 8.0f,
                9.0f, 10.0f, 11.0f, 12.0f,
                13.0f, 14.0f, 15.0f, 16.0f
            );

            LibMath::Matrix4 transposed = mat.transpose();
            glm::mat4 transposedGlm = glm::transpose(matGlm);

            CHECK_MATRIX4(transposed, transposedGlm);
        }

        SECTION("Determinant")
        {
            LibMath::Matrix4 mat(
                1.0f, 2.0f, 3.0f, 4.0f,
                5.0f, 6.0f, 7.0f, 8.0f,
                9.0f, 10.0f, 18.0f, 12.0f,
                13.0f, 14.0f, 15.0f, 16.0f
            );
            float det = mat.determinant();

            glm::mat4 matGlm(
                1.0f, 2.0f, 3.0f, 4.0f,
                5.0f, 6.0f, 7.0f, 8.0f,
                9.0f, 10.0f, 18.0f, 12.0f,
                13.0f, 14.0f, 15.0f, 16.0f
            );

            float detGlm = glm::determinant(matGlm);

            CHECK(det == detGlm);
        }

    }

    SECTION("Transformation")
    {
        SECTION("Identity")
        {
            LibMath::Matrix4 identity = LibMath::Matrix4::identity();
            glm::mat4 identityGlm{ 1.f };

            CHECK_MATRIX4(identity, identityGlm);
        }

        SECTION("Create Translate")
        {
            LibMath::Vector3 translate(2.0f, 3.0f, 4.0f);
            LibMath::Matrix4 translation = LibMath::Matrix4::createTranslate(translate);

            glm::vec3 translateGlm(2.f, 3.f, 4.f);
            glm::mat4 translationGlm = glm::translate(glm::mat4{ 1.f }, translateGlm);

            CHECK_MATRIX4(translation, translationGlm);
        }

        SECTION("Create Rotation X")
        {
            LibMath::Radian angle(static_cast<float>(M_PI) / 2.0f); // 90 degrees
            LibMath::Matrix4 rotation = LibMath::Matrix4::createRotationX(angle);

            glm::mat4 rotationGlm = glm::rotate(glm::mat4{ 1.f }, angle.raw(), glm::vec3(1.f, 0.f, 0.f));

            CHECK_MATRIX4(rotation, rotationGlm);

        }

        SECTION("Create Rotation Y")
        {
            LibMath::Radian angle(static_cast<float>(M_PI) / 2.0f); // 90 degrees
            LibMath::Matrix4 rotation = LibMath::Matrix4::createRotationY(angle);

            glm::mat4 rotationGlm = glm::rotate(glm::mat4{ 1.f }, angle.raw(), glm::vec3(0.f, 1.f, 0.f));

            CHECK_MATRIX4(rotation, rotationGlm);


        }

        SECTION("Create Rotation Z")
        {
            LibMath::Radian angle(static_cast<float>(M_PI) / 2.0f); // 90 degrees
            LibMath::Matrix4 rotation = LibMath::Matrix4::createRotationZ(angle);

            glm::mat4 rotationGlm = glm::rotate(glm::mat4{ 1.f }, angle.raw(), glm::vec3(0.f, 0.f, 1.f));

            CHECK_MATRIX4(rotation, rotationGlm);

        }

        SECTION("Create Scale")
        {
            LibMath::Vector3 scale(2.0f, 3.0f, 4.0f);
            LibMath::Matrix4 scaling = LibMath::Matrix4::createScale(scale);

            glm::mat4 scalingGlm = glm::scale(glm::mat4(1.f), glm::vec3(2.f, 3.f, 4.f));

            CHECK_MATRIX4(scaling, scalingGlm);
        }
    }

    SECTION("Arithmetic")
    {
        LibMath::Matrix4 mat1(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        );
        LibMath::Matrix4 mat2(
            16.0f, 15.0f, 14.0f, 120.0f,
            12.0f, 11.0f, 10.0f, 9.0f,
            8.0f, 7.0f, 6.0f, 5.0f,
            4.0f, 3.0f, 2.0f, 1.0f
        );

        glm::mat4 mat1Glm( 
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        );

        glm::mat4 mat2Glm( 
            16.0f, 15.0f, 14.0f, 120.0f,
            12.0f, 11.0f, 10.0f, 9.0f,
            8.0f, 7.0f, 6.0f, 5.0f,
            4.0f, 3.0f, 2.0f, 1.0f
        );

        // Addition
        LibMath::Matrix4 sum = mat1 + mat2;
        glm::mat4 sumGlm = mat1Glm + mat2Glm;

        CHECK_MATRIX4(sum, sumGlm);

        // Scalar multiplication
        LibMath::Matrix4 scaled = mat1 * 2.0f;
        glm::mat4 scaledGlm = mat1Glm * 2.f;

        CHECK_MATRIX4(scaled, scaledGlm);

        // Matrix multiplication
        LibMath::Matrix4 product = mat1 * mat2;
        glm::mat4 productGlm = mat1Glm * mat2Glm;

        CHECK_MATRIX4(product, productGlm);
    }

    SECTION("Edge Cases")
    {
        LibMath::Matrix4 mat(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        );
        // Out-of-bounds access (if applicable)
        CHECK_THROWS(mat[4][0]); // Row out of range
        CHECK_THROWS(mat[0][4]); // Column out of range

    }
}