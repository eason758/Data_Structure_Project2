#include <iostream>
#include <string>
#include <fstream>
#include "class.h"
#include "floor.h"
#include "func.h"
#include "robot.h"

#include <time.h>


using namespace std;

//ifstream f;
//ofstream o("final.path", ios::out);

void init(Floor& floor);
void run(Floor& floor);
void output(Floor& floor);











void debug(Floor& floor);

int main() {

	START = clock();

	//f.open(argv[1]);
	Floor floor;
	

	init(floor);

	run(floor);

	output(floor);

	END = clock();
	
	debug(floor);
	cout << "程式跑的時間:\n" << (END - PROCESS_START) / CLOCKS_PER_SEC << endl;
	cout << "總共跑的時間:\n" << (END - START)/CLOCKS_PER_SEC << endl;
	
	return 0;
}


void init(Floor& floor){
	cout << "Initializing..." << endl;
	int r, c, b;
	cin >> r >> c >> b;

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



}
