////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	Collider.h
//
// summary:	Declares the collider class
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Shapes\Shapes.h"
#include "Transform.h"

namespace HAPISPACE {

	class Surface;

	/// <summary>	The collision result. </summary>
	enum class ECollisionResult
	{
		eBoundingFail,
		eBoundingPass,
		eOneOfFail,
		eOneOfPass,
		ePixelPerfectFail,
		ePixelPerfectPass
	};

	inline bool CollisionResultNoCollision(ECollisionResult result)
	{
		if (result == ECollisionResult::eBoundingFail ||
			result == ECollisionResult::eOneOfFail ||
			result == ECollisionResult::ePixelPerfectFail)
			return true;
		return false;
	}

	/// <summary>	Information about the relevant test that resulted in ECollisionResult. </summary>
	enum class ECollisionShapeType
	{		
		eRectRect,
		eCircleCircle,
		eRectCircle,
		eCircleRect, // as above but this circle with other rect
		ePixel
	};
	

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Determines transform, which collision checks are carried out, and what data is returned.
	/// </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	struct CollisionSettings
	{
		/// <summary>	Transforms for the two colliders involved in the collision test. </summary>
		Transform thisTransform;

		/// <summary>	The other transform. </summary>
		Transform otherTransform;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// When a collider has a collection of 'one of' shapes, setting this to true will test those
		/// (after normal bounds checks)
		/// A collision is judged to have happened if one of them collides.
		/// </summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool enableOneOfTests{ false };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Returns position and normal of a collision, requires the collisionLine to be provided (if not
		/// doing pixel perfect)
		/// </summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool calculateCollisionData{ false };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Does not use collider shapes but the sprite surface itself (after normal bounds checks)
		/// </summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool enablePixelPerfectCollisions{ false };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// If checking via ColliderComponent this is filled in automatically for you.
		/// Required to calculate collision data when calculateCollisionData is true (but not when
		/// enablePixelPerfectCollisions is true)
		/// Should be formed from the last position and the new position of the entity.
		/// </summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		LineF collisionLine;
	};	

	/// <summary>	Returned information about a collision test. </summary>
	struct CollisionInfo
	{
		/// <summary>	Result of the collision. </summary>
		ECollisionResult result{ ECollisionResult::eBoundingFail };

		/// <summary>	Type of the collision. </summary>
		ECollisionShapeType type{ ECollisionShapeType::eRectRect };

		/// <summary>	Name of the collider in this sprite that collided. </summary>
		std::string thisColliderName;
		
		/// <summary>	Name of the collider in other sprite that collided. </summary>
		std::string otherColliderName;
		
		// The following are only provided if CollisionSettings has calculateCollisionData set to true
		// Or a pixel perfect collision is being carried out

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Pixel on the screen where the collision occured. Only provided if CollisionSettings has
		/// calculateCollisionData set to true Or a pixel perfect collision is being carried out.
		/// </summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		VectorI screenPos;

		/// <summary>	Normal at the point of collision on 'other'.Only provided if CollisionSettings has
		/// calculateCollisionData set to true Or a pixel perfect collision is being carried out.
		/// </summary>
		VectorF normal;

		/// <summary>	Local position relative to the frame of 'this' where collision happened.Only provided if CollisionSettings has
		/// calculateCollisionData set to true Or a pixel perfect collision is being carried out.
		/// </summary>
		VectorI thisLocalPos;

		/// <summary>	Local position relative to the frame of 'other' where collision happened.Only provided if CollisionSettings has
		/// calculateCollisionData set to true Or a pixel perfect collision is being carried out.
		/// </summary>
		VectorI otherLocalPos;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Helper to convert shape type to string. </summary>
		///
		/// <param name="type">	The shape type. </param>
		///
		/// <returns>	Shape type as a string. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static std::string CollisionShapeTypeToString(ECollisionShapeType type)
		{
			switch (type)
			{
			case ECollisionShapeType::eRectRect:
				return "Rectangle v Rectangle Shape Test";
			case ECollisionShapeType::eCircleCircle:
				return "Circle v Circle Shape Test";
			case ECollisionShapeType::eRectCircle:
				return "Rectangle v Circle Shape Test";
			case ECollisionShapeType::eCircleRect:
				return "Circle v Rectangle Shape Test";
			case ECollisionShapeType::ePixel:
				return "Pixel v Pixel Test";
			default:
				break;
			}

			return "ERROR: ECollisionShapeType Unknown enum";
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Helper to convert result to a string. </summary>
		///
		/// <param name="result">	The result. </param>
		///
		/// <returns>	The result as a string. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static std::string CollisionResultToString(ECollisionResult result)
		{
			switch (result)
			{
			case ECollisionResult::eBoundingFail:
				return "Bounding Fail";
			case ECollisionResult::eBoundingPass:
				return "Bounding Pass";
			case ECollisionResult::eOneOfFail:
				return "One Of Fail";
			case ECollisionResult::eOneOfPass:
				return "One Of Pass";
			case ECollisionResult::ePixelPerfectFail:
				return "Pixel Perfect Fail";
			case ECollisionResult::ePixelPerfectPass:
				return "Pixel Perfect Pass";
			default:
				break;
			}

			return "ERROR: Unknown ECollisionResult enum";
		}
	};


