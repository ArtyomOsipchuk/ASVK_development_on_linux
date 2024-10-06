#!/bin/bash

DELAY=$1
if [ "$DELAY" == "" ]; then
	DELAY=0
fi

tput clear

X=0
Y=0
FILE=$(mktemp)
FILE2=$(mktemp)
# maybe I should use UTF-8 cause it works with russian letters without LC_ALL=C
iconv -f ASCII -t UCS-2 | od -vd -An > $FILE
cat $FILE | while read -r line; do
    for word in $line; do
	case $word in
		"32")
			X=$(( X + 1 ))
			continue ;;
		"10")
			Y=$(( Y + 1 ))
        		X=0
			continue
			;;
		*)
			echo "$X $Y $word" >> $FILE2
			X=$(( X + 1 ))
	esac
    done 
done

cat $FILE2 | shuf | while read -r x y byte; do
        tput cup $y $x
	printf '%b\0' "\u$(printf '%04x' "$byte")"
	sleep $DELAY
done

ROWS=$(echo "$(stty size < /dev/tty)" | cut -d' ' -f1)
tput cup $(( ROWS )) 0

rm -f $FILE
rm -f $FILE2
