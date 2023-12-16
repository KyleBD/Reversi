#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void printBoard (char board[][26], int n);

void switchColours(char userArray[][26], int row, int col, char colour,int  deltaRow,int deltaCol, int boardDimensions);

void CheckUserMove(char userArray[][26], bool * IsAValidMove, int boardDimension, int row, int col, char colour, char computerColour);

bool CheckOneColour(char userArray[][26], int boardDimension);

void printOrigionalBoard(char board[][26], int n);

bool positionInBounds(int n, int row, int col);

bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);

void findWinner(char userArray[][26], int boardDimension);

//This function will calculate the max amount of tiles flipped in all of the given directions to find what move will give the max.
int maxTilesFlipped(char userArray[][26], int row, int col, int boardDimension, int deltaRow, int deltaCol, char colour);

void computerMove(char userArray[][26], char computerColour, int boardDimension);

int computerScore(char userArray[][26], int boardDimension, char compouterColour);

int userScore(char userArray[][26], int boardDimension, char userColour);

void userTurn(char userArray[][26], bool * IsAValidMove, int boardDimension, char userColour, char computerColour, char Playing);

void computerTurn(char userArray[][26], int boardDimension, char computerColour);

char DetermineTurn(char userArray[][26], int boardDimension, bool* IsAValidMove, char computerColour, char userColour, char currentPlayer);

int makeMove(char board[][26], int n, char turn, int *row, int *col);

bool fullBoard(char userArray[][26], int n);

//This program will check if there are any possible moves left for the player. It will use similar structure
//to the code that printed possible moves,  but this times it will reutrn bool.
bool possibleMove(char userArray[][26], int boardDimension, char colour);

bool endGame(char userArray[][26], int boardDimension, bool* IsAValidMove);



int main (void){
int boardDimensions;
char computerColour;
char userColour;
char Playing = 'B';
bool IsAValidMove = true;
int scoreOfUser;
int scoreOfComputer;

printf("Enter the board dimension: ");
scanf("%d", &boardDimensions);


  char userArray[26][26];
  for(int i = 0; i<boardDimensions; i++){
    for(int j = 0; j<boardDimensions; j++){
        userArray[i][j]= 'U';
    }
  }
  userArray[boardDimensions/2][boardDimensions/2] = 'W';
  userArray[boardDimensions/2][(boardDimensions/2)-1] = 'B';
  userArray[(boardDimensions/2)-1][boardDimensions/2] = 'B';
  userArray[(boardDimensions/2)-1][(boardDimensions/2)-1] = 'W';
    printf("Computer plays (B/W): ");
    scanf(" %c", &computerColour);
    printBoard(userArray, boardDimensions);

    if(computerColour == 'W'){
        userColour = 'B';
    }
    if(computerColour == 'B'){
        userColour = 'W';
    }
    while(endGame(userArray, boardDimensions, &IsAValidMove) == false){
        Playing = DetermineTurn(userArray, boardDimensions, &IsAValidMove, computerColour, userColour, Playing);
    }
    if(IsAValidMove == true){
        findWinner(userArray, boardDimensions);
    }
    return 0;
}

bool CheckOneColour(char userArray[][26], int boardDimension){
  int numBlack = 0;
  int numWhite = 0;
  int numU = 0;
  for(int i = 0; i<boardDimension; i++){
    for(int j = 0; j< boardDimension; j++){
      if(userArray[i][j] == 'B'){
        numBlack++;
      }
      if(userArray[i][j] == 'W'){
        numWhite++;
      }
      if(userArray[i][j] == 'U'){
        numU++;
      }
    }
  }
  if(numBlack == 0 || numWhite == 0 || numU == 0){
    return false;
  }
  else{
    return true;
  }
}


