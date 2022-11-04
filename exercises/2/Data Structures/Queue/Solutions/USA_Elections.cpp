#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>

static const std::vector<std::string> states = {
	  "Alabama"
	, "Alaska"
	, "Arizona"
	, "Arkansas"
	, "California"
	, "Colorado"
	, "Connecticut"
	, "Delaware"
	, "Florida"
	, "Georgia"
	, "Hawaii"
	, "Idaho"
	, "Illinois"
	, "Indiana"
	, "Iowa"
	, "Kansas"
	, "Kentucky"
	, "Louisiana"
	, "Maine"
	, "Maryland"
	, "Massachusetts"
	, "Michigan"
	, "Minnesota"
	, "Mississippi"
	, "Missouri"
	, "Montana"
	, "Nebraska"
	, "Nevada"
	, "New Hampshire"
	, "New Jersey"
	, "New Mexico"
	, "New York"
	, "North Carolina"
	, "North Dakota"
	, "Ohio"
	, "Oklahoma"
	, "Oregon"
	, "Pennsylvania"
	, "Rhode Island"
	, "South Carolina"
	, "South Dakota"
	, "Tennessee"
	, "Texas"
	, "Utah"
	, "Vermont"
	, "Virginia"
	, "Washington"
	, "West Virginia"
	, "Wisconsin"
	, "Wyoming"
};

struct Bulletin
{
	std::string name;
	std::string state;
	std::string color;
	bool valid = true;

	void print() const
	{
		std::cout << "Bulletin for " << name << ", from State of " << state << "; " << color << std::endl;
	}
};

void StartElectionDay()
{
	std::queue<Bulletin> allVotes;
	std::stack<Bulletin> trumpVotes;
	std::stack<Bulletin> bidenVotes;
	std::vector<Bulletin> statistics;

	while ( true )
	{
		std::string command;
		std::cin >> command;

		if ( command == "vote" )
		{
			Bulletin current;
			std::string name;
			std::cin >> name;
			if ( name == "Trump" )
			{
				current.name = name;
			}
			else if ( name == "Biden" )
			{
				current.name = name;
			}
			else
			{
				current.name = "Invalid name";
				current.valid = false;
			}
			std::string state;
			std::cin >> state;
			std::vector<std::string>::const_iterator stateIt = std::find( states.begin(), states.end(), state );
			if ( stateIt != states.end() )
			{
				current.state = state;
			}
			else
			{
				current.state = "Invalid state";
				current.valid = false;
			}
			
			std::string color;
			std::cin >> color;
			if ( color == "red" )
			{
				current.color = color;
			}
			else if ( color == "blue" )
			{
				current.color = color;
			}
			else
			{
				current.color = "Invalid color";
				current.valid = false;
			}
			allVotes.push( current );
			std::cout << "The vote has been added!" << std::endl;
		}
		else if ( command == "count" )
		{
			if ( !allVotes.empty() )
			{
				Bulletin currentBulletin = allVotes.front();
				allVotes.pop();
				if ( currentBulletin.valid )
				{
					if ( currentBulletin.name == "Trump" )
					{
						trumpVotes.push( currentBulletin );
					}
					else if ( currentBulletin.name == "Biden" )
					{
						bidenVotes.push( currentBulletin );
					}
					std::cout << "The vote has been counted" << std::endl;
				}
				else
				{
					std::cout << "Invalid bulletin" << std::endl;
				}
			}
			else
			{
				std::cout << "There is no votes to count. Try later :)" << std::endl;
			}
		}
		else if ( command == "info-election" )
		{
			size_t countAllVotesForNow = trumpVotes.size() + bidenVotes.size();
			std::cout << "Trump has: " << ( (double)trumpVotes.size() / countAllVotesForNow ) / 100 << " %" << std::endl;
			std::cout << "Biden has: " << ( (double)bidenVotes.size() / countAllVotesForNow ) / 100 << " %" << std::endl;
		}
		else if ( command == "take" )
		{
			std::string color;
			std::cin >> color;
			if ( color == "red" )
			{
				if ( !trumpVotes.empty() )
				{
					Bulletin topBulletin = trumpVotes.top();
					trumpVotes.pop();
					topBulletin.print();
					statistics.push_back( topBulletin );
				}
				else
				{
					std::cout << "There is no red votes to take! All has been added to the statistics" << std::endl;
				}
			}
			else if ( color == "blue" )
			{
				if ( !trumpVotes.empty() )
				{
					Bulletin topBulletin = bidenVotes.top();
					bidenVotes.pop();
					topBulletin.print();
					statistics.push_back( topBulletin );
				}
				else
				{
					std::cout << "There is no blue votes to take! All has been added to the statistics" << std::endl;
				}
			}
		}
		else if ( command == "info" )
		{
			std::string state;
			std::cin >> state;
			std::vector<std::string>::const_iterator stateIt = std::find( states.begin(), states.end(), state );
			if ( stateIt != states.end() )
			{
				for ( const Bulletin& bulletin : statistics )
				{
					if ( bulletin.state == state )
					{
						bulletin.print();
					}
				}
			}
			else
			{
				std::cout << "Invalid state" << std::endl;
			}
		}
		else if ( command == "end" )
		{
			break;
		}
	}

}


int main()
{
	StartElectionDay();

	return 0;
}