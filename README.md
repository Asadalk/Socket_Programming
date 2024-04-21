# Socket_Programming

## Tic Tac Toe Game - Server and Client

### Overview:

This program implements a simple Tic Tac Toe game using a client-server architecture. The server hosts the game, and clients can connect to play against each other.

### Server Part:

- **Functionality:**
  - Hosts the Tic Tac Toe game.
  - Receives player moves from clients.
  - Validates moves and checks for a winner or draw.
  - Sends game status updates to clients.

### Client Part:

- **Functionality:**
  - Connects to the Tic Tac Toe game server.
  - Displays the game board.
  - Allows the player to make moves by choosing cell numbers.
  - Sends moves to the server and receives updates.

### How to Use:

1. **Compilation:**
   - Compile the server program using a C compiler, such as `gcc`.
   - Compile the client program using a C compiler, such as `gcc`.

2. **Execution:**
   - Run the server program first. It will start hosting the Tic Tac Toe game.
   - Run the client program to connect to the server and start playing the game.

3. **Gameplay:**
   - Players take turns making moves by entering cell numbers (1 to 9).
   - The server validates each move and checks for a winner or draw after each move.
   - The game continues until one player wins or the game ends in a draw.

4. **End of Game:**
   - If one player wins, the server sends a message indicating the winner to both clients.
   - If the game ends in a draw, the server sends a draw message to both clients.

### Additional Notes:

- Ensure that both the server and client programs are executed on the same network for communication.
- The server listens on a specified port (8080 by default) for client connections.
- The client program should specify the IP address and port number of the server to connect.
- Error handling is basic and may need enhancements for robustness in a production environment.

### Files:

- **server.c:** Contains the server-side code for hosting the Tic Tac Toe game.
- **client.c:** Contains the client-side code for connecting to the server and playing the game.

### Dependencies:

- Standard C libraries: `stdio.h`, `stdlib.h`, `string.h`, `unistd.h`, `arpa/inet.h`, `netinet/in.h`.
- Assumes the availability of functions `recv()` and `send()` for network communication.




## Snake and Ladder Game - Server and Client

### Overview:

This program implements a Snake and Ladder game using a client-server architecture. The server hosts the game, and clients can connect to play against each other.

### Server Part:

- **Functionality:**
  - Hosts the Snake and Ladder game.
  - Manages player movements based on dice rolls.
  - Handles snakes and ladders interactions.
  - Sends game board updates to clients.

### Client Part:

- **Functionality:**
  - Connects to the Snake and Ladder game server.
  - Displays the game board.
  - Allows players to roll the dice and see the results.
  - Receives game board updates from the server.

### How to Use:

1. **Compilation:**
   - Compile the server program using a C compiler, such as `gcc`.
   - Compile the client program using a C compiler, such as `gcc`.

2. **Execution:**
   - Run the server program first. It will start hosting the Snake and Ladder game.
   - Run the client program to connect to the server and start playing the game.

3. **Gameplay:**
   - Players take turns rolling the dice.
   - The server calculates the new position based on the dice roll and handles snakes and ladders.
   - The game continues until one player reaches the final square (100).

4. **End of Game:**
   - The server declares the winner when one player reaches the final square.
   - Players can continue playing by rolling the dice until the game ends.

### Additional Notes:

- Ensure that both the server and client programs are executed on the same network for communication.
- The server listens on a specified port for client connections.
- The client program should specify the IP address and port number of the server to connect.
- The game board displays the positions of both players, snakes, and ladders.
- The client sends a request to roll the dice to the server, which sends back the result.

### Files:

- **server.c:** Contains the server-side code for hosting the Snake and Ladder game.
- **client.c:** Contains the client-side code for connecting to the server and playing the game.

### Dependencies:

- Standard C libraries: `stdio.h`, `stdlib.h`, `string.h`, `time.h`.
- Assumes the availability of functions `recv()` and `send()` for network communication.
- Uses ANSI escape codes for colored output on supported terminals.




### System of Linear Equations Solver - Server and Client

#### Overview:

This program implements a system of linear equations solver using a client-server architecture. The server hosts the solver, and clients can connect to solve their systems of linear equations.

#### Server Part:

- **Functionality:**
  - Hosts the system of linear equations solver.
  - Implements Gaussian elimination to solve the equations.
  - Sends the solution (if exists) or information about the solution type back to the client.

#### Client Part:

- **Functionality:**
  - Connects to the server to solve a system of linear equations.
  - Sends the coefficients and constants of the equations to the server.
  - Receives and displays the solution or information about the solution type from the server.

#### How to Use:

1. **Compilation:**
   - Compile the server program using a C compiler, such as `gcc`.
   - Compile the client program using a C compiler, such as `gcc`.

2. **Execution:**
   - Run the server program first. It will start hosting the linear equations solver.
   - Run the client program to connect to the server and solve the system of linear equations.

3. **Input:**
   - Provide the number of equations and variables.
   - Enter the coefficients of each equation and constants.
   - The client sends this input to the server.

4. **Output:**
   - The server calculates the solution using Gaussian elimination.
   - It sends the solution type (unique, infinite, or no solution) and the solution (if exists) back to the client.
   - The client displays the solution or information about the solution type.

#### Additional Notes:

- Ensure that both the server and client programs are executed on the same network for communication.
- The server listens on a specified port for client connections.
- The client program should specify the IP address and port number of the server to connect.
- The solver uses Gaussian elimination to solve the system of linear equations.
- It communicates with the client to send and receive data related to the equations and solution.

#### Files:

- **server.c:** Contains the server-side code for hosting the linear equations solver.
- **client.c:** Contains the client-side code for connecting to the server and solving the equations.

#### Dependencies:

- Standard C libraries: `stdio.h`, `stdlib.h`, `string.h`, `math.h`.
- Assumes the availability of functions `recv()` and `send()` for network communication.




## Maze Escape Game

### Introduction
Maze Escape is a text-based game where you navigate through a maze-like grid to reach the end point. The game consists of multiple levels, each with increasing difficulty.

### Features
- Randomly generated maze-like grids for each level.
- Obstacles and pitfalls scattered throughout the grid to challenge the player.
- Simple controls for movement: Up (8), Down (2), Left (4), Right (6).
- Clear rules and instructions provided at the start of the game.

### How to Play
1. Compile and run the `version.c` file using a C compiler.
2. Follow the on-screen instructions to navigate through the maze.
3. Use the controls to move the player character ('P') towards the exit ('E').
4. Avoid obstacles ('X') and pitfalls ('*') to prevent losing the game.
5. Reach the end point to progress to the next level.

### Controls
- Enter `0` to display the game rules.
- Use `2`, `4`, `6`, `8` to move the player character: Down, Left, Right, Up respectively.
- At the end of each level, enter `Y` to progress to the next level or any other key to quit.
- If you lose strictly before level 5 then you to restart the game from level 1 or in other cases you will get chance to continue game from level 5.

### Game Progression
- The game consists of multiple levels, each with a unique randomly generated maze.
- As you progress through levels, the difficulty increases with more obstacles and pitfalls.
- Win the end of level 7 to win the game and become the ultimate maze escape champion!

### Requirements
- C Compiler (GCC recommended)
- Standard C Libraries: `stdio.h`, `stdlib.h`, `time.h`

### Author
Created by Asadullah Faisal(Faizal)

### Acknowledgments
Inspired by maze games and programming challenges.
