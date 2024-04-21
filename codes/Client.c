#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<math.h>
#include<ctype.h>
#include<time.h>
#include<stdbool.h>

// Function to display the Tic Tac Toe board
void displayBoard(char square[]) {
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

//for equation solver
#define PORT 8080

//for Differential Equation Solver

#define SIZE 100



//for Escape Maze Game


// Function to display game rules
void rule(char m[],int n) {
    if(m[0] == '0' && m[1]=='\0') {
        printf("GAME RULES\n");
        printf("You will be placed at 1st position and you have to go to the last position in each level.\n");
        printf("If you lose before level 5 then you will have to restart the game from level 1.\n");
        printf("If you lose at level 5 or after level 5 then you will get to restart the game from level 5.\n");
        printf("Enter s to move Down\n");
        printf("Enter a to move Left\n");
        printf("Enter w to move Up\n");
        printf("Enter d to move Right\n");
    }
}

// Function to initialize the game board
void makeboard(char a[16][16], int l) {
    // Initialize all cells with '.'
    for(int i = 0; i < 16; i++)
        for(int j = 0; j < 16; j++)
            a[i][j] = '.';
    
    // Place Player 'P' at (0, 0) and End 'E' at (15, 15)
    a[0][0] = 'P';
    a[15][15] = 'E';
    
    srand(time(NULL)); // Initialize random seed
    int c = 0;

    // Place obstacles 'X' in <= 10*l random positions
    while(c < 10 * l) {
        int x = rand() % 16;
        int y = rand() % 16;
        if((x != 0 || y != 0) && (x != 15 || y != 15)) {
            a[x][y] = 'X';
            c++;
        }
    }
    c = 0;

    // Place traps '*' in <= 2*l random positions
    while(c < 2 * l) {
        int x = rand() % 16;
        int y = rand() % 16;
        if((x != 0 || y != 0) && (x != 15 || y != 15) && a[x][y] != 'X') {
            a[x][y] = '*';
            c++;
        }
    }
}

// Function to print the game board
void printboard(char a[16][16]) {
    for(int i = 0; i < 16; i++) {
        for(int j = 0; j < 16; j++) {
            printf("%c ", a[i][j]);
        }
        printf("\n");
    }
}

// Structure to store player position
typedef struct position {
    int x;
    int y;
}sop;

// Function to check if there is a valid path to win the game
bool isValidPath(char a[16][16], sop s) {
    bool visited[16][16] = {false};
    int queue[256][2];
    int front = 0, rear = 0;

    // Add starting position to the queue
    queue[rear][0] = s.x;
    queue[rear][1] = s.y;
    rear++;

    while (front != rear) {
        int x = queue[front][0];
        int y = queue[front][1];
        front++;

        // Check if the current position is the end point
        if (x == 15 && y == 15) {
            return true;
        }

        // Check adjacent positions
        if (x > 0 && !visited[x - 1][y] && a[x - 1][y] != 'X' && a[x - 1][y] != '*') {
            queue[rear][0] = x - 1;
            queue[rear][1] = y;
            rear++;
            visited[x - 1][y] = true;
        }
        if (x < 15 && !visited[x + 1][y] && a[x + 1][y] != 'X' && a[x + 1][y] != '*') {
            queue[rear][0] = x + 1;
            queue[rear][1] = y;
            rear++;
            visited[x + 1][y] = true;
        }
        if (y > 0 && !visited[x][y - 1] && a[x][y - 1] != 'X' && a[x][y - 1] != '*') {
            queue[rear][0] = x;
            queue[rear][1] = y - 1;
            rear++;
            visited[x][y - 1] = true;
        }
        if (y < 15 && !visited[x][y + 1] && a[x][y + 1] != 'X' && a[x][y + 1] != '*') {
            queue[rear][0] = x;
            queue[rear][1] = y + 1;
            rear++;
            visited[x][y + 1] = true;
        }
    }

    return false;
}


// Function to regenerate the game board
void regenerateBoard(char a[16][16], int l, sop *s) {
    makeboard(a, l);
    s->x = 0;
    s->y = 0;
}

// Function to handle player movement
void movement(char a[16][16], char m[],int n, sop *s) {
    int u = s->x;
    int v = s->y;
    if((m[0] == 'a' || m[0]=='A') && m[1]=='\0')
        s->y = s->y - 1;
    else if((m[0] == 'd' || m[0] =='D') && m[1]=='\0')
        s->y = s->y + 1;
    else if((m[0] == 's' || m[0] =='S') && m[1]=='\0')
        s->x = s->x + 1;
    else if((m[0] == 'w' || m[0] =='W') && m[1]=='\0')
        s->x = s->x - 1;

    // Check boundaries and obstacles
    if(s->x < 0 || s->x >= 16 || s->y < 0 || s->y >= 16) {
        s->x = u;
        s->y = v;
    }
    // If position is valid, update player position
    else if(s->x >= 0 && s->x < 16 && s->y > -1 && s->y < 16 && a[s->x][s->y] != 'X' && a[s->x][s->y] != '*') {
        a[u][v] = '.';
        a[s->x][s->y] = 'P';
    }
    // If player reaches the end point
    else if(s->x == 15 && s->y == 15) {
        a[u][v] = '.';
        a[s->x][s->y] = 'P';
    }
    // If player encounters obstacle
    else if(a[s->x][s->y] == 'X') {
        s->x = u;
        s->y = v;
        printf("You are not allowed to use this position\n");
    }
}

//main function
int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to Server\n");

    
        int n;
        printf("Enter 1 to play Tic Tac Toe\n");
        printf("Enter 2 to play Snake and Ladder\n");
        printf("Enter 3 to solve a system of linear equations\n");
        printf("Enter 4 to solve Polynomial Equation\n");
        printf("Enter 5 to play Maze Escape Game\n");
        printf("Enter 6 to solve Differential Equation\n");
        scanf("%d",&n);
        send(clientSocket, &n, sizeof(n), 0);
        if(n==1){
            printf("Connected to Tic Tac Toe Server\n");
            displayBoard("0123456789");
        
            int i,choice;
            char result[200];
            char square[10];
            do {
                
                printf("Enter your move (1-9): ");
                scanf(" %d", &choice);
                if (choice < 1 && choice > 9 && square[choice] != '0' + choice){
                    printf("Invalid move\n");
                }
                else{
                send(clientSocket, &choice, sizeof(choice), 0);
                recv(clientSocket, &i, sizeof(i), 0);
                if(i==0||i==1){
                    recv(clientSocket, result, sizeof(result), 0);
                    printf("%s",result);
                    break;
                }else{
                
                recv(clientSocket, square, sizeof(square), 0);
                displayBoard(square);
                }
                }
                
            } while (i!=0||i!=1);
        }

        else if(n==2){
            printf("Connected to Snake and Ladder Server\n");

            char name1[15], name2[15];

            printf("Enter Player 1 Name: ");
            scanf(" %s", name1);

            printf("Enter Player 2 Name: ");
            scanf(" %s", name2);

            send(clientSocket, name1, sizeof(name1), 0);
            send(clientSocket, name2, sizeof(name2), 0);

            while (1) {
                printf("Press Enter to roll the dice: ");
                getchar(); // Clear input buffer
                getchar(); // Wait for Enter key press

                send(clientSocket, "Roll", sizeof("Roll"), 0);

                int roll;
                recv(clientSocket, &roll, sizeof(roll), 0);

                printf("You rolled: %d\n", roll);

                char board[1024];
                recv(clientSocket, board, sizeof(board), 0);

                printf(" %s", board);
            }

        }

        else if(n==3){
            // Input number of equations and variables
            int num_equations, num_variables;
            printf("Enter the number of equations: ");
            scanf("%d", &num_equations);
            printf("Enter the number of variables: ");
            scanf("%d", &num_variables);

            // Send number of equations and variables to server
            send(clientSocket, &num_equations, sizeof(num_equations), 0);
            send(clientSocket, &num_variables, sizeof(num_variables), 0);

            // Input coefficients of equations
            float **coefficients = (float **)malloc(num_equations * sizeof(float *));
            for (int i = 0; i < num_equations; i++) {
                coefficients[i] = (float *)malloc(num_variables * sizeof(float));
                printf("Enter coefficients of equation %d: ", i + 1);
                for (int j = 0; j < num_variables; j++) {
                    scanf("%f", &coefficients[i][j]);
                }
                // Send coefficients to server
                send(clientSocket, coefficients[i], num_variables * sizeof(float), 0);
            }

            // Input constants of equations
            float *constants = (float *)malloc(num_equations * sizeof(float));
            printf("Enter constants of equations:\n");
            for (int i = 0; i < num_equations; i++) {
                printf("Constant for equation %d: ", i + 1);
                scanf("%f", &constants[i]);
            }
            // Send constants to server
            send(clientSocket, constants, num_equations * sizeof(float), 0);

            // Receive solution from server
            int solution_type;
            recv(clientSocket, &solution_type, sizeof(int), 0);
            float *solution = (float *)malloc(num_variables * sizeof(float));
            recv(clientSocket, solution, num_variables * sizeof(float), 0);

            // Print the result
            if (solution_type == 1) {
                printf("The system of linear equations has a unique solution:\n");
                for (int i = 0; i < num_variables; i++) {
                    printf("x%d = %.2f\n", i + 1, solution[i]);
                }
            } else if (solution_type == 2) {
                printf("The system of linear equations has infinite solutions.\n");
            } else {
                printf("The system of linear equations has no solution.\n");
            }

            // Free dynamically allocated memory
            for (int i = 0; i < num_equations; i++) {
                free(coefficients[i]);
            }
            free(coefficients);
            free(constants);
            free(solution);
        }

        else if(n==4){
            // Input degree of the polynomial equation
            int degree;
            printf("Enter the degree of the polynomial equation: ");
            scanf("%d", &degree);

            // Send degree to server
            send(clientSocket, &degree, sizeof(degree), 0);

            // Dynamically allocate memory for coefficients
            double *coefficients = (double *)malloc((degree + 1) * sizeof(double));

            // Input coefficients from user
            printf("Enter the coefficients of the polynomial equation (from highest degree to constant term):\n");
            for (int i = degree; i >= 0; i--) {
                printf("Coefficient of x^%d: ", i);
                scanf("%lf", &coefficients[degree - i]);
            }

            // Send coefficients to server
            send(clientSocket, coefficients, (degree + 1) * sizeof(double), 0);

            // Input initial guess, a, and b
            double initial_guess, a, b;
            printf("Enter initial guess: ");
            scanf("%lf", &initial_guess);
            printf("Enter initial interval [a, b]: ");
            scanf("%lf%lf", &a, &b);

            // Send initial guess, a, and b to server
            send(clientSocket, &initial_guess, sizeof(initial_guess), 0);
            send(clientSocket, &a, sizeof(a), 0);
            send(clientSocket, &b, sizeof(b), 0);

            // Receive roots from server
            double roots[degree];
            recv(clientSocket, roots, degree * sizeof(double), 0);

            // Display roots
            printf("Roots of the polynomial equation:\n");
            for (int i = 0; i < degree; i++) {
                printf("Root %d: %lf\n", i+1, roots[i]);
            }

            // Free dynamically allocated memory
            free(coefficients);
        }
        else if(n==5){
            int k;
            int l = 1;
            char m[100],bd[16][16];
            printf("For rules of the game press 0\n");
            makeboard(bd, l);
            sop step;
            step.x = 0;
            step.y = 0;
            sop *s;
            s = &step;
            
            // Main game loop
            do {
                if (!isValidPath(bd, *s)) {
                    regenerateBoard(bd, l, s);
                    continue;
                }
                printboard(bd);
                printf("Take your step : ");
                scanf(" %s", m);
                // Input validation loop
                do {
                    if(m[0] == '0' && m[1]=='\0') {
                        rule(m,100);
                        scanf(" %s", m);
                    }
                    else if((m[0] != 's' && m[0] != 'a' && m[0] != 'd' && m[0] != 'w' && m[0] != 'S' && m[0] != 'A' && m[0] != 'D' && m[0] != 'W') || m[1]!='\0') {
                        printf("Wrong Input! type 0 to know rules OR Retake your step\n");
                        scanf(" %s", m);
                    }
                } while(m[0] != 's' && m[0] != 'a' && m[0] != 'd' && m[0] != 'w' && m[0] != 'S' && m[0] != 'A' && m[0] != 'D' && m[0] != 'W' && m[1]!='\0');
                // Handle player movement
                movement(bd, m,100, s);

                // Check if player hits a trap and handle game over condition
                if(bd[s->x][s->y] == '*' && l < 5) {
                    printf("You have lost the game \n Write R to start again from level 1 OR write Q if you are a QUITTER : ");
                    char i[100];
                    scanf("  %s", i);
                    if((i[0] == 'R' || i[0] == 'r')&& i[1]=='\0') {
                        printf("Go WARRIOR\n");
                        makeboard(bd, 1);
                        s->x = 0;
                        s->y = 0;
                        continue;
                    }
                    else {
                        printf("Jazakallah Khair\n");
                        k=1;
                        send(clientSocket,&k,sizeof(k),0);
                        break;
                    }
                }
                else if(bd[s->x][s->y] == '*' && l >= 5) {
                    printf("You have lost the game \n Write R to start again from level 5 OR write Q if you are a QUITTER : ");
                    char i[100];
                    scanf("  %s", i);
                    if((i[0] == 'R' || i[0] == 'r')&& i[1]=='\0') {
                        printf("Go WARRIOR\n");
                        makeboard(bd, 5);
                        s->x = 0;
                        s->y = 0;
                        continue;
                    }
                    else {
                        printf("Jazakallah Khair\n");
                        k=1;
                        send(clientSocket,&k,sizeof(k),0);
                        break;
                    }
                }
                // Check if player reaches the end and handle level completion
                if(s->x == 15 && s->y == 15 && l < 7) {
                    printf("Congratulations warrior you did it!\n");
                    printf("Now let's go to next level and show who is the boss\n");
                    printf("Write Y to go to next level or write anything I really don't like QUITTER : ");
                    char i[100];
                    scanf(" %s", i);
                    if((i[0] == 'Y'|| i[0] == 'y') && i[1]=='\0') {
                        l++;
                        makeboard(bd, l);
                        s->x = 0;
                        s->y = 0;
                        continue;
                    }
                    else {
                        printf("Jazakallah Khair!\n");
                        k=1;
                        send(clientSocket,&k,sizeof(k),0);
                        break;
                    }
                }
            } while(bd[15][15] != 'P' && bd[s->x][s->y] != '*' && l < 8);
            if(bd[15][15]=='P' && l==7){
                printf("HURRAY! You've conquered all the levels! Your determination and intelligence shine through brightly. Keep up the fantastic work, and stay tuned for the next challenge. You're a true superstar!\n");
            }
            k=1;
            send(clientSocket,&k,sizeof(k),0);
        }
        else if(n==6){
             // Input equation and parameters
            char inputstr[SIZE];
            printf("Enter the differential equation in the form dy/dx = f(x, y): ");
            fgets(inputstr, SIZE, stdin);
            inputstr[strcspn(inputstr, "\n")] = '\0';  // Remove trailing newline if present
            while (getchar() != '\n');

            char function[SIZE] = "";
            sscanf(inputstr, "dy/dx=%[^=]", function);

            double x0, y0, x_final, h;
            printf("Enter initial x-value (x0): ");
            scanf("%lf", &x0);
            printf("Enter initial y-value (y0): ");
            scanf("%lf", &y0);

            printf("Enter final x-value (x_final): ");
            scanf("%lf", &x_final);
            printf("Enter step size (h): ");
            scanf("%lf", &h);

            if (h <= 0) {
                printf("Error: Step size (h) must be positive.\n");
                return 1;
            }

            // Send equation and parameters to server
            send(clientSocket, function, SIZE, 0);
            send(clientSocket, &x0, sizeof(double), 0);
            send(clientSocket, &y0, sizeof(double), 0);
            send(clientSocket, &x_final, sizeof(double), 0);
            send(clientSocket, &h, sizeof(double), 0);

            // Receive solution from server
            // Receive solution from server
            char response[1024];
            recv(clientSocket, response, sizeof(response), 0);

            // Display solution
            printf("%s\n", response);
        }



    close(clientSocket);

    return 0;
}






