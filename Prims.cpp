#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
using namespace std;

#define infinity 9999
#define MAX 20
int span[MAX][MAX], n = 3;
int G[MAX][MAX];
int Prims();
//@author 88min    Solving minimum cost spanning tree by Prim's Algorithm

int Prims()
{
    int cost[MAX][MAX];
    int u, v = 0, min_distance, distance[MAX], previous[MAX];
    int checked[MAX], no_of_edges, i, min_cost, j;

    //create matrix, spanning, cost
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            if (G[i][j] == 0) {
                span[i][j] = 0;
                cost[i][j] = infinity;
            }
            else {
                cost[i][j] = G[i][j];
                span[i][j] = 99999; //infinity value
            }
        }
    //initialization checked, distance, previous
    distance[0] = 0;
    checked[0] = 1;

    for (i = 1; i < n; i++)
    {
        distance[i] = cost[0][i];
        previous[i] = 0;
        checked[i] = 0;
    }

    min_cost = 0;           //spanning tree cost
    no_of_edges = n - 1;    //number of edges 

    while (no_of_edges > 0)
    {
        //finding vertex with minimum distance from the tree
        min_distance = infinity;
        for (i = 1; i < n; i++)
            if (checked[i] == 0 && distance[i] < min_distance)
            {
                v = i;
                min_distance = distance[i];
            }

        u = previous[v];

        //adding edge in spanning tree
        span[u][v] = distance[v];
        span[v][u] = distance[v];
        no_of_edges--;
        checked[v] = 1;

        //update distance
        for (i = 1; i < n; i++)
            if (checked[i] == 0 && cost[i][v] < distance[i])
            {
                distance[i] = cost[i][v];
                previous[i] = v;
            }
        min_cost = min_cost + cost[u][v];
    }
    return(min_cost);
}

int main()
{
    //initialization of input output txt file
    ifstream input_txt;
    ofstream output_txt;
    int i, j, total_cost;
    input_txt.open("input.txt");
    output_txt.open("output.txt");

    //read adjacency matrix from input.txt
    if (!input_txt.is_open()) return -1;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            input_txt >> G[i][j];
        }
    }

    total_cost = Prims();

    //output print in output.txt
    for (i = 0; i < n; i++)
    {
        output_txt << "\n";
        for (j = 0; j < n; j++) {
            output_txt << "\t";
            output_txt << span[i][j];
        }
    }
    system("PAUSE");
    return 0;
}

