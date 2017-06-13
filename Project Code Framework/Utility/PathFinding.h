/*
#pragma once
#include "../GUI/UI_info.h"
#include "../GUI/Output.h"
#include <vector>
#include <unordered_map>
#include <map>
#include <queue>
#include <math.h>

#define INFINITE UI.height*UI.width+1  //NO route ever should be equal to this length
#define GRID_SIZE 20 

struct Point
{
	int x,y;
	Point(int _x,int _y):x(_x),y(_y){}
};

class GridCell
{
	int G,H,F;
	Point topcorner;
	int local_cost(Output* out);
	friend struct compartor;
public:
	GridCell(int gCost=INFINITE,int hCost=INFINITE,Point top=Point(-1,-1)):G(gCost),H(hCost),topcorner(top){}
	int G_Value();			 //--> Used to calculate G score 
	int H_Value(Point end); //--> Used to calculate heuristic cost
	int F_Value();			//F(NODE)=G(NODE)+H(NODE)		
	void set_G(int gscore){G=gscore;}
};

struct compartor
{
	bool operator()(const GridCell& c1,const GridCell& c2)
	{
		return c1.F<c2.F;
	}
};

class PathFinder
{
private:
	unordered_map <long,GridCell*> closedSet;  //The key is x*1000+y
	map <long,GridCell*> comefrom;
	map <long,GridCell*,compartor> OpenSet;
	Point start;
	Point end;
	Point current;
	Output *out;

	GridCell* getlowest() 
	{
		pair<long, GridCell*> min = *min_element(OpenSet.begin(), OpenSet.end(), compartor());
		return min.second; 
	}

public:
	PathFinder(GraphicsInfo start_end,Output* pOUT)
		:start(start_end.x1,start_end.y1),end(start_end.x2,start_end.y2),out(pOUT),current(start)
	{
		//construct the OpenSet map here 
	}
	bool FindPath() //returns true if there is a possible path and saves that path
	{
		OpenSet.at(start.x*1000+start.y)->set_G(0);//start point has a G cost of ZERO
		while(!OpenSet.empty())
		{

		}

	}
	vector <GraphicsInfo> reconstruct_path(); 
	~PathFinder();
};

*/
/*
function A*(start, goal)
    // The set of nodes already evaluated.
    closedSet := {}
    // The set of currently discovered nodes still to be evaluated.
    // Initially, only the start node is known.
    openSet := {start}
    // For each node, which node it can most efficiently be reached from.
    // If a node can be reached from many nodes, cameFrom will eventually contain the
    // most efficient previous step.
    cameFrom := the empty map

    // For each node, the cost of getting from the start node to that node.
    gScore := map with default value of Infinity
    // The cost of going from start to start is zero.
    gScore[start] := 0 
    // For each node, the total cost of getting from the start node to the goal
    // by passing by that node. That value is partly known, partly heuristic.
    fScore := map with default value of Infinity
    // For the first node, that value is completely heuristic.
    fScore[start] := heuristic_cost_estimate(start, goal)

    while openSet is not empty
        current := the node in openSet having the lowest fScore[] value
        if current = goal
            return reconstruct_path(cameFrom, current)

        openSet.Remove(current)
        closedSet.Add(current)
        for each neighbor of current
            if neighbor in closedSet
                continue		// Ignore the neighbor which is already evaluated.
            // The distance from start to a neighbor
            tentative_gScore := gScore[current] + dist_between(current, neighbor)
            if neighbor not in openSet	// Discover a new node
                openSet.Add(neighbor)
            else if tentative_gScore >= gScore[neighbor]
                continue		// This is not a better path.

            // This path is the best until now. Record it!
            cameFrom[neighbor] := current
            gScore[neighbor] := tentative_gScore
            fScore[neighbor] := gScore[neighbor] + heuristic_cost_estimate(neighbor, goal)

    return failure

function reconstruct_path(cameFrom, current)
    total_path := [current]
    while current in cameFrom.Keys:
        current := cameFrom[current]
        total_path.append(current)
    return total_path
	
*/	