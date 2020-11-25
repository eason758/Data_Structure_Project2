#pragma once

#ifndef FLOOR
#define FLOOR

#include "class.h"

void debugg(Node* root);


#define MAX(a,b) ((a>b) ? a : b ) 

void Floor::init(int r, int c, int b) {

	finish = false;
	row = r;
	col = c;
	battery = b;

	init_unclean_size = unclean_size;

	PROCESS_START = clock();

}


void Floor::clear(){

	tree.root = new Node(home);
	tree.leaf = tree.root;

	path.push_back(home->loc);

	map[home->loc.y][home->loc.x]->visited = 1;

	evaluate(home);

	cur_step = 0;
	do
	{
		walk();
		if(!finish)
			walk_back();
		
		
		//cout << "--------------------------------------------------------";
		//debug();
		//cout << "--------------------------------------------------------";
	} while (!finish);


}


void Floor::walk() {
	//cout << "walk!" << endl;


	while (cur_step < battery/2)
	{
		/*
		debugg(tree.root);
	
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				cout << map[i][j]->visited << " ";
			}
			cout << endl;
		}
		*/
		
		cur_step++;

		//cout << "step: " << cur_step << endl;

		set_node_cost(tree.leaf, false);
		set_node_max_cost(tree.leaf, false);
		/*
		cout << "1 : " << tree.leaf->cost[0] << endl;
		cout << "2 : " << tree.leaf->cost[1] << endl;
		cout << "3 : " << tree.leaf->cost[2] << endl;
		cout << "4 : " << tree.leaf->cost[3] << endl;
		if (!branchable.empty())
			cout << "branchable : " << branchable.top()->loc << endl;
		else cout << "branchable emp" << endl;
		cout << "max : " << tree.leaf->max_cost << endl;
		cout << "now: " << tree.leaf->cel->loc << endl;
		*/
		int x = tree.leaf->cel->loc.x;
		int y = tree.leaf->cel->loc.y;


		if (tree.leaf->max_cost == 0) {
			//cout << "bbbbbbbbbbbbbbbbbbb" << endl;
			//cout << "unclean.size() :" << unclean.size() << endl;
			// 全都走過了
			if (unclean_size == 0) {
				go_home(tree.leaf);
				finish = true;
				break;
			}
			else {
				while (!branchable.empty())
				{
					/*
					cout << branchable.top()->loc << endl;
					cout << map[branchable.top()->loc.y][branchable.top()->loc.x + 1]->visited << endl;
					cout << map[branchable.top()->loc.y - 1][branchable.top()->loc.x]->visited << endl;
					cout << map[branchable.top()->loc.y][branchable.top()->loc.x - 1]->visited << endl;
					cout << map[branchable.top()->loc.y + 1][branchable.top()->loc.x]->visited << endl;
					*/
					if ((map[branchable.top()->loc.y][branchable.top()->loc.x + 1]->visited == 1 ||
						!walkable(branchable.top()->loc.x + 1, branchable.top()->loc.y)) &&
						(map[branchable.top()->loc.y - 1][branchable.top()->loc.x]->visited == 1 ||
							!walkable(branchable.top()->loc.x, branchable.top()->loc.y - 1)) &&
							(map[branchable.top()->loc.y][branchable.top()->loc.x - 1]->visited == 1 ||
								!walkable(branchable.top()->loc.x - 1, branchable.top()->loc.y)) &&
								(map[branchable.top()->loc.y + 1][branchable.top()->loc.x]->visited == 1 ||
									!walkable(branchable.top()->loc.x, branchable.top()->loc.y + 1))) {
						branchable.pop();
						//cout << "pop" << endl;
					}
					else break;
				}
				tree.leaf = go_to(tree.leaf, branchable.top());
			}


		}
		else {

			int x = tree.leaf->cel->loc.x;
			int y = tree.leaf->cel->loc.y;		// current cell position


			bool find = false;

			if ((tree.leaf->cost[0] > 0 && tree.leaf->cost[1] > 0) || (tree.leaf->cost[0] > 0 && tree.leaf->cost[2] > 0) || (tree.leaf->cost[0] > 0 && tree.leaf->cost[3] > 0) ||
				(tree.leaf->cost[1] > 0 && tree.leaf->cost[2] > 0) || (tree.leaf->cost[1] > 0 && tree.leaf->cost[3] > 0) || (tree.leaf->cost[2] > 0 && tree.leaf->cost[3] > 0)) {
				branchable.push(map[y][x]);
			}

			if (tree.leaf->cost[0] == tree.leaf->max_cost)
			{
				//set child & parent
				tree.leaf->child = new Node(map[y][x + 1], tree.leaf);

				path.push_back(map[y][x + 1]->loc);

				// set cell branch_visit
				map[y][x + 1]->visited = 1;
				//set same level vector
				tree.leaf = tree.leaf->child;

				unclean_size--;

				}
			else if (tree.leaf->cost[1] == tree.leaf->max_cost)
				{// one of max_grid
					
					//set child & parent
					tree.leaf->child =
						new Node(map[y - 1][x], tree.leaf);

					path.push_back(map[y - 1][x]->loc);

					// set cell branch_visit
					map[y - 1][x]->visited = 1;
					//set same level vector
					tree.leaf = tree.leaf->child;

					unclean_size--;
					
					find = true;
				}
			else if (tree.leaf->cost[2] == tree.leaf->max_cost)
				{// one of max_grid

					//set child & parent
					tree.leaf->child =
						new Node(map[y][x - 1], tree.leaf);

					path.push_back(map[y][x - 1]->loc);

					// set cell branch_visit
					map[y][x - 1]->visited = 1;
					//set same level vector
					tree.leaf = tree.leaf->child;

					unclean_size--;

					find = true;
				}
			else if (tree.leaf->cost[3] == tree.leaf->max_cost)
				{// one of max_grid

					//set child & parent
					tree.leaf->child =
						new Node(map[y + 1][x], tree.leaf);

					path.push_back(map[y + 1][x]->loc);

					// set cell branch_visit
					map[y + 1][x]->visited = 1;
					//set same level vector
					tree.leaf = tree.leaf->child;

					unclean_size--;

					find = true;
				}
			
		}

	}


}

