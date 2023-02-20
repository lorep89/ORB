#!/bin/sh
IP=$(ifconfig | grep -Eo 'inet (addr:)?([0-9]*\.){3}[0-9]*' | grep -Eo '([0-9]*\.){3}[0-9]*' | grep -v '127.0.0.1')
sed -i "4d" ./inc/def.h
sed -i "4i#define\tNSIP\t\"$IP\"" ./inc/def.h
