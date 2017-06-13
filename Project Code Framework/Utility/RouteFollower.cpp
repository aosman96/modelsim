#include "RouteFollower.h"
#include "../Components/Component.h"

Traverser::Traverser():start(NULL),loop_found(false){}

void Traverser::depth_first_search(Component* node,int level)
{
	vector<Component*> neigbhours;
	if(visited_set.find(node)!=visited_set.end()){ //Mean that the node is in the visited set
		loop_found=true;
		return;
	}

	if(node->getLevel()==level)  //No need to re porccess this again
		return;

	visited_set.insert(node);
	master_visited_set.insert(node);

	neigbhours=node->Next();
	node->setLevel(level);

	for(auto& N:neigbhours) 
		depth_first_search(N,level+1);
			
	visited_set.erase(node);  //backtracking here, clear visit for subroute(s)
}

void Traverser::set_starting_point(Component* __start)
{
	start=__start;
}

int Traverser::Loop_detect()
{
	if(start)
		depth_first_search(start);
	return loop_found? FEEDBACK:NO_ERRORS;
}

int Traverser::Get_NumberOf_Visited_Components()
{
	return master_visited_set.size();
}

Traverser::~Traverser(){}