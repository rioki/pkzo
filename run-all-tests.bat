
msbuild /m /p:Configuration=Debug /property:Platform=x86 pkzo.sln
msbuild /m /p:Configuration=Release /property:Platform=x86 pkzo.sln
msbuild /m /p:Configuration=Debug /property:Platform=x64 pkzo.sln
msbuild /m /p:Configuration=Release /property:Platform=x64 pkzo.sln

bin\x86\Debug\pkzo-test.exe
bin\x86\Release\pkzo-test.exe
bin\x64\Debug\pkzo-test.exe
bin\x64\Release\pkzo-test.exe

pause