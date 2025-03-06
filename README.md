# Practice code for INF443 - 3D Graphics

## Download

_Note: Do not use the "Code -> Download ZIP" option from the GitHub GUI as you won't get the CGP library as submodule with the code._

* [inf443_lab_code.zip](https://imagecomputing.net/course/2023_2024/inf443/lab_code/inf443_lab_code.zip)
* [inf443_lab_code.tar.gz](https://imagecomputing.net/course/2023_2024/inf443/lab_code/inf443_lab_code.tar.gz)

## Clone

```
git clone --recurse-submodules https://github.com/drohmer/inf443_practice_code.git
```

or

```
git clone https://github.com/drohmer/inf443_practice_code.git
cd inf443_practice_code/
git submodule init
git submodule update
```




## Compilation

Scenes are in a directory _scenes_inf443/xx_Name/_

Each scene is provided with its own CMakeLists.txt and Makefile

Compilation via CMake
```
cd scenes_inf443/01_introduction/
cmake -B build/
cd build/
make -j8 # or any -jN, with N=$(nproc)
./01_introduction
```

Compilation via Makefile
```
cd scenes_inf443/01_introduction/
make -j8 # or any -jN, with N=$(nproc)
./01_introduction
```

More details are provided in the dedicated [Installation setup and Compilation page](https://imagecomputing.net/cgp/compilation) if needed (Windows, Linux, Mac).

## Requirement

The code requires the GLFW library in Linux.

### Linux (/Ubuntu)

```
sudo apt-get install libglfw3-dev
```

### MacOS:

* You may use [brew](https://brew.sh/) to install [glfw](https://formulae.brew.sh/formula/glfw). And then add the following two lines on your .zshrc to add glfw library to the path
```
export CPATH=/opt/homebrew/include
export LIBRARY_PATH=/opt/homebrew/lib
```

* Alternatively, a pre-compiled glfw can be used without installation. To activate it, open the CMakeLists.txt file and set the option MACOS_GLFW_PRECOMPILED to ON. You may need to explicitely allow the mac to use the library if security triggers an alert.

### Windows:

The simplest way is the use of [Visual Studio](https://visualstudio.microsoft.com/downloads/) with the __scripts/windows_cmake_visual.bat__ generating a visual studio project.


## IDE

The full edition/compilation/debug toolchain should work with the following IDE:

* [Visual Studio Code/vscode](https://code.visualstudio.com/) on **Linux and MacOS**: You may open a project with the dedicated configuration file `vscode.code-workspace`.
* [Visual Studio](https://visualstudio.microsoft.com/downloads/) on **Windows only**. Free for individuals.
* [CLion](https://www.jetbrains.com/clion) on any plateform (you need to install a compiler on Windows). Note that as student you are elligible for a free licence to this IDE. A project can be loaded directly from the CMakeLists.txt.
* [QtCreator](https://www.qt.io/product/development-tools) on Linux and MacOS. Install it via your package manager (apt/brew). A project can be loaded directly from the CMakeLists.txt (you may have to indicate to build in RelWithDebInfo instead of the default Debug).


## Scripts

You may use the provided scripts (in directory scripts/) and configuration files to ease some of the compilation process
* _vscode.code-workspace_: workspace configuration file for Visual Code Studio (vscode). 
* _scripts/linux_compile_run_cmake.py_: Run CMake, compile and run the code on Linux and MacOS. linux_clean.py remove temporary files.
* _scripts/windows_cmake_visual.bat_: On Windows, call CMake and generate a Visual Studio project. CMake must be accessible on the command line path. scripts/windows_clean.bat remove the temporary files and the visual studio project.
* _scripts/linux_compile_emscripten.py_: Generate a webpage runing the code of the scene. The script can run on Linux and MacOS if [emscripten](https://emscripten.org/docs/getting_started/downloads.html) is installed.

## Links

* [Lab class exercises](https://imagecomputing.net/course/2023_2024/inf443/lab)
* [Documentation on CGP library](https://imagecomputing.net/cgp/index.html)

