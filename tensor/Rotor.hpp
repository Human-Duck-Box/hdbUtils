#ifndef HDB_ROTOR_HPP
#define HDB_ROTOR_HPP

#include "Vector4.hpp"
#include <cstring>

namespace hdb {

template <typename T>
class Rotor {
public:
	Rotor() {
		w = 1;
		yz = 0;
		zx = 0;
		xy = 0;
	}

	Rotor(T yz, T zx, T xy, T w) {
		this->yz = yz;
		this->zx = zx;
		this->xy = xy;
		this->w = w;
	}

	Rotor(Vector<T, 3> axis, T angle) {
		angle *= (T)0.5;
		this->w = cos(angle);

		axis *= cos(angle) * 2;
		std::memcpy(this, &axis, 3 * sizeof(T));
	}

	Rotor(Vector<T, 3> a, Vector<T, 3> b) {
		this->w = a.dot(b);

		decltype(a) bivector = a.cross(b);
		std::memcpy(this, &bivector, 3 * sizeof(T));
	}
	
	constexpr Rotor operator*(Rotor rotor) const {
		return {
			w * rotor.yz + xy * rotor.zx + yz * rotor.w + zx * rotor.xy,
			w * rotor.zx - xy * rotor.yz + yz * rotor.xy + zx * rotor.w,
			w * rotor.xy + xy * rotor.w - yz * rotor.zx + zx * rotor.yz,
			w * rotor.w - xy * rotor.xy - yz * rotor.yz - zx * rotor.zx
		};
	}

	constexpr Rotor operator*=(Rotor rotor) {
		return *this = *this * rotor;
	}

	constexpr Rotor operator-() const {
		return {
			-yz,
			-zx,
			-xy,
			w
		};
	}

	constexpr Vector<T, 3> rotate(Vector<T, 3> vector) const {
		Vector<T, 4> v = {
			w * vector.x + xy * vector.y - zx * vector.z,
			w * vector.y + yz * vector.z - xy * vector.x,
			w * vector.z + zx * vector.x - yz * vector.y,
			yz * vector.x + zx * vector.y + xy * vector.z
		};

		return {
			w * v.x + xy * v.y + yz * v.w - zx * v.z,
			w * v.y - xy * v.x + yz * v.z + zx * v.w,
			w * v.z + xy * v.w - yz * v.y + zx * v.x
		};
	}

	T yz, zx, xy, w;
};

typedef Rotor<float> Rotorf;
typedef Rotor<double> Rotord;

}

#endif
