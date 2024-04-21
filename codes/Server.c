#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <math.h>
#include <ctype.h>

void playGame1(int);
void playGame2(int);
void playGame3(int);
void playGame4(int);
void playGame5(int);
void playGame6(int);

//For snake and ladder


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"



int rollDie() {
    return rand() % 6 + 1;
}

int movePlayer(int Player, int roll, int currentPlayer, int *newSquare) {
    int newPosition = Player + roll;

    *newSquare = newPosition;
    switch(newPosition) {
        case 6: *newSquare = 40; break;
        case 23: *newSquare = 10; break;
        case 45: *newSquare = 7; break;
        case 61: *newSquare = 18; break;
        case 65: *newSquare = 83; break;
        case 77: *newSquare = 5; break;
        case 98: *newSquare = 10; break;
    }

    if (*newSquare != newPosition) {
        if (*newSquare > newPosition) {
            return -(*newSquare); // Negative value indicates ladder
        } else {
            return *newSquare; // Positive value indicates snake
        }
    }

    if (newPosition > 100) {
        newPosition = Player;
    }

    return newPosition;
}

void sendBoard(int clientSocket, int player1, int player2, char *message, char *pos, char name1_initial, char name2_initial) {
    char board[1024];
    memset(board, 0, sizeof(board));

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            int square = (i % 2 == 0) ? 100 - 10 * i - j : 100 - 10 * i + j + 1 - 10;
            if (player1 == square) {
                strcat(board, ANSI_COLOR_RED);
                sprintf(board + strlen(board), " %c ", name1_initial);
                strcat(board, ANSI_COLOR_RESET);
            } else if (player2 == square) {
                strcat(board, ANSI_COLOR_YELLOW);
                sprintf(board + strlen(board), " %c ", name2_initial);
                strcat(board, ANSI_COLOR_RESET);
            } else {
                char temp[5];
                sprintf(temp, "%3d", square);
                strcat(board, temp);
            }
            strcat(board, " ");
        }
        strcat(board, "\n");
    }

    strcat(board, pos); // Add position information to the board
    strcat(board, message); // Append message to the board

    send(clientSocket, board, sizeof(board), 0);
}

//DIfferential equation solver

#define SIZE 100

double calculate_term(const char *term, double x, double y);
double rk(const char *function, double x0, double y0, double x_final, double h);
double calculate_term(const char *term, double x, double y) {
    double result = 0.0;
    char operation = '+'; // Default operation is addition
    double operand = 0.0; // Current operand

    // Iterate over each character in the term
    for (int i = 0; term[i] != '\0'; i++) {
        char current = term[i];

        // Check if the current character is an operator
        if (current == '+' || current == '-' || current == '*' || current == '/' || current == '^') {
            // Perform the operation based on the previous operator
            switch (operation) {
                case '+':
                    result += operand;
                    break;
                case '-':
                    result -= operand;
                    break;
                case '*':
                    result *= operand;
                    break;
                case '/':
                    if (operand == 0) {
                        printf("Error: Division by zero.\n");
                        exit(1);
                    }
                    result /= operand;
                    break;
                case '^':
                    result = pow(result, operand);
                    break;
            }

            // Update the current operation
            operation = current;
            operand = 0.0; // Reset the operand for the next number
        } else if (isdigit(current) || current == '-' || current == '.') {
            // Accumulate digits to form the operand
            operand = operand * 10 + (current - '0');
        } else if (current == 'x' || current == 'y') {
            // Handle variables
            operand = (current == 'x') ? x : y;
        } else if (isspace(current)) {
            // Skip whitespace
            continue;
        } else {
            // Unsupported character
            printf("Error: Unsupported character '%c'.\n", current);
            exit(1);
        }
    }

    // Perform the final operation
    switch (operation) {
        case '+':
            result += operand;
            break;
        case '-':
            result -= operand;
            break;
        case '*':
            result *= operand;
            break;
        case '/':
            if (operand == 0) {
                printf("Error: Division by zero.\n");
                exit(1);
            }
            result /= operand;
            break;
        case '^':
            result = pow(result, operand);
            break;
    }

    return result;
}

