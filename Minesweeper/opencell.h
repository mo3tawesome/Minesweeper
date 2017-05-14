#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

int filecharacters;
int i, j, k, rows_num, columns_num = 10, mines_num;
int moves_flag=0, flags_flag=0, opencells_flag=0, qmark_flag=0; // flags for display
int desired_row, desired_column, user_choice ;
int seconds_flag=0; //flag to get seconds to zero after a minute
FILE *fgamefile;
FILE *fmines_display ; // main game file that gets displayed to user
char *gamefile = "gamefile.txt";
char *mines_display = "mines_display.txt";
char *flagsDisplay = "flagsDisplay.txt";
char *save = "save.txt";
double seconds = 0.0;
double minutes = 0.0;
time_t start;
time_t stop;

int file_characters_count();
void user_choices();
void start_game();
void mainmenu();
void printfile(char filename[50]);
void endgame(int w,int row,int column);
void display_timeANDflags();



void rankfile(char name[15],int score){
    FILE*scorepointer;
    char ch;

    i =0;

    scorepointer = fopen("scoresheet.txt","r");
    while(!feof(scorepointer)){
         ch = fgetc(scorepointer);
        if(ch == '\n')
            {
        i++;
        }
    }
    fclose(scorepointer);

    i++;
    int temp;
    char temper[15];
    char names[i][15];

    int  scores[i];
    k=0;


 scorepointer=fopen("scoresheet.txt","r");
    while(!feof(scorepointer)){
    fscanf(scorepointer,"%s %d \n",&temper,&scores[k]);
    strcpy(names[k],temper);

    k++;

    }

    fclose(scorepointer);
    printf("%d",i);

     for(k=0;k<i;k++)
        printf("%s %d ",names[k],scores[k]);



      for(k=0;k<i-1;k++){

        if(scores[k]<scores[k+1]){
           temp = scores[k];
           scores[k]= scores[k+1];
            scores[k+1] = temp;

        }

    }

     for(k=0;k<i;k++)
        printf(" %d ",scores[k]);





}

int calculate_BIts(int row ,int column){
    int no_of_bits = ((((columns_num+1)*4)+1)*row+(4*column));
    return no_of_bits;
}


