////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	UIObjectMenu.h
//
// summary:	Declares the object menu class
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "UI\UIObject.h"

namespace HAPI_UI_SPACE
{
	/// <summary>	A menu item. </summary>
	struct MenuItem
	{
		/// <summary>	The text. </summary>
		std::string text;
		/// <summary>	True to enable, false to disable. </summary>
		bool enabled{ true };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor. </summary>
		///
		/// <param name="itemText">	The item text. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		MenuItem(std::string itemText) : text(itemText) {}
	};

	/// <summary>	A position. </summary>
	struct Position
	{
		/// <summary>	The rectangle. </summary>
		RectangleI rect;
		/// <summary>	The text position. </summary>
		VectorI textPos;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor. </summary>
		///
		/// <param name="rct">	The rectangle. </param>
		/// <param name="pos">	The position. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Position(RectangleI rct, VectorI pos) :rect(rct),textPos(pos){}
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	An object menu. This class cannot be inherited. </summary>
	///
	/// <seealso cref="T:UIObject"/>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class UIObjectMenu final : public UIObject
	{
	public:
		// Not drawn - just an identifier

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets the seperator. </summary>
		///
		/// <returns>	A std::string. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static std::string Seperator() { return "---"; }
	private:
		/// <summary>	The menu items. </summary>
		std::vector<MenuItem> m_menuItems;

		/// <summary>	1:1 with menuItems, as offsets. </summary>
		std::vector<Position> m_positioning;

		/// <summary>	True to in menu bar. </summary>
		bool m_inMenuBar{ true };

		/// <summary>	The selected item. </summary>
		std::string m_selectedItem;

		/// <summary>	The highlight bar frame number. </summary>
		int m_highlightBarFrameNumber{ 0 };

		/// <summary>	The type. </summary>
		EMenuType m_type{ EMenuType::eDropDown };
		/// <summary>	True if fully expanded. </summary>
		bool m_fullyExpanded{ false };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets drop down area bounds. </summary>
		///
		/// <returns>	The drop down area bounds. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		RectangleI GetDropDownAreaBounds() const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Handles the mouse over menu described by pressed. </summary>
		///
		/// <param name="pressed">	True if pressed. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool HandleMouseOverMenu(bool pressed);

		/// <summary>	An editor. </summary>
		friend class UIEditor;
		/// <summary>	Form for viewing the user interface editor object menu. </summary>
		friend class UIEditorObjectMenuWindow;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets the items. </summary>
		///
		/// <returns>	The items. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::vector<std::string> GetItems() const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Replace items. </summary>
		///
		/// <param name="items">	The items. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void ReplaceItems(const std::vector<std::string>& items);

	public:
		// Constructs a menu. If type is drop down then the first item is the menu title

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor. </summary>
		///
		/// <param name="owner">		[in,out] If non-null, the owner. </param>
		/// <param name="name">			The name. </param>
		/// <param name="tag">			The tag. </param>
		/// <param name="textStyle">	The text style. </param>
		/// <param name="menuItems">	The menu items. </param>
		/// <param name="type">			(Optional) The type. </param>
		/// <param name="inMenuBar">	(Optional) True to in menu bar. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		UIObjectMenu(UIWindow* owner, std::string name, std::string tag, UiTextStyleGroup textStyle, const std::vector<std::string>& menuItems, EMenuType type = EMenuType::eDropDown, bool inMenuBar=true);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	construct from XML node. </summary>
		///
		/// <param name="owner">	[in,out] If non-null, the owner. </param>
		/// <param name="xml">  	[in,out] The XML. </param>
		/// <param name="root"> 	[in,out] If non-null, the root. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		UIObjectMenu(UIWindow* owner, CHapiXML &xml, CHapiXMLNode *root);
		/// <summary>	Destructor. </summary>
		~UIObjectMenu() = default;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets menu type. </summary>
		///
		/// <returns>	The menu type. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		EMenuType GetMenuType() const { return m_type; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Enables the menu item. </summary>
		///
		/// <param name="item">  	The item. </param>
		/// <param name="enable">	True to enable, false to disable. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void EnableMenuItem(const std::string&item, bool enable);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Restrict to menu bar. </summary>
		///
		/// <param name="set">	True to set. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void RestrictToMenuBar(bool set) { m_inMenuBar = set; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Query if this object is restricted to menu bar. </summary>
		///
		/// <returns>	True if restricted to menu bar, false if not. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool IsRestrictedToMenuBar() const { return m_inMenuBar; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// These come from mappings of key / mouse combinations e.g. CTRL-C is ePaste Return true if
		/// handled.
		/// </summary>
		///
		/// <param name="action">	 	The action. </param>
		/// <param name="lastAction">	The last action. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool HandleInputAction(EInputMappingAction action, EInputMappingAction lastAction) override final;

		/// <summary>	Overrides required by UIObject. </summary>
		void LostFocus() override final;
		/// <summary>	Gained focus. </summary>
		void GainedFocus() override final;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Renders this object. </summary>
		///
		/// <param name="surface">  	[in,out] The surface. </param>
		/// <param name="translate">	The translation. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void Render(std::shared_ptr<Surface> &surface, VectorI translate) const override final;		

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Change action state. </summary>
		///
		/// <param name="newState">	New state. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void ChangeActionState(EActionState newState) override final;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Writes an XML. </summary>
		///
		/// <param name="rootNode">	[in,out] If non-null, the root node. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool WriteXML(CHapiXMLNode *rootNode) override final;		

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets render priority. </summary>
		///
		/// <returns>	The render priority. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		ERenderPriority GetRenderPriority() const override final { return ERenderPriority::eLast; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets skin style. </summary>
		///
		/// <returns>	The skin style. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		ESkinStyle GetSkinStyle() const override final { return ESkinStyle::eMenu; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets the type. </summary>
		///
		/// <returns>	The type. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		EObjectType GetType() const override final { return EObjectType::eMenu; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Optional overrides Some objects may need multiple rects to describe their 'hit' areas.
		/// </summary>
		///
		/// <returns>	The window space collision rectangles. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::vector<RectangleI> GetWindowSpaceCollisionRectangles() const override final;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets bounding rectangle object space. </summary>
		///
		/// <returns>	The bounding rectangle object space. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		RectangleI GetBoundingRectangleObjectSpace() const override final;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets maximum bounding rectangle object space. </summary>
		///
		/// <returns>	The maximum bounding rectangle object space. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		RectangleI GetMaxBoundingRectangleObjectSpace() const override final;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Determine if we can give up focus. </summary>
		///
		/// <param name="action">	The action. </param>
		///
		/// <returns>	True if we can give up focus, false if not. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool CanGiveUpFocus(EInputMappingAction action) const override final;
	protected:
		// Renders to surfaces and uploads to HW for quick rendering
		/// <summary>	Creates the surfaces. </summary>
		void CreateSurfaces() override final;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Does the rendering. </summary>
		///
		/// <param name="surface">	  	[in,out] The surface. </param>
		/// <param name="surfaceRect">	The surface rectangle. </param>
		/// <param name="sub">		  	The sub. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void RenderToSurface(std::shared_ptr<Surface> &surface, RectangleI surfaceRect, ESkinSubStyle sub) const override final;
		// Calculates bounds and positioning of gfx etc.
		void CalculateSizes(const RectangleI& newSize, bool forceSize = false) override final;
	};
}