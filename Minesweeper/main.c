#include "opencell.h"
#ifndef OPENCELL_H_INCLUDED
#define OPENCELL_H_INCLUDED
#endif // OPENCELL_H_INCLUDED



void display_timeANDflags(){

    time(&stop);// end of time counting
    seconds = difftime(stop, start); // calculate time in seconds since start
    seconds=(seconds-minutes*60);
    fgamefile = fopen("flagsDisplay.txt", "w");
    fclose(fgamefile);
    fgamefile = fopen("flagsDisplay.txt", "a");
    fprintf(fgamefile, "Number of moves:\t %d \n", moves_flag);
    fprintf(fgamefile, "Number of flags placed:\t %d \n", flags_flag);
    fprintf(fgamefile, "Number of open cells:\t %d \n", opencells_flag);
    if(seconds>59) {              //if seconds are 60, inc minutes and flag
            minutes++;
            seconds = 0;
        }
    seconds = difftime(stop, start); // calculate time in seconds since start
    seconds=(seconds-minutes*60);
    fprintf(fgamefile, "Time passed is: %g minutes and %g seconds \n",minutes, seconds);
    fclose(fgamefile);
}

void printfile(char filename[50]){ // this function can print any file with the entered name + .txt
    FILE *fpointer;
    char singlefile[filecharacters];




       int i = 0;
       int k;

        fpointer = fopen(filename,"r"); // puts the  values file in an array
        while ((singlefile[i] = fgetc(fpointer)) != EOF){
               i++;
            }
        fclose(fpointer);


         for(k=0;k<i;k++)
            printf("%c",singlefile[k]);



}


int* random_number_generator(){ // function to generate random numbers to assign the mines to
    int * array; // a one dimention array to dmalloc and store values of the places of the mines
        array = malloc(sizeof(int)*(rows_num*columns_num));
    for ( i = 0; i <(rows_num*columns_num); i++) {     // fill array
        array[i] = i;
    }

    for ( i = 0; i < (rows_num*columns_num); i++) {    // shuffle array
        int temporary = array[i];
        int randomIndex = rand() % ((rows_num*columns_num)+1);

        array[i]           = array[randomIndex];
        array[randomIndex] = temporary;
    }
    return array;
}


int* random_distribution(){ // function to randomly distribute mines

        int* r; // randomly generated row for the i th mine
        r = random_number_generator();
        int * mines1D; // a one dimention array to dmalloc and store values of the places of the mines
        mines1D = malloc(sizeof(int)*rows_num*columns_num);
        for(i=0; i<(rows_num*columns_num); i++){  //initialization of it with zero
            mines1D[i]=0;
        }
        for(i=0; i<mines_num; i++){ // for loop to generate mines and put 666 in the array if a mine is there
            mines1D[r[i]]=666;
        }


return mines1D;
}

