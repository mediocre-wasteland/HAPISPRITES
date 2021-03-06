////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	UIObjectText.h
//
// summary:	Declares the object text class
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "UI\UIObject.h"

namespace HAPI_UI_SPACE
{	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Note: text handles new lines (multi-line) </summary>
	///
	/// <seealso cref="T:UIObject"/>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class UIObjectText final : public UIObject
	{
	private:
		/// <summary>	The text. </summary>
		std::string m_text;
		/// <summary>	The type. </summary>
		ETextType m_type{ ETextType::eStatic };
		/// <summary>	Form for viewing the user interface editor object text. </summary>
		friend class UIEditorObjectTextWindow;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets text type. </summary>
		///
		/// <returns>	The text type. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		ETextType GetTextType() const { return m_type; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Sets text type. </summary>
		///
		/// <param name="newType">	Type of the new. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void SetTextType(ETextType newType) { m_type = newType; Recreate(); }
	public:
		// Uses skin style for all colours

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor. </summary>
		///
		/// <param name="owner">		[in,out] If non-null, the owner. </param>
		/// <param name="name">			The name. </param>
		/// <param name="tag">			The tag. </param>
		/// <param name="textStyle">	The text style. </param>
		/// <param name="text">			The text. </param>
		/// <param name="type">			(Optional) The type. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		UIObjectText(UIWindow* owner, std::string name, std::string tag, UiTextStyleGroup textStyle, std::string text,
			ETextType type = ETextType::eStatic);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Construct from XML. </summary>
		///
		/// <param name="owner">	[in,out] If non-null, the owner. </param>
		/// <param name="xml">  	[in,out] The XML. </param>
		/// <param name="root"> 	[in,out] If non-null, the root. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		UIObjectText(UIWindow* owner, CHapiXML &xml, CHapiXMLNode *root);
		/// <summary>	Destructor. </summary>
		~UIObjectText()=default;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Overrides required by UIObject. </summary>
		///
		/// <param name="newText">	The new text. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void SetText(const std::string &newText) override final;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets the text. </summary>
		///
		/// <returns>	The text. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::string GetText() const override final { return m_text; }

		/// <summary>	Lost focus. </summary>
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
		/// <summary>
		/// These come from mappings of key / mouse combinations e.g. CTRL-C is ePaste These come from
		/// mappings of key / mouse combinations e.g. CTRL-C is ePaste Return true if handled.
		/// </summary>
		///
		/// <param name="action">	 	The action. </param>
		/// <param name="lastAction">	The last action. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool HandleInputAction(EInputMappingAction action, EInputMappingAction lastAction) override final;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Do we want / can  we take focus? Optional. </summary>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool WantsFocus() const override final;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Varies on text type. </summary>
		///
		/// <returns>	The skin style. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		ESkinStyle GetSkinStyle() const override final { 
			if (m_type == ETextType::eStatic) return ESkinStyle::eNormalText; 
			if (m_type == ETextType::eClickable) return ESkinStyle::eClickableText; return ESkinStyle::eHeadingText;}

 		////////////////////////////////////////////////////////////////////////////////////////////////////
 		/// <summary>	Gets the type. </summary>
 		///
 		/// <returns>	The type. </returns>
 		////////////////////////////////////////////////////////////////////////////////////////////////////
 		EObjectType GetType() const override final { return EObjectType::eText; }
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