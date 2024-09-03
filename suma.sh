#! /usr/bin/bash
echo -n "Escribi dos enteros"
read primero
read segundo
echo $(($primero * $segundo))
echo $(($primero + $segundo))
