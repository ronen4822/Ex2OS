#!/bin/bash

echo "1
2
3
4" > 10.in
{ cat 10.in; ./RSleep 350 ; echo "6";echo "8";} | ./a.out > 10.out

diff 10.out 10.out.good
if [ "$?" -eq 0 ] ; then 
	echo "test 10 OK"
elif [ `tail -1 10.out` = "10" ] ; then
        echo "test 10 OK. Timing difference!"
else
	echo "test 10 NOT OK"
fi


echo "1
2
3
4
5" > 15.in
{ cat 15.in; echo "6"; ./RSleep 550 ; echo "6";echo "7";} | ./a.out > 15.out

diff 15.out 15.out.good
if [ "$?" -eq 0 ] ; then 
	echo "test 15 OK"
elif [ `tail -1 15.out` = "15" ] ; then
        echo "test 15 OK. Timing difference!"
else
	echo "test 15 NOT OK"
fi


echo "1
2
3
4
5
3
2
" > 20.in
{ cat 20.in; echo "6"; echo "8";} | ./a.out > 20.out

diff 20.out 20.out.good
if [ "$?" -eq 0 ] ; then 
	echo "test 20 OK"
elif [ `tail -1 20.out` = "20" ] ; then
        echo "test 20 OK. Timing difference!"
else
	echo "test 20 NOT OK"
fi


echo "1
2
3
b
b
bbb
23
12
bb
b
4
5
3
2
5
2
3
1
4
" > ERROR-35.in
{ cat ERROR-35.in ;echo "8";} | ./a.out > ERROR-35.out

if [ `tail -1 ERROR-35.out` = "35" ] ; then
	echo "test ERROR-35 OK!"
else
	echo "test ERROR-35 NOT OK!"
fi

