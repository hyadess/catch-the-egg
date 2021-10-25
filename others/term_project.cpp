
# include "iGraphics.h"
# include "gl.h"
# include "windows.h"
# include "mmsystem.h"

int point=0;
int background=1;

double st_hen=0;
double nd_hen=300;
double rd_hen=600;
double speed=4;
int music=1;
double hen_1_speed=4;
double hen_2_speed=8;
double hen_3_speed=12;
int busket_x=500;
char bus[2][200]={"final_bmp//busket.bmp","final_bmp//busket_2.bmp"};
double busket_length=100;
int egg_point=1;
int busket_toggle=0;
int player_score[10];
char player_name[10][200];

//hen is laying egg......
double egg_1_break=200;
double egg_2_break=200;
double egg_3_break=200;
//.......................


int bonus_egg_speed=300;
int bonus_x;
int bonus_y;
int bonus_type=0;
int saved=0;

double falling_speed=8;
int timer=2400;

typedef struct _broken_eggs{
double n=0;
int t=30;
}broken_egg;
broken_egg broken_eggs[200];

typedef struct _hen_1{
double x=-1;
double y;
int egg_type;
}egg_place;
egg_place hen_1_egg[200];
egg_place hen_2_egg[200];
egg_place hen_3_egg[200];

char c[100];
int nu;
char pics[15][200]={"final_bmp//speed.bmp","final_bmp//time.bmp","final_bmp//busket_point.bmp","final_bmp//x2point.bmp","final_bmp//500points.bmp",
                    "final_bmp//HalfSpeed.bmp"};

typedef struct _bonus{
    double x=-1;
    double y=0;
    int type=0;


}bon;

bon bonus_pics[200];




