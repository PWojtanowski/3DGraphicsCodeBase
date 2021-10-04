# A 3D graphics programming project.

After cloning the repository 

```shell
git clone git@github.com:Dydaktyka/Graphics3D.git
cd Graphics3D
git submodule init
git submodule update
```

To make this work you need to have the  ssh key added in you github account.
This is the prefered option. If not you can use 
```shell
git clone https://github.com/Dydaktyka/Graphics3D.git
```
and log to you github account when prompted. 

Use CMake to compile:

```shell
mkdir build
cd build
cmake ..
make -j 
./src/Examples/CameraMovement
```

## CLion 

This projects integrates with CLion IDE "out of the box". Just chose Open project and then choose the project 
directory.

## VS Code

Same with VS Code
## QTCreator 

Choose Open project and then choose &lt;project dir&gt;/CMakeLists.txt file. 