void Floor::walk_back() {
	//cout << "walk back!" << endl;
	
	while (tree.leaf->cel != home)
	{
		/*
		debugg(tree.root);

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				cout << map[i][j]->visited << " ";
			}
			cout << endl;
		}
		cout << "step: " << cur_step << endl;
		*/
		cur_step++;


		set_node_cost(tree.leaf, true);
		set_node_max_cost(tree.leaf, true);

		int x = tree.leaf->cel->loc.x;
		int y = tree.leaf->cel->loc.y;
		/*
		cout << "1 : " << tree.leaf->cost[0] << endl;
		cout << "2 : " << tree.leaf->cost[1] << endl;
		cout << "3 : " << tree.leaf->cost[2] << endl;
		cout << "4 : " << tree.leaf->cost[3] << endl;
		if (!branchable.empty())
			cout << "branchable : " << branchable.top()->loc << endl;
		else cout << "branchable emp"<< endl;
		cout << "max : " << tree.leaf->max_cost << endl;
		*/

		if (tree.leaf->max_cost == 0) {
			if ((walkable(x + 1, y) && map[y][x + 1]->cost > 0 && map[y][x + 1]->visited) || (walkable(x, y - 1) && map[y - 1][x]->cost > 0 && map[y - 1][x]->visited) ||
				(walkable(x - 1, y) && map[y][x - 1]->cost > 0 && map[y][x - 1]->visited) || (walkable(x, y + 1) && map[y + 1][x]->cost > 0 && map[y + 1][x]->visited))
			{
				branchable.push(map[y][x]);
			}
			// 全都走過了
			if (unclean_size == 0) {
				go_home(tree.leaf);
				finish = true;
				break;
			}
			else {
				while (!branchable.empty())
				{
					/*
					cout << branchable.top()->loc << endl;
					cout << map[branchable.top()->loc.y][branchable.top()->loc.x + 1]->visited << endl;
					cout << map[branchable.top()->loc.y - 1][branchable.top()->loc.x]->visited << endl;
					cout << map[branchable.top()->loc.y][branchable.top()->loc.x - 1]->visited << endl;
					cout << map[branchable.top()->loc.y + 1][branchable.top()->loc.x]->visited << endl;
					*/
					if ((map[branchable.top()->loc.y][branchable.top()->loc.x + 1]->visited == 1 ||
						!walkable(branchable.top()->loc.x + 1, branchable.top()->loc.y)) &&
						(map[branchable.top()->loc.y - 1][branchable.top()->loc.x]->visited == 1 ||
							!walkable(branchable.top()->loc.x, branchable.top()->loc.y - 1)) &&
							(map[branchable.top()->loc.y][branchable.top()->loc.x - 1]->visited == 1 ||
								!walkable(branchable.top()->loc.x - 1, branchable.top()->loc.y)) &&
								(map[branchable.top()->loc.y + 1][branchable.top()->loc.x]->visited == 1 ||
									!walkable(branchable.top()->loc.x, branchable.top()->loc.y + 1)))
						branchable.pop();
					else break;
				}
				tree.leaf = go_to(tree.leaf, branchable.top());
			}
			
		}
		else {
			int x = tree.leaf->cel->loc.x;
			int y = tree.leaf->cel->loc.y;		// current cell position


			bool find = false;



			int cost[4];
			cost[0] = tree.leaf->cost[0];
			cost[1] = tree.leaf->cost[1];
			cost[2] = tree.leaf->cost[2];
			cost[3] = tree.leaf->cost[3];

			if ((walkable(x + 1, y) && map[y][x + 1]->cost > 0 && map[y][x + 1]->visited) || (walkable(x, y - 1) && map[y - 1][x]->cost > 0 && map[y - 1][x]->visited) ||
				(walkable(x - 1, y) && map[y][x - 1]->cost > 0 && map[y][x - 1]->visited) || (walkable(x, y + 1) && map[y + 1][x]->cost > 0 && map[y + 1][x]->visited))
			{
				branchable.push(map[y][x]);
			}

			if (tree.leaf->cost[0] == tree.leaf->max_cost)
			{// one of max_grid

				//set child & parent
				tree.leaf->child =
					new Node(map[y][x + 1], tree.leaf);

				path.push_back(map[y][x + 1]->loc);

				// set cell branch_visit
				map[y][x + 1]->visited = 1;
				//set same level vector
				tree.leaf = tree.leaf->child;

				unclean_size--;

				find = true;
			}
			else if (tree.leaf->cost[1] == tree.leaf->max_cost)
			{// one of max_grid

				//set child & parent
				tree.leaf->child =
					new Node(map[y - 1][x], tree.leaf);

				path.push_back(map[y - 1][x]->loc);

				// set cell branch_visit
				map[y - 1][x]->visited = 1;
				//set same level vector
				tree.leaf = tree.leaf->child;

				unclean_size--;

				find = true;
			}
			else if (tree.leaf->cost[2] == tree.leaf->max_cost)
			{// one of max_grid

				//set child & parent
				tree.leaf->child =
					new Node(map[y][x - 1], tree.leaf);

				path.push_back(map[y][x - 1]->loc);

				// set cell branch_visit
				map[y][x - 1]->visited = 1;
				//set same level vector
				tree.leaf = tree.leaf->child;

				unclean_size--;

				find = true;
			}
			else if (tree.leaf->cost[3] == tree.leaf->max_cost )
			{// one of max_grid

				//set child & parent
				tree.leaf->child =
					new Node(map[y + 1][x], tree.leaf);

				path.push_back(map[y + 1][x]->loc);

				// set cell branch_visit
				map[y + 1][x]->visited = 1;
				//set same level vector
				tree.leaf = tree.leaf->child;

				unclean_size--;

				find = true;
			}

		}

	}
	cur_step = 0;


}



