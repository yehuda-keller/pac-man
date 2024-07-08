# Pacman Game

## Introduction to Object-Oriented Programming and Software Engineering

## General Explanation:

In this exercise, we implemented the well-known and beloved Pacman game. The goal of the game is to progress through the levels and avoid the ghosts that try to prevent us from eating the cookies. We created three levels of varying difficulty and tried to incorporate as much gameplay as possible while utilizing the knowledge we gained in the course.

## Gameplay:

In each level, there are several cookies that the player needs to eat to progress. To advance to the next level, all cookies must be eaten. There are several obstacles in each level, such as doors that prevent access to certain rooms unless a key is eaten, walls that cannot be passed through, and ghosts that try to stop us from reaching the cookies.

## Created Files:

### Core Files:
- `Main.cpp`

### Board Files:
- `Board.h` `Board.cpp`
  - This class serves as a base class for `DataBoard` and `GameBoard`.

### Cookie Files:
- `Cookie.h` `Cookie.cpp`
  - This class represents the game's cookies that the player must eat. Each cookie grants the player 2 points.

### Date Board Files:
- `DateBoard.h` `DateBoard.cpp`
  - This class displays game information, including game time, remaining lives, and the remaining time for any timed gifts collected.

### Demon Files:
- `Demon.h` `Demon.cpp`
  - This class, inheriting from `MovingObject`, represents the game's enemies and serves as a base class for `RandomDemon` and `SmartDemon`.

### Door Files:
- `Door.h` `Door.cpp`
  - This class manages the doors in the game. Players cannot pass through them unless they collect a key. In Super Pacman mode, players can smash through the doors.

### Gift Files:
- `FreezeGift.h`
  - This class represents a gift that freezes ghosts in place for a limited time.
- `LifeGift.h`
  - This class, inheriting from `Gift`, grants the player an extra life if they have less than three lives. If the player has full lives, the gift is ignored.
- `SuperGift.h`
  - This gift, inheriting from `Gift`, turns the player into Super Pacman.
- `TimeGift.h`
  - This gift, inheriting from `Gift`, grants additional time to complete the game.

### Game Board Files:
- `GameBoard.h` `GameBoard.cpp`
  - This class manages the game board, its size, and generates an invisible board to obtain initial object sizes and positions.

### Game Controller Files:
- `GameController.h` `GameController.cpp`
  - This is the core class of the game, responsible for the game flow, including updating the game with each board movement.

### Game Object Files:
- `GameObject.h` `GameObject.cpp`
  - This class serves as a base class for `MovingObject` and `StaticObject`.

### Game Resources Files:
- `GameResources.h` `GameResources.cpp`
  - This class is responsible for loading game files, including effects, textures, and fonts.

### Key Files:
- `Key.h` `Key.cpp`
  - This class manages the keys collected to pass through doors.

### Menu Files:
- `Menu.h` `Menu.cpp`
  - The lobby serves as the entry point to the game, allowing users to start the game, get help, exit, or mute the background sound.

### Moving Object Files:
- `MovingObject.h` `MovingObject.cpp`
  - This class serves as a base class for `Player` and `Demon`.

### Pacman State Files:
- `PacmanState.h`
  - This class serves as a base class for `RegularState` and `SuperState`.

### Player Files:
- `Player.h` `Player.cpp`
  - This class manages the player in the game and holds the player's score.

### Random Demon Files:
- `RandomDemon.h` `RandomDemon.cpp`
  - This class manages the random ghost. If it collides with the player, the player loses a life, and the ghost returns to its initial position.

### Regular State Files:
- `RegularState.h` `RegularState.cpp`
  - This class manages player collisions in regular mode.

### Smart Demon Files:
- `SmartDemon.h` `SmartDemon.cpp`
  - This class manages the smart ghost, which tracks the player in regular mode and avoids the player in Super Pacman mode.

### Static Object Files:
- `StaticObject.h`
  - This class serves as a base class for all static objects in the game.

### Super State Files:
- `SuperState.h` `SuperState.cpp`
  - This class manages collisions in Super Pacman mode, allowing the player to smash through doors and reset ghosts to their initial positions.

### Time Manager Files:
- `TimeManager.h` `TimeManager.cpp`
  - This class manages the game's timing, including stage time, movement time, Super Pacman time, and freeze time.

### Wall Files:
- `Wall.h` `Wall.cpp`
  - This class, inheriting from `StaticObject`, represents the game's walls and defines the stage boundaries.

### Event Handler Files:
- `EventHandler.cpp`
  - This file contains functions that assist in updating events during the game.

## Design Patterns:

- **Singleton Pattern**: Implemented in `GameResources`, `DataBoard`, and `TimeManager` to allow global access across classes.
- **State Pattern**: Implemented in `PacmanState` to manage player states (Regular and Super).

## Algorithms / Game Mechanics:

### Smart Ghost:
- The smart ghost receives a pointer to the player object to know its position. It calculates the larger distance, either horizontal or vertical, to reduce the gap in that direction. If the player is in Super Pacman mode, the ghost tries to move away from the player.

### Adding a Level:
- To add a level beyond the three created, edit the text file to add the stage size and allotted time. For example:
