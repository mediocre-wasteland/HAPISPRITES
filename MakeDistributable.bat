del /s /q Demo\*.*
rd Demo
md Demo
md Demo\Data
md Demo\Data\Levels
md Demo\Data\Sounds
md Demo\Data\Sprites
md Demo\Data\UserInterface
md Demo\Data\Sounds\Running

copy HAPI_App\HAPI_SPRITES\Libs64 Demo\
copy HAPI_App\Data Demo\Data\
copy HAPI_App\Data\Levels Demo\Data\Levels
copy HAPI_App\Data\Sounds Demo\Data\Sounds
copy HAPI_App\Data\Sprites Demo\Data\Sprites
copy HAPI_App\Data\UserInterface Demo\Data\UserInterface
copy HAPI_APP\Data\Sounds\Running Demo\Data\Sounds\Running
copy x64\Release\HAPI_APP.exe Demo\Demo.exe
