#include <iostream>
#include <string>
#include <fstream>
#include "class.h"
#include "floor.h"
#include "func.h"
#include "robot.h"

#include <time.h>


using namespace std;

ifstream f;
ofstream o("final.path", ios::out);

void init(Floor& floor);
void run(Floor& floor);
void output(Floor& floor);



double OUTPUT_START;
double OUTPUT_END;






void debug(Floor& floor);

int main(int argc, char *argv[]) {

	START = clock();

	f.open(argv[1]);
	Floor floor;
	

	init(floor);

	run(floor);

	double PROCESS_END = clock();
	
	output(floor);

	END = clock();
	
	//debug(floor);
	cout << "程式跑的時間:\n" << (PROCESS_END - PROCESS_START) / CLOCKS_PER_SEC << endl;
	cout << "總共跑的時間:\n" << (END - START)/CLOCKS_PER_SEC << endl;
	cout << "輸出共跑的時間:\n" << (OUTPUT_END - OUTPUT_START) / CLOCKS_PER_SEC << endl;
	return 0;
}


void init(Floor& floor){
	cout << "Initializing..." << endl;
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
	cout << "Floor init success!" << endl;


}

void run(Floor& floor) {

	//while (floor.unclean_size() > 0) {
	//
		floor.clear();				//clean一次 = 出去又回來
	//
	//}

}

void output(Floor& floor) {
	Node* cur = floor.get_root();
	
	vector<coor> path;

	int pre_x(cur->cel->loc.x - 1), pre_y(cur->cel->loc.y);
	int step = -1;
	while (cur != nullptr)
	{
		if ( abs(cur->cel->loc.x - pre_x) > 1) {
			cout << "wrong!" << endl;
			unsigned int i = 0;
			path.push_back(cur->cel->loc);
			while (i < path.size())
			{
				cout << path[i];
				i++;
			}
			OUTPUT_END = clock();
			exit(1);
		}
		if (abs(cur->cel->loc.y - pre_y) > 1) {
			cout << "wrong!" << endl;
			unsigned int i = 0;
			path.push_back(cur->cel->loc);
			while (i < path.size())
			{
				cout << path[i];
				i++;
			}
			OUTPUT_END = clock();
			exit(1);
		}
		if (abs(cur->cel->loc.x - pre_x) + abs(cur->cel->loc.y - pre_y) > 1) {
			cout << "wrong!" << endl;
			unsigned int i = 0;
			path.push_back(cur->cel->loc);
			while (i < path.size())
			{
				cout << path[i];
				i++;
			}
			OUTPUT_END = clock();
			exit(1);
		}
		if (abs(cur->cel->loc.x - pre_x) + abs(cur->cel->loc.y - pre_y) == 0) {
			cout << "wrong! same step!" << endl;
			unsigned int i = 0;
			path.push_back(cur->cel->loc);
			while (i < path.size())
			{
				cout << path[i];
				i++;
			}
			OUTPUT_END = clock();
			exit(1);
		}
		if (floor.map[cur->cel->loc.x][cur->cel->loc.y]->attr == WALL) {
			cout << "wrong! WALL!" << endl;
			unsigned int i = 0;
			path.push_back(cur->cel->loc);
			while (i < path.size())
			{
				cout << path[i];
				i++;
			}
			OUTPUT_END = clock();
			exit(1);
		}
		
		pre_x = cur->cel->loc.x;
		pre_y = cur->cel->loc.y;
		path.push_back(cur->cel->loc);
		cur = cur->child;
		step++;
	}


	cout << step << endl;
	o << step << endl;
	cur = floor.get_root();
	OUTPUT_START = clock();
	while (cur != nullptr)
	{
	//	cout << cur->cel->loc.y << " " << cur->cel->loc.x << endl;
		o << cur->cel->loc.y << " " << cur->cel->loc.x << endl;
		cur = cur->child;
	}
	OUTPUT_END  = clock();

	cout << "list 輸出共跑的時間:\n" << (OUTPUT_END - OUTPUT_START) / CLOCKS_PER_SEC << endl;
	
	OUTPUT_START = clock();
	unsigned int i = 0;
	while (i < path.size())
	{
		o << path[i];
		i++;
	}
	OUTPUT_END = clock();

	cout << "vec 輸出共跑的時間:\n" << (OUTPUT_END - OUTPUT_START) / CLOCKS_PER_SEC << endl;
}
