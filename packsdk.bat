rem @echo off

set VSERION=0.1.0

rmdir /s /q pkzo-%VSERION%
mkdir pkzo-%VSERION%

mkdir pkzo-%VSERION%\include
mkdir pkzo-%VSERION%\include\pkzo
xcopy /s pkzo\*.h pkzo-%VSERION%\include\pkzo
mkdir pkzo-%VSERION%\include\rgm
xcopy /s ext\rgm-0.1.1\include\rgm\*.h pkzo-%VSERION%\include\rgm

mkdir pkzo-%VSERION%\x86\Debug
copy x86\Debug\*.dll pkzo-%VSERION%\x86\Debug
copy x86\Debug\pkzo*.lib pkzo-%VSERION%\x86\Debug
copy x86\Debug\pkzo*.pdb pkzo-%VSERION%\x86\Debug
copy ext\SDL2-2.0.7\lib\x86\*.dll pkzo-%VSERION%\x86\Debug
copy ext\SDL2_image-2.0.1\lib\x86\*.dll pkzo-%VSERION%\x86\Debug
copy ext\SDL2_ttf-2.0.14\lib\x86\*.dll pkzo-%VSERION%\x86\Debug

mkdir pkzo-%VSERION%\x86\Release
copy x86\Release\*.dll pkzo-%VSERION%\x86\Release
copy x86\Release\pkzo*.lib pkzo-%VSERION%\x86\Release
copy x86\Release\pkzo*.pdb pkzo-%VSERION%\x86\Release
copy ext\SDL2-2.0.7\lib\x86\*.dll pkzo-%VSERION%\x86\Release
copy ext\SDL2_image-2.0.1\lib\x86\*.dll pkzo-%VSERION%\x86\Release
copy ext\SDL2_ttf-2.0.14\lib\x86\*.dll pkzo-%VSERION%\x86\Release

mkdir pkzo-%VSERION%\x64\Debug
copy x64\Debug\*.dll pkzo-%VSERION%\x64\Debug
copy x64\Debug\pkzo*.lib pkzo-%VSERION%\x64\Debug
copy x64\Debug\pkzo*.pdb pkzo-%VSERION%\x64\Debug
copy ext\SDL2-2.0.7\lib\x64\*.dll pkzo-%VSERION%\x86\Debug
copy ext\SDL2_image-2.0.1\lib\x64\*.dll pkzo-%VSERION%\x64\Debug
copy ext\SDL2_ttf-2.0.14\lib\x64\*.dll pkzo-%VSERION%\x64\Debug

mkdir pkzo-%VSERION%\x64\Release
copy x64\Release\*.dll pkzo-%VSERION%\x64\Release
copy x64\Release\pkzo*.lib pkzo-%VSERION%\x64\Release
copy x64\Release\pkzo*.pdb pkzo-%VSERION%\x64\Release
copy ext\SDL2-2.0.7\lib\x64\*.dll pkzo-%VSERION%\x86\Release
copy ext\SDL2_image-2.0.1\lib\x64\*.dll pkzo-%VSERION%\x64\Release
copy ext\SDL2_ttf-2.0.14\lib\x64\*.dll pkzo-%VSERION%\x64\Release

copy README.md pkzo-%VSERION%