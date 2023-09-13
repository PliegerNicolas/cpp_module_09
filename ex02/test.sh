#!/bin/bash

if [ $# -ne 2 ]; then
	echo "Usage: bash $0 <command> <count>"
	exit 1
fi

command=$1
count=$2

if ! [[ "$count" =~ ^[0-9]+$ ]]; then
	echo "Error: count must be a positive integer."
	exit 1
fi

random_numbers=""
for ((i=1; i<=count; i++)); do
	random_numbers+="$((RANDOM % $count)) "
done

random_numbers="${random_numbers# }"

#echo "Arguments : "
#echo "${random_numbers[@]}"

"$command" "${random_numbers[@]}"
