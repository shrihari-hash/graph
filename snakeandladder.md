1. Convert Board

Convert the 2D zig-zag board into 1D.

connection[position] = destination;

If there is a snake/ladder, store its destination; otherwise keep -1.

2. Build Graph

Treat every position as a node.

From each position, dice can move 1 to 6 positions.

i → i+1, i+2, ..., i+6

If the destination has a snake/ladder, directly connect to its final destination.

3. BFS

Use BFS to find the minimum dice throws.

1 BFS level = 1 dice throw

Use visited so the same position is not processed again.

Final idea:

2D Board → 1D Graph → BFS 