//We need to write a function that uses the others to check if the move used is allowed.
void CheckUserMove(char userArray[][26], bool * IsAValidMove, int boardDimension, int row, int col,char colour, char computerColour){
  if(!positionInBounds(boardDimension, row, col) || !CheckOneColour(userArray, boardDimension)){
    printf("Invalid move.\n");
    return;
  }
  bool ValidMove = false;
  //First we need to make sure that it in bounds.
  if(positionInBounds(boardDimension, row, col)){
    for(int i = 0; i<boardDimension; i++){
    for(int j = 0; j<boardDimension; j++){
      if(userArray[i][j] == 'U'){
        //North
        if((checkLegalInDirection(userArray, boardDimension , i, j, colour,0,1)) && i == row && j==col){
            userArray[i][j] = colour;

            switchColours(userArray, row, col, colour, 0, 1, boardDimension);
            ValidMove = true;
          
        }
        //EAST
        if((checkLegalInDirection(userArray, boardDimension , i, j, colour,1,0)) && i == row && j==col){
            userArray[i][j] = colour;

            switchColours(userArray, row, col, colour, 1, 0, boardDimension);
            ValidMove = true;          

        }
        //South
        if((checkLegalInDirection(userArray, boardDimension , i, j, colour,0,-1)) && i == row && j==col){
            userArray[i][j] = colour;

            switchColours(userArray, row, col, colour, 0, -1, boardDimension);
            ValidMove = true;           
        }
        //West
       if((checkLegalInDirection(userArray, boardDimension , i, j, colour,-1,0)) && i == row && j==col){
            userArray[i][j] = colour;

            switchColours(userArray, row, col, colour, -1, 0, boardDimension);
            ValidMove = true;           
        }
        //North East
        if((checkLegalInDirection(userArray, boardDimension , i, j, colour,1,1)) && i == row && j==col){
            userArray[i][j] = colour;

            switchColours(userArray, row, col, colour, 1, 1, boardDimension);
            ValidMove = true;         
        }
        //South East
        if((checkLegalInDirection(userArray, boardDimension , i, j, colour,1,-1)) && i == row && j==col){

            userArray[i][j] = colour;

            switchColours(userArray,  row, col, colour, 1, -1, boardDimension);
            ValidMove = true;            
        }
        //South West
        if((checkLegalInDirection(userArray, boardDimension , i, j, colour,-1,-1)) && i == row && j==col){
            userArray[i][j] = colour;

            switchColours(userArray,  row, col, colour, -1, -1, boardDimension);
            ValidMove = true;            
        }
        //North West
        if((checkLegalInDirection(userArray, boardDimension , i, j, colour,-1,1)) && i == row && j==col){
            userArray[i][j] = colour;

            switchColours(userArray, row, col, colour, -1, 1, boardDimension);
            ValidMove = true;          
        }                                                        
      }
    }
  }
}
if(ValidMove == true){
    printBoard(userArray, boardDimension);
}
else{
  *IsAValidMove = false;
  printf("Invalid move.\n");
  printf("%c player wins.", computerColour);
}
}
// We not need to write a function that will find the possible moves and give them to the player.

void printBoard (char board[26][26], int n){
  printf("  ");
  for(int character = 0; character<n; character++){
    printf("%c", 'a'+character);
  }
  printf("\n");
  for(int i = 0; i<n; i++){
    printf("%c ", 'a'+i);
    for(int j = 0; j<n; j++){
    printf("%c", board[i][j]);
    }
    printf("\n");
  }
}
bool positionInBounds(int n, int row, int col){
  if((row >= 0) && (row<n) && (col >= 0) && (col<n)){
    return true;
  }
  else{
    return false;
  }
}


bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol){
int index = 1;
  while(((board[row + (deltaRow * index)][col + deltaCol*index]) != 'U') && ((board[deltaRow*index +row][col+deltaCol*index]) != colour) && (positionInBounds(n,deltaRow*index +row,deltaCol*index+col))){
  
    index++;
    if((positionInBounds(n,deltaRow*index +row,deltaCol*index+col)) && (board[deltaRow*index +row][deltaCol*index+col] ==colour)){
    return true;
    }
    if(!positionInBounds(n, row+(deltaRow*index), col+(deltaCol+index) && board[deltaRow*index +row] != colour && board[deltaRow*index +row] != 'U')){    
      if(board[row + (deltaRow * index)][col + (deltaCol * index)] == colour && positionInBounds(n,deltaRow*index +row,deltaCol*index+col)){
          return true;
        }
    }
    }
    return false;
  }


