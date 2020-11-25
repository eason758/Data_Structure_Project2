#include <iostream>
#include <string>
#include <fstream>
#include "class.h"
#include "floor.h"
#include "func.h"
#include "robot.h"



using namespace std;

ifstream f;
ofstream o("final.path", ios::out);

void init(Floor& floor);
void run(Floor& floor);
void output(Floor& floor);

int main(int argc, char *argv[]) {

	f.open(argv[1]);
	Floor floor;
	
	init(floor);

	run(floor);

	output(floor);

	return 0;
}


void init(Floor& floor){

	floor.unclean_size = 0;
	int r, c, b;
	f >> r >> c >> b;

	floor.map = new cell**[r];
	for (int i = 0; i < r; i++) floor.map[i] = new cell*[c];

	char block;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			f >> block;
			if (block == '1') floor.map[i][j] = new cell(coor(i, j), WALL, -1);
			else if (block == '0')
			{
				floor.map[i][j] = new cell(coor(i, j), ROAD, 0);
				floor.unclean_size++;
			}
			else floor.home = floor.map[i][j] = new cell(coor(i, j), HOME, 0);
		}
	}

	floor.init(r, c, b);

}

void run(Floor& floor) {

		floor.clear();
}

void output(Floor& floor) {

	cout << floor.path.size()-1 << endl;

	for(unsigned int i = 0 ; i < floor.path.size() ; i++)
		o << floor.path[i].y<< " "<< floor.path[i].x << endl;
}