//A*
Node* Floor::go_home(Node * cur) {

	int root_x = (cur)->cel->loc.x;
	int root_y = (cur)->cel->loc.y;


	Node* fake_root = new Node((cur)->cel,cur->parent);
	priority_queue<Node*,vector<Node*>, cmp> open;

	set<cell*> close = {};
	open.push(fake_root);

	vector<coor>  go_home_path;


	while (open.top()->cel != home)
	{
		//cout << "top: " << open.top()->cel->loc <<" home: " << home->loc<<endl;
		Node * n = open.top();
		open.pop();
		int x = n->cel->loc.x;
		int y = n->cel->loc.y;
		
		int child = 0;
		if (walkable(x + 1, y) && !close.count(map[y][x + 1]))
		{
			n->childs[child] = new Node(map[y][x + 1],n);
			open.push(n->childs[child++]);
		}
		if (walkable(x, y - 1) && !close.count(map[y - 1][x]))
		{
			n->childs[child] = new Node(map[y - 1][x], n);
			open.push(n->childs[child++]);
		}
		if (walkable(x - 1, y) && !close.count(map[y][x - 1]))
		{
			n->childs[child] = new Node(map[y][x - 1], n);
			open.push(n->childs[child++]);
		}
		if (walkable(x, y + 1) && !close.count(map[y + 1][x]))
		{
			n->childs[child] = new Node(map[y + 1][x], n);
			open.push(n->childs[child++]);
		}

		close.insert(map[y][x]);

	}

	(cur) = reverse_tree(open.top());
	cur_step = 0;
	return open.top();

}

