#!/bin/bash
line=$(sed -n "/^$1Objs/=" Makefile)
echo $line
if [ -z "$line" ]
 then
   sed -i "\$a\\\n$1:" Makefile
   sed -i "\$a\\\tmake\ -C\ ./Autogen\ $1" Makefile
 else
   echo "target $1 already in Makefile"
fi