	/// <summary>	Supported collider shapes. </summary>
	enum class EColliderShape
	{
		eRectangle,
		eCircle
		// polygon. capsule... TODO
	};	

	/// <summary>	Supported collider types. </summary>
	enum class EColliderType
	{
		// A bounding area collider, must be intersected for a true collision response. 
		eBounding,	
		// One or more of these collider types must be hit for a true collision response
		eOneOf,		
		// Used to determine screen positions for points or to detect areas hit etc. not part of collision result
		eMarker		
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Base collider class. Colliders are all defined in local space i.e. with 0,0 top left of
	/// frame. They are all shapes. Pixel perfect collisions are done via the component or sprite
	/// directly.
	/// </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Collider
	{
	protected:
		std::string m_name;
		EColliderType m_type;
		Collider() = default;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Writes base XML data. </summary>
		///
		/// <param name="thisNode">	[in,out] If non-null, this node. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void WriteBase(CHapiXMLNode* thisNode) const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Reads base XML data. </summary>
		///
		/// <param name="thisNode">	[in,out] If non-null, this node. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool ReadBase(CHapiXMLNode* thisNode);
		
		friend class ColliderGroup;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// For debug purposes can render the collider to a surface. Cannot be called direct as needs
		/// cache update.Renders this object.
		/// </summary>
		///
		/// <param name="renderSurface">	[in,out] The render surface. </param>
		/// <param name="transform">		The transform. </param>
		/// <param name="col">				The colour. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void Render(std::shared_ptr<Surface> &renderSurface, const Transform& transform, const Colour255& col) const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Cache transform. </summary>
		///
		/// <param name="trans">	The transform. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void CacheTransform(const Transform& trans) = 0;
	public:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor. </summary>
		///
		/// <param name="name">	The name. </param>
		/// <param name="type">	The collider type. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Collider(std::string name, EColliderType type) noexcept : m_name(name), m_type(type) {}
		virtual ~Collider() = default;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets the shape enum. </summary>
		///
		/// <returns>	The shape. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual EColliderShape GetShape() const = 0;		

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Writes XML. </summary>
		///
		/// <param name="parentNode">	[in,out] If non-null, the parent node. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void WriteXML(CHapiXMLNode* parentNode) const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets the name. </summary>
		///
		/// <returns>	The name. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const std::string& GetName() const { return m_name; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets the type. </summary>
		///
		/// <returns>	The type. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		EColliderType GetType() const { return m_type; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Changes type. Prefer to do via ColliderGroup to maintain cache integrity. </summary>
		///
		/// <param name="newType">	Type of the new. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void ChangeType(EColliderType newType) { m_type = newType; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Change name. </summary>
		///
		/// <param name="newName">	New name. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void ChangeName(std::string newName) { m_name = newName; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets local space bounding rectangle. </summary>
		///
		/// <returns>	The local space bounding rectangle. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual RectangleI GetLocalSpaceBoundingRectangle() const = 0;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	A rectangle collider. </summary>
	///
	/// <seealso cref="T:Collider"/>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class RectangleCollider : public Collider
	{
	private:
		RectangleI m_rect;
		RectangleOrientedF m_transformed;	
		// Additional caching as this was taking a lot of time - monitor
		Polygon m_tranformedAsPolygon;
	protected:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// For debug purposes can render the collider to a surface. Cannot be called direct as needs
		/// cache update. Renders this object.
		/// </summary>
		///
		/// <param name="renderSurface">	[in,out] The render surface. </param>
		/// <param name="transform">		The transform. </param>
		/// <param name="col">				The colour. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void Render(std::shared_ptr<Surface> &renderSurface, const Transform& transform, const Colour255& col) const override final;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Cache transform. </summary>
		///
		/// <param name="trans">	The transform. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void CacheTransform(const Transform& trans) override final;
		
	public:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor from rect. </summary>
		///
		/// <param name="name">	The name. </param>
		/// <param name="rect">	The rectangle. </param>
		/// <param name="type">	The type. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		RectangleCollider(std::string name, RectangleI rect, EColliderType type) noexcept : m_rect(rect), Collider(name, type){}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Construct from XML. </summary>
		///
		/// <param name="xml"> 	The XML. </param>
		/// <param name="node">	[in,out] If non-null, the node. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		RectangleCollider(const CHapiXML& xml, CHapiXMLNode* node);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets the rectangle. </summary>
		///
		/// <returns>	The rectangle. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const RectangleI &GetRect() const { return m_rect; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Change Rectangle. Prefer to do via ColliderGroup to maintain cache integrity.
		/// </summary>
		///
		/// <param name="newRect">	The new rectangle. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void ChangeRect(RectangleI newRect) { m_rect = newRect; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Writes XML. </summary>
		///
		/// <param name="parentNode">	[in,out] If non-null, the parent node. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void WriteXML(CHapiXMLNode* parentNode) const override final;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets the shape. </summary>
		///
		/// <returns>	The shape. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		EColliderShape GetShape() const override final { return EColliderShape::eRectangle; }		

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Cached result. </summary>
		///
		/// <returns>	Cached OBR. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const RectangleOrientedF& CachedResult() const { return m_transformed; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Cached outline of the collider. </summary>
		///
		/// <returns>	A polygon describing the outline. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const Polygon& CachedOutline() const { return m_tranformedAsPolygon; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets local space bounding rectangle. </summary>
		///
		/// <returns>	The local space bounding rectangle. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		RectangleI GetLocalSpaceBoundingRectangle() const override final { return m_rect; }
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	A circle collider. </summary>
	///
	/// <seealso cref="T:Collider"/>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class CircleCollider : public Collider
	{
	private:
		Circle m_circle;
		Circle m_transformed;
	protected:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// For debug purposes can render the collider to a surface. Cannot be called direct as needs
		/// cache update. Renders this object.
		/// </summary>
		///
		/// <param name="renderSurface">	[in,out] The render surface. </param>
		/// <param name="transform">		The transform. </param>
		/// <param name="col">				The colour. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void Render(std::shared_ptr<Surface> &renderSurface, const Transform& transform, const Colour255& col) const override final;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Cache transform. </summary>
		///
		/// <param name="trans">	The transform. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void CacheTransform(const Transform& trans) override final;
		
	public:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor. </summary>
		///
		/// <param name="name">	The name. </param>
		/// <param name="circ">	The circle. </param>
		/// <param name="type">	The type. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		CircleCollider(std::string name, Circle circ, EColliderType type) noexcept : m_circle(circ), Collider(name,type) {}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Construct from XML. </summary>
		///
		/// <param name="xml"> 	The XML. </param>
		/// <param name="node">	[in,out] If non-null, the node. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		CircleCollider(const CHapiXML& xml, CHapiXMLNode* node);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets the circle. </summary>
		///
		/// <returns>	The circle. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const Circle& GetCircle() const { return m_circle; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Change the circle. Prefer to do via ColliderGroup to maintain cache integrity.
		/// </summary>
		///
		/// <param name="newCircle">	The new circle. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void ChangeCircle(Circle newCircle) { m_circle = newCircle; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Writes XML. </summary>
		///
		/// <param name="parentNode">	[in,out] If non-null, the parent node. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void WriteXML(CHapiXMLNode* parentNode) const override final;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets the shape. </summary>
		///
		/// <returns>	The shape. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		EColliderShape GetShape() const override final { return EColliderShape::eCircle; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Cached result. </summary>
		///
		/// <returns>	A reference to a const Circle. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const Circle& CachedResult() const { return m_transformed; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets local space bounding rectangle. </summary>
		///
		/// <returns>	The local space bounding rectangle. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		RectangleI GetLocalSpaceBoundingRectangle() const override final { return (RectangleI)m_circle.GetEnclosingAABB(); }
	};
}
