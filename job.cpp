#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Class to represent a job
// class Job {
// public:
//     char id;        // Job ID
//     int deadline;   // Deadline of the job
//     int profit;     // Profit of the job

//     // Constructor to initialize job details
//     Job(char id, int deadline, int profit) {
//         this->id = id;
//         this->deadline = deadline;
//         this->profit = profit;
//     }
// };

// // Function to compare jobs based on profit (for sorting)
// bool compare(Job a, Job b) {
//     return a.profit > b.profit;  // Sort in decreasing order of profit
// }

// void jobScheduling(vector<Job> &jobs) {
//     int n = jobs.size();

//     // Sort jobs based on profit (greedy step)
//     sort(jobs.begin(), jobs.end(), compare);

//     // Array to track if a time slot is occupied
//     vector<bool> slot(n, false);
//     vector<char> jobSequence;  // To store the sequence of jobs

//     int totalProfit = 0; // Total profit
//     int jobCount = 0;    // Total number of jobs done

//     // Iterate through all jobs to find suitable time slots
//     for (int i = 0; i < n; i++) {
//         // Find the latest available slot before the deadline
//         for (int j = min(n, jobs[i].deadline) - 1; j >= 0; j--) {
//             if (!slot[j]) {  // If the slot is free
//                 slot[j] = true;  // Mark the slot as filled
//                 jobSequence.push_back(jobs[i].id);  // Add job to the sequence
//                 totalProfit += jobs[i].profit;  // Add profit
//                 jobCount++;  // Increment number of jobs done
//                 break;  // Exit the loop once a slot is found
//             }
//         }
//     }

//     // Output the results
//     cout << "Total jobs done: " << jobCount << endl;
//     cout << "Total profit: " << totalProfit << endl;
//     cout << "Job sequence: ";
//     for (char c : jobSequence) {
//         cout << c << " ";
//     }
//     cout << endl;
// }

// int main() {
//     int n;
//     cout << "Enter the number of jobs: ";
//     cin >> n;

//     // Use a vector to hold the jobs
//     vector<Job> jobs;

//     cout << "Enter job details (ID, Deadline, Profit) for each job:" << endl;
//     for (int i = 0; i < n; i++) {
//         char id;
//         int deadline, profit;
//         cout << "Job " << i + 1 << ": ";
//         cin >> id >> deadline >> profit;
//         jobs.push_back(Job(id, deadline, profit)); // Add job to vector
//     }

//     // Call the job scheduling function
//     jobScheduling(jobs);

//     return 0;
// }

// Enter the number of jobs: 5
// Enter job details (ID, Deadline, Profit) for each job:
// Job 1: A 2 20
// Job 2: B 2 15
// Job 3: C 1 10
// Job 4: D 3 5
// Job 5: E 3 1
// Total jobs done: 3
// Total profit: 40
// Job sequence: A B D

// ------------ Job Scheduling -------------
struct Job
{
    int processing_time;
    int profit;
    int deadline;
};

bool compareJobs(const Job &job1, const Job &job2)
{
    return job1.deadline < job2.deadline;
}

pair<int, vector<Job>> greedyJobScheduling(vector<Job> &jobs)
{
    sort(jobs.begin(), jobs.end(), compareJobs);
    int current_time = 0, total_profit = 0;
    vector<Job> scheduled_jobs;

    for (Job &job : jobs)
    {
        if (current_time + job.processing_time <= job.deadline)
        {
            current_time += job.processing_time;
            scheduled_jobs.push_back(job);
            total_profit += job.profit;
        }
    }
    return make_pair(total_profit, scheduled_jobs);
}
int main()
{
    int n;
    cout << "Enter number of jobs: ";
    cin >> n;

    vector<Job> jobs(n);
    cout << "Enter processing_time, profit, deadline for each job:\n";
    for (int i = 0; i < n; ++i) {
        cin >> jobs[i].processing_time >> jobs[i].profit >> jobs[i].deadline;
    }
    // vector<Job> jobs = {{5, 20, 2}, {2, 10, 1}, {3, 15, 3}};
    auto result = greedyJobScheduling(jobs);
    cout << "Total profit earned: " << result.first << endl;
    cout << "Scheduled jobs:\n";
    for (const Job &job : result.second)
    {
        cout << "Processing time: " << job.processing_time
             << ", Profit: " << job.profit
             << ", Deadline: " << job.deadline << endl;
    }
        return 0;
}