#!/bin/bash

BACKUP_DIR=~/backup

create_backup_dir() {
	if [[ ! -d $BACKUP_DIR ]]
	then
		mkdir $BACKUP_DIR
	fi
}


list_files() {
	ls $BACKUP_DIR
}

print_file_count() { 
	echo "Number of files and folders: $(echo `expr $(du ~/backup/ -a | wc -l) - $(echo 1)`)"
}

print_disk_usage() {
	echo "Disk Usage: $(du $BACKUP_DIR -s | awk '{ print $1 }')KB"
}

print_help() {
	echo "backup <targetFileList> [options]"
	echo "options:"
	echo -e "\t\t-c\t\t\tCounts the number of files and displays the total disk usage"
	echo -e "\t\t-l\t\t\tLists files and directories int ${BACKUP_DIR}"
	echo -e "\t\t--help\t\t\tDisplay this message"
}

handle_flag() {
	case $1 in
		-c)
			print_file_count
			print_disk_usage
			;;
		-l)
			list_files
			;;
		--help)
			print_help
			;;
	esac
}
handle_arg() {
	if [[ -f $1 ]]
	then
		cp $1 $BACKUP_DIR
	else
		if [[ -d $1 ]]
		then
			cp -r $1 $BACKUP_DIR
		else
			echo "${1} does not exist!"
		fi
	fi
}

if [[ $# -eq 0 ]]
then
	echo "Must enter at least one argument"
fi

create_backup_dir
for arg in $@
do
	if [[ $arg == -* ]]
	then
		handle_flag $arg
	else
		handle_arg $arg
	fi
done
