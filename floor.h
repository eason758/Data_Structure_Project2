#pragma once

#ifndef FLOOR
#define FLOOR

#include "class.h"

#define MAX(a,b) ((a>b) ? a : b ) 

void Floor::init(int r, int c, int b) {

	finish = false;
	row = r;
	col = c;
	battery = b;

}


void Floor::clear(){

	rear = new Node(home);

	path.push_back(home->loc);

	map[home->loc.y][home->loc.x]->visited = 1;

	evaluate(home);

	cur_step = 0;

	int i = 0;
	do
	{
		walk();
		if(!finish)
			walk_back();
	} while (!finish);
}


void Floor::walk() {

	while (cur_step < battery/2)
	{
		cur_step++;

		set_node_cost(rear, false);
		set_node_max_cost(rear, false);
		
		if (rear->max_cost == 0) {

			// 全都走過了
			if (unclean_size <= 0) {
				stack<coor> tmp_stack = stack_go_home(rear);
				while (!tmp_stack.empty())
				{
					path.push_back(tmp_stack.top());
					tmp_stack.pop();
				}

				finish = true;
				break;
			}
			else {
				while (!branchable.empty())
				{
					if ((map[branchable.top()->loc.y][branchable.top()->loc.x + 1]->visited == 1 ||
						!walkable(branchable.top()->loc.x + 1, branchable.top()->loc.y)) &&
						(map[branchable.top()->loc.y - 1][branchable.top()->loc.x]->visited == 1 ||
							!walkable(branchable.top()->loc.x, branchable.top()->loc.y - 1)) &&
							(map[branchable.top()->loc.y][branchable.top()->loc.x - 1]->visited == 1 ||
								!walkable(branchable.top()->loc.x - 1, branchable.top()->loc.y)) &&
								(map[branchable.top()->loc.y + 1][branchable.top()->loc.x]->visited == 1 ||
									!walkable(branchable.top()->loc.x, branchable.top()->loc.y + 1))) {
						branchable.pop();

					}
					else break;
				}
				stack<coor> tmp_stack = stack_go_to(rear, branchable.top());
				if (tmp_stack.empty()) {
					tmp_stack = stack_go_home(rear);
					while (!tmp_stack.empty())
					{
						path.push_back(tmp_stack.top());
						tmp_stack.pop();
					}
				}
				else {
					while (!tmp_stack.empty())
					{
						cur_step++;
						path.push_back(tmp_stack.top());
						tmp_stack.pop();
					}
					cur_step--;
				}
				rear = new Node(map[path.back().y][path.back().x]);
			}


		}
		else {

			int x = rear->cel->loc.x;
			int y = rear->cel->loc.y;		// current cell position


			if ((rear->cost[0] > 0 && rear->cost[1] > 0) || (rear->cost[0] > 0 && rear->cost[2] > 0) || (rear->cost[0] > 0 && rear->cost[3] > 0) ||
				(rear->cost[1] > 0 && rear->cost[2] > 0) || (rear->cost[1] > 0 && rear->cost[3] > 0) || (rear->cost[2] > 0 && rear->cost[3] > 0)) {
				branchable.push(map[y][x]);
			}

			if (rear->cost[0] == rear->max_cost)
			{

				path.push_back(map[y][x + 1]->loc);

				// set cell branch_visit
				map[y][x + 1]->visited = 1;
				//set same level vector
				rear = new Node(map[y][x + 1]);

				unclean_size--;
				}
			else if (rear->cost[1] == rear->max_cost)
			{

				path.push_back(map[y - 1][x]->loc);

				// set cell branch_visit
				map[y - 1][x]->visited = 1;
				//set same level vector
				rear = new Node(map[y - 1][x]);

				unclean_size--;
					
			}
			else if (rear->cost[2] == rear->max_cost)
			{
				path.push_back(map[y][x - 1]->loc);

				// set cell branch_visit
				map[y][x - 1]->visited = 1;
				//set same level vector
				rear = new Node(map[y][x - 1]);

				unclean_size--;
			}
			else if (rear->cost[3] == rear->max_cost)
			{
				path.push_back(map[y + 1][x]->loc);

				// set cell branch_visit
				map[y + 1][x]->visited = 1;

				rear = new Node(map[y + 1][x]);

				unclean_size--;
			}
			
		}

	}


}

