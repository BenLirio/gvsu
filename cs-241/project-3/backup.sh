#!/bin/bash
clear
rm -r ~/backup

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
	ls -l | awk 'NR==1 { print $2 }'
}
print_disk_usage() {
	du $BACKUP_DIR -a | awk '{ print $1 }' | head -n -1
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
		echo "${1} does not exist!"
	fi
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
