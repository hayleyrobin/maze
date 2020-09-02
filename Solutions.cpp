/*
Name: Hayley Robinson
Class: CSCI 235
Instructor: Professor Oyewole Oyekoya
Project 4: The objective for this project is to find the shortest path from start-point to end-point of a general link-based maze using the following algorithms: Depth-First Search, Breadth-First Search, and Dead-End Filling.
*/
#include "Maze.cpp"

#include <stack>
#include <queue> 
#include <algorithm>  //reverse
#include <utility> //make pair
using namespace std;

namespace solutions
{

int getNumberOfWalls(MazeNode *a_node)
{
    int wall_counter = 0;
    for (directions::nesw dir = directions::NORTH; dir <= directions::WEST; dir = directions::nesw(dir + 1))
    {
        if (a_node->getDirectionNode(dir) == nullptr || a_node->getDirectionNode(dir)->isWall() || a_node->getDirectionNode(dir)->isVisited())
        {
            wall_counter++;
        }
    }
    return wall_counter;
}

bool canTravel(MazeNode *a_node)
{
    if (a_node == nullptr ||a_node->isVisited() || a_node->isWall()) //checks if node points to nothing, is visited or is a wall
    {
        return false;
    }
    return true;
}


std::vector<MazeNode> solveDFS(Maze &a_maze)
{
    std::vector<MazeNode> path1;    // create vector to return the shortest path
    stack<MazeNode> stack1;     //a new empty stack
    
    MazeNode *firstnode = a_maze.getFirstNode(); //get first node
    firstnode->setVisited(); //mark origin node as visited
    
    
    MazeNode *currentnode = a_maze.getCurrentNode(); //get current node
    MazeNode *lastnode = a_maze.getLastNode(); // get last node

    stack1.push(*firstnode);  //pushes first node into stack

    while(!stack1.empty())  // loop until the stack is empty
    {
        if(currentnode == lastnode)  //base case: if the current node is last node
        {
            while(!stack1.empty()) // until stack is empty
            {
                path1.push_back(stack1.top());  // push nodes into vector
                stack1.pop(); // pop nodes off of stack to end while loop
            }
            std::reverse(path1.begin(),path1.end()); //reverse order
            return path1; // return vector that holds the path nodes from start-point to end-point
        }
        
        if(solutions::canTravel(currentnode->getDirectionNode(directions::NORTH))) //if node can travel north
        {
            currentnode = currentnode->getDirectionNode(directions::NORTH);  //sets current to new node in direction
            currentnode->setVisited();                                       //mark as visited
            stack1.push(*currentnode);                                       //push node onto stack

        }
        else if(solutions::canTravel(currentnode->getDirectionNode(directions::EAST))) //if node can travel east
        {
            currentnode = currentnode->getDirectionNode(directions::EAST);  //sets current to new node in direction 
            currentnode->setVisited();                                       //mark as visited
            stack1.push(*currentnode);                                       //push node onto stack
        }
        else if(solutions::canTravel(currentnode->getDirectionNode(directions::SOUTH))) //if node can travel south
        {
            currentnode = currentnode->getDirectionNode(directions::SOUTH);  //sets current to new node in direction
            currentnode->setVisited();                                       //mark as visited
            stack1.push(*currentnode);                                       //push node onto stack
        }
        else if(solutions::canTravel(currentnode->getDirectionNode(directions::WEST))) //if node can travel west
        {
            currentnode = currentnode->getDirectionNode(directions::WEST);  //sets current to new node in direction 
            currentnode->setVisited();                                       //mark as visited
            stack1.push(*currentnode);                                       //push node onto stack
        }
        else                                                                 //backtracking
        {                                                                    //if node cant go in any direction
            stack1.pop();                                                    //pop node off of stack
            currentnode = &stack1.top();                                     //set current node to address of last node in stack
        }
    }
    
    return path1; //return vector of path taken
}



std::vector<MazeNode > solveBFS(Maze &a_maze)
{
    queue<MazeNode> queue2; //create a queue
    std::vector<MazeNode> path2; //create new vector to hold path
    std::vector<std::pair<MazeNode , MazeNode> > familypath; //create new vector to hold path of family nodes
    
    stack<MazeNode> holder; //stack to temporarily hold nodes

    MazeNode *firstnode = a_maze.getFirstNode();    //get first node
    firstnode->setVisited();    //mark origin node as visited
    

    MazeNode *currentnode = a_maze.getCurrentNode(); //get current node
    MazeNode *lastnode = a_maze.getLastNode(); // get last node
    MazeNode *newnode = currentnode; // pointer to get neighbors of current node


    queue2.push(*firstnode); //add start node to queue
    path2.push_back(*firstnode); //adding node to path

    
    while(newnode != lastnode) //while neighbor node does not equal last node
    {
        
        for(directions::nesw dir = directions::NORTH; dir <= directions::WEST; dir = directions::nesw(dir + 1)) //loop through different directions
        {
        
            if((solutions::canTravel(currentnode->getDirectionNodeArray()[dir]))) //if cantravel to node in this direction
            {
                MazeNode current = *currentnode; //store current node poisition

                newnode = currentnode->getDirectionNode(dir); //points to neighbor
                MazeNode next = *newnode; //store next node position
                
                queue2.push(*newnode);  //adds neighbor to queue
                if(!newnode->isVisited()) //if node isnt visited
                {
                    newnode->setVisited(); //set visited
                    //vector <pair <MazeNode parent, MazeNode child>>
                    familypath.push_back(std::make_pair(current,next)); //make pair of current node and next node
                
                }
            }
        }
        //after doing in all 4 directions
        queue2.pop(); //pop current from queue
        currentnode = &queue2.front(); //and change currentnode to whats now at front of queue
    }
    
    currentnode = newnode; //set currentnode to lastnode
        
    for (auto i = familypath.rbegin(); i != familypath.rend(); ++i ) //iterate through the last element to first element of family path
    {
        if(i->second.getStrPos() == currentnode->getStrPos()) //if child element is the same node as currentnode
        {
            holder.push(*currentnode); //add to stack 
            currentnode = &i->first; //set currentnode to next child
        }
    }
        
    while(!holder.empty()) //while traversing through stack
    {
        path2.push_back(holder.top()); //add to final path
        holder.pop(); //pop off of stack
    }
    
    return path2; //return final path
}


std::vector<MazeNode> solveDEF(Maze &a_maze)
{   
   
    std::vector<MazeNode> path3; //create vector to return
    stack<MazeNode*> stack3; //create stack of pointer to hold dead-ends

    MazeNode *firstnode = a_maze.getFirstNode();    //get first node
    MazeNode *currentnode = a_maze.getCurrentNode(); //get current node
    MazeNode *lastnode = a_maze.getLastNode(); // get last node

    for(auto i :a_maze.getNodes()) //auto iteration through all the nodes in the maze
    {
        if(getNumberOfWalls(&i) >= 3 && !i.isWall() && i.getStrPos() != lastnode->getStrPos() && i.getStrPos() != firstnode->getStrPos()) //if node isnt first/last node and isnt a wall and has 3 or more walls
        {
            stack3.push(a_maze.contains(i.getPos())); //push deadend into stack
            a_maze.contains(i.getPos())->setWall(); //set it to wall
        }
    }
    currentnode = stack3.top(); //point to deadend in stack
    while(!stack3.empty()) //loop until there are no dead ends
    {
        currentnode =stack3.top(); //set current node to dead end adter each iteration
        stack3.pop(); //pop it off stack
        for(directions::nesw dir = directions::NORTH; dir <= directions::WEST; dir = directions::nesw(dir + 1)) //loop through different directions
        {
          if(solutions::getNumberOfWalls(currentnode->getDirectionNodeArray()[dir]) >= 3  && canTravel(currentnode->getDirectionNode(dir))) //if can travel to node and node has 3 or more walls
          {
              currentnode->getDirectionNode(dir)->setWall(); //set it to wall
              stack3.push(currentnode->getDirectionNode(dir)); //push neighbor onto stack
          }
        }
    }
    path3 = solveDFS(a_maze); //get path with no walls
    return path3; //return vector of path

}

std::vector<MazeNode> solveCustom(Maze &a_maze)
{
    std::vector<MazeNode> path4;
    stack<MazeNode> stack1;     //a new empty stack
    
    MazeNode *firstnode = a_maze.getFirstNode(); //get first node
    firstnode->setVisited(); //mark origin node as visited
    
    
    MazeNode *currentnode = a_maze.getCurrentNode(); //get current node
    MazeNode *lastnode = a_maze.getLastNode(); // get last node

    stack1.push(*firstnode);  //pushes first node into stack

    while(!stack1.empty())  // loop until the stack is empty
    {
        if(currentnode == lastnode)  //base case: if the current node is last node
        {
            while(!stack1.empty()) // until stack is empty
            {
                path4.push_back(stack1.top());  // push nodes into vector
                stack1.pop(); // pop nodes off of stack to end while loop
            }
            std::reverse(path4.begin(),path4.end()); //reverse order
            return path4; // return vector that holds the path nodes from start-point to end-point
        }
        
        if(solutions::canTravel(currentnode->getDirectionNode(directions::NORTH))) //if node can travel north
        {
            currentnode = currentnode->getDirectionNode(directions::NORTH);  //sets current to new node in direction
            currentnode->setVisited();                                       //mark as visited
            stack1.push(*currentnode);                                       //push node onto stack

        }
        else if(solutions::canTravel(currentnode->getDirectionNode(directions::EAST))) //if node can travel east
        {
            currentnode = currentnode->getDirectionNode(directions::EAST);  //sets current to new node in direction 
            currentnode->setVisited();                                       //mark as visited
            stack1.push(*currentnode);                                       //push node onto stack
        }
        else if(solutions::canTravel(currentnode->getDirectionNode(directions::SOUTH))) //if node can travel south
        {
            currentnode = currentnode->getDirectionNode(directions::SOUTH);  //sets current to new node in direction
            currentnode->setVisited();                                       //mark as visited
            stack1.push(*currentnode);                                       //push node onto stack
        }
        else if(solutions::canTravel(currentnode->getDirectionNode(directions::WEST))) //if node can travel west
        {
            currentnode = currentnode->getDirectionNode(directions::WEST);  //sets current to new node in direction 
            currentnode->setVisited();                                       //mark as visited
            stack1.push(*currentnode);                                       //push node onto stack
        }
        else                                                                 //backtracking
        {                                                                    //if node cant go in any direction
            stack1.pop();                                                    //pop node off of stack
            currentnode = &stack1.top();                                     //set current node to address of last node in stack
        }
    }

    return path4; // return path
}

} // namespace solutions

