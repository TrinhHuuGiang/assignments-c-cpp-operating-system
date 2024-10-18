#!/bin/bash
#debug: set -x
#user input path
input_dir="${1}"

#default path of sub program
df_prg1="."
df_prg2="./build"
df_prg="$df_prg2"

#program name
prg1="order"

#first check the directory not exist
#then  check the directory not empty
if [ ! -d "$1" ] || [ -z "$(ls -A "$1")" ]
then 
	echo "[WARN] The folder [$input_dir] is empty or not exist"
	exit 1
fi

#then check the path of 'order' program exist
#then set execute permission
if [ ! -f "${df_prg1}/${prg1}" ] && [ ! -f "${df_prg2}/${prg1}" ]
then
	echo "Program [${prg1}] not available"
	echo "Path 1: ${df_prg1}/${prg1}"
    echo "Path 2: ${df_prg2}/${prg1}"
	exit 2
fi
#check if user build program in "."
#so priority run in "."
if [ -f "${df_prg1}/${prg1}" ]
then
	df_prg="$df_prg1"
fi
#then check execute permisstion
if [ ! -x "${df_prg}/${prg1}" ]
then
	echo "Setting permissions for [$prg1]"
	chmod +x "${df_prg}/${prg1}"
fi

# check folder and file in path and save an array
empty_file=()
# Function find empty file
function save_Empty_file {
    # check folder and fine in current path
    for item in "${1}/"* "${1}/."*
    do
    	if [[ "$item" == "${1}/." || "$item" == "${1}/.." ]]
    	then
    		#ignore
    		continue
	elif [ -d "$item" ]
	then
		# Recursing with sub folder
		save_Empty_file "$item"
	elif [ -f "$item" ]
	then
		# check file empty
		if [ ! -s "$item" ]
		then
			#add file into array
			empty_file+=("$item")  # Thêm tệp vào mảng
		fi
	fi
    done
}

# Finding empty files
save_Empty_file "$input_dir"

# Run a loop until user want exit
while true
do
	echo "-----------------------------"
	# Now provide link from array empty file for 'order' program
	command="${df_prg}/${prg1}"
	for link in "${empty_file[@]}"
	do
		#link list empty file to program
		command="$command \"${link}\""
	done
	# Now run 'order'
	# echo $command
	# using eval fo execute because ${command} can't detect ""
	eval ${command}
	# then get return code
	result=$?
	# echo $result
	# if user want delete, input >0
	if [[ "$result" > "0" ]]
	then
		# Delete link at array[result-1]
		# Get the file to delete based on the result
		file_to_delete="${empty_file[result-1]}"  # result-1 because array indexing starts at 0
		# Confirm deletion
		read -p "Are you sure delete $file_to_delete? (y/n): " confirm
		if [[ "$confirm" == "y" || "$confirm" == "Y" ]]
		then
			rm "$file_to_delete"  # delete file
			echo "Deleted: $file_to_delete"
			# update array using unset
            unset 'empty_file[result-1]'  # remove link from array
            # update array to remove ""
            empty_file=("${empty_file[@]}")
		fi
	fi
	
	#continue ?
	choice="n"
	while [[ "$choice" != "y" && "$choice" != "Y" ]]
	do
		read -p "Do you want to continue deleting? (y/n): " choice
		if [[ "$choice" == "n" || "$choice" == "N" ]]
		then
			echo "Exit."
        		exit 0
        fi
        done
done