void switchColours(char userArray[][26], int row, int col, char colour,int  deltaRow,int deltaCol, int boardDimensions){
userArray[row][col] = colour;
int index = 1;
char opposite;

if(colour == 'B'){
  opposite = 'W';
}
if(colour == 'W'){
  opposite = 'B';
}
while(userArray[row + index*deltaRow][col +index*deltaCol] == opposite && positionInBounds(boardDimensions, row+ index*deltaRow, col + index*deltaCol)){
  userArray[row + index*deltaRow][col +index*deltaCol] = colour;
  index++;
}
}

int maxTilesFlipped(char userArray[][26], int row, int col, int boardDimension, int deltaRow, int deltaCol, char colour){
  int maxVal = 0;
  int index = 1;
    while(userArray[row + (index*deltaRow)][col + (index*deltaCol)] != colour && positionInBounds(boardDimension, row + (index*deltaRow), col +(col*deltaCol))){
      maxVal++;
      index++;
    }
    return maxVal;
}

/*This functions will use very similar structure to what was used in my find possible moves function
because we will want it to check through all the moves just like the possible moves function
*/
void computerMove(char userArray[][26], char computerColour, int boardDimension){
    int tilesFliped = 0;
    int maxValArray[26][26];

  for(int i= 0; i<boardDimension; i++){
    for(int j = 0; j<boardDimension; j++){
      if(userArray[i][j] == 'U' && positionInBounds(boardDimension, i, j)){

        if((checkLegalInDirection(userArray, boardDimension , i, j, computerColour,0,1)) ){
            tilesFliped = tilesFliped + maxTilesFlipped(userArray, i, j, boardDimension, 0, 1, computerColour);
        }
        //EAST
        if((checkLegalInDirection(userArray, boardDimension , i, j, computerColour,1,0)) ){
          tilesFliped = tilesFliped + maxTilesFlipped(userArray, i, j, boardDimension, 1, 0, computerColour);

        }
        //South
        if((checkLegalInDirection(userArray, boardDimension , i, j, computerColour,0,-1)) ){
           tilesFliped = tilesFliped + maxTilesFlipped(userArray, i, j, boardDimension, 0, -1, computerColour);
        }
        //West
       if((checkLegalInDirection(userArray, boardDimension , i, j, computerColour,-1,0)) ){
          tilesFliped = tilesFliped + maxTilesFlipped(userArray, i, j, boardDimension, -1, 0, computerColour);
        }
        //North East
        if((checkLegalInDirection(userArray, boardDimension , i, j, computerColour,1,1)) ){
            tilesFliped = tilesFliped + maxTilesFlipped(userArray, i, j, boardDimension, 1, 1, computerColour);
        }
        //South East
        if((checkLegalInDirection(userArray, boardDimension , i, j, computerColour,1,-1)) ){
            tilesFliped = tilesFliped + maxTilesFlipped(userArray, i, j, boardDimension, 1, -1, computerColour);
        }
        //South West
        if((checkLegalInDirection(userArray, boardDimension , i, j, computerColour,-1,-1)) ){
            tilesFliped = tilesFliped + maxTilesFlipped(userArray, i, j, boardDimension, -1, -1, computerColour);
        }
        //North West
        if((checkLegalInDirection(userArray, boardDimension , i, j, computerColour,-1,1)) ){
            tilesFliped = tilesFliped + maxTilesFlipped(userArray, i, j, boardDimension, -1, 1, computerColour);
        }
        
      }
      //This will give us a new array that will store all of the values of the amount of 
      //tiles flipped depending on the placement.
      maxValArray[i][j] = tilesFliped;
      tilesFliped = 0;
    }
  }
  /* Now I will go through the newly created array to find what row and column values are where the maximum amount of tiles
  are stored.*/
  int maxRowVal = 0;
  int maxColVal = 0;
  int highScore = 0;
  for(int k = 0; k<boardDimension; k++){
    for(int z= 0; z<boardDimension; z++){
        if(maxValArray[k][z] > highScore){
            highScore = maxValArray[k][z];
            maxRowVal = k;
            maxColVal = z;
            
        }
    }
  }
    //NORTH
    if((checkLegalInDirection(userArray, boardDimension , maxRowVal, maxColVal, computerColour,0,1)) ){
        switchColours(userArray, maxRowVal, maxColVal, computerColour, 0, 1, boardDimension);
    }
    //EAST
    if((checkLegalInDirection(userArray, boardDimension , maxRowVal, maxColVal, computerColour,1,0)) ){
        switchColours(userArray, maxRowVal, maxColVal, computerColour, 1, 0, boardDimension);
    }
    //South
    if((checkLegalInDirection(userArray, boardDimension , maxRowVal, maxColVal, computerColour,0,-1)) ){
        switchColours(userArray, maxRowVal, maxColVal, computerColour, 0, -1, boardDimension);
    }
    //West
    if((checkLegalInDirection(userArray, boardDimension , maxRowVal, maxColVal, computerColour,-1,0)) ){
        switchColours(userArray, maxRowVal, maxColVal, computerColour, -1, 0, boardDimension);
    }
    //North East
    if((checkLegalInDirection(userArray, boardDimension , maxRowVal, maxColVal, computerColour,1,1)) ){
        switchColours(userArray, maxRowVal, maxColVal, computerColour, 1, 1, boardDimension);
    }
    //South East
    if((checkLegalInDirection(userArray, boardDimension , maxRowVal, maxColVal, computerColour,1,-1)) ){
        switchColours(userArray, maxRowVal, maxColVal, computerColour, 1, -1, boardDimension);
        }
    //South West
    if((checkLegalInDirection(userArray, boardDimension , maxRowVal, maxColVal, computerColour,-1,-1)) ){
        switchColours(userArray, maxRowVal, maxColVal, computerColour, -1, -1, boardDimension);
    }
    //North West
    if((checkLegalInDirection(userArray, boardDimension , maxRowVal, maxColVal, computerColour,-1,1)) ){
        switchColours(userArray, maxRowVal, maxColVal, computerColour, -1, 1, boardDimension);
    }
    printf("Computer places %c at %c%c.\n", computerColour, maxRowVal+97, maxColVal+97);
    printBoard(userArray, boardDimension);
}

