////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	Colour.h
//
// summary:	Declares the colour class
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace HAPISPACE {

	// BYTE colour
	class Colour255 final
	{
	public:
		BYTE red{ 255 };
		BYTE green{ 255 };
		BYTE blue{ 255 };
		BYTE alpha{ 255 };

		// Constructor 1 - Colour defaults to white	
		Colour255()  noexcept = default;

		// Constructor 2 - Colour channels passed in, alpha defaults to 255 (opaque) if not provided
		Colour255(BYTE r, BYTE g, BYTE b, BYTE a = 255) noexcept : red(r), green(g), blue(b), alpha(a) {}

		// Constructor 3 - gray
		Colour255(BYTE gray, BYTE a = 255)  noexcept : red(gray), green(gray), blue(gray), alpha(a) {}

		// Helpers
		static const Colour255 BLACK;
		static const Colour255 WHITE;
		static const Colour255 RED;
		static const Colour255 GREEN;
		static const Colour255 BLUE;
		static const Colour255 YELLOW;
		static const Colour255 CYAN;
		static const Colour255 MAGENTA;
		static const Colour255 HORRID_PINK;
		static const Colour255 ZERO; // 0,0,0,0

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Returns a random colour. </summary>
		///
		/// <returns>	A Colour255. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static Colour255 Random() { return Colour255(rand() % 255, rand() % 255, rand() % 255); }

		friend std::ostream& operator<<(std::ostream& os, const Colour255& col);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Convert this object into a string representation. </summary>
		///
		/// <returns>	A std::string that represents this object. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::string ToString() const { std::stringstream str; str << *this; return str.str(); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Convert to legacy format. Cannot be done via a cast operator unfortunately.
		/// </summary>
		///
		/// <returns>	A reference to a const HAPI_TColour. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const HAPI_TColour& AsHAPI_TColour() const{
			return *(const HAPI_TColour*)this;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Modulate. Note: must be accurate so no bit shift used. </summary>
		///
		/// <param name="rhs">	The right hand side. </param>
		///
		/// <returns>	The result of the operation. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Colour255& operator*=(const Colour255 &rhs)
		{
			red = (red * rhs.red) / 255;
			green = (green * rhs.green) / 255;
			blue = (blue * rhs.blue) / 255;
			alpha = (alpha * rhs.alpha) / 255;
			return *this;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Assignment operator. </summary>
		///
		/// <param name="rhs">	The right hand side. </param>
		///
		/// <returns>	A shallow copy of this object. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Colour255& operator=(const HAPI_TColour &rhs)
		{
			// Byte copy
			*this = *(const Colour255*)&rhs;
			return *this;
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Can be used with cout to output colour to output pane and log. </summary>
	///
	/// <param name="os"> 	[in,out] The stream. </param>
	/// <param name="col">	The colour. </param>
	///
	/// <returns>	The streamed result. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	inline std::ostream& operator<<(std::ostream& os, const Colour255& col)
	{
		os << "R: " + std::to_string(col.red) +
			" G: " + std::to_string(col.green) +
			" B: " + std::to_string(col.blue) +
			" A: " + std::to_string(col.alpha);
		return os;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Equivelance operator. </summary>
	///
	/// <param name="lhs">	The first instance to compare. </param>
	/// <param name="rhs">	The second instance to compare. </param>
	///
	/// <returns>	True if the parameters are considered equivalent. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	inline bool operator==(const Colour255& lhs, const Colour255& rhs)
	{
		return (*(DWORD*)&lhs == *(DWORD*)&rhs);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Inequality operator. </summary>
	///
	/// <param name="lhs">	The first instance to compare. </param>
	/// <param name="rhs">	The second instance to compare. </param>
	///
	/// <returns>	True if the parameters are not considered equivalent. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	inline bool operator!=(const Colour255& lhs, const Colour255& rhs)
	{
		return !(lhs == rhs);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Subtract one colour from the other handling wrap around. </summary>
	///
	/// <param name="lhs">	The first value. </param>
	/// <param name="rhs">	A value to subtract from it. </param>
	///
	/// <returns>	The result of the operation. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	inline Colour255 operator- (const Colour255& lhs, const Colour255& rhs)
	{
		// Allow loop around
		int r = lhs.red - rhs.red;
		if (r < 0) r += 255;
		int g = lhs.green - rhs.green;
		if (g < 0) g += 255;
		int b = lhs.blue - rhs.blue;
		if (b < 0) b += 255;
		int a = lhs.alpha - rhs.alpha;
		if (a < 0) a += 255;
		return Colour255((BYTE)r, (BYTE)g, (BYTE)b, (BYTE)a);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Modulate one colour by another. </summary>
	///
	/// <param name="lhs">	The first value to multiply. </param>
	/// <param name="rhs">	The second value to multiply. </param>
	///
	/// <returns>	The result of the operation. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	inline Colour255 operator* (const Colour255& lhs, Colour255 rhs)
	{
		Colour255 sourceMod{ lhs };
		sourceMod.red = (lhs.red * rhs.red) >> 8;
		sourceMod.green = (lhs.green * rhs.green) >> 8;
		sourceMod.blue = (lhs.blue * rhs.blue) >> 8;
		sourceMod.alpha = (lhs.alpha * rhs.alpha) >> 8;
		return sourceMod;
	}

	/// <summary>	A simple floating point colour type. </summary>
	class ColourF
	{
	public:
		float red{ 1.f };
		float green{ 1.f };
		float blue{ 1.f };
		float alpha{ 1.f };

		/// <summary>	Constructor 1 - Colour defaults to white. </summary>
		ColourF() noexcept = default;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Constructor 2 - Colours passed in, alpha defaults to 1 (opaque) if not provided.
		/// </summary>
		///
		/// <param name="r">	Red channel. </param>
		/// <param name="g">	Green channel. </param>
		/// <param name="b">	Blue channel. </param>
		/// <param name="a">	(Optional) Alpha channel. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		ColourF(float r, float g, float b, float a = 1.0f) noexcept : red(r), green(g), blue(b), alpha(a) {}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor 3 - gray. </summary>
		///
		/// <param name="gray">	The gray scale - filled into R, G and B channels. </param>
		/// <param name="a">   	(Optional)  Alpha channel. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		ColourF(float gray, float a = 1.0f) noexcept : red(gray), green(gray), blue(gray), alpha(a) {}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor 4 - from a Colour255. </summary>
		///
		/// <param name="col">	The colour. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		ColourF(Colour255 col) noexcept : red{ col.red / 255.0f }, green{ col.green / 255.0f }, blue{ col.blue / 255.0f }, alpha{ col.alpha / 255.0f } {}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Add a Colour to this. </summary>
		///
		/// <param name="rhs">	The right hand side. </param>
		///
		/// <returns>	The result of the operation. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		ColourF& operator+=(ColourF rhs)
		{
			red += rhs.red;
			green += rhs.green;
			blue += rhs.blue;
			alpha += rhs.alpha;
			return *this;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Subtract a Colour from this. </summary>
		///
		/// <param name="rhs">	The right hand side. </param>
		///
		/// <returns>	The result of the operation. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		ColourF& operator-=(ColourF rhs)
		{
			red -= rhs.red;
			green -= rhs.green;
			blue -= rhs.blue;
			alpha -= rhs.alpha;
			return *this;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Division assignment operator. </summary>
		///
		/// <param name="rhs">	The right hand side. </param>
		///
		/// <returns>	The result of the operation. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		ColourF& operator/=(float rhs)
		{
			if (rhs == 0.0f)
				return *this; // should be an error really
			red /= rhs;
			green /= rhs;
			blue /= rhs;
			alpha /= rhs;
			return *this;
		}

		/// <summary>	Helpers. </summary>
		static const ColourF BLACK;
		/// <summary>	white. </summary>
		static const ColourF WHITE;
		/// <summary>	red. </summary>
		static const ColourF RED;
		/// <summary>	green. </summary>
		static const ColourF GREEN;
		/// <summary>	blue. </summary>
		static const ColourF BLUE;
		/// <summary>	yellow. </summary>
		static const ColourF YELLOW;
		/// <summary>	cyan. </summary>
		static const ColourF CYAN;
		/// <summary>	magenta. </summary>
		static const ColourF MAGENTA;
		/// <summary>	0,0,0,0. </summary>
		static const ColourF ZERO;
		/// <summary>	A horrid pink. </summary>
		static const ColourF HORRID_PINK;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets a random colour. </summary>
		///
		/// <returns>	A ColourF. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static const ColourF Random() { return Colour255(rand() % 255, rand() % 255, rand() % 255); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Stream insertion operator. </summary>
		///
		/// <param name="os"> 	[in,out] The output stream. </param>
		/// <param name="col">	The colour. </param>
		///
		/// <returns>	The output stream. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		friend std::ostream& operator<<(std::ostream& os, const ColourF& col);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Convert this object into a string representation. </summary>
		///
		/// <returns>	A std::string that represents this object. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::string ToString() const { std::stringstream str; str << *this; return str.str(); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Query if this object is white. </summary>
		///
		/// <returns>	True if white, false if not. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool IsWhite() const { return (red == 1.0f && green == 1.0f && blue == 1.0f && alpha == 1.0f); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Conversion. Made explicit as it is not a straight forward operation so user needs to know.
		/// </summary>
		///
		/// <returns>	The result of the operation. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		explicit operator Colour255() const
		{ 
			// May lose data if values outside range
			return Colour255((BYTE)(red*255.0f), (BYTE)(green*255.0f), (BYTE)(blue*255.0f), (BYTE)(alpha*255.0f));
		}	
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Can be used with cout to output colour to output pane and log. </summary>
	///
	/// <param name="os"> 	[in,out] The stream. </param>
	/// <param name="col">	The colour. </param>
	///
	/// <returns>	The streamed result. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	inline std::ostream& operator<<(std::ostream& os, const ColourF& col)
	{
		os << "R: " + std::to_string(col.red) +
			" G: " + std::to_string(col.green) +
			" B: " + std::to_string(col.blue) +
			" A: " + std::to_string(col.alpha);
		return os;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Equality operator. </summary>
	///
	/// <param name="lhs">	The first instance to compare. </param>
	/// <param name="rhs">	The second instance to compare. </param>
	///
	/// <returns>	True if the parameters are considered equivalent. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	inline bool operator==(const ColourF& lhs, const ColourF& rhs)
	{
		return (lhs.red == rhs.red && lhs.green == rhs.green && lhs.blue == rhs.blue && lhs.alpha == rhs.alpha);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Inequality operator. </summary>
	///
	/// <param name="lhs">	The first instance to compare. </param>
	/// <param name="rhs">	The second instance to compare. </param>
	///
	/// <returns>	True if the parameters are not considered equivalent. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	inline bool operator!=(const ColourF& lhs, const ColourF& rhs)
	{
		return !(lhs == rhs);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Subtraction operator. </summary>
	///
	/// <param name="lhs">	The first value. </param>
	/// <param name="rhs">	A value to subtract from it. </param>
	///
	/// <returns>	The result of the operation. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	inline ColourF operator- (ColourF lhs, const ColourF& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Addition operator. </summary>
	///
	/// <param name="lhs">	The first value. </param>
	/// <param name="rhs">	A value to add to it. </param>
	///
	/// <returns>	The result of the operation. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	inline ColourF operator+ (ColourF lhs, const ColourF& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Modulate one colour by another per channel. </summary>
	///
	/// <param name="lhs">	The first value to multiply. </param>
	/// <param name="rhs">	The second value to multiply. </param>
	///
	/// <returns>	The result of the operation. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	inline ColourF operator* (const ColourF& lhs, const ColourF &rhs)
	{
		return ColourF(lhs.red * rhs.red, lhs.green * rhs.green, lhs.blue * rhs.blue, lhs.alpha * rhs.alpha);
	}
}