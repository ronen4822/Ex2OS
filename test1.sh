#!/bin/bash

echo "1
2
3
4
5
1
2
3
4
5
" > 30.in

{ cat 30.in; sleep 1; echo "6"; sleep 0;echo "7";} | ./a.out > 30.out

if [ `tail -1 30.out` = "30" ] ; then 
	echo "test 30 OK"
else
	echo "test 30 NOT OK"
fi

echo "1
2
3
4
5
1
2
3
4
5
1
2
3
4
2
3
4
5
" > 54.in

{ cat 54.in; sleep 1; echo "6"; sleep 0;echo "8";} | ./a.out > 54.out

if [ `tail -1 54.out` = "54" ] ; then 
	echo "test 54 OK"
else
	echo "test 54 NOT OK"
fi

echo "1
2
3
4
5
1
2
3
4
30
b
bb
bbb
bb
b
5
1
2
3
4
2
3
4
5
" > ERROR-54.in

{ cat ERROR-54.in; sleep 1; echo "6"; sleep 0;echo "8";} | ./a.out > ERROR-54.out

if [ `tail -1 ERROR-54.out` = "54" ] ; then 
	echo "test ERR 54 OK"
else
	echo "test ERR 54 NOT OK"
fi

echo "
5
3
2
6
5
5
1
5
6
8
" > lectorInput.in

{ cat lectorInput.in;} | ./a.out > lectorInput.out

if [ `tail -1 lectorInput.out` = "26" ] ; then 
	echo "test lector 26 OK"
else
	echo "test lector 26 NOT OK"
fi

