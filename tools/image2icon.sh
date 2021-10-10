#!/bin/sh
echo 'unsigned long icon[] = {'
identify -format '%w, %h,' $1
convert $1 -color-matrix '0 0 1 0, 0 1 0 0, 1 0 0 0, 0 0 0 1' RGBA:- | hexdump -v -e '1/4 "0x%08x,\n"'
echo '};' 
