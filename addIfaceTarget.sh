#!/bin/bash
line=$(sed -n "/^$1:/=" Makefile)
echo $line
if [ -z "$line" ]
 then
   sed -i "\$a\\\n$1:" Makefile
   sed -i "\$a\\\tmake\ -C\ ./Autogen\ $1" Makefile
   sed -i "\$a\\\nwipe$1:" Makefile
   sed -i "\$a\\\trm\ -f\ ./obj/$1*\ ./lib/lib$1.so" Makefile
 else
   echo "target $1 already in Makefile"
fi
