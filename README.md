# Atestat 2026
A Digital Logic Simulation and Circuit Builder written in C as part of my High School Professional Licence in Computer Science

> **This project is greatly inspired by (if not entirely based on) Sebastian Lague's [Digital Logic Sim](https://github.com/SebLague/Digital-Logic-Sim.git)**

# Building from source
This project was made in C using Makefile. We recommend installing the [Git](https://git-scm.com/install/windows) environment for Windows along with [MingW64](https://www.mingw-w64.org/) and placing them in your PATH.

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
The dependencies are
1. GLFW 3 (https://www.glfw.org/)
2. OpenGL 3.3 loaded using GLAD (https://glad.dav1d.de/)
3. STB_image (https://github.com/nothings/stb)
   
These are present in the `Dev/Dep` directory and are statically linked with the executable so there should be no reason to install them separately.

# Assets
Some UI Icons are taken from SHMORGUS' [Universal Icon Pack 8x8](https://shmorgus.itch.io/micro-icon-pack)