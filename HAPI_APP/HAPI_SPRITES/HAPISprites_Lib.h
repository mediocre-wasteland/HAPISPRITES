////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	HAPISprites_Lib.h
//
// summary:	All the includes required to use the basic HAPI Sprites library
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

// HAPI Sprites is a 2D game API, written by Keith Ditchburn and free to use for all.
// 
// To import HAPI Sprites code library names: using namespace HAPISPACE
// 
// To use the UI you need to include its header:
// #include <HAPISprites_UI.h>
// 
// To import UI names: using namespace HAPI_UI_SPACE
// 
// For full details on using the library please see the online documentation and demos: (CTRL-Click
// to Open):
// https://scma-intranet.tees.ac.uk/users/u0018197/Happier/
// Also the full class and function reference:
// https://scma-intranet.tees.ac.uk/users/u0018197/Happier/doc/html/index.html
// 
// Last modified by Keith Ditchburn: March 2019
// 
// SELF NOTE: PRIOR TO FINALISING GENERATE DOXYGEN
//
// Version 0.88 26/03/19
// - NEW: Added the ability to size a button to the image shader via:
//	- UIObject resize function now being public
//	- Added GetSurface function to image shader (so you can query the size) 
//	- TODO: Once time I will add a better mechanism for sizing buttons to images
// - BUGFIX: Fixed a bug where the collision code was incorrectly trying to get a normal from the sprite sheet
//  - Plus added better code to trap this issue in the future
// - BUGFIX: Added debug output rather than an assert when a problem happens in DrawSuperEllipse to help solve an issue
//
// Version 0.87 24/03/19
// - NEW: Added a LimitFrameRate function to restrict FPS
// - NEW: Added a Vsync option flag to initialise (not to be used with above)
// - BUGFIX: issue with one - of colliders colliding only with same type
// - BUGFIX : improved circle vs rect collision for one specific corner case
// - Sprite Editor : toolbox entry of collider / frame values now updates handles correctly
// - Sprite Editor : up down movement reversed
// - Sprite Editor : copy now replaces collider if same name and type
// - Sprite Editor : improved edit selection of frame when colliders not shown 
// - DOC: further improvements to the documentation (this will be on going)
// - TIDY: tidied up some interfaces
//
// Version 0.86 17/03/19
//
// NEW : UI Menu now stays open until focus changes
// NEW : UI Menu now allows selection to be changed via input actions
// BUGFIX: PP Collision code for non scaled and rotated returned wrong local value
// BUGFIX : reworked the collision code to resolve a number of issues around shapes
// BUGFIX : fixed issue where circle collider collision point could be wrong
// BUGFIX : fixed issue in auto fit colliders with circle collider
// BUGFIX: Sprite Editor was rendering bounding shapes with the wrong transform
// BUGFIX: Circle vs Rect collision was erroneously reporting no ray intersection
// BUGFIX: Auto fit colliders was not working when frames have names
// OPT: increased collision test speeds a lot
// OPT: GenerateNormals speeded up. Also now allows a number of smoothing passes to be set (less is faster)
// OPT: Optimised some collision functions
//  
// Older version history is in the ReadMe.txt file

// C++ standard library types required by HAPI Sprites
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <iostream>
#include <map>
#include <stack>
#include <unordered_map>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <list>

