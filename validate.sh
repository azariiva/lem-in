#!/bin/sh

IPATH="$HOME/goinfre/test.txt"
OPATH="$HOME/goinfre/out.txt"
ILINK="$(dirname "$0")/test-link"
OLINK="$(dirname "$0")/out-link"


if [ -z $1 ]
then
	echo "usage: ./script.sh [option]"
else
	./generator $1 > $IPATH
	if [ -s $IPATH ]
	then
		rm -f $ILINK $OLINK
		./lem-in -i $IPATH -o $OPATH
		ln -s $IPATH $ILINK
		ln -s $OPATH $OLINK
		a=$(wc -l $IPATH | awk '{printf "%s\n", $1}')
		b=$(wc -l $OPATH | awk '{print $1}')
		OUR=$(expr $b - $a - 1)
		PERF=$(sed '2q;d' $IPATH | tr -dc '0-9')
		echo "Result: $OUR/$PERF"
		python3 checker.py < $OPATH
	fi
fi
