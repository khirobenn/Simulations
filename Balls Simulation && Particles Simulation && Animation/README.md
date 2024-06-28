# Balls Simulation & Particles Simulation & Animation
## 1. Ball Simulation :
- I used [verlet integration](https://en.wikipedia.org/wiki/Verlet_integration) to calculate the position of the ball each time.
- For collision detection, I used [Quadtree](https://en.wikipedia.org/wiki/Quadtree) to have a complexity of `nlog(n)`.
- A collision is detected if the **distance** between the center of the ball1 and the center of the ball2 **square** is `less or equal` than the **sum** of the radius of the ball1 and ball2 **square**.
- When a collision is detected, we **move** the two balls by the **normal vector** by overlap/2.

## 2. Particles Simulation :
- For collision detection, I used the samething as the collision detection in **1. Ball Simulation**.
- When a collision is detected the **color** of the two balls becomes `Red`.

## 3. Animation :
- I used the equation of a circle ( **x² + y² = radius²** ).
- For the infinity animation, I used the equation of the circle too, I just **change the x coordinate of the center of the cirlce** by **2*radius** to the left or right to make it look like infinity.


# How to use ?
## Before starting:
You will need to install [SFML](https://www.sfml-dev.org/index.php).
## 1. How to compile ? :
I compiled these files in `linux` using `make` command, this command will do all the commands we set in the `Makefile` file.
## 2. Running the file :
Add execute permission by this command : `chmod +x prog` and use this command : `./prog`.

# Some examples :
## Example 1: Balls Simulation with quadtree grid
### 1. Menu :
![1](https://github.com/khirobenn/Simulations/assets/126425282/94938e20-21ab-4ce5-b8fe-48910da2daf1)
### 2. Mode :
![2](https://github.com/khirobenn/Simulations/assets/126425282/1ac22517-90ac-4145-9749-f6317ac6a996)

### 3. Window :
After choosing the mode a window will open up.
![3](https://github.com/khirobenn/Simulations/assets/126425282/7bb6341b-7926-4b4c-8473-16202b527e54)

### Now, you can add balls by the mouse left click in the screen.
https://github.com/khirobenn/Simulations/assets/126425282/d48d985e-88d3-4bb4-81b1-de3053e07b5c

## Example 2 : Particles Simulation without quadtree grid
https://github.com/khirobenn/Simulations/assets/126425282/c0f74250-67ba-404d-8ba2-a1ec98079edd

## Example 3 : Infinity Animation
https://github.com/khirobenn/Simulations/assets/126425282/3322b8d5-548f-4e5b-93e9-9aea6b5e0a84

# Thank you for visiting my project, have a nice day !
