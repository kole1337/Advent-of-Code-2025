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

vector<pair<int, int>> find_accessible_positions(const vector<string>& grid) {
    vector<pair<int, int>> positions;
    int rows = grid.size();
    
    for (int i = 0; i < rows; i++) {
        int cols = grid[i].size();
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == '@') {
                int adjacent = count_adjacent_rolls(grid, i, j);
                if (adjacent < 4) {
                    positions.push_back({i, j});
                }
            }
        }
    }
    
    return positions;
}

void print_grid(const vector<string>& grid) {
    for (const auto& row : grid) {
        cout << row << '\n';
    }
}

int simulate_removal(vector<string>& grid, bool verbose = false) {
    int total_removed = 0;
    int iteration = 0;
    
    while (true) {
        // Find all accessible rolls
        vector<pair<int, int>> accessible = find_accessible_positions(grid);
        
        if (accessible.empty()) {
            break;
        }
        
        iteration++;
        int removed_this_round = accessible.size();
        total_removed += removed_this_round;
        
        if (verbose) {
            cout << "\nIteration " << iteration << ": Removing " 
                 << removed_this_round << " rolls\n";
        }
        
        // Remove all accessible rolls
        for (const auto& pos : accessible) {
            grid[pos.first][pos.second] = '.';
        }
        
        if (verbose && iteration <= 5) {
            print_grid(grid);
        }
    }
    
    if (verbose && iteration > 5) {
        cout << "\n... (" << (iteration - 5) << " more iterations)\n";
        cout << "\nFinal state:\n";
        print_grid(grid);
    }
    
    return total_removed;
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
    
    // Part 1: Count initially accessible rolls
    cout << "=== Part 1 ===" << endl;
    int part1_answer = count_accessible_rolls(grid);
    cout << "Initially accessible rolls: " << part1_answer << endl;
    
    // Part 2: Simulate removal process
    cout << "\n=== Part 2 ===" << endl;
    cout << "Initial state:\n";
    print_grid(grid);
    
    // Make a copy for simulation
    vector<string> grid_copy = grid;
    int part2_answer = simulate_removal(grid_copy, true);
    
    cout << "\nTotal rolls removed: " << part2_answer << endl;
    
    return 0;
}