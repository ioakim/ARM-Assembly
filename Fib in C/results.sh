#!/bin/bash
#this script accepts a flag -r followed by the name of a command
#followed by a flag -f followed by a list of file names to print
#example: ./results.sh -r "./mywc < proverb.txt" -f "results.sh
#mywc.c makefile"

clear

#using getopts to read the arguments
while getopts ":r:f:" opt; do
	case $opt in
		r)
		 command=$OPTARG;; 
		f)
		 files=$OPTARG;;
		\?)
		 echo "invalid option: -$OPTARG" >&2;;
		:)
		 echo "option -$OPTARG requires an argument" >&2
		 exit 1;;
	esac
done

#executing command
eval $command

echo

#printing the files
cat $files
