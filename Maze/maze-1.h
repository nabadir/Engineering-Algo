#pragma once 


#include <iostream>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include "graph.h" 
#include <vector>
#include <queue>



class maze
{
public:
    maze(ifstream& fin)
        
    {
        fin >> rows;
        fin >> collumns;

        char x;

        value.resize(rows, collumns);
        for (int i = 0; i <= rows - 1; i++)
            for (int j = 0; j <= collumns - 1; j++)
            {
                fin >> x;
                if (x == 'O')
                    value[i][j] = 1;
                else
                    value[i][j] = 0;
            }

        map.resize(rows, collumns);
    }

    int getCols()
    {
        return collumns;
    }

    int getRows()
    {
        return rows;
    }

    void setMap(int x, int y, int n)
    {
        map[x][y] = n;
    }

    matrix<int> getMap(int x, int y) const
    {
        return map;
    }

    void print(int I, int J, int currI, int currJ)

    {
        cout << endl;

        if (I < 0 || I > rows || J < 0 || J > collumns)
            throw rangeError("Bad value ");

        if (currI < 0 || currI > rows || currJ < 0 || currJ > collumns)
            throw rangeError("Bad value ");

        for (int i = 0; i <= rows - 1; i++)
        {
            for (int j = 0; j <= collumns - 1; j++)
            {
                if (i == I && j == J)
                    cout << "*";
                else

                    if (i == currI && j == currJ)
                        cout << "+";

                    else
                        if (value[i][j])
                            cout << " ";

                        else
                            cout << "X";
            }
            cout << endl;
        }
        cout << endl;
    }

    bool Legal(int i, int j)

    {
        if (i < 0 || i > rows || j < 0 || j > collumns)
            throw rangeError("Bad value");

        return value[i][j];
    }

    void MazeToGraph(graph& g)

