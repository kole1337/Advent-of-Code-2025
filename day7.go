package main

import (
	"fmt"
	"strings"
)

func main() {
	input := `-`

	splits := solvePartTwo(input)
	fmt.Printf("Total Splits: %d\n", splits)
}

func solve(input string) int {
	lines := strings.Split(input, "\n")
	
	grid := make([]string, 0)
	for _, line := range lines {
		trimmed := strings.TrimSpace(line)
		if trimmed != "" {
			grid = append(grid, trimmed)
		}
	}

	if len(grid) == 0 {
		return 0
	}

	height := len(grid)
	width := len(grid[0])

	startCol := -1
	startRow := -1
	for r := 0; r < height; r++ {
		for c := 0; c < len(grid[r]); c++ {
			if grid[r][c] == 'S' {
				startCol = c
				startRow = r
				break
			}
		}
		if startCol != -1 {
			break
		}
	}

	if startCol == -1 {
		panic("No start 'S' found in grid")
	}

	activeCols := make(map[int]bool)
	activeCols[startCol] = true

	totalSplits := 0

	for r := startRow + 1; r < height; r++ {
		nextActiveCols := make(map[int]bool)
		
		for col := range activeCols {
			if col < 0 || col >= width {
				continue
			}

			cell := grid[r][col]

			if cell == '^' {
				totalSplits++
			
				if col-1 >= 0 {
					nextActiveCols[col-1] = true
				}
				if col+1 < width {
					nextActiveCols[col+1] = true
				}

			} else {
				nextActiveCols[col] = true
			}
		}

		activeCols = nextActiveCols

		if len(activeCols) == 0 {
			break
		}
	}

	return totalSplits
}

func solvePartTwo(input string) int {
	lines := strings.Split(input, "\n")
	grid := make([]string, 0)
	for _, line := range lines {
		trimmed := strings.TrimSpace(line)
		if trimmed != "" {
			grid = append(grid, trimmed)
		}
	}

	if len(grid) == 0 {
		return 0
	}

	height := len(grid)
	width := len(grid[0])

	startCol := -1
	startRow := -1
	for r := 0; r < height; r++ {
		for c := 0; c < len(grid[r]); c++ {
			if grid[r][c] == 'S' {
				startCol = c
				startRow = r
				break
			}
		}
		if startCol != -1 {
			break
		}
	}

	activeTimelines := make(map[int]int)
	
	activeTimelines[startCol] = 1
	
	for r := startRow + 1; r < height; r++ {
		nextTimelines := make(map[int]int)
		
		for col, count := range activeTimelines {
			if col < 0 || col >= width {
				continue
			}

			cell := grid[r][col]

			if cell == '^' {
				
				if col-1 >= 0 {
					nextTimelines[col-1] += count
				}
				if col+1 < width {
					nextTimelines[col+1] += count
				}
			} else {
				nextTimelines[col] += count
			}
		}
		
		activeTimelines = nextTimelines
		
		if len(activeTimelines) == 0 {
			break
		}
	}

	totalTimelines := 0
	for _, count := range activeTimelines {
		totalTimelines += count
	}

	return totalTimelines
}