void  opencell(int row ,int column)
{


    FILE*valuespointer ;
    FILE*gamepointer ;




    int w =0;// counter
    int i = 0;// counter
    char values_array[filecharacters];
    char game_array [filecharacters];



        valuespointer = fopen("changedvalues.txt","r"); // puts the  values file in an array
        while ((values_array[w] = fgetc(valuespointer)) != EOF){
               w++;
            }
         fclose(valuespointer);


         gamepointer = fopen("gamefile.txt","r"); // puts the  game (X) file in an array
        while ((game_array[i] = fgetc(gamepointer)) != EOF){
               i++;
            }
         fclose(gamepointer);

        int j =i;



/// value check


        if((values_array[calculate_BIts(row,column) ] == '0')){


        game_array[calculate_BIts(row,column)] = '0'; // changes the value to the user
        values_array[calculate_BIts(row,column)] = ' '; // changes the vaue to avoid bugs
        opencells_flag++;

        valuespointer = fopen("changedvalues.txt","w");
        valuespointer = fopen("changedvalues.txt","a+"); // puts the new values array into the file
            for(i=0;i<j;i++){
               fprintf(valuespointer,"%c",values_array[i]);
            }
         fclose(valuespointer);



       gamepointer = fopen("gamefile.txt","w");
       gamepointer = fopen("gamefile.txt","a+"); // puts the game array into the file
            for(i=0;i<j;i++){
               fprintf(gamepointer,"%c",game_array[i]);
            }
         fclose(gamepointer);




        if((values_array[calculate_BIts((row-1),column)] >= '0') && (values_array[calculate_BIts((row-1),column) ] != '*') && (values_array[calculate_BIts((row-1),column)] != ' ') && (game_array[calculate_BIts((row-1),column)] == 'X')) {        // up check

            opencell((row-1),column);

        }

        if((values_array[calculate_BIts((row+1),column) ] >= '0') &&(values_array[calculate_BIts((row+1),column) ] != '*')  && (values_array[calculate_BIts((row+1),column) ] != ' ') && (game_array[calculate_BIts((row+1),column)] == 'X') ) {  //down check

        opencell((row+1),column);

        }

        if((values_array[calculate_BIts(row,column+1) ] >= '0') && (values_array[calculate_BIts(row,column+1) ] != '*') &&( column != columns_num)  && (game_array[calculate_BIts(row,column+1)] == 'X')){  //right check

        opencell(row,(column+1));

        }

        if((values_array[calculate_BIts(row,column-1)])  && (values_array[calculate_BIts(row,column-1)] != '*')&& (values_array[calculate_BIts(row,column-1)] != ' ')&&( column != 1) && (game_array[calculate_BIts(row,column-1)] == 'X')) {  //left  check

        opencell(row,(column-1));

        }
        if((values_array[calculate_BIts(row-1,column+1)])  && (values_array[calculate_BIts(row-1,column+1)] != '*')&& (values_array[calculate_BIts(row-1,column+1)] != ' ')&&( column != columns_num) && (game_array[calculate_BIts(row-1,column+1)] == 'X')) {  //right up corner check

        opencell(row-1,(column+1));

        }
        if((values_array[calculate_BIts(row-1,column-1)])  && (values_array[calculate_BIts(row-1,column-1)] != '*')&& (values_array[calculate_BIts(row-1,column-1)] != ' ')&&( column != 1)&& (game_array[calculate_BIts(row-1,column-1)] == 'X')) {  //left up corner check

        opencell(row-1,(column-1));

        }
        if((values_array[calculate_BIts(row+1,column+1)])  && (values_array[calculate_BIts(row+1,column+1)] != '*')&& (values_array[calculate_BIts(row+1,column+1)] != ' ')&& ( column != columns_num )&& (game_array[calculate_BIts(row+1,column+1)] == 'X')) {  //right down corner check

        opencell(row+1,(column+1));

        }
        if((values_array[calculate_BIts(row+1,column-1)])  && (values_array[calculate_BIts(row+1,column-1)] != '*')&& (values_array[calculate_BIts(row+1,column-1)] != ' ')&&( column != 1) && (game_array[calculate_BIts(row+1,column-1)] == 'X')) {  //left down corner check

        opencell(row+1,(column-1));

        }


    }
    else if((values_array[calculate_BIts(row,column)] != '0')&&(values_array[calculate_BIts(row,column)] != '*')&&(values_array[calculate_BIts(row,column)] != ' ')&& (game_array[calculate_BIts(row,column)] == 'X')){

    game_array[calculate_BIts(row,column)] = values_array[calculate_BIts(row,column)];
    opencells_flag++;


        gamepointer = fopen("gamefile.txt","w");
        gamepointer = fopen("gamefile.txt","a+"); // puts the game array into the file
            for(i=0;i<j;i++){
               fprintf(gamepointer,"%c",game_array[i]);
            }
         fclose(gamepointer);



    } else if (values_array[calculate_BIts(row,column)] == '*'){ // if he chooses a cell with a mine (* or 666 or M)
       game_array[calculate_BIts(row,column)] = '!';
       opencells_flag++;

        endgame(0,row,column);


    }




}




