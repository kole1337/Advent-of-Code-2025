#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int find_joltage(char *line) {
    int len = strlen(line);
    int max_joltage = 0;
    
    for (int i = 0; i < len; i++) {
        if (line[i] < '0' || line[i] > '9') continue;
        
        for (int j = i + 1; j < len; j++) {
            if (line[j] < '0' || line[j] > '9') continue;
                        int joltage = (line[i] - '0') * 10 + (line[j] - '0');
            
            if (joltage > max_joltage) {
                max_joltage = joltage;
            }
        }
    }
    
    return max_joltage;
}

unsigned long long find_max_joltage(char *line, int count) {
    int len = strlen(line);
    int digits_found = 0;
    
    // Count actual digits in the line
    for (int i = 0; i < len; i++) {
        if (line[i] >= '0' && line[i] <= '9') {
            digits_found++;
        }
    }
    
    // If we need to select all or more digits than available
    if (count >= digits_found) {
        unsigned long long result = 0;
        for (int i = 0; i < len; i++) {
            if (line[i] >= '0' && line[i] <= '9') {
                result = result * 10 + (line[i] - '0');
            }
        }
        return result;
    }
    
    // Greedy approach: select the largest digits while maintaining order
    char selected[256];
    int selected_count = 0;
    int skip_count = digits_found - count; // Number of digits to skip
    
    int pos = 0;
    while (selected_count < count) {
        // Find valid digit positions
        int digit_positions[256];
        int digit_count = 0;
        
        for (int i = pos; i < len; i++) {
            if (line[i] >= '0' && line[i] <= '9') {
                digit_positions[digit_count++] = i;
            }
        }
        
        // Find the largest digit we can take while leaving enough digits
        int best_pos = -1;
        char best_digit = '0' - 1;
        
        for (int i = 0; i < digit_count; i++) {
            int remaining_after = digit_count - i - 1;
            int needed = count - selected_count - 1;
            
            if (remaining_after >= needed) {
                if (line[digit_positions[i]] > best_digit) {
                    best_digit = line[digit_positions[i]];
                    best_pos = digit_positions[i];
                }
            }
        }
        
        if (best_pos != -1) {
            selected[selected_count++] = best_digit;
            pos = best_pos + 1;
        }
    }
    
    selected[selected_count] = '\0';
    
    // Convert to number
    unsigned long long result = 0;
    for (int i = 0; i < selected_count; i++) {
        result = result * 10 + (selected[i] - '0');
    }
    
    return result;
}

int main(int argc, char *argv[]) {
    FILE *file;
    char line[1024];
    unsigned long long total_joltage = 0;
    int batteries_to_select = 12; // Part 2 uses 12 batteries
    
    // Handle file input
    if (argc > 1) {
        file = fopen(argv[1], "r");
        if (!file) {
            printf("Error: Could not open file %s\n", argv[1]);
            return 1;
        }
    } else {
        printf("Usage: %s <input_file>\n", argv[0]);
        printf("Or enter banks manually (Ctrl+Z then Enter to finish on Windows):\n");
        file = stdin;
    }
    
    // Read input line by line
    while (fgets(line, sizeof(line), file)) {
        // Remove newline if present
        line[strcspn(line, "\n")] = 0;
        line[strcspn(line, "\r")] = 0;
        
        if (strlen(line) == 0) continue;
        
        unsigned long long max = find_max_joltage(line, batteries_to_select);
        printf("Bank: %s -> Max joltage: %llu\n", line, max);
        total_joltage += max;
    }
    
    if (file != stdin) {
        fclose(file);
    }
    
    printf("\nTotal output joltage: %llu\n", total_joltage);
    
    return 0;
}