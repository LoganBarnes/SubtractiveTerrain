@ECHO OFF

rem goes into each shader directory and comiles the shaders into
rem SPIR-V byte code

cd default

@ECHO ON

C:\VulkanSDK\1.0.26.0\Bin\glslangValidator.exe -V shader.vert
C:\VulkanSDK\1.0.26.0\Bin\glslangValidator.exe -V shader.frag

@ECHO OFF

cd ..
