#! /bin/bash

output_file="script_output.log"
count=0

while true; do
    count=$((count + 1))
    bash cc.sh > "$output_file" 2>&1
    exit_code=$?
    if [[ $exit_code -ne 0 ]]; then
        break
    fi
done

echo "Script failed after $count runs."
echo "Output of the script:"
cat "$output_file"

rm $output_file
