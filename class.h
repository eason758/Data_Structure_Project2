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
	bool visited;	
	bool evaluated;
	bool disted;
	enum attribute attr;
	int cost;
	int dist;

	cell(coor _loc = coor(0, 0), set<int> v_b = set<int>{}, attribute _a = ROAD, int _cost = 0) :
		loc(_loc), visited(false), attr(_a), cost(_cost),evaluated(false),disted(false){}
	cell(coor _loc, attribute _a, int _cost = 0) :
		loc(_loc), attr(_a), cost(_cost), evaluated(false), disted(false), visited(false) {};




};



struct Node {

	cell* cel;
	Node * parent;
	Node * child;
	Node * childs[4];
						//以下兩個在尋路的時候才會附值
	int cost[4];		// 右上左下
	int max_cost;
	vector<int> branch;
	Node(cell* c = new cell,Node*p = nullptr) :
		cel(c),parent(p)
	{
		child = nullptr;
	}
	

};
struct cmp
{
	bool operator() (Node* lhs, Node* rhs) { return lhs->cel->dist > rhs->cel->dist; }
};





class OneTripTree {
	Node* root;
	Node* leaf;


public:
	friend class Floor;
	inline void set_root(Node* n) { root = n; }
	inline Node* get_root() { return root; }

	void delete_tree(Node * cur) {
	}

private:

};



class Floor {

	int row;
	int col;
	int battery;
	int cur_step;
	int goto_step;
	stack<cell*> branchable;
	bool finish;
	int init_unclean_size;
	vector<coor> path;

	OneTripTree tree;
	

public:
	cell* home;
	cell*** map;
	set<cell*> unclean;
	int unclean_size;
	Floor() {}
	~Floor() {}


	void init(int r, int c, int b);
	cell get_home() { return *home; }
	inline int left_step() { return battery - cur_step; }
	inline int get_unclean_size() { return unclean.size(); }
	inline Node* get_root() { return tree.root; }


	void clear();

	void debug();


private:

	void evaluate(cell* root);
	void walk();
	void walk_back();
	Node* go_home(Node* cur);
	Node* go_to(Node* src, cell* dest);
	Node* reverse_tree(Node* cur);

	void set_node_max_cost(Node* node,bool consider_dist);
	void set_node_cost(Node* node,bool consider_dist);

	bool walkable(int x, int y);

};

#endif
