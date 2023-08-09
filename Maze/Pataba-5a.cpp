//Written By Nicholas Abadir and Parth Patel
//Maze 5a



#include <iostream>
#include "maze.h"
#include "graph.h"
#include <fstream>

using namespace std;


int main()
{

    int i = 0;
    while(i < 3)
    {
        
        ifstream fin;

        graph graph_maze;

        string fileName;

        int current_c = 0;
        int current_r = 0;

        
        if (i == 0)
        {
         
            fileName = "Maze 1";
            fin.open(fileName.c_str());

            if (!fin)
            {
               cout << "Cannot Open File " << endl;
               return 0;
            }
        }
        if (i == 1)
        {
            
            fileName = "Maze 2";
            fin.open(fileName.c_str());

            if (!fin)
            {
                cout << "Cannot Open File " << endl;
                return 0;
            }
        }
        if (i == 2)
        {
            
            fileName = "Maze 3";
            fin.open(fileName.c_str());

            if (!fin)
            {
                cout << "Cannot Open File " << endl;
                return 0;
            }
        }

        while (fin && fin.peek() != 'Z')
        {
            cout << "BFS Algo" << endl;

            int count = 0;
            maze mazee(fin);
            mazee.MazeToGraph(graph_maze);
            if (count == 0)
            {
               mazee.findPathNonRecursive(graph_maze);
            }
            if (mazee.exists)
            {
              
                for (int j = 0; j < mazee.pat.size(); j++)
                {
                    
                    switch (mazee.pat[j])
                    {
                        
                    case -1:

                        current_c -= 1;
                        
                        mazee.print(mazee.getRows() - 1, mazee.getCols() - 1, current_r, current_c);
                        break;
                       
                    case 1:

                        current_c += 1;
                        
                        mazee.print(mazee.getRows() - 1, mazee.getCols() - 1, current_r, current_c);
                        break;
                        
                    case -2:

                        current_r -= 1;
                       
                        mazee.print(mazee.getRows() - 1, mazee.getCols() - 1, current_r, current_c);
                        break;
                       
                    case 2:

                        current_r += 1;
                        
                        mazee.print(mazee.getRows() - 1, mazee.getCols() - 1, current_r, current_c);
                        break;
                    default:

                        cout << "error";
                        break;
                    }
                }
                cout << endl << "End of " << fileName << endl;;
            }

            
            cout << endl << "DFS Algo" << endl;

            mazee.exists = 0;
            mazee.pat.clear();
            graph_maze.clearVisit();
            int current_coll = 0;
            int current_row = 0;

            
            mazee.visited.push_back(0);
            graph_maze.visit(0);

            mazee.findPathRecursive(graph_maze, 0, 0);

            if (mazee.exists)
            {
                for (int j = 0; j < mazee.pat.size(); j++)
                {
                    switch (mazee.pat[j])
                    {
                    case -1:

                        current_coll -= 1;
                        mazee.print(mazee.getRows() - 1, mazee.getCols() - 1, current_row, current_coll);

                        break;
                    case 1:

                        current_coll += 1;
                        mazee.print(mazee.getRows() - 1, mazee.getCols() - 1, current_row, current_coll);

                        break;
                    case -2:

                        current_row -= 1;
                        mazee.print(mazee.getRows() - 1, mazee.getCols() - 1, current_row, current_coll);

                        break;
                    case 2:

                        current_row += 1;
                        mazee.print(mazee.getRows() - 1, mazee.getCols() - 1, current_row, current_coll);

                        break;
                    default:

                        cout << "error";
                        break;
                    }
                }
                cout << endl << "End of " << fileName << endl;
            }
        }
        fin.close();
        i++;
    }
}