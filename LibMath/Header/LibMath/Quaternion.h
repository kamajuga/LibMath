#ifndef LIBMATH_QUATERNION_H_
#define LIBMATH_QUATERNION_H_


namespace LibMath
{
	class Radian;
	class Vector3;
	class Matrix3;

	class Quaternion
	{
	public:
		Quaternion() = default;										// set all component to 0
		Quaternion(float x, float y, float z, float w);				// set all component individually
		Quaternion(Quaternion const& other);						// copy all component
		Quaternion(Radian rad, Vector3 vec);						// create rotation from an angle and an axis
		Quaternion(Vector3 vec);						
		Quaternion(Radian rad_x, Radian rad_y, Radian rad_z);					// create rotation from euler angles
		~Quaternion() = default;

		float magnitude(void) const;
		float magnitudeSquare(void) const;

		void normalize(void);

		Quaternion conjugate(void);

		Quaternion inverse(void);

		Radian angleBetween(Quaternion const& other) const;

		Vector3 rotate(Vector3 const& vec);

		Matrix3 toMatrix(void);

		bool isUnit(void) const;

		static Quaternion	identity();						// todo: return a valid quaternion with a rotation of 0
		static Quaternion	slerp(Quaternion const& qStart, Quaternion const& qEnd, float t);
		static Quaternion	nlerp(Quaternion const& qStart, Quaternion const& qEnd, float t);

		float& operator[](unsigned int index);

		float operator[](unsigned int index) const;

		float m_x = 0.f;
		float m_y = 0.f;
		float m_z = 0.f;
		float m_w = 0.f;				// Real part
	};

	Quaternion	operator*(Quaternion const& q1, Quaternion const& q2);					// todo:
	Quaternion	operator+(Quaternion const& q1, Quaternion const& q2);
	Quaternion	operator*(Quaternion const& q, float const& scalair);
	bool		operator==(Quaternion const& q1, Quaternion const& q2);

}

#endif // !LIBMATH_QUATERNION_H_
