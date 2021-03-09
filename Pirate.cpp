/*

File:     Pirate.cpp
Author:   Ara Carmel Quinones
Date:     10/8/2020
Section:  CMSC 202 Section 10
Description:

"... you will need to read in two text files – one of pirates a\
nd one about types of pirate ships. The Game class will manage \
the two arrays of pirates and ships. Both lists can be assumed \
to be static and you have been given two constants to count thr\
ough the files as needed.                                       
                                                                
The player (or user) starts with a pirate and a type of ship. T\
hen they can search for treasure. When they encounter an enemy,\
 if they think they can beat the enemy, they can choose to batt\
le with the enemy pirate or try to flee. If they have a faster \
ship, they will be able to sneak away but if they are too slow,\
 the enemy ship will attack them.                               
"

*/


#include "Pirate.h"

// Name: Pirate() - Default Constructor
// Desc: Used to build a new Pirate
// Preconditions - Requires default values
// Postconditions - Creates a new Pirate
Pirate::Pirate(){
}
// Name: Pirate(name, rating, years, origin, desc) - Overloaded Constructor
// Desc: Used to build a new Pirate
// Preconditions - Requires new values
// Postconditions - Creates a new Pirate
Pirate::Pirate(string name, int rating, string origin, string desc){
  m_pirateName = name; //Name of Pirate
  m_pirateRating = rating; //Rating of Pirate
  m_pirateOrigin = origin; //Country of Origin of Pirate
  m_pirateDesc = desc; //Description of Pirate
  m_pirateCargo = 0; //Tons of cargo earned
  m_pirateDays = 0; //Days elapsed

}
// Name: GetName()
// Desc - Getter for Pirate name
// Preconditions - Pirate exists
// Postconditions - Returns the name of the Pirate
string Pirate::GetName(){
  return m_pirateName;
}
// Name: GetRating()
// Desc - Gets the Pirate's rating
// Preconditions - Pirate exists
// Postconditions - Returns rating of Pirate
int Pirate::GetRating(){
  return m_pirateRating;
}
// Name: SetRating()
// Desc - Sets the Pirate's rating
// Preconditions - Pirate exists
// Postconditions - Updates the Pirate's rating
void Pirate::SetRating(int rating){
  m_pirateRating = rating;
}
// Name: GetOrigin()
// Desc - Describes the country of origin of the Pirate
// Preconditions - Pirate exists
// Postconditions - Returns the country of origin on the Pirate
string Pirate::GetOrigin(){
  return m_pirateOrigin;
}
// Name: GetDesc()
// Desc - Describes the Pirate
// Preconditions - Pirate exists
// Postconditions - Returns the description of the Pirate
string Pirate::GetDesc(){
  return m_pirateDesc;
}
// Name: SetCurShip (ship)
// Desc - Sets the pirates' type of ship
// Preconditions - Pirate exists
// Postconditions - Updates m_curShip

