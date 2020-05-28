# cub3d - @ Codam Coding College
This project will allow us to understand the math behind a raycasting program/game.
Firstly reading a file rendering everything with the information given.

#### How do I run it?
You can run the command 'make' which will compile everything and make a executable. This executable can be run with any valid .cub file.

#### What is a .cub file?
A .cub file will need 9 things. 
1. `R x y` (x y will be replaced by the resolution of your choice)
2. `NO PATH_OF_FILE` *(PATH_OF_FILE will be replaced by file path)* North texture
3. `SO PATH_OF_FILE` *(PATH_OF_FILE will be replaced by file path)* South texure
4. `EA PATH_OF_FILE` *(PATH_OF_FILE will be replaced by file path)* East texture
5. `WE PATH_OF_FILE` *(PATH_OF_FILE will be replaced by file path)* West texture
6. `S PATH_OF_FILE` *(PATH_OF_FILE will be replaced by file path)* Sprite/Object texture
7. `C x,x,x` (the 3 exes will be replaced by a rgb code. must be between 0-255) Ceiling colour
8. `F x,x,x` (the 3 exes will be replaced by a rgb code. must be between 0-255) Floor colour
9. A map.
9a. Movable space is 0.
9b. Walls are 1.
9c. Padding is ' ' (space)
9d. Sprite/object is 2
