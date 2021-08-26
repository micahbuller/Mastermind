#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <string>
using namespace std;

//The colors of pegs in this game are Abbreviated to the first letter of the colors: Teal, Orange, Brown, Green, Yellow, Red, Magenta, Carmel.

int randomNumber = 0;
int numOfGuesses = 0;
int maxGuesses = 12;
int numOfColors = 8;
int numOfPegs = 4;
int allowDuplicates = 0;

// This function is used to take in the random number chosen and return a letter that coorisponds to the number.
char returnLetter(int numberIn){
  switch(numberIn){
    case 0 : return 't'; //t is for Teal
      break;
    case 1 : return 'o'; //o is for Orange
      break;
    case 2 : return 'b'; //b is for Brown
      break;
    case 3 : return 'g'; //g is for Green
      break;
    case 4 : return 'y'; //y is for Yellow
      break;
    case 5 : return 'r'; //r is for Red
      break;
    case 6 : return 'm'; //m is for Magenta
      break;
    case 7 : return 'c'; //c is for Carmel
      break;
    default: cout << "We encountered a problem when converting your computers soltuion numbers to characters" << endl;
    return 'n';
  }
}

// This function is used to take in the random number chosen and return a letter that coorisponds to the number.
int returnNumber(char letterIn){
  switch(letterIn){
    case 't' : return 0; //t is for Teal
      break;
    case 'o' : return 1; //o is for Orange
      break;
    case 'b' : return 2; //b is for Brown
      break;
    case 'g' : return 3; //g is for Green
      break;
    case 'y' : return 4; //y is for Yellow
      break;
    case 'r' : return 5; //r is for Red
      break;
    case 'm' : return 6; //m is for Magenta
      break;
    case 'c' : return 7; //c is for Carmel
      break;
    default: cout << "We encountered a problem when converting your letters to numbers" << endl;
    return 'n';
  }
}


void returnRandomSolution(int numOfPegs, char * solution){
  //This function recieves the number of pegs that the user has chose to play with as well as whether we can have duplicate colors and will return an array of pegs.

  srand (time(NULL)); //Initializing random seed

  if(allowDuplicates){
    int count = 0;
    int tempInt = 10;
    while (count != numOfPegs){
      tempInt = (rand() % 8);
      solution[count] = returnLetter(tempInt);
      count++;
    }
    
  }else{
    //NEED TO FILL THIS IN NO NOT ALLOW DUPLICATE COLORS
    //What you can do is to check the char array for duplicates and if they exist just run the random generator again till it succeeds. Use a while loop.
    
    int tempInt = 10;
    int isDuplicate = 1;

    while (isDuplicate == 1){
      int count = 0;
      int howManyColors[8] = {0};

      while (count != numOfPegs){
        
        tempInt = (rand() % 8);
        howManyColors[tempInt]+=1;
        solution[count] = returnLetter(tempInt);
        count++;
      }


      // check through to see if there areDuplicates
      count = 0;
    
      while (count != 8){
        
        if(howManyColors[count] > 1){
          isDuplicate = 1;
          break;
        }
        else{
          isDuplicate = 0;
        }
        count++;
      }
      
    }
  }
}

//The function will return 0 if you didnt win and 1 if you did win.
int checkGuess(char * guess, char * solution, char * response){
  
  int count = 0;
  int numCorrect = 0;
  int correctArray[numOfPegs];
  int colorsInIndicies[8] = {0}; //Each indicies will represent how many colors there are of each peg.
  int responseCount = 0;
  int returnIndicies;

  // Count how many colors have multiples.
  while(count != numOfPegs){
    returnIndicies = returnNumber(solution[count]);
    colorsInIndicies[returnIndicies]+=1;
    count++;
  }
  

  //we will use this array to mark which indicies are correct in the users guess.
  count = 0;
  while(count != numOfPegs){
    correctArray[count] = 0;
    response[count] = '-';
    count++;
  }

  count = 0;
  //Check to see if nothing matched
  while(count != numOfPegs){
    if(guess[count] != solution[count]){
      response[count] = '-';
    }
    count++;
  }

  count = 0;
  // Check to see how many were correct
  while(count != numOfPegs){
    if(guess[count] == solution[count]){
      correctArray[count] = 1;
      response[numCorrect] = 'X';
      // take away from how many colors have been guessed.
      returnIndicies = returnNumber(solution[count]);
      colorsInIndicies[returnIndicies]-=1;

      numCorrect++;
      responseCount++;
    }
    count++;
  }

  if(numCorrect == numOfPegs){
    cout << "*****************************************\n";
    cout << "************ WOW, You won! ! ************\n";
    cout << "*****************************************\n";
    return 1;
  }

  //Check to see if the color is there but in the wrong spot.
  count = 0;
  int innerCount = 0;
  while(count != numOfPegs){
    if(correctArray[count] != 1){
        while(innerCount != numOfPegs){
          if(correctArray[innerCount] != 1){
            //Now we check to see if the pairs are a match.
            if(guess[count] == solution[innerCount]){
              returnIndicies = returnNumber(solution[innerCount]);
              if(colorsInIndicies[returnIndicies] != 0){
                correctArray[innerCount] = 3;
                response[responseCount] = '0';
                responseCount++;
                colorsInIndicies[returnIndicies]-=1;
              } 
            }
          }
          innerCount++;
        }
    }
    count++;
    innerCount = 0;
  }
  
  return 0;
}