void findWinner(char userArray[][26], int boardDimension){
    int BlackTotal = 0;
    int WhiteTotal = 0;
    for(int i = 0; i<boardDimension; i++){
        for (int j = 0; j <boardDimension; j++){
            if(userArray[i][j] == 'B'){
                BlackTotal++;
            }
            if(userArray[i][j] == 'W'){
                WhiteTotal++;
            }
        }
    }
    if(BlackTotal > WhiteTotal){
        printf("B player wins.\n");
    }
    if(WhiteTotal > BlackTotal){
        printf("W player wins.\n");
    }
    if(WhiteTotal == BlackTotal){
        printf("Draw!");
    }
}

//These functions will calculate how many of the given colour there are to compare them at the 
//End of the game.
int computerScore(char userArray[][26], int boardDimension, char compouterColour){
    int compScore = 0;
    for(int i = 0; i< boardDimension; i++){
        for(int j = 0; j< boardDimension; j++){
            if(userArray[i][j] == compouterColour){
                compScore++;
            }
        }
    }
    return compScore;
}
int userScore(char userArray[][26], int boardDimension, char userColour){
    int useScore = 0;
    for(int i = 0; i< boardDimension; i++){
        for(int j = 0; j< boardDimension; j++){
            if(userArray[i][j] == userColour){
                useScore++;
            }
        }
    }
    return useScore;
}
void userTurn(char userArray[][26], bool * IsAValidMove, int boardDimension, char userColour, char computerColour, char Playing){
char userRow, userCol;
int rowTemp;
int colTemp;
if(possibleMove(userArray, boardDimension, userColour )){
    printf("Enter move for colour %c (RowCol): ", userColour);
    scanf(" %c%c", &userRow, &userCol);
    rowTemp = userRow - 'a';
    colTemp = userCol - 'a';
    CheckUserMove(userArray, IsAValidMove, boardDimension, rowTemp, colTemp, Playing, computerColour);
    return;
}
else{
    printf("%c player has no valid move.\n", userColour);
    return;
}

}

