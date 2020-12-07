#!/bin/bash

BACKUP_DIR=~/backup
FILES=""

copy_files_to_backup() {
	cp "{${FILES}} ${BACKUP_DIR}"
}

create_backup_dir() {
	if [[ ! -d $BACKUP_DIR ]]
	then
		mkdir $BACKUP_DIR
	fi
}


list_files() {
	ls $BACKUP_DIR
}
print_files() {
	echo "FIXME counting files"
}
print_disk_usage() {
	echo "FIXME print disk usage"
}
print_help() {
	echo "backup <targetFileList> [options]"
	echo "options:"
	echo -e "\t\t-c\t\t\t\tCounts the number of files and displays the total disk usage"
	echo -e "\t\t-l\t\t\t\tLists files and directories int ${BACKUP_DIR}"
	echo -e "\t\t--help\t\t\tDisplay this message"
}

handle_flag() {
	case $1 in
		-c)
			print_files
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
	FILES="${FILES},${arg}"
}

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
