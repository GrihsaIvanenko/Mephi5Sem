#!/bin/bash

#com='ps -eo fuser,euser,comm'
#outp=$( $com )
#for line in $outp:
#do
#	echo "$line"
#done
#exit 0

ps -eo ruid,euid,comm |
while IFS=' ' read ruid euid comm
do
	if [ $ruid != "RUID" ]
	then
		if [ $ruid != $euid ]
		then 
			echo "$comm"
		fi
	fi
done
