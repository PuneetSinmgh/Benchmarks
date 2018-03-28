#!/bin/bash

name=$(echo $1 | cut -d '-' -f1 -)
node1=$(echo $1 | cut -d '-' -f2 - | tr -d '[')
node2=$(echo $1 | cut -d '-' -f3 - | tr -d ']')
if [ "$(hostname)" == "$name-$node1" ]
then
	echo $(hostname)
	echo $2-$3 
	./netbenchtcp s $2 $3
else
	sleep 20
	echo $(hostname)
	echo $2-$3
	./netbenchtcp c $name-$node1 $2 $3
fi
