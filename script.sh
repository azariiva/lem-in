#!/bin/zsh

# ./generator --big-superposition > test.txt
./lem-in < test.txt > out.txt;
a=$(wc -l test.txt | awk '{printf "%s\n", $1}')
b=$(wc -l out.txt | awk '{print $1}');
expr $b - $a - 1
sed '2q;d' test.txt
