#!/bin/bash

make -C ./..
echo 'testing zero arguments'
(../philo 2> zero_arguments.txt)
output=$(diff zero_arguments.txt no_arguments.txt)

if [ -z "$output" ]
then
	echo 'OK'
else
	echo 'KO'
fi

echo 'testing seven arguments'
(../philo 1 2 3 4 5 6 2> seven_arguments.txt)
output=$(diff seven_arguments.txt too_many_arguments.txt)

if [ -z "$output" ]
then
	echo 'OK'
else
	echo 'KO'
fi

echo 'testing nonnumeric arguments'
(../philo 1a 2 3 b 2> non-num_arguments.txt)
output=$(diff non-num_arguments.txt incorrect_arguments.txt)

if [ -z "$output" ]
then
	echo 'OK'
else
	echo 'KO'
fi

echo 'testing with zero philosophers'
(../philo 0 2 3 7 2> zero-arguments.txt)
output=$(diff zero-arguments.txt incorrect_val_arguments.txt)

if [ -z "$output" ]
then
	echo 'OK'
else
	echo 'KO'
fi

echo 'testing with zero time to die'
(../philo 1 0 70 70 > zero_tt_die.txt)
output=$(diff zero_tt_die.txt zero_time_to_die.txt)

if [ -z "$output" ]
then
	echo 'OK'
else
	echo 'KO'
fi

echo 'testing one philosopher'
(../philo 1 120 70 70 | grep died > one_philo.txt)
output=$(diff one_philo.txt one_philosopher.txt)

if [ -z "$output" ]
then
	echo 'OK'
else
	echo 'KO'
fi

make fclean -C ./..