double rk(const char *function, double x0, double y0, double x_final, double h) {
    int n = (int)ceil((x_final - x0) / h);

    for (int i = 0; i < n; i++) {
        double x = x0 + i * h;
        double k1 = calculate_term(function, x, y0);
        double k2 = calculate_term(function, x + h / 2.0, y0 + k1 * h / 2.0);
        double k3 = calculate_term(function, x + h / 2.0, y0 + k2 * h / 2.0);
        double k4 = calculate_term(function, x + h, y0 + k3 * h);

        // Update y0 using weighted average of slopes
        y0 += h / 6.0 * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
        // Move to the next step
    }

    return y0;
}


//for polynomial equation solver


#define EPSILON 1e-6

// Define equation, bisection, newtons_method, and secant_method functions here
double equation(double x, int degree, double coefficients[]) {
    double result = 0.0;
    for (int i = 0; i <= degree; i++) {
        result += coefficients[i] * pow(x, degree - i);
    }
    return result;
}

double bisection(double (*func)(double, int, double[]), double a, double b, int degree, double coefficients[]) {
    double fa = func(a, degree, coefficients);
    double fb = func(b, degree, coefficients);
    if (fa * fb >= 0) {
        printf("Bisection method cannot guarantee convergence for the given interval.\n");
        return NAN; // Not a Number
    }
    
    while (fabs(b - a) > EPSILON) {
        double c = (a + b) / 2;
        double fc = func(c, degree, coefficients);
        if (fc == 0) {
            return c; // Root found
        } else if (fa * fc < 0) {
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }
    }
    return (a + b) / 2;
}

double newtons_method(double (*func)(double, int, double[]), double x0, int degree, double coefficients[]) {
    double x = x0;
    while (1) {
        double fx = func(x, degree, coefficients);
        double f_prime_x = (func(x + EPSILON, degree, coefficients) - func(x - EPSILON, degree, coefficients)) / (2 * EPSILON);
        double x_new = x - fx / f_prime_x;
        if (fabs(x_new - x) < EPSILON) {
            return x_new; // Root found
        }
        x = x_new;
    }
}

double secant_method(double (*func)(double, int, double[]), double x0, double x1, int degree, double coefficients[]) {
    double x_prev = x0;
    double x = x1;
    while (1) {
        double fx = func(x, degree, coefficients);
        double fx_prev = func(x_prev, degree, coefficients);
        double x_new = x - fx * (x - x_prev) / (fx - fx_prev);
        if (fabs(x_new - x) < EPSILON) {
            return x_new; // Root found
        }
        x_prev = x;
        x = x_new;
    }
}


//for Linear equation solver


#define PORT 8080

#define EPSILO 1e-10

void swap_rows(float **mat, int row1, int row2, int num_columns) {
    float *temp = mat[row1];
    mat[row1] = mat[row2];
    mat[row2] = temp;
}

void scale_row(float *row, int num_columns, float scalar) {
    for (int i = 0; i < num_columns; i++) {
        row[i] *= scalar;
    }
}

void add_scaled_row(float *src_row, float *dst_row, int num_columns, float scalar) {
    for (int i = 0; i < num_columns; i++) {
        dst_row[i] += scalar * src_row[i];
    }
}

