// MoodSnap - A simple mood journaling CLI tool
// main.cpp
// Includes: Menu, Entry, Journal, TipManager classes, file handling, and comments
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <map> // Added for weekly summary

using namespace std;

// Entry class: stores a single mood entry
class Entry {
public:
    string date;
    string mood;
    string event;
    string learning;
    string tip;

    // Constructor
    Entry(const string& d, const string& m, const string& e, const string& l, const string& t)
        : date(d), mood(m), event(e), learning(l), tip(t) {}

    // Format entry for saving to file
    string toString() const {
        stringstream ss;
        ss << "Date: " << date << "\nMood: " << mood << "\nEvent: " << event
           << "\nLearning: " << learning << "\nTip: " << tip << "\n---\n";
        return ss.str();
    }

    // Parse entry from file lines
    static Entry fromString(const vector<string>& lines) {
        string d = lines[0].substr(6); // now expects dd-mm-yyyy
        string m = lines[1].substr(6);
        string e = lines[2].substr(7);
        string l = lines[3].substr(10);
        string t = lines[4].substr(5);
        return Entry(d, m, e, l, t);
    }
};

// TipBox class: provides random motivational tips
class TipBox {
    vector<string> tips;
public:
    TipBox() {
        // Add some motivational tips
        tips = {
            "Keep going, you're doing great!",
            "Every day is a new beginning.",
            "Believe in yourself!",
            "Small steps lead to big changes.",
            "You are stronger than you think."
        };
    }
    // Get a random tip
    string getRandomTip() {
        int idx = rand() % tips.size();
        return tips[idx];
    }
};

// MoodLog class: manages a list of entries
class MoodLog {
    vector<Entry> entries;
    string filename;
public:
    MoodLog(const string& fname) : filename(fname) {
        loadFromFile();
    }

    // Add a new entry
    void addEntry(const Entry& entry) {
        entries.push_back(entry);
        saveToFile();
    }

    // Display all entries
    void displayEntries() const {
        if (entries.empty()) {
            cout << "No entries found.\n";
            return;
        }
        for (const auto& e : entries) {
            cout << e.toString();
        }
    }

    // Weekly mood summary (counts moods in last 7 days)
    void weeklySummary() const {
        if (entries.empty()) {
            cout << "No entries to summarize.\n";
            return;
        }
        // Get current date
        time_t now = time(0);
        tm* now_tm = localtime(&now);
        char buf[11];
        strftime(buf, sizeof(buf), "%d-%m-%Y", now_tm);
        string today(buf);

        // Count moods in last 7 days
        map<string, int> moodCount;
        for (const auto& e : entries) {
            if (isWithinLast7Days(e.date, today)) {
                moodCount[e.mood]++;
            }
        }
        cout << "Mood counts in the last 7 days:\n";
        for (const auto& p : moodCount) {
            cout << p.first << ": " << p.second << endl;
        }
        if (moodCount.empty()) {
            cout << "No entries in the last 7 days.\n";
        }
    }

    // Helper: check if date is within last 7 days
    static bool isWithinLast7Days(const string& entryDate, const string& today) {
        tm ed = {}, td = {};
        // Parse dd-mm-yyyy manually
        sscanf(entryDate.c_str(), "%2d-%2d-%4d", &ed.tm_mday, &ed.tm_mon, &ed.tm_year);
        sscanf(today.c_str(), "%2d-%2d-%4d", &td.tm_mday, &td.tm_mon, &td.tm_year);
        ed.tm_mon -= 1; td.tm_mon -= 1; // tm_mon is 0-based
        ed.tm_year -= 1900; td.tm_year -= 1900; // tm_year is years since 1900
        time_t t_ed = mktime(&ed);
        time_t t_td = mktime(&td);
        double diff = difftime(t_td, t_ed) / (60 * 60 * 24);
        return diff >= 0 && diff < 7;
    }

    // Save entries to file
    void saveToFile() const {
        ofstream ofs(filename);
        for (const auto& e : entries) {
            ofs << e.toString();
        }
    }

    // Load entries from file
    void loadFromFile() {
        entries.clear();
        ifstream ifs(filename);
        string line;
        vector<string> lines;
        while (getline(ifs, line)) {
            if (line == "---") {
                if (lines.size() == 5) {
                    entries.push_back(Entry::fromString(lines));
                }
                lines.clear();
            } else {
                lines.push_back(line);
            }
        }
    }
};

// Helper: get current date as string in dd-mm-yyyy format
string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buf[11];
    strftime(buf, sizeof(buf), "%d-%m-%Y", ltm);
    return string(buf);
}

// Main menu
void showMenu() {
    cout << "\nMoodSnap - Mood Journal" << endl;
    cout << "1. Log New Mood Entry" << endl;
    cout << "2. View All Entries" << endl;
    cout << "3. Weekly Mood Summary" << endl;
    cout << "4. Exit" << endl;
    cout << "Choose an option: ";
}

int main() {
    srand(time(0)); // Seed random for tips
    MoodLog moodLog("moodlog.txt");
    TipBox tipBox;
    int choice;
    do {
        showMenu();
        cin >> choice;
        cin.ignore(); // Clear newline
        if (choice == 1) {
            // Log new entry
            string mood, event, learning;
            cout << "Enter your mood: ";
            getline(cin, mood);
            cout << "Describe today's main event: ";
            getline(cin, event);
            cout << "What did you learn today?: ";
            getline(cin, learning);
            string tip = tipBox.getRandomTip();
            string date = getCurrentDate();
            Entry entry(date, mood, event, learning, tip);
            moodLog.addEntry(entry);
            cout << "Entry saved! Motivational tip: " << tip << endl;
        } else if (choice == 2) {
            // View all entries
            moodLog.displayEntries();
        } else if (choice == 3) {
            // Weekly summary
            moodLog.weeklySummary();
        } else if (choice == 4) {
            cout << "Goodbye!" << endl;
        } else {
            cout << "Invalid option. Try again.\n";
        }
    } while (choice != 4);
    return 0;
} 