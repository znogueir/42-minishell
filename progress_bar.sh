#!/bin/bash

RED="\e[38;5;1m"
GREEN="\e[38;5;2m"
RESET="\e[0m"

# echo -en "$GREEN███████████████████$RESET" 
# sleep 1
# echo -en "\r                   \r"
# sleep 1
# echo -en "$GREEN███████████████████$RESET" 
# sleep 1
# echo -en "\r"

#infinite rotation

BAR="[>---------------]"

LIBFT_SIZE=ls ./libft/ | grep .c | wc -l

printf LIBFT_SIZE

echo -en " "
while ((1))
do
	for i in {2..16}
	do
		echo -en "\r" $BAR
		BAR="${BAR:0:i-1}->${BAR:i+1}"
		sleep 0.05
	done
	for i in {16..2}
	do
		echo -en "\r" $BAR
		BAR="${BAR:0:i-1}<-${BAR:i+1}"
		sleep 0.05
	done
done