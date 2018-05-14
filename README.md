﻿# We are the team JADY

## Introduction
This game was created by 4 students of UPC, CITM on the Game Design and Development degree.
In this project we will recreate the arcade game Last Resort, 
we will use the sprites of the original game and we will program it from scratch.
You can find all the information and necessary material we used to recreate this game in our repository on Github.
About Last Resort
Last Resort game imerses us in a world where the apocalypse is approaching and we will try to stop it.
In order to acomplish our mission, we pilot a spaceship with the help of a small drone , the "unit",
and we will defeat all kinds of enemies.
It is a sci-fi side-scrolling shooter developed by SNK 1992.


## Find project
https://github.com/YessicaSD/JADY_Project1_CITM_UPC/edit/master/README.md
https://github.com/Dasanch/Project_1_JADY_UPC


## Credits

> Jaume Montagut i Guix
* _Find him on his webpage https://wadoren.wixsite.com/gamedev
* _Github profile: https://github.com/JaumeMontagut_

> Alejandro Gamarra Niño
* _Find him on Instragram as @ax3_rt_
* _Github profile: https://github.com/alejandro61299_

> Dani Sanchez Flores
* _Find him on Instragram as @vampir_nex
* _Github profile: https://github.com/Dasanch_

> Yessica Servin Dominguez          
* _Find her on Instragram as @randomgerbit_
* _Github profile: https://github.com/YessicaSD_

##SPAWN PLAYERS ---------------------------------------------------------------------
	- Add credits: "c"
	- Spawn player 1: "1"
	- Spawn player 2: "2"

## Movement keys --------------------------------------------------------------------
### Player 1:
#### Keyboard:
- **A**: Move left
- **S**: Move down
- **D**: Move right
- **W**: Move up
- **Space**: Shoot
- **Left shift**: Lock the unit
#### Controller:
- **Left Joystick**: Movement
- **B**: Shoot

### Player 2:
#### Keyboard:
-** Left arrow **: Move left
-** Down arrow **: Move down
-** Right arrow **: Move right
-** Up arrow **: Move up
-** Rigth Ctrl **: Shoot
-** Rigth Shift **: Lock the unit
#### Controller:
-** Left Joystick **: Movement
-** B **: Shoot


## Other functions --------------------------------------------------------------------
-** Esc **: Closes the game
-** Space **: Skip intro
-** Numpad +**: Volume up
-** Numpad -**: Volume down

## Debug functionality ----------------------------------------------------------------

### BASIC DEBUGGING:
-** F1 **: Show collision boxes
-** F2 **: God mode
-** F3 **: Pause/Play game
-** F4 **: Frame forward (only when the game is paused)

### CAMERA DEBUGGING
- **Numpad 7**: Zoom in
- **Numpad 9**: Zoom out
- **Numpad 8**: Move camera up
- **Numpad 4**: Move camera left
- **Numpad 5**: Move camera down
- **Numpad 6**: Move camera right
- **Numpad 0**: Re-center camera
- **Numpad /**: Show world grid (which has marks every 100 units)
- **Numpad (*)**: Show background grid (which has marks every 100 units)

### ADVANCED DEBUGGING:
How to use advanced debugging?
1. DEBUG:
   - Release the **F5** key to go to a stage.
   - Release the **F7** key to spawn an enemy in front of the player's 1 ship.
   - Release the **F8** key to spawn a powerup in front of the player's 1 ship.
2. SELECT ANOTHER ELEMENT FOR DEBUGGING:
   - **Hold F5** to select stages, and **press the number/s** of the scene you want to go to (see debug stages table).
   - **Hold F7** to select enemies, and **press the number/s** of the enemy you want to spawn in front of the player's 1 ship (see debug enemies table).
   - **Hold F8** to select powerups, and **press the number/s** of the powerup you want to spawn in front of the player's 1 ship (see debug powerups table).

#### STAGES DEBUG TABLE:
	- 1: Stage 1
	- 2: Stage 2
	- 5: Stage 5
	- 6: Win
	- 7: Lose
	- 8: Neo geo screen
	- 9: Title screen
	- 10: Ready screen
	- 11: Continue screen

#### ENEMIES DEBUG TABLE:
	- 0: Basic
	- 1: Oscilator
	- 2: Powerdropper
	- 3: Metalcrow

#### POWERUPS DEBUG TABLE:
	- 0: Speed
	- 1: Despeed
	- 2: Laser
	- 3: Homing
	- 4: Ground

## Changes ----------------------------------------------------------------------------

### CHANGES IN V0.7.0.0
- Added ship colliders
- Added  2 enemies: Oscilator & RedBat
- Added camera debbuging mode
-Added pause/play key (**F3**)
- Enemies can now take damage and change their sprite
- Now the unit inflicts damage
- Camera movement has been fixed
- Several bugs solved

### CHANGES IN V0.6.0.0
- Added stage 5 music
- Added stage 5 stars background and ship
- Added fullscreen mode
- Added advance debugger
- Added ability to throw the unit

### CHANGES IN V0.5.0.0
- Added UI
- 2 Power Ups
- 3 Enemies (One that shot)
- Debug Modes (GodMode)
- Second player
- Unit

### CHANGES IN V0.4.0.0
- Partially added last resort title animations
- Added colliders for the player and a static enemy
- Added particles and sfx when the player shoots
- Completed neo geo screen animation
 
### CHANGES IN 0.3.1.0
- Added Continue Screen
- Fixed GameOver Screen

### CHANGES IN V0.3.0.0
- The player movement is fixed. 
- Added level 2.
- Added the game title screen, the neogeo screen, game over screen. 
- Added music to neogeo, the title screen, level 1 and 2.

### CHANGES IN V0.2.0.1:
- Added lights
- Changed 3r level of the background.
- Player transition move.

### CHANGES IN V0.2.0.0:
- Added player 1 movement and animation
- Added paralax for all backgrounds with 3 different levels of depth.
- Added unfunctional audio module