void flag_check(int row , int column ){
    FILE*valuespointer ;
    FILE*gamepointer ;


    int w =0;// counter
    int i = 0;// counter

    char values_array[filecharacters];
    char game_array[filecharacters];



        gamepointer = fopen("gamefile.txt","r"); // puts the  game (X) file in an array
        while ((game_array[i] = fgetc(gamepointer)) != EOF){
               i++;
            }
         fclose(gamepointer);


        valuespointer = fopen("changedvalues.txt","r"); // puts the  values file in an array
        while ((values_array[w] = fgetc(valuespointer)) != EOF){
               w++;
            }
         fclose(valuespointer);




      if(game_array[calculate_BIts(row,column)] == 'F'){

        if((game_array[calculate_BIts((row-1),column)]!='X' ) && (game_array[calculate_BIts((row-1),column)]!='F' )&&(game_array[calculate_BIts((row-1),column)]!='?' )) {        // up check

        flag_check((row-1),column);

        }

        if((game_array[calculate_BIts((row+1),column)]!='X' ) && (game_array[calculate_BIts((row+1),column)]!='F' )&&(game_array[calculate_BIts((row+1),column)]!='?' )) {        // DOWN check

            flag_check((row+1),column);


        }


       if((game_array[calculate_BIts(row,(column+1))]!='X' ) && (game_array[calculate_BIts(row,(column+1))]!='F' )&&(game_array[calculate_BIts(row,(column+1))]!='?' )) {        // right check

        flag_check(row,(column+1));

        }

        if((game_array[calculate_BIts(row,(column-1))]!='X' ) && (game_array[calculate_BIts(row,(column-1))]!='F' )&&(game_array[calculate_BIts(row,(column-1))]!='?' )) {           // left check

        flag_check(row,(column-1));

        }
        if((game_array[calculate_BIts(row-1,(column+1))]!='X' ) && (game_array[calculate_BIts(row-1,(column+1))]!='F' )&&(game_array[calculate_BIts(row-1,(column+1))]!='?' )) {  // right up corner  check

        flag_check(row-1,(column+1));

        }
        if((game_array[calculate_BIts(row-1,(column-1))]!='X' ) && (game_array[calculate_BIts(row-1,(column-1))]!='F' )&&(game_array[calculate_BIts(row-1,(column-1))]!='?' )) {  //left up corner check

         flag_check(row-1,(column-1));

        }
        if((game_array[calculate_BIts(row+1,(column+1))]!='X' ) && (game_array[calculate_BIts(row+1,(column+1))]!='F' )&&(game_array[calculate_BIts(row+1,(column+1))]!='?' )) {  //right down corner check

        flag_check(row+1,(column+1));

        }
        if((game_array[calculate_BIts(row+1,(column-1))]!='X' ) && (game_array[calculate_BIts(row+1,(column-1))]!='F' )&&(game_array[calculate_BIts(row+1,(column-1))]!='?' )) {  //left down corner check

        flag_check(row+1,(column-1));
        }

      }else if ((game_array[calculate_BIts(row,column)] > 0 ) && (game_array[calculate_BIts(row,column)] != 'F' ) && (game_array[calculate_BIts(row,column)] != 'X' ) && (game_array[calculate_BIts(row,column)] != '?' )){

            int flag =0;
            if(game_array[calculate_BIts(row -1,column)] == 'F'){ flag++;}  // up flag check
            if(game_array[calculate_BIts(row+1,column)] == 'F'){ flag++;}   // down flag check
            if(game_array[calculate_BIts(row,column+1)] == 'F'){ flag++;}   // right flag check
            if(game_array[calculate_BIts(row,column-1)] == 'F'){ flag++;}   // left flag check
            if(game_array[calculate_BIts(row-1,column-1)] == 'F'){ flag++;} // up left corner flag check
            if(game_array[calculate_BIts(row-1,column+1)] == 'F'){ flag++;} // up right corner flag check
            if(game_array[calculate_BIts(row+1,column-1)] == 'F'){ flag++;} // down left corner flag check
            if(game_array[calculate_BIts(row+1,column+1)] == 'F'){ flag++;} // down right corner flag check



            int counter = 0;

            // to compare the
            if(game_array[calculate_BIts(row ,column)] == '1'){counter = 1 ;}
            if(game_array[calculate_BIts(row ,column)] == '2'){counter = 2 ;}
            if(game_array[calculate_BIts(row ,column)] == '3'){counter = 3 ;}
            if(game_array[calculate_BIts(row ,column)] == '4'){counter = 4 ;}
            if(game_array[calculate_BIts(row ,column)] == '5'){counter = 5 ;}
            if(game_array[calculate_BIts(row ,column)] == '6'){counter = 6 ;}
            if(game_array[calculate_BIts(row ,column)] == '7'){counter = 7 ;}
            if(game_array[calculate_BIts(row ,column)] == '8'){counter = 8 ;}





          if (flag == counter){ // opens all Unflaged cells if no, of flags equals the value in the cell

            if(game_array[calculate_BIts(row-1,column)] != 'F'){opencell(row-1,column);}  // up flag check
            if(game_array[calculate_BIts(row+1,column)] != 'F'){opencell(row+1,column);}   // down flag check
            if(game_array[calculate_BIts(row,column+1)] != 'F'){opencell(row,column+1);}   // right flag check
            if(game_array[calculate_BIts(row,column-1)] != 'F'){ opencell(row,column-1);}   // left flag check
            if(game_array[calculate_BIts(row-1,column-1)] != 'F'){ opencell(row-1,column-1);} // up left corner flag check
            if(game_array[calculate_BIts(row-1,column+1)] != 'F'){ opencell(row-1,column+1);} // up right corner flag check
            if(game_array[calculate_BIts(row+1,column-1)] != 'F'){ opencell(row+1,column-1);} // down left corner flag check
            if(game_array[calculate_BIts(row+1,column+1)] != 'F'){ opencell(row+1,column+1);} // down right corner flag check






        }



      }


}

