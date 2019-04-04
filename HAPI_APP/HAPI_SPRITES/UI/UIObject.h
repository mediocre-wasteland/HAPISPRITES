////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	UIObject.h
//
// summary:	Declares the object class
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "UI\UITypes.h"
#include "UI\UISkin.h"

namespace HAPISPACE
{
	class UIandSkinPayloadData;
	class SizeUndo;
	class PositionUndo;
}

namespace HAPI_UI_SPACE
{	
	/// <summary>	UI Object base class. </summary>
	class UIObject
	{
	private:
		VectorI m_position;
		UiTextStyleGroup m_textStyle;
		UiWindowStyleGroup m_windowStyle;
		void CalculateMaxBorderWidth();
		friend class UIWindow;
		// Do not call directly, do via window
		void ChangeName(std::string newName) { m_name = std::move(newName); }	
	protected:
		std::string m_name;
		RectangleI m_bounds;
		RectangleI m_originalBounds;
		VectorI m_originalPosition;
		int m_maxBorderWidth{ 0 };
		int m_maxShadowWidth{ 0 };
		bool m_visible{ true };
		EActionState m_actionState{ EActionState::eNormal };
		EActionState m_actionStatePriorToBeingDisabled{ EActionState::eNormal };
		std::shared_ptr<Sprite> m_precreatedSprite;

		// Unfortunately cannot use a shared pointer for this
		UIWindow* m_owningWindow{ nullptr };

		// Tag for grouping e.g. into screens.
		std::string m_tag;

		void RenderText(std::shared_ptr<Surface> &surface, VectorI p, const std::string& text, const UiTextStyle& style) const;
		void DrawWindowFilledRect(std::shared_ptr<Surface> &surface, const RectangleI &rect, const UiWindowStyle& style) const;

		/// <summary>	Arbitray line that uses window style border shader and width. </summary>
		void DrawWindowLine(std::shared_ptr<Surface> &surface, const LineI &line, const UiWindowStyle& style) const;

		/// <summary> setShadowWritesAlpha is special case for adornments which need to burn alpha.</summary>
		void DrawWindowBorderRect(std::shared_ptr<Surface> &surface, const RectangleI &rect, const UiWindowStyle& style) const;

		/// <summary>	top is needed to know which way to send border. </summary>
		void DrawHorizontalWindowBorder(std::shared_ptr<Surface> &surface, VectorI pos, int width, const UiWindowStyle& style,bool top) const;

		/// <summary>	Draw vertical window border. </summary>
		void DrawVerticalWindowBorder(std::shared_ptr<Surface> &surface, VectorI pos, int height, const UiWindowStyle& style,bool left) const;

		/// <summary>	Draw horizontal window line. </summary>
		void DrawHorizontalWindowLine(std::shared_ptr<Surface> &surface, VectorI pos, int width, const UiWindowStyle& style) const;

		/// <summary>	Draw vertical window line. </summary>
		void DrawVerticalWindowLine(std::shared_ptr<Surface> &surface, VectorI pos, int height, const UiWindowStyle& style) const;

		/// <summary>	Draw shadow. </summary>
		void DrawShadow(std::shared_ptr<Surface> &surface, const RectangleF &rect, const UiWindowStyle& style) const;

		/// <summary>	Loads base XML. </summary>
		bool LoadBaseXML(CHapiXML &xml, CHapiXMLNode *root);

		/// <summary>Solving issue when object first created and user has supplied a position in the rect. </summary>
		RectangleI RemovePositionFromCreationRect(RectangleI dimensions);

		/// <summary>	Renders to surfaces and uploads to HW for quick rendering. </summary>
		virtual void CreateSurfaces() = 0;

		/// <summary>	Calculates bounds and positioning of gfx etc. </summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void CalculateSizes(const RectangleI &newSize, bool forceSize = false) = 0;

		/// <summary>	Render anything that needs to be rendered to surface type. </summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void RenderToSurface(std::shared_ptr<Surface> &surface, RectangleI surfaceRect, ESkinSubStyle sub) const = 0;

		/*
			All sizing and positioning operations must go via the owning window
		*/
		
		friend class UIWindow;

		/// <summary>	USed when resizing. </summary>
		RectangleI GetOriginalBounds() const { return m_originalBounds; }

		/// <summary>	Gets original position. </summary>
		VectorI GetOriginalPosition() const { return m_originalPosition; }

		friend class HAPISPACE::UIandSkinPayloadData;



		/// <summary>	Gets largest of all subtypes in terms of bounding rect. </summary>
		RectangleI GetTextRect(const std::string &text) const;

		/// <summary>	allows edit. </summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		UiTextStyleGroup& GetTextStyleGroupSettings() { return m_textStyle; }

		/// <summary>	Gets window style group settings. </summary>
		UiWindowStyleGroup& GetWindowStyleGroupSettings() { return m_windowStyle; }

