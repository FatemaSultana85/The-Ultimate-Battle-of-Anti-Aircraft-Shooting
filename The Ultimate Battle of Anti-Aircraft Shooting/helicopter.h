#ifndef HELICOPTER_H_INCLUDED
#define HELICOPTER_H_INCLUDED

int i=0,dx=5;
int heli[2];
int heliIndex[3];
int bullet_dx=8,bullet_dy=8;
float missile_x, missile_y;// missile_dx,missile_dy;
int score;
int heliShoot_x[3],heliShoot_y[3];
char score_str[15];
int AA_x=0,AA_y=0;
int fireMissile;
char level_str[20];


struct helicopter
{
    int heli_x;
    int heli_y;

}h[3];

//::::::::::::::::function to generate helis for the first time, called from main()::::::::
void generateHeli()
{
	 for(int k=0;k<3;k++)
    {
        h[k].heli_x= 1000+rand()%550;
		h[k].heli_y = 420+rand()%130;
		heliIndex[k]=1;
		heliShoot_x[k] = h[k].heli_x;
		heliShoot_y[k] =h[k].heli_y;
    }

}
//::::::::::function for Heli movement,passed to iSetTimer function as argument in main():::::::::
void heliMove()
{
	for(int i=0;i<3;i++)
	h[i].heli_x-=dx;
}
//::::::::::::::::::::Helicopters showing function and Missile Colission with Heli:::::::::::::::
void showHeli()
{
	for(int k=0,c=0;k<3;k++,c++)
	{
		
		if(missile_x+30 >= h[k].heli_x && missile_x+30 <= h[k].heli_x+130 && missile_y+60 >= h[k].heli_y && missile_y+60 <= h[k].heli_y+65)
		{	
			missile_x=AA_x+80;
			missile_y=AA_y;
			fireMissile=0;
			heliIndex[c]=0;
			h[k].heli_x = 1000+rand()%550;
			h[k].heli_y = 420+rand()%130;	
			
			heliShoot_x[k] = h[k].heli_x;
			heliShoot_y[k] =h[k].heli_y;
			score+=100;
			sprintf(score_str,"%d",score);
			if(score>800)
			{
				dx=8;
				bullet_dx=12;
				bullet_dy=12;
				strcpy(level_str,"Level 2");
			
			}
		}
		if(missile_x+30 >=1000 || missile_y+60 >=600)
		{
			fireMissile=0;
			missile_x=AA_x+80;
			missile_y=AA_y;
		
		}
		if(heliIndex[c]==1)
		{
			if(i==0)
			{
				iShowImage(h[k].heli_x,h[k].heli_y,170,65,heli[i]);
				i++;
			}
			else if(i==1)
			{
				iShowImage(h[k].heli_x,h[k].heli_y,170,65,heli[i]);
				i--;
			}
		}	
	}	
}

//:::::::::::::::::::::::Random Cordinates of Helicopters generating function,called from iDraw()::::::::::::
void Heli()
{
	for(int k=0;k<3;k++)
	{
		if(h[k].heli_x<=0)
		{
			h[k].heli_x = 1000+rand()%550;
			h[k].heli_y = 420+rand()%130;		
			heliShoot_x[k] = h[k].heli_x;
			heliShoot_y[k] =h[k].heli_y;
			heliIndex[k]=1;
		}
	}
	showHeli();
}

//:::::::::::::::::::::::heli bullets shooting function,called from iDraw()::::::::::::

void heliShoot()
{
	for(int k=0;k<3;k++)
	{
		if(heliIndex[k]==1)
		{
			iRotate(heliShoot_x[k],heliShoot_y[k]+20,-25);
			iSetColor(0,0,0);
			iFilledRectangle(heliShoot_x[k],heliShoot_y[k]+20,4,25);
			iUnRotate();
		}
		if(heliShoot_y[k]<=0)
		{	
			heliShoot_x[k] = h[k].heli_x;
			heliShoot_y[k] =h[k].heli_y;
			iRotate(heliShoot_x[k],heliShoot_y[k]+20,-25);
			iSetColor(0,0,0);
			iFilledRectangle(heliShoot_x[k],heliShoot_y[k]+20,4,25);
			iUnRotate();
		}
	}
}
//::::::: heli bullets movement function,called by the timer funcion from main()::::::::::::::::::::
void heliFireMove()
{
	for(int k=0;k<3;k++)
	{
		heliShoot_x[k]-=bullet_dx;
		heliShoot_y[k]-=bullet_dy;
	}

}

#endif // HELICOPTER_H_INCLUDED
