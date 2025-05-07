#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, int> P; // pair<weight, vertex>

class Graph {
    int V;
    vector<vector<P>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }


    int primsMST(int start) {
        priority_queue<P,vector<P>,greater<P>>pq;
        pq.push({0,start});
        vector<bool> inMst(V,false);
        int sum=0;
        while(!pq.empty())
        {
            auto p=pq.top();
            pq.pop();

            int wt=p.first;
            int node=p.second;

            if(inMst[node]==true)
                continue;
            
            inMst[node]=true;
            sum+=wt;
            
            for(auto &tmp:adj[node])
            {
                int neighbor=tmp.first;
                int neighbot_wt=tmp.second;

                if(inMst[neighbor]==false)
                {
                    pq.push({neighbot_wt,neighbor});
                }
            }

        }
        return sum;
    }
};
class Job {
    public:
        char id;        // Job ID
        int deadline;   // Deadline of the job
        int profit;     // Profit of the job
    
        // Constructor to initialize job details
        Job(char id, int deadline, int profit) {
            this->id = id;
            this->deadline = deadline;
            this->profit = profit;
        }
    };
    
    // Function to compare jobs based on profit (for sorting)
    bool compare(Job a, Job b) {
        return a.profit > b.profit;  // Sort in decreasing order of profit
    }
    
    void jobScheduling(vector<Job> &jobs) {
        int n = jobs.size();
    
        // Sort jobs based on profit (greedy step)
        sort(jobs.begin(), jobs.end(), compare);
    
        // Array to track if a time slot is occupied
        vector<bool> slot(n, false);
        vector<char> jobSequence;  // To store the sequence of jobs
    
        int totalProfit = 0; // Total profit
        int jobCount = 0;    // Total number of jobs done
    
        // Iterate through all jobs to find suitable time slots
        for (int i = 0; i < n; i++) {
            // Find the latest available slot before the deadline
            for (int j = min(n, jobs[i].deadline) - 1; j >= 0; j--) {
                if (!slot[j]) {  // If the slot is free
                    slot[j] = true;  // Mark the slot as filled
                    jobSequence.push_back(jobs[i].id);  // Add job to the sequence
                    totalProfit += jobs[i].profit;  // Add profit
                    jobCount++;  // Increment number of jobs done
                    break;  // Exit the loop once a slot is found
                }
            }
        }
    
        // Output the results
        cout << "Total jobs done: " << jobCount << endl;
        cout << "Total profit: " << totalProfit << endl;
        cout << "Job sequence: ";
        for (char c : jobSequence) {
            cout << c << " ";
        }
        cout << endl;
    }
int main() {
    int choice;
    cout << "===== MENU =====\n";
    cout << "1. Find MST using Prim's Algorithm\n";
    cout << "2. Perform Greedy Job Scheduling\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        int V, E;
        cout << "Enter number of vertices and edges: ";
        cin >> V >> E;

        Graph g(V);
        cout << "Enter " << E << " edges (u v weight):\n";
        for (int i = 0; i < E; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            g.addEdge(u, v, w);
        }
        int start;
        cout << "Enter starting node for Prim's Algorithm (0 to " << V - 1 << "): ";
        cin >> start;
    
        if (start < 0 || start >= V) {
            cout << "Invalid starting node.\n";
            return 1;
        }
    
        int mstWeight = g.primsMST(start);
        // int mstWeight = g.primsMST();
        cout << "Total weight of MST: " << mstWeight << endl;
    }
    else if (choice == 2) {
        int n;
    cout << "Enter the number of jobs: ";
    cin >> n;

    // Use a vector to hold the jobs
    vector<Job> jobs;

    cout << "Enter job details (ID, Deadline, Profit) for each job:" << endl;
    for (int i = 0; i < n; i++) {
        char id;
        int deadline, profit;
        cout << "Job " << i + 1 << ": ";
        cin >> id >> deadline >> profit;  //fflush(stdin); use if not taken proper input
        jobs.push_back(Job(id, deadline, profit)); // Add job to vector
    }

    // Call the job scheduling function
    jobScheduling(jobs);

    }
    else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