    {
        node n;
        edge e;
        int counter = 0;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < collumns; j++)
            {
                if (value[i][j])
                {
                    n.setId(counter);
                    g.addNode(n);
                    setMap(i, j, counter);
                }
                else {
                    setMap(i, j, -1);
                }
                counter++;
            }
        }

        counter = 0;
        int num1, num2;

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < collumns; j++)
            {
                if (value[i][j])
                {
                    for (int x = 0; x < g.numNodes(); x++)
                    {
                        if (counter == g.getNode(x).getId())
                            num1 = x;
                    }
                    if (i > 0)
                    {
                        if (map[i - 1][j] != -1)
                        {
                            for (int x = 0; x < g.numNodes(); x++)
                                if (map[i - 1][j] == g.getNode(x).getId())
                                    num2 = x;
                            
                            g.addEdge(num1, num2);
                        }
                    }

                    if (i < rows - 1)
                    {
                        if (map[i + 1][j] != -1)
                        {
                            for (int x = 0; x < g.numNodes(); x++)
                                if (map[i + 1][j] == g.getNode(x).getId())
                                    num2 = x;
                            
                            g.addEdge(num1, num2);
                        }
                    }

                    if (j - 1 > -1)
                    {
                        if (map[i][j - 1] != -1)
                        {
                            for (int x = 0; x < g.numNodes(); x++)
                                if (map[i][j - 1] == g.getNode(x).getId())
                                    num2 = x;
                            
                            g.addEdge(num1, num2);
                        }
                    }

                    if (j + 1 > collumns)
                    {
                        if (map[i][j + 1] != -1)
                        {
                            for (int x = 0; x < g.numNodes(); x++)
                                if (map[i + 1][j] == g.getNode(x).getId())
                                    num2 = x;
                            
                            g.addEdge(num1, num2);
                        }
                    }
                }

                counter++;
            }
        }
    }


    void findPathRecursive(graph& tame, int n, int prev)
    {

        int row1;
        int col1;
        int row2;
        int col2;
        col1 = tame.getNode(prev).getId() % getCols();
        row1 = (tame.getNode(prev).getId() - col1) / getCols();
        col2 = tame.getNode(n).getId() % getCols();
        row2 = (tame.getNode(n).getId() - col2) / getCols();


        if (col1 != col2 && !exists)
        {
            if (col1 > col2)
            {
                pat.push_back(-1);
                std::cout << "Left" << endl;
                
            }
            if(col1 < col2)
            {
                std::cout << "Right" << endl;
                pat.push_back(1);
            }
        }
        if (row1 != row2 && !exists)
        {
            if (row1 > row2)
            {
                std::cout << "Up" << endl;
                pat.push_back(-2);
            }
            if (row1 < row2) {
                std::cout << "Down" << endl;
                pat.push_back(2);
            }
        }


        if (n + 1  == tame.numNodes())
        {
            std::cout << endl << "Path solved through DFS" << endl;;
            exists = 1;
        }
        else {
            {
                for (int i = 0; i < tame.numNodes(); i++)
                {

                    if ((tame.Edge(n, i) || tame.Edge(i, n)) && !tame.alrVisited(i))
                    {
                        visited.push_back(i);

                        tame.visit(i);

                        findPathRecursive(tame, i, n);

                        col1 = tame.getNode(i).getId() % getCols();
                        row1 = (tame.getNode(i).getId() - col1) / getCols();

                        col2 = tame.getNode(n).getId() % getCols();
                        row2 = (tame.getNode(n).getId() - col2) / getCols();

                       
                        if (col1 != col2 && !exists)
                        {
                            if (col1 > col2)
                            {
                                std::cout << "Left" << endl;pat.push_back(-1);
                            }
                            if (col1 < col2)
                            {
                                std::cout << "Right" << endl;pat.push_back(1);
                            }
                        }
                        else if (row1 != row2 && !exists)
                        {
                            if (row1 > row2) {
                                std::cout << "Up" << endl; pat.push_back(-2);
                            }
                            else {
                                std::cout << "Down" << endl; pat.push_back(2);
                            }
                        }
                    }
                }
            }
        }
    }
 
    void findPathNonRecursive(graph& goo)
    {

        goo.clearVisit();
        queue<int> qu;

        vector<int> visited;
        vector<int> parents;
        vector<int> pre;


        int current;
        int col1, row1, coll2, row2;


        qu.push(0);

        visited.push_back(0);

        parents.resize(goo.numNodes());
        
        goo.visit(0);

        for (int j = 0; j < visited.size(); j++)
        {

            if (visited[j] == goo.numNodes() - 1)
            {
                exists = 0;
                current = j;
            }
        }

        if (exists)
        {
            do
            {
                pre.push_back(current);
                current = parents[current];

            } while (current != 0);
            pre.push_back(0);


            for (int j = pre.size() - 1; j > 0; j--)
            {

                col1 = goo.getNode(pre[j]).getId() % getCols();

                row1 = (goo.getNode(pre[j]).getId() - col1) / getCols();

                coll2 = goo.getNode(pre[j - 1]).getId() % getCols();

                row2 = (goo.getNode(pre[j - 1]).getId() - coll2) / getCols();


                if (col1 != coll2)
                {
                    if (col1 > coll2)
                    {
                        std::cout << "Left" << endl;pat.push_back(-1);
                    }
                    else
                    {
                        std::cout << "Right" << endl;pat.push_back(1);
                    }
                }
                if (row1 != row2)
                {
                    if (row1 > row2)
                    {
                        std::cout << "Up" << endl;pat.push_back(-2);
                    }
                    else 
                    {
                        std::cout << "Down" << endl;;pat.push_back(2);
                    }
                }
            }
            std::cout << endl << "Path solved through BTS" << endl;

        }
    }
    
    vector<int> visited;
    bool exists;
    
    vector<int> pat;


    int rows; 
    int collumns;

    matrix<bool> value;
    matrix<int> map;      
};




