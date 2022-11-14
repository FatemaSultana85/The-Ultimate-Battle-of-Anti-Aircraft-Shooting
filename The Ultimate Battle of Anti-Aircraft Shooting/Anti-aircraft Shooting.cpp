#include "iGraphics.h"
#include "bitmap_loader.h"
#include "helicopter.h"
#include "leaderboard.h"

int bgd,AA; //Image Storing Variables
int menuBG;	//Image Storing Variables
int newGame,controls;	//Function Check variales
int mainMenu=1,pauseScreen;
int missileIMG;
int AA_health = 100;
char AA_health_str[20];
int AAmoveRight=0,AAmoveLeft=0; //Antiaircraft Movement Check
int index;
int gameOver;
char userName[20];
int nameLength;
int userScore;
int menuIcon;
int gameOverIMG;
int finalScore;
int activeTyping;
char emptyString[10];
int playMusic=1;



//::::::::::::::::::::User Vehicle Anti-aircraft Movement Function:::::::::::::::::::::::
void antiaircraftMove()
{
	if(AAmoveRight==1)
		{
			AA_x+=12;
			AAmoveRight=0;
		}
	else if(AAmoveLeft==1)
		{
			AA_x-=12;
			AAmoveLeft=0;
		}
	iShowImage(AA_x,AA_y,200,130,AA);
}