void read_file(){
    FILE *fp;
    fp=fopen("info.txt","r");
    fscanf(fp,"%lf%lf%lf\n",&st_hen,&nd_hen,&rd_hen);
    fscanf(fp,"%lf%lf%lf\n",&hen_1_speed,&hen_2_speed,&hen_3_speed);
    fscanf(fp,"%d\n",&busket_x);
    fscanf(fp,"%lf%lf%lf\n",&egg_1_break,&egg_2_break,&egg_3_break);

    fscanf(fp,"%d%d%d%d\n",&bonus_egg_speed,&bonus_x,&bonus_y,&bonus_type);
    fscanf(fp,"%d\n",&point);
    fscanf(fp,"%d\n",&timer);
    fscanf(fp,"%lf\n",&speed);
    hen_1_speed=speed;
    hen_2_speed=speed*2;
    hen_3_speed=speed*3;
    fscanf(fp,"%d\n",&egg_point);

    fscanf(fp,"%lf\n",&falling_speed);
    fscanf(fp,"%d\n",&busket_toggle);
    fscanf(fp,"%lf\n",&busket_length);
    for(int i=0;i<200;i++)
        fscanf(fp,"%lf%lf%d\n",&hen_1_egg[i].x,&hen_1_egg[i].y,&hen_1_egg[i].egg_type);
    for(int i=0;i<200;i++)
        fscanf(fp,"%lf%lf%d\n",&hen_2_egg[i].x,&hen_2_egg[i].y,&hen_2_egg[i].egg_type);
    for(int i=0;i<200;i++)
        fscanf(fp,"%lf%lf%d\n",&hen_3_egg[i].x,&hen_3_egg[i].y,&hen_3_egg[i].egg_type);
    for(int i=0;i<200;i++)
        fscanf(fp,"%lf%d\n",&broken_eggs[i].n,&broken_eggs[i].t);





    fclose(fp);
    return;


}
void write_file(){
    FILE *fp;
    fp=fopen("info.txt","w");
    fprintf(fp,"%lf %lf %lf\n",st_hen,nd_hen,rd_hen);
    fprintf(fp,"%lf %lf %lf\n",hen_1_speed,hen_2_speed,hen_3_speed);
    fprintf(fp,"%d\n",busket_x);
    fprintf(fp,"%lf %lf %lf\n",egg_1_break,egg_2_break,egg_3_break);


    fprintf(fp,"%d %d %d %d\n",bonus_egg_speed,bonus_x,bonus_y,bonus_type);
    fprintf(fp,"%d\n",point);
    fprintf(fp,"%d\n",timer);
    fprintf(fp,"%lf\n",speed);
    fprintf(fp,"%d\n",egg_point);
    fprintf(fp,"%lf\n",falling_speed);
    fprintf(fp,"%d\n",busket_toggle);
    fprintf(fp,"%lf\n",busket_length);
    for(int i=0;i<200;i++)
        fprintf(fp,"%lf %lf %d\n",hen_1_egg[i].x,hen_1_egg[i].y,hen_1_egg[i].egg_type);
    for(int i=0;i<200;i++)
        fprintf(fp,"%lf %lf %d\n",hen_2_egg[i].x,hen_2_egg[i].y,hen_2_egg[i].egg_type);
    for(int i=0;i<200;i++)
        fprintf(fp,"%lf %lf %d\n",hen_3_egg[i].x,hen_3_egg[i].y,hen_3_egg[i].egg_type);
    for(int i=0;i<200;i++)
        fprintf(fp,"%lf %d\n",broken_eggs[i].n,broken_eggs[i].t);





    fclose(fp);
    return;
}
void read_and_write_score(int point,char* nam){
    int score[15];
    char name[15][200];
    FILE *fp;
    fp=fopen("score.txt","r");
    for(int i=0;i<10;i++){
        int temp;
        fscanf(fp,"%s %d\n",name[i],&temp);
        score[i]=temp;
        }
    fclose(fp);
    fp=fopen("score.txt","w");
    int i;
    for(i=0;i<10;i++){
        if(score[i]>point)
            fprintf(fp,"%s %d\n",name[i],score[i]);
        else break;
    }
    if(i<10){
        fprintf(fp,"%s %d\n",nam,point);
        i++;
        while(i<10){
            fprintf(fp,"%s %d\n",name[i-1],score[i-1]);
            i++;
        }
    }
    fclose(fp);
}
void reset_info(){
    FILE *fp;
    fp=fopen("info.txt","w");
    fprintf(fp,"0 300 600\n");
    fprintf(fp,"4 8 12\n");
    fprintf(fp,"500\n");
    fprintf(fp,"200 200 200\n");


    fprintf(fp,"300 0 0 0\n");
    fprintf(fp,"0\n");
    fprintf(fp,"2400\n");
    fprintf(fp,"4\n");
    fprintf(fp,"1\n");
    fprintf(fp,"8\n");
    fprintf(fp,"0\n");
    fprintf(fp,"100\n");
    for(int i=0;i<200;i++)
        fprintf(fp,"-1 0 0\n");
    for(int i=0;i<200;i++)
        fprintf(fp,"-1 0 0\n");
    for(int i=0;i<200;i++)
        fprintf(fp,"-1 0 0\n");
    for(int i=0;i<200;i++)
        fprintf(fp,"0 30\n");





    fclose(fp);
    return;


}
void show_score(){

    FILE *fp;
    fp=fopen("score.txt","r");
    for(int i=0;i<10;i++){
        int temp;
        fscanf(fp,"%s %d\n",player_name[i],&temp);
        player_score[i]=temp;
        }
    fclose(fp);



}

