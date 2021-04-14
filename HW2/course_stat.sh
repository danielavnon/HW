#!/bin/bash
#script name: course_stat.sh
#(lines 1-9) check feasible input
#(lines 10-16) create a new folder named as specified and feed it grades file
#(lines 17-22) run the C compiled executable on the grades file, create analysis file

if [[ $# != 1 ]]; then
	echo "Wrong number of arguments" 1>&2
	exit
fi
is_arg_txt=`ls -l | grep -oP "($1).txt" | wc -l`
if [[ $is_arg_txt -eq 0 ]]; then
	echo "Course not found" 1>&2
	exit
fi
is_arg_folder=`ls -l | grep -oP "($1)_stat" | wc -l`
if [[ $is_arg_folder -eq 1 ]]; then
	rm -dr "$1"_stat
fi
mkdir "$1"_stat
awk '(NR!=1)  {print $2}' "$1".txt > grades.txt
mv grades.txt ./"$1"_stat
gcc -g -Wall calc_statistics.c -o prog.exe
mv ./prog.exe ./$1_stat
cd ./$1_stat
./prog.exe
cat course_statistics.txt
cd ..
