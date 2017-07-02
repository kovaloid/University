#!/bin/bash

count=1
cores=4

while [[ $count -lt 2*$cores+2 ]]; do
  echo "_______"
  echo "$count"
  time ./prog $count > /dev/null
  let count=count+1
done


