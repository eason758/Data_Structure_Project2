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
	cur_step = 0;


	map = new cell**[row];
	for (int i = 0; i < row; i++) map[i] = new cell*[col];

	
	char block;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cin >> block;
			if (block == '1') map[i][j] = new cell(coor(i, j), WALL, -1);
			else if(block == '0') 
			{
				map[i][j] = new cell(coor(i, j), ROAD, 0);
				unclean.push_back(map[i][j]);
			}
			else home = map[i][j] = new cell(coor(i, j), HOME, 0);
		}
	}


	PROCESS_START = clock();











}



//在此假設battery無限 (battery有限之後再改)
//貪婪:每條走可以把最多格填滿就是最好路徑
//步驟:
//把所有可以走的cell 都記起來(在哪裡 這是第幾步) 然後比較彼此之間的數值
//數值:(跟R越遠越好 - 是否走過*10000)  問題:怎麼知道他跟R的距離? 每次都用A*?
//
//取最大值的那幾個當作child, 記錄在queue裡面
//
//while loop取queue的所有Node 每一個Node個別再執行一次(這個while在 clear()中)
//他們所產生的child 都比較彼此之間的數值(亦即 同一個height 的node 都比較彼此的數值
//來決定要不要留)
//
//如果每個node都只能走到"走過"的格子 就
//
//
//
//
//
//while 直到 queue空了
//
//最後順利到達R的(如果有非最大值的child 就會死在路中央) 記錄他從leaf到root的step
//如果是 min 就紀錄順序
//繼續找有沒有其他順利到達R的 然後再執行前兩行


void Floor::clear(){


	distance_evaluation(home);
	
	tree.set_root(new Node(home));
	tree.leaves.push_back(tree.root);
	tree.total_branch = 1;
	tree.cur_branch = 1;

	
	do
	{
		cur_step = 0;
		walk();
		//walk_back();
	} while (0);
		//!finish);

}

