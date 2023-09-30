#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Usage: bash $0 <count>"
	exit 1
fi

count=$1

if ! [[ "$count" =~ ^[0-9]+$ ]]; then
	echo "Error: count must be a positive integer."
	exit 1
fi

random_numbers=""
for ((i=1; i<=count; i++)); do
	random_numbers+="$((RANDOM % (count + 100))) "
done

random_numbers="${random_numbers# }"

#echo "Arguments : "
#echo "${random_numbers[@]}"

gdb --args ./PmergeMe "${random_numbers[@]}"
#./PmergeMe "${random_numbers[@]}"
