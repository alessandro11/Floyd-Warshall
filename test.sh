#!/usr/bin/env bash

for file in $(ls graph-examples/*.dot); do
    echo "$file"
done