void start_game(){
    fgamefile = fopen("gamefile.txt", "w"); // create the file
    fclose(fgamefile);
    fmines_display = fopen("mines_display.txt", "w"); // create the file
    fclose(fmines_display);
    printf("Enter number of rows: \t");
    scanf("%d", &rows_num);
    if (rows_num<2){rows_num=4;}
    printf("Enter number of columns: ");
    scanf("%d", &columns_num);
    if (columns_num<2){columns_num=4;}
    mines_num = 1 + (rows_num * columns_num)/10 ;


    int array[rows_num*columns_num];
    for ( i = 0; i <(rows_num*columns_num); i++) {     // fill array
        array[i] = i;
    }

    for ( i = 0; i < (rows_num*columns_num); i++) {    // shuffle array
        int temporary = array[i];
        int randomIndex = rand() % ((rows_num*columns_num)+1);

        array[i]           = array[randomIndex];
        array[randomIndex] = temporary;
    }
        int mines1D [rows_num*columns_num];
        for(i=0; i<(rows_num*columns_num); i++){  //initialization of it with zero
            mines1D[i]=0;
        }
        for(i=0; i<mines_num; i++){ // for loop to generate mines and put 666 in the array if a mine is there
            mines1D[array[i]]=666;
        }



    int game_array [rows_num][columns_num]; // array to store what's being projected on screen



    int flag=0; // flag to count on mines1D
    for(i=0; i<rows_num; i++){                     // loop to initialize gmae_array
        for(j=0; j<columns_num; j++){
                game_array [i][j] = 0;
            }

          flag++;
        }
    flag=0;
    for(i=0; i<rows_num; i++){                     // loop to mark the mines
        for(j=0; j<columns_num; j++){
            if (mines1D[flag]==666){
                game_array [i][j] = 666;
            }

          flag++;
        }
    }
    flag=0;

    for(i=0; i<rows_num; i++){                     // loop to check on mines and inc flag if there's an adjacent mine
        for(j=0; j<columns_num; j++){
                if ((game_array [i][j]) != 666 ){
                    if (game_array [(i-1)][(j-1)] == 666 && i != 0 && j != 0 ) {flag+=1;}
                    if (game_array [(i-1)][(j)] == 666 && i != 0) {flag+=1;}
                    if (game_array [(i-1)][(j+1)] == 666 && i != 0 && j != (columns_num-1) ) {flag+=1;}
                    if (game_array [(i)][(j-1)] == 666 && j != 0 ) {flag+=1;}
                    if (game_array [(i)][(j+1)] == 666 && j != (columns_num-1) ) {flag+=1;}
                    if (game_array [(i+1)][(j-1)] == 666 && i != (rows_num-1) && j != 0 ) {flag+=1;}
                    if (game_array [(i+1)][(j)] == 666 && i != (rows_num-1)  ) {flag+=1;}
                    if (game_array [(i+1)][(j+1)] == 666 && i != (rows_num-1) && j != (columns_num-1)) {flag+=1;}
                }

            if(flag != 0){game_array[i][j] = flag;} // puts the value of the number of adjacent mines to the cell
            flag = 0;
        }
    }

 int indexed [(rows_num+1)][(columns_num+1)]; // array to store the game aray inside but with index numbers on top
   for(i=0;i<=(rows_num); i++){                 // initialization of the array to avoid bugs
            for(j=0; j<=(columns_num); j++){
                indexed[i][j] = 0;
            }
        }
    for(i=0;i<rows_num+1; i++){                 // index filling
        for(j=0; j<(columns_num+1); j++){
            indexed [0][j]=j;
            indexed[i][0]=i;

        }
    }

    for(i=0;i<rows_num; i++){                   // storing the game array inside it with a shift 1 row and 1 column
            for(j=0; j<columns_num; j++){
                indexed[i+1][j+1] = game_array[i][j];
            }
        }
fgamefile = fopen("gamefile.txt", "a");
    for(i=0; i<rows_num+1; i++){                     /// loop to fill in the matrix of the game
        for(j=0; j<columns_num+1; j++){

                if(i==0 || j==0){                    // if it's the first row or the first column print the index instead of X
                        if(i<10 && j<10){
                            fprintf(fgamefile, "%d   ", indexed[i][j]);  // if the number is less than 2 digits, print extra space
                        }
                        else if(i>=10 || j>=10){
                            fprintf(fgamefile, "%d  ", indexed[i][j]);      // just to even out the look
                        }
                }
                else {fprintf(fgamefile, "X   ");}
                }
                    fprintf(fgamefile, "\n");
        }
    fclose(fgamefile);

   /// code to remove the X and reveal what's behind it

 fmines_display = fopen("mines_display.txt", "a");
    for(i=0; i<rows_num+1; i++){                     /// loop to fill in the matrix of the game
        for(j=0; j<columns_num+1; j++){
                if(i==0 || j==0){                    // if it's the first row or the first column print the index instead of X
                        if(i<10 && j<10){
                            fprintf(fmines_display, "%d   ", indexed[i][j]);  // if the number is less than 2 digits, print extra space
                        }
                        else if(i>=10 || j>=10){
                            fprintf(fmines_display, "%d  ", indexed[i][j]);      // just to even out the look
                        }
                }
                else if (indexed[i][j] != 666){
                        fprintf(fmines_display, "%d   ", indexed[i][j]);
                }
                else if (indexed[i][j] == 666){
                        fprintf(fmines_display, "*   ");
                }
        }

        fprintf(fmines_display, "\n");  // create new line for the next row
    }


    fclose(fmines_display);

    /// code related to open cell function

    file_characters_count();

    char  finalarray [filecharacters];
    int w=0;
    int i =0;
    FILE* Changevalauespointer;

        Changevalauespointer = fopen("mines_display.txt","r"); // puts the  values file in an array
        while ((finalarray[w] = fgetc(Changevalauespointer)) != EOF){
               w++;
            }
         fclose(Changevalauespointer);



       Changevalauespointer = fopen("changedvalues.txt","w");
       Changevalauespointer = fopen("changedvalues.txt","a+"); // puts the vlaues array into the new file
            for(i=0;i<w;i++){
               fprintf(Changevalauespointer,"%c",finalarray[i]);
            }

         fclose(Changevalauespointer );
      ///back to my code

    time(&start); // start ticking time

    system("cls");
    printfile(gamefile);
    display_timeANDflags();
    printfile(flagsDisplay);

}