		/// <summary>	Gets text style settings. </summary>
		const UiTextStyle& GetTextStyleSettings(ESkinSubStyle sub) const { return m_textStyle.GetSub(sub); }

		/// <summary>	Gets window style settings. </summary>
		const UiWindowStyle& GetWindowStyleSettings(ESkinSubStyle sub) const { return m_windowStyle.GetSub(sub); }

		/// <summary>	Gets skin sizes. </summary>
		const UiSkinSizes& GetSkinSizes() const;

		/// <summary>	Gets skin sub style from action state. </summary>
		ESkinSubStyle GetSkinSubStyleFromActionState() const;

		friend class HAPISPACE::SizeUndo;
		friend class HAPISPACE::PositionUndo;

		/// <summary>	Change the position of the object. </summary>
		void SetPositionWindowSpace(VectorI newPos, bool setAsOriginal = true) 
		{ 
			m_position = newPos; 
			if (setAsOriginal) m_originalPosition = newPos; 
		}

		/// <summary>	Writes a base XML. </summary>
		bool WriteBaseXML(CHapiXMLNode *rootNode) const;
				
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Construct with a name and owning window. </summary>
		///
		/// <param name="owner">		[in,out] If non-null, the owner. </param>
		/// <param name="name">			The name. </param>
		/// <param name="tag">			The tag. </param>
		/// <param name="textStyle">	The text style. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		UIObject(UIWindow* owner, std::string name, std::string tag, UiTextStyleGroup textStyle)  noexcept :
			m_owningWindow(owner), m_name(name), m_tag(tag), m_textStyle(textStyle) {}

		virtual ~UIObject() = default;		

		/// <summary>	Recreate all graphics (will also cascade styles) </summary>
		void Recreate();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Change tag. </summary>
		///
		/// <param name="newTag">	The new tag. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void ChangeTag(const std::string &newTag) { m_tag = newTag; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets text style group settings. </summary>
		///
		/// <returns>	The text style group settings. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const UiTextStyleGroup& GetTextStyleGroupSettings() const { return m_textStyle; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets window style group settings. </summary>
		///
		/// <returns>	The window style group settings. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const UiWindowStyleGroup& GetWindowStyleGroupSettings() const { return m_windowStyle; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Allows this object's instance data to be set for text style. Note: will cause a style cascade
		/// and a complete recreation of all object's graphics.
		/// </summary>
		///
		/// <param name="textStyle">	The text style. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void SetTextStyleGroupSettings(const UiTextStyleGroup& textStyle) { m_textStyle = textStyle; Recreate(); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Allows this object's instance data to be set for window style. Note: will cause a style
		/// cascade and a complete recreation of all object's graphics.
		/// </summary>
		///
		/// <param name="winStyle">	The window style. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void SetWindowStyleGroupSettings(const UiWindowStyleGroup& winStyle) { m_windowStyle = winStyle; Recreate();}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Every object is owned by a window. </summary>
		///
		/// <returns>	The owning window. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		UIWindow& GetOwningWindow() const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Query if this object is visible. </summary>
		///
		/// <returns>	True if visible, false if not. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool IsVisible() const { return m_visible; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Sets visibility. </summary>
		///
		/// <param name="set">	True to set. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void SetVisible(bool set) { m_visible = set; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Every object has a name unique to the window it is part of. </summary>
		///
		/// <returns>	The name. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const std::string& GetName() const { return m_name; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Object's can optionally have a tag. </summary>
		///
		/// <returns>	The tag. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const std::string& GetTag() const { return m_tag; }		

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	An object is always in a state. </summary>
		///
		/// <returns>	The action state. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		EActionState GetActionState() const { return m_actionState; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Change state - updates listeners if relevant Prefer to use Disable if wanting to set to
		/// disabled.
		/// </summary>
		///
		/// <param name="newState">	New state. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void ChangeActionState(EActionState newState) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// True - Disables but remembers previous state to return to.
		/// </summary>
		///
		/// <param name="set">	True to set.  False - returns to previous state. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void Disable(bool set);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets position in window space. </summary>
		///
		/// <returns>	The position window space. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		VectorI GetPositionWindowSpace() const { return m_position; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets position in screen space. </summary>
		///
		/// <param name="windowTopLeft">	The window top left. </param>
		///
		/// <returns>	The position screen space. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		VectorI GetPositionScreenSpace(VectorI windowTopLeft) const { return GetPositionWindowSpace() + windowTopLeft; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Note this can vary dependant on object shape e.g. the menu can be expanded or just a title
		/// Therefore to get size when fully expanded call GetMaxBoundingRectangleObjectSpace. This is
		/// virtual to allow things like menu to redefine.
		/// </summary>
		///
		/// <returns>	The bounding rectangle object space. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual RectangleI GetBoundingRectangleObjectSpace() const { return m_bounds; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets maximum bounding rectangle in object space. </summary>
		///
		/// <returns>	The maximum bounding rectangle in object space. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual RectangleI GetMaxBoundingRectangleObjectSpace() const { return GetBoundingRectangleObjectSpace(); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets bounding rectangle in window space. </summary>
		///
		/// <returns>	The bounding rectangle in window space. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		RectangleI GetBoundingRectangleWindowSpace() const { return GetBoundingRectangleObjectSpace().Translated(m_position); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets bounding rectangle window space including border. </summary>
		///
		/// <returns>	The bounding rectangle window space include border. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		RectangleI GetBoundingRectangleWindowSpaceIncludeBorder() const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets bounding rectangle in screen space. </summary>
		///
		/// <param name="windowTopLeft">	The window top left. </param>
		///
		/// <returns>	The bounding rectangle screen space. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		RectangleI GetBoundingRectangleScreenSpace(const VectorI& windowTopLeft) const { return GetBoundingRectangleWindowSpace().Translated(windowTopLeft); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets the maximum border size. </summary>
		///
		/// <returns>	The maximum border size. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		int GetMaxBorderSize() const { return m_maxBorderWidth; }