bool possibleMove(char userArray[][26], int boardDimension, char colour){
for(int i = 0; i<boardDimension; i++){
    for(int j = 0; j<boardDimension; j++){
      if(userArray[i][j] == 'U'){
        //North
        if((checkLegalInDirection(userArray, boardDimension , i, j, colour,0,1))){
            return true;
          
        }
        //EAST
        else if((checkLegalInDirection(userArray, boardDimension , i, j, colour,1,0))){
            return true;
        }
        //South
        else if((checkLegalInDirection(userArray,boardDimension, i, j, colour,0,-1))){
            return true;
          
        }
        //West
       else if((checkLegalInDirection(userArray,boardDimension, i, j, colour,-1,0))){
            return true;
        }
        //North East
        else if((checkLegalInDirection(userArray,boardDimension, i, j, colour,1,1))){
            return true;
          
        }
        //South East
        else if((checkLegalInDirection(userArray,boardDimension, i, j, colour,1,-1))){

            return true;
        }
        //South West
        else if((checkLegalInDirection(userArray,boardDimension, i, j, colour,-1,-1))){
            return true;
        }
        //North West
        else if((checkLegalInDirection(userArray,boardDimension, i, j, colour,-1,1))){
            return true;
        }                                                        
      }
    }
  }
return false;
}

void computerTurn(char userArray[][26], int boardDimension, char computerColour){
    if(possibleMove(userArray, boardDimension, computerColour)){
        computerMove(userArray, computerColour, boardDimension);
    }
    else{
        printf("%c player has no valid move.\n", computerColour);
    }

}
char DetermineTurn(char userArray[][26], int boardDimension, bool* IsAValidMove, char computerColour, char userColour, char Playing){
    if(computerColour == Playing){
        computerTurn(userArray, boardDimension, computerColour);
        Playing = userColour;
    }
    else if(userColour == Playing){
        userTurn(userArray, IsAValidMove, boardDimension, userColour, computerColour, Playing);
        Playing = computerColour;
    }
    return Playing;
}
bool endGame(char userArray[][26], int boardDimension, bool* IsAValidMove){
    if(*IsAValidMove == false){
        return true;
    }
    for(int i = 0; i<boardDimension; i++){
        for(int j = 0; j< boardDimension; j++){
            if(userArray[i][j] == 'U'){
                return false;
            }
        }
    }
    return true;
}


/* This function includes
- positionInBounds
- checkLegalInDirection
- maxTilesFlipped
TODO: ** Append these into Examify **
*/
bool possibleMove(char userArray[][26], int boardDimension, char colour){
for(int i = 0; i<boardDimension; i++){
    for(int j = 0; j<boardDimension; j++){
      if(userArray[i][j] == 'U'){
        //North
        if((checkLegalInDirection(userArray, boardDimension , i, j, colour,0,1))){
            return true;
          
        }
        //EAST
        else if((checkLegalInDirection(userArray, boardDimension , i, j, colour,1,0))){
            return true;
        }
        //South
        else if((checkLegalInDirection(userArray,boardDimension, i, j, colour,0,-1))){
            return true;
          
        }
        //West
       else if((checkLegalInDirection(userArray,boardDimension, i, j, colour,-1,0))){
            return true;
        }
        //North East
        else if((checkLegalInDirection(userArray,boardDimension, i, j, colour,1,1))){
            return true;
          
        }
        //South East
        else if((checkLegalInDirection(userArray,boardDimension, i, j, colour,1,-1))){

            return true;
        }
        //South West
        else if((checkLegalInDirection(userArray,boardDimension, i, j, colour,-1,-1))){
            return true;
        }
        //North West
        else if((checkLegalInDirection(userArray,boardDimension, i, j, colour,-1,1))){
            return true;
        }                                                        
      }
    }
  }
return false;
}

void computerTurn(char userArray[][26], int boardDimension, char computerColour){
    if(possibleMove(userArray, boardDimension, computerColour)){
        computerMove(userArray, computerColour, boardDimension);
    }
    else{
        printf("%c player has no valid move.\n", computerColour);
    }

}
char DetermineTurn(char userArray[][26], int boardDimension, bool* IsAValidMove, char computerColour, char userColour, char Playing){
    if(computerColour == Playing){
        computerTurn(userArray, boardDimension, computerColour);
        Playing = userColour;
    }
    else if(userColour == Playing){
        userTurn(userArray, IsAValidMove, boardDimension, userColour, computerColour, Playing);
        Playing = computerColour;
    }
    return Playing;
}
bool endGame(char userArray[][26], int boardDimension, bool* IsAValidMove){
    if(*IsAValidMove == false){
        return true;
    }
    for(int i = 0; i<boardDimension; i++){
        for(int j = 0; j< boardDimension; j++){
            if(userArray[i][j] == 'U'){
                return false;
            }
        }
    }
    return true;
}


