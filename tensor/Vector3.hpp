#ifndef HDB_VECTOR3_HPP
#define HDB_VECTOR3_HPP

#include "Vector.hpp"

#define operatorVector3(o)\
	constexpr Vector operator o (Vector vector) const {\
		return Vector(x o vector.x, y o vector.y, z o vector.z);\
	}\
	constexpr Vector operator o##= (Vector vector) {\
		return Vector(x o##= vector.x, y o##= vector.y, z o##= vector.z);\
	}

namespace hdb {

template <typename T>
class Vector<T, 3> {
public:
	constexpr Vector() {}

	constexpr Vector(T s) {
		x = s; y = s; z = s;
	}

	constexpr Vector(T x, T y, T z) {
		this->x = x; this->y = y; this->z = z;
	}

	operatorVector3(+);
	operatorVector3(-);
	operatorVector3(*);
	operatorVector3(/);

	constexpr Vector operator-() const {
		return Vector(-x, -y, -z);
	}

	constexpr Vector operator*(T s) const {
		return Vector(x * s, y * s, z * s);
	}

	constexpr Vector operator/(T s) const {
		T is = 1.0f / s;
		return Vector(x * is, y * is, z * is);
	}

	constexpr Vector normal() const {
		T p = (T)1 / sqrt(x * x + y * y + z * z);

		Vector ret = *this;

		ret *= p;

		return ret;
	}

	constexpr Vector normalize() {
		T p = (T)1 / sqrt(x * x + y * y + z * z);

		*this *= p;

		return *this;
	}

	static constexpr Vector normalize(Vector vector) {
		T p = (T)1 / sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);

		return vector * p;
	}

	constexpr T dot(Vector vector) const {
		return x * vector.x + y * vector.y + z * vector.z;
	}

	static constexpr T dot(Vector a, Vector b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	constexpr T magnitude() const {
		return sqrt(x * x + y * y + z * z);
	}

	constexpr Vector cross(Vector vector) const {
		return Vector(y * vector.z - z * vector.y, z * vector.x - x * vector.z, x * vector.y - y * vector.x);
	}

	static constexpr Vector cross(Vector a, Vector b) {
		return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	}
	static constexpr const unsigned int getDimension() { return 3; }

	union {
		T data[3];
		struct { T x, y, z; };
		struct { T r, g, b; };
	};
};

}

#endif
