#Maxit
###Game rules
>
MaxIt is played on a game board which looks like a grid (7x7 up to 10x10). Each cell in the game board contains a number which can be either positive or negative. The players take turns selecting numbers from the game board, these numbers are added to the players cumulative score (negative numbers lower the players score).
>
The rules for selecting numbers from the game board are quite simple. The player (that's you) can select any number along a horizontal row that the cursor is on. When you have selected a number, the cursor moves to that cell on the game board and the number at that location gets added to your score and removed from the board. Your opponent (the computer) then selects a number from the game board. The computer can only select numbers along the vertical column that the cursor is on. Play continues in this fashion until there is no move available (due to an empty row or column).
>
The object of the game is to have the highest score when the game ends.
Source: http://www.craigcolvin.com/Moosesoftware/maxit_rules.html

###About the repo
Max-it game in C++. Computer uses minimax algo with alpha beta pruning to calculate his moves. Working with different grid sizes and different depths of traversing the game tree. 

**WARNING!** The game tree has enormous amount of nodes for grids larger than 4x4. Using search with big depth (more than 7) with grids larger than 8x8 may kill your RAM. Be careful! 

[Documentation](https://github.com/stoimenoff/Maxit/blob/master/doc.md)