void time_calc_no_filewrite(){
    time(&stop);
    seconds = difftime(stop, start);
    if(seconds>59) {              //if seconds are 60, inc minutes and flag
            minutes++;
            seconds_flag+=60;
        }
    seconds-=seconds_flag;
}



int file_characters_count(){
	char ch;
	int count=0;
	FILE *fptr;
	fptr=fopen("gamefile.txt","r");
	while((ch=fgetc(fptr))!=EOF) {
		count++;
	}
	fclose(fptr);
	filecharacters = count;
	return count;
}
int revealed_file_characters_count(){
	char ch;
	int count=0;
	FILE *fptr;
	fptr=fopen("mines_display.txt","r");
	while((ch=fgetc(fptr))!=EOF) {
		count++;
	}
	fclose(fptr);
	return count;
}


void user_choices(){
    /// flag that if a user made a choice it gets a value of one for instance the clock resets ticking
    /// and if the clock gets to a minute before this flag is detected the time is updated  and display timeANDflag is called

    printf("\n enter the desired row:\t");
    //while (!kbhit()){time_refresh();}  // update the time if nothing is pressed for a minute
    scanf("%d", &desired_row);
    if(desired_row==0 || desired_row>rows_num ){
        printf("Invalid input");
        for (i=0; i<999999999; i++){k=0;}

        system("cls");
        printfile(gamefile);
        display_timeANDflags();
        printfile(flagsDisplay);
        user_choices();
    }
    printf("enter the desired column:\t");
    //while (!kbhit()){time_refresh();}
    scanf("%d", &desired_column);
    if(desired_column==0 || desired_column>columns_num){
        printf("Invalid input");
        for (i=0; i<999999999; i++){k=0;}

        system("cls");
        printfile(gamefile);
        display_timeANDflags();
        printfile(flagsDisplay);
        user_choices();
    }
    printf("choose action:\n 1- open cell \n 2- flag cell \n 3- question mark cell \n 4- unmark cell \n 5- save \n 6- Main menu \n=>");
    //while (!kbhit()){time_refresh();}
    scanf("%d", &user_choice);
    int cell = calculate_BIts(desired_row,desired_column);     // calculating the location of the desired bit
    int file_size= file_characters_count(); // Getting the size of the file to use in an array
    char game_array [file_size]; // array of chars of the files size to put the file inside
    FILE * fpointer;

    i=0;
    fgamefile = fopen("gamefile.txt","r"); // open the file to put in an array for read
    while ((game_array[i] = fgetc(fgamefile)) != EOF){  // put it in an array game_array
            i++;
    }
    char revealed_array [file_size]; // array of chars of the files size to put the file inside
    i=0;
    fmines_display = fopen("mines_display.txt","r"); // open the file to put in an array for read
    while ((revealed_array[i] = fgetc(fmines_display)) != EOF){  // put it in an array revealed_array
            i++;
    }


       if (user_choice==1){
        moves_flag++;
        if(revealed_array[cell]=='*' && moves_flag!=0){   /// check in mines display if it makes him lose, else open it
           endgame(0,desired_row,desired_column);
        }
        else if(revealed_array[cell]=='*' && moves_flag ==0){   // if the first choice was a mine, replace the mine with a zero
            for(i=0; i<file_size; i++){                         // and vice versa
                if (revealed_array[i]=='0' ){j=i;}
            }
            int temporary = revealed_array[cell];
            revealed_array[cell]=revealed_array[j];
            revealed_array[j]=temporary;
          opencell(desired_row,desired_column);

        }
        else{
          opencell(desired_row,desired_column);
        }
            system("cls");
            printfile(gamefile);
            display_timeANDflags();
            printfile(flagsDisplay);

    }
    else if (user_choice==2){
            game_array[cell]= 'F';                 //prints the array with the modified part to the file


            fpointer = fopen("gamefile.txt","w");
            fpointer = fopen("gamefile.txt","a+");
            for(i=0; i< file_size ; i++){
            fprintf(fpointer,"%c",game_array[i] );
            }
            fclose(fpointer);


            flag_check(desired_row,desired_column);

            moves_flag++;
            flags_flag++;
            system("cls");
            printfile(gamefile);
            display_timeANDflags();
            printfile(flagsDisplay);

    }
    else if (user_choice==3){
            game_array[cell]= '?';     //prints the array with the modified part to the file
            fpointer = fopen("gamefile.txt","w");
            fpointer = fopen("gamefile.txt","a+");
            for(i=0; i< file_size ; i++){
            fprintf(fpointer,"%c",game_array[i] );
            }
            fclose(fpointer);

            moves_flag++;
            qmark_flag++;

            system("cls");
            printfile(gamefile);
            display_timeANDflags();
            printfile(flagsDisplay);

    }
    else if (user_choice==4){ //prints the array with the modified part to the file
            if (game_array[cell]=='F'){
                    flags_flag--;
                    game_array[cell]= 'X';
            }
            else if (game_array[cell]=='?'){
                    qmark_flag--;
                    game_array[cell]= 'X';
            }

            fpointer = fopen("gamefile.txt","w");
            fclose(fpointer);
            fpointer = fopen("gamefile.txt","a+");
            for(i=0; i< file_size ; i++){
            fprintf(fpointer,"%c",game_array[i] );
            }

            fclose(fpointer);
            moves_flag++;
            system("cls");
            printfile(gamefile);
            display_timeANDflags();
            printfile(flagsDisplay);

    }
    else if (user_choice==5){
        fpointer = fopen("gamefile.txt","w");
        fpointer = fopen("gamefile.txt","a+");
        for(i=0; i< file_size ; i++){
            fprintf(fpointer,"%c",game_array[i] );
        }
            fclose(fpointer);
            savefile();
            system("cls");
            printfile(gamefile);
            display_timeANDflags();
            printfile(flagsDisplay);

    }
    else if (user_choice==6){
             system("cls");
            mainmenu();
    }
    else{
        printf("Invalid input");
        for (i=0; i<999999999; i++){k=0;}
        fpointer = fopen("gamefile.txt","a");
        for(i=0; i< file_size ; i++){
            fprintf(fpointer,"%c",game_array[i] );
        }
        fclose(fpointer);
        system("cls");
        printfile(gamefile);
        display_timeANDflags();
        printfile(flagsDisplay);
        user_choices();
    }

    game_check();
    user_choices();

}


/// save function prints an extra line??! as well as print file
int main(){
 mainmenu();
return 0;
}
