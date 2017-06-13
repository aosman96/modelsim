#ifndef _ROUTE_FOLLOWER_
#define _ROUTE_FOLLOWER_

#include "../ApplicationManager.h"
#include <unordered_set>
using std::unordered_set;

class Traverser
{
	Component* start;
	unordered_set<Component*> visited_set;
	unordered_set<Component*> master_visited_set;
	void depth_first_search(Component* node,int level=0);
	bool loop_found;
public:
	Traverser();
	void set_starting_point(Component* __start);
	int Loop_detect();
	int Get_NumberOf_Visited_Components();
	~Traverser();
};

#endif