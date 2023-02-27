
//c script written by Christos Angelopoulos, Jan 2023
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
int compareTwoString(char *, char *);

void check_flags(int argc, char **argv,char **flag_short,char **flag_long,char **value_s)
{
	int v;
 	for (v = 0; v < argc; v++)
	{
  int compare1 = compareTwoString(argv[v], *flag_short);
  int compare2 = compareTwoString(argv[v], *flag_long);
		if ((compare1 == 0)||(compare2 == 0))
  {
   *value_s=argv[v+1];
  }
 }
}
int get_int_code(char *val, int code)
{
	int x,def;
	def=code;
	char vals[10][2]={"0","1","2","3","4","5","6","7","8","9"};
	for(x=0;x<10;x++)
	{
		int compare = compareTwoString(val,vals[x]);
		  if (compare == 0)
  {
			def=x;
   break;
  }
	}
   return(def);
}//get_int_code

void print_help()
{
	printf("C-PIPES\n\nThis script written in the C language will render random coloured\nzigzag lines in the terminal, while the font, speed, density and\nnumber of lines are fully costumizable.\nEach line stops once it reaches the edge of the window, only for\na new line to begin.\nThis script was inspired by this bash script:\n\nhttps://github.com/pipeseroni/pipes.sh\n\n\nUSAGE\n\nWhile in the c-pipes/ directory,first you need to\ncompile the c script:\n\n\tgcc c-pipes.c -Wall -o c-pipes\n\nThen you can run the executable:\n\n\t./c-pipes\n\nYou may want to add the flags that you prefer in order to have \nan outcome of your liking.\n\nFLAGS\n\nThe user can either use the short or the long flag version\n(i.e. c-pipes -h and c-pipes --help are the same).\n\n-h,--help\tShows this help text.\n\n-l,--lines\tDefines the number of lines to appear at the same time\n\t\ton the terminal window.\n\t\tAcceptable values 1-9 (default: 2).\n\n-s,--speed\tDefines the speed of the lines.\n\t\tAcceptable values 0-9 (default: 3).\n\n-d,--dense\tDefines how many lines will be rendered before the screen\n\t\tis empty again.\n\t\tAcceptable values 0-9 (default: 5).\n\t\t0 Screen refreshed after only one line\n\t\t9 Screen refreshed after 90 lines\n\n-f,--font\tDefines the font of the lines.\n\t\tAcceptable values 0-9 (default: 2).\n\n\t\t0 Chars used:─│┘┐└┌\t1 Chars used:─│╯╮╰╭\n\n\t\t2 Chars used:━┃┛┓┗┏\t3 Chars used:═║╝╗╚╔\n\n\t\t4 Chars used:┈┊┐┘└┌\t5 Chars used:┄┆┘┐└┌\n\n\t\t6 Chars used:┅┇┛┓┗┏\t7 Chars used:┉┋┛┓┗┏\n\n\t\t8 Chars used:↑↓↗↖↘↙←→\t9 Chars used:█\n\n-t,--turn\tDefines the probability of the lines to be straight or turn.\n\t\tAcceptable values 0-9 (default: 5).\n\t\t0: lines with frequent turns\n\t\t9:lines quite straight, less turns.\n\n-m,--monochrome\tRenders single colored lines.\n\t\tIf this flag is ommitted, each line gets a random color.\n\t\tAcceptable values 0-7.\n\t\t0 black\t1 red\n\t\t2 green\t3 yellow\n\t\t4 blue\t5 magenta\n\t\t6 cyan\t7 white\n\nEXAMPLE 1\n\n./c-pipes \n\nwill render lines with the default values.\n\nEXAMPLE 2\n\n./c-pipes -f 1 -m 2 -d 7 -l 4.\n\nwill produce a quite dense screen with 4 rapid growing green\n\nlines with rounded angles.\n\n");
	exit(0);
	}//print_help

