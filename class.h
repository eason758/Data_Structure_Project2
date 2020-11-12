#pragma once

#ifndef CLASS
#define CLASS

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <stack>
#include <time.h>
double START;
double PROCESS_START;
double END;
using namespace std;

struct coor {
	coor() { x = 0; y = 0; }
	int x;
	int y;
	coor(int _y, int _x) :x(_x), y(_y) {}
	friend class floor;
};
ostream& operator<<(ostream& os, coor c) {
	os << "( " << c.y << " , " << c.x << " )";
	return os;
}

enum attribute {

	ROAD = 0,
	WALL,
	HOME
};

struct cell {

	coor loc;
	set<int> visited_branches;	
	bool evaluated;
	enum attribute attr;
	int cost;

	cell(coor _loc = coor(0, 0), set<int> v_b = set<int>{}, attribute _a = ROAD, int _cost = 0) :
		loc(_loc), visited_branches(v_b), attr(_a), cost(_cost),evaluated(false){}
	cell(coor _loc, attribute _a, int _cost = 0) :
		loc(_loc), attr(_a), cost(_cost), evaluated(false) {};


};




struct Node {

	cell* cel;
	Node * parent;
	Node * child[4];
						//以下兩個在尋路的時候才會附值
	int cost[4];		// 右上左下
	int max_cost;
	vector<int> branch;
	Node(cell* c = new cell,Node*p = nullptr) :
		cel(c),parent(p)
	{
		child[0] = nullptr;
		child[1] = nullptr;
		child[2] = nullptr;
		child[3] = nullptr;

	}

};
Node* reverse_tree(Node* cur);

class OneTripTree {
	Node* root;
	vector<Node*> leaves;
	int cur_branch;
	int total_branch;


public:
	friend class Floor;
	inline void set_root(Node* n) { root = n; }
	inline Node* get_root() { return root; }

	void delete_tree(Node * cur) {
		for (int i = 0; i < 4; i++) {
			delete_tree(cur->child[i]);
		}
		delete cur;
	}

private:

};



class Floor {

	int row;
	int col;
	int battery;
	int emp_min_step;
	int cur_step;
	bool finish;
	Node * finalNode;
	vector<cell*> unclean;
	cell* home;
	cell*** map;
	OneTripTree tree;
	

public:
	Floor() {}
	~Floor() {}


	void init(int r, int c, int b);
	cell get_home() { return *home; }
	inline int left_step() { return battery - cur_step; }
	inline int get_unclean_size() { return unclean.size(); }



	void clear();

	void debug();


private:

	void distance_evaluation(cell* root);
	Node** find_emp_cell(Node* root);
	void walk();
	void walk_back();


	void set_node_max_cost(Node* node);
	void set_node_cost(Node* node);
	bool visited(Node* node, int x, int y);

	bool walkable(int x, int y);

};

#endif
