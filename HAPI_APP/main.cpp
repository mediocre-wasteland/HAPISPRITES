/*
	HAPI Sprites Start
	------------------

		MakeDistributable.bat - a batch file for populating a Demo folder for stand alone running
		Clean.bat  - a batch file to remove all the Viz temporary files and hence reduce the size of the folder		
		Note: this should be run with Visual Studio closed

	Last updated: Keith Ditchburn 17/01/19
*/

#include "World.h"

//Check for memory leaks
#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

void HAPI_Sprites_Main()
{
	//Create an instance of the game world
	World gameWorld;

	if (!gameWorld.Initialise())
	{
		return;
	}
}
