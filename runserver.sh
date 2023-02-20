#!/bin/bash

if [ $# -gt 0 ]
then
	if [ $1 = "c" ]
	then
		make cleanServer
		make testServer
	fi
fi
# clear
echo " "; echo " ----------------- RUN RESULTS -------------------- "; echo " "
export LD_LIBRARY_PATH=./lib
././bin/testServer
