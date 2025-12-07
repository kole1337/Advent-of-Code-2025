use std::env;
use std::fs;

#[derive(Debug)]
struct Range {
    start: i64,
    end: i64,
}

impl Range {
    fn contains(&self, value: i64) -> bool {
        value >= self.start && value <= self.end
    }
}

fn parse_range(line: &str) -> Option<Range> {
    let parts: Vec<&str> = line.split('-').collect();
    if parts.len() == 2 {
        if let (Ok(start), Ok(end)) = (parts[0].parse::<i64>(), parts[1].parse::<i64>()) {
            return Some(Range { start, end });
        }
    }
    None
}

fn is_fresh(id: i64, ranges: &[Range]) -> bool {
    ranges.iter().any(|range| range.contains(id))
}

fn main() {
    let input = "\
model input data was here, because i CBA to download rust
";
    
    let args: Vec<String> = env::args().collect();
    let input_data = if args.len() > 1 {
        fs::read_to_string(&args[1]).expect("Failed to read file")
    } else {
        input.to_string()
    };
    
    let lines: Vec<&str> = input_data.lines().collect();
    
    let mut ranges: Vec<Range> = Vec::new();
    let mut ingredient_ids: Vec<i64> = Vec::new();
    let mut parsing_ranges = true;
    
    for line in lines {
        let trimmed = line.trim();
        
        if trimmed.is_empty() {
            parsing_ranges = false;
            continue;
        }
        
        if parsing_ranges {
            if let Some(range) = parse_range(trimmed) {
                ranges.push(range);
            }
        } else {
            if let Ok(id) = trimmed.parse::<i64>() {
                ingredient_ids.push(id);
            }
        }
    }
    
    println!("Parsed {} fresh ingredient ID ranges:", ranges.len());
    for (i, range) in ranges.iter().enumerate() {
        if i < 5 {
            println!("  {}-{}", range.start, range.end);
        }
    }
    if ranges.len() > 5 {
        println!("  ... and {} more ranges", ranges.len() - 5);
    }
    println!();
    
    let mut fresh_count = 0;
    
    println!("Checking {} ingredient IDs:", ingredient_ids.len());
    for (i, id) in ingredient_ids.iter().enumerate() {
        let fresh = is_fresh(*id, &ranges);
        let status = if fresh { "FRESH" } else { "SPOILED" };
        
        if i < 10 {
            println!("  Ingredient ID {}: {}", id, status);
        }
        
        if fresh {
            fresh_count += 1;
        }
    }
    if ingredient_ids.len() > 10 {
        println!("  ... and {} more IDs checked", ingredient_ids.len() - 10);
    }
    
    println!("\nTotal fresh ingredients: {}", fresh_count);
}