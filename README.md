# VaKon2D

## ⭐ Intro

I have been creating a game engine using raw OpenGL and my wrappings of its. You can use it to write your own game. It's
easier than writing on raw OpenGL, and it gives more abilities than SFML.
For example, you can create a game like a Terraria, or some RPG game.
<b>Accomplishment of this engine, that all possible calculations will process your GPU.</b>
<br>
Also, you can use this engine as an OpenGL wrapper for the usual code of OpenGL. It has an MIT license, so use it
everywhere!

## Table of Contents

>
> 1. [Getting started](#-getting-started)
>    1. [At first, let's install it](#at-first-lets-install-it)
>    2. [How to write your own game?](#how-to-write-your-own-game)
>    3. [Where to find binaries and how to build a <u>game</u>?](#where-to-find-binaries-and-how-to-build-a-u-game-u-)
>    4. [At first, let's install it](#at-first-lets-install-it)
> 2. [Game-template](#-game-template)
> 3. [If you want to rewrite game-template](#-if-you-want-to-rewrite-game-template)
> 4. [How to generate a docs(doxygen)](#-how-to-generate-a-docs--doxygen-)
> 5. [Docs](#-docs)
> 6. [Code-tutorial & classes & examples](#-code-tutorial--classes--examples-)
>    1. [Init your game environment](#init-your-game-environment)
>    2. [Write your shader](#write-your-shader)
>    3. [Create your own shader-program](#create-your-own-shader-program)
>    4. [Load textures](#load-textures)
>    5. [Creating the first rectangle](#creating-the-first-rectangle)
>    6. [Main Loop](#main-loop)
>    7. [Timers](#timers)
>    8. [Using OpenGL wrappers](#using-opengl-wrappers)
> 7. [What in the future?](#-what-in-the-future)
> 8. [Feedback & Contacts](#-feedback--contacts)

## 🎉 Getting started

### At first, let's install it

1. Download and install
   ```GIT```([download](https://git-scm.com/downloads), [how to install it](https://github.com/git-guides/install-git))
2. Download and install some compiler or ```IDE```. I.e.
   ```MSVC```([download](https://visualstudio.microsoft.com/downloads/), [how to install VS](https://learn.microsoft.com/en-us/cpp/build/vscpp-step-0-installation?view=msvc-170))
3. Download and install the last version of ```Cmake```([download](https://cmake.org/download/))
4. Clone
   the
   repository([how to do it](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository))
5. Open a ```CMD```(```console```/```terminal```) inside the <u>cloned
   directory</u>([how to open CMD](https://www.youtube.com/watch?v=8gUvxU7EoNE))
6. In the CMD run: ```mkdir build```
7. In the CMD run: ```cd build```
8. In the CMD run: ```cmake ../ -DCMAKE_BUILD_TYPE=Debug```. If you want to build a Release version, type ```Release```
   instead of ```Debug```. Also, if you have a custom compiler, you need to write a path to this compiler.
9. In the CMD run: ```cmake --build .```

### How to write your own game?

1. After a successful build (previous point), you can write your own game
2. Go to folder /game/
3. There you'll find three folder: ```assets```, ```include```, ```source```
    1. What to store in the folder ```asset```: you can create your own directories to store your game data(i.e.
       textures, audio files, shaders, etc.)
    2. What to store in the folder ```include```: you can store your include files(.h/.hpp) for your own game
    3. What to store in the folder ```source```: you can store your include files(.c/.cpp/.cxx) for your own game
4. Put your sources into ```source``` directory and your headers to ```include``` directory

### Where to find binaries and how to build a <u>game</u>?

After previous points, you can say: <i>How to get an ```.exe``` file of my game?</i> - it's easy!
Let's do it:

1. [Make this point](#-at-first-lets-install-it)
2. Go to ```/build/game/```
3. Looking at your compiler, you can find in this folder(or sub-folders)```VaKon2D.exe``` file - it's your game
4. You'll need a folder ```assets``` and a file ```VaKon2D.exe``` for successful launching of a game. Just pack your
   game
   with these two items - that's all!

## 📑 Game-template

Basic game template, just an example of a game, you can find in the folder ```/game/```

## 📑 If you want to rewrite game-template

1. You can edit ```/game/source/main.cpp``` and remove all needed files from the directory ```/game```
2. One rule: don't forget the next rows at the start of your game:

```C++
// !!!!!! don't change an order !!!!!! -->
Logger::initLogger();
GlfwWrapper::initGlfw(3, 3);
GetWindow().create({800, 600}, "Game name");
GladWrapper::initGlad();
GetWorld().init();
// <---------------------------------------
```

## 📄 How to generate a docs(doxygen)

1. Download and install doxygen([download](https://www.doxygen.nl/download.html))
2. Add doxygen.exe to the Environment
   Variable([how to do it](https://docs.oracle.com/en/database/oracle/machine-learning/oml4r/1.5.1/oread/creating-and-modifying-environment-variables-on-windows.html#GUID-DD6F9982-60D5-48F6-8270-A27EC53807D0))
3. Open a ```CMD```(```console```/```terminal```) inside the <u>cloned
   directory</u>([how to open CMD](https://www.youtube.com/watch?v=8gUvxU7EoNE))
4. Run the next command: ```doxygen```
5. Go to ```docs/html/index.html``` - it's your doc!

## 📃 Docs

You can find docs by engine classes in the next directory: ```/docs/html/index.html```

## 📌 Code-tutorial & classes & examples:

### Init your game environment

Add the next lines to your code to init game-env:

```C++
Logger::initLogger();
GlfwWrapper::initGlfw(3, 3);
GetWindow().create({800, 600}, "Game name");
GladWrapper::initGlad();
GetWorld().init();
```

First, you should initialize the game logger. It will write some logs to /game/logs folder. The logger be used in all
places of the next code, so you should initialize it first.
After that, initialize GlfwWrapper to get the ability to work with a window, window-event. If you want, you can change
the major and minor versions. You can't create a window or initialize a GLAD without initializing GLFW.
Let's initialize your window:

```c++
GetWindow().create({800, 600}, "Game name"); 
```

You can pass your values to the window's size or window's title.
After that going forward GLAD initialization and World initialization.

### Write your shader

How to include it: ```#include "Shader.h"``` and don't forget to add ```Core-Wrappers``` to your CMake-game
At the first you can write simple shader, like the next:

```glsl
// ======FRAGMENT SHADER=======
#version 330 core
out vec4 FragColor;
in vec2 ioCv;
uniform sampler2D uTexture;
void main()
{
    FragColor = texture(uTexture, ioCv);
}
```

And such like next too:

```glsl
// ======VERTEX SHADER=======
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aCv;
out vec2 ioCv;
uniform mat4 uTransform;
void main()
{
    ioCv = aCv;
    gl_Position = uTransform * vec4(aPos.x, aPos.y, 0.0, 1.0);
}
```

Afet that load them to the shader class ```Shader```.

```c++
Shader vertex("assets/shaders/main-vertex.glsl", Gl::Shader::Type::Vertex);
Shader fragment("assets/shaders/main-fragment.glsl", Gl::Shader::Type::Fragment);
```

### Create your own shader-program

Shader program will save and transfer the shader[s] to the GPU
How to include it: ```#include "CustomShaderProgram.h"``` and don't forget to add ```Core-Wrappers``` to your CMake-game
dependencies(```target_link_libraries(YouGameTarget PRIVATE Core-wrappers)```
Create the first shader-program and attach shaders to it.

```c++
CustomShaderProgram program(true);
program.attachShader(vertex);
program.attachShader(fragment);
```

To create and bind shader program we can pass ```true``` like an argument to the ```CustomShaderProgram``` constructor.
After that we are attaching shaders to the shader-program.

And now you can use your shader program. Just write

```c++
program.use();
```

### Load textures

To load texture we should use a class Texture(```#include "Texture.h"``` and don't forget to add ```Core-Wrappers``` to
your CMake-game dependencies(```target_link_libraries(YouGameTarget PRIVATE Core-wrappers)```))
and use class ```Image``` too(```#include "Image.h"```)

```c++
Texture texture(Gl::Texture::Target::Texture2D, true, true);
Image image("assets/textures/apple.png");
texture.setImage(image);
texture.setMagAndMinFilter(Gl::Texture::MagFilter::Linear, Gl::Texture::MinFilter::LinearMipmapLinear);
```

We want to render texture 2D, so in the Texture's constructor we should pass ```Gl::Texture::Target::Texture2D```. Also,
if you want to generate and bind a texture 'in-place', we can pass ```true``` and ```true``` like the 2nd and 3rd
argument of this class.
After that we are loading an image: ```Image image("assets/textures/apple.png")```
The class Image provides more convenient interface for loading an images and getting some data about it for you or fot
the textures.
Don't forget to set image to your texture: ```texture.setImage(image);```
If you want to set mag & min filter, you can use the next functions to do
it: ```Texture::steMinFilter``` & ```Texture::setMagFilter```

### Creating the first rectangle

```c++
class Rectangle rect;
rect.setTexture(texture);
rect.prepare();
```

We should create our class Rectangle and set a texture to it. After that don't forget to call
function ```Rectangle::prepare``` - to prepare all OpenGL data. This function you should call only one time.

### Main Loop

```c++
while (!GetWindow().shouldClose())
{
    GetWindow().clearColor(0.2f, 0.3f, 0.3f, 1.0f);
    GetWindow().clear(GL_COLOR_BUFFER_BIT);

    rect.draw(program);

    GetWindow().swapBuffers();
    GetWindow().pollEvent();

    GetWorld().update();
}
```

At the start of main loop, we should work while the window is open. After that need to clear background color and clear
ColorBufferBit.

```c++
GetWindow().clearColor(0.2f, 0.3f, 0.3f, 1.0f);
GetWindow().clear(GL_COLOR_BUFFER_BIT);
```

Don't forget to draw your rectangle:

```c++
rect.draw(program);
```

And don't forget to process buffers and events. It needs for correct working of all window events.

```c++
GetWindow().swapBuffers();
GetWindow().pollEvent();
```

Also, we have a world data. For example, timers - it's a part of a world. You should update all this data.
So, write:

```c++
GetWorld().update();
```

### Timers

If you want work with timers you should add a target ```World``` to you ```target_link_libraries``` of a game. Example:

```cmake
target_link_libraries(VaKon2D PUBLIC World)
```

After that include ```Timers.h``` to your code.

Now you can use timers in your code. At first, let's create new timer:

```c++
Timer timer;
```

And let's set mode Infinity and set frequency one time per second. Also, don't forget to set a callback. This lambda
will be called one time per 1000ms(1s).

```c++
timer.setFrequency(Timer::Unit(1000));
timer.setMode(Timer::Mode::Infinity);
timer.setCallback([&](){ rect.move({-0.1f, 0.f}); });
```

Therefore, move this timer to world timer manager:

```c++
GetWorld().addTimer(std::move(timer));
```

After that your timer will be invalid. But you can get timer ID from a function ```World::addTimer```. You can use this
id to delete(like an example) your timer in the future.

### Using OpenGL wrappers

You can connect to your game Core-Wrappers and use OpenGL wrappers. You should add a target ```Core-Wrappers``` to
you ```target_link_libraries``` of a game. Example:
OpenGL wrappers take off a chance to get a mistake while you working with OpenGL. Just use it!
For example, you can create your own VBO/VAO:

```c++
#include "Gl.h"
...
auto vbo = Gl::Vbo::generate();
auto vao = Gl::Vao::generate();
```

Others function will be available in the
class ```Gl```, ```Gl::Program```, ```Gl::Shader```, ```Gl::Vao```, ```Gl::Vbo```, ```Gl::Texture```

## 💭 What in the future?

I want to implement more and more things to give abilities like:

- Working with network, like in UnrealEngine 4\5:
    - real-time replications
    - different types of replications
    - write my own UDP protocol for data transferring
- Improve working with lightning:
    - Give an ability to create different types of lighting: global, point
    - Working with gamma and post-processing
- Pick up all the best things from an SFML(and plugins to it) in one Engine(VaKon2D)
- Easy working with se\deserializing of game data
- Adding an ability to integrate own DLC to a game
- Supporting of all new compilers: GCC, G++, Clang, MSVC
- The engine will be cross-platform
- Easy working with textures and shaders
- Custom shader integration
- Shader builder for PRO users
- Add working with audio
- Working with a camera

## 📞 Feedback & Contacts

You can send me e-mail: Valerii.Koniushenko@gmail.com or try to find me in telegram: @markmoran24