void refresh_screen(char *(*MATRIX)[48][191],int (*COLOR)[48][191])
{
	int x,y;
	for(x=0;x<48;x++)
	{
		for(y=0;y<191;y++)
		{
			*(*(*MATRIX+x)+y)=" ";
			*(*(*COLOR+x)+y)=32;
		}
	}
}
void new_coordinates(int (*cursor_x)[10],int (*cursor_y)[10],int (*direction)[10],int *row,int *col,int (*color)[10],int *i,int *mono,int *sq_height,int *sq_width)
{
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	(*(*direction+*i))=0;
	*(*cursor_x+*i)=rand() % w.ws_row + *sq_height ;*(*cursor_y+*i)=rand() % w.ws_col + *sq_width;	
	if(*mono==11){*(*color+*i)=rand() % 7 + 31;}else{*(*color+*i)=30 + *mono;}
	*row=w.ws_row;*col=w.ws_col;
}

int main(int argc, char **argv) {
//declare variables
 char *flag_h="-h";
 char *flag_help="--help";
 char *flag_s="-s";
 char *flag_speed="--speed";
	char *speed_s="";
 int speed=3;

	char *flag_l="-l";
 char *flag_lines="--lines";
	char *lines_s="";
	int lines=1;

 char *flag_d="-d";
 char *flag_dense="--dense";
	char *dense_s="";
	int dense=5;

	char *flag_f="-f";
 char *flag_font="--font";
	char *font_s="";
 int font=2;

 char *flag_t="-t";
 char *flag_turn="--turn";
	char *turn_s="";
	int turn=5;

 char *flag_m="-m";
 char *flag_mono="--monochrome";
	char *mono_s="";
	int mono=11;
	int color[10];

	int s[10]={0,0,0,0,0,0,0,0,0,0};
	int sq_height=4;
	int sq_width=9;
	int a,b,d,i,ii,v;
	int row=48,col=191; //max values
	int direction[10],new_direction[10],new_cursor_x[10],new_cursor_y[10];
	char *element[10];
	char *north[10][2]={{"│","└"},{"│","╰"},{"┃","┗"},{"║","╚"},{"┊","└"},{"┆","└"},{"┇","┗"},{"┋","┗"},{"↑","↖"},{"█","█"}};
	char *east[10][4]={{"─","┌"},{"─","╭"},{"━","┏"},{"═","╔"},{"┈","┌"},{"┄","┌"},{"┅","┏"},{"┉","┏"},{"→","↗"},{"█","█","█","█"}};
	char *south[10][2]={{"│","┐"},{"│","╮"},{"┃","┓"},{"║","╗"},{"┊","┐"},{"┆","┐"},{"┇","┓"},{"┋","┓"},{"↓","↘"},{"█","█"}};
	char *west[10][2]={{"─","┘"},{"─","╯"},{"━","┛"},{"═","╝"},{"┈","┘"},{"┄","┘"},{"┅","┛"},{"┉","┛"},{"←","↙"},{"█","█"}};
	int loop=1;
	int cursor_x[10];
	int cursor_y[10];
	char *MATRIX[row][col];
	int MATRIX_COLOR[48][191];
 refresh_screen(&MATRIX,&MATRIX_COLOR);
	for(ii=0;ii<lines;ii++)
	{
	 new_coordinates(&cursor_x,&cursor_y,&direction,&row,&col,&color,&ii,&mono,&sq_height,&sq_width);
	}
	for (v = 0; v < argc; v++)
	{
	 int compare1 = compareTwoString(argv[v], flag_h);
	 int compare2 = compareTwoString(argv[v], flag_help);
		if ((compare1 == 0)||(compare2 == 0)){print_help();}
	}
	check_flags(argc,argv,&flag_s,&flag_speed,&speed_s);
	check_flags(argc,argv,&flag_l,&flag_lines,&lines_s);
	check_flags(argc,argv,&flag_d,&flag_dense,&dense_s);
	check_flags(argc,argv,&flag_f,&flag_font,&font_s);
	check_flags(argc,argv,&flag_t,&flag_turn,&turn_s);
	check_flags(argc,argv,&flag_m,&flag_mono,&mono_s);
	speed=get_int_code(speed_s,speed);
	lines=get_int_code(lines_s,lines);
	dense=get_int_code(dense_s,dense);
	font=get_int_code(font_s,font);
	turn=get_int_code(turn_s,turn);
	mono=get_int_code(mono_s,mono);
	if((mono>7)||(mono<0)){mono=11;}
	// LOOP***************************************************************
	while(loop==1)
	{
		while (d<1+10*dense)
		{
		for(i=0;i<lines;i++)
		{
					//DRAW LINE***********************************************************

						new_direction[i]=direction[i];
						s[i]++;

					switch (new_direction[i])
					{
						case 0: if (s[i]==1){element[i]=north[font][1];}else{element[i]=north[font][0];};
														new_cursor_x[i]=cursor_x[i]-1;new_cursor_y[i]=cursor_y[i];break;
						case 1: if (s[i]==1){element[i]=east[font][1];}else{element[i]=east[font][0];};
														new_cursor_x[i]=cursor_x[i];new_cursor_y[i]=cursor_y[i]+1;break;
						case 2: if (s[i]==1){element[i]=south[font][1];}else{element[i]=south[font][0];};
														new_cursor_x[i]=cursor_x[i]+1;new_cursor_y[i]=cursor_y[i];break;
						case 3: if (s[i]==1){element[i]=west[font][1];}else{element[i]=west[font][0];};
														new_cursor_x[i]=cursor_x[i];new_cursor_y[i]=cursor_y[i]-1;break;
					}
					//usleep(10000);
					MATRIX[cursor_x[i]][cursor_y[i]]=element[i];
					if(mono==11){MATRIX_COLOR[cursor_x[i]][cursor_y[i]]=color[i];}
					else{MATRIX_COLOR[cursor_x[i]][cursor_y[i]]=30 + mono;}
					cursor_x[i]=new_cursor_x[i];
					cursor_y[i]=new_cursor_y[i];
					direction[i]=new_direction[i];
					struct winsize w;
					ioctl(0, TIOCGWINSZ, &w);
					if ((row != w.ws_row )||( col != w.ws_col))
					{
						refresh_screen(&MATRIX,&MATRIX_COLOR);
						for(ii=0;ii<lines;ii++)
						{
						new_coordinates(&cursor_x,&cursor_y,&direction,&row,&col,&color,&ii,&mono,&sq_height,&sq_width);
						}
					}
					
					if (((direction[i]==0)||(direction[i]==2))&&(s[i]>sq_height))
					{
						d++;
						direction[i]++;
						s[i]=0;
					}
					if (((direction[i]==1)||(direction[i]==3))&&(s[i]>sq_width))
					{
						d++;
						direction[i]++;
						s[i]=0;
					}					
					if (direction[i]>3)
						{	
							new_coordinates(&cursor_x,&cursor_y,&direction,&row,&col,&color,&i,&mono,&sq_height,&sq_width);
						}					
					
				//usleep(10000);
			}//line loop
		struct winsize w;
		ioctl(0, TIOCGWINSZ, &w);
		system("clear");
		for(a=0;a+1<w.ws_row;a++)
		{
			for(b=0;b<w.ws_col;b++)
			{
				printf("\x1b[%dm%s\x1b[0m",MATRIX_COLOR[a][b],MATRIX[a][b]);
			}
		}
		printf("\n");
		usleep(30000 + speed*10000);
	}//dense
	refresh_screen(&MATRIX,&MATRIX_COLOR);
		for(ii=0;ii<lines;ii++)
		{
	 	new_coordinates(&cursor_x,&cursor_y,&direction,&row,&col,&color,&ii,&mono,&sq_height,&sq_width);
		}
	d=0;
	}//loop
}

// Comparing both the strings using pointers
//code as found in https://www.scaler.com/topics/c/string-comparison-in-c/
int compareTwoString(char *a, char *b)
{
    int flag = 0;
    while (*a != '\0' && *b != '\0') // while loop
    {
        if (*a != *b)
        {
            flag = 1;
        }
        a++;
        b++;
    }
 if(*a!='\0'||*b!='\0')
       return 1;
    if (flag == 0)
        return 0;
    else
        return 1;
}
