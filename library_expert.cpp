#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>

using namespace std;

// Helper to convert string to lowercase
string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Book structure
struct Book {
    string title;
    string author;
    string domain;
    string language;
    string level;
    int complexity; // 1 - Basic, 2 - Intermediate, 3 - Advanced
};

// Knowledge base of books
vector<Book> bookDatabase = {
    {"Python Machine Learning", "Sebastian Raschka", "ai", "python", "ug", 2},
    {"Artificial Intelligence: A Modern Approach", "Russell & Norvig", "ai", "python", "pg", 3},
    {"Eloquent JavaScript", "Marijn Haverbeke", "web dev", "javascript", "ug", 2},
    {"Flask Web Development", "Miguel Grinberg", "web dev", "python", "ug", 2},
    {"Computer Networking: Principles", "Olivier Bonaventure", "networking", "c++", "pg", 3},
    {"Data Communications", "Behrouz Forouzan", "networking", "java", "ug", 2},
    {"Hands-On Data Science", "Valliappa Lakshmanan", "data science", "python", "ug", 2},
    {"Data Science from Scratch", "Joel Grus", "data science", "python", "pg", 3},
    {"Java: The Complete Reference", "Herbert Schildt", "general", "java", "ug", 1},
    {"C++ Primer", "Stanley B. Lippman", "general", "c++", "pg", 2}
};

// Compute match score
int computeScore(const Book& book, const string& domain, const string& lang, const string& level, int complexity) {
    int score = 0;
    if (book.domain == domain) score += 40;
    if (book.language == lang) score += 30;
    if (book.level == level) score += 20;

    // Smaller difference in complexity gives higher score
    int diff = abs(book.complexity - complexity);
    score += max(0, 10 - diff * 5);
    return score;
}

int main() {
    string userDomain, userLang, userLevel;
    int userComplexity;

    cout << "-------- Advanced Library Expert System --------\n";
    cout << "Enter your project domain (AI, Web Dev, Networking, Data Science): ";
    getline(cin, userDomain);
    cout << "Enter your programming language (Python, Java, C++, JavaScript): ";
    getline(cin, userLang);
    cout << "Enter your academic level (UG/PG): ";
    getline(cin, userLevel);
    cout << "Enter project complexity level (1=Basic, 2=Intermediate, 3=Advanced): ";
    cin >> userComplexity;

    userDomain = toLower(userDomain);
    userLang = toLower(userLang);
    userLevel = toLower(userLevel);

    // Store matching books with scores
    vector<pair<int, Book>> recommendations;

    for (const Book& b : bookDatabase) {
        int score = computeScore(b, userDomain, userLang, userLevel, userComplexity);
        if (score >= 40) { // Threshold
            recommendations.push_back({score, b});
        }
    }

    // Sort by score descending
    sort(recommendations.begin(), recommendations.end(), [](auto& a, auto& b) {
        return a.first > b.first;
    });

    // Output
    cout << "\nTop Book Recommendations:\n";
    if (recommendations.empty()) {
        cout << "No matching books found. Try modifying your input.\n";
    } else {
        for (const auto& pair : recommendations) {
            cout << "\nTitle: " << pair.second.title;
            cout << "\nAuthor: " << pair.second.author;
            cout << "\nDomain: " << pair.second.domain;
            cout << "\nLanguage: " << pair.second.language;
            cout << "\nLevel: " << pair.second.level;
            cout << "\nConfidence Score: " << pair.first << "/100\n";
        }
    }

    return 0;
}
