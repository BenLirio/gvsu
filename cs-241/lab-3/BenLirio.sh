#!/bin/bash

#Variables
filename=input.txt
secondfilename=input2.txt

# Task 1
grep gvsu $filename 
head -n 1 $filename
grep gvsu $filename | awk '{print $2}'

# Task 2
cp $filename $secondfilename
sed -i '/^$/d' $secondfilename
sed -i '/Linux/d' $secondfilename

# Task 3
sed -i -e "s/cis/CIS/g" $secondfilename
read -p "Please enter a string to be replaced: " originalWord
lines=$(grep ${originalWord} $secondfilename | wc -l)

# Make sure the user entered in an existing word
if [[ lines -eq 0 ]]
then
	echo "Word does not exist"
	exit 0
fi
read -p "Please enter a new sting: " newWord
sed -i -e "s/${originalWord}/${newWord}/g" $secondfilename