		// Virtuals

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Some objects may need multiple rects to describe their 'hit' areas. </summary>
		///
		/// <returns>	The window space collision rectangles. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual std::vector<RectangleI> GetWindowSpaceCollisionRectangles() const {
			// Default is just the one bounding
			return std::vector<RectangleI>{GetBoundingRectangleWindowSpace()};
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Allows setting text directly (if object supports it) </summary>
		///
		/// <param name="newText">	The new text. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void SetText(const std::string &newText) { std::cerr << "SetText: Unsupported call" << std::endl; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Allows getting text directly (if supported else empty) </summary>
		///
		/// <returns>	The text. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual std::string GetText() const { return std::string(); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Allows setting value directly (if object supports it). Will be clamped between 0 and 1 and
		/// may be snapped to resolution.
		/// </summary>
		///
		/// <param name="ratioValue">	The ratio value. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void SetValue(float ratioValue) { std::cerr << "SetValue: Unsupported call" << std::endl; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Allows getting value directly (if object supports it). What the value means depends on object
		/// type but normally ranges from 0.0f to 1.0f.
		/// </summary>
		///
		/// <returns>	The value. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual float GetValue() const { std::cerr << "GetValue: Unsuported call" << std::endl;  return -1.0f; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Interpreted key event occured when we have focus, return true if we handled it.
		/// </summary>
		///
		/// <param name="c">	The character. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool TextEntered(char c) { return false; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	priority 0 is rendered first. TODO: allow this to be user set? </summary>
		///
		/// <returns>	The render priority. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual ERenderPriority GetRenderPriority() const { return ERenderPriority::eDontCare; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Object type. </summary>
		///
		/// <returns>	The type. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual EObjectType GetType() const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	These are hard coded in child to return an enum. </summary>
		///
		/// <returns>	The skin style. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual ESkinStyle GetSkinStyle() const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	By default objects obey layout rules. </summary>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool ShouldObayWindowLayoutRules() const { return true; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Resizes.Attempt to resize. May not be possible or there may be a minimum allowed. However if
		/// force flag is true they must use it. Passing by value to avoid aliasing issues when called
		/// with m_bounds.
		/// </summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void Resize(RectangleI newSize, bool forceSize = false, bool setAsOriginal = true);
private:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Determine if we can give up focus. Some objects may want to hold on to focus e.g. text entry
		/// Some may want to hold on to it if mouse has just moved away and no button click e.g. right
		/// click menu.
		/// </summary>
		///
		/// <param name="action">	The action. </param>
		///
		/// <returns>	True if we can give up focus, false if not. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool CanGiveUpFocus(EInputMappingAction action) const { return true; }

		/// <summary>	Object has lost focus (no argument) </summary>
		virtual void LostFocus() = 0;

		/// <summary>	UI wants to set this object as the one with focus (no argument) </summary>
		virtual void GainedFocus() = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Draw this object to the surface. </summary>
		///
		/// <param name="surface">  	[in,out] The surface. </param>
		/// <param name="translate">	The translation. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void Render(std::shared_ptr<Surface> &surface,VectorI translate) const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Writes to XML. </summary>
		///
		/// <param name="rootNode">	[in,out] If non-null, the root node. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool WriteXML(CHapiXMLNode *rootNode) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Do we want / can we take focus? Optional. </summary>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool WantsFocus() const
		{
			if (GetActionState() == EActionState::eDisabled)
				return false;
			return true;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// These come from mappings of key / mouse combinations e.g. CTRL-C is ePaste. Return true if
		/// handled.
		/// </summary>
		///
		/// <param name="action">	 	The action. </param>
		/// <param name="lastAction">	The last action. </param>
		///
		/// <returns>	True if handled. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool HandleInputAction(EInputMappingAction action, EInputMappingAction lastAction) = 0;		
	};
}