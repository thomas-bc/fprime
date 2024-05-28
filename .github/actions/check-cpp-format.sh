#!/bin/bash

# Define the default folders
folders="Fw/Types"

FORMAT_ERROR=0

# Check if the environment variable is set
if [[ -n $FOLDERS_LIST ]]; then
    folders=$FOLDERS_LIST
fi

# Loop over the folders
for folder in $folders; do
    echo "[INFO] Processing folder: $folder"
    find $folder -name "*.cpp" -o -name "*.hpp" | fprime-util format --stdin --no-backup -q
    find $folder -name "*.cpp" -o -name "*.hpp" | xargs git diff --exit-code
    if [ $? -ne 0 ]; then
        echo "[ERROR] Files in the folder $folder are not formatted correctly."
        FORMAT_ERROR=1
    else
        echo "[INFO] $folder format OK"
    fi
done

if [ $FORMAT_ERROR -ne 0 ]; then
    echo "[ERROR] Format error. See logs above for details."
    exit 1
fi
