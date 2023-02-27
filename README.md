# c-pipes

![c-pipes.png](images/c-pipes.png)

This script written in the C language will render random coloured
zigzag lines in the terminal, while the font, speed, density and
number of lines are fully costumizable.
Each line stops once it reaches the edge of the window, only for
a new line to begin.
This script was inspired by this bash script:

[https://github.com/pipeseroni/pipes.sh](https://github.com/pipeseroni/pipes.sh)



## USAGE

While in the c-pipes/ directory,first you need to
 compile the c script:

    gcc c-pipes.c -Wall -o c-pipes

Then you can run the executable:

    ./c-pipes

You may want to add the flags that you prefer in order to have
an outcome of your liking.

## FLAGS

The user can either use the short or the long flag version
(i.e. c-pipes -h and c-pipes --help are the same).


|short|long|explanation|
|----|-------|-----------|
|-h|--help|	Shows this help text.|
|-l|--lines|	Defines the number of lines to appear at the same time|
|||		on the terminal window.|
|||		Acceptable values 1-9 (default: 2).|
|-s|--speed|	Defines the speed of the lines.|
|||		Acceptable values 0-9 (default: 3).|
|-d|--dense|	Defines how many lines will be rendered before |
|||the screen is empty again.|
|||		Acceptable values 0-9 (default: 5).|
|||		0 Screen refreshed after only one line|
|||		9 Screen refreshed after 90 lines|
|-f|--font|	Defines the font of the lines.|
|||		Acceptable values 0-9 (default: 2).|
|||		0: Chars used:─│┘┐└┌	1|
|||   1: Chars used:─│╯╮╰╭|
|||		2: Chars used:━┃┛┓┗┏|
|||	3 Chars used:═║╝╗╚╔|
|||		4: Chars used:┈┊┐┘└┌|
|||	5 Chars used:┄┆┘┐└┌|
|||		6: Chars used:┅┇┛┓┗┏|
|||	7 Chars used:┉┋┛┓┗┏|
|||		8 Chars used:↑↓↗↖↘↙←→	|
|||9 Chars used:█|
|-t|--turn	|Defines the probability of the lines to be straight or full of turns.|
|||		Acceptable values 0-9 (default: 5).|
|||		0: lines with frequent turns.|
|||		9: lines quite straight, less turns.|
|-m|--monochrome|	Renders single colored lines.|
|||		If this flag is omitted, each line gets a random color.|
|||		Acceptable values 0-7.|
|||	0 : black
|||	1 red|
|||	2 : green|
||| 3 yellow|
|||	4 : blue|
|||	5 : magenta|
|||	6 : cyan|
|||	7 : white|



### EXAMPLE 1

    ./c-pipes

will render lines with the default values.

![1.gif](images/1.gif)

### EXAMPLE 2

    ./c-pipes -f 1 -m 2 -d 7 -l 4

will produce a quite dense screen with 4 rapid growing green lines with rounded angles.

![2.gif](images/2.gif)