Node* Floor::go_to(Node* src, cell* dest) {

	//cout << "  goto!  " << endl;

	Node* cur = src;

	int root_x = (cur)->cel->loc.x;
	int root_y = (cur)->cel->loc.y;


	Node* fake_root = new Node((cur)->cel);
	vector<Node*> open;

	set<cell*> close = {};
	open.push_back(fake_root);
	int min_index = 0;



	while (open[min_index]->cel != dest)
	{
		
		
		Node * n = open[min_index];
		open.erase(open.begin() + min_index);
		int x = n->cel->loc.x;
		int y = n->cel->loc.y;

		int child = 0;
		if (walkable(x + 1, y) && !close.count(map[y][x + 1]))
		{
			n->childs[child] = new Node(map[y][x + 1], n);
			open.push_back(n->childs[child++]);
		}
		if (walkable(x, y - 1) && !close.count(map[y - 1][x]))
		{
			n->childs[child] = new Node(map[y - 1][x], n);
			open.push_back(n->childs[child++]);
		}
		if (walkable(x - 1, y) && !close.count(map[y][x - 1]))
		{
			n->childs[child] = new Node(map[y][x - 1], n);
			open.push_back(n->childs[child++]);
		}
		if (walkable(x, y + 1) && !close.count(map[y + 1][x]))
		{
			n->childs[child] = new Node(map[y + 1][x], n);
			open.push_back(n->childs[child++]);
		}

		close.insert(map[y][x]);



		

		min_index = 0;
		for (unsigned i = 0; i < open.size(); i++) {

			if (abs(open[min_index]->cel->loc.x - dest->loc.x) + abs(open[min_index]->cel->loc.y - dest->loc.y)
				>
				abs(open[i]->cel->loc.x - dest->loc.x) + abs(open[i]->cel->loc.y - dest->loc.y))
				min_index = i;

		}

	}
	Node* tmp = reverse_tree(open[min_index]);

	if (tmp == nullptr) {
		return go_home(tree.leaf);
	}
	else {
		src->child = tmp->child;
		cur_step += goto_step;
		return open[min_index];
	}
	

}