void Floor::walk() {

			/*
				!!! 
					cost < max_max 的branch到底該不該留?
														!!!
															*/




	

	
	/*
	
		要寫walkback 後的開始 (即一開始就find emp 或找到新路)
																*/
	/*
	
		walk_back可以延續 tree->branch
											*/
	while (battery--)
	{
		cur_step++;
		//cout << "total branch : " << tree.total_branch << endl;

		int  max_max_cost = 0;
		int new_branch = 0;

		vector<Node*> new_leaves;

		// set node cost and check whether max_max = 0
		for (int i = 0; i < tree.cur_branch; i++)
		{
			set_node_cost(tree.leaves[i]);
			set_node_max_cost(tree.leaves[i]);
			
			max_max_cost = MAX(max_max_cost, tree.leaves[i]->max_cost);
			/*
			cout << "i: " << i << "  tree.leaves[i].loc: " << tree.leaves[i]->cel->loc
				<< " max: " << tree.leaves[i]->max_cost << endl;

			cout << "branch number: ";
			for (size_t j = 0; j < tree.leaves[i]->branch.size(); j++)
				cout << tree.leaves[i]->branch[j] << " ";
			cout << endl;
			cout << "right cell set: ";
			if(walkable(x + 1, y))
			for (auto j = map[tree.leaves[i]->cel->loc.y][tree.leaves[i]->cel->loc.x + 1]->visited_branches.begin(); j != map[tree.leaves[i]->cel->loc.y][tree.leaves[i]->cel->loc.x + 1]->visited_branches.end(); j++)
				cout << *j << " ";
			cout << endl;
			cout << "up cell set: ";
			if(walkable(x, y - 1))
			for (auto j = map[tree.leaves[i]->cel->loc.y - 1][tree.leaves[i]->cel->loc.x]->visited_branches.begin(); j != map[tree.leaves[i]->cel->loc.y - 1][tree.leaves[i]->cel->loc.x]->visited_branches.end(); j++)
				cout << *j << " "; 
			cout << endl;
			cout << "left cell set: ";
			if(walkable(x - 1, y))
			for (auto j = map[tree.leaves[i]->cel->loc.y][tree.leaves[i]->cel->loc.x - 1]->visited_branches.begin(); j != map[tree.leaves[i]->cel->loc.y][tree.leaves[i]->cel->loc.x - 1]->visited_branches.end(); j++)
				cout << *j << " "; 
			cout << endl;
			cout << "down cell set: ";
			if(walkable(x, y + 1))
			for (auto j = map[tree.leaves[i]->cel->loc.y + 1][tree.leaves[i]->cel->loc.x]->visited_branches.begin(); j != map[tree.leaves[i]->cel->loc.y + 1][tree.leaves[i]->cel->loc.x]->visited_branches.end(); j++)
				cout << *j << " ";

			cout << endl << endl;

			for (Node* cur = tree.leaves[i] ; cur != nullptr ; cur = cur->parent)
				cout << cur->cel->loc << " ";

			cout << endl << endl;
			*/

		}
		


		// !!!!!要處理同高度 有人到home 有沒結束在其他地方的情況(max_max都是0)
		// !!!!!要處理"只取最短的 go to emp" 以減少branch
		if (max_max_cost == 0) {

			bool go_out = false;

			int* steps = new int[tree.cur_branch];

			emp_min_step = 1000000;

			for (int i = 0; i < tree.cur_branch; i++) {
							// path from leaves to emp node
				

				Node** n = find_emp_cell(tree.leaves[i]);
				
				// 全都走過了
				if (n == nullptr) {
					cout << "QQQQQQQQQQQQQQQQQQQQ!" << endl;
					finalNode = tree.leaves[i];
					finish = true;
					//go home (A*)
					go_out = true;
					break;
				}

				steps[i] = n[2]->max_cost;
				if (steps[i] < emp_min_step)emp_min_step = steps[i];


				tree.leaves[i]->child[0] = n[0];
				n[0]->parent = tree.leaves[i];
				n[1]->branch = tree.leaves[i]->branch;
				tree.leaves[i] = n[1];



				//cout << "visited_branches: " << tree.leaves[i]->cel->visited_branches[0]<<endl;
			}
			if (go_out)break;

			for (int i = 0; i < tree.cur_branch; i++) {

				if (steps[i] == emp_min_step) {

					new_leaves.push_back(tree.leaves[i]);
					// set cell branch_visit
					tree.leaves[i]->cel->visited_branches.insert(tree.leaves[i]->branch.back());
					new_branch++;
				}
			}
			
		}
		else {

			//cout << endl;
			//cout<< "total_branch : " << tree.total_branch << endl << endl;

			
			for (int i = 0 ; i < tree.cur_branch; i++)
			{
				if (tree.leaves[i]->max_cost == max_max_cost) {
					int x = tree.leaves[i]->cel->loc.x;
					int y = tree.leaves[i]->cel->loc.y;		// current cell position

					int child = 0;
					bool go_branch = false;

					if ((tree.leaves[i]->cost[0] == tree.leaves[i]->cost[1] && tree.leaves[i]->cost[1] == tree.leaves[i]->max_cost) ||
						(tree.leaves[i]->cost[0] == tree.leaves[i]->cost[2] && tree.leaves[i]->cost[2] == tree.leaves[i]->max_cost) ||
						(tree.leaves[i]->cost[0] == tree.leaves[i]->cost[3] && tree.leaves[i]->cost[3] == tree.leaves[i]->max_cost) ||
						(tree.leaves[i]->cost[1] == tree.leaves[i]->cost[2] && tree.leaves[i]->cost[2] == tree.leaves[i]->max_cost) ||
						(tree.leaves[i]->cost[1] == tree.leaves[i]->cost[3] && tree.leaves[i]->cost[3] == tree.leaves[i]->max_cost) ||
						(tree.leaves[i]->cost[2] == tree.leaves[i]->cost[3] && tree.leaves[i]->cost[3] == tree.leaves[i]->max_cost))
					{
						go_branch = true;
					}

					if (tree.leaves[i]->cost[0] == max_max_cost)
					{// one of max_grid

						//set child & parent
						tree.leaves[i]->child[child] =
							new Node(map[y][x + 1], tree.leaves[i]);

						// set branch number
						tree.leaves[i]->child[child]->branch = tree.leaves[i]->branch;;
						if (go_branch) {
							tree.total_branch++;
							tree.leaves[i]->child[child]->branch.push_back(tree.total_branch);

						}
						// set cell branch_visit
						tree.leaves[i]->child[child]->cel->visited_branches.insert(tree.leaves[i]->child[child]->branch.back());

						//set same level vector
						new_leaves.push_back(tree.leaves[i]->child[child++]);

						new_branch++;
					}

					if (tree.leaves[i]->cost[1] == max_max_cost)
					{// one of max_grid

						//set child & parent
						tree.leaves[i]->child[child] =
							new Node(map[y - 1][x], tree.leaves[i]);

						// set branch number
						tree.leaves[i]->child[child]->branch = tree.leaves[i]->branch;;
						if (go_branch) {
							tree.total_branch++;
							tree.leaves[i]->child[child]->branch.push_back(tree.total_branch);

						}

						// set cell branch_visit
						tree.leaves[i]->child[child]->cel->visited_branches.insert(tree.leaves[i]->child[child]->branch.back());

						//set same level vector
						new_leaves.push_back(tree.leaves[i]->child[child++]);

						new_branch++;
					}

					if (tree.leaves[i]->cost[2] == max_max_cost)
					{/// one of max_grid

						//set child & parent
						tree.leaves[i]->child[child] =
							new Node(map[y][x - 1], tree.leaves[i]);

						// set branch number
						tree.leaves[i]->child[child]->branch = tree.leaves[i]->branch;;
						if (go_branch) {
							tree.total_branch++;
							tree.leaves[i]->child[child]->branch.push_back(tree.total_branch);

						}

						// set cell branch_visit
						tree.leaves[i]->child[child]->cel->visited_branches.insert(tree.leaves[i]->child[child]->branch.back());

						//set same level vector
						new_leaves.push_back(tree.leaves[i]->child[child++]);

						new_branch++;
					}

					if (tree.leaves[i]->cost[3] == max_max_cost)
					{// one of max_grid

						//set child & parent
						tree.leaves[i]->child[child] =
							new Node(map[y + 1][x], tree.leaves[i]);

						// set branch number
						tree.leaves[i]->child[child]->branch = tree.leaves[i]->branch;;
						if (go_branch) {
							tree.total_branch++;
							tree.leaves[i]->child[child]->branch.push_back(tree.total_branch);

						}

						// set cell branch_visit
						tree.leaves[i]->child[child]->cel->visited_branches.insert(tree.leaves[i]->child[child]->branch.back());

						//set same level vector
						new_leaves.push_back(tree.leaves[i]->child[child++]);

						new_branch++;
					}

				}
			}
			
			
			
		}
		
		tree.leaves = new_leaves;
		tree.cur_branch = new_branch;
		

	}


}

