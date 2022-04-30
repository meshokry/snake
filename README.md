# snake
Snake game with data structure by c++

We have two versions 
First version : implementaion with array and without the ability to play with computer->>>(The code is in "version 1" branch)
Second version: implementation with circularly doubly linked list and with the ability to play with computer->>> (The code is in main and "version 2" branch)

================================================================================================
This game is created by:
			Mostafa Darwish
			Mohammed Emad
			Abdelrahman Adel
================================================================================================

Some instructions before you run the code:
	1. Change the keyboard layout to English.
	2. If the caps button in the keyboard is on, please turn it off.
	3. The main function of the code is on game.c file so you should run the game from this file.
	4. note that you must add all the ".h" and ".c" files to the same folder that you put game.c in or you can copy the codes from these files and put it in the game file.

How to play:
	1. after running the game, you choose the width and the height of the game.
	2. then you choose the game mode either with border or without.
	3. you move the snake with "w,a,s,d" keys like any other game.
	4. the object of this game is to eat the fruit and not get hit by the pc's snake or the boarder (if you chose the game to be with boarder).
	5. when the game ends whoever have higher score wins (that means he eat more fruits than the other player).

Development of the game:
	The game has two version the first is implemented using arrays and the second is implemented using double linked lists. After measuring the time that each
	version takes to start up the game, we found that the second version is faster than the first one. We also added some new features in the second version 
	like  1. pc can play with you.
	      2. you can choose the size of the game.
	      3. you can play to modes with boarder or without it.
 
Some notes about the performance:
	After some testing we found that the startup time of the game increases as the height and the width of game increase and the that the increase on the height
	affects the startup time more than the increase on the width by a significant amount due to the code's structure.

All the time testing is done by using the below code

#include<chrono>
int main()
{
    auto start = std::chrono::steady_clock::now();
    /* THE CODE */
    auto end = std::chrono::steady_clock::now();
    double elapsed_time_ns = double (std::chrono::duration_cast <std::chrono::nanoseconds> (end - start).count());
    std::cout << "elapsed time (s): "<<elapsed_time_ns/1e9<<std::endl;

    return 0;
}
