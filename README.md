Subtractive Terrain
===================

A new implementation of an old hackathon project optimizing procedural terrain in a ray traced environment.


Download
--------
Make sure to clone all submodules as well:

```bash
git clone --recursive https://github.com/LoganBarnes/SubtractiveTerrain.git
```

If the project was already cloned without submodules use this command from the root folder:
```bash
git submodule update --init --recursive
```


Unix
----

Ensure the Vulkan SDK location is added to the environment path before running commands.

```bash
cd run
./unixConfigureAndBuild.sh
./bin/runSubtractiveTerrain
```


Windows
-------

Ensure the Vulkan SDK location is added to the environment path and Visual Studio has been installed before running commands.

```bash
cd run
winConfigureAndBuild.cmd
bin\runSubtractiveTerrain
```
