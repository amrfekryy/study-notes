- Read about POP vs OOP.

### Terminology
- `Class`: a structure definition (blueprint/template) that groups some `members` together:
	- `attributes/properties`: variables that hold related pieces of data.
	- `methods/procedures`: functions that operate on the data.
- `Object`: an instance of a class.
	- properties differ from an object to another.
	- methods are shared among all objects of a class.
- `Abstraction`: hiding the internals of the object and providing a `public interface` for the user using `access specifiers`:
	- `public` members: accessible by inside methods and outside functions.
	- `private` members: only accessible by inside methods. (default if not specified)
	- `const` methods do not change attributes.
	- `getters/accessors`: methods that get the value of a private attribute (should be const).
	- `setters/mutators`: methods that set the value of a private attribute.
	- why abstraction?
		- protecting private data through getters.
		- validating data in setters.

### Defining and Using Classes
- see lec2 - p 16, 20 - 26

- we should avoid `stale` data.
	- a class shouldn't have attributes that depend on other attributes.
	- when we update dependencies we will have to update dependants.
	- unupdated dependants will hold stale values.
	- we should use methods to calculate dependants instead.


### File Strucuture

```cpp
	// ClassName.h (header/specification file) : Rectangle.h

	class Rectangle
	{
		private:
			double width;
			double length;

		public:
			// functions declarations
			void setWidth(double);
			void setLength(double);
			double getWidth() const;
			double getLength() const;
			double getArea() const;
			
			// inline function definitions
			void setWidth(double wid) { width = wid; }
			void setLength(double len) { length = len; }
			double getWidth() const { return width; }
			double getLength() const { return length; }
			double getArea() const { return width * length; }
	
	}; // semi-colon

		// inline function definitions		
	inline void Rectangle::setWidth(double wid) { width = wid; } // no semi-colon
	inline void Rectangle::setLength(double len) { length = len; }
	inline double Rectangle::getWidth() const { return width; }
	inline double Rectangle::getLength() const { return length; }
	inline double Rectangle::getArea() const { return width * length; }

```

```cpp
	// ClassName.cpp (implementation file) : Rectangle.cpp

	#include 'Rectangle.h'

	// regular function definitions
	void Rectangle::setWidth(double wid) { width = wid; } // no semi-colon
	void Rectangle::setLength(double len) { length = len; }
	double Rectangle::getWidth() const { return width; }
	double Rectangle::getLength() const { return length; }
	double Rectangle::getArea() const { return width * length; }

	// inline VS regular functions
	// inine: code is copied -> more memory but less CPU and execution
	// regular: code is referenced -> less memory but more CPU for lookups
```

```cpp
	// Main.cpp

	#include 'Rectangle.h'

	Rectangle box;
	box.setWidth(5)
	box.setWidth(5)
	box.getArea() // 25
```

### Constructors
- a member function that is automatically called when an object is created.
	- to construct the object, give attributes initial values.
- has no return type.
- has same name as the class.
- can be regular or inline ??

```cpp
	// Rectangle.h

	class Rectangle
	{
		private:
			double width;
			double length;

		public:
			// default constructor (has no args)
			Rectangle() {/* does nothing */} // written by cpp if we don't write it.
			
			Rectangle() { // user defined default constructor.
				width = 0;
				length = 0;
			}

			// parametrized constructor (with args)
			Rectangle(double wid, double len) { // user defined parametrized constructor
				width = wid;
				length = len;
			}

			Rectangle(double = 0, double = 0); // if all args has default values then it is a default constructor.

			// member initializer list (another way to initialize member attributes)
			// default
			Rectangle(): width(0), length(0) {} 
			Rectangle(): width{0}, length{0} {} 
			// parametrized
			Rectangle(double wid, double len): width(wid), length(len) {} 
			Rectangle(double wid, double len): width{wid}, length{len} {} 

	};

	// Main.cpp
	
	// class instantiation
	Rectangle r; // calls default constructor , throws error if constructor if parametrized.

	Rectangle r(10, 5); // calls parametrized constructor.

```