// HAPI Sprites specific types
#include "HAPISprites_Types.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// namespace: HAPISPACE
///
/// summary:	All of HAPI Sprites (apart from the UI) is wrapped inside the HAPISPACE namespace.
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace HAPISPACE {

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Public HAPI Sprites Interface. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class IHapiSprites
	{
	public:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Initializes HAPI Sprites. Must be called before any other HAPI Sprites calls.
		/// 
		/// Sets the required window size, optionally can provide a window title and can combine some flags.
		/// See InitialisationFlags for options.
		/// </summary>
		///
		/// <param name="width">	  	[in,out] The width. </param>
		/// <param name="height">	  	[in,out] The height. </param>
		/// <param name="windowTitle">	(Optional) The window title. </param>
		/// <param name="flags">	  	(Optional) The flags, see \ref HAPISPACE::InitialisationFlags. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool Initialise(int &width, int &height, const std::string &windowTitle = std::string("HAPI Sprites"),
			unsigned int flags = eHSDefaults) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Create a surface from a texture, returns a shared pointer. </summary>
		///
		/// <param name="filename">	Filename of the texture. </param>
		///
		/// <returns>	The surface. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual std::shared_ptr<Surface> LoadSurface(const std::string &filename) const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Create a surface from scratch, returns a shared pointer. If filename is empty one is generated,
		/// colour defaults to Zero (all channels 0)
		/// </summary>
		///
		/// <param name="width">   	The width. </param>
		/// <param name="height">  	The height. </param>
		/// <param name="filename">	(Optional) Filename. </param>
		/// <param name="colour">  	(Optional) The colour. </param>
		///
		/// <returns>	The surface </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual std::shared_ptr<Surface> MakeSurface(int width, int height, std::string filename = std::string(), Colour255 colour = Colour255::ZERO) const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Creates a full (deep) copy of a surface, returns new shared pointer. </summary>
		///
		/// <param name="other"> Another instance to be copied. </param>
		///
		/// <returns> A new surface </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual std::shared_ptr<Surface> CopySurface(const std::shared_ptr<Surface> &other) const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Returns the screen surface. Prefer to use the shortcut SCREEN_SURFACE </summary>
		///
		/// <returns>	The screen surface. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual std::shared_ptr<Surface> GetScreenSurface() const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Add listener to get input events from mouse, keyboard or controller. Note: done automatically
		/// when you create a class derived from IHapiSpritesInputListener but here in case you want to
		/// remove and add again.
		/// </summary>
		///
		/// <param name="listener">	[in,out] The listener. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool AddInputListener(IHapiSpritesInputListener &listener) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Remove input event listener  done automatically at destruction of IHapiSpritesInputListener
		/// derived class.
		/// </summary>
		///
		/// <param name="listener">	[in,out] The listener. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool RemoveInputListener(IHapiSpritesInputListener &listener) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Load a SpriteSheet and create a sprite for it. This one has the advantage of loading full
		/// frame set data etc.
		/// </summary>
		///
		/// <param name="xmlFilename">	  	Filename of the XML file. </param>
		/// <param name="textureRootPath">	(Optional) Full pathname of the texture root file. </param>
		///
		/// <returns>	The sprite. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual std::unique_ptr<Sprite> LoadSprite(const std::string& xmlFilename, const std::string& textureRootPath = std::string()) const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Shortcut to create a surface, SpriteSheet and sprite (returned) from a texture filename.
		/// </summary>
		///
		/// <param name="textureFilename">	Filename of the texture file. </param>
		/// <param name="numFrames">	  	(Optional) Number of frames. </param>
		/// <param name="horizontal">	  	(Optional) True for horizontal lay out. </param>
		/// <param name="frameSetName">   	(Optional) Name of the frame set. </param>
		///
		/// <returns>	A std::unique_ptr&lt;Sprite&gt; </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual std::unique_ptr<Sprite> MakeSprite(const std::string& textureFilename, int numFrames = 1, bool horizontal = true, const std::string& frameSetName = std::string()) const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Make a sprite from an existing SpriteSheet. </summary>
		///
		/// <param name="spriteSheet">	The sprite sheet. </param>
		///
		/// <returns>	A std::unique_ptr&lt;Sprite&gt; </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual std::unique_ptr<Sprite> MakeSprite(std::shared_ptr<SpriteSheet> spriteSheet) const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Make a sprite from a surface - creates a default SpriteSheet. </summary>
		///
		/// <param name="surface">	The surface. </param>
		///
		/// <returns>	A std::unique_ptr&lt;Sprite&gt; </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual std::unique_ptr<Sprite> MakeSprite(std::shared_ptr<Surface> surface) const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Loads a SpriteSheet from an xml file. If texture not in same directory you can provide a path.
		/// to it.
		/// </summary>
		///
		/// <param name="xmlFilename">	  	Filename of the XML file. </param>
		/// <param name="textureRootPath">	(Optional) Full pathname of the texture root file. </param>
		///
		/// <returns>	The SpriteSheet. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual std::shared_ptr<SpriteSheet> LoadSpritesheet(const std::string& xmlFilename, const std::string& textureRootPath = std::string()) const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Create a spriteSheet from a surface and creates a basic frame layout. </summary>
		///
		/// <param name="textureFilename">	Filename of the texture file. </param>
		/// <param name="numFrames">	  	(Optional) Number of frames. </param>
		/// <param name="horizontal">	  	(Optional) True for horizontal layout. </param>
		///
		/// <returns>	A std::shared_ptr&lt;SpriteSheet&gt; </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual std::shared_ptr<SpriteSheet> MakeSpritesheet(const std::string& textureFilename, int numFrames = 1, bool horizontal = true) const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Creates a full copy of a SpriteSheet, returns new shared pointer. </summary>
		///
		/// <param name="other">	Other instance to copy. </param>
		///
		/// <returns>	A std::shared_ptr&lt;SpriteSheet&gt; </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual std::shared_ptr<SpriteSheet> CopySpritesheet(const std::shared_ptr<SpriteSheet> &other) const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Causes HAPI Sprites to close the main window and return false in the next update call.
		/// </summary>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool Close() = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// HAPI Sprites must be regularly updated via this call. Returns false when app is closing.
		/// </summary>
		///
		/// <returns>	True if it succeeds, false if HAPI Sprites is closing. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool Update() = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Tells HAPI Sprites to display (or not) the frames per second, defaults to upper left (0,0)
		/// </summary>
		///
		/// <param name="set">	(Optional) True to show. </param>
		/// <param name="x">  	(Optional) The x coordinate. </param>
		/// <param name="y">  	(Optional) The y coordinate. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool SetShowFPS(bool set = true, int x = 0, int y = 0) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Retrieve the current FPS (rounded to an int). </summary>
		///
		/// <returns>	The FPS. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual int GetFPS() const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Returns a structure with the current mouse state. </summary>
		///
		/// <returns>	The mouse data. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual const MouseData& GetMouseData() const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Returns a structure with the current keyboard state. </summary>
		///
		/// <returns>	The keyboard data. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual const KeyboardData& GetKeyboardData() const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Returns a structure with the specified controller's (up to GetMaxControllers) state 
		/// Note: you must check that the isAttached member is true.
		/// </summary>
		///
		/// <param name="controller">	The controller. </param>
		///
		/// <returns>	The controller data. Only valid if the isAttached member is true. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual const ControllerData& GetControllerData(int controller) const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Returns the maximum number of controller devices that could be installed (not how many
		/// actually are)
		/// </summary>
		///
		/// <returns>	The maximum controllers. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual int GetMaxControllers() const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Load a sound file, most formats are supported: ogg, wav, flac, aiff, au, raw, paf, svx, nist,
		/// voc, ircam, w64, mat4, mat5 pvf, htk, sds, avr, sd2, caf, wve, mpc2k, rf64.
		/// </summary>
		///
		/// <param name="filename">	Filename. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool LoadSound(const std::string &filename) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Plays a sound.
		/// Note: there is a hardware limit on how many sounds can be playing at once (1024 on PC but 32
		/// on mobiles)
		/// </summary>
		///
		/// <param name="filename">	Filename. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool PlaySound(const std::string &filename) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Plays a sound and also allows volume, pan etc. to be changed from the defaults. </summary>
		///
		/// <param name="filename">	Filename. </param>
		/// <param name="options"> 	Options for controlling the playback. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool PlaySound(const std::string &filename, const SoundOptions &options) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Plays a sound and also returns instanceId (for use when querying sound status) </summary>
		///
		/// <param name="filename">  	Filename. </param>
		/// <param name="options">   	Options for controlling the playback. </param>
		/// <param name="instanceId">	[in,out] Identifier for the instance. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool PlaySound(const std::string &filename, const SoundOptions &options, int &instanceId) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Stop a sound early. Use the id retrieved from PlaySound. </summary>
		///
		/// <param name="soundInstanceId">	Identifier for the sound instance. </param>
		/// <param name="togglePause">	  	(Optional) True to toggle pause. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool StopSound(int soundInstanceId, bool togglePause = false) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	You can change things like pitch, volume and loop as the sound is playing. </summary>
		///
		/// <param name="soundInstanceId">	[in,out] Identifier for the sound instance. </param>
		/// <param name="options">		  	Options for controlling the operation. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool ChangePlayingSoundOptions(int &soundInstanceId, const SoundOptions &options) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Retrieve info on a sound instance e.g. to see if it is paused, finished etc.
		/// </summary>
		///
		/// <param name="soundInstanceId"> 	Identifier for the sound instance. </param>
		/// <param name="playbackPosition">	[in,out] The playback position. </param>
		///
		/// <returns>	The sound status. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual const EMediaStatus GetSoundStatus(int soundInstanceId, float &playbackPosition) const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Plays streamed music using default options. </summary>
		///
		/// <param name="filename">		  	Filename. </param>
		/// <param name="startTimeOffset">	(Optional) The start time offset. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool PlayStreamedMedia(const std::string &filename, float startTimeOffset = 0.0f) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Plays streamed music and allows playback options to be set and instance obtained.
		/// </summary>
		///
		/// <param name="filename">		  	Filename. </param>
		/// <param name="options">		  	Options for controlling the operation. </param>
		/// <param name="instanceId">	  	[in,out] Identifier for the instance. </param>
		/// <param name="startTimeOffset">	(Optional) The start time offset. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool PlayStreamedMedia(const std::string &filename, const SoundOptions& options, int &instanceId, float startTimeOffset = 0.0f) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Restarts streamed media that has already been played (more efficient than reloading it)
		/// </summary>
		///
		/// <param name="instanceId">	  	Identifier for the instance. </param>
		/// <param name="startTimeOffset">	(Optional) The start time offset. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool PlayStreamedMedia(int instanceId, float startTimeOffset = 0.0f) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Stops streaming media started via PlayStreamedMedia. </summary>
		///
		/// <param name="instanceId">	Identifier of the instance. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool StopStreamedMedia(int instanceId) const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Pause or unpause streamed media started with PlayStreamedMedia. </summary>
		///
		/// <param name="instanceId">	Identifier for the instance. </param>
		/// <param name="pause">	 	(Optional) True to pause. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool PauseStreamedMedia(int instanceId, bool pause = true) const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Returns info about the media playback e.g. like current position. </summary>
		///
		/// <param name="instanceId">	Identifier for the instance. </param>
		///
		/// <returns>	The streamed media information. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual const StreamedMediaInfo& GetStreamedMediaInfo(int instanceId) const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Allows the font to be changed. This version uses fonts registered with the OS.
		/// Subsequent text operations will use this font. (Note: the UI has its own system)
		/// </summary>
		///
		/// <param name="fontName">	Name of the font. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool ChangeFont(const std::string &fontName) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Allows the font to be changed. This version allows it to be loaded from a file.
		/// </summary>
		///
		/// <param name="fontFilename">	Filename of the font file. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool ChangeFontFromFile(const std::string &fontFilename) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Allows text to be drawn on the screen at a position and with a specified fill colour with the
		/// current font. Text size and flags for bold, italic etc. are optional. Note: you can also do
		/// SCREEN_SURFACE.DrawText.
		/// </summary>
		///
		/// <param name="x">		 	The x coordinate. </param>
		/// <param name="y">		 	The y coordinate. </param>
		/// <param name="fillColour">	The fill colour. </param>
		/// <param name="text">		 	The text. </param>
		/// <param name="textSize">  	(Optional) Size of the text. </param>
		/// <param name="styleFlags">	(Optional) The style flags. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool RenderText(int x, int y, const Colour255 &fillColour, const std::string& text,
			int textSize = 12, unsigned int styleFlags = eRegular) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Render text Version taking a vector. Note: you can also do SCREEN_SURFACE.DrawText.
		/// </summary>
		///
		/// <param name="p">		 	Position. </param>
		/// <param name="fillColour">	The fill colour. </param>
		/// <param name="text">		 	The text. </param>
		/// <param name="textSize">  	(Optional) Size of the text. </param>
		/// <param name="styleFlags">	(Optional) The style flags. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool RenderText(VectorI p, const Colour255 &fillColour, const std::string& text,
			int textSize = 12, unsigned int styleFlags = eRegular) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// As above but allows you to specify another colour to act as an outline to the text and how
		/// thick it should be Note: you can also do SCREEN_SURFACE.DrawText. Can also supply a clip area.
		/// </summary>
		///
		/// <param name="x">			   	The x coordinate. </param>
		/// <param name="y">			   	The y coordinate. </param>
		/// <param name="fillColour">	   	The fill colour. </param>
		/// <param name="outlineColour">   	The outline colour. </param>
		/// <param name="outlineThickness">	The outline thickness. </param>
		/// <param name="text">			   	The text. </param>
		/// <param name="pointSize">	   	(Optional) Size of the font. </param>
		/// <param name="styleFlags">	   	(Optional) The style flags. </param>
		/// <param name="clipArea">		   	(Optional) The clip area. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool RenderText(int x, int y, const Colour255 &fillColour, const Colour255 &outlineColour,
			float outlineThickness, const std::string& text, int pointSize = 12, unsigned int styleFlags = eRegular,
			RectangleI clipArea = RectangleI()) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// This one allows you to specify a memory buffer to write to. Assumes 32 bit and that surface
		/// points to surfaceWidth * surfaceHeight * 4 bytes. Can also supply a clip area.
		/// </summary>
		///
		/// <param name="x">			   	The x coordinate. </param>
		/// <param name="y">			   	The y coordinate. </param>
		/// <param name="fillColour">	   	The fill colour. </param>
		/// <param name="outlineColour">   	The outline colour. </param>
		/// <param name="outlineThickness">	The outline thickness. </param>
		/// <param name="text">			   	The text. </param>
		/// <param name="surface">		   	[in,out] If non-null, the surface. </param>
		/// <param name="surfaceWidth">	   	Width of the surface. </param>
		/// <param name="surfaceHeight">   	Height of the surface. </param>
		/// <param name="textSize">		   	(Optional) Size of the text. </param>
		/// <param name="styleFlags">	   	(Optional) The style flags. </param>
		/// <param name="writeAlpha">	   	(Optional) True to write alpha. </param>
		/// <param name="clipArea">		   	(Optional) The clip area. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool RenderText(int x, int y, Colour255 fillColour, Colour255 outlineColour,
			float outlineThickness, const std::string& text, BYTE *surface, int surfaceWidth, int surfaceHeight,
			int textSize = 12, unsigned int styleFlags = eRegular, bool writeAlpha = true, RectangleI clipArea = RectangleI()) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Allows the size of the text to be calculated. Returns the size in a rectangle.
		/// </summary>
		///
		/// <param name="text">			   	The text. </param>
		/// <param name="pointSize">	    Text point size. </param>
		/// <param name="styleFlags">	   	(Optional) The style flags. </param>
		/// <param name="outlineThickness">	(Optional) The outline thickness. </param>
		///
		/// <returns>	The text size. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual RectangleI GetTextSize(const std::string& text, int pointSize, unsigned int styleFlags = eRegular, float outlineThickness = 0) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Helper to determine if a file exists on disk. </summary>
		///
		/// <param name="filename">	Full path and filename of the file. </param>
		///
		/// <returns>	True if it does, false if it does not. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool DoesFileExist(const std::string &filename) const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Tells HAPI Sprites to display or not the cursor (mouse pointer) </summary>
		///
		/// <param name="set">	True to display. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool SetShowCursor(bool set) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Returns text interpreted by the OS i.e. takes localization into account. </summary>
		///
		/// <returns>	The entered text. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual char GetEnteredText() const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Brings up one of the internal apps. Note that all user code will now not operate until the
		/// app is closed. Current choices are eSpriteEditor, eSkinEditor, eUiEditor. Also can be accessed
		/// via SHIFT-F1 when running as a non distributable.
		/// </summary>
		///
		/// <param name="which"> Which app. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void LaunchInternalApp(EInternalApp which) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Sets the rumble motor speeds for the specified controller. </summary>
		///
		/// <param name="controller">	The controller index. </param>
		/// <param name="leftMotor"> 	The left motor. </param>
		/// <param name="rightMotor">	The right motor. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool SetControllerRumble(int controller, WORD leftMotor, WORD rightMotor) const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// If a HAPI Sprites call fails this can be used to retrieve the error code and system the error
		/// occurred in (see enum and documentation for more details on errors as well as the output pane
		/// in viz and the generated log)
		/// </summary>
		///
		/// <param name="system">	[in,out] The system. </param>
		///
		/// <returns>	The last error. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual EErrorCodes GetLastError(HAPI_System &system) const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Returns the time since HAPI Sprites was initialised in milliseconds. </summary>
		///
		/// <returns>	The time. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual DWORD GetTime() const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Display a message box to the user, returns affirmative or not. </summary>
		///
		/// <param name="text">		 	The text to show in the middle of the dialog. </param>
		/// <param name="title">	 	(Optional) The title text. </param>
		/// <param name="buttonType">	(Optional) Type of buttons to use. </param>
		///
		/// <returns>	An EUserResponse. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual EUserResponse UserMessage(const std::string &text, const std::string& title = "Message", EMessageButtonType buttonType = EMessageButtonType::eButtonTypeOk) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Displays a modal dialog box to get input from the user. </summary>
		///
		/// <param name="question">   	The question. </param>
		/// <param name="result">	  	[in,out] The result. </param>
		/// <param name="initialText">	(Optional) The initial text. </param>
		/// <param name="dialogWidth">	(Optional) Width of the dialog. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool UserTextEntry(const std::string &question, std::string &result,
			std::string initialText = std::string(), int dialogWidth = 0) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Display a file open or file save dialog. Opens at the programs current working directory, this
		/// can be changed if required via the optional parameter.
		/// </summary>
		///
		/// <param name="filters">		   	The file extension filters. </param>
		/// <param name="saveAsDialog">	   	True to save as dialog. </param>
		/// <param name="filename">		   	[in,out] Filename. </param>
		/// <param name="response">		   	[in,out] The response. </param>
		/// <param name="startDirectory">  	(Optional) Pathname of the start directory. </param>
		/// <param name="selectFolderOnly">	(Optional) True to select a folder only. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool FileDialog(const std::vector<FileDialogFilters>& filters, bool saveAsDialog,
			std::string &filename, HAPI_UserResponse &response,
			const std::string& startDirectory = std::string(), bool selectFolderOnly = false) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	As above but specifically to allow multiple file selection. </summary>
		///
		/// <param name="filters">		 	The filters. </param>
		/// <param name="filenames">	 	[in,out] The filenames. </param>
		/// <param name="response">		 	[in,out] The response. </param>
		/// <param name="startDirectory">	(Optional) Pathname of the start directory. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool FileDialogMultipleSelect(const std::vector<FileDialogFilters>& filters,
			std::vector<std::string> &filenames, HAPI_UserResponse &response,
			const std::string& startDirectory = std::string()) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Allows the icon shown in the window and task bar to be changed from the default HAPI Sprites logo.
		/// </summary>
		///
		/// <param name="surface">	The surface. </param>
		/// <param name="width">  	The width. </param>
		/// <param name="height"> 	The height. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool SetIcon(const std::shared_ptr<Surface> &surface, int width, int height) const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Retrieve the directory the exe is running from. </summary>
		///
		/// <returns>	The executable directory. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual std::string GetExecutableDirectory() const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Retrieve the working directory. Useful as a root for then finding data files. This is normally
		/// where the visual studio project file is, if running under viz, otherwise it is where the
		/// executable is.
		/// </summary>
		///
		/// <returns>	The working directory. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual std::string GetWorkingDirectory() const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Saves the log to disk early. It always gets saved on exit but there are cases where you may want
		/// to dump it sooner.
		/// </summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void WriteLogSoFar() const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Helper function that simply divides a filename into its parts. </summary>
		///
		/// <param name="filename">	Filename </param>
		///
		/// <returns>	The parts in the FilenameParts structure. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual FilenameParts SplitFilename(const std::string &filename) const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Enables the UI functionality in HAPI Sprites. Not needed if initialised with eHSEnableUI flag.
		/// </summary>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool EnableUI() = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Returns the UI system. Note: UI must be created first either via start up flag or by calling EnableUI
		/// </summary>
		///
		/// <returns>	The user interface system. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual HAPI_UI_SPACE::UISystem& GetUISystem() const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Get text in windows clipboard. </summary>
		///
		/// <returns>	The clipboard text. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual std::string GetClipboardText() const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Set text in windows clipboard. </summary>
		///
		/// <param name="newText">	The new text. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void SetClipboardText(const std::string &newText) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	HAPI Sprites Version as a string. </summary>
		///
		/// <returns>	The version. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual std::string GetVersion() const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Allows access to the raw sample data of a sound. Note: to see how to interpret the raw data
		/// use the values from SoundFormat.
		/// </summary>
		///
		/// <param name="filename"> 	Filename. </param>
		/// <param name="rawData">  	[in,out] The raw data. </param>
		/// <param name="soundInfo">	[in,out] Information describing the sound. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool GetSoundRawData(const std::string& filename, std::vector<SWORD>& rawData, SoundFormat &soundInfo) const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Allows changing a sound's sample data. Note: if sound is currently playing it will be stopped.
		/// </summary>
		///
		/// <param name="filename"> 	Filename. </param>
		/// <param name="rawData">  	The raw data. </param>
		/// <param name="soundInfo">	Information describing the sound. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool SetSoundRawData(const std::string& filename, const std::vector<SWORD>& rawData, const SoundFormat &soundInfo) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Allows a sound to be created from scratch. </summary>
		///
		/// <param name="name">			The sound name. </param>
		/// <param name="rawData">  	The raw data. </param>
		/// <param name="soundInfo">	Information describing the sound. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool CreateSound(const std::string& name, const std::vector<SWORD>& rawData, const SoundFormat &soundInfo) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Saves a sound under a new filename. Supported formats (derived from filename extension) : ogg,
		/// wav, flac, aiff, au, raw, paf, svx, nist, voc, ircam, w64, mat4, mat5 pvf, htk, sds, avr, sd2,
		/// caf, wve, mpc2k, rf64.
		/// </summary>
		///
		/// <param name="name">		  	The name. </param>
		/// <param name="newFilename">	The new filename. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool SaveSound(const std::string& name, const std::string& newFilename) const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Limits the frame rate. </summary>
		///
		/// <param name="framesPerSecondLimit">	The frames per second limit. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void LimitFrameRate(int framesPerSecondLimit) const =0;
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Returns the HAPI Sprites instance, prefer to use the HAPI_Sprites macro.
/// </summary>
///
/// <returns>	The HAPI sprites instance. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
HAPISPACE::IHapiSprites& GetHAPI_Sprites();

/// <summary>	The HAPI Sprites instance macro. A shortcut to GetHAPI_Sprites. </summary>
#define HAPI_Sprites GetHAPI_Sprites()

/// <summary>	Another shortcut, this time to the, always present, screen surface. </summary>
#define SCREEN_SURFACE HAPI_Sprites.GetScreenSurface()

/// <summary>
/// Provides access to the UI system. Make sure you have created it first either via init flag or
/// direct call and included &lt;HAPISprites_UI.h&gt;
/// </summary>
#define UI HAPI_Sprites.GetUISystem()