void endgame(int w,int row,int column){  // i takes 1/0 0 = lose,1= win

    int playerscore;
    char PLayername[50];


    FILE* gamepointer;
    FILE* valuespointer;
    char gamearray[filecharacters];
    char valuesarray[filecharacters];

    i=0;

    gamepointer = fopen(gamefile,"r");
    while((gamearray[i] = fgetc(gamepointer)) != EOF){
        i++;
    }
    fclose(gamepointer);


    i=0;
    valuespointer = fopen(mines_display,"r");
    while((valuesarray[i] = fgetc(valuespointer)) != EOF){
        i++;
    }
    fclose(valuespointer);




    if(w == 0){ // LOSE
    display_timeANDflags();

     system("cls");
     printf("\n YOU LOST BY CELL %d,%d! \n",row,column);
     printfile("flagsDisplay.txt");

     for(i=0;i<filecharacters;i++){
        if ((valuesarray[i] == '*') && (gamearray[i] != 'F')){

            gamearray[i] = 'M';

        }else   if ((valuesarray[i] != '*') && (gamearray[i] == 'F')){

             gamearray[i] = '_';

            }else   if ((valuesarray[i] == '*') && (gamearray[i] == 'X')){

             gamearray[i] = '*';

            }


     }

     gamearray[calculate_BIts(row,column)] = '!';



    for(i=0;i<filecharacters;i++){
        printf("%c",gamearray[i]);
    }





     mainmenu();


}    else if (w == 1){ // WIN


    playerscore = (pow(rows_num,4)*pow(columns_num,4))/(seconds*flags_flag);
    display_timeANDflags();

    system("cls");

    for(i=0;i<filecharacters;i++){
    if (valuesarray[i] == '*'){

            gamearray[i] = 'F';
            }
            }

    for(i=0;i<filecharacters;i++){
        printf("%c",gamearray[i]);
    }

    printf("You win !\n");
    printfile("flagsDisplay.txt");
    printf("score: %d \n",playerscore);






    printf("Enter Your Name ,Game conquerer!");
    scanf("%s",PLayername);








       mainmenu();
    }

}

void savefile(){ // this function copies data from the game file to the save file
    FILE * savepointer ; // used for the saved game file
    FILE * gamepointer;
    int i =0;
    int w = 0;
    char *singlefile= malloc(2000 *sizeof (char));


        gamepointer = fopen("gamefile.txt","r"); // puts the  game file in an array
        while ((singlefile[i] = fgetc(gamepointer)) != EOF){
               i++;
        }
        fclose(gamepointer);

        savepointer = fopen("save.txt","w");
       savepointer = fopen("save.txt","a+"); // puts the vlaues array into the new file
                for(w=0;w<i;w++){
               fprintf(savepointer,"%c",singlefile[w]);
            }
         fclose(savepointer );



}

void loadfile(){ // this function copies the data from  the saved to the game file as LOAD
    FILE * loadpointer; // used for the saved game file
    FILE * gamepointer;
    int i =0;
    int w = 0;
    char *singeleefile= malloc(2000 *sizeof (char));


        loadpointer = fopen("save.txt","r"); // puts the  game file in an array
        while ((singeleefile[i] = fgetc(loadpointer)) != EOF){
               i++;
        }
        fclose(loadpointer);

        gamepointer = fopen("gamefile.txt","w");
       gamepointer = fopen("gamefile.txt","a+"); // puts the vlaues array into the new file
                for(w=0;w<i;w++){
               fprintf(gamepointer,"%c",singeleefile[w]);
            }
         fclose(gamepointer );





}

void mainmenu(){
    int mainchoice;

    printf("Choose from the following : \n 1-Start New Game \n 2-Load Game \n 3-Display All players scores \n ");
    scanf(" %d",&mainchoice);

    if(mainchoice==1){ // generate game function

    start_game();
    user_choices();

    }else  if(mainchoice==2){ // load old game function

    loadfile();
    printfile("gamefile.txt");
    user_choices();

    }else if(mainchoice==3){ // score display fucntion


    }else{
        system("cls");
        mainmenu();

    }


}



void game_check(){
    int valuescounter =0;
    int gamecounter = 0;


    char gamearray[filecharacters];
    char valuesaray[filecharacters];

    FILE *gamepointer;
    FILE *valuespointer;

     i =0;
    valuespointer = fopen(mines_display,"r");
    while((valuesaray[i] = fgetc(valuespointer)) != EOF ){

        if(valuesaray[i] != '*'){
            valuescounter++;
        }

        i++;
    }


    i=0;
    gamepointer = fopen(gamefile,"r");
    while ((gamearray[i] = fgetc(gamepointer)) != EOF){
               i++;
            }
    fclose(gamepointer);



    for(i=0;i<filecharacters;i++){
        if(valuesaray[i] != '*'){
            if(gamearray[i] == valuesaray[i]){

                gamecounter++;
            }
        }
    }


    if(gamecounter == valuescounter){

        endgame(1,1,1);
    }



}
