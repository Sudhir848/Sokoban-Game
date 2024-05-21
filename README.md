## Contact

Name: Sudhir Gunaseelan

## Description

What the project does:
This project is an implementation of the Sokoban game in C++. It is based on pushing boxes to the designated storage locations, where there is a constraint that boxes can only be pushed, not pulled. The player loses if they get stuck, i.e. the boxes cannot be moved anymore.
Within this code, there is a class named Sokoban which contains information about what is happening during the game in addition to how the player can move around within it so as to win it too. This class is an extension of the sf::Drawable class found within the SFML library, which allows it to be drawn to a window. It has a number of data members as well, such as grid vector for storing the game board; board dimensions (width and height); textures and sprites corresponding to each of the game elements respectively (walls, boxes etc). It also has a player_position member that stores the player's current position on the board.
The Sokoban constructor reads in a level file and initializes the game state based on the contents of the file. When the player wants to move in a certain direction, it will be supported by the movePlayer method. In order to draw the game on the screen/window, SFML uses an implementation that follows sf::Drawable interface known as draw method. For each cell inside a grid vector, draw() method iterates setting sprite’s position coupled with changing its texture following the cell’s value.
One of the key algorithms used in the Sokoban class is the movePlayer method, which updates the game state when the player tries to move in a certain direction. It first checks if the player is trying to move outside the play area or into a wall. If the player is trying to move into a box, it checks if the box can be moved and updates the game state accordingly.
Another important method need for congratulating if the player wins is the isWon method, which checks if all of the boxes are in their designated final storage locations. It loops through the grid vector and counts the total number of boxes and the number of boxes in storage locations. If these two counts are equal, then the game is won.

### Features

Implemented a movePlayer() which moves the player sprite in 4 cardinal directions. It takes two integer parameters, x and y, which represent the horizontal and vertical movement of the player, respectively. You first calculate the new x-coordinate of the player's position by adding the x offset to the current x-coordinate. Then the new y-coordinate of the player's position by adding the y offset to the current y-coordinate. Similarly with the corresponding boxes. If the player is not trying to move into a wall or another box, the function updates the game grid by moving the player to the new position and updating the old position with an empty cell. If there is a box in the new position, the function checks whether the box can be moved to the new position based on the same conditions as for the player. If the box cannot be moved, the function returns without making any changes. Otherwise, the function updates the game grid by moving the box to the new position and the player to the old box position.
Then I have my isWon() that checks whether the current game state is a winning state or not. I did this by counting the number of boxes, the number of boxes on storage areas, and the number of storage areas in the current grid. If the number of boxes equals the number of boxes on storage areas and the number of boxes equals the number of storage areas, then the game is considered won and the method returns true. Otherwise, the method returns false.

### Memory

How I decided to store the level data including whether you used smart pointers.
I decided to store the level data using ifstream. So for this, I created an argument named filename in my constructor and then used it call in that particular level entered by the user in the command-line argument resizing the grid corresponding to the level.

### Lambdas

The lambda expression is passed as an argument to the std::for_each algorithm in the draw method of the Sokoban class. The lambda function iterates over each cell in the grid vector and draws the corresponding sprite based on the type of cell. The lambda function captures the member variables this, target, sprite, and states by reference.

In this code, I used the algorithm library as the std::for_each function, which applies the given function to each element of the range specified by the two iterators. In the Sokoban class, std::for_each is used to iterate over the elements of the grid vector, and apply a function to each element. The function checks the type of the cell and sets the appropriate texture for the sprite to be drawn. This is done by switching on the value of the cell enum variable.

## Acknowledgements

https://en.wikipedia.org/wiki/Row-_and_column-major_order
https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Texture.php
https://www.vectorstock.com/royalty-free-vector/you-win-comic-speech-bubble-cartoon-game-assets-vector-9673756
