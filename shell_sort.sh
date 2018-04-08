#!/bin/bash

for ((i = 1; i < 100; i++));do
	python test.py
	g++ quick_sort.cpp
	./a.out
	result=`diff output output2 | wc -l`
	if [[ result -eq 0 ]]; then
		echo "ok"
	else
		echo "$result i = $i"
		break
	fi

done
