
// Done by Marc Latorre && Ferran Martín //

#include <iostream>

using namespace std;

#define GRAHP_SIZE 5

void PrintPath(int path[], bool isCycle);

// Checks if the vertex v can be added at index 'pos' in the path
bool CanBeAddedToPath(int v, bool graph[GRAHP_SIZE][GRAHP_SIZE], int path[], int pos)
{
	if (graph[path[pos - 1]][v] == 0)	// Checks if the position we are analizing and the previous path pos is connected
		return false;

	for (int i = 0; i < pos; i++)		// Checks if the next position is already in the path
		if (path[i] == v)
			return false;

	return true;
}

bool CheckHamiltonian(bool graph[GRAHP_SIZE][GRAHP_SIZE], int path[], int pos, bool& isCycle)
{
	if (pos == GRAHP_SIZE) // Path completed
	{
		if (graph[path[pos - 1]][path[0]] == 1)
		{
			isCycle = true;
			return true;
		}
		else
		{
			isCycle = false;
			return true;
		}
	}

	for (int i = 1; i < GRAHP_SIZE; i++)
	{
		if (CanBeAddedToPath(i, graph, path, pos))
		{
			// If it can be added the vertex is added to the path, 
			// if not the path position goes back to be -1 to check new paths if they exist
			path[pos] = i;
			if (CheckHamiltonian(graph, path, pos + 1, isCycle) == true)
				return true;
			path[pos] = -1;
		}
	}
	return false;
}

bool DoHamiltonian(bool graph[GRAHP_SIZE][GRAHP_SIZE])
{
	bool isCycle;
	int *path = new int[GRAHP_SIZE];

	for (int i = 0; i < GRAHP_SIZE; i++)
		path[i] = -1;
	path[0] = 0;

	if (CheckHamiltonian(graph, path, 1, isCycle) == false)
	{
		cout << "\nSolution does not exist" << endl;
		return false;
	}

	PrintPath(path, isCycle);
	return true;
}

void PrintPath(int path[], bool isCycle)
{
	if (isCycle)
	{
		cout << "\nThere is a Hamiltonian Cycle which is:\n" << endl;
		for (int i = 0; i < GRAHP_SIZE; i++)
			cout << path[i] << "  ";
		cout << path[0] << endl;
	}
	else
	{
		cout << "\nThere is a Hamiltonian Path which is:\n" << endl;
		for (int i = 0; i < GRAHP_SIZE; i++)
			cout << path[i] << "  ";
	}
}
int main()
{
	/*
	(0)-------(2)
	|          |
	|   -(1)-  |
	|  /     \ |
	(3)       (4)    
	*/
	bool graph1[GRAHP_SIZE][GRAHP_SIZE] =
	{	{ 0, 0, 1, 1, 0 },
		{ 0, 0, 0, 1, 1 },
		{ 1, 0, 0, 0, 1 },
		{ 1, 1, 0, 0, 0 },
		{ 0, 1, 1, 0, 0 },
	};

	DoHamiltonian(graph1);

	system("pause");
	return 0;
}