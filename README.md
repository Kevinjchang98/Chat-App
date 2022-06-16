# Chat-App

## Building the app

### Prerequisites
You will need GLFW (http://www.glfw.org):

Linux: `apt-get install libglfw-dev`

Mac OS X: `brew install glfw`
  
MSYS2: `pacman -S --noconfirm --needed mingw-w64-x86_64-toolchain mingw-w64-x86_64-glfw`

### Compiling and building
Navigate to the project directory and run `make`. This should create a `build` folder, and an executable named `chat_app` inside.

If you want to delete old or current build files and the executable, run `make clean` and this will remove them from the project directory and remove the `build` folder.

## Running
After building the app, run `./build/chat_app`