void iDraw()
{

    iClear();

	iSetColor(255, 255, 255);

    //playing game..............
	if(background==0){
        write_file();

        iSetColor(255, 255, 255);

        iShowBMP(0,0,"final_bmp\\2ndback.bmp");

    //converting points and time to a string and printing......
    char s[10]={'0','0','0','0','0','0','0','0','0'};
    int cur=point,h=0;
    while(cur>0){
        s[h]='0'+cur%10;
        cur=cur/10;
        h++;
    }
    strrev(s);
    if(point<0)
        point=0;
    iSetColor(0, 0, 0);
    iText(0,680,s,GLUT_BITMAP_TIMES_ROMAN_24);

    char t[10]={'0','0',':','0'};
    cur=timer,h=0;

    if(cur>=2400)
        t[3]='2';
    else if(cur>=1200)
        t[3]='1';
    else
        t[3]='0';
    int mit=(cur/20)%60;

    while(mit>0){
        t[h]='0'+mit%10;
        mit=mit/10;
        h++;
    }
    strrev(t);
    iSetColor(0, 0, 0);
    iText(850,680,t,GLUT_BITMAP_TIMES_ROMAN_24);

    //................................................


    iSetColor(0, 0, 0);
    iLine(0,550,990,550);
    iLine(0,475,990,475);
    iLine(0,400,990,400);


    for(int i=0;i<200;i++){
        if(broken_eggs[i].n!=0){
            iShowBMP2(broken_eggs[i].n,0,"final_bmp\\broken egg.bmp",0);
            broken_eggs[i].t--;
            if(broken_eggs[i].t==0)
            broken_eggs[i].n=0;

        }

    }


    iShowBMP2(busket_x,0,bus[busket_toggle],0);

    for(int i=0;i<200;i++){
        if(hen_1_egg[i].egg_type==1)
            iShowBMP2(hen_1_egg[i].x,hen_1_egg[i].y,"final_bmp\\while egg.bmp",0);
        else if(hen_1_egg[i].egg_type==4)
            iShowBMP2(hen_1_egg[i].x,hen_1_egg[i].y,"final_bmp\\rottten_egg.bmp",0);
        else if(hen_1_egg[i].egg_type==2)
            iShowBMP2(hen_1_egg[i].x,hen_1_egg[i].y,"final_bmp\\silver egg.bmp",0);

        else if(hen_1_egg[i].egg_type==3)
            iShowBMP2(hen_1_egg[i].x,hen_1_egg[i].y,"final_bmp\\golden egg.bmp",0);

    }
    for(int i=0;i<200;i++){
        if(hen_2_egg[i].egg_type==1)
            iShowBMP2(hen_2_egg[i].x,hen_2_egg[i].y,"final_bmp\\while egg.bmp",0);
        else if(hen_2_egg[i].egg_type==4)
            iShowBMP2(hen_2_egg[i].x,hen_2_egg[i].y,"final_bmp\\rottten_egg.bmp",0);
        else if(hen_2_egg[i].egg_type==2)
            iShowBMP2(hen_2_egg[i].x,hen_2_egg[i].y,"final_bmp\\silver egg.bmp",0);
        else if(hen_2_egg[i].egg_type==3)
            iShowBMP2(hen_2_egg[i].x,hen_2_egg[i].y,"final_bmp\\golden egg.bmp",0);
        }
    for(int i=0;i<200;i++){

        if(hen_3_egg[i].egg_type==1)
            iShowBMP2(hen_3_egg[i].x,hen_3_egg[i].y,"final_bmp\\while egg.bmp",0);
        else if(hen_3_egg[i].egg_type==4)
            iShowBMP2(hen_3_egg[i].x,hen_3_egg[i].y,"final_bmp\\rottten_egg.bmp",0);
        else if(hen_3_egg[i].egg_type==2)
            iShowBMP2(hen_3_egg[i].x,hen_3_egg[i].y,"final_bmp\\silver egg.bmp",0);
        else if(hen_3_egg[i].egg_type==3)
            iShowBMP2(hen_3_egg[i].x,hen_3_egg[i].y,"final_bmp\\golden egg.bmp",0);

    }








    iSetColor(255, 255, 255);
    iShowBMP2(st_hen,550,"final_bmp\\_final.bmp",0);
    iShowBMP2(nd_hen,475,"final_bmp\\_final.bmp",0);
    iShowBMP2(rd_hen,400,"final_bmp\\_final.bmp",0);
    if(bonus_x>0 && bonus_y>0)
    iShowBMP2(bonus_x,bonus_y,pics[bonus_type],0);


	}


    //time finish................
	else if(background==2){
        iShowBMP(0,0,"final_bmp\\2ndback.bmp");
        iSetColor(0,10,100);
        iText(200,600,"YOUR TIME IS FINISHED!",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(200,550,"ENTER YOUR NAME:",GLUT_BITMAP_TIMES_ROMAN_24);
        iRectangle(200,475,280,50);

        iSetColor(0,0,0);
        iText(210,490,c,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(200,400,"PRESS SPACE TO SAVE",GLUT_BITMAP_TIMES_ROMAN_24);
        if(saved){
            iText(200,300,"YOUR DATA IS SAVED!!!",GLUT_BITMAP_TIMES_ROMAN_24);
            iShowBMP2(375,100,"final_bmp\\play button.bmp",0);
            iText(430,135,"HOME",GLUT_BITMAP_TIMES_ROMAN_24);
        }

	}

    //show high score............
    else if(background==3){
        iShowBMP(0,0,"final_bmp\\2ndback.bmp");
        iSetColor(0,0,0);
        iText(200,600,"HERE IS THE TOP PLAYERS:",GLUT_BITMAP_TIMES_ROMAN_24);
        for(int i=0;i<10;i++)
            iText(200,600-(i+1)*35,player_name[i],GLUT_BITMAP_TIMES_ROMAN_24);
        for(int i=0;i<10;i++){
            char e[10]={0};
            int cu=player_score[i];
            int jh=0;
            while(cu>0){
                e[jh]='0'+cu%10;
                cu=cu/10;
                jh++;
            }
            strrev(e);
            iSetColor(0,0,0);
            iText(400,600-(i+1)*35,e,GLUT_BITMAP_TIMES_ROMAN_24);

        }
        iShowBMP2(375,100,"final_bmp\\play button.bmp",0);
        iText(430,135,"HOME",GLUT_BITMAP_TIMES_ROMAN_24);
    }

	//main page..................
	else if(background==1){
        iShowBMP(0,0,"final_bmp\\1stback.bmp");
        iSetColor(0,0,0);
        iShowBMP2(450,500,"final_bmp\\play button.bmp",0);
        iText(490,535,"RESUME",GLUT_BITMAP_TIMES_ROMAN_24);

        iShowBMP2(450,440,"final_bmp\\play button.bmp",0);
        iText(500,475,"PLAY",GLUT_BITMAP_TIMES_ROMAN_24);

        iShowBMP2(450,380,"final_bmp\\play button.bmp",0);
        iText(495,415,"SCORE",GLUT_BITMAP_TIMES_ROMAN_24);

        iShowBMP2(450,320,"final_bmp\\play button.bmp",0);
        iText(495,355,"MUSIC",GLUT_BITMAP_TIMES_ROMAN_24);

        iShowBMP2(450,260,"final_bmp\\play button.bmp",0);
        iText(510,295,"EXIT",GLUT_BITMAP_TIMES_ROMAN_24);

        iShowBMP2(800,600,"final_bmp\\play button.bmp",0);
        iText(855,635,"HELP",GLUT_BITMAP_TIMES_ROMAN_24);


	}

    //do you want to return to home page???WHILE PLAYING........
    else if(background==4){
        iShowBMP(0,0,"final_bmp\\2ndback.bmp");
        iSetColor(0,10,100);
        iText(250,500,"DO YOU WANT TO RETURN TO HOME PAGE?",GLUT_BITMAP_TIMES_ROMAN_24);
        iShowBMP2(375,375,"final_bmp\\play button.bmp",0);
        iText(435,410,"YES",GLUT_BITMAP_TIMES_ROMAN_24);
        iShowBMP2(525,375,"final_bmp\\play button.bmp",0);
        iText(600,410,"NO",GLUT_BITMAP_TIMES_ROMAN_24);


    }

    //do you want to exit..............
    else if(background==5){
        iShowBMP(0,0,"final_bmp\\2ndback.bmp");
        iSetColor(0,10,100);
        iText(400,500,"DO YOU WANT TO EXIT",GLUT_BITMAP_TIMES_ROMAN_24);
        iShowBMP2(375,375,"final_bmp\\play button.bmp",0);
        iText(435,410,"YES",GLUT_BITMAP_TIMES_ROMAN_24);
        iShowBMP2(525,375,"final_bmp\\play button.bmp",0);
        iText(600,410,"NO",GLUT_BITMAP_TIMES_ROMAN_24);


    }

    //help menu.......................
    else if(background==6){
        iShowBMP(0,0,"final_bmp\\2ndback.bmp");
        iSetColor(0,10,100);
        iText(20,650,"collect eggs and earn point",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(20,620,"white egg- 1 point",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(20,590,"silver egg- 5 points",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(20,560,"golden egg-10 points",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(20,520,"rotten egg will deduct 10 points. collect bonus egg for amazing bonuses like bigger busket,",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(20,490,"increase in time and speed,bonus points,double points for collecting eggs,slow speed etc.",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(20,300,"you will get 2 minutes to collect eggs...enjoy",GLUT_BITMAP_TIMES_ROMAN_24);

        iShowBMP2(375,100,"final_bmp\\play button.bmp",0);
        iText(430,135,"HOME",GLUT_BITMAP_TIMES_ROMAN_24);

    }

    else if(background==7){
        iShowBMP(0,0,"final_bmp\\2ndback.bmp");
        iSetColor(0,10,100);
        iText(300,500,"DO YOU WANT MUSIC TO TURN ",GLUT_BITMAP_TIMES_ROMAN_24);
        if(music)
            iText(680,500,"OFF",GLUT_BITMAP_TIMES_ROMAN_24);
        else
            iText(680,500,"ON",GLUT_BITMAP_TIMES_ROMAN_24);
        iShowBMP2(375,375,"final_bmp\\play button.bmp",0);
        iText(435,410,"YES",GLUT_BITMAP_TIMES_ROMAN_24);
        iShowBMP2(525,375,"final_bmp\\play button.bmp",0);
        iText(600,410,"NO",GLUT_BITMAP_TIMES_ROMAN_24);

    }

}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	busket_x=mx;
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)

	{
	    if(background==1){
            if(mx>=470 && mx<=600 && my>=520 && my<=570){
                read_file();
                background=0;

            }
            else if(mx>=470 && mx<=600 && my>=460 && my<=510){
                reset_info();
                read_file();
                background=0;

            }
            else if(mx>=470 && mx<=600 && my>=400 && my<=450){
                show_score();
                background=3;
            }
            else if(mx>=820 && mx<=950 && my>=620 && my<=670){
                background=6;
            }

            else if(mx>=470 && mx<=600 && my>=340 && my<=390){

                background=7;
            }



            else if(mx>=470 && mx<=600 && my>=280 && my<=330)

                background=5;

        }
        else if(background==4){
            if(mx>=390 && mx<=540 && my>=390 && my<=450){

                background=1;

            }
            else if(mx>=540 && mx<=690 && my>=390 && my<=450){
                read_file();
                background=0;

            }
        }
        else if(background==5){
            if(mx>=390 && mx<=540 && my>=390 && my<=450){

                exit(0);

            }
            else if(mx>=540 && mx<=690 && my>=390 && my<=450){

                background=1;

            }
        }
        else if(background==6){
            if(mx>=395 && mx<=545 && my>=120 && my<=170){

                background=1;

            }

        }
        else if(background==2){
            if(mx>=395 && mx<=545 && my>=120 && my<=170){
                saved=0;
                background=1;

            }

        }
        else if(background==3){
            if(mx>=395 && mx<=545 && my>=120 && my<=170){

                background=1;

            }

        }
        else if(background==7){
            if(mx>=390 && mx<=540 && my>=390 && my<=450){

                if(music){
                    music=0;
                    PlaySound(0,0,0);

                }
                else{
                    music=1;
                    PlaySound((LPCSTR) "bg_music.wav", NULL, SND_LOOP | SND_ASYNC);
                }
                background=1;
            }
            else if(mx>=540 && mx<=690 && my>=390 && my<=450){

                background=1;

            }
        }

	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if(background==2){
        char df=key;
        if(df==' '){
            saved=1;
            FILE *fp;
            fp=fopen("all_scores.txt","a");
            fprintf(fp,"%s %d\n",c,point);
            fclose(fp);
            read_and_write_score(point,c);
            point=0;
            timer=2400;
            for(int i=0;i<100;i++)
                c[i]='\0';
            nu=0;
            reset_info();
        }

        c[nu]=df;
        nu++;

    }
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{
    if(key==GLUT_KEY_HOME){
        if(background==2 || background==3){
            saved=0;
            background=1;
        }
        else if(background==0)
            background=4;

    }
    else if(key==GLUT_KEY_END)
        background=5;
    if(background==0){
        if(key==GLUT_KEY_LEFT)
        busket_x-=30;
        else if(key==GLUT_KEY_RIGHT)
        busket_x+=30;
    }
}





void changeway(){
    if(background==0){
    timer--;
    if(timer==0){
        background=2;

    }
    else{
    //hen is moving..............
    st_hen+=hen_1_speed;
    nd_hen+=hen_2_speed;
    rd_hen+=hen_3_speed;
    egg_1_break-=speed;
    egg_2_break-=speed;
    egg_3_break-=speed;
    if(st_hen>920){
        st_hen=920;
        hen_1_speed*=-1;
    }
    if(st_hen<0){
        st_hen=0;
        hen_1_speed*=-1;
    }
    if(nd_hen>920){
        nd_hen=920;
        hen_2_speed*=-1;
    }
    if(nd_hen<0){
        nd_hen=0;
        hen_2_speed*=-1;
    }
    if(rd_hen>920){
        rd_hen=920;
        hen_3_speed*=-1;
    }
    if(rd_hen<0){
        rd_hen=0;
        hen_3_speed*=-1;
    }
    //...........................

    //hen is laying eggs.........


    if(egg_1_break<=0){
        int g=rand()%11;
        int f;
        if(g<7)
            f=1;
        else if(g<8)
            f=4;

        else if(g<10)
            f=2;
        else
            f=3;

        for(int j=0;j<200;j++)
            if(hen_1_egg[j].x==-1){
                hen_1_egg[j].x=st_hen;
                hen_1_egg[j].y=550;
                hen_1_egg[j].egg_type=f;

                break;
            }

    egg_1_break=200;
    }

    if(egg_2_break<=0){
        int g=rand()%11;
        int f;
        if(g<7)
            f=1;
        else if(g<8)
            f=4;
        else if(g<10)
            f=2;
        else
            f=3;

        for(int j=0;j<200;j++)
            if(hen_2_egg[j].x==-1){
                hen_2_egg[j].x=nd_hen;
                hen_2_egg[j].y=475;
                hen_2_egg[j].egg_type=f;

                break;
            }

    egg_2_break=200;
    }

    if(egg_3_break<=0){
        int g=rand()%11;
        int f;
        if(g<7)
            f=1;
        else if(g<8)
            f=4;
        else if(g<10)
            f=2;
        else
            f=3;


        for(int j=0;j<200;j++)
            if(hen_3_egg[j].x==-1){
                hen_3_egg[j].x=rd_hen;
                hen_3_egg[j].y=400;
                hen_3_egg[j].egg_type=f;

                break;
            }

   egg_3_break=200;
    }

    //...................................

    //egg is falling and breaking........
    for(int i=0;i<200;i++){
        if(hen_1_egg[i].x!=-1){
            hen_1_egg[i].y-=falling_speed;
            if((hen_1_egg[i].y<=50 && hen_1_egg[i].y>0) && (busket_x-20<=hen_1_egg[i].x && busket_x+busket_length>=hen_1_egg[i].x)){
                    hen_1_egg[i].x=-1;
                    int y=hen_1_egg[i].egg_type;
                    if(y==1)
                        point+=egg_point;
                    else if(y==2)
                        point+=egg_point*5;
                    else if(y==4)
                        point-=egg_point*10;
                    else
                        point+=egg_point*10;

               }
            else if(hen_1_egg[i].y<0){

                for(int k=0;k<200;k++){
                    if(broken_eggs[k].n==0){
                        broken_eggs[k].n=hen_1_egg[i].x;
                        broken_eggs[k].t=30;
                        break;
                    }
                }
                hen_1_egg[i].x=-1;
                hen_1_egg[i].egg_type=0;
            }
        }

    }
    for(int i=0;i<200;i++){
        if(hen_2_egg[i].x!=-1){
            hen_2_egg[i].y-=falling_speed;
            if((hen_2_egg[i].y<=50 && hen_2_egg[i].y>0) && (busket_x-20<=hen_2_egg[i].x && busket_x+busket_length>=hen_2_egg[i].x)){
                    hen_2_egg[i].x=-1;

                    int y=hen_2_egg[i].egg_type;
                    if(y==1)
                        point+=egg_point;
                    else if(y==2)

                        point+=5*egg_point;
                    else if(y==4)
                        point-=10*egg_point;
                    else
                        point+=10*egg_point;

               }
            else if(hen_2_egg[i].y<0){

                for(int k=0;k<200;k++){
                    if(broken_eggs[k].n==0){
                        broken_eggs[k].n=hen_2_egg[i].x;
                        broken_eggs[k].t=30;

                        break;
                    }
                }
                hen_2_egg[i].x=-1;
                hen_2_egg[i].egg_type=0;
            }
        }

    }
    for(int i=0;i<200;i++){
        if(hen_3_egg[i].x!=-1){
            hen_3_egg[i].y-=falling_speed;
            if((hen_3_egg[i].y<=50 && hen_3_egg[i].y>0) && (busket_x-20<=hen_3_egg[i].x && busket_x+busket_length>=hen_3_egg[i].x)){
                    hen_3_egg[i].x=-1;
                    int y=hen_3_egg[i].egg_type;
                    if(y==1)
                        point+=egg_point;
                    else if(y==2)
                        point+=5*egg_point;
                    else if(y==4)
                        point-=10*egg_point;
                    else
                        point+=10*egg_point;


               }

            else if(hen_3_egg[i].y<0){

                for(int k=0;k<200;k++){
                    if(broken_eggs[k].n==0){
                        broken_eggs[k].n=hen_3_egg[i].x;
                        broken_eggs[k].t=30;

                        break;
                    }
                }
                hen_3_egg[i].x=-1;
                hen_3_egg[i].egg_type=0;
            }
        }

    }
    //...................................


    //bonus egg..........................

    bonus_egg_speed--;
    if(bonus_y>0){
        bonus_y-=falling_speed;
    }
    if((bonus_y<=50 && bonus_y>0) && (busket_x-20<=bonus_x && busket_x+busket_length>=bonus_x)){
        bonus_x=0;
        bonus_y=0;
        if(bonus_type==0){
            speed+=4;

            hen_1_speed=speed;
            hen_2_speed=speed*2.0;
            hen_3_speed=speed*3.0;

            falling_speed=speed*2;


        }
        else if(bonus_type==1){
            timer+=200;
        }
        else if(bonus_type==2){
            busket_toggle=1;
            busket_length=150;
        }
        else if(bonus_type==3){
            egg_point=egg_point*2;
        }
        else if(bonus_type==4){
            point+=500;
        }
        else if(bonus_type==5){
            speed-=4;
            if(speed<=0)
                speed=2;
            hen_1_speed=speed;
            hen_2_speed=speed*2.0;
            hen_3_speed=speed*3.0;


            falling_speed=speed*2;

        }


    }

    if(bonus_egg_speed<0 && bonus_y<=0){
        bonus_egg_speed=300;
        bonus_y=700;
        bonus_x=rand()%900+1;
        bonus_type=rand()%6;
        if(busket_toggle==1 && bonus_type==2)
            bonus_type=0;
    }

    //...................................
    }
    }
}

int main()
{

    iSetTimer(1,changeway);
    if(music)
        PlaySound((LPCSTR) "bg_music.wav", NULL, SND_LOOP | SND_ASYNC);
	iInitialize(990, 700, "Catch The Egg");


	return 0;
}