/* This function includes
- positionInBounds
- checkLegalInDirection
- maxTilesFlipped
TODO: ** Append these into Examify **
*/
int makeMove(char board[26][26], int n, char turn, int *row, int *col) {

    int tilesFliped = 0;
    int maxValArray[26][26];
    if(!possibleMove(board, n, turn)){
    return 0;
    }
    if(fullBoard(board, n)){
    return 0;
    }
  if(possibleMove(board, n, turn) || !fullBoard(board, n)){
  for(int i= 0; i<n; i++){
    for(int j = 0; j<n; j++){
      if(board[i][j] == 'U' && positionInBounds(n, i, j)){

        //NORTH
        if((checkLegalInDirection(board, n , i, j, turn,0,1)) ){
            tilesFliped = tilesFliped + maxTilesFlipped(board, i, j, n, 0, 1, turn);
              if( (i== 0 || i== n-1) && ( j==0 || j == n-1)){
              tilesFliped += 100;
              }
              if( ((i ==0 || i==7) && (j==1 || j==6)) || ((i ==1 || i==6) && (j==0 || j==7)) || ((i ==1 || i==6) && (j==1 || j==6)) ){
              tilesFliped -= 1;
              }
              if( ( (i == 0 || i==7) && (j > 1 && j<6) ) ||  ( (j == 0 || j==7) && (i > 1 && i<6) )){
              tilesFliped += 10;
              }

        }
        //EAST
        if((checkLegalInDirection(board, n , i, j, turn,1,0)) ){
          tilesFliped = tilesFliped + maxTilesFlipped(board, i, j, n, 1, 0, turn);
               if( (i== 0 || i== n-1) && ( j==0 || j == n-1)){
              tilesFliped += 100;
              }
              if( ((i ==0 || i==7) && (j==1 || j==6)) || ((i ==1 || i==6) && (j==0 || j==7)) || ((i ==1 || i==6) && (j==1 || j==6)) ){
              tilesFliped -= 1;
              }
              if( ( (i == 0 || i==7) && (j > 1 && j<6) ) ||  ( (j == 0 || j==7) && (i > 1 && i<6) )){
              tilesFliped += 10;
              }
        }
        //South
        if((checkLegalInDirection(board, n , i, j, turn,0,-1)) ){
           tilesFliped = tilesFliped + maxTilesFlipped(board, i, j, n, 0, -1, turn) ;
              if( (i== 0 || i== n-1) && ( j==0 || j == n-1)){
              tilesFliped += 100;
              }
              if( ((i ==0 || i==7) && (j==1 || j==6)) || ((i ==1 || i==6) && (j==0 || j==7)) || ((i ==1 || i==6) && (j==1 || j==6)) ){
              tilesFliped -= 1;
              }              
              if( ( (i == 0 || i==7) && (j > 1 && j<6) ) ||  ( (j == 0 || j==7) && (i > 1 && i<6) )){
              tilesFliped += 10;
              }
        }
        //West
       if((checkLegalInDirection(board, n , i, j, turn,-1,0)) ){
          tilesFliped = tilesFliped + maxTilesFlipped(board, i, j, n, -1, 0, turn) ;
              if( (i== 0 || i== n-1) && ( j==0 || j == n-1)){
              tilesFliped += 100;
              }
              if( ((i ==0 || i==7) && (j==1 || j==6)) || ((i ==1 || i==6) && (j==0 || j==7)) || ((i ==1 || i==6) && (j==1 || j==6)) ){
              tilesFliped -= 1;
              }
              if( ( (i == 0 || i==7) && (j > 1 && j<6) ) ||  ( (j == 0 || j==7) && (i > 1 && i<6) )){
              tilesFliped += 10;
              }              
        }
        //North East
        if((checkLegalInDirection(board, n , i, j, turn,1,1)) ){
            tilesFliped = tilesFliped + maxTilesFlipped(board, i, j, n, 1, 1, turn) ;
              if( (i== 0 || i== n-1) && ( j==0 || j == n-1)){
              tilesFliped += 100;
              }
              if( ((i ==0 || i==7) && (j==1 || j==6)) || ((i ==1 || i==6) && (j==0 || j==7)) || ((i ==1 || i==6) && (j==1 || j==6)) ){
              tilesFliped -= 1;
              }
              if( ( (i == 0 || i==7) && (j > 1 && j<6) ) ||  ( (j == 0 || j==7) && (i > 1 && i<6) )){
              tilesFliped += 10;
              }              
        }
        //South East
        if((checkLegalInDirection(board, n , i, j, turn,1,-1)) ){
            tilesFliped = tilesFliped + maxTilesFlipped(board, i, j, n, 1, -1, turn) ;
              if( (i== 0 || i== n-1) && ( j==0 || j == n-1)){
              tilesFliped += 100;
              }
              if( ((i ==0 || i==7) && (j==1 || j==6)) || ((i ==1 || i==6) && (j==0 || j==7)) || ((i ==1 || i==6) && (j==1 || j==6)) ){
              tilesFliped -= 1;
              } 
              if( ( (i == 0 || i==7) && (j > 1 && j<6) ) ||  ( (j == 0 || j==7) && (i > 1 && i<6) )){
              tilesFliped += 10;
              }                           
        }
        //South West
        if((checkLegalInDirection(board, n , i, j, turn,-1,-1)) ){
            tilesFliped = tilesFliped + maxTilesFlipped(board, i, j, n, -1, -1, turn) ;
              if( (i== 0 || i== n-1) && ( j==0 || j == n-1)){
              tilesFliped += 100;
              }
               if( ((i ==0 || i==7) && (j==1 || j==6)) || ((i ==1 || i==6) && (j==0 || j==7)) || ((i ==1 || i==6) && (j==1 || j==6)) ){
              tilesFliped -= 1;
              } 
              if( ( (i == 0 || i==7) && (j > 1 && j<6) ) ||  ( (j == 0 || j==7) && (i > 1 && i<6) )){
              tilesFliped += 10;
              }                         
        }

        //North West
        if((checkLegalInDirection(board, n , i, j, turn,-1,1)) ){
            tilesFliped = tilesFliped + maxTilesFlipped(board, i, j, n, -1, 1, turn) ;
              if( (i== 0 || i== n-1) && ( j==0 || j == n-1)){
              tilesFliped += 100;
              }
              if( ((i ==0 || i==7) && (j==1 || j==6)) || ((i ==1 || i==6) && (j==0 || j==7)) || ((i ==1 || i==6) && (j==1 || j==6)) ){
              tilesFliped -= 1;
              } 
              if( ( (i == 0 || i==7) && (j > 1 && j<6) ) ||  ( (j == 0 || j==7) && (i > 1 && i<6) )){
              tilesFliped += 10;
              }                           
              
        }
        
      }

      //This will give us a new array that will store all of the values of the amount of 
      //tiles flipped depending on the placement.

      maxValArray[i][j] = tilesFliped;
      tilesFliped = 0;
    }
  }
  /* This part of the function will put values on different sqaures. For example the corners will be weighted higher
  and the edges will be second heighest, and the places surrounding the edges will be lowest.
  */
  /*

  /* Now I will go through the newly created array to find what row and column values are where the maximum amount of tiles
  are stored.*/
  int highScore = 0;
  int highRow = 0;
  int highCol = 0;
  
  for(int k = 0; k<n; k++){
    for(int z= 0; z<n; z++){
        if(maxValArray[k][z] > highScore){
            highScore = maxValArray[k][z];
            highRow = k;
            highCol = z;
            
        }
    }
  }
  *row = highRow;
  *col = highCol;
  return 0;
  }
return 0;
}
bool fullBoard(char userArray[][26], int n){
  for(int i =0; i<n; i++){
    for(int j = 0; j<n; j++){
      if(userArray[i][j] == 'U'){
        return false;
      }
    }
  }
  return true;
}