int solve_linear_equations(float **coefficients, float *constants, int num_equations, int num_variables, float *solution) {
    // Augmenting the coefficient matrix with constants
    float **augmented_matrix = (float **)malloc(num_equations * sizeof(float *));
    for (int i = 0; i < num_equations; i++) {
        augmented_matrix[i] = (float *)malloc((num_variables + 1) * sizeof(float));
        for (int j = 0; j < num_variables; j++) {
            augmented_matrix[i][j] = coefficients[i][j];
        }
        augmented_matrix[i][num_variables] = constants[i];
    }

    // Gaussian elimination to get row-reduced echelon form (RREF)
    int num_pivots = 0;
    for (int pivot_row = 0; pivot_row < num_equations; pivot_row++) {
        // Find pivot column
        int pivot_column = num_pivots;
        while (pivot_column < num_variables && fabs(augmented_matrix[pivot_row][pivot_column]) < EPSILO) {
            pivot_column++;
        }
        if (pivot_column == num_variables) {
            // All remaining entries in this row are zero
            if (fabs(augmented_matrix[pivot_row][num_variables]) > EPSILO) {
                // Inconsistent system: constant term is nonzero in a row of zeros
                return 0;  // No solution
            } else {
                // Redundant row: can be ignored
                continue;
            }
        }

        // Swap rows to bring pivot to diagonal
        if (pivot_row != num_pivots) {
            swap_rows(augmented_matrix, pivot_row, num_pivots, num_variables + 1);
        }

        // Scale pivot row so pivot = 1
        float pivot_value = augmented_matrix[num_pivots][pivot_column];
        scale_row(augmented_matrix[num_pivots], num_variables + 1, 1.0 / pivot_value);

        // Eliminate other entries in pivot column
        for (int row = 0; row < num_equations; row++) {
            if (row != num_pivots) {
                float scale_factor = -augmented_matrix[row][pivot_column];
                add_scaled_row(augmented_matrix[num_pivots], augmented_matrix[row], num_variables + 1, scale_factor);
            }
        }

        num_pivots++;
    }

    // Check for rows with no pivot columns
    for (int i = num_pivots; i < num_equations; i++) {
        int has_nonzero_constant = 0;
        for (int j = 0; j < num_variables; j++) {
            if (fabs(augmented_matrix[i][j]) > EPSILO) {
                // Nonzero coefficient in a column with no pivot
                if (fabs(augmented_matrix[i][num_variables]) > EPSILO) {
                    // Nonzero constant term
                    return 0;  // No solution
                } else {
                    has_nonzero_constant = 1;
                    break;
                }
            }
        }
        if (!has_nonzero_constant) {
            // All coefficients are zero in a row with no pivot
            return 2;  // Infinite solutions
        }
    }

    // Extract solutions if unique solution
    if (num_pivots == num_variables) {
        for (int i = 0; i < num_variables; i++) {
            solution[i] = augmented_matrix[i][num_variables];
        }
    }

    // Free dynamically allocated memory
    for (int i = 0; i < num_equations; i++) {
        free(augmented_matrix[i]);
    }
    free(augmented_matrix);

    return num_pivots == num_variables ? 1 : 2;  // Return solution type
}


//For tic tac toe


char square[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

int checkwin() {
    if (square[1] == square[2] && square[2] == square[3])
        return 1;
    else if (square[4] == square[5] && square[5] == square[6])
        return 1;
    else if (square[7] == square[8] && square[8] == square[9])
        return 1;
    else if (square[1] == square[4] && square[4] == square[7])
        return 1;
    else if (square[2] == square[5] && square[5] == square[8])
        return 1;
    else if (square[3] == square[6] && square[6] == square[9])
        return 1;
    else if (square[1] == square[5] && square[5] == square[9])
        return 1;
    else if (square[3] == square[5] && square[5] == square[7])
        return 1;
    else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&
             square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7]
             != '7' && square[8] != '8' && square[9] != '9')
        return 0;
    else
        return  -1;
}

void board() {
    system("clear");
    printf("\n\n\t\t\t\tTic Tac Toe\n\n");
    printf("\t\t\tPlayer 1 (X)  -  Player 2 (O)\n\n\n");
    printf("\t\t\t\t  %c  |  %c  |  %c \n", square[1], square[2], square[3]);
    printf("\t\t\t\t_____|_____|_____\n");
    printf("\t\t\t\t     |     |     \n");
    printf("\t\t\t\t  %c  |  %c  |  %c \n", square[4], square[5], square[6]);
    printf("\t\t\t\t_____|_____|_____\n");
    printf("\t\t\t\t     |     |     \n");
    printf("\t\t\t\t  %c  |  %c  |  %c \n", square[7], square[8], square[9]);
    printf("\t\t\t\t     |     |     \n\n");
}


