#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int count_adjacent_rolls(const vector<string>& grid, int row, int col) {
    int rows = grid.size();
    int cols = grid[0].size();
    int count = 0;
    
    // Check all 8 adjacent positions
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    
    for (int i = 0; i < 8; i++) {
        int new_row = row + dx[i];
        int new_col = col + dy[i];
        
        // Check bounds
        if (new_row >= 0 && new_row < rows && 
            new_col >= 0 && new_col < cols) {
            if (grid[new_row][new_col] == '@') {
                count++;
            }
        }
    }
    
    return count;
}

int count_accessible_rolls(const vector<string>& grid) {
    int accessible = 0;
    int rows = grid.size();
    
    for (int i = 0; i < rows; i++) {
        int cols = grid[i].size();
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == '@') {
                int adjacent = count_adjacent_rolls(grid, i, j);
                if (adjacent < 4) {
                    accessible++;
                }
            }
        }
    }
    
    return accessible;
}

void print_accessible_rolls(const vector<string>& grid) {
    int rows = grid.size();
    
    cout << "\nAccessible rolls marked with 'x':\n";
    for (int i = 0; i < rows; i++) {
        int cols = grid[i].size();
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == '@') {
                int adjacent = count_adjacent_rolls(grid, i, j);
                if (adjacent < 4) {
                    cout << 'x';
                } else {
                    cout << '@';
                }
            } else {
                cout << grid[i][j];
            }
        }
        cout << '\n';
    }
}

int main(int argc, char* argv[]) {
    vector<string> grid;
    
    if (argc > 1) {
        // Read from file
        ifstream file(argv[1]);
        if (!file) {
            cerr << "Error: Could not open file " << argv[1] << endl;
            return 1;
        }
        
        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                grid.push_back(line);
            }
        }
        file.close();
    } else {
        // Read from stdin
        cout << "Enter the grid (empty line to finish):\n";
        string line;
        while (getline(cin, line)) {
            if (line.empty()) break;
            grid.push_back(line);
        }
    }
    
    if (grid.empty()) {
        cout << "No input provided.\n";
        return 1;
    }
    
    // Print the visualization
    print_accessible_rolls(grid);
    
    // Count accessible rolls
    int accessible = count_accessible_rolls(grid);
    
    cout << "\nTotal accessible rolls: " << accessible << endl;
    
    return 0;
}