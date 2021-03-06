#! /bin/bash

# MUSY have 1 argument as output file path.
if [ "$#" -ne 1 ]
then
echo "Invalid_Argument"
exit 1
fi

# Test if we have access to output file.
touch "$1"
if [ ! -f "$1" ]
then
echo "Cannot_Create_File"
exit 2
fi

# Clean previous output first.
echo "" > $1

# Test if git already installed.
which git > /dev/null
if [ $? -ne 0 ]
then
echo "Git_Not_Found"
exit 3
fi

let timestamp="`date +%s`%86400"
AUTO_VERSION=`date +%g%m%d_`$timestamp

GIT_VERSION=`git describe --tags --dirty`
if [ $? -ne 0 ]
then
echo "No_Git_Tag_Found"
exit 4
fi

echo "/* DO NOT MODIFY, THIS FILE IS AUTO GENERATED BY SCRIPTS.   " > $1
echo " * Generated at `date `                                     " >> $1
echo " */                                                         " >> $1

echo "#ifndef __AUTO_VERSION__" >> $1
echo "#define __AUTO_VERSION__" >> $1
echo "" >> $1
echo "#define VERSION_STRING \"$GIT_VERSION\""  >> $1
echo "#define VERSION_DESC   \"$AUTO_VERSION\"" >> $1
echo "" >> $1
echo "#endif" >> $1

exit 0

