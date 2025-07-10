# MoodSnap

**Author:** Nikhil

A C++ command-line tool to log your mood, daily events, and personal learning.

## Features
- Log new mood entries with date, event, learning, and a random motivational tip
- View all past entries
- Get a weekly mood summary (counts moods in the last 7 days)
- Entries are saved in a readable format in `moodlog.txt`

## How it Works (Class Overview)
- **Entry**: Stores a single mood entry (date, mood, event, learning, tip)
- **MoodLog**: Manages your list of entries (add, display, summary, file save/load)
- **TipBox**: Gives you a random motivational tip from a fixed list

## How to Compile and Run

1. **Open a terminal in the MoodSnap directory.**
2. **Compile:**
   
   On Windows (using g++):
   ```sh
   g++ -o MoodSnap main.cpp
   ```
   On Linux/Mac:
   ```sh
   g++ -o MoodSnap main.cpp
   ```
3. **Run:**
   ```sh
   ./MoodSnap
   ```
   (On Windows, use `MoodSnap.exe`)

## Sample Output
```
MoodSnap - Mood Journal
1. Log New Mood Entry
2. View All Entries
3. Weekly Mood Summary
4. Exit
Choose an option: 1
Enter your mood: Happy
Describe today's main event: Finished a project
What did you learn today?: Consistency pays off
Entry saved! Motivational tip: Keep going, you're doing great!

MoodSnap - Mood Journal
1. Log New Mood Entry
2. View All Entries
3. Weekly Mood Summary
4. Exit
Choose an option: 2
Date: 01-06-2024
Mood: Happy
Event: Finished a project
Learning: Consistency pays off
Tip: Keep going, you're doing great!
---

MoodSnap - Mood Journal
1. Log New Mood Entry
2. View All Entries
3. Weekly Mood Summary
4. Exit
Choose an option: 3
Mood counts in the last 7 days:
Happy: 1
```

## How to Run with Sample Data
- To test with sample data, you can manually add entries to `moodlog.txt` in the following format:
  ```
  Date: 01-06-2024
  Mood: Happy
  Event: Finished a project
  Learning: Consistency pays off
  Tip: Keep going, you're doing great!
  ---
  Date: 02-06-2024
  Mood: Sad
  Event: Missed a deadline
  Learning: Plan better
  Tip: Every day is a new beginning.
  ---
  ```
- Then run the program and use the menu options to view or summarize entries.

---

This project is beginner-friendly and suitable for portfolio use. Enjoy tracking your mood with MoodSnap!

---

Created by Nikhil. 
