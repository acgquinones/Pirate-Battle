/*

File:         Game.cpp
Author:       Ara Carmel Quinones
Date:         10/8/2020
Section:      CMSC 202 Section 10
Description:  

"... you will need to read in two text files – one of pirates and one about types of pirate ships. The Game class will manage the two arrays of pirates and ships. Both lists can be assumed to be static and you have been given two constants to count through the files as needed.

The player (or user) starts with a pirate and a type of ship. Then they can search for treasure. When they encounter an enemy, if they think they can beat the enemy, they can choose to battle with the enemy pirate or try to flee. If they have a faster ship, they will be able to sneak away but if they are too slow, the enemy ship will attack them.
"
*/

#include "Game.h"

/* Name: Game() Default Constructor
// Desc - Builds a new game by:
// 1. Displaying the Game Title
// 2. Loads all ships and their information into m_ships
// 3. Loads all pirates and their information into m_pirates
// Preconditions - None
// Postconditions - m_allPirates and m_ships are populated
*/
Game::Game(){  //Default Constructor
  //functional calls to print Title, to loadship, and load pirates
  GameTitle();
  LoadShips();
  LoadPirates();
}
// Name: LoadShips
// Desc - Loads each type of ship into m_ships from file (Do not use EOF)
// Preconditions - Requires file with valid ship data
// Postconditions - m_ships is populated with ship structs
void Game::LoadShips(){
  ifstream inputStream; //holds streams of data from file
  string type;          //the type/name of ship
  string cannon;        //num of cannons of the ship
  string toughness;     //num of toughness of the ship
  string speed;         //num of speed of the ship
  string desc;          //description of the ship

  //opens the ships file
  inputStream.open(PROJ2_SHIPS);

  //assigns data from the file to its respective variables
  for (int i = 0; i < MAX_SHIPS; i++){

    getline(inputStream, type, ',');
    getline(inputStream, cannon, ',');
    getline(inputStream, toughness, ',');
    getline(inputStream, speed, ',');
    getline(inputStream, desc);
    m_ships[i] = Ship(type, stoi(cannon), stoi(toughness), stoi(speed), desc);

  }
  inputStream.close();
  cout << MAX_SHIPS << " ships loaded." << endl;
}
// Name: LoadPirates
// Desc - Loads each pirate into m_allPirates from file (Do not use EOF)
// Preconditions - Requires file with valid pirate data
// Postconditions - m_allPirates is populated with pirate objects
void Game::LoadPirates(){
  ifstream inputStream;  //holds stream of data from pirate file
  string name;           //name of the pirate
  string rating;         //rating of the pirate
  string origin;         //origin of the pirate
  string desc;           //description of the pirate

  //opens PROJ2_PIRATES file
  inputStream.open(PROJ2_PIRATES);
  //assigns data from the file to its respective variables 
  for (int i = 0; i < MAX_PIRATES; i++){
    getline(inputStream, name, ',');
    getline(inputStream, rating, ',');
    getline(inputStream, origin, ',');
    getline(inputStream, desc);
    m_allPirates[i] = Pirate(name, stoi(rating), origin, desc);
  }
  //close the file
  inputStream.close();
  cout << MAX_PIRATES << " pirates loaded." << endl;
}
// Name: StartGame()
// Desc - Does the following:
//        1. Randomly assigns a pirate from the list as the user's pirate (m_myPirate)
//        2. Randomly assigns a ship to the user's pirate (updates m_myPirate's ship)
//        3. Manages the game itself including win conditions continually
//         calling the main menu
// Preconditions - Player (Pirate) is placed in game
// Postconditions - Continually checks to see if player has entered 4 (retires)
void Game::StartGame(){
  int randNumPirate = 0;    //random integer for index to find pirate
  int randNumShip = 0;      //random integer for indes to find ship
  string myRandNamePirate;  //the name of the enemy pirate
  string myRandNameShip;    //the name of the enemy ship

  //get a random number to use as index to find the pirate
  randNumPirate = rand() % MAX_PIRATES;

  //set the pirate's data to pirate object m_myPirate
  m_myPirate = m_allPirates[randNumPirate];

  //gets the name of the pirate
  myRandNamePirate = m_myPirate.GetName();

  //get a random number to use as index to find a ship
  randNumShip = rand() % MAX_SHIPS;

  //set the ship as the pirate's current ship
  m_myPirate.SetCurShip(m_ships[randNumShip]);
  
  cout << "Congratulations! " << myRandNamePirate << " is now available to plunder!" << endl;
  cout << myRandNamePirate << " is aboard a " << m_ships[randNumShip].m_type << endl;
  MainMenu();
}
// Name: MainMenu()
// Desc - Displays and manages menu.
// Preconditions - Player has a Pirate
// Postconditions - Returns number including exit
int Game::MainMenu(){
  int choice = 0; //num integer of user choice
  
  //use while loop to keep the program running 'till user wants to retire
  while (choice != 4) {

    //do while loop to print menu
    do{
      cout << "What would you like to do?" << endl;
      cout << '\t' << "1. Search for Treasure" << endl;
      cout << '\t' << "2. Repair Ship" << endl;
      cout << '\t' << "3. See Score" << endl;
      cout << '\t' << "4. Retire" << endl;
      cin >> choice;

    //prints out menu again if user enters integers less than 1 and greater than 4
    }while(choice < 1 || choice > 4);

    //switch loop to call functions/do specific tasks
    switch (choice){
    case 1:
      SearchTreasure();
      break;
    case 2:
      m_myPirate.RepairShip();
      break;
    case 3:
      m_myPirate.DisplayScore();
      break;
    case 4:
      m_myPirate.DisplayScore();
      cout << m_myPirate.GetName() << " sails off into retirement!" << endl;
      cout << "Thanks for playing Pirates!" << endl;
      break;
    default:
      cout << "Invalid Input." << endl;
    }
  }
  return 0;
  
}
// Name: SearchTreasure()
// Desc - Attempts to search for ships and allows user to either battle or attempt to flee
// Preconditions - Pirates loaded
// Postconditions - Identifies enemy pirate to fight
void Game::SearchTreasure(){
  int choice = 0; //num integer of user's choice

  //Pirate object to contain enemy's pirate data
  Pirate randPirate = m_allPirates[rand() % MAX_PIRATES];

  //Ship object to contain enemy's ship data
  Ship randShip = m_ships[rand() % MAX_SHIPS];
  
  cout << "You scan the horizon for prospective targets..."
       << "Off in the distance, you see "<< randPirate.GetName() << " on a "
       << randShip.m_type << "!" << endl;

  //do while loop to print our menu
  do{
    cout << "What would you like to do?" << endl;
    cout << '\t' << "1. Attack " <<  randPirate.GetName() << endl;
    cout << '\t' << "2. Attempt to Flee from " << randPirate.GetName() << endl;
    cin >> choice;
    //reprint menu if user enter invalid integers
  }while((choice < 1) || (choice > 2));

  //call battle function if user chooses to battle
  if (choice == 1){
    m_myPirate.Battle(randPirate, randShip);
  //call flee function if user chooses to flee 
  }else{  
    m_myPirate.Flee(randPirate, randShip);
  }
}
