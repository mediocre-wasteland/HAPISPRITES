////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	Polygon.h
//
// summary:	Declares the polygon class
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace HAPISPACE {

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// A polygon class. Assumes last point and first point are joined. Always uses float vectors.
	/// </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Polygon final
	{
	public:
		/// <summary>	The points of the polygon. </summary>
		std::vector<Vector<float>> points;

		/// <summary>	Default constructor. </summary>
		Polygon() noexcept = default;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Construct from points. Note: you need 3 or more points to make a poly. </summary>
		///
		/// <param name="pIn">	The points. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Polygon(std::vector<Vector<float>> pIn) noexcept : points(std::move(pIn)) {}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Stream insertion operator. </summary>
		///
		/// <param name="os">	[in,out] The output stream. </param>
		/// <param name="l"> 	A Polygon to process. </param>
		///
		/// <returns>	The output stream. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		friend std::ostream& operator<<(std::ostream& os, const Polygon& l);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Convert this object into a string representation. </summary>
		///
		/// <returns>	A std::string that represents this object. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::string ToString() const { std::stringstream str; str << *this; return str.str(); }

		/// <summary>	Clears this object to its blank/initial state. </summary>
		void Clear() { points.clear(); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Adds a point to the end of the polygon. </summary>
		///
		/// <param name="newPoint">	The new point. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void AddPoint(Vector<float> newPoint) {
			points.emplace_back(newPoint);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Same as number of points as last line goes back to start. </summary>
		///
		/// <returns>	The number of lines. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		size_t GetNumLines() const { return points.size(); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets a line. </summary>
		///
		/// <param name="which">	Which line to get. </param>
		///
		/// <returns>	The line. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Line<float> GetLine(size_t which) const
		{
			assert(which < GetNumLines());
			if (which == GetNumLines() - 1)
				return Line<float>(points[which], points[0]);

			return Line<float>(points[which], points[which + 1]);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets all lines. </summary>
		///
		/// <returns>	The lines. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::vector<Line<float>> GetLines() const
		{
			std::vector<Line<float>> lines;
			lines.resize(GetNumLines());
			for (size_t i = 0; i < GetNumLines(); i++)
				lines[i] = GetLine(i);
			return lines;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Creates a new polygon representing the area of intersection of this with other. Note: if the
		/// returned polygon has no vertices there was no intersection.
		/// </summary>
		///
		/// <param name="other">	The other. </param>
		///
		/// <returns>	The area of intersection. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Polygon GetAreaOfIntersection(const Polygon& other) const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	What determines the centre of a polygon? This is a rough result. </summary>
		///
		/// <returns>	The centre. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		VectorF GetCentre() const
		{
			VectorF sum{ 0,0 };
			for (const auto& p : points)
				sum += p;
			return (sum / points.size());
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets the bounds of the polygon as a rectangle. </summary>
		///
		/// <returns>	The bounds. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		RectangleF GetBounds() const
		{
			if (points.empty())
				return Rectangle<float>();

			RectangleF bounds{ points[0].x,points[0].x, points[0].y,points[0].y };

			for (const auto& p : points)
			{
				bounds.left = std::min( bounds.left,p.x );
				bounds.right = std::max( bounds.right,p.x );
				bounds.top = std::min( bounds.top,p.y );
				bounds.bottom = std::max( bounds.bottom,p.y );
			}

			return bounds;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Changes all points by adding trans. </summary>
		///
		/// <param name="trans">	The translation. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void Translate(const VectorF &trans)
		{
			for (auto& p : points)
				p += trans;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Returns translated version. </summary>
		///
		/// <param name="trans">	The translation. </param>
		///
		/// <returns>	The translation Polygon. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Polygon Translated(const VectorF &trans) const
		{
			Polygon newPoly{ points };
			newPoly.Translate(trans);
			return newPoly;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Gets the position of the first intersection of a line and this poly. Normal is from the line
		/// intersection. Returns false if no intersection.
		/// </summary>
		///
		/// <param name="line">	The line. </param>
		/// <param name="pnt"> 	[in,out] The point. </param>
		/// <param name="N">   	[in,out] A VectorF to process. </param>
		///
		/// <returns>	Returns false if no intersection. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool Intersection(const LineF& line, VectorF& pnt, VectorF& N) const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Intersection to infinity. </summary>
		///
		/// <param name="line">	The line. </param>
		/// <param name="pnt"> 	[in,out] The intersection point. </param>
		/// <param name="N">   	[in,out] The normal . </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool IntersectionInfinity(const LineF& line, VectorF& pnt, VectorF& N) const;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Can be used with cout to output values to output pane and log. </summary>
	///
	/// <param name="os">	[in,out] The output stream. </param>
	/// <param name="l"> 	A Polygon to output. </param>
	///
	/// <returns>	The output stream. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	inline std::ostream& operator<<(std::ostream& os, const Polygon& l)
	{
		for (size_t i = 0; i < l.points.size(); i++)
			os << "P" << i << ": " << l.points[i] << " ";
		return os;
	}
}