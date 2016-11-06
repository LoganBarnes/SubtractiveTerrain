@ECHO OFF

rem run this from the Developer Command Prompt for VS since
rem the MSBuild.exe path will already be set

SET RUN_DIR="%CD%"

IF EXIST _build GOTO NOWINDIR
mkdir _build
:NOWINDIR

cd _build
cmake -DCMAKE_INSTALL_PREFIX=%RUN_DIR% ..\..
cmake --build . --target INSTALL --config Debug
cd ..
