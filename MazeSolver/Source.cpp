#include <iostream>
#include <fstream>
#include <vector>

struct point
{
	int x, y;
};

int rowCount, colCount;
bool **walls, **opened;
std::vector<point> way;

bool **createBoolMatrix(int rowCount, int colCount)
{
	bool** arr = new bool*[rowCount];
	for (int i = 0; i < rowCount; ++i)
		arr[i] = new bool[colCount];
	return arr;
}

void freeBoolMatrix(bool **matrix, int rowCount)
{
	for (int i = 0; i < rowCount; i++)
		delete[] matrix[i];
	delete[] matrix;
}

bool findSolution(int x, int y)
{
	// Check if the position in the maze 
	if (x < 0 || y < 0 || x > rowCount - 1 || y > colCount - 1)
		return false;

	// Check if wall or if opened
	if (walls[x][y] || opened[x][y])
		return false;
	
	way.push_back({ x, y });

	// Check if goal
	if (x == rowCount - 1 && y == colCount - 1)
		return true;

	opened[x][y] = true;

	if (findSolution(x - 1, y)	|| // North
		findSolution(x, y + 1)	|| // East
		findSolution(x + 1, y)	|| // South
		findSolution(x, y - 1))	   // West
		return true;

	way.pop_back();
	return false;
}

void printResult()
{
	std::cout << "X  Y" << std::endl << std::endl;
	for (std::vector<point>::iterator iter = way.begin(); iter != way.end(); ++iter)
	{
		std::cout << (*iter).x << "  " << (*iter).y << std::endl;
		std::cout << "-----" << std::endl;
	}

	std::cout << '\n';	
}

int main()
{
	char fileName[256];
	std::cout << "Enter file name: " << std::endl;
	std::cin >> fileName;

	std::ifstream infile(fileName);
	if (!infile)
	{
		std::cout << "File does not exist." << std::endl;
		return 1;
	}

	infile >> rowCount;
	infile >> colCount;

	walls = createBoolMatrix(rowCount, colCount);
	opened = createBoolMatrix(rowCount, colCount);
	for (int x = 0; x < rowCount; x++)
	{
		for (int y = 0; y < colCount; y++)
		{
			infile >> walls[x][y]; // Input from file
			opened[x][y] = false; // Set default value
		}
	}
	infile.close();

	if (findSolution(0, 0))
		printResult();
	else
		std::cout << "There is no way!";

	freeBoolMatrix(walls, rowCount);
	freeBoolMatrix(opened, rowCount);
	std::cin.get();
	std::cin.get();
	return 0;
}