//evaluated cost and distance
void Floor::evaluate(cell* root) {
	
	queue<cell*> q;
	q.push(root);
	root->cost = 0;
	int root_x = root->loc.x;
	int root_y = root->loc.y;

	while (!q.empty())
	{

		cell* cur = q.front();
		cur->evaluated = true;
		q.pop();

		int x = cur->loc.x;
		int y = cur->loc.y;

		// set cost
		if (walkable(x + 1, y) && !map[y][x + 1]->evaluated) {
			
			map[y][x + 1]->cost = cur->cost + 1;
			map[y][x + 1]->evaluated = true;
			q.push(map[y][x + 1]);
		}
		if (walkable(x, y - 1) && !map[y - 1][x]->evaluated) {
			map[y - 1][x]->cost = cur->cost + 1;
			map[y - 1][x]->evaluated = true;
			q.push(map[y - 1][x]);
		}
		if (walkable(x - 1, y) && !map[y][x - 1]->evaluated) {
			map[y][x - 1]->cost = cur->cost + 1;
			map[y][x - 1]->evaluated = true;
			q.push(map[y][x - 1]);
		}
		if (walkable(x, y + 1) && !map[y + 1][x]->evaluated) {
			map[y + 1][x]->cost = cur->cost + 1;
			map[y + 1][x]->evaluated = true;
			q.push(map[y + 1][x]);
		}

		//set
		if (walkable(x + 1, y - 1) && !map[y - 1][x + 1]->evaluated) {
			if (walkable(x + 1, y) && walkable(x, y - 1)) {
				map[y - 1][x + 1]->cost = cur->cost + 1;
				map[y - 1][x + 1]->evaluated = true;
				q.push(map[y - 1][x + 1]);
			}
		}
		if (walkable(x - 1, y - 1) && !map[y - 1][x - 1]->evaluated) {
			if (walkable(x - 1, y) && walkable(x, y - 1)) {
				map[y - 1][x - 1]->cost = cur->cost + 1;
				map[y - 1][x - 1]->evaluated = true;
				q.push(map[y - 1][x - 1]);
			}
		}
		if (walkable(x - 1, y + 1) && !map[y + 1][x - 1]->evaluated) {
			if (walkable(x - 1, y) && walkable(x, y + 1)) {
				map[y + 1][x - 1]->cost = cur->cost + 1;
				map[y + 1][x - 1]->evaluated = true;
				q.push(map[y + 1][x - 1]);
			}
		}
		if (walkable(x + 1, y + 1) && !map[y + 1][x + 1]->evaluated) {
			if (walkable(x + 1, y) && walkable(x, y + 1)) {
				map[y + 1][x + 1]->cost = cur->cost + 1;
				map[y + 1][x + 1]->evaluated = true;
				q.push(map[y + 1][x + 1]);
			}
		}
	}

	q.push(root);
	root->dist = 0;
	root->disted = true;
	while (!q.empty())
	{

		cell* cur = q.front();
		q.pop();

		int x = cur->loc.x;
		int y = cur->loc.y;

		if (walkable(x + 1, y) && !map[y][x + 1]->disted) {

			map[y][x + 1]->dist = cur->dist + 1;
			map[y][x + 1]->disted = true;
			q.push(map[y][x + 1]);
		}
		if (walkable(x, y - 1) && !map[y - 1][x]->disted) {
			map[y - 1][x]->dist = cur->dist + 1;
			map[y - 1][x]->disted = true;
			q.push(map[y - 1][x]);
		}
		if (walkable(x - 1, y) && !map[y][x - 1]->disted) {
			map[y][x - 1]->dist = cur->dist + 1;
			map[y][x - 1]->disted = true;
			q.push(map[y][x - 1]);
		}
		if (walkable(x, y + 1) && !map[y + 1][x]->disted) {
			map[y + 1][x]->dist = cur->dist + 1;
			map[y + 1][x]->disted = true;
			q.push(map[y + 1][x]);
		}

	}




}



bool Floor::walkable(int x, int y) {

	if (x < 0 || x >= col || y < 0 || y >= row) return false;
	if ((*map[y][x]).attr == WALL) return false;
	else return true;

}



void debugg(Node* root) {
	Node* cur = root;
	while (cur != nullptr)
	{
		cout << cur->cel->loc << " ";
		cur = cur->child;
	}
	cout << endl;

}


#endif
