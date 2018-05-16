#ifndef _UTIL_HPP_
#define _UTIL_HPP_

#include "engine.hpp"
#include "graphics.hpp"
#include "text.hpp"

namespace Engine {
	namespace Util {

		/*************************************************
		* 2D VECTOR CLASS                                *
		*************************************************/

		template <typename T> class Vector2 {
		public:
			T x;
			T y;

			Vector2();
			Vector2(T X, T Y);
			template <typename U> explicit Vector2(const Vector2<U>& vector);
		};

		template <typename T> Vector2<T> operator-(const Vector2<T>& v1);
		template <typename T> Vector2<T>& operator+=(Vector2<T>& v1, const Vector2<T>& v2);
		template <typename T> Vector2<T>& operator-=(Vector2<T>& v1, const Vector2<T>& v2);
		template <typename T> Vector2<T> operator+(const Vector2<T>& v1, const Vector2<T>& v2);
		template <typename T> Vector2<T> operator-(const Vector2<T>& v1, const Vector2<T>& v2);
		template <typename T> Vector2<T> operator*(const Vector2<T>& v1, T t1);
		template <typename T> Vector2<T> operator*(T t1, const Vector2<T>& v1);
		template <typename T> Vector2<T>& operator*=(Vector2<T>& v1, T t1);
		template <typename T> Vector2<T> operator/(T t1, const Vector2<T>& v1);
		template <typename T> Vector2<T>& operator/=(Vector2<T>& v1, T t1);
		template <typename T> Vector2<T> operator==(const Vector2<T>& v1, const Vector2<T>& v2);
		template <typename T> Vector2<T> operator!=(const Vector2<T>& v1, const Vector2<T>& v2);

		template <typename T> inline Vector2<T>::Vector2() {
			x = T(0);
			y = T(0);
		}

		template <typename T> inline Vector2<T>::Vector2(T X, T Y) {
			x = T(X);
			y = T(Y);
		}

		template <typename T> template <typename U> inline Vector2<T>::Vector2(const Vector2<U>& vector) {
			x(static_cast<T>(vector.x));
			x(static_cast<T>(vector.y));
		}

		template <typename T> inline Vector2<T> operator-(const Vector2<T>& v1) {
			return Vector2<T>(-v1.x, -v1.y);
		}	

		template <typename T> inline Vector2<T>& operator+=(Vector2<T>& v1, const Vector2<T>& v2) {
			v1.x += v2.x;
			v1.y += v2.y;

			return v1;
		}

		template <typename T> inline Vector2<T>& operator-=(Vector2<T>& v1, const Vector2<T>& v2) {
			v1.x -= v2.x;
			v1.y -= v2.y;

			return v1;
		}

		template <typename T> inline Vector2<T> operator+(const Vector2<T>& v1, const Vector2<T>& v2) {
			return Vector2<T>(v1.x + v2.x, v1.y + v2.y);
		}

		template <typename T> inline Vector2<T> operator-(const Vector2<T>& v1, const Vector2<T>& v2) {
			return Vector2<T>(v1.x - v2.x, v1.y - v2.y);
		}

		template <typename T> inline Vector2<T> operator*(const Vector2<T>& v1, T t1) {
			return Vector2<T>(v1.x * t1, v1.y * t1);
		}

		template <typename T> inline Vector2<T> operator*(T t1, const Vector2<T>& v1) {
			return Vector2<T>(v1.x * t1, v1.y * t1);
		}

		template <typename T> inline Vector2<T>& operator*=(Vector2<T>& v1, T t1) {
			v1.x *= t1;
			v1.y *= t1;

			return v1;
		}

		template <typename T> inline Vector2<T> operator/(const Vector2<T>& v1, T t1) {
			return Vector2<T>(v1.x / t1, v1.y / t1);
		}

		template <typename T> inline Vector2<T>& operator/=(Vector2<T>& v1, T t1) {
			v1.x /= t1;
			v1.y /= t1;

			return v1;
		}

		template <typename T> inline Vector2<T> operator==(const Vector2<T>& v1, const Vector2<T>& v2) {
			return (v1.x == v2.x) && (v1.y == v2.y);
		}

		template <typename T> inline Vector2<T> operator!=(const Vector2<T>& v1, const Vector2<T>& v2) {
			return (v1.x != v2.x) || (v1.y != v2.y);
		}

		typedef Vector2<int> Vector2i;
		typedef Vector2<unsigned int> Vector2u;
		typedef Vector2<long> Vector2l;
		typedef Vector2<unsigned long> Vector2ul;
		typedef Vector2<float> Vector2f;
		typedef Vector2<double> Vector2d;
              
        /*************************************************
		* UTILITY FUNCTIONS                              *
		*************************************************/
         
         void drawFpsCounter (float frameTime, const Graphics::ColorRGB& color = Graphics::RGB_Yellow);
         
    }
}

#endif
