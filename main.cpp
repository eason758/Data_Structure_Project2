#include <iostream>
#include <string>
#include <fstream>
#include "class.h"
#include "floor.h"
#include "func.h"
#include "robot.h"

using namespace std;

//ifstream f;
//ofstream o("final.path", ios::out);

void init(Floor& floor, Robot& robot);
void run(Floor& floor, Robot& robot);
void output(Floor& floor, Robot& robot);

void debug(Floor& floor, Robot& robot);

int main() {


	//f.open(argv[1]);
	Floor floor;
	Robot robot;

	init(floor, robot);

	run(floor, robot);

	output(floor, robot);


	debug(floor, robot);

	
	return 0;
}


void init(Floor& floor,Robot& robot){
	cout << "Initializing..." << endl;
	int r, c, b;
	cin >> r >> c >> b;

	floor.init(r, c);
	cout << "Floor init success!" << endl;
	robot.init(b, floor.get_home());
	cout << "Robot init success!" << endl;
}

void run(Floor& floor, Robot& robot) {


}

void output(Floor& floor, Robot& robot) {



}