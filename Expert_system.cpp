#include<iostream>
#include<vector>
#include<string>
#include<map>

using namespace std;
class EmploteeExpertSystem
{
private:
    struct EmployeeRecord
    {
        string name;
        int score;
        string performance;
        string recommendation;
        vector<string> suggestions;
    };
    vector<EmployeeRecord> employeeRecords;

    const vector<pair<string,int>> questions={
        {"Does the employee meet deadlines",2},
        {"Does the employee work well in a team",2},
        {"Does the employee take initiative", 2},
        {"Does the employee have leadership qualities", 2},
        {"Does the employee consistently exceed expectations", 2},
        {" Is the employee punctual", 1},
        {"Does the employee adapt well to new challenges", 2},
        {"Does the employee show strong problem-solving skills", 2},
        {"Does the employee maintain a positive attitude", 2},
        {"Does the employee effectively communicate with colleagues", 2}


    };
    void provideSuggestion(vector<string> &suggestions,const vector<string> &negative_reasons)
    {
        for(const auto&neg:negative_reasons)
        {
            if(neg.find("deadline") != string::npos)
            {
                suggestions.push_back("Attend time management training");
            }
            else if (neg.find("team") != string::npos)
                suggestions.push_back("Participate in team-building activities.");
            else if (neg.find("leadership") != string::npos)
                suggestions.push_back("Take a leadership development course.");
            else if (neg.find("initiative") != string::npos)
                suggestions.push_back("Be proactive in task ownership.");
            else if (neg.find("problem-solving") != string::npos)
                suggestions.push_back("Improve analytical and logical thinking.");
            else if (neg.find("punctual") != string::npos)
                suggestions.push_back("Work on punctuality and discipline.");
            else if (neg.find("communicate") != string::npos)
                suggestions.push_back("Improve verbal and written communication.");
        }
    }
    string generatedRecommendation(int score,const vector<string> &negative_resons)
    {    if (score >= 17)
        return "Recommend for Promotion";
    else if (score >= 13)
        return "Eligible for Bonus/Recognition";
    else if (score <= 9)
        return "Needs Training & Mentoring";
    else
        return "Satisfactory but monitor performance";
    }

public:
    void evaluateEmployee()
    {
        cout<<"\nEnter employee Name: ";
        string name;
        cin.ignore();
        getline(cin,name);

        cout<<"\nPerformance Evalutaion (yes/no):"<<endl;
        int score=0;
        vector<string>negative_reasons;
        for(int i=0;i<questions.size();i++)
        {
            string question=questions[i].first;
            int wt=questions[i].second;


            string answer;
            cout<<question<<"? ";
            cin>>answer;

            if(answer=="yes"|| answer=="YES"|| answer=="y"|| answer=="Y"||answer=="Yes")
            {
                score+=wt;
            }
            else
            {
                negative_reasons.push_back("Not able to "+question.substr(17));
            }
        }

        string performance;
        if(score>=18) performance="Excellent";
        else if(score>=14) performance="Good";
        else if(score>=10) performance="Average";
        else performance="Poor";

        vector<string> suggestions;
        provideSuggestion(suggestions,negative_reasons);

        string recommendation=generatedRecommendation(score,negative_reasons);
        employeeRecords.push_back({name,score,performance,recommendation,suggestions});
        cout<<"\n Final Evalution : "<<performance<<endl;
        cout<<"Score : "<<score<<" / 20 "<<endl;
        cout<<"Recommendation : "<<recommendation<<endl;

        if(!negative_reasons.empty())
        {
            cout<<"\nAreas for Improvement : "<<endl;
            for(const auto&reasons: negative_reasons)
            {
                cout<<"- "<<reasons<<endl;
            }
        }
        if(!suggestions.empty())
        {
            cout<<"\nExpert suggestions"<<endl;
            for(const auto& suggestion:suggestions)
            {
                cout<<"* "<<suggestion<<endl;
            }
        }
    }
    void showEmployeeRecords()
    {
        if(employeeRecords.empty())
        {
            cout<<"\n No record found.."<<endl;
            return ;
        }
        cout<<"\n Employee Records : \n"<<endl;
        int ex=0,gd=0,av=0,pr=0;
        for(const auto& record:employeeRecords)
        {
            cout<<"Name : "<<record.name
            <<", Score: "<<record.score
            <<", Performance: "<<record.performance
            <<", Recommendation: "<<record.recommendation<<endl;


            if(record.performance=="Excellent") ex++;
            else if (record.performance == "Good") gd++;
            else if (record.performance == "Average") av++;
            else pr++;
        }
        cout<<"\n Summary Statistics: "<<endl;
        cout<<"Excellent : "<<ex<<", Good : "<<gd<<
        ", Average : "<<av<<", Poor : "<<pr<<endl;

    }
    void run()
    {
        while(true)
        {
            cout<<"Select option: \n 1- Evaluate employee \n 2-Show Records \n 3- Exit"<<endl;
            int ch;
            cin>>ch;
            switch(ch)
            {
                case 1: evaluateEmployee(); break;
                case 2: showEmployeeRecords(); break;
                case 3: cout<<"Exiting\n"; return;
                default: cout<<"Invalid choice"<<endl;
            }
        }
    }
};
int main()
{
    EmploteeExpertSystem system;
    system.run();
    return 0;
}