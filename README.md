\mainpage Carousel documentation

Carousel
========

Note, that it is still in development
----------

Carousel is a managed component library for desktop applications that helps to extending core functionality of the application by external or internal components. An extension (component) can provide a toolbar with new tools, menus,  commands or dock widgets, listen for and respond to events, perform feature validation, and so on. 

There are Carousel's basic concepts: **Components**, **Providers**, **Installers**, **Bootloaders** and **Service Locator**.

Components
----------

An IComponent is a base unit of the Carousel, that can contain UI and/or logic features, provides or exposes some services for the other components. The instances of the IComponent class could
be registered statically in code or discovered by other ways - e.g., loaded from the specified paths at start-time or by demand.

Components are integrated in the application by the **Providers**. Different providers specify different component configuring and loading time - the simplest **ComponentProvider** means **compile-time** components populating:

	IComponentProvider *Bootloader::createComponentProvider()
	{
		IComponentProvider *provider = new ComponentProvider();
		provider->registerComponent(new InteractionServiceComponent());
		provider->registerComponent(new DisplayComponent());

		return provider;
	}

DirectoryComponentProvider can discover and load components	on **run-time**. It uses to load custom components (which may appear as custom installed plugins) from the specified library path. For example, this directory provider will discover and load (if it is possible) all components from the **./components** directory at the **startup-time**:

	IComponentProvider *Bootloader::createComponentProvider()
	{
		DirectoryComponentProvider *directoryProvider = new DirectoryComponentProvider("./components");

		return directoryProvider;
	}	

You also can use FileComponentProvider to load component by demand (e.g., user wants to load just-downloaded component) on **run-time**.

External components can be loaded in right order (if they have a dependencies) from the defining paths or can be configured statically in the code (internal components).

Providers
---------

Installers
----------

Bootloaders
-----------
The bootloader instance is one of the first instances who starts Carousel mechanism.
Mainly, is starts a **registration phase**.

It creates and registers an IServiceLocator itself and common services, like LoggerFacade,
IComponentManager and, optionally, QMainWindow for the GUI applications. QMainWindow is
just a shell or frame for the application, it is absolutely empty, but then new components
could populate it with menus, toolbars, dock widgets and the central widget.

Usually an IBootloader is implemented (in BootloaderBase or in more specific CarouselBootloader
class) as a sequence of pairs **create<smth>() - configure<smth>()** methods, and each of them
could be overridden to replace default instantiation or default configuration.
For example, to use your own logger system it is just needed to override BootloaderBase::createLoggerEngine()
method.

After bootloading process the configured IServiceLocator is available through
serviceLocator() method. Later it will be injected to the all components and other
elements during **configuration phase**, when they will start or initialize. It is needed to register/locate to
common services and your components' services.

To start new application you also should to override BootloaderBase::createComponentProvider() or
BootloaderBase::configureComponentProvider() method to determine way in which your application will
be populated by the components. For example, here is a component **provider** which will load components
from the **"./components"** directory at the **start-time** and which also has four built-in components,
configured statically at the **compile-time**:

	IComponentProvider *MyBootloader::createComponentProvider()
	{
	    CompositeComponentProvider *provider = new CompositeComponentProvider();
	    provider->addProvider(new DirectoryComponentProvider("./components"));
	    provider->registerComponent(new InteractionServiceComponent());
	    provider->registerComponent(new ComponentSystemUIComponent());
	    provider->registerComponent(new UndoComponent());
	    return provider;
	}

Then just pass bootloader to the application:

	#include "MyBootloader.h"
	#include <framework/AbstractApplication.h>
	
	int main(int argc, char *argv[])
	{
	    AbstractApplication application(argc, argv);
	 
	    MyBootloader bootloader;
	    return application.runApplicationLoop(bootloader);
	}


Service Locator
---------------

Build
=====
Read the BUILD.txt to generate MSVS/Xcode solutions using cmake.

Supported compilers (tested ones):
==================================
<ol>
<li>msvc11 x32</li>
<li>msvc11 x64</li>
<li>mingw4.7 x32</li>
<li>mingw4.7 x64</li>
<li>gcc-4.4.5</li> - CHECK ON LINUX, IT WILL BE 4.7
</ol>