void Pirate::SetCurShip(Ship curShip){
  m_curShip = curShip;
}
// Name: CalcTreasure
// Desc - Calculates treasure and added to m_pirateCargo
// Calculated as enemy ship's cannon, max toughness, and speed divided by 3
// Preconditions - Pirate exists and battle has concluded
// Postconditions - Updates total cargo
void Pirate::CalcTreasure(Ship enemyShip){
  int treasure = 0;

  //adds enemy's cannon, toughness,speed and becomes treasure for my pirate 
  treasure = (enemyShip.m_cannon + enemyShip.m_toughness + enemyShip.m_speed)/3;
  m_pirateCargo = treasure;
  
}
// Name: Battle(pirate, ship)
// Desc - Battles user pirate vs computer's enemy pirate
//        If user's ship has m_curToughness of 0 then must repair before battle
//        Two outcomes possible - User pirate wins = CalcTreasure and maybe damaged ship
//        Computer pirate wins = damaged ship and pirate's m_cargo halved
//        User always attacks enemy pirate first
//        Pirate rating (higher = better) is percentage liklihood of hit
//        (rating 95 = 95% hit per cannon)
//        When either user curToughness < 1 or enemyShip curToughness < 1 battle is over
// Preconditions - Enemy pirate found
// Postconditions - Either user pirate wins or enemy pirate wins
void Pirate::Battle(Pirate enemyPirate, Ship enemyShip){
  int myShots = 0;
  int enemyShots = 0;

  //increments pirate days by 1 when enters Battle
  m_pirateDays++;
  
  cout << "A naval battle of the ages commences between " << m_pirateName
       << " and " << enemyPirate.GetName() << endl;
  cout << endl;
  
  //pirate cannot go on battle if curToughness is 0 and below, must repair ship first
  if (m_curShip.m_curToughness < 1)
    {
      RepairShip();
    }
  
  else
    {
      //while loop ends when either the user or the computer curToughness is less than 1
      while ((m_curShip.m_curToughness > 0) && (enemyShip.m_curToughness > 0))
	{
	  cout << m_pirateName << " fires " << m_curShip.m_cannon << " cannons!" << endl;

	  //check each cannon to see if it is a hit or not
	  for (int i = 0; i < m_curShip.m_cannon; i++)
	    {

	      //calculates if the cannon will hit or not  
	      if (rand() % 100 + 1 >= (100 - m_pirateRating))
		{

		  //counts how many cannons hits the enemy  
		  myShots++;
		}
	    }
	  cout << myShots << " shots hit!" << endl;

	  //the enemy's ship takes damage, their toughness gets lowers
	  enemyShip.m_curToughness = enemyShip.m_curToughness - myShots;
	  
	  //if enemy's toughness is 0 or lower, it cannot attac; if not, attack back
	  if (enemyShip.m_curToughness > 0)
	    {
	      cout << enemyPirate.GetName() << " fires " << enemyShip.m_cannon << " back!" << endl;
	      //check each cannon to see if it is a hit or not
	      for (int i = 0; i < enemyShip.m_cannon; i++)
		{
		  //calculate if the cannon will hit or not
		  if (rand() % 100 + 1 >= (100 - enemyPirate.GetRating()))
		    {
		      //counts how many cannons hits the enemy 
		      enemyShots++;
		    }
		}
	      cout << enemyShots << " shots hit!" << endl;
	      //the enemy's ship takes damage, their toughness gets lower
	      m_curShip.m_curToughness = m_curShip.m_curToughness - enemyShots;
	    }
	  //resets both myShots and enemyShots for another round of battle
	  myShots = 0;
	  enemyShots = 0;
	}
      //user ship lose if toughness is 0 and lower: their cargo cuts in half, ship gets repaired
      if (m_curShip.m_curToughness < 1)
	{
	  cout << "You lose!" << endl;
	  m_pirateCargo = m_pirateCargo/2;
	  RepairShip();
	}
      //user wins if toughness is more than 0: collects treasure and shares to his crew
      else
	{
	  cout << "You win!" << endl;
	  CalcTreasure(enemyShip);
	  cout << m_pirateName << " shares " << m_pirateCargo << " treasure with his crew!" << endl;
	}
    }
}
// Name: RepairShip
// Desc - Repairs m_curShip and increases m_pirateDays by 1 per m_maxToughness - m_curToughness
// Preconditions - Ship damaged
// Postconditions - Repairs ship and increases days (1 day per point of damage)
void Pirate::RepairShip(){
  int days = 0;

  //calculates how many days it will take to repair the ship
  days = m_curShip.m_toughness - m_curShip.m_curToughness;
  cout << "It takes "<< days << " days to repair your " << m_curShip.m_type << endl;

  //adds the calculated days to the pirate's days 
  m_pirateDays = m_pirateDays + days;

}
// Name: Flee(pirate, ship)
// Desc - User pirate tries to fleet enemy pirate.
// If m_curShip's speed is higher than enemy then successful flee otherwise Battle occurs
// Preconditions - Pirate tries to flee
// Postconditions - Returns to menu or Battle occurs
void Pirate::Flee(Pirate enemyPirate, Ship enemyShip){
  //pirateDays gets incremented by 1 when it tries to Flee
  m_pirateDays++;
  
  cout << "name of my current ship: " << m_curShip.m_type << endl;
  cout << "enemy's ship: " << enemyShip.m_type << endl << endl;
  cout << "You attempt to flee from " << enemyPirate.GetName() << "!" << endl;
  cout << "my current ship speed: " << m_curShip.m_speed << endl;
  cout << "enemyShip speed: " << enemyShip.m_speed << endl;

  //user ship escapes if its speed is greater than the enemy's
  if (m_curShip.m_speed > enemyShip.m_speed)
    {
      cout << "You narrowly escape from " << enemyPirate.GetName() << endl;
    }
  //user ship enters battle is its speed is less than the enemy's
  else
    {
      Battle(enemyPirate, enemyShip);
    }
}
// Name: DisplayScore()
// Desc - Describes information about the Pirate
// Preconditions - Pirate exists
// Postconditions - Displays name, rating, origin, desc, cargo, days, cargo/days, and
//  info about m_curShip
void Pirate::DisplayScore(){

  cout << "Name: " << m_pirateName << endl;
  cout << "Rating: " << m_pirateRating << endl;
  cout << "Country of Origin: " << m_pirateOrigin << endl;
  cout << "Description: " << m_pirateDesc << endl;
  cout << "Days Sailing: " << m_pirateDays << endl;
  cout << "Cargo Captured: " << m_pirateCargo<< endl;
  cout << "m_pirateDays: " << m_pirateDays << endl;
  cout << "Cargo Per Day: " << double(m_pirateCargo)/double(m_pirateDays) << endl;
  cout << "Ship Type: " << m_curShip.m_type << endl;
  cout << "Ship Cannons: " << m_curShip.m_cannon << endl;
  cout << "Ship Current Toughness: " << m_curShip.m_curToughness << endl;
  cout << "Ship Max Toughness: " << m_curShip.m_toughness << endl;
  cout << "Ship Speed: " << m_curShip.m_speed << endl;
  cout << "*********************" << endl;  
}
