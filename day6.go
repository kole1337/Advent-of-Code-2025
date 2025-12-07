package main

import (
	"fmt"
	"strconv"
	"strings"
	"unicode"
)

func main() {

	input := `input code`
	total := solvePartTwo(input)
	fmt.Printf("Solution: %d\n", total)
}

func solvePartOne(input string) int {
	lines := strings.Split(input, "\n")


	maxWidth := 0
	for _, line := range lines {
		if len(line) > maxWidth {
			maxWidth = len(line)
		}
	}

	for i := range lines {
		if len(lines[i]) < maxWidth {
			lines[i] = lines[i] + strings.Repeat(" ", maxWidth-len(lines[i]))
		}
	}


	var problemRanges [][2]int
	inProblem := false
	startCol := 0

	for col := 0; col < maxWidth; col++ {
		isSeparator := true
		for _, line := range lines {
			if !unicode.IsSpace(rune(line[col])) {
				isSeparator = false
				break
			}
		}

		if !isSeparator {
			if !inProblem {
				inProblem = true
				startCol = col
			}
		} else {
			if inProblem {
				problemRanges = append(problemRanges, [2]int{startCol, col})
				inProblem = false
			}
		}
	}
	if inProblem {
		problemRanges = append(problemRanges, [2]int{startCol, maxWidth})
	}

	grandTotal := 0

	for i, rng := range problemRanges {
		start, end := rng[0], rng[1]
		var nums []int
		var operator string

		for _, line := range lines {
			segment := line[start:end]
			trimmed := strings.TrimSpace(segment)

			if trimmed == "" {
				continue
			}

			if trimmed == "+" || trimmed == "*" {
				operator = trimmed
			} else {
				val, err := strconv.Atoi(trimmed)
				if err == nil {
					nums = append(nums, val)
				}
			}
		}

		res := 0
		if operator == "+" {
			res = 0
			for _, n := range nums {
				res += n
			}
		} else if operator == "*" {
			res = 1
			for _, n := range nums {
				res *= n
			}
		} else {
			fmt.Printf("Problem %d (cols %d-%d) has no operator\n", i+1, start, end)
		}
		
		grandTotal += res
	}

	return grandTotal
}

func solvePartTwo(input string) int {
	lines := strings.Split(input, "\n")

	maxWidth := 0
	for _, line := range lines {
		if len(line) > maxWidth {
			maxWidth = len(line)
		}
	}
	for i := range lines {
		if len(lines[i]) < maxWidth {
			lines[i] = lines[i] + strings.Repeat(" ", maxWidth-len(lines[i]))
		}
	}

	
	var problemRanges [][2]int
	inProblem := false
	startCol := 0

	for col := 0; col < maxWidth; col++ {
		isSeparator := true
		for _, line := range lines {
			if !unicode.IsSpace(rune(line[col])) {
				isSeparator = false
				break
			}
		}

		if !isSeparator {
			if !inProblem {
				inProblem = true
				startCol = col
			}
		} else {
			if inProblem {
				problemRanges = append(problemRanges, [2]int{startCol, col})
				inProblem = false
			}
		}
	}
	if inProblem {
		problemRanges = append(problemRanges, [2]int{startCol, maxWidth})
	}

	grandTotal := 0

	for _, rng := range problemRanges {
		start, end := rng[0], rng[1]
		var nums []int
		var operator string

		for col := end - 1; col >= start; col-- {
			var digitStr strings.Builder
			
			for _, line := range lines {
				char := rune(line[col])
				
				if unicode.IsDigit(char) {
					digitStr.WriteRune(char)
				} else if char == '+' || char == '*' {
					operator = string(char)
				}
			}

			if digitStr.Len() > 0 {
				val, _ := strconv.Atoi(digitStr.String())
				nums = append(nums, val)
			}
		}

		res := 0
		if operator == "+" {
			res = 0
			for _, n := range nums {
				res += n
			}
		} else if operator == "*" {
			res = 1
			for _, n := range nums {
				res *= n
			}
		}
		
		grandTotal += res
	}

	return grandTotal
}