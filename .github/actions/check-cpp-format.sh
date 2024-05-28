#!/bin/bash

# Define the default folders
folders="Fw/Types"

FORMAT_ERROR=0

# Check if the environment variable is set
if [[ -n $FOLDERS_LIST ]]; then
    folders=$FOLDERS_LIST
fi

# --name-only flag unless debug is set
if [[ -z $RUNNER_DEBUG ]]; then
    GIT_DIFF_FLAGS="--name-only"
fi

# Loop over the folders
for folder in $folders; do
    echo "[INFO] Processing folder: $folder"
    find $folder -name "*.cpp" -o -name "*.hpp" | fprime-util format --stdin --no-backup -q
    find $folder -name "*.cpp" -o -name "*.hpp" | xargs git diff --exit-code $GIT_DIFF_FLAGS
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
