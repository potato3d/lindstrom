# lindstrom
Terrain simplification algorithm using Geometry Shaders

Based on the paper ["Terrain simplification simplified: a general framework for view-dependent out-of-core visualization"](https://ieeexplore.ieee.org/document/1021577)

This was a test application to see if the proposed mesh simplification algorithm could be efficiently implemented inside the GPU using Geometry Shaders (at the time there were no Tessellation Shaders).
The conclusion was that it was not efficient. Emitting many vertices in Geometry Shader was too slow and there was a severe limitation on the total number of scalar values that could be emitted.

# Description
Requires OpenSceneGraph
Visual Studio project files in visualstudio directory
Algorithm implemented in src/main.cpp, src/TerrainImpl.cpp and bin/shaders directory
