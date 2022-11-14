#ifndef LEADERBOARD_H_INCLUDED
#define LEADERBOARD_H_INCLUDED
int leaderBoard;
char leaderboard_str[20],lbScore_str[7];
int scoreSorting=1;
int flag=0;
int lbIMG;//Image Storing Variables
struct leaderBoard
{
    char name[30];
    int scores;

}lb[50];
void ADDscore(char _name[], int _scores)
{
	FILE *fp = fopen("Leaderboard.txt", "a");

	if (fp != NULL)
	{
		fprintf(fp, "%s ", _name);
		fprintf(fp, "%d\n", _scores);
	}

	fclose(fp);
	flag=0;
}
void sortScores()
{

	int temp;
    char s[100];

    for (int i = 0; i < 50 - 1; i++)
        {
            for (int j = 0; j<50-1-i; j++)
            {
                if (lb[j].scores < lb[j+1].scores)
                {
                    temp = lb[j].scores;
                    lb[j].scores = lb[j + 1].scores;
                    lb[j + 1].scores = temp;
                    strcpy(s, lb[j].name);
                    strcpy(lb[j].name, lb[j + 1].name);
                    strcpy(lb[j + 1].name, s);
                }
            }
 
       }
	scoreSorting =0;
}

void showLeaderboard()
{
	iClear();
	iShowImage(0,0,1000,600,lbIMG);
	iSetColor(0,255,255);
	iFilledRectangle(800,30,100,60);
	iSetColor(0,0,0);
	iText(825,55,"Back",GLUT_BITMAP_TIMES_ROMAN_24);  
    iSetColor(0,0,0);
	iText(50,555,"Name                        Score",GLUT_BITMAP_TIMES_ROMAN_24);
    for(int i=0,p=60,q=520;i<5;i++)
       {
           strcpy(leaderboard_str,lb[i].name);
           iText(p,q,leaderboard_str,GLUT_BITMAP_HELVETICA_18);
		   sprintf(lbScore_str,"%d",lb[i].scores);
		   iText(p+200,q,lbScore_str,GLUT_BITMAP_HELVETICA_18);
		   q-=45;

       
		}
	scoreSorting=1;
	
	if(scoreSorting == 1)
	sortScores();
	

}








#endif // LEADERBOARD_H_INCLUDED
