@ECHO OFF

rem goes into each shader directory and comiles the shaders into
rem SPIR-V byte code

cd default

@ECHO ON

glslangValidator.exe -V shader.vert
glslangValidator.exe -V shader.frag

@ECHO OFF

cd ..
