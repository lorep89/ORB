#!/bin/sh

if [ $# -gt 0 ]
then
	if [ $1 = "c" ]
	then
		make cleanNameServer
		make NameServer
	fi
fi
clear
echo " "; echo " ----------------- RUN RESULTS -------------------- "; echo " "
././bin/NameServer
