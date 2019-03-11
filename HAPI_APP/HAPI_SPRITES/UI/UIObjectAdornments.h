////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	UIObjectAdornments.h
//
// summary:	Declares the object adornments class
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "UI\UIObject.h"

namespace HAPI_UI_SPACE
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// An object adornments. Can be used as background for a window. Fill colour and border colour
	/// come from style unless overwritten.
	/// </summary>
	///
	/// <seealso cref="T:UIObject"/>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class UIObjectAdornments final : public UIObject
	{
	private:
		RectangleI m_titleBarRect;
		RectangleI m_menuBarRect;
		RectangleI m_sizingAreaRect;
		RectangleI m_newSizeRect;

		/// <summary>	Different when minimised. </summary>
		RectangleI m_minimisedBounds;

		/// <summary>	So can restore after minimisation. </summary>
		RectangleI m_oldBounds;

		VectorI m_textPos;
		VectorI m_crossPos;
		VectorI m_minimisePos;
		VectorI m_dragStart;

		/// <summary>	For the minimise, maximise and close buttons. </summary>
		VectorI m_iconSize;
		int m_closeFrameNum{ 0 };
		int m_minimiseFrameNum{ 0 };
		int m_maximiseFrameNum{ 0 };						

		std::string m_titleText;

		unsigned int m_featuresFlags;

		bool m_sizing{ false };
		bool m_previousMouseDownState{ false };		
		bool m_highlightCross{ false };
		bool m_highlightMinimise{ false };		
	public:	
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor. </summary>
		///
		/// <param name="owner">			[in,out] If non-null, the owning window. </param>
		/// <param name="name">				The name. </param>
		/// <param name="tag">				The tag. </param>
		/// <param name="textStyle">		The text style. </param>
		/// <param name="dimensions">   	The dimensions. </param>
		/// <param name="featuresFlags">	The features flags. </param>
		/// <param name="titleText">		The title text. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		UIObjectAdornments(UIWindow* owner, std::string name, std::string tag, UiTextStyleGroup textStyle, RectangleI dimensions,
			unsigned int featuresFlags,std::string titleText);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor from XML. </summary>
		///
		/// <param name="owner">		 	[in,out] If non-null, the owning window. </param>
		/// <param name="name">			 	The name. </param>
		/// <param name="xml">			 	[in,out] The XML data. </param>
		/// <param name="adornmentsNode">	[in,out] If non-null, the adornments node. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		UIObjectAdornments(UIWindow* owner, std::string name, CHapiXML &xml, CHapiXMLNode *adornmentsNode);
		/// <summary>	Destructor. </summary>
		~UIObjectAdornments() = default;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Allows change after creation. </summary>
		///
		/// <param name="which">	The feature flag. </param>
		/// <param name="set">  	True to set. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void SetFeatureFlag(WindowFeatures::EAdornmentFeatures which, bool set);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Owning window is minimised. </summary>
		///
		/// <param name="set">	True to set. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void OwningWindowIsMinimised(bool set);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// For adornments refers to window title.
		/// </summary>
		///
		/// <param name="newText">	The new title text. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void SetText(const std::string &newText) override final { m_titleText = newText;  Recreate(); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Allows getting text directly.  </summary>
		///
		/// <returns>	The title text. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::string GetText() const override final { return m_titleText; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets client rectangle. </summary>
		///
		/// <returns>	The client rectangle. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		RectangleI GetClientRect() const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets menu area. </summary>
		///
		/// <returns>	The menu area. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		RectangleI GetMenuArea() const { return m_menuBarRect; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets features flags. </summary>
		///
		/// <returns>	The features flags. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		unsigned int GetFeaturesFlags() const { return m_featuresFlags; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets if this is user draw. </summary>
		///
		/// <returns>	True if it is. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool GetUserDraw() const { return (m_featuresFlags & WindowFeatures::eUserDraw || m_featuresFlags & WindowFeatures::eSystem); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets weather should scale on size. </summary>
		///
		/// <returns>	True if it should </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool GetShouldScaleOnSize() const { return (m_featuresFlags & WindowFeatures::eScaleWhenSized); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Some objects may need multiple rects to describe their 'hit' areas. </summary>
		///
		/// <returns>	The window space collision rectangles. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::vector<RectangleI> GetWindowSpaceCollisionRectangles() const override final
		{
			// For collision detection we only want to use the title bar (if there is one)
			// Note: adornment rects are already in window space			

			// Addition - also want sizing area to hit	
			// But it depends on mode if we have a title bar
			if (m_featuresFlags & WindowFeatures::eTitleText)
				return std::vector<RectangleI>{m_titleBarRect, m_sizingAreaRect};

			return std::vector<RectangleI>{m_sizingAreaRect};
		}

		// Overrides from UIObject

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// These come from mappings of key / mouse combinations e.g. CTRL-C is ePaste. Return true if
		/// handled.
		/// </summary>
		///
		/// <param name="action">	 	The action. </param>
		/// <param name="lastAction">	The last action. </param>
		///
		/// <returns>	True if it handled the action, false otherwise. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool HandleInputAction(EInputMappingAction action, EInputMappingAction lastAction) override final;

		/// <summary>	Lost focus. </summary>
		void LostFocus() override final;

		/// <summary>	Gained focus. </summary>
		void GainedFocus() override final;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Determine if we can give up focus. </summary>
		///
		/// <param name="action">	The action. </param>
		///
		/// <returns>	True if we can give up focus, false if not. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool CanGiveUpFocus(EInputMappingAction action) const override;

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
		/// <summary>	Writes XML data. </summary>
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
		ERenderPriority GetRenderPriority() const override final { return ERenderPriority::eFirst; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets skin style. </summary>
		///
		/// <returns>	The skin style. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		ESkinStyle GetSkinStyle() const override final { return ESkinStyle::eWindowNormal; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets the object type. </summary>
		///
		/// <returns>	The type. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		EObjectType GetType() const override final { return EObjectType::eAdornment; }

	protected:
		/// <summary>	Creates the surfaces.Renders to surfaces and uploads to HW for quick rendering. </summary>
		void CreateSurfaces() override final;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Does the rendering. </summary>
		///
		/// <param name="surface">	  	[in,out] The surface. </param>
		/// <param name="surfaceRect">	The surface rectangle. </param>
		/// <param name="sub">		  	The sub. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void RenderToSurface(std::shared_ptr<Surface> &surface, RectangleI surfaceRect, ESkinSubStyle sub) const override final;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Calculates bounds and positioning of gfx etc. </summary>
		///
		/// <param name="newSize">  	Size of the desired  rectangle. </param>
		/// <param name="forceSize">	(Optional) True to force size. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void CalculateSizes(const RectangleI& newSize, bool forceSize = false) override final;
	};

}