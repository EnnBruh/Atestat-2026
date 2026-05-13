# Atestat 2026
A Digital Logic Simulation and Circuit Builder written as part of my High School Professional Licence in Computer Science

> **This project is greatly inspired by (if not entirely based on) Sebastian Lague's [Digital Logic Sim](https://github.com/SebLague/Digital-Logic-Sim.git)**

![Example of a 4BIT-ADDER](Examples/4BIT-ADDER%20Example.png)

# Building from source
This project is written in C using the GNU C Compiler and a Makefile based build system. We recommend installing the [Git](https://git-scm.com/install/windows) environment for Windows along with [MingW64](https://www.mingw-w64.org/) and [Make](https://gnuwin32.sourceforge.net/packages/make.htm) and placing them in your PATH.

After installing you should be able to run
```
git clone https://github.com/EnnBruh/Atestat-2026.git
cd Atestat-2026
cd Dev
make
```
This will compile to the `Debug` version of the project
```
make build_release
```
Will compile in Release mode.

# Dependencies
This project uses the following libraries for handling graphical contexts and input.
1. GLFW 3 (https://www.glfw.org/)
2. OpenGL 3.3 loaded using GLAD (https://glad.dav1d.de/)
3. STB_image (https://github.com/nothings/stb)
   
These are present in the `Dev/Dep` directory and are statically linked with the executable so there should be no reason to install them separately.

# Assets
Some UI Icons are taken from SHMORGUS' [Universal Icon Pack 8x8](https://shmorgus.itch.io/micro-icon-pack)