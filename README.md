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




## System of Linear Equations Solver - Server and Client

### Overview:

This program implements a system of linear equations solver using a client-server architecture. The server hosts the solver, and clients can connect to solve their systems of linear equations.

### Server Part:

- **Functionality:**
  - Hosts the system of linear equations solver.
  - Implements Gaussian elimination to solve the equations.
  - Sends the solution (if exists) or information about the solution type back to the client.

### Client Part:

- **Functionality:**
  - Connects to the server to solve a system of linear equations.
  - Sends the coefficients and constants of the equations to the server.
  - Receives and displays the solution or information about the solution type from the server.

### How to Use:

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

### Additional Notes:

- Ensure that both the server and client programs are executed on the same network for communication.
- The server listens on a specified port for client connections.
- The client program should specify the IP address and port number of the server to connect.
- The solver uses Gaussian elimination to solve the system of linear equations.
- It communicates with the client to send and receive data related to the equations and solution.

### Files:

- **server.c:** Contains the server-side code for hosting the linear equations solver.
- **client.c:** Contains the client-side code for connecting to the server and solving the equations.

### Dependencies:

- Standard C libraries: `stdio.h`, `stdlib.h`, `string.h`, `math.h`.
- Assumes the availability of functions `recv()` and `send()` for network communication.




## Polynomial Equation Solver - Server and Client

### Overview:

This program implements a polynomial equation solver using a client-server architecture. The server hosts the solver, and clients can connect to solve their polynomial equations.

### Server Part:

- **Functionality:**
  - Hosts the polynomial equation solver.
  - Implements bisection, Newton's method, and secant method to find roots of the polynomial equation.
  - Sends the roots back to the client.

### Client Part:

- **Functionality:**
  - Connects to the server to solve a polynomial equation.
  - Sends the degree and coefficients of the polynomial equation, along with initial guesses and interval bounds, to the server.
  - Receives and displays the roots of the polynomial equation from the server.

### How to Use:

1. **Compilation:**
   - Compile the server program using a C compiler, such as `gcc`.
   - Compile the client program using a C compiler, such as `gcc`.

2. **Execution:**
   - Run the server program first. It will start hosting the polynomial equation solver.
   - Run the client program to connect to the server and solve the polynomial equation.

3. **Input:**
   - Provide the degree of the polynomial equation.
   - Enter the coefficients of the polynomial equation in descending order of degree.
   - Provide an initial guess for iterative methods (Newton's method and secant method).
   - Specify an initial interval \([a, b]\) for the bisection method.

4. **Output:**
   - The server calculates the roots using various methods and sends them back to the client.
   - The client displays the roots of the polynomial equation.

### Additional Notes:

- Ensure that both the server and client programs are executed on the same network for communication.
- The server listens on a specified port for client connections.
- The client program should specify the IP address and port number of the server to connect.
- The solver offers multiple methods (bisection, Newton's method, secant method) for finding roots based on the user's input.
- It communicates with the client to send and receive data related to the polynomial equation and roots.

### Files:

- **server.c:** Contains the server-side code for hosting the polynomial equation solver.
- **client.c:** Contains the client-side code for connecting to the server and solving the polynomial equation.

### Dependencies:

- Standard C libraries: `stdio.h`, `stdlib.h`, `math.h`.
- Assumes the availability of functions `recv()` and `send()` for network communication.



## Maze Escape Game - Server and Client

### Game Overview:

The Maze Escape Game is an exciting adventure where players navigate through a maze to reach the end point while avoiding obstacles and traps. Players start from the initial position and must find a way to the last position on the game board. If they encounter traps or fail to reach the end, they have options to restart the game from the beginning or continue from a specific level.

### Game Rules:

- Players are placed at the 1st position on the game board and must reach the last position to win.
- If a player loses before reaching level 5, they must restart the game from level 1.
- If a player loses at level 5 or beyond, they can restart the game from level 5.
- Players can move in four directions: Up, Down, Left, and Right.
- Players should avoid obstacles ('X') and traps ('*') on the game board.
- To move, players need to input the following keys:
  - 'w' or 'W' to move Up
  - 's' or 'S' to move Down
  - 'a' or 'A' to move Left
  - 'd' or 'D' to move Right

### Game Mechanics:

- The game board is a 16x16 grid.
- The player ('P') starts at position (0, 0) and must reach position (15, 15) to win.
- Obstacles ('X') are randomly placed on the game board to add challenge.
- Traps ('*') are also placed randomly, and if a player steps on a trap, they might lose the game depending on the level.
- Players can move one step at a time and must make strategic decisions to avoid obstacles and traps.
- The game offers multiple levels, and each level increases in difficulty.
- Players have the option to restart the game from level 1 or level 5 if they lose.

### Game Implementation:

- The game is implemented in C language.
- The `makeboard` function initializes the game board with obstacles, traps, player position, and end point.
- Players can input their moves, and the `movement` function handles player movement and validates input.
- The `isValidPath` function checks if there is a valid path to reach the end point.
- Players receive feedback on their moves and game progress.
- The game continues until the player reaches the end, encounters a trap, or completes all levels.

### Running the Game:

- Compile the source code using a C compiler.
- Run the executable file to start the game.
- Follow the on-screen instructions to play the game.
- Enjoy the challenge of navigating through the maze and reaching the end!

### Additional Notes:

- Players can explore different strategies to find the optimal path through the maze.
- The game offers a blend of strategy, problem-solving, and entertainment.
- Players can compete with friends to see who can complete all levels with the fewest moves.

### Have Fun Playing!

Enjoy the Maze Escape Game and challenge yourself to conquer all levels. Good luck, and may your escape be swift and successful!
