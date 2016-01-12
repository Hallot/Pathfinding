# Pathfinding
Various pathfinding algorithms in C++

On my machine: Intel(R) Core(TM) i7-4700HQ CPU @ 2.40GHz (Quadcore), 12GB    
Compiler: G++ 4.9.2    
On a 500x500x500 grid with some obstacles.

## The algorithms:

1.A\*: Classic A\* using hash maps for both the open and closed list.    
* Time: 38ms    
* Memory usage: 692.6kB
    
2.A\*Quick: Classic A\* using an ordered map along the hash map in the open list to keep track of the lowest cost node.
* Time: 3.3ms    
* Memory usage: 1100.9kB

3.SMA\*(4): Modification of A\*Quick that has a maximum openset size of 4, if a newnode has a higher cost than the highest-cost element of the openset and openset is full, it is rejected. Not optimal, but works well on "best case" pathfinding.
* Time: 2.3ms    
* Memory usage: 134.3kB

3.SMA\*(10): Modification of A\*Quick that has a maximum openset size of 10, if a newnode has a higher cost than the highest-cost element of the openset and openset is full, it is rejected. Not optimal, but works well on "best case" pathfinding.
* Time: 2.4ms    
* Memory usage: 143.3kB
