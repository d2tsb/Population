# Population
This is a generative algo, with agents moving on a 2D Plane. 
It features probabilistical and chaotic mapping.
Here's some footage of how it looks, when executed in a terminal 
(loading the footage can be quite slow):


![alt text](https://raw.githubusercontent.com/d2tsb/gifs/main/population/execution.gif)

## the Plane:
The plane is a datastructure which contains a stack of agents (the so called AgentClusters) at each point of a 2D surface. 
It can be empty, which represents that no agent is currently at that 
single point. The plane is initialized by several agents at each points.

## the AgentCluster:
It's a container, which represents a point in space, at which 0..N* agents are currently at.
In a Term UI its state gets printed:
- a more reddish tone indicates that the cluster is visited by a lot of agents.
- a more greenish tone indicates that the grade is higher

## the Agent:
The agent increases or decreases its probability to move into a direction, 
by bumping into another agent. How much the probability is increased or decreased,
depends on the Grade, which is set to 0 at birth. It takes 5 steps until an agent
can increment its grade. 

## Motivation
The idea was to model a world in which people are bumping into each other,
changing their course, or statistical drift. People which are rarely bumping
into other people, have a lower grade. Those which have a higher grade, 
will have more impact/ influence on the direction, in which the statistically lower grade
being intends to go. 
It should show that idd variables manipulated by 
some conditions being set, cannot be recognized by white noise characteristics. The outcome and generation,
vary drastically from time to time, depending on the seed (time) set.
Try it out on your own, and run it a couple of times, to get an own picture.

## Features:
It features a terminal UI written in ANSI-ESCAPE. 
The TUI shows the current state of the Agentclusters.
It also displays the average grade count of the agents.

Lightweight and efficient selfwritten container datastructure 'Vector.h', 
which replaces the <vector> stdlib.

## Details:
the project was developed under my old git account,
some time ago, not knowing .gitignore existed.
The commits contain some binaries, which makes it 
impossible to continue the project, since its 
size bloated to 500mb+. This project may be continued under 
another name. Updates might come in future.
