# Game Development

## Table of Contents

- [Game Development](#game-development)
  - [Table of Contents](#table-of-contents)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [Usage](#usage)
  - [Directory Structure](#directory-structure)

---

## Prerequisites

Before using the framework, ensure you have the following dependencies installed:

- **C++ Compiler:** A C++ compiler with support for C++17.
- **CMake:** CMake build-system to handle building.
- **SFML Library:** The SFML library for windowing and event handling.

Please refer to the respective libraries' official documentation for installation instructions on your platform.

## Installation

Follow these steps to set up and use the framework:

1. **Clone the Repository:**

   Clone this repository to your local machine using Git:

   ```bash
   git clone https://github.com/firaatozkan/GameDemo.git

2. **Navigate to the Project Directory:**   

    Change your working directory to the project folder:

   ```bash
    cd GameDemo

3. **Build the project using the provided build system (e.g., Makefile):**

   ```bash
    conan install . --build=missing
    mkdir build
    cd build
    cmake ..
    cmake --build . --config

4. **Run the Sample Application:**

    Execute the sample application to verify that the framework is working:

   ```bash
    # Locate your executable
    ./GameDemo # You should see the sample "Level_1" running in a window.

## Usage

To create your own game using this framework, follow these steps:

1. **Extend the AbstractLevel Class:**

    Begin by extending the AbstractLevel class to define your game levels. Each level can have its own unique logic, entities, and components.

2. **Create Custom Game Entities:**

    Inherit from the ECS::Entity class to create custom game entities. Add various components to these entities to define their behavior, appearance, and interactions.

3. **Implement Input Handling:**

    Implement input handling logic for your game entities using the Inputs::IInputable interface. Respond to keyboard and other input events as needed.

4. **Simulate Physics:**

    Use the Physics::IUpdatable interface to simulate physics interactions for your game objects.

5. **Render Graphics:**

    Render 2D graphics and animations with the help of the Graphics::IRenderable interface.

6. **Customize Levels:**

    Customize the provided "Level_1" class or create entirely new levels for the game.

7. **Explore the Codebase:**

    Dive into the codebase, read comments, and consult the documentation to understand how to use the framework effectively.


For detailed code examples and usage guidelines, refer to the project's source code and documentation.

## Directory Structure
The project follows a structured directory layout:

**src/:** Contains the source code of the framework, organized by modules (e.g., ECS, Inputs, Physics).

**include/:** Holds header files for external inclusion.

**assets/:** A directory for storing images and assets used in your game.

**README.md:** This README file.