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

diff 30.out 30.out.good
if [ "$?" -eq 0 ] ; then 
	echo "test 30 OK"
elif [ `tail -1 30.out` = "30" ] ; then
        echo "test 30 OK. Timing difference!"
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

diff 54.out 54.out.good
if [ "$?" -eq 0 ] ; then 
	echo "test 54 OK"
elif [ `tail -1 54.out` = "54" ] ; then
        echo "test 54 OK. Timing difference!"
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

diff lectorInput.out lectorInput.out.good

if [ "$?" -eq 0 ] ; then 
	echo "test lector 26 OK"
elif [ `tail -1 lectorInput.out` = "26" ] ; then
        echo "test lectorInput 26 OK. Timing difference!"
else
	echo "test lector 26 NOT OK"
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
5
" > 45.in

{ cat 45.in; sleep 1; echo "6"; sleep 1; echo "7";} | ./a.out > 45.out

diff 45.out 45.out.good
if [ "$?" -eq 0 ] ; then
        echo "test 45 OK"
elif [ `tail -1 45.out` = "45" ] ; then
        echo "test 45 OK. Timing difference!"
else
        echo "test 45 NOT OK"
fi