int userGuesses(){
  char solution[numOfPegs]; //This will be used to hold the solution.
  char guess[numOfPegs]; //This will be used to hold the users guesses.
  char response[numOfPegs];
  // didWin 0 means user did not win, a 1 will mean that they won!
  int didWin = 0;

  //NEED TO FILL! ASK USER FOR THE SIZE OF THEIR GUESS.

  // this returns solution array of size num of pegs
  returnRandomSolution(numOfPegs, solution);

/* For testing purposes only to see the solution!*/
cout << endl << endl << "The solution is:";
  int count = 0;
    while (count != numOfPegs){
      cout << solution[count];
      count++;
    }
    cout << endl << endl;
/**/
    cout << "*****************************************\n";
    cout << "******** Please enter your guess ********\n";
    cout << "*****************************************\n\n";
    cout << "1: Make sure that your guess is lowercase\n";
    cout << "2: Make sure that your guess has no spaces\n";
    cout << "3: Your colors to choose from are:\n";
    cout << "   Teal, Orange, Brown, Green, Yellow,\n";
    cout << "   Red, Magenta, and Carmel.\n\n";
    cout << "*****************************************\n";
    cout << "*************** Good Luck ***************\n";
    cout << "*****************************************\n";

    

  while (numOfGuesses != maxGuesses){
    
    cin >> guess;

    didWin = checkGuess(guess, solution, response);

    //checking to see if the user guessed correctly
    if(didWin == 1){
      return 0; // Just go back to main and end!
    }

    int count = 0;
    while (count != numOfPegs){
      
      cout << response[count];
      count++;
    }
    cout << endl;

    numOfGuesses++;
  }

  cout << endl << endl << "You lost!  :`(";
  return 0;
}


int computerGuesses(){
  int didWin = 0;
  int numOfGuesses = 0;
  char computerGuess[numOfPegs];
  char response[numOfPegs];

  char userSolution[numOfPegs];
    cout << "*****************************************\n";
    cout << "****** Please enter your Solution *******\n";
    cout << "*****************************************\n\n";
    cout << "1: Solution must be lowercase\n";
    cout << "2: Solution must have no spaces\n";
    cout << "3: Your colors to choose from are:\n";
    cout << "   Teal, Orange, Brown, Green, Yellow,\n";
    cout << "   Red, Magenta, and Carmel.\n\n";
    cout << "*****************************************\n";
    cout << "*************** Good Luck ***************\n";
    cout << "*****************************************\n\n";
    cout << "         Please enter a solution.\n";
    cout << " Your solution should not be longer than\n"; 
    cout << "            "<< numOfPegs << " chatacters.\n\n"; 

  cin >> userSolution;

  while (numOfGuesses != maxGuesses){

    //getting the first guess
  returnRandomSolution(numOfPegs, computerGuess);

  int count = 0;
    cout << "*****************************************\n";
    cout << "********  Computers " << numOfGuesses + 1 << " guess  ********\n";
    cout << "*****************************************\n\n";
  
    while (count != numOfPegs){
      
      cout << computerGuess[count];
      count++;
    }
    cout << endl;

    didWin = checkGuess(computerGuess, userSolution, response);

    //checking to see if the user guessed correctly
    if(didWin == 1){
      return 0; // Just go back to main and end!
    }

    count = 0;
    while (count != numOfPegs){
      
      cout << response[count];
      count++;
    }
    cout << endl;

    numOfGuesses++;
    sleep(1);
  }

  cout << endl << endl << "You lost!  :`(";


  return 0;
}


int main() {

  int whoPlays = 0; // User guesses is 0, computer Guesses is 1

    cout << "*****************************************\n";
    cout << "*****************************************\n\n";
    cout << "           Welcome to Mastermind\n";
    cout << "             by: Micah Buller\n\n";
    cout << "*****************************************\n";
    cout << "*****************************************\n\n\n";
    cout << "1: Would you like to choose guess?\n";
    cout << "2: Or, the computer to guess?\n";

    //Check user input
    cout << "Enter a 1 or a 2.\n\n";
      cin >> whoPlays;
    while(whoPlays < 1 || whoPlays > 2){
      cout << "INVALID! Enter a 1 or a 2 please.\n\n";
      cin >> whoPlays;
    }

    cout << "*****************************************\n";
    cout << "*****************************************\n";
    cout << "How many colors would you like to play with?\n";
    cout << "       The more colors you play with\n";
    cout << "           the harder it is!\n";

    //Check user input
    do{
      cout << "Enter a numer 4 through 8.\n\n";
      cin >> numOfPegs;
    }while((numOfPegs > 8) || (numOfPegs < 4));

    cout << "*****************************************\n";
    cout << "*****************************************\n";
    cout << "Would you like to play with duplicate colors\n";
    cout << "             in the solution?\n";
    cout << "               Its harder!\n";

    //Check user input
    do{
      cout << "Enter a numer 0 for no, 1 for yes.\n\n";
      cin >> allowDuplicates;
    }while((allowDuplicates > 1) || (allowDuplicates < 0));

    int gameEnd = 0;
    //going into either user guessing or computer guessing.
    if(whoPlays == 1){
      
      gameEnd = userGuesses();
    }else{
      //INSERT CODE FOR COMPUTER TO PLAY
      
      gameEnd = computerGuesses();
      
    }

  return 0;
}