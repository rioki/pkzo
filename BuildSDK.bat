rem @echo off

call "%VS140COMNTOOLS%\..\..\vc\vcvarsall.bat" x86

msbuild pkzo.sln /t:Build /p:Configuration=Debug /p:Platform="x86" /m:3
msbuild pkzo.sln /t:Build /p:Configuration=Release /p:Platform="x86" /m:3

call "%VS140COMNTOOLS%\..\..\vc\vcvarsall.bat" x64

msbuild pkzo.sln /t:Build /p:Configuration=Debug /p:Platform="x64" /m:3
msbuild pkzo.sln /t:Build /p:Configuration=Release /p:Platform="x64" /m:3

rmdir /s /q pkzo-0.1.0
mkdir pkzo-0.1.0

mkdir pkzo-0.1.0\include
xcopy /s include pkzo-0.1.0\include

mkdir pkzo-0.1.0\x86\Debug
copy x86\Debug\*.dll pkzo-0.1.0\x86\Debug
copy x86\Debug\pkzo*.lib pkzo-0.1.0\x86\Debug
copy x86\Debug\pkzo*.pdb pkzo-0.1.0\x86\Debug

mkdir pkzo-0.1.0\x86\Release
copy x86\Release\*.dll pkzo-0.1.0\x86\Release
copy x86\Release\pkzo*.lib pkzo-0.1.0\x86\Release
copy x86\Release\pkzo*.pdb pkzo-0.1.0\x86\Release

mkdir pkzo-0.1.0\x64\Debug
copy x64\Debug\*.dll pkzo-0.1.0\x64\Debug
copy x64\Debug\pkzo*.lib pkzo-0.1.0\x64\Debug
copy x64\Debug\pkzo*.pdb pkzo-0.1.0\x64\Debug

mkdir pkzo-0.1.0\x64\Release
copy x64\Release\*.dll pkzo-0.1.0\x64\Release
copy x64\Release\pkzo*.lib pkzo-0.1.0\x64\Release
copy x64\Release\pkzo*.pdb pkzo-0.1.0\x64\Release
