# Space Rocket
An upcoming simple game where you control a space rocket that must avoid asteroids and shoot them down with a laser beam. 
The game is built in C++ using the ***OPENGL*** & ***GLUT*** library for graphics and input handling.

## Design Pattern

The game is structured using the Model-View-Controller (MVC) design pattern. The Model represents the game state, including the position of the rocket and asteroids, the score, and other variables. The View handles the graphical rendering of the game, including the background, the rocket, the asteroids, and the laser beams. The Controller handles user input, updating the model, and triggering the view to update accordingly.

## How to Play

Use your mouse to move the space rocket and avoid the asteroids. The rocket fires a laser beam automatically which can be used to destroy the asteroids. Whenever the laser beam collides with an asteroid, you will earn points. The game is over when the rocket collides with an asteroid. Good luck!

## Installations and Dependencies

To run this game, you must install:
  1. C++ Compiler
  2. OpenGL
  3. GLUT 
