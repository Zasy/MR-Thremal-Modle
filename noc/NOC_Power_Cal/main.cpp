//
// Created by zhanGGe on 2018/9/26.
//

#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>

#include "graph/graph.h"
#include "mr/mr.h"
#include "routing_data.h"

using namespace std;


int getShortestNumberHop(int s, int d, int NOC_WIDTH, int NOC_HEIGHT){
    int s_x = s % NOC_WIDTH;
    int s_y = s / NOC_WIDTH;

    int d_x = d % NOC_WIDTH;
    int d_y = d / NOC_WIDTH;

    int delta_x = max(d_x - s_x, s_x - d_x);
    int delta_y = max(d_y - s_y, s_y - d_y);

    return delta_x + delta_y + 1;
}

int NOC_WIDTH   = 8;
int NOC_HEIGHT  = 8;

vector<double> chip_temp = {
        62.55,66.05,64.54,64.52,63.93,63.88,63.58,63.03,
        63.67,65.41,67.26,67.3,65.08,65.01,63.76,61.9,
        62.64,65.57,67.69,67.89,66.57,64.23,62.26,61,
        61.97,64.34,67.41,67.4,67.25,64.02,61.62,60.41,
        60.65,63.41,65.21,66.96,66.14,63.3,62.4,60.49,
        59.84,61.8,61.82,63.59,62.8,60.95,59.84,59.42,
        58.78,59.72,60.52,61.57,63.07,59.63,58.81,58.25,
        57.79,58.12,59.02,64.63,62.48,59.21,58.19,57.46,
};

double GetPathLoss(vector<int> routinglist, vector<double> chip_temp){
    double temp = 0;
    int in_d =0;
    int out_d = get_output_direaction(routinglist[0], routinglist[1], NOC_WIDTH, NOC_HEIGHT);
    double temp_loss = 0;

    temp_loss += GetRouterLoss(in_d, out_d, chip_temp[routinglist[0]]);
    for (int i = 1; i < (routinglist.size() - 1); i++)
    {
        in_d = get_input_direction(routinglist[i - 1], routinglist[i], NOC_WIDTH, NOC_HEIGHT);
        out_d = get_output_direaction(routinglist[i], routinglist[i + 1], NOC_WIDTH, NOC_HEIGHT);
        temp_loss += GetRouterLoss(in_d, out_d, chip_temp[routinglist[i]]);
    }

    in_d = get_input_direction(routinglist[routinglist.size() - 2], routinglist[routinglist.size() - 1], NOC_WIDTH, NOC_HEIGHT);
    out_d = 0;

    temp_loss += GetRouterLoss(in_d, out_d, chip_temp[routinglist[routinglist.size() - 1]]);
    return temp_loss;
}
// Driver program
int main()
{
    // Create a graph given in the above diagram


    int process_no = NOC_HEIGHT * NOC_WIDTH;

    Graph g(process_no);

    for(int i = 0 ; i < NOC_WIDTH; i++){
        for(int j = 0; j < NOC_HEIGHT; j++){
            int src = j*NOC_HEIGHT + i;
            if(i - 1 >=0){
                g.addEdge(src, src - 1);
            }
            if(i + 1 < NOC_WIDTH){
                g.addEdge(src, src + 1);
            }

            if(j - 1 >= 0){
                g.addEdge(src, src - NOC_WIDTH);
            }

            if(j + 1 < NOC_WIDTH){
                g.addEdge(src, src + NOC_WIDTH);
            }
        }
    }
    int s = 0, d = 63;
    cout << "Following are all different paths from " << s
         << " to " << d << endl;

    int hops = getShortestNumberHop(s, d, NOC_WIDTH, NOC_HEIGHT);
    int k = 5;
    vector<vector<int>> paths = g.printAllPaths(s, d, hops);

    auto cmp = [](vector<int> left, vector<int> right){ return GetPathLoss(left, chip_temp) < GetPathLoss(right, chip_temp);};
    priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> q(cmp);

    priority_queue<double> q_loss;
    for(vector<int> path: paths){
        if(q.size() < k){
            q.push(path);
        }else{
            vector<int> temp_path = q.top();
            if(GetPathLoss(temp_path, chip_temp) > GetPathLoss(path, chip_temp)){
                q.pop();
                q.push(path);
            }
        }

//        q.push(path);
//        q_loss.push(GetPathLoss(path, chip_temp));
    }
    while(!q.empty()){
        cout << GetPathLoss(q.top(), chip_temp) << "\t";
        for(int v : q.top()){
            cout << v << "\t";
        }
        cout << endl;
        q.pop();
    }
    cout << endl;
}








