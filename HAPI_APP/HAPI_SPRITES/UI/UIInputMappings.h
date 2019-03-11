////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	UIInputMappings.h
//
// summary:	Declares the input mappings class
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "UI\UITypes.h"

namespace HAPI_UI_SPACE
{
	/// <summary>	A macro that defines the number of modifiers. </summary>
	#define NUM_MODIFERS 3

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// An input combination. Realistically a user cannot hold more than 4 keys at a time. All apart from
	/// one of those would need to be modifier keys.
	/// </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	struct InputCombi
	{
		// Main key is map key and is not a modifier

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Extra keys that need to be held at same time as the main one	e.g. shift, alt, control (can
		/// also be left shift only etc.)
		/// </summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::vector<EInputModifiers> modifiers;

		EInputMappingAction action{ EInputMappingAction::eUnmapped };

		InputCombi(EInputMappingAction actionIn, 
			std::vector<EInputModifiers> mods = std::vector<EInputModifiers>())
			: action(actionIn), modifiers(std::move(mods))
		{
			
		}					
	};	

	/// <summary>	Input mappings. </summary>
	class UIInputMappings
	{
	private:
		//	The key mappings. Need to use multimap as may have duplicate keys
		std::multimap<BYTE, InputCombi> m_keyMappings;							
		EInputModifiers m_currentMods[NUM_MODIFERS]{ EInputModifiers::eUnmapped };
		EInputMappingAction m_lastAction;
		DWORD m_lastTimeActionTriggered{ 0 };					
		MouseData m_lastMouseState;
		bool m_dragging{ false };
		BYTE m_currentKey{ 0 };

		void AssignKeyMappings();
		constexpr BYTE NoMainKeyCombi() const noexcept { return 255; }
	public:
		UIInputMappings();
		~UIInputMappings();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// For fixing a rare bug where mouse click stuck (after using FileOpen dialog) this clears
		/// </summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void Clear();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets action from current state. </summary>
		///
		/// <returns>	The action from current state. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		EInputMappingAction GetActionFromCurrentState();

		/// <summary>	Assign default mappings. </summary>
		void AssignDefaultMappings();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Key event happened. </summary>
		///
		/// <param name="keyEvent">	The key event. </param>
		/// <param name="keyCode"> 	The key code. </param>
		///
		/// <returns>	An EInputMappingAction. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		EInputMappingAction KeyEventHappened(EKeyEvent keyEvent, BYTE keyCode);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Mouse event happened. </summary>
		///
		/// <param name="mouseEvent">	The mouse event. </param>
		/// <param name="mouseData"> 	Information describing the mouse state. </param>
		///
		/// <returns>	An EInputMappingAction. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		EInputMappingAction MouseEventHappened(EMouseEvent mouseEvent, const MouseData& mouseData);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Mouse move happened. </summary>
		///
		/// <param name="mouseData">	Information describing the mouse state. </param>
		///
		/// <returns>	An EInputMappingAction. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		EInputMappingAction MouseMoveHappened(const MouseData& mouseData);

	};

}

