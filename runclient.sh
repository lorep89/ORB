#!/bin/bash

if [ $# -gt 0 ]
then
	if [ $1 = "c" ]
	then
		make cleanClient		
		make testClient
	fi
fi
# clear
echo " "; echo " ----------------- RUN RESULTS -------------------- "; echo " "
export LD_LIBRARY_PATH=./lib
././bin/testClient