void Floor::walk_back() {

	while (rear->cel != home)
	{
		cur_step++;

		set_node_cost(rear, true);
		set_node_max_cost(rear, true);

		int x = rear->cel->loc.x;
		int y = rear->cel->loc.y;

		if (rear->max_cost == 0) {

			if ((walkable(x + 1, y) && map[y][x + 1]->cost > 0 && map[y][x + 1]->visited) || (walkable(x, y - 1) && map[y - 1][x]->cost > 0 && map[y - 1][x]->visited) ||
				(walkable(x - 1, y) && map[y][x - 1]->cost > 0 && map[y][x - 1]->visited) || (walkable(x, y + 1) && map[y + 1][x]->cost > 0 && map[y + 1][x]->visited))
			{
				branchable.push(map[y][x]);
			}
			
			// 全都走過了
			if (unclean_size <= 0) {

				stack<coor> tmp_stack = stack_go_home(rear);
				while (!tmp_stack.empty())
				{
					path.push_back(tmp_stack.top());
					tmp_stack.pop();
				}

				finish = true;
				break;
			}
			else {
				while (!branchable.empty())
				{
					
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

				stack<coor> tmp_stack = stack_go_to(rear, branchable.top());

				if (tmp_stack.empty()) {
					tmp_stack = stack_go_home(rear);
					while (!tmp_stack.empty())
					{
						path.push_back(tmp_stack.top());
						tmp_stack.pop();
					}
				}
				else {
					while (!tmp_stack.empty())
					{
						cur_step++;
						path.push_back(tmp_stack.top());
						tmp_stack.pop();
					}
					cur_step--;
				}
				rear = rear = new Node(map[path.back().y][path.back().x]);
			}
			
		}
		else {
			int x = rear->cel->loc.x;
			int y = rear->cel->loc.y;		// current cell position


			if ((walkable(x + 1, y) && map[y][x + 1]->cost > 0 && map[y][x + 1]->visited) || (walkable(x, y - 1) && map[y - 1][x]->cost > 0 && map[y - 1][x]->visited) ||
				(walkable(x - 1, y) && map[y][x - 1]->cost > 0 && map[y][x - 1]->visited) || (walkable(x, y + 1) && map[y + 1][x]->cost > 0 && map[y + 1][x]->visited))
			{
				branchable.push(map[y][x]);
			}

			if (rear->cost[0] == rear->max_cost)
			{
				path.push_back(map[y][x + 1]->loc);

				// set cell branch_visit
				map[y][x + 1]->visited = 1;
				//set same level vector
				rear = new Node(map[y][x + 1]);

				unclean_size--;
				
			}
			else if (rear->cost[1] == rear->max_cost)
			{
				path.push_back(map[y - 1][x]->loc);

				// set cell branch_visit
				map[y - 1][x]->visited = 1;
				//set same level vector
				rear = new Node(map[y - 1][x]);

				unclean_size--;
				
			}
			else if (rear->cost[2] == rear->max_cost)
			{
				path.push_back(map[y][x - 1]->loc);

				// set cell branch_visit
				map[y][x - 1]->visited = 1;
				//set same level vector
				rear = new Node(map[y][x - 1]);

				unclean_size--;
				
			}
			else if (rear->cost[3] == rear->max_cost )
			{
				path.push_back(map[y + 1][x]->loc);

				// set cell branch_visit
				map[y + 1][x]->visited = 1;
				//set same level vector
				rear = new Node(map[y + 1][x]);

				unclean_size--;
				
			}

		}

	}
	cur_step = 0;
}


stack<coor> Floor::stack_go_home(Node * cur) {

	int root_x = (cur)->cel->loc.x;
	int root_y = (cur)->cel->loc.y;


	Node* fake_root = new Node((cur)->cel, cur->parent);
	priority_queue<Node*, vector<Node*>, cmp> open;

	set<cell*> close = {};
	open.push(fake_root);

	vector<coor>  go_home_path;


	while (open.top()->cel != home)
	{
		Node * n = open.top();
		open.pop();
		int x = n->cel->loc.x;
		int y = n->cel->loc.y;

		int child = 0;
		if (walkable(x + 1, y) && !close.count(map[y][x + 1]))
		{
			n->childs[child] = new Node(map[y][x + 1], n);
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

	stack<coor> reverse_path;
	Node * cur_ = open.top();
	while (cur_ != nullptr)
	{
		reverse_path.push(cur_->cel->loc);
		cur_ = cur_->parent;
	}
	cur_step = 0;
	reverse_path.pop();
	
	return reverse_path;

}


// min_index use heap tree?(自己刻)


stack<coor> Floor::stack_go_to(Node* src, cell* dest) {

	Node* cur = src;

	int root_x = (cur)->cel->loc.x;
	int root_y = (cur)->cel->loc.y;

	Node* fake_root = new Node((cur)->cel);
	myheap open(dest->loc);


	set<cell*> close = {};


	open.push(fake_root);



	int min_index = 0;

	while (open.top()->cel != dest)
	{
		Node * n = open.top();
		open.pop();
		int x = n->cel->loc.x;
		int y = n->cel->loc.y;

		int child = 0;
		if (walkable(x + 1, y) && !close.count(map[y][x + 1]))
		{
			n->childs[child] = new Node(map[y][x + 1], n);
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
	
	stack<coor> reverve_path;
	cur = open.top();
	int dest_dist = open.top()->cel->dist;
	while (cur != nullptr)
	{
		reverve_path.push(cur->cel->loc);
		cur = cur->parent;
	}
	reverve_path.pop();


	int reserve_path_step = reverve_path.size();

	if (reserve_path_step + dest_dist > left_step()) return stack<coor> {};
	else {
		return reverve_path;
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


#endif
