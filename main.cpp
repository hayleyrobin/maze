#include "Solutions.cpp"

int main()
{
    Maze maze1("maze_1.csv");

    //cout << "Maze 1 data : "<<endl;
    //cout << "Length: " << maze1.getLength() <<endl;
    //cout << "Width: " << maze1.getWidth() <<endl;
    //cout << "Size: " << maze1.getSize() <<endl;
    
    //std::pair<int,int> p1(1,0);
   // MazeNode *anode = maze1.contains(p1); //seeing if maze contains node
   // cout << "Contains? : " << *anode <<endl;
   //std::pair<int, int> dir_node = node1->getPos(); 
    //cout << dir_node.first << dir_node.second << endl;

    MazeNode *startnode = maze1.getFirstNode(); 
    //cout << "First node: " << *startnode <<endl; //first node

    MazeNode *lastnode = maze1.getLastNode(); //gets location of last node
    //cout << "Last node: " << *lastnode <<endl;

    MazeNode *currentnode = maze1.getCurrentNode(); //gets location of current node
    //cout << "Current node: " << *currentnode <<endl;
 
    cout <<"Deep First Search: " << endl;
    std::vector<MazeNode> vector1 = solutions::solveDFS(maze1);
    for(int i = 0; i< vector1.size(); i++)
    {
        cout<< vector1.at(i) << endl;
    }

    cout <<"Breadth First Search: " << endl;
    std::vector<MazeNode>  vector2= solutions::solveBFS(maze1);
    for(int i = 0; i< vector2.size(); i++)
    {
      cout<< vector2.at(i) << endl;
    }
      
    std::vector<MazeNode> vector3 = solutions::solveDEF(maze1);
    for(int i = 0; i< vector3.size(); i++)
    {
      cout<< vector3.at(i) << endl;
    }

    Maze maze2("maze_2.csv");

    cout << "Maze 2 data : "<<endl;
    cout << "Length: " << maze2.getLength() <<endl;
    cout << "Width: " << maze2.getWidth() <<endl;
    cout << "Size: " << maze2.getSize() <<endl;
    MazeNode *node2 = maze2.getFirstNode(); 
    cout << "First node: " << *node2 <<endl; //first node

    MazeNode *lastnode2 = maze2.getLastNode(); //gets location of last node
    cout << "Last node: " << *lastnode2 <<endl;

    std::vector<MazeNode> vector4 = solutions::solveDFS(maze2);
    
    cout <<"Deep First Search: " << endl;
    for(int i = 0; i< vector4.size(); i++)
    {
        cout<< vector4.at(i) << endl;
    };
    cout <<"Breadth First Search: " << endl;
    std::vector<MazeNode>  vector5 = solutions::solveBFS(maze2);
    for(int i = 0; i< vector5.size(); i++)
    {
      cout<< vector5.at(i) << endl;
    };

    cout << "Dead-End Filling: " << endl;
    std::vector<MazeNode>  vector6 = solutions::solveBFS(maze2);
    for(int i = 0; i< vector6.size(); i++)
    {
      cout<< vector6.at(i) << endl;
    }

    Maze maze3("maze_3.csv");

    cout << "Maze 3 data : "<<endl;
    cout << "Length: " << maze3.getLength() <<endl;
    cout << "Width: " << maze3.getWidth() <<endl;
    cout << "Size: " << maze3.getSize() <<endl;

   MazeNode *node3 = maze3.getFirstNode(); 
    cout << "First node: " << *node3 <<endl; //first node

    MazeNode *lastnode3 = maze3.getLastNode(); //gets location of last node
    cout << "Last node: " << *lastnode3 <<endl;

    MazeNode *current = maze3.getCurrentNode(); //gets location of current node
    cout << "Current node: " << *current <<endl;

    cout <<"Deep First Search: " << endl;
    std::vector<MazeNode> vector7 = solutions::solveDFS(maze3);
    for(int i = 0; i< vector7.size(); i++)
    {
      cout<< vector7.at(i) << endl;
    }
   
    cout <<"Breadth First Search: " << endl;
    std::vector<MazeNode>  vector8 = solutions::solveBFS(maze3);
    for(int i = 0; i< vector8.size(); i++)
    {
      cout<< vector8.at(i) << endl;
    }

    cout << "Dead-End Filling: " << endl;
    std::vector<MazeNode>  vector9 = solutions::solveBFS(maze3);
    for(int i = 0; i< vector9.size(); i++)
    {
      cout<< vector9.at(i) << endl;
    }

   
    return 0;
    
}