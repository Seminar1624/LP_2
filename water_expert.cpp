#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

struct Rule {
    vector<string> conditions;
    string conclusion;
    string explanation;
};

class ExpertSystem {
private:
    map<string, bool> facts;                    // Known truths
    vector<Rule> rules;                         // IF-THEN rules
    map<string, string> reasons;               // Explanations

public:
    // Set a fact
    void setFact(string fact, bool value) {
        facts[fact] = value;
    }

    // Add a rule
    void addRule(vector<string> conditions, string conclusion, string explanation) {
        rules.push_back({conditions, conclusion, explanation});
    }

    // Check if all conditions of a rule are true
    bool allConditionsTrue(const Rule& rule) {
        for (string condition : rule.conditions) {
            if (facts.find(condition) == facts.end() || !facts[condition])
                return false;
        }
        return true;
    }

    // Apply rules and infer new facts
    void infer() {
        bool newFactFound;
        do {
            newFactFound = false;
            for (auto& rule : rules) {
                if (facts.find(rule.conclusion) == facts.end() && allConditionsTrue(rule)) {
                    facts[rule.conclusion] = true;
                    reasons[rule.conclusion] = rule.explanation;
                    newFactFound = true;
                }
            }
        } while (newFactFound);
    }

    // Answer a WHY question
    void explain(string query) {
        cout << "\nQ: Why is '" << query << "'?\n";
        if (facts.find(query) != facts.end() && facts[query]) {
            cout << "A: " << reasons[query] << endl;
        } else {
            cout << "A: Sorry, I don't have enough information to answer that.\n";
        }
    }

    // Show all inferred facts (for debugging or learning)
    void showAllFacts() {
        cout << "\n--- All Known Facts ---\n";
        for (auto& fact : facts) {
            if (fact.second) {
                cout << fact.first << " = TRUE\n";
            }
        }
    }
};

int main() {
    ExpertSystem system;

    // Step 1: Add facts (current situation)
    system.setFact("today_is_monday", true);
    system.setFact("water_pump_is_off", true);
    system.setFact("lights_in_passage_are_off", true);
    system.setFact("power_backup_is_off", true);
    system.setFact("maintenance_is_scheduled", true);

    // Step 2: Add rules
    system.addRule({"today_is_monday", "water_pump_is_off"},
                   "water_supply_is_off",
                   "Because it's Monday and the water pump was OFF.");

    system.addRule({"lights_in_passage_are_off", "power_backup_is_off"},
                   "common_passage_is_dark",
                   "Because the passage lights are OFF and no power backup is available.");

    system.addRule({"maintenance_is_scheduled"},
                   "services_may_be_disrupted",
                   "Because maintenance is scheduled, some services may be unavailable.");

    // Step 3: Run inference engine
    system.infer();

    // Step 4: Ask questions
    system.explain("water_supply_is_off");
    system.explain("common_passage_is_dark");

    // Optional: Show all facts
    system.showAllFacts();

    return 0;
}