int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, 1) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is running...\n");

    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrLen);
    if (clientSocket < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    printf("Client connected\n");
    printf("Enter 1 to play Tic Tac Toe\n");
    printf("Enter 2 to play Snake and Ladder\n");
    printf("Enter 3 to solve a system of linear equations\n");
    printf("Enter 4 to solve Polynomial Equation\n");
    printf("Enter 5 to play Maze Escape Game\n");
    printf("Enter 6 to solve Differential Equation\n");

    int n=1024;
    while(n!=0){
        recv(clientSocket, &n, sizeof(n), 0);
        if(n==1){
            playGame1(clientSocket);
        }
        else if(n==2){
            playGame2(clientSocket);
        }
        else if(n==3){
            playGame3(clientSocket);
        }
        else if(n==4){
            playGame4(clientSocket);
        }
        else if(n==5){
            playGame5(clientSocket);
        }
        else if(n==6){
            playGame6(clientSocket);
        }
    }
    close(clientSocket);
    close(serverSocket);

    return 0;
}



void playGame1(int clientSocket) {
    int i, choice;
    char mark;
   char result[200];

    do {
        recv(clientSocket, &choice, sizeof(choice), 0);
        mark = 'X'; // Player 1's turn

        if (choice >= 1 && choice <= 9 && square[choice] == '0' + choice) {
            square[choice] = mark;
        } else {
            printf("Invalid move\n");
        }

        i = checkwin();
        if (i == 1) {
             sprintf(result,"player 1 win!\n");
              send(clientSocket, &i, sizeof(i), 0);
             send(clientSocket, result, sizeof(result), 0);
             break;
        } else if (i == 0) {
            sprintf(result,"Game Over - Draw!");
             send(clientSocket, &i, sizeof(i), 0);
            send(clientSocket, result, sizeof(result), 0);
            break;
        }

        send(clientSocket, &i, sizeof(i), 0);
        send(clientSocket, square, sizeof(square), 0);
      
        mark = 'O'; // Player 2's turn
        printf("Waiting for Player 2's move...\n");
        recv(clientSocket, &choice, sizeof(choice), 0);

        if (choice >= 1 && choice <= 9 && square[choice] == '0' + choice) {
            square[choice] = mark;
        } else {
            printf("Invalid move\n");
        }

        i = checkwin();
        if (i == 1) {
            sprintf(result,"Player 2 wins!\n");
             send(clientSocket, &i, sizeof(i), 0);
            send(clientSocket, result, sizeof(result), 0); 
            break;
        } else if (i == 0) {
            sprintf(result,"Game Over - Draw!\n");
             send(clientSocket, &i, sizeof(i), 0);
             send(clientSocket, result, sizeof(result), 0);
            break;
        }

              send(clientSocket, &i, sizeof(i), 0);

        send(clientSocket, square, sizeof(square), 0);
    } while (i ==  -1);
}

