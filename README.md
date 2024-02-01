# Population
This is a generative algo, with agents moving on a 2D Plane. 
It features probabilistical and chaotic mapping.
Here's some footage of how it looks, when executed in a terminal:


## the Plane:
The plane is a datastructure which contains a stack of agents (the so called AgentClusters) at each point. 
It can be empty, which represents that no agent is currently at that 
single point. The plane is initialized by several agents at each points.


## the Agent:
The agent increases or decreases its probability to move into a direction, 
by bumping into another agent. How much the probability is increased or decreased,
depends on the Grade, which is set to 0 at birth. It takes 5 steps until an agent
can increment its grade. 

## Motivation
The idea was to model a world in which people are bumping in each other,
changing their course, or statistical drift. People which are rarely bumping
into other people, have a lower grade. Those which have a higher grade, 
will have more influence on the direction, in which the statistically lower grade
being intends to go. 
It should show that probability is not probability, since the outcome and generation,
vary from time to time, hardly depending on the seed (time) set.
Try it out on your, and run it a couple of times, to get an own picture.

## Features:
It features a terminal UI written in ANSI-ESCAPE. 
