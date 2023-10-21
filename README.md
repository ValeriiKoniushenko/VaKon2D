![GitHub Workflow Status (with event)](https://img.shields.io/github/actions/workflow/status/ValeriiKoniushenko/VaKon2D/c-cpp.yml)
![GitHub](https://img.shields.io/github/license/ValeriiKoniushenko/VaKon2D)
![Static Badge](https://img.shields.io/badge/c%2B%2B-20-brightgreen)
![Static Badge](https://img.shields.io/badge/boost-1.8-red)
![Static Badge](https://img.shields.io/badge/OpenGL-3.x-red)

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
>    1. [Let's install it](#step-1--lets-install-it)
>    2. [Writing a game](#step-2--writing-a-game)
>    3. [Getting binaries](#step-3--getting-binaries)
> 2. [Game-template](#-game-template)
> 3. [If you want to rewrite game-template](#-if-you-want-to-rewrite-game-template)
> 4. [How to generate a docs(doxygen)](#-how-to-generate-a-docs--doxygen-)
> 5. [Docs](#-docs)
> 6. [Code-tutorial & classes & examples](#-code-tutorial--classes--examples-)
>    1. [Init your game environment](#init-your-game-environment)
>       1. [Initer](#initer)
>    2. [Write your shader](#write-your-shader)
>    3. [Shader-program](#shader-program)
>    4. [Textures](#textures)
>       1. [Transparent background](#transparent-background)
>       2. [Calculate correct texture size](#calculate-correct-texture-size)
>       3. [Texture rect](#texture-rect)
>    5. [First widget](#first-widget)
>    6. [Main Loop](#main-loop)
>    7. [Updateable Collector](#updateable-collector)
>    8. [Timers](#timers)
>    9. [Keyboard](#keyboard)
>    10. [Mouse](#mouse)
>    11. [Delegate](#delegates)
>    12. [World Variables](#world-variables)
>    13. [Widget Reflector](#widget-reflector)
>    14. [Input Actions](#input-actions)
>    15. [Text](#text)
>    16. [Using OpenGL wrappers](#using-opengl-wrappers)
>    17. [Coordinate System](#coordinate-system)
>    18. [Clock or game tick](#clock-or-game-tick)
>    19. [Camera](#camera)
>    20. [Shader pack](#shader-pack)
>    21. [OpenGL Debug](#opengl-debug)
>    22. [Game Mode](#game-mode)
> 7. [What in the future?](#-what-in-the-future)
> 8. [Feedback & Contacts](#-feedback--contacts)

## 🎉 Getting started
To start develop your own game you have to do the next steps:

### Step #1: let's install it

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

### Step #2: writing a game
After a successful build (previous point), you can write your own game
1. At start create your own directory "Name-of-your-game"
2. Put inside this directory all folder with an Engine
3. After that, nearby to the Engine's folder create a folder with your game
4. Connect it using CMake: just add ```VaKon2D``` like a subdirectory

### Step #3: getting binaries

After previous points, you can say: "<i>How to get an ```.exe``` file of my game?</i>" - it's easy!
Let's do it:

1. [Make step #1](#step-1--lets-install-it)
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

PS: don't forget to connect dependencies to your ```CMakeLists.txt```

```cmake
# /game/CMakeLists.txt
target_link_libraries(
	VaKon2D PUBLIC
    ...
        Core-Wrappers
        Glad
        Logger
        Misc
        World
        glfw
    ...
)
```

#### Initer
To make a game environment easier you can use ```Initer```. Just write the next code to initialize your game's env:
```c++
Initer::init({.glfwVersion = {3, 3}, .windowSize = {800, 600}, .title = "My game"});
```

It's going to replace the previous code:
```C++
Logger::initLogger();
GlfwWrapper::initGlfw(3, 3);
GetWindow().create({800, 600}, "Game name");
GladWrapper::initGlad();
GetWorld().init();
```

---

### Write your own shader

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

PS: don't forget to connect ```Core-Wrappers``` to your ```CMakeLists.txt```
```cmake
# /game/CMakeLists.txt
target_link_libraries(
	VaKon2D PUBLIC
    ...
	Core-Wrappers
    ...
)
```

---

### Shader-program

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

Also, if you want to use this shader program to draw your own ```Widget``` you must create ```ShaderPack```. Look how to do
it below([how to create your own shader pack](#shader-pack) - it's easy).

PS: don't forget to connect ```Core-Wrappers``` to your ```CMakeLists.txt```
```cmake
# /game/CMakeLists.txt
target_link_libraries(
	VaKon2D PUBLIC
    ...
	Core-Wrappers
    ...
)
```

---

### Textures

To load texture we should use a class Texture(```#include "Texture.h"``` and don't forget to add ```Core-Wrappers``` to
your CMake-game dependencies(```target_link_libraries(YouGameTarget PRIVATE Core-wrappers)```))
and use class ```Image``` too(```#include "Image.h"```)

```c++
Image image("assets/textures/apple.png");

Texture texture(Gl::Texture::Target::Texture2D, true, true);
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

PS: don't forget to connect ```Core-Wrappers``` to your ```CMakeLists.txt```
```cmake
# /game/CMakeLists.txt
target_link_libraries(
	VaKon2D PUBLIC
    ...
	Core-Wrappers
    ...
)
```

#### Transparent background
If you want to add a widget with a transparent background you must use ```SRGBA``` or ```RGBA```.
```c++
Image image("assets/textures/apple.png");
image.setInternalChannel(Gl::Texture::Channel::SRGBA);

Texture texture(Gl::Texture::Target::Texture2D, true, true);
texture.setImage(image);
texture.setMagAndMinFilter(Gl::Texture::MagFilter::Linear, Gl::Texture::MinFilter::LinearMipmapLinear);
```

#### Calculate correct texture size
In the case you don't know(or just lazy to remember\set) the correct texture size you can use the function ```Widget::calculateFitTextureSize()```.
It's getting correct texture size from an ```Image``` in the texture, and set the texture size corresponding to an image's size.
But do it only after setting up an image!

Example:
```C++
Texture texture(Gl::Texture::Target::Texture2D, true, true);
texture.setImage(image);

Widget widget;
widget.setTexture(texture);
widget.calculateFitTextureSize();
```

#### Texture rect
If you are using texture atlases, and you want to set one unit of it you have to use the function ```Widget::setTextureRect(const Utils::Rect<int> &rect)```
So, just write: 
```c++
widget.setTextureRect(Utils::IRect{{32, 0}, {32,  32}});
```
And you will get the texture by the next coordinates: ```X: 32; Y: 0```; with a size: ```Width: 32; Height: 32```; 

---

### First widget

```c++
Widget rect;
rect.setTexture(texture);
rect.prepare();
```

We should create our class Rectangle and set a texture to it. After that don't forget to call
function ```Rectangle::prepare``` - to prepare all OpenGL data. This function you should call only one time. But you must
know that this function very expensive, **call it only if you really need it**.

PS: don't forget to connect ```Shapes``` to your ```CMakeLists.txt```
```cmake
# /game/CMakeLists.txt
target_link_libraries(
	VaKon2D PUBLIC
    ...
	Shapes
    ...
)
```

---

### Main Loop

```c++
Image image("assets/textures/apple.png");
image.setInternalChannel(Gl::Texture::Channel::SRGBA);

Texture texture(Gl::Texture::Target::Texture2D, true, true);
texture.setImage(image);
texture.setMagAndMinFilter(Gl::Texture::MagFilter::Linear, Gl::Texture::MinFilter::LinearMipmapLinear);

Widget rect;
rect.setTexture(texture);
rect.prepare(shaderPack);

while (!GetWindow().shouldClose())
{
    GetWindow().clearColor(0.2f, 0.3f, 0.3f, 1.0f);
    GetWindow().clear(GL_COLOR_BUFFER_BIT);

    rect.draw(shaderPack);
    rect.update();
    
    GetWindow().swapBuffers();
    GetWindow().pollEvent();

    GetWorld().update();
}
```

At the start of main loop, we should work while the window is open. After that need to clear background color and clear
```ColorBufferBit```.

Also, don't forget to update a widget's data. For that we use the function ```Widget::update```.

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

PS: don't forget to connect ```Window``` & ```Core-Wrappers``` to the game's ```CMakeLists.txt```
```cmake
# /game/CMakeLists.txt
target_link_libraries(
	VaKon2D PUBLIC
    ...
	Window
	Core-Wrappers
    ...
)
```

---

### Stop-Motion Animations
I have implemented a stop-motion animations for the Engine. So, you can easily use it.

At first be sure that you connect needed CMake target to your game:
```cmake
# /game/CMakeLists.txt
target_link_libraries(
	VaKon2D PUBLIC
    ...
	Animations
    ...
)
```

And let's look at the simple example:
```c++
StopMotionAnimation animation;
animation.setupAnimation({{0, 0}, {32, 32}}, {{544, 0}, {32, 32}}, widget);
animation.setFrameGap(100);
animation.setMode(IAnimation::Mode::Repeating);
animation.start();

while (!GetWindow().shouldClose())
{
    GetWindow().clearColor({0.2f, 0.3f, 0.3f});
    GetWindow().clear(GL_COLOR_BUFFER_BIT);

    animation.draw(shaderPack);

    GetUpdateableCollector().updateAll();
    GetWorld().update();
    GetWindow().swapBuffers();
    GetWindow().pollEvent();
}
```
So, it was easy! Just create an instance of you ```StopMotionAnimation```. After that setup animation frame-set:
```c++
animation.setupAnimation(
        {   // First frame
            {0, 0}, // position of the first frame
            {32, 32} // texture size of the first frame
        }, 
        {   // Last frame
            {544, 0}, // position of the last frame
            {32, 32}  // texture size of the last frame
        }, 
        widget);
```

After that you can set animation-mode: ```Repeating```, ```Ping-Pong```, ```Single-Shot```.
- ```Repeating```: will be infinity repeat your animation from the start, to the end. After that, it's going to the start again.
- ```Ping-Pong```: just simple ping-pong: going from start to end and again to the start.
- ```Sing-Shot```: just one shot of the animation.

Also, don't forget about ```frameGap```. It's how much time passed after every frame. Frame, not animation!
Just set a value in ```ms``` using the next function ```StopMotionAnimation::setFrameGap(ms)```.

And let's start it! Just call a function ```StopMotionAnimation::start()```.

After that, don't forget to draw your animation:

```c++
while (!GetWindow().shouldClose())
{
    ...
    animation.draw(shaderPack);
    ...
}
```


PS: don't forget to connect it in your game-cmake using target ```Animations```
```cmake
target_link_libraries(YourGame PUBLIC Animations)
```

---

### Updateable Collector
If you have a lot of widgets, and you don't want to update every of it you can use ```UpdateableCollector```. So, if you 
create a widget it's automatically registering in the ```UpdateableCollector```. And everything you need it's to get ```UpdateableCollector``` 
and to call ```UpdateableCollector::updateAll()```.

Example:
```c++
while (!GetWindow().shouldClose()) {
    // ...
    GetUpdateableCollector().updateAll();
    // ...
}
```

---

### Timers
The timers help you to call some part of a code ad many times as you need.

If you want work with timers you should add a target ```World``` to you ```target_link_libraries``` of a game. Example:

```cmake
# /game/CMakeLists.txt
target_link_libraries(
	VaKon2D PUBLIC
	...
	World
	...
)
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

---

### Keyboard

If you want to work with a keyboard you can use class Keyboard. But if your target is to spy for key pressing, or you want to do something on key press better to use class [InputActions](#input-actions).
So, if you still want to use it you can check key state with two functions:
```c++
#include "Mouse.h"

while (!GetWindow().shouldClose())
{
    // ...
    if (Keyboard::isKeyPressed(Keyboard::Key::W))
        goForward();
    
    if (Keyboard::isKeyReleased(Keyboard::Key::Esc))
        goToSettings();
    // ...
}
```

PS: don't forget to connect ```Input-Devices``` to your game's ```target_link_libraries```
```cmake
# /game/CMakeLists.txt
target_link_libraries(
	VaKon2D PUBLIC
    ...
	Input-Devices
    ...
)
```

---

### Mouse

If you want to work with a mouse you can use class Mouse. But if your target is to spy for key pressing, or you want to do something on key press better to use class [InputActions](#input-actions).
So, if you still want to use it you can check key state with two functions:

```c++
#include "Mouse.h"

while (!GetWindow().shouldClose())
{
    // ...
    if (Mouse::isKeyReleased(Mouse::Key::Right))
        zoom();
    
    if (Keyboard::isKeyPressed(Keyboard::Key::Left))
        fire();
    // ...
}
```

PS: don't forget to connect ```Input-Devices``` to your game's ```target_link_libraries```
```cmake
# /game/CMakeLists.txt
target_link_libraries(
	VaKon2D PUBLIC
    ...
	Input-Devices
    ...
)
```

---

### Delegates

The best solution to program anything is to use delegates. Delegate it's like a channel on YouTube, and you are subscriber of this channel. It's a delegates. You can create a listener(delegate) and wait for some event. At this time in the engine we have 3 types of delegates:
1. ```LambdaDelegate\<F>```
2. ```LambdaMulticastDelegate\<F>```
3. ```Delegate<F,CallbackT>```

#### LambdaDelegate
You can use it to call a lambda function on some event. It can have only one subscriber.
To use it write the next code:
```c++
LambdaDelegate<void()> d;
d.subscribe([](){ std::cout << "Hello world"; });
...
d.trigger();
```

#### LambdaMulticastDelegate
Almost the same as before, but it supports more than one subscriber.
```c++
LambdaMulticastDelegate<void()> d;
d.subscribe([](){ std::cout << "Hello world1"; });
d.subscribe([](){ std::cout << "Hello world2"; });
...
d.trigger();
```

#### Delegate
Almost the same as before, but it supports only one subscriber and can work with object's functions.
```c++
Delegate<VaKon2D, void(VaKon2D::*)()> d;
d.subscribe(this, &VaKon2D::print);
...
d.trigger();
```

---

### World variables

World variables it's replacement of global variables. You can exchange these variables between objects and apply them everywhere.
At first, you can put some variable to the 'world':
```c++
GetWorldVariables().set("hello", "world");
```
or 
```c++
GetWorldVariables()["hello"] = "world";
```

Of course, you can get it back:
```c++
cout << GetWorldVariables()["hello"]; // "world"
```

And also you can clear some keys if you don't need it:
```c++
GetWorldVariables().forceClear("hello");
```

---

### Widget reflector

If you want to debug your widgets you can use widget reflector. At first, you have to activate it:
```c++
getWidgetReflector().activate();
```
After that you can click at the widget and get into ```std::cout``` needed info about your widget.

More standard way to use it, it's using by pressing F1 key.
```c++
KeyboardInputAction iaWidgetReflector("WidgetReflector", Keyboard::Key::F1);
iaWidgetReflector.setFrequency(KeyboardInputAction::TimeT(100));
iaWidgetReflector.onAction.subscribe([]() { getWidgetReflector().toggle(); });
```

---

### Input actions

Input actions its cool part of this engine. The simplest way to work with input it's using of class ```Keyboard``` and ```Mouse```, but it has no any controls, you can't set frequency of pressing, pressing mode and many others.
You can work with ```KeyboardInputAction``` to get more control over your keyboard input, and class ```MouseInputAction``` to get more control over your mouse.
At start, let's create new instance of ```KeyboardInputAction```:
```c++
KeyboardInputAction input("input", Keyboard::Key::W);
```

After that you can set frequency of pressing using the function ```setFrequency```. It uses units ```ms```(1/1000s) to control the time, so you have to wrap a time into ```KeyboardInputAction::TimeT```.
```c++
input.setFrequency(KeyboardInputAction::TimeT(100));
```

If you create an input for moving my a map, it should repeat a lot of times per second. So we have to set repeatable mode.
```c++
input.setIsRepeatable(true);
```

And in the end let's subscribe at this action!
```c++
input.onAction.subscribe([&player]() { player.moveForward(); });
```

---

### Text

Working with text is pretty easy, at first you have to load font, after that set this font into your Text and that's all!
```c++
Font font("assets/fonts/Roboto-Medium.ttf");
LineText text(font, "Hello world");
```

Also, don't forget to load a needed shaders for text:
```glsl
// ========FRAGMENT SHADER========
#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    color = vec4(textColor, 1.0) * sampled;
}
```

```glsl
// ========VERTEX SHADER========
#version 330 core
layout (location = 0) in vec2 aVertex;
layout (location = 1) in vec2 aUv;

out vec2 TexCoords;

uniform vec2 uResolution;

void main()
{
    gl_Position = vec4(aVertex / uResolution, 0.0, 1.0);
    TexCoords = aUv;
}
```
And let's create new shader program:
```c++
CustomShaderProgram textProgram("assets/shaders/text.vert", "assets/shaders/text.frag");
```

Now, you can print your text on the display:
```c++
text.draw(textProgram);
```

PS: don't forget to connect it in your game-cmake using target ```Core-Wrappers```
```cmake
target_link_libraries(YourGame PUBLIC Core-Wrappers)
```

---

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

---

### Coordinate System
The coordinate system is the same as in ```HTML```, ```SFML``` and others similar languages\libs.
It's going from left to right and from top to down.
So, you want to move a widget to right and to down you can write the next code:

```c++
Widget widget;
widget.setTexture(texture);
widget.move({100, 100});
```

---

### Clock or game tick
Best practice is to measure the previous game frame and use this time as a game tick. So, if you want to do it you have 
to use ```Clock```.

```c++
while (!GetWindow().shouldClose())
{
    Clock clock;
    clock.start();
    ...
    clock.stop()
    auto gap = clock.getGap();
}
```

Or more brief example:
```c++
while (!GetWindow().shouldClose())
{
    Clock clock(true);
    ...
    auto gap = clock.stop();
}
```

PS: don't forget to connect it in your game-cmake using target ```Utils```
```cmake
target_link_libraries(YourGame PUBLIC Utils)
```

---

### Camera
Game camera is a pretty simple object. So, if you want to use it just create the ```Camera```'s object at you GameState
(best practice) and use it. But, don't forget to registry your camera in the ```Window``` object, and don't forget to set 
a tick for you camera. Camera tick it's frame-gap that you can use in the camera to decrease or increase camera's movement 
speed. Let's create our own camera:
```c++
Camera camera;
camera.setSize({1000, 1000});
camera.setOrigin({1000 / 2, 1000 / 2});
GetWindow().setCamera(camera);
```
Let's discuss this code: at first, we have to create new object of our ```Camera```. After that settings size and origin.
Size of the ```Camera``` is viewport that you can see. Origin is ```Camera```'s offset to the center of your screen.
And, don't forget to connect a camera to your window. If you don't do it then you will get undefined behaviour.

In the main loop of you program you shouldn't update your camera, just call ```UpdateableCollector::updateAll()``` to 
refresh all Updateable things in you app(```Camera``` will be updated too).

Also, you can pass game-tick(frame-tick) to your ```Camera``` using method ```Camera::setTick```. Usually it's doing 
in the end of the main loop of your program.

So, finally code will be looks like that:
```c++
Camera camera;
camera.setSize({1000, 1000});
camera.setOrigin({1000 / 2, 1000 / 2});
GetWindow().setCamera(camera);

while (!GetWindow().shouldClose())
{
    Clock clock(true);
    ...
    GetUpdateableCollector().updateAll();
    camera.setTick(clock.stop());
}
```

Also, using camera you maybe want to zoom, set new position or(in the future) rotate it.
Just use the next functions to do it: 
- ```setZoom``` - to set ```new``` value to the ```Camera```'s zoom.
- ```zoom``` - to increase\decrease ```Camera```'s zoom. Just pass new value to append to the current.
- ```setPosition``` - to set ```new``` value to the ```Camera```'s position.
- ```move``` - to increase\decrease ```Camera```'s position. Just pass new value to append to the current.

After everything we understand that zooming our ```Camera``` we will change real viewport resolution. So if you want to
get real mouse(for example) position on your scene you must use the function ```Camera::toGlobalCoordinates(point)```.

PS: don't forget to connect it in your game-cmake using target ```Camera```
```cmake
target_link_libraries(YourGame PUBLIC Camera)
```

---

### Shader pack
Simple program can use only one shader(frag,vert), but more complex app can use a lot of shaders. By this reason was
 created ```ShaderPack```. It stores a lot of shader-program in one pack. To use it look at the next code:
```c++
ShaderPack shaderPack;
shaderPack.loadShaders("shader-program1", "path-to-vertex-shader", "path-to-fragment-shader");
shaderPack.loadShaders("shader-program2", "path-to-vertex-shader", "path-to-fragment-shader");
shaderPack.loadShaders("shader-program3", "path-to-vertex-shader", "path-to-fragment-shader");

CustomShaderProgram csp = shaderPack["shader-program1"];
csp.use();
```

Everything pretty simple, so if you will have some questions just look at the code or write me([my contacts](#-feedback--contacts)).


PS: don't forget to connect it in your game-cmake using target ```Core-Wrappers```
```cmake
target_link_libraries(YourGame PUBLIC Core-Wrappers)
```

---

### OpenGL Debug
To enable OpenGL debugging you must add ```OPENGL_DEUBUG``` macros to your game. How to do it look below:
```cmake
if (DEFINED CMAKE_BUILD_TYPE)
	if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
		message(STATUS "Project build type: DEBUG")
		add_compile_definitions(OPENGL_DEBUG)
	endif ()
endif ()
```

or just write simple code:
```cmake
add_compile_definitions(OPENGL_DEBUG)
```

---

### Game Mode
Like we know with ```UnrealEngine``` GameMode it's needed for:

While certain fundamentals, like the number of players required to play, or the method by which those players join the
game, are common to many types of games, limitless rule variations are possible depending on the specific game you are
developing. Regardless of what those rules are, Game Modes are designed to define and implement them.

So, if you want to create your own game mode you must inherit from base class: ```BaseGameMode```.

PS: don't forget to connect it in your game-cmake using target ```BaseGame```
```cmake
target_link_libraries(YourGame PUBLIC BaseGame)
```

---

### Game State
Like we know with ```UnrealEngine``` GameState it's needed for:

The Game State is responsible for enabling the clients to monitor the state of the game. Conceptually, the Game State 
should manage information that is meant to be known to all connected clients and is specific to the Game Mode but is 
not specific to any individual player. It can keep track of game-wide properties such as the list of connected players,
team score in Capture The Flag, missions that have been completed in an open world game, and so on.

So, if you want to create your own game state you must inherit from base class: ```BaseGameState```.

PS: don't forget to connect it in your game-cmake using target ```BaseGame```
```cmake
target_link_libraries(YourGame PUBLIC BaseGame)
```

---

### Player State
Like we know with ```UnrealEngine``` PlayerState it's needed for:

A PlayerState is created for every player on a server (or in a standalone game). PlayerStates are replicated to all clients, 
and contain network game relevant information about the player, such as playername, score, etc.

So, if you want to create your own player mode you must inherit from base class: ```BasePlayerState```.

PS: don't forget to connect it in your game-cmake using target ```BaseGame```
```cmake
target_link_libraries(YourGame PUBLIC BaseGame)
```



## 💭 What in the future?

I want to implement more and more things to give abilities like:

- Working with network, like in UnrealEngine 4\5:
    - real-time replications
    - different types of replications
    - write my own UDP protocol for data transferring
- Improve working with lightning:
    - Give an ability to create different types of lighting: global, point
    - Working with gamma and post-processing
- Pick up all the best things from an SFML(and plugins to it) in the one Engine(VaKon2D)
- Easy working with se\deserializing of game data
- Adding an ability to integrate own DLC to a game
- Supporting of all new compilers: GCC, G++, Clang, MSVC
- The engine will be cross-platform
- Shader builder for PRO users
- Add working with audio

---

## 📞 Feedback & Contacts

You can send me e-mail: Valerii.Koniushenko@gmail.com or try to find me in telegram: @markmoran24
