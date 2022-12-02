# Cub3D

This project is inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever. The goal of this project is to explore the concept of ray-casting by creating a dynamic view inside a maze, in which the user has to find their way. 

This project is an excellent way to practice and refine skills in many areas, including: 
- Rigor 
- Use of C 
- Use of basic algorithms 
- Information research 
- Windows 
- Colors 
- Events 
- Fill shapes 

This project is also a great way to explore the playful practical applications of mathematics without having to understand the specifics. By referencing the numerous documents available on the internet, users can use mathematics as a tool to create elegant and efficient algorithms. 

The project must be written in C and must comply with the Norm. All heap allocated memory space must be properly freed when necessary, and any unexpected quits, segmentation faults, bus errors, double frees, and other undefined behaviors will result in a 0 evaluation. 

## How do I run it?
You can run the command 'make' which will compile everything and make a executable. This executable can be run with any valid .cub file.

## What is a .cub file?
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

Good luck and have fun with Cub3D!
