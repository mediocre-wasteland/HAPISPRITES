////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	Vector.h
//
// summary:	Declares the vector class
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace HAPISPACE {

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// A vector. A basic vector or point type Performance wise is best passed by value not const
	/// reference.
	/// </summary>
	///
	/// <typeparam name="T">	Generic type parameter. </typeparam>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template <typename T>
	class Vector final
	{
	public:
		/// <summary>	A T to process. </summary>
		T x{ 0 };
		/// <summary>	A T to process. </summary>
		T y{ 0 };

		/// <summary>	Construct x and y values. </summary>
		Vector() noexcept {}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor. </summary>
		///
		/// <param name="bothIn">	The both in. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector(T bothIn) noexcept : x(bothIn), y(bothIn) {}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor. </summary>
		///
		/// <param name="xin">	The xin. </param>
		/// <param name="yin">	The yin. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector(T xin, T yin) noexcept : x(xin), y(yin) {}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts U to T. </summary>
		///
		/// <typeparam name="U">	Generic type parameter. </typeparam>
		/// <param name="vector">	The vector. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename U>
		explicit Vector(const Vector<U>& vector) noexcept :
			x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y)) {}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Add rhs to this. </summary>
		///
		/// <param name="rhs">	The right hand side. </param>
		///
		/// <returns>	The result of the operation. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector& operator+=(Vector rhs) 
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Subtract rhs from this. </summary>
		///
		/// <param name="rhs">	The right hand side. </param>
		///
		/// <returns>	The result of the operation. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector& operator-=(Vector rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Scale this. </summary>
		///
		/// <param name="mult">	The multiply. </param>
		///
		/// <returns>	The result of the operation. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector& operator*=(T mult)
		{
			x *= mult;
			y *= mult;
			return *this;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Scale this. </summary>
		///
		/// <param name="mult">	The multiply. </param>
		///
		/// <returns>	The result of the operation. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector& operator*=(Vector<T> mult)
		{
			x *= mult.x;
			y *= mult.y;
			return *this;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Divide this. </summary>
		///
		/// <param name="div">	The div. </param>
		///
		/// <returns>	The result of the operation. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector& operator/=(T div)
		{
			x /= div;
			y /= div;
			return *this;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Negate this. </summary>
		///
		/// <returns>	The result of the operation. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector operator-() const
		{
			return Vector{ -x,-y };
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Returns cosine of the angle between this and other. </summary>
		///
		/// <param name="other">	The other. </param>
		///
		/// <returns>	A float. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		float Dot(const Vector& other) const
		{			
			return x * other.x + y * other.y;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Calculates the 2D cross product of 2 vectors. </summary>
		///
		/// <param name="other">	The other. </param>
		///
		/// <returns>	A float. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		float Cross(const Vector& other) const
		{
			return (x * other.y) - (y * other.x);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Distance to other point vector from this point vector squared. </summary>
		///
		/// <param name="other">	The other. </param>
		///
		/// <returns>	A T. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		T DistanceBetweenSquared(const Vector<T> &other) const
		{
			return (other.x - x)*(other.x - x) + (other.y - y)*(other.y - y);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Distance to other point vector from this point vector. </summary>
		///
		/// <param name="other">	The other. </param>
		///
		/// <returns>	A float. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		float DistanceBetween(const Vector &other) const
		{
			return sqrt((float)DistanceBetweenSquared(other));
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Manhattan distance to other point vector from this point vector. </summary>
		///
		/// <param name="p2">	The second Vector. </param>
		///
		/// <returns>	An int. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		int ManhattanDistanceBetween(const Vector &p2) const
		{
			return (int)(abs(x - p2.x) + abs(y - p2.y));
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Length squared. </summary>
		///
		/// <returns>	A float. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		float LengthSquared() { return (float)(x*x + y*y); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets the length. </summary>
		///
		/// <returns>	A float. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		float Length() { return sqrt((float)(x*x + y*y)); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Scale this so vector length is newLength. </summary>
		///
		/// <param name="newLength">	Length of the new. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void ScaleToLength(T newLength)
		{
			float len{ Length() };
			if (len != 0)
			{
				x = T((float)x * newLength / len);
				y = T((float)y * newLength / len);
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Returns scaled so vector length is newLength. </summary>
		///
		/// <param name="newLength">	Length of the new. </param>
		///
		/// <returns>	A Vector&lt;T&gt; </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector<T> ScaledToLength(T newLength)
		{
			Vector<T> ret{ *this };
			ret.ScaledToLength(newLength);
			return ret;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets the zero. </summary>
		///
		/// <returns>	A Vector&lt;T&gt; </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static Vector<T> Zero() { return Vector<T>{0, 0}; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Query if this object is zero. </summary>
		///
		/// <returns>	True if zero, false if not. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool IsZero() const { return (x == 0 && y == 0); }

		/// <summary>	only relevant for a float vector. </summary>
		void Normalize()
		{
			float length{ Length() };
			if (length != 0)
			{
				x = T((float)x / length);
				y = T((float)y / length);
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Normal of this vector does not change this. </summary>
		///
		/// <returns>	A Vector&lt;float&gt; </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector<float> Normalized() const
		{
			Vector<float> ret((Vector<float>)*this);
			ret.Normalize();
			return ret;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Rotate by angle in radians Does not change this. </summary>
		///
		/// <param name="angle">	The angle. </param>
		///
		/// <returns>	A Vector. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector Rotated(float angle) const
		{
			Vector ret;

			ret.x = x * cos(angle) - y * sin(angle);
			ret.y = y * cos(angle) + x * sin(angle);

			return ret;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Rotate by angle in radians. </summary>
		///
		/// <param name="angle">	The angle. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void Rotate(float angle)
		{
			T oldX{ x };
			x = x * cos(angle) - y * sin(angle);
			y = y * cos(angle) + oldX * sin(angle);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Rotate around a point. </summary>
		///
		/// <param name="radians">	The radians. </param>
		/// <param name="origin"> 	The origin. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void Rotate(float radians, const Vector<T>& origin)
		{
			x -= origin.x; y -= origin.y;
			Rotate(radians);
			x += origin.x; y += origin.y;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Creates a random vector with x and y values between min and max. </summary>
		///
		/// <param name="minX">	The minimum x coordinate. </param>
		/// <param name="maxX">	The maximum x coordinate. </param>
		/// <param name="minY">	The minimum y coordinate. </param>
		/// <param name="maxY">	The maximum y coordinate. </param>
		///
		/// <returns>	A Vector. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static Vector Random(T minX, T maxX, T minY, T maxY)
		{
			return Vector(static_cast<T>(minX + rand() % (int)(maxX - minX)),
				static_cast<T>(minY + rand() % (int)(maxY - minY)));
		};

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Creates a random vector from 0 to max. </summary>
		///
		/// <param name="maxX">	The maximum x coordinate. </param>
		/// <param name="maxY">	The maximum y coordinate. </param>
		///
		/// <returns>	A Vector. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static Vector Random(T maxX, T maxY)
		{
			return Random(0, maxX, 0, maxY);
		};

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Creates a random directional vector (length is unity) </summary>
		///
		/// <returns>	A Vector. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static Vector RandomDirection()
		{
			Vector res{ (rand() % 100)-50.0f, (rand() % 100)-50.0f };
			res.Normalize();
			return res;
		};

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// implicit conversion Note: it is worth making this explicit sometimes to detect any uneeded
		/// casts automatically happening	(it happens a lot)
		/// </summary>
		///
		/// <returns>	The result of the operation. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename U> // explicit
			operator Vector<U>() const { return Vector<U>((U)x, U(y)); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Cast that converts the given std::ostream&amp; to a &lt;&lt;&lt;typename T&gt;
		/// </summary>
		///
		/// <param name="os">	[in,out] The output stream. </param>
		/// <param name="p"> 	A Vector&lt;T&gt; to process. </param>
		///
		/// <returns>	The result of the operation. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		friend std::ostream& operator<<(std::ostream& os, const Vector<T>& p);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Convert this object into a string representation. </summary>
		///
		/// <returns>	A std::string that represents this object. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::string ToString() const { std::stringstream str; str << *this; return str.str(); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets the up. </summary>
		///
		/// <returns>	A Vector&lt;T&gt; </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static Vector<T> Up() { return Vector<T>{0, -1}; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets the down. </summary>
		///
		/// <returns>	A Vector&lt;T&gt; </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static Vector<T> Down() { return Vector<T>{0, 1}; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets the left. </summary>
		///
		/// <returns>	A Vector&lt;T&gt; </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static Vector<T> Left() { return Vector<T>{-1, 0}; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets the right. </summary>
		///
		/// <returns>	A Vector&lt;T&gt; </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static Vector<T> Right() { return Vector<T>{1, 0}; }

		// No need for assignment operator or copy or move since default bitwise ones work fine (its just 8 bytes normally)
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Can be used with cout to output values to output pane and log. </summary>
	///
	/// <param name="os">	[in,out] The output stream. </param>
	/// <param name="p"> 	A Vector&lt;T&gt; to process. </param>
	///
	/// <returns>	The result of the operation. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template <typename T>
	inline std::ostream& operator<<(std::ostream& os, const Vector<T>& p)
	{
		os << "X: " << p.x << " Y: " << p.y;
		return os;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Equals. </summary>
	///
	/// <param name="lhs">	The left hand side. </param>
	/// <param name="rhs">	The right hand side. </param>
	///
	/// <returns>	The result of the operation. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template <typename T>
	inline bool operator==(const Vector<T>& lhs,const Vector<T>& rhs)
	{ 
		return (lhs.x == rhs.x && lhs.y == rhs.y); 
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Does not equal. </summary>
	///
	/// <param name="lhs">	The left hand side. </param>
	/// <param name="rhs">	The right hand side. </param>
	///
	/// <returns>	The result of the operation. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template <typename T>
	inline bool operator!=(Vector<T> lhs, Vector<T> rhs)
	{
		return !operator==(lhs, rhs); 
	}

	// Other comparison operators like <,>,<=,>= are meaningless when dealing with vectors
	// Unary operators are also meaningless

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Add two vector. </summary>
	///
	/// <param name="lhs">	The left hand side. </param>
	/// <param name="rhs">	The right hand side. </param>
	///
	/// <returns>	The result of the operation. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template <typename T>
	inline Vector<T> operator+(Vector<T> lhs, const Vector<T> &rhs)
	{
		lhs += rhs;
		return lhs;
	}	

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Subtract two vector. </summary>
	///
	/// <param name="lhs">	The left hand side. </param>
	/// <param name="rhs">	The right hand side. </param>
	///
	/// <returns>	The result of the operation. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template <typename T>
	inline Vector<T> operator-(Vector<T> lhs, const Vector<T> &rhs)
	{
		lhs -= rhs;
		return lhs;
	}	

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Multiplication operator. </summary>
	///
	/// <param name="s">  	An U to process. </param>
	/// <param name="rhs">	The right hand side. </param>
	///
	/// <returns>	The result of the operation. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template <typename T, typename U>
	inline Vector<T> operator*(const U &s, Vector<T> rhs)
	{
		return rhs *= (T)s;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Multiplication operator. </summary>
	///
	/// <param name="lhs">	The left hand side. </param>
	/// <param name="s">  	An U to process. </param>
	///
	/// <returns>	The result of the operation. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template <typename T, typename U>
	inline Vector<T> operator*(Vector<T> lhs, const U &s)
	{
		return lhs *= (T)s;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Multiplication operator. </summary>
	///
	/// <param name="lhs">	The left hand side. </param>
	/// <param name="s">  	A Vector&lt;U&gt; to process. </param>
	///
	/// <returns>	The result of the operation. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template <typename T, typename U>
	inline Vector<T> operator*(Vector<T> lhs, const Vector<U> &s)
	{
		return lhs *= s;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	divide vector. </summary>
	///
	/// <param name="lhs">	The left hand side. </param>
	/// <param name="s">  	An U to process. </param>
	///
	/// <returns>	The result of the operation. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template <typename T,typename U>
	inline Vector<T> operator/(Vector<T> lhs, const U &s)
	{
		return lhs /= (T)s;
	}

	/// <summary>	Helpers. </summary>
	using VectorI = Vector<int>;
	/// <summary>	The vector f. </summary>
	using VectorF = Vector<float>;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Reflect off surface described by normal, vectors must be floats. </summary>
	///
	/// <param name="v">	 	A VectorF to process. </param>
	/// <param name="normal">	The normal. </param>
	///
	/// <returns>	A VectorF. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	inline VectorF Reflect(const VectorF& v, const VectorF& normal)
	{
		VectorF res = normal * -2 * v.Dot(normal) + v;
		return res;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Convert from 2D to isometric. </summary>
	///
	/// <param name="v">	2D point to process. </param>
	///
	/// <returns>	Converted Point. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	inline VectorF TwoDToIsometric(const VectorF &v)
	{
		return VectorF{ v.x - v.y, (v.x + v.y) / 2.0f };
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Convert from isometric to 2D. </summary>
	///
	/// <param name="v">	Isometric point to process. </param>
	///
	/// <returns>	Converted Point. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	inline VectorF IsometricToTwoD(const VectorF &v)
	{
		return VectorF{ (2 * v.y + v.x) / 2.0f ,(2 * v.y - v.x) / 2.0f };
	}
}