# OpenGL-4D-Graph-Designer
  This C++OpenGL application uses 3D slicing and 3D projection wireframe methods to visualize various scenes in four-dimensional physical space, such as walls, terrain, water bodies, lights, dynamic physical rigid bodies, particles, dynamic sky boxes, and simple decorations. These scenes include the calculation of various texture maps, four-dimensional normals, and the use of a built-in CPU four-dimensional physics engine, allowing players to rotate, walk, and run freely, Jumping and flying to explore scenes can interact with objects such as dynamic physical rigid bodies, as well as basic editing functions such as building, controlling, modifying, and deleting 4d objects.

## Playing Methods
* Rotate and move players to observe the scene
* Control and drag dynamic rigid bodies
* Terrain coloring
* Building and deleting objects
* Shooting and detonating objects and triggering rigid body behavior
## Features
* Use vertex shader to slice 4d objects
* Some 4d space rooms to explore
* 4d terrain with mulitple textures rendering.
* Coordinate system projection lines and 4d objects wireframes
* 3d texture mapping and smooth four-dimensional normals caculating at 4d objects and particles
* 4d point lights and direction light display on 3d section
* Physical simulation of 4d rigid bodies and simple joints
* Some animations of translation and rotation of 4d objects
* 4d particle system
* Sky box and sun light color calculation in 4d space
* Water surface reflection in 4d space
* Highlights and specular reflections of 4d objects
## Controls
Press W/S/A/D/R/F: players move forward, backward, left, right, ana, and kata

Space: jump

Double press Space: fly or land

Double press W: run

Move the mouse: move the player's perspective within a three-dimensional plane

Left click on the mouse: move the player's perspective and move the 3D section

In control mode

Press Right click :drag an object

Left and right mouse buttons :throw objects

In other modes

Right click on the mouse :execute the corresponding behavior

I: turn on or off the UI

C: Turn on or off the world coordinate system lines

G: Show or turn off wireframe

Ctrl: Lift up the construction site

F2:Captures the window (RGB) and save the image

Delete: delete the half build joint or delete objects in the selection area

M/N: Zoom in and out of perspective

1/2/3/4/5/6 or Mouse wheel: Switching behavior mode

## Issues:
1. This application currently only supports the Windows operating system and does not currently support Linux or Mac operating systems.
2. There may be non-standard writing in this C++application, which may result in failure to open or memory overflow. Please understand if any issues are found.
3. If you want to play it,please make sure the exe file,openal32.dll,sfml-audio-2.dll,sfml-system-2.dll and resourcefile is in the same folder.
