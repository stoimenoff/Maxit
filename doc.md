## Maxit game
### 1. Position class
Simply keeps a pair of integers - row and column coordinates of the game board. Default values are -1 and -1, meaning the position wasn't initialized. Overriden `==` operator for easier comparison between two positions.

### 2. Node class
The node object is designed to be used by the Tree class. The Tree class builds a tree for all possible moves that can be played. Each Node stores some basic information for a state of the game:

- Static constant which sets the game grid size.
- Which player has to make a move. Boolean variable which is true if it's computer turn and false otherwise.
- Current difference between computer's and player's points. 
- Depth - how many moves have been played since the begining of the game.
- Position object that stores the position of the last move which have been played.
- Node pointer to the Node's parent. (Parent node stores the previous game state.)
- Vector of pointers to the Node's children. (The Node's children are the next possible game states.)
- Vector of pointers to Position objects. Each Position in the vector is a possible next move, but the node(child) that corresponds to this state of the game haven't been created by the Tree.

**Important**: Node children are managed *only* by the Tree class. The nodes cannot generate children themselves. It is up to the tree to generate them.

Some info on functions:

- Constructor: There is no default constructor! The constructor takes four arguments: 
    - Parent pointer
    - Last move position pointer
    - Difference between points
    - Boolean variable which states whose turn is it.

    If the Parent pointer is **nullptr**, the node is the root of the tree so there is no need to store the previous game states(if there are ones). Then the depth is set to 0, otherwise it is parent's depth + 1. The constructor sets all the position from the cursor row or column to be available moves.(Row for player node and column for computer node.) It is up to the Tree class to manage them and use the `setMoveToUnavailable` function to remove unavailable moves.

- Destructor: **Node destruction is recursive!** The nodes destructs all of its children! Then destructs the Position objects in the `available_moves` vector.

- Functions used by the tree to manipulate node's children:
    - addChild: Takes a pointer to a node object as argument. If the object's cursor position is in the node's available moves(the child is a valid move from this node) it pushes it to the children vector and sets this move to unavailable to prevent children duplicates.

    - removeChild: Removes a child at given position and returns it. Overloaded and can take a Position object as argument or two integers - row and column. Used by the tree to change root.

    - setMoveToUnavailable: Remove a position object from the `available_moves` vector. Overloaded to take Position object or two integers.

- setParent function. Accepts pointer to Node(or nullptr) and sets node's parent to it.

- Some get functions

### 3. Tree class
The tree object is built by initial game grid and initial cursor position. It uses Minimax algorithm with alphabeta purning(up to certain depth) to calculate best possible move. It contains few members that describe the game and the algorithm specs:

- Static constant g_size. It is equal to the Node's class gird size constant.
- Integer MAX_NUM. It is passed to the constructor and cannot be changed. Each integer in the grid equal to MAX_NUM is considered as already taken by some of the players. So it is not possible to play there again.
- Integer MAX_DEPTH. It is passed to the constructor and cannot be changed.Determines how many moves forward the minimax algorithm should search for a best move. There is an enourmous amount of different games, so it is not possible to build the whole game tree and search on it. (or at least not in 8gb of RAM)
- Node pointer to the root of the tree. The root node corresponds to the current state of the game.
- 2D array of integers which represents the game grid at the current state.
- Position object for the best move. By default it is unitilialized position(-1, -1). It is calculated and changed by the `alphaBetaMiniMax` function when the user asks the tree to make best move with `makeBestMove` function.

Functions:

- Constructor: Takes 4 arguments: 2D array of the initial grid, initial position, and two integers - max_num and max_depth. Sets the corresponding class members to the parameters and creates a root node. Initializes the best move.

- makeMove: Takes two integers - row and column of the selected move. When the players chooses a move, the move's coordinates are passed to the function. If the move is legitimate the function makes the move and returns true, otherwise-returns false. Making the move is simple. The root of the tree have to be replaced with a new one that corresponds to the new game state. The new root is one of the current root's children. The tree uses the `removeChild` function of the root and this way gets a pointer to the new root. There is a possibility that this children of the root haven't been created. If so generate the next child of the root and try to get the new root again. This process repeats until the new root is generated, which is guaranteed to happen because the move is legitimate. After the new root is generated, call the destructor of the current root so it deletes itself and its children, which are no more needed. *Note* Here notice that `removeChild` function have removed the new root from the current one's vector of children, so when destructing the root it won't delete the new one, because it is no more in its vector of children. When the unneeded nodes are deleted, simply change the root to the new one. Set the new root parent to nullptr. Then set the number in the grid at the new root's move to MAX_NUM so point that it has been played. Finally, reset the `best_move`.

- createNextChildOf: Private function. Takes a pointer to a Node as argument. If the pointer is not nullptr and the node it points to has ungenerated children, generate the node's next child: Create a new node for the child, delete the unavailable moves and use the `addChild` function to add it to the parent.

- alphaBetaMiniMax: Calculates the root's best move with the Minimax algorithm. Modifies the `best_move` varaible to keep the best move.

- makeBestMove: Calls the alphaBetaMiniMax to calculate the best move, then calls makeMove function with the best move's position.

- printGrid: Prints the grid to the console.

- gameOver: Returns true if the root node has no children, false otherwise.

### 4. Temporary main
The main function creates a grid and plays the moves calculated by the algorithm. Also prints the game and the result.