void playGame2(int clientSocket){
    srand(time(0));
    int currentPlayer = 1;
    int won = 0, player1 = 0, player2 = 0, count = 1, newSquare;

    printf("Snake and Ladder Server is running...\n");
    printf("Client connected\n");

    char name1[15], name2[15];
    char name1_initial, name2_initial;

    recv(clientSocket, name1, sizeof(name1), 0);
    recv(clientSocket, name2, sizeof(name2), 0);

    name1_initial = name1[0]; // Get the initial of name1
    name2_initial = name2[0]; // Get the initial of name2

    while (!won) {
        count++;

        char rollRequest[1024];
        recv(clientSocket, rollRequest, sizeof(rollRequest), 0);

        int roll = rollDie();

        send(clientSocket, &roll, sizeof(roll), 0);

        printf("Roll result sent to client: %d\n", roll);

        char message[256] = "", pos[100] = "";
        int newPosition;
        if (currentPlayer == 1) {
            newPosition = movePlayer(player1, roll, currentPlayer, &newSquare);
            sprintf(pos, "%s is now at square %d.\n\n", name1, abs(newPosition));
            if (newPosition < 0) {
                sprintf(message, "%s climbed a ladder from %d to %d!\n", name1, abs(player1+roll), abs(newPosition));
            } else if (newPosition > 0 && (player1+roll)!= newPosition) {
                sprintf(message, "%s got bitten by a snake from %d to %d!\n", name1, abs(player1+roll), abs(newPosition));
            }
            player1 = abs(newPosition);
            if (player1 == 100) {
                printf("%s wins!\n", name1);
                won = 1;
            }
        } else {
            newPosition = movePlayer(player2, roll, currentPlayer, &newSquare);
            sprintf(pos, "%s is now at square %d.\n", name2, abs(newPosition));
            if (newPosition < 0) {
                sprintf(message, "%s climbed a ladder from %d to %d!\n", name2, abs(player2+roll), abs(newPosition));
            } else if (newPosition > 0 &&(player2+roll)!= newPosition) {
                sprintf(message, "%s got bitten by a snake from %d to %d!\n", name2, abs(player2+roll), abs(newPosition));
            }
            player2 = abs(newPosition);
            if (player2 == 100) {
                printf("%s wins!\n", name2);
                won = 1;
            }
        }

        sendBoard(clientSocket, player1, player2, message, pos, name1_initial, name2_initial);

        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
}

void playGame3(int clientSocket){
    // Receive number of equations and variables from client
    int num_equations, num_variables;
    recv(clientSocket, &num_equations, sizeof(num_equations), 0);
    recv(clientSocket, &num_variables, sizeof(num_variables), 0);

    // Receive coefficients of equations from client
    float **coefficients = (float **)malloc(num_equations * sizeof(float *));
    for (int i = 0; i < num_equations; i++) {
        coefficients[i] = (float *)malloc(num_variables * sizeof(float));
        recv(clientSocket, coefficients[i], num_variables * sizeof(float), 0);
    }

    // Receive constants of equations from client
    float *constants = (float *)malloc(num_equations * sizeof(float));
    recv(clientSocket, constants, num_equations * sizeof(float), 0);

    // Allocate memory for solution
    float *solution = (float *)malloc(num_variables * sizeof(float));

    // Solve linear equations
    int solution_type=solve_linear_equations(coefficients, constants, num_equations, num_variables, solution);

    // Send solution back to client
    send(clientSocket, &solution_type,sizeof(int), 0);
    send(clientSocket, solution, num_variables * sizeof(float), 0);

    // Free dynamically allocated memory
    for (int i = 0; i < num_equations; i++) {
        free(coefficients[i]);
    }
    free(coefficients);
    free(constants);
    free(solution);
}

void playGame4(int clientSocket){
    // Receive degree and coefficients from client
    int degree;
    recv(clientSocket, &degree, sizeof(degree), 0);

    double *coefficients = (double *)malloc((degree + 1) * sizeof(double));
    recv(clientSocket, coefficients, (degree + 1) * sizeof(double), 0);

    // Receive a, b, and initial_guess from client
    double a, b, initial_guess;
    recv(clientSocket, &a, sizeof(a), 0);
    recv(clientSocket, &b, sizeof(b), 0);
    recv(clientSocket, &initial_guess, sizeof(initial_guess), 0);

    // Calculate roots using various methods
    double roots[degree];
    roots[0] = bisection(equation, a, b, degree, coefficients);
    roots[1] = newtons_method(equation, initial_guess, degree, coefficients);
    roots[2] = secant_method(equation, initial_guess, initial_guess + 1.0, degree, coefficients);

    // Send roots back to client
    send(clientSocket, roots, degree * sizeof(double), 0);

    // Free memory
    free(coefficients);
}

void playGame5(int clientSocket){
    int k;
    recv(clientSocket,&k,sizeof(k),0);
}

void playGame6(int clientSocket) {
    while (1) {
        char function[SIZE] = "";
        double x0, y0, x_final, h;

        recv(clientSocket, function, SIZE, 0);
        recv(clientSocket, &x0, sizeof(double), 0);
        recv(clientSocket, &y0, sizeof(double), 0);
        recv(clientSocket, &x_final, sizeof(double), 0);
        recv(clientSocket, &h, sizeof(double), 0);

        double y_final = rk(function, x0, y0, x_final, h);

        char response[1024];
        sprintf(response, "Solution at x = %.4lf: y = %.4lf\n", x_final, y_final);

        // Send response to client
        send(clientSocket, response, strlen(response), 0);
    }

}

