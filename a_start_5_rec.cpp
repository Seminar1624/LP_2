#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

// Room dimensions
const int ROOM_WIDTH = 10;
const int ROOM_HEIGHT = 10;

struct Object {
    int width, height;
    string type;
};

struct Position {
    int x, y;
};

// Represents a placed object
struct PlacedObject {
    Object obj;
    Position pos;
};

// State of room
struct State {
    vector<PlacedObject> placed;
    vector<Object> remaining;
    vector<vector<bool>> room;

    int cost;       // g(n): objects placed
    int heuristic;  // h(n): estimated remaining effort

    int totalCost() const {
        return cost + heuristic;
    }

    // Compare for A* priority queue (min-heap)
    bool operator<(const State& other) const {
        return totalCost() > other.totalCost(); // reverse for min-heap
    }
};

// Check if object can be placed at (x,y)
bool canPlace(const vector<vector<bool>>& room, const Object& obj, int x, int y) {
    if (x + obj.width > ROOM_WIDTH || y + obj.height > ROOM_HEIGHT)
        return false;

    for (int i = x; i < x + obj.width; ++i) {
        for (int j = y; j < y + obj.height; ++j) {
            if (room[i][j])
                return false;
        }
    }
    return true;
}

// Place object and return new room state
vector<vector<bool>> placeObject(const vector<vector<bool>>& room, const Object& obj, int x, int y) {
    vector<vector<bool>> newRoom = room;
    for (int i = x; i < x + obj.width; ++i) {
        for (int j = y; j < y + obj.height; ++j) {
            newRoom[i][j] = true;
        }
    }
    return newRoom;
}

// Heuristic: area of remaining objects
int calculateHeuristic(const vector<Object>& remaining) {
    int total = 0;
    for (const auto& obj : remaining)
        total += obj.width * obj.height;
    return total;
}

void aStarPlacement(vector<Object> allObjects) {
    // Initial state
    State start;
    start.room = vector<vector<bool>>(ROOM_WIDTH, vector<bool>(ROOM_HEIGHT, false));
    start.remaining = allObjects;
    start.cost = 0;
    start.heuristic = calculateHeuristic(allObjects);

    priority_queue<State> openList;
    openList.push(start);

    while (!openList.empty()) {
        State current = openList.top();
        openList.pop();

        // Goal check
        if (current.remaining.empty()) {
            cout << "All objects placed successfully:\n";
            for (const auto& po : current.placed) {
                cout << po.obj.type << " at (" << po.pos.x << ", " << po.pos.y << ")\n";
            }
            return;
        }

        // Next object to place
        Object obj = current.remaining.back();
        current.remaining.pop_back();

        // Try placing it at every position
        for (int x = 0; x < ROOM_WIDTH; ++x) {
            for (int y = 0; y < ROOM_HEIGHT; ++y) {
                if (canPlace(current.room, obj, x, y)) {
                    State next = current;
                    next.room = placeObject(current.room, obj, x, y);
                    next.placed.push_back({obj, {x, y}});
                    next.cost = current.cost + obj.width * obj.height;
                    next.heuristic = calculateHeuristic(next.remaining);
                    openList.push(next);
                }
            }
        }
    }

    cout << "Could not place all objects in the room.\n";
}

int main() {
    vector<Object> objects;

    // 5 rectangles
    for (int i = 0; i < 5; ++i)
        objects.push_back({2, 4, "Rectangle"});

    // 4 squares
    for (int i = 0; i < 4; ++i)
        objects.push_back({2, 2, "Square"});

    aStarPlacement(objects);

    return 0;
}