void Floor::distance_evaluation(cell* root) {
	
	queue<cell*> q;
	q.push(root);
	root->cost = 0;

	while (!q.empty())
	{

		cell* cur = q.front();
		cur->evaluated = true;
		q.pop();

		int x = cur->loc.x;
		int y = cur->loc.y;

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


}


//[0] == head ; [1] = rear ; [2] = steps
Node** Floor::find_emp_cell(Node* root) {
	
	int root_x = root->cel->loc.x;
	int root_y = root->cel->loc.y;
	vector<int> branch = root->branch;
	Node* fake_root = new Node(root->cel);

	Node* tmp_node = fake_root;
	queue<Node*> q;
	q.push(fake_root);



	bool** fake_map = new bool*[row];
	for (int i = 0; i < row; i++) {
		fake_map[i] = new bool[col];
		for (int j = 0; j < col; j++) {
			fake_map[i][j] = false;
		}
	}
	fake_map[root_y][root_x] = true;


	int step = 0;
	bool found = false;
	while (!q.empty())
	{
		step++;
		int child = 0;
		tmp_node = q.front();
		int x = tmp_node->cel->loc.x;
		int y = tmp_node->cel->loc.y;
		q.pop();

		if (walkable(x + 1, y) && fake_map[y][x + 1] == false) {
			fake_map[y][x + 1] = true;
			vector<int>::iterator it = branch.begin();
			while ( it != branch.end() ) {
				if (map[y][x + 1]->visited_branches.count(*it)) {
					tmp_node->child[child] = new Node(map[y][x + 1], tmp_node);
					q.push(tmp_node->child[child++]);
					break;
				}
				it++;
			}
			//代表是emp cell;
			if (it == branch.end()) {
				tmp_node->child[0] = new Node(map[y][x + 1], tmp_node);
				tmp_node = tmp_node->child[0];
				found = true;
				break;
			}
		}

		if (walkable(x, y - 1) && fake_map[y - 1][x] == false) {
			fake_map[y - 1][x] = true;
			vector<int>::iterator it = branch.begin();
			while (it != branch.end()) {
				if (map[y - 1][x]->visited_branches.count(*it)) {
					tmp_node->child[child] = new Node(map[y - 1][x], tmp_node);
					q.push(tmp_node->child[child++]);
					break;
				}
				it++;
			}
			//代表是emp cell;
			if (it == branch.end()) {
				tmp_node->child[0] = new Node(map[y - 1][x], tmp_node);
				tmp_node = tmp_node->child[0];
				found = true;
				break;
			}
		}

		if (walkable(x - 1, y) && fake_map[y][x - 1] == false) {
			fake_map[y][x - 1] = true;
			vector<int>::iterator it = branch.begin();
			while (it != branch.end()) {
				if (map[y][x - 1]->visited_branches.count(*it)) {
					tmp_node->child[child] = new Node(map[y][x - 1], tmp_node);
					q.push(tmp_node->child[child++]);
					break;
				}
				it++;
			}
			//代表是emp cell;
			if (it == branch.end()) {
				tmp_node->child[0] = new Node(map[y][x - 1], tmp_node);
				tmp_node = tmp_node->child[0];
				found = true;
				break;
			}
		}

		if (walkable(x, y + 1) && fake_map[y + 1][x] == false) {
			fake_map[y + 1][x] = true;
			vector<int>::iterator it = branch.begin();
			while (it != branch.end()) {
				if (map[y + 1][x]->visited_branches.count(*it)) {
					tmp_node->child[child] = new Node(map[y + 1][x], tmp_node);
					q.push(tmp_node->child[child++]);
					break;
				}
				it++;
			}
			//代表是emp cell;
			if (it == branch.end()) {
				tmp_node->child[0] = new Node(map[y + 1][x], tmp_node);
				tmp_node = tmp_node->child[0];
				found = true;
				break;
			}
		}

	}
	
	//代表有找到emp
	if (found) {
		//cout << "found: " << tmp_node ->cel->loc<< endl;
		//delete 除了 child[0]的branch
		Node** n = new Node*[3];
		n[1] = tmp_node;
		n[0] = reverse_tree(tmp_node)->child[0];
		n[2] = new Node();
		n[2]->max_cost = step;
		return n;
	}
	else {
		return nullptr;
	}
}

bool Floor::walkable(int x, int y) {

	if (x < 0 || x >= col || y < 0 || y >= row) return false;
	if ((*map[y][x]).attr == WALL) return false;
	else return true;

}


#endif
