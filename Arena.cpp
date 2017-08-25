#include "Team.h"
#include "Arena.h"
#include "Factory.h"

Arena::Arena()
{

}

Arena::~Arena()
{
	delete red;
	delete blue;
}

void Arena::arena_type(unsigned type)
{
	if (type == 1)
	{
		blue = new Team("Blue", 1);
		red  = new Team("Red",  1);

		cout << endl << "It's a pvp between " << blue->getVec().at(0)->getName() << blue->getVec().at(0)->getID()
			 << " and " << red->getVec().at(0)->getName() << red->getVec().at(0)->getID() << endl << endl;
		pvp(blue->getVec().at(0), red->getVec().at(0));
	}
	else if (type == 5)
	{
		arena_5x5();
	}
	//else if (kind_of_battle == size_deathmatch)
	//{
	//	arena_deathmatch();
	//}
	else
	{
		cout << "Oops, something went wrong.." << endl;
		exit(1);
	}
}

void Arena::pvp(Human *unit1, Human *unit2)
{
	while (unit1->isAlive() && unit2->isAlive())
	{
		if (unit1->isAlive() && unit1->hasWeapon())
		{
			unit1->action(unit2);
			cout << endl;
		}
		if (unit2->isAlive() && unit2->hasWeapon())
		{
			unit2->action(unit1);
			cout << endl;
		}
	}

	red->whoWin();
	blue->whoWin();
}

void Arena::arena_5x5()
{
	std::cout << "Welcome to the Arena, heroes!" << std::endl;

	blue = new Team("Blue", teamSize);
	red  = new Team("Red", teamSize );

	queue <Human *> qu;
	vector<Human *> dead;

	while ( i != teamSize )
	{
		if ( !blue->getVec().empty() && !red->getVec().empty() )
		{
			qu.push( blue->getVec().at(i) );
			qu.push( red->getVec().at(i)  );
		}
		++i;
	}

	i = 0;
	std::cout << std::endl;
	while ( blue->anyOneAlive() && red->anyOneAlive() )
	{
		std::cout << "//////////////////////" << std::endl;
		std::cout << "Round: " << i << std::endl;
		std::cout << std::endl;

		if (
				      qu.front()->isAlive()
				&&  ( blue->anyOneAlive()	|| red->anyOneAlive() )
		   )
		{
			auto fighter = qu.front();
			Team *enemy_team = fighter->getTeam() == red ? blue : red;
			auto best_enemy = enemy_team->getLeastLivesAlive();
			qu.push(fighter);
			qu.pop();

			if (
					    i < twoTeamsSize 
					&&  fighter->isAlive() 
					&&  fighter->hasWeapon() 
					&&  qu.front()->getTeam() != fighter->getTeam()
				) 
			{
				fighter->action( qu.front() );
			} /* if */
			else if (
							i >= twoTeamsSize 
						&&  best_enemy
						&&  best_enemy->isAlive() 
						&&  fighter->isAlive() 
						&&  fighter->hasWeapon() 
						&&  best_enemy->getTeam() != fighter->getTeam()
					) 
			{
				fighter->action(best_enemy);
				cout << "BEST ENEMY: " << endl;
				best_enemy->getTeamName();
				cout << " " << best_enemy->getName() << best_enemy->getID() << " " << best_enemy->getHP() << endl;
			} /* else if */	
			if (!best_enemy->isAlive())
			{
				dead.push_back( best_enemy );
			}
		} /* if( qu.front()->isAlive()&&(blue->isAllAlive()||red->isAllAlive()) ) */

		if ( !qu.front()->isAlive() )
		{
			qu.pop();
		}

		++i;
	}

	red->whoWin();
	blue->whoWin();

	cout << "/////////////// Dead: " << dead.size() << " ///////////////";
	for ( auto i : dead )
	{
		cout << endl;
		cout << "Team: ";
		i->getTeamName();
		i->information();
	}

	//std::cout << "///////////////Stats of Blue Team///////////////";
	//for (auto i : blue->getVec())
	//{
	//	i->information();
	//}
	//std::cout << "///////////////Stats of Red Team///////////////";
	//for (auto j : red->getVec())
	//{
	//	j->information();
	//}
}