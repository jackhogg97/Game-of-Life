//Code for BBC assessment 
//Using a 2D Vector to represent the grid 
//Using local variables on the stack
//Implementation could be further developed later 
//To create a variable on the heap as pass it by reference 
//Making the program more efficient
//Program asks for a text file at the console which is the scenario
//Jack Hogg

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void generate_grid(vector<vector<int>> grid); //Function to print grid
vector<vector<int>> count_neighbours(vector<vector<int>> grid); //Returns grid of same size with number of neighbours as each element

int main()
{
	//Grid uses int as 0s or 1s 
	//Could of used boolean or enumerated datatypes
	//Dynamic 2D array which represents the grid, 0 is a dead cell, 1 is a live cell.
	vector<vector<int>>  grid;

	//Ask user for scenario to run
	cout << "Enter the scenario's filename.\n";
	string filename;
	cin >> filename;
	
	//Get input scenario from file
	ifstream input;
	input.open(filename); //Open file
	//Check for error
	if (!input) 
	{
		cout << "Error: Can't open the file \n";
		exit(1);
	}


	//Intialise grid
	int a = 0; //Used a row iterator
	//Get line from input file
	string line; 
	getline(input, line);
	while (input)
	{
		grid.resize(a + 1); //Add row to grid
		for (unsigned int i = 0; i < line.length(); i++)
		{
			//The ASCII number for 0 and 1 is 48 and 49 respectively
			//Therefore line[i] will equal 48 or 49
			//Minusing '0' will give us 0 or 1
			int cell = line[i] - '0'; 
			grid[a].push_back(cell); //Add element to row
		}
		a++; //Next row in grid vector
		getline(input, line); //Get next line
	}

	//Next state of grid
	bool cont = true;
	while(cont)
	{
		//Call to a function which will return a another grid the same size as the grid given
		//Each element will contain the number of neighbours at the corresponding cell of the grid given
		vector<vector<int>> neighbours_grid = count_neighbours(grid);

		//Loop through grid row major
		for (unsigned int i = 0; i < grid.size(); i++)
		{
			for (unsigned int x = 0; x < grid[i].size(); x++)
			{
				//Number of neighbours at cell
				int neighbours = neighbours_grid[i][x];

				if (grid[i][x] == 1) //Cell alive
				{
					if (neighbours < 2) grid[i][x] = 0; //Underpopulation
					else if (neighbours > 3) grid[i][x] = 0; //Overpopulation
					else grid[i][x] = 1; //Survival
				}
				else //Cell dead
				{
					if (neighbours > 2) grid[i][x] = 1; //Creation of life
				}
			}
			//end of the row
		}

		//Print grid 
		generate_grid(grid);
		
		//Does user want to end the game
		cout << "Evolve to next state? (y/n)\n";
		string user_input;
		cin >> user_input;
		if (user_input.compare("n") == 0) cont = false;
	
	}
}

void generate_grid(vector<vector<int>> grid)
{
	//function will use two for loops to cycle through the grid row-major
	for (unsigned int i = 0; i < grid.size(); i++)
	{
		for (unsigned int x = 0; x < grid[i].size(); x++)
		{
			if (grid[i][x] == 1 ) cout << '*'; //live cell
			else cout << '.'; //dead cell
		}
		//end of the row
		cout << endl;
	}
}
vector<vector<int>> count_neighbours(vector<vector<int>> grid)
{
	//Declare a 2D vector with size of grid
	//2D vector will store number of neighbors of each element in its corresponding position
	vector<vector<int>> neighbours(grid.size(), vector<int> (grid[0].size())); 
	
	for (unsigned int i = 0; i < grid.size(); i++)
	{

		for (unsigned int x = 0; x < grid[i].size(); x++)
		{
			int n = 0; //temporally store number of neightbours
			const int kMax_neighbours = 3; //Number of maximum potential neighbours including oneself
			int r[kMax_neighbours] = { i - 1, i, i + 1 }; //Position of potential row neighbours
			int c[kMax_neighbours] = { x - 1, x, x + 1 }; //Position of potential column neighbours

			for (int k = 0; k < kMax_neighbours; k++)
			{
				for (int l = 0; l < kMax_neighbours; l++)
				{
					//Check to see if memory address is valid before accessing
					if (r[k] >= 0 && 
						r[k] < grid.size() && 
						c[l] >= 0 && 
						c[l] < grid[0].size())
					{
						if (grid[r[k]][c[l]] == 1) n++;
					}
				}
				
			}
			if (grid[i][x] == 1) neighbours[i][x] = n - 1; //Disregard itself as neighbour
			else neighbours[i][x] = n;
		}
		//end of the row
	}

	return neighbours;
}

