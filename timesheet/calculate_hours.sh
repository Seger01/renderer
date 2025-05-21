#!/bin/bash

# List of CSV files
files=("seger_sheet.csv")

# Loop over each file
for file in "${files[@]}"
do
  # Check if the file exists
  if [ ! -f "$file" ]; then
    echo "File not found: $file"
    continue
  fi

  # Initialize sum variable
  total_hours=0

  # Read the CSV file
  while IFS=',' read -r date time duration activity || [ -n "$date" ]
  do
    # Skip the header line (assuming the header has "Duration" as a column name)
    if [[ "$duration" == "Duration(in hours)" ]]; then
      continue
    fi
    
    # Add the duration to the total hours
    total_hours=$(echo "$total_hours + $duration" | bc)
  done < "$file"

  # Print the total sum of hours for the current file
  echo "Total hours for $file: $total_hours"
done
