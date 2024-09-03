#!/usr/bin/bash

echo -n "Jugaste alguna vez de 5?"
read answer
if [ "$answer" == "si" ]
then
	echo  "Bien ahi"
else
	echo  "mal ahi"
fi
