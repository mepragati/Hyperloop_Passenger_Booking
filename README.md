**Hyperloop Passenger Booking**

### Steps to run the files:
- Keep all the files in the same folder
- Run the main.cpp file (It will automatically read the input from input.txt file and perform the operation)


This repository contains files for the "Hyperloop Passenger Booking", which is based on the below problem statement. 

## Problem :
	You are to program a passenger booking system for a hyperloop transport of a particular station.

## Assumptions
1.	All the hyperloop routes with distance and the starting station will be given as input. (See the below input section for details)
2.	The speed of the pod is constant but the distance between routes will vary.
3.	A pod can travel from one connection to another in any direction in the given route. (i.e both A to B and B to A)
4.	One pod can accommodate only one passenger at a time.
5.	Passengers will be booked into their pods one by one. 
    - All passengers will start from the given starting station. 
    - Whenever a pod is started, the oldest person in the queue will board the pod first.
6.	Passengers can arrive at any time as well as pods can start at any time.
7.	Assume an infinite supply of pods and collisions will never happen.

## System Logic : 
Whenever a pod is started, the pod should pickup 
- the oldest person by age from the passenger queue and
- take the fastest route

The command line should handle the following Commands

`INIT`
`ADD_PASSENGER` 
`START_POD` 
`PRINT_Q`

The arguments and details of the commands are mentioned below.

1.	`INIT` Command  - Initializes the system with
    - Number of interconnecting routes (N) and the Starting station.
    - Next N lines denotes connection between two interconnections and their distance.
	Without initializing - all other commands should throw proper error.

2.	`ADD_PASSENGER` command adds passengers to the line.
    - `ADD_PASSENGER` X adds X number of passengers to the line. X lines following the ADD command denote the passenger's name, age and destination
    - NAME AGE DEST

3.	`START_POD` command starts pod with a passenger having highest age to his destination following the minimum interconnection points. Print the passenger name and route.
    - `START_POD` X starts X number of passengers of oldest age. (X lines are printed with name and route )
    - NAME ROUTE

4.	`PRINT_Q` command prints the number of passengers and their details who are remaining in the queue.
    - COUNT
    - NAME AGE

**This implementation read data from input.txt file and perform operations over it.**