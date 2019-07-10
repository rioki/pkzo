
# A Friendly Greeting

Hello and welcome to pkzo. In this tutorial I will show you how to get started 
with pkzo. This tutorial assumes you already have a working installation of 
pkzo.

## The Engine

The Engine class is the class that holds everything together, it initializes
everything, ensures that everything gets updated and cleans up the afterwards.
It is generally advised, although not necessary, that you derive you own 
instance of the Engine class. In the case of this tutorial I have created
the HelloEngine class.

``` cpp
namespace hello
{
	class HelloEngine : public pkzo::Engine
	{
	public:
		HelloEngine();

	private:

	};
}
```

Each engine instance has it's own id. This id is used for multiple things, such
as it determines the default location of your settings. This id needs to be 
given to the Engine on construction. To this end the default constructor calls
the Engine constructor with it's id. 

``` cpp
	HelloEngine::HelloEngine()
	: Engine{"Hello"}
	{
		// ...
	}
```

## The Main Function

As you know, the main function is the function that is the most outer function
of your program, also known as the entry point. This is the location the engine
will reside in. This tutorial has the standard main function for pkzo:

``` cpp
int main(int argc, char* argv[])
{
	try
	{
		auto engine = hello::HelloEngine{};
		return engine.run();
	}
	catch (const std::exception& ex)
	{
		pkzo::show_error_dialog("Exception", ex.what());
		return -1;
	}
}
```

It creates an instance of the engine and calls the run function which is the 
so called main loop. The engine execution is wrapped by a try/catch block
to catch any stray exceptions. 

The catch block only handles std::exception, because all exceptions that
pkzo generates are derived from std::exception. If you are paranoid,
you can also add the elypsis catch block below the one for 
std::exception. This may be of interest if you integrate third party
libraries. 

``` cpp
	catch (...)
	{
		pkzo::show_error_dialog("Exception", "Unknown exception.");
		return -1;
	}
```

## The Greeting Screen

So far the program only shows a blank screen. A greeting program would 
not be a greeting program if it did not have a friendly greeting. 

The GreetingScreeen does exactly this. Like the engine it is advised,
but not required, to subtype the Screen class.

``` cpp
namespace hello
{
	class GreetingScreen : public pkzo::Screen
	{
	public:
		GreetingScreen(const glm::vec2& size);
	};
}
```

The GreetingScreen has as a construction parameter the size. This is done to
match the screen to the window size in the constructor. Screens can have any
size you like, but for overlay screens, aka HUD, you generally get the best
results by syncing the window size to the screen size and adjusting the 
elements accordingly. 

``` cpp
    HelloEngine::HelloEngine()
    : Engine{"Hello"}
    {
        auto screen = std::make_shared<GreetingScreen>(glm::vec2(get_window().get_size()));
        set_screen(screen);
    }
```

The overlay screen is simply set on the engine with set_screen. Please not that 
the given screen will only be active on the next frame, so calling get_screen
immediately will still have the previous screen.

pkzo provides three basic built in type of element for screen, called screen 
nodes, that is Rectangle, Text and HitArea. These can then be grouped into more
complex elements using ScreenNodeGroup. A companion library pkzo-ui provides 
higher level user interface items, such as Button, CheckBox or TextInput.

The greeting screen contains two nodes a text node and a rectangle node. 
The text node is constructed as follows:

``` cpp
		auto font = std::make_shared<pkzo::Font>("../data/fonts/DejaVuSans.ttf", 52);
        auto white = std::make_shared<pkzo::Material>("../data/materials/TextWhite.pxm");
        auto hello_text = std::make_shared<pkzo::Text>(glm::vec2{0.0f, 150.0f}, "Hello", font, white);
        add_node(hello_text);
```

It loads a font and a material and create the text node with the test "Hello" and
adds it the screen. For a start it is advised you use the materials and shaders
provided by pkzo, how to create your own will be handled in a different tutorial.

The rectangle node is constructed as follows:

``` cpp
        auto logo = std::make_shared<pkzo::Material>("../data/materials/PkzoLogo.pxm");
        auto rectangle = std::make_shared<pkzo::Rectangle>(glm::vec2{0.0f}, glm::vec2(395.0f, 117.0f), logo);
        add_node(rectangle);
```

It just loads a material, constructs the rectangle and puts it onto the screen. 
You may notice that the material just renders the pkzo logo. 

Now you have yourself a nice friendly program.
