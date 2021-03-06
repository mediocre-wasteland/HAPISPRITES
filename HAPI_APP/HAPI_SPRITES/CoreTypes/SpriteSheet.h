////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	SpriteSheet.h
//
// summary:	Declares the sprite sheet class
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Frame.h"

namespace HAPISPACE {

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// A SpriteSheet has a surface and a number of frame descriptions. RULES: every frame must have a
	/// name and every frame name must be unique within the SpriteSheet.
	/// </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class SpriteSheet
	{
	private:
		std::vector<Frame> m_frames;
		std::shared_ptr<Surface> m_surface;

		//std::map<VectorI, VectorF> m_normals;
		
		// From 0.86 switched to using a 2D array for the normals for performance reasons
		std::unique_ptr<VectorF[]> m_normals;

		// Used for PP collisions and also normal generation
		BYTE m_minAlphaForCollision{ 255 };

		// Editor internal access
		friend class SpriteEditor;
		friend class SpriteEditorMainWindow;
		friend class SpriteEditorPayloadData;
		friend class SpriteEditorCopyWindow;
		friend class SpriteEditorToolboxWindow;

		// Potentially slow. Returns null if none
		Frame* GetFrameAtPoint(VectorI pnt) ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Editor get frames. Direct write access to frame data for editor use only. NOTE: if you add a
		/// frame or change position of one you must call m_shared->spriteSheet->SortFrames();
		/// </summary>
		///
		/// <returns>	A reference to a std::vector&lt;Frame&gt; </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::vector<Frame>& EditorGetFrames() { return m_frames; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets a frame by name. </summary>
		///
		/// <param name="name">	The name. </param>
		///
		/// <returns>	Null if it fails, else the frame. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Frame* GetFrameByName(const std::string& name);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Check if pixel in frame has alpha >= minAlpha (for collisions) </summary>
		///
		/// <param name="frame">   	The frame. </param>
		/// <param name="pnt">	   	The point. </param>
		/// <param name="minAlpha">	The minimum alpha. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool CheckPixel(const Frame& frame, VectorI pnt, BYTE minAlpha);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Fits a tight circle around data in the frame. </summary>
		///
		/// <param name="circle">  	[in,out] The circle. </param>
		/// <param name="frame">   	[in,out] The frame. </param>
		/// <param name="minAlpha">	The minimum alpha considered to be solid. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void FitCircle(Circle &circle, Frame& frame, BYTE minAlpha);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Fits a tight rectangle around data in the frame. </summary>
		///
		/// <param name="rect">	   	[in,out] The rectangle. </param>
		/// <param name="minAlpha">	The minimum alpha considered to be solid. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void FitRect(RectangleI &rect, BYTE minAlpha);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	When using frame sets, the frame index returned here != frame number. </summary>
		///
		/// <param name="frameSetName">  	Name of the frame set. </param>
		/// <param name="frameSetNumber">	The frame set number. </param>
		///
		/// <returns>	The frame number in set. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		int GetFrameNumberInSet(const std::string& frameSetName, int frameSetNumber) const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Load. </summary>
		///
		/// <param name="byteStream">	XML byte stream </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void ParseXML(const std::vector<BYTE>& byteStream);

		/// <summary>	Editor needs frames to always be sorted. </summary>
		void SortFrames();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Saves the XML. </summary>
		///
		/// <returns>	Null if it fails, else a pointer to a CHapiXMLNode. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		CHapiXMLNode* SaveXML() const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets the neighbours for breadth search. </summary>
		///
		/// <param name="pnt">	The point. </param>
		/// <param name="w">  	The width. </param>
		/// <param name="h">  	The height. </param>
		///
		/// <returns>	The neighbours. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::vector<VectorI> GetNeighbours(VectorI pnt, int w, int h);

		mutable std::string m_filename{ "noname.xml" };
	public:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor. </summary>
		///
		/// <param name="surface">		   	The surface. </param>
		/// <param name="numFrames">	   	(Optional) Number of frames. </param>
		/// <param name="layoutHorizontal">	(Optional) True for horizontal layout. </param>
		/// <param name="frameSetName">	   	(Optional) Name of the frame set. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		SpriteSheet(std::shared_ptr<Surface> surface, unsigned int numFrames = 1, bool layoutHorizontal = true, const std::string& frameSetName = std::string());

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Allows creation from a provided vector of Frame representing the frames within the surface.
		/// </summary>
		///
		/// <param name="surface">	The surface. </param>
		/// <param name="frames"> 	The frames. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		SpriteSheet(std::shared_ptr<Surface> surface, std::vector<Frame> frames);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Allows creation from an existing Surface and an XML file that describes the layout.
		/// </summary>
		///
		/// <param name="surface">	  	The surface. </param>
		/// <param name="xmlFilename">	Filename of the XML file. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		SpriteSheet(std::shared_ptr<Surface> surface, const std::string& xmlFilename);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Allows creation of a new surface and SpriteSheet from an XML file that describes the layout.
		/// </summary>
		///
		/// <param name="xmlFilename">	  	Filename of the XML file. </param>
		/// <param name="textureRootPath">	(Optional) Full pathname of the texture root file if different. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		SpriteSheet(const std::string& xmlFilename, const std::string& textureRootPath = std::string());

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Allows creation of a new surface and SpriteSheet from an XML byte stream that describes the layout.
		/// </summary>
		///
		/// <param name="xmlByteSteam">	The XML byte steam. </param>
		/// <param name="texturePath"> 	(Optional) Full pathname of the texture file. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		SpriteSheet::SpriteSheet(const std::vector<BYTE> &xmlByteSteam, const std::string& texturePath = std::string());

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Copy constructor, allocates memory and copies raw data - deep copy. </summary>
		///
		/// <param name="other">	The other SpriteSheet. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		SpriteSheet(const SpriteSheet &other);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Copy constructor, allocates memory and copies raw data - deep copy. </summary>
		///
		/// <param name="other">	The other SpriteSheet. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		SpriteSheet(const std::shared_ptr<SpriteSheet> &other);

		~SpriteSheet() = default;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Retrieves original filename (if there is one) otherwise noname.xml. </summary>
		///
		/// <returns>	The filename. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const std::string& GetFilename() const { return m_filename; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Checks integrity including checking the following rules
		/// - every frame has a name
		/// - every frame name is unique
		/// - any frame sets have sequential numbering.
		/// </summary>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool Validate() const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Min alpha defaults to 255 meaning collisions occur only when alpha is 255. This function
		/// allows you to lower that amount. NOTE: any surface normal calculations will need recalculating
		/// (not done automatically)
		/// </summary>
		///
		/// <param name="minAlpha">	The minimum alpha. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void SetMinimumAlphaForCollision(BYTE minAlpha) { m_minAlphaForCollision = minAlpha; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets minimum alpha for collision. </summary>
		///
		/// <returns>	The minimum alpha for collision. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		BYTE GetMinimumAlphaForCollision() const { return m_minAlphaForCollision; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Generate normals. Can be slow. Note: uses current value of m_minAlphaForCollision.
		/// </summary>
		///
		/// <param name="smoothingAmount">	(Optional) The smoothing amount. Defaults to not doing smoothing. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void GenerateNormals(int smoothingAmount=0);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets a normal, if generated, otherwise returns Zero vector. </summary>
		///
		/// <param name="surfacePosition">	The surface position. </param>
		///
		/// <returns>	The normal. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		VectorF GetNormal(VectorI surfacePosition) const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets read access to the surface the SpriteSheet uses. </summary>
		///
		/// <returns>	The surface. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const std::shared_ptr<Surface>& GetSurface() const { return m_surface; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets read / write access to the surface the SpriteSheet uses. </summary>
		///
		/// <returns>	The surface. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::shared_ptr<Surface> GetSurface() { return m_surface; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Returns the number of frames. Optionally can limit to the number in a frame set.
		/// </summary>
		///
		/// <param name="setName">	(Optional) Name of the frame set. </param>
		///
		/// <returns>	The number of frames. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		int GetNumFrames(const std::string &setName = std::string()) const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Does a frame with this name exist? </summary>
		///
		/// <param name="frameName">	Name of the frame. </param>
		///
		/// <returns>	True if it exist, false if it does not. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool GetFrameExists(const std::string& frameName) const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Does a frame set with this name exist? </summary>
		///
		/// <param name="frameSetName">	Name of the frame set. </param>
		///
		/// <returns>	True if it exist, false if it does not </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool GetFrameSetExists(const std::string& frameSetName) const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Returns a vector of all frameset names. </summary>
		///
		/// <returns>	The frame set names. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::vector<std::string> GetFrameSetNames() const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Returns a unique frame name. </summary>
		///
		/// <param name="root">	The name root. </param>
		///
		/// <returns>	The unique name. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::string GetUniqueName(const std::string root) const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Get the rectangle for a frame and hence the size. </summary>
		///
		/// <param name="frameNum">	   	The frame number. </param>
		/// <param name="frameSetName">	(Optional) Name of the frame set. </param>
		///
		/// <returns>	The frame rectangle. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		RectangleI GetFrameRect(unsigned int frameNum, const std::string& frameSetName = std::string()) const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Get collider group for this frame. </summary>
		///
		/// <param name="frameNum">	   	The frame number. </param>
		/// <param name="frameSetName">	(Optional) Name of the frame set. </param>
		///
		/// <returns>	The frame collider. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const ColliderGroup& GetFrameCollider(unsigned int frameNum, const std::string& frameSetName = std::string()) const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Read access to a frame. </summary>
		///
		/// <param name="frameNum">	   	The frame number. </param>
		/// <param name="frameSetName">	(Optional) Name of the frame set. </param>
		///
		/// <returns>	The frame. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const Frame& GetFrame(unsigned int frameNum, const std::string& frameSetName = std::string()) const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Return the read only information for all frames. </summary>
		///
		/// <returns>	all frames. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const std::vector<Frame>& GetAllFrames() const { return m_frames; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Completely replace the frame information. Note: if sort set to true frames are sorted from top
		/// left to bottom right in row order.
		/// </summary>
		///
		/// <param name="newFrames">	The new frames. </param>
		/// <param name="sort">			(Optional) True to sort. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void ModifyFrames(std::vector<Frame> newFrames, bool sort = false);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Deletes the frame with this name (and collider data). Warning: this can be slow.
		/// </summary>
		///
		/// <param name="frameName">	Name of the frame. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void DeleteFrame(const std::string frameName);

		/// <summary>	Removes all frames and collider data. </summary>
		void DeleteAllFrames();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Automatically finds frames in the image by finding solid blocks of colour (with alpha >
		/// minAlpha)
		/// How well it works will depend if there are gaps between frames in the image. Warning: replaces
		/// all existing frame data if removeExistingFrames is true.
		/// </summary>
		///
		/// <param name="removeExistingFrames">	(Optional) True to remove existing frames. </param>
		/// <param name="minAlpha">			   	(Optional) The minimum alpha. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void AutoFindFrames(bool removeExistingFrames = false, BYTE minAlpha = 1 );

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Divides a surface up into equally sized frames. Replaces all existing frame data. </summary>
		///
		/// <param name="numX">	Number of frames in x. </param>
		/// <param name="numY">	Number of frames in y. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void GridFrames(int numX, int numY);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Searches out from pos to find extents of a frame. Returns name of new frame or empty string if
		/// none
		/// </summary>
		///
		/// <param name="searchPoint">	The search point. </param>
		/// <param name="minAlpha">   	(Optional) The minimum alpha. </param>
		///
		/// <returns>	name of new frame or empty string if none</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::string AutoFindFrame(VectorI searchPoint,BYTE minAlpha = 1);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Delete a collider. Collider names are not unique per SpriteSheet so you need to specify the
		/// frame name as well (which is unique)
		/// </summary>
		///
		/// <param name="frameName">   	Name of the frame. </param>
		/// <param name="colliderName">	Name of the collider. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool DeleteCollider(const std::string& frameName, const std::string& colliderName);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Check if sprite is valid / loaded correctly. </summary>
		///
		/// <returns>	True if valid, false if not </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool HasData() const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Saves an XML file describing the layout of the surface. Optionally saves the surface as well
		/// (in the same directory)
		/// </summary>
		///
		/// <param name="filename">   	Filename. </param>
		/// <param name="saveSurface">	(Optional) True to save surface. </param>
		///
		/// <returns>	True if it succeeds, false if it fails. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool SaveAsXML(const std::string& filename, bool saveSurface = false) const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Saves to a byte stream. </summary>
		///
		/// <returns>	A std::vector&lt;BYTE&gt; Empty on error.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::vector<BYTE> SaveToByteStream() const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Creates a new SpriteSheet with a new surface which is made up solely of areas in the frame
		/// collection. This is useful for trimming away dead areas or for making more cache friendly. If
		/// alongX is true then frames are added left to right. If alongX is false then frames are added
		/// top to bottom (the default, as this is best cache friendly method). Can also limit to a frame
		/// set (or provide an empty string for all). Note: does memory allocation so potentially slow.
		/// </summary>
		///
		/// <param name="alongX">  	(Optional) True to create along x coordinate. </param>
		/// <param name="frameSet">	(Optional) Set the frame set. </param>
		///
		/// <returns>	The new compacted. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::unique_ptr<SpriteSheet> CreateCompacted(bool alongX = false, const std::string& frameSet = std::string()) const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Joins two SpriteSheets together to create a third. If alongX is true then other sprite is
		/// added to the right of this. If alongX is false then other sprite is added below this. Note:
		/// does memory allocation so potentially slow.
		/// </summary>
		///
		/// <param name="other">	The other sheet. </param>
		/// <param name="dir">  	(Optional) The direction to add. </param>
		///
		/// <returns>	The new combined SpriteSheet. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::unique_ptr<SpriteSheet> CreateCombined(const std::shared_ptr<SpriteSheet>& other, EDirection dir = EDirection::eEast) const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Flips image data for each frame and creates a new frame with extension _flipHoriz. You can
		/// specify which frame set to process (empty string for all) and a frame set name for the new
		/// frames. Currently only supports horizontal flip (TODO). Horizontal of true means frames laid
		/// out along x otherwise down y. Useful if you have a character graphic facing one way and need
		/// it to face another way as well. Not for real time use, does lots of memory allocation and
		/// copying. Creates and returns a new SpriteSheet, does not modify existing.
		/// </summary>
		///
		/// <param name="whichFrameSet">  	(Optional) For which frame set. </param>
		/// <param name="newFrameSetName">	(Optional) Name of the new frame set. </param>
		/// <param name="horizontal">	  	(Optional) True to flip horizontal. </param>
		///
		/// <returns>	The new flipped frames SpriteSheet. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::unique_ptr<SpriteSheet> CreateFlippedFrames(const std::string& whichFrameSet = std::string(), const std::string& newFrameSetName = std::string(), bool horizontal = false) const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Creates a new surface repeating the image num times (mip mapping). Each time scaleX, scaleY
		/// is different in size. Then creates a new sprite with frame data set to each of the repeats.
		/// If alongX is true then scaled surfaces are added horizontally, if alongX is false then scaled
		/// surfaces are added vertically. Be careful! The resulting surface could become enormous if
		/// your scale factors are too high.
		/// </summary>
		///
		/// <param name="scaleX">	The scale x coordinate. </param>
		/// <param name="scaleY">	The scale y coordinate. </param>
		/// <param name="num">   	Number of sizes. </param>
		/// <param name="alongX">	(Optional) True to lay out along x coordinate. </param>
		/// <param name="filter">	(Optional) Specifies the filter. </param>
		///
		/// <returns>	The new sizes. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::unique_ptr<SpriteSheet> CreateSizes(float scaleX, float scaleY, int num, bool alongX = true, EFilter filter = EFilter::eBilinear) const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Creates a new surface for each frame of this SpriteSheet. They are saved under a filename
		/// generated as: [surface name]_[Frame name].png. Returns a vector with all the new filenames.
		/// You can specify destination directory and file type (via the extension).
		/// </summary>
		///
		/// <param name="directory">	Path. </param>
		/// <param name="extension">	(Optional) The extension. </param>
		///
		/// <returns>	The saved file names </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::vector<std::string> SaveFramesAsImages(const std::string &directory, std::string extension = ".png") const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Reduce collider sizes to tightest fit. Note: uses current value of m_minAlphaForCollision.
		/// </summary>
		///
		/// <param name="limitToFrame">	(Optional) The frame to limit to. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void AutoFitColliders(const std::string& limitToFrame=std::string());

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Sets colliders back to defaults (a bounding rectangle and a circle around it and loose fit)
		/// </summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void ResetColliders();
	};
}