//:::::::::::::::::::: Function to show Main Menu,called from iDraw:::::::::::::::::::::::
void showMainmenu()
{
	
	
		iShowImage(0, 0, 1000, 600, menuBG);
		iShowImage(43,452,200,76,menuIcon);
		iShowImage(43,372,200,76,menuIcon);
		iShowImage(43,292,200,76,menuIcon);
		iShowImage(43,212,200,76,menuIcon);

		iSetColor(0, 0, 0);
		iText(85,485,"New Game" , GLUT_BITMAP_TIMES_ROMAN_24) ;
		iText(98, 405,"Controls " , GLUT_BITMAP_TIMES_ROMAN_24) ;
		iText(78,325,"LeaderBoard " , GLUT_BITMAP_TIMES_ROMAN_24) ;
		iText(120,245,"Exit " , GLUT_BITMAP_TIMES_ROMAN_24) ;	

		iSetColor(0, 0, 0);
		iText(285,570,"Anti-aircraft Shooting : The Ultimate Battle" , GLUT_BITMAP_TIMES_ROMAN_24) ;

		gameOver = 0;
		score =0;
		sprintf(score_str,"%d",score);
		AA_health = 100;
		AA_x=0;
		generateHeli();
		nameLength=0;
		flag=0;
		strcpy(userName,emptyString);
		strcpy(level_str,"Level 1");
		dx=5;
		bullet_dx=8;
		bullet_dy=8;

}
//:::::::::::::::::::: Function for showing Controls,called from iDraw:::::::::::::::::::::::
void showControls()
	{	
		iSetColor(0,0,0);
		iFilledRectangle(0,0,1000,600);
		iSetColor(225,225,225);
		iText(470,500,"Controls",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(120,400,"Use Right Arrow nad Left Arrow to move for aiming and dodging missiles.",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(50,350,"Click LMB to shoot and take down as many enemy helicopters as possible to get more points.",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(58,300,"   Each heli takedown = 100 points and Each enemy bullet hit means 10 less Health.",GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(0,255,255);
		iFilledRectangle(800,80,100,60);
		iSetColor(0,0,0);
		iText(825,105,"Back",GLUT_BITMAP_TIMES_ROMAN_24);


	}
//:::::::Show PauseMenu messages::::::::::::::::::::
void showPauseScreen()
{
	iSetColor(0,0,0);
	iText(250,250,"Game Paused,press R to resume, Q to quit to Main Menu",GLUT_BITMAP_TIMES_ROMAN_24);

}
//:::::::Showing missile from anti-aircraft,called from iDraw()::::::::::::::::::::
void showMissile()
{
	iShowImage(missile_x,missile_y,40,70,missileIMG);
	
}
//::::::: missile movement from anti-aircraft,called by the timer funcion from main()::::::::::::::::::::
void missileMove()
{
	missile_x+=5;
	missile_y+=12;
}
//:::::::function to check colission between anti-aircraft and heli bullets ; called from iDraw()::::::::::::::::::::
void checkAAColission()
{
	if(AA_health == 0)
	{
		gameOver=1;
		
	}
	for(int k=0;k<3;k++)
		{
			if(heliShoot_x[k] >=AA_x && heliShoot_x[k] <=AA_x+200 && heliShoot_y[k] <=AA_y+80)
				{
					AA_health-=10;
					heliShoot_x[k] = h[k].heli_x;
					heliShoot_y[k] =h[k].heli_y;
				}
			iSetColor(0,0,0);
			iText(55,550,"Health",GLUT_BITMAP_TIMES_ROMAN_24);
			sprintf(AA_health_str,"%d",AA_health);
			iText(130,550,AA_health_str,GLUT_BITMAP_TIMES_ROMAN_24);
		}

}

void iDraw()
{	
	iClear();
	if(mainMenu==1)
		showMainmenu();
	
	if(newGame==1)
	{
		iShowImage(0,0,1000,600,bgd);
		Heli();
		heliShoot();
		if(AA_x==900)
			AA_x=0;
		if(AA_x<=0)
			AA_x=0;
		antiaircraftMove();

		iSetColor(0,0,0);
		iText(840,550,"Score",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(920,550,score_str,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(910,580,level_str,GLUT_BITMAP_TIMES_ROMAN_24);


		if(fireMissile==1)
		showMissile();
		checkAAColission();

		
		
	}
	if(gameOver==1)
		{
			newGame=0;
			iShowImage(0,0,1000,600,gameOverIMG);
			iSetColor(0,255,255);
			iText(370,200," Click in the box below to type your name",GLUT_BITMAP_TIMES_ROMAN_24);
			iFilledRectangle(420,120,200,50);
			iSetColor(0,0,0);
			iText(425,140,userName,GLUT_BITMAP_TIMES_ROMAN_24);
			finalScore =score;
			
			//score=0;
			//mainMenu=1;
				
		}
	if(flag==1)
		{
			ADDscore(userName,finalScore);
			mainMenu=1;
			gameOver=0;
			sortScores();
		}


	if(leaderBoard==1)
			showLeaderboard();

	if(controls==1)
		showControls();
	
	if(pauseScreen==1)
	showPauseScreen();
}

void iPassiveMouse(int x, int y)
{
		
}

void iMouseMove(int mx, int my)
{

}

void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(mx >=60 && mx<=225 && my >=460 && my<=520)
			{
				newGame=1;
				mainMenu=0;
			}
		if(mainMenu == 1 && mx >=60 && mx<=225 && my >=380 && my<=440 )
			controls=1;
		if(mainMenu == 1 && mx >=60 && mx<=225 && my >=300 && my<=360)
			leaderBoard=1;
		if(mainMenu == 1 && mx >=60 && mx<=225 && my >=220 && my<=280)
			exit(0);

		if(controls==1 && mx >=800&& mx<=900 && my >=80 && my<=140)
		{
			mainMenu=1;
			controls=0;	
		}

		if(leaderBoard==1 && mx >=800&& mx<=900 && my >=30 && my<=90)
		{
			mainMenu=1;
			leaderBoard=0;
		}
		if(newGame==1)
		{
			fireMissile=1;
			if(missile_x>=1000 || missile_y>=600 )
			{
				missile_x=AA_x+80;
				missile_y=AA_y;
				fireMissile=0;
				
			}
		}
		if(gameOver==1 && mx >=420&& mx<=620 && my >=120 && my<=170)
			activeTyping=1;


	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		
	}
}

void iKeyboard(unsigned char key)
{
	if(activeTyping==1)
	{
		userName[nameLength]=key;
		nameLength++;

		if(key== '\r')
			{
				flag=1;
				activeTyping=0;
			}
	}
	
	if(newGame==1)
	{
		if (key == 'p')
		{
			iPauseTimer(0);
			iPauseTimer(1);
			iPauseTimer(2);
			pauseScreen=1;	
		}
	
		if (key == 'r')
		{
			iResumeTimer(0);
			iResumeTimer(1);
			iResumeTimer(2);
			pauseScreen=0;
	
		}
		if (key == 'q')
		{
			newGame=0;
			mainMenu=1;
			pauseScreen=0;
			score =0;
			AA_health = 100;
			AA_x=0;
			generateHeli();
		
		}
		if(key == 'x')
		{
			fireMissile=1;
			if(missile_x>=1000 || missile_y>=600 )
			{
				missile_x=AA_x+80;
				missile_y=AA_y;
				fireMissile=0;
				
			}
		
		
		
		
		}
	}
	
}

void iSpecialKeyboard(unsigned char key)
{
	if(key == GLUT_KEY_LEFT)
	{
		AAmoveLeft =1;
		
	}
	if(key == GLUT_KEY_RIGHT)
	{
		AAmoveRight =1;
	}

}

int main()
{
	FILE *fp = fopen("Leaderboard.txt", "r");
   
	
     while(fscanf(fp,"%s %d",lb[index].name,&lb[index].scores)!=EOF)
		  index++;

	 fclose(fp);


	iInitialize(1000, 600, "Anti-aircraft Shooting : The Ultimate Battle");
	heli[0]= iLoadImage("images\\viperMoment1.png");
	heli[1]=iLoadImage("images\\viperMoment2.png");
	bgd=iLoadImage("images\\background.jpg");
	AA=iLoadImage("images\\tunguska.png");
	menuBG=iLoadImage("images\\backgroundMain.jpg");
	lbIMG=iLoadImage("images\\nlb.jpg");
	missileIMG=iLoadImage("images\\AA_missile.png");
	gameOver=iLoadImage("images\\gameover.jpg");
	menuIcon=iLoadImage("images\\menuIcon.png");
	gameOverIMG=iLoadImage("images\\gameoverIMG.png");

	generateHeli();
	iSetTimer(30,heliMove);
	iSetTimer(40,heliFireMove);
	iSetTimer(30,missileMove);
	iStart(); 

	return 0;
}

