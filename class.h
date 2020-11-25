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



double START;
double PROCESS_START;
double END;
using namespace std;

struct coor {
	coor() { x = 0; y = 0; }
	int x,y;
	coor(int _y, int _x) :x(_x), y(_y) {}
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

	Node(cell* c = new cell, Node*p = nullptr) :
		cel(c), parent(p), child(nullptr) {}
	

};
struct cmp
{
	bool operator() (Node* lhs, Node* rhs) { return lhs->cel->dist > rhs->cel->dist; }
};

class myheap {

	coor dest;
	vector<Node*> heap;

public:
	myheap(coor d) { dest = d; }
	~myheap() {}
	inline Node* top() { return heap[0]; }
	void push(Node* node);
	void pop();
	inline bool empty() { return(!heap.empty()); }
private:
	bool smaller_than(Node* lhs, Node* rhs);
};



class Floor {
	int row;
	int col;
	int battery;
	int cur_step;
	stack<cell*> branchable;
	bool finish;
	Node* rear;

public:

	vector<coor> path;
	cell* home;
	cell*** map;
	int unclean_size;
	Floor() {}
	~Floor() {}


	void init(int r, int c, int b);
	cell get_home() { return *home; }
	inline int left_step() { return battery - cur_step; }

	void clear();

private:

	void evaluate(cell* root);
	void walk();
	void walk_back();
	stack<coor> stack_go_home(Node * cur);
	stack<coor> stack_go_to(Node* src, cell* dest);

	void set_node_max_cost(Node* node,bool consider_dist);
	void set_node_cost(Node* node,bool consider_dist);

	bool walkable(int x, int y);

};

#endif
