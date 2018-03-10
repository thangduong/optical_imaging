D3D TileDemo Examples
---------------------

All of these were written in Visual C++ 5 Professional. It also compiles
with Visual C++ 6, but I only have the introductory edition and didn't
want to ship executables with splash screens!

The demos have been tested on the following machines:

Intel Celeron-A 450 Mhz, TNT2 Ultra (32 Mb), 128 Mb RAM, Windows 2000 RC3.
AMD K6 450 Mhz, Voodoo Banshee, 64 Mb RAM, Windows 98.
Intel Pentium II 233 Mhz, Voodoo Graphics (4 Mb), Windows 98-SE.

The demos require DirectX 6.

Demo 1: Demonstrates isometric tiling in general, using Direct3D wireframe
        rendering.
Demo 2: Adds a texture to demo 1.
Demo 3: Randomly lights the textured landscape (VERY trippy)
Demo 4: Adds a heightmap, and simple lighting based on height.

When you compile them, please don't forget to include the DirectX SDK's
include directory as the FIRST entry in your compiler's include directory
list, and also each project will need the following library files linked:

D3DIM.LIB, DDRAW.LIB, DXGUID.LIB

If you have any questions, comments, or if you find a machine this doesn't
work on.... feel free to email me at bracket@unforgettable.com

Thanks,
Herbert Wolverson.