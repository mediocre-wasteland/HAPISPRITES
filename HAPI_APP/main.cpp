/*
	HAPI Sprites Start
	------------------
	This solution contains an already set up HAPI Sprites project and this main file with brief example code
	Release and Debug configurations for 64 bit builds are configured for you (32 bit is not supported).
	
	The directory structure and main files are:

	HAPISprites_Start - contains the Visual Studio solution file (HAPI_APP.sln)
		HAPI_APP - contains the Visual Studio HAPI_APP project file (HAPI_APP.vcxproj) and source code
			HAPI_SPRITES - the directory with all the HAPI library files including GLM
			Data - a place to put all your data files

		MakeDistributable.bat - a batch file for populating a Demo folder for stand alone running
		Clean.bat  - a batch file to remove all the Viz temporary files and hence reduce the size of the folder		
		Note: this should be run with Visual Studio closed

	Last updated: Keith Ditchburn 17/01/19
*/

#include "World.h"

void HAPI_Sprites_Main()
{
	World gameWorld;

	if (!gameWorld.Initialise())
	{
		return;
	}

	if (!gameWorld.Play())
	{
		return;
	}
}
