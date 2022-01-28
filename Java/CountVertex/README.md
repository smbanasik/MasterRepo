## Description

This is a school related program created in the fall of 2021. The purpose of this program is to use a breadth first search to count the number of other verticies reachable from the inputted source in a directed graph.

My method first marks the source as being visited. It then checks if the source is equal to the destination. If it is not, it loops through the adjacent verticies, checks if they have not been visited, and if so, recursively checks if the destination is reachable from that vertex.


**Note: Only the function and instances of isReachable , resetMarked, and the boolean array hasVisted are mine. Everything else was provided to me as a part of the assignment.**
