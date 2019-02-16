#include<fstream>
#include<bits/stdc++.h>

using namespace std;


#define row 17
#define col 33

//Global variables
string seperator="|---+---+---+---+---+---+---+---|";
string disk[10][10];
char current_player;
int x_super1=0, x_super2=0, x_super3=0, o_super1=0, o_super2=0, o_super3=0;


//Global variables declaration ends


// Functions

void initialize();
void print_grid();
void start_banner();
void wait_();
void new_page();
void menu();
void new_game();
int search_o();
int search_x();
void help();
void start_game();
void change_player();
void save_a();
bool load_a();
bool chk(int r,int c);
void make_move(int r,int c); // comment
string opponent(char ch);
bool valid_move_exists();
bool isFlipped(int r,int c); // comment
void super_1();
void super_2();
void super_3();



// Functions declarations ends






// Initializes the grid
void initialize()
{
    o_super1=o_super2=o_super3=x_super1=x_super2=x_super3=0;
    current_player='X';
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            disk[i][j]=" ";
        }
    }
    disk[4][4]=disk[5][5]="O";
    disk[5][4]=disk[4][5]="X";
}





// Prints the entire grid and the position of both player's disks
void print_grid()
{
   cout<<endl;

   for(int i=1;i<=row;i++){
       if(i%2==1){
           cout<<"  "<<seperator<<endl;
           continue;
       }
       cout<<9-i/2<<' ';
       for(int j=1;j<9;j++){
           cout<<"| ";
           cout<<disk[i/2][j]<<' ';
       }
       cout<<"|"<<endl;
   }
   cout<<"  ";
   for(int i=0;i<8;i++){
       cout<<"  "<<(char)('a'+i)<<" ";
   }
   cout<<endl;
   cout<<endl;

   cout<<"Score:          "<<"O = "<<search_o()<<"   "<<"X = "<<search_x()<<endl;
   cout<<"Current Player: "<<current_player<<endl;
   cout<<endl;
}






//Prints the banner
void start_banner()
{

    //Prints the banner
    for(int i=0;i<5;i++) cout<<endl;
    cout<< "\n\
        \n    OOOOO   TTTTTTT  HHH   HHH  EEEEEEE  LLL      LLL       OOOOO\
        \n   OO   OO  T  T  T   H     H    E        L        L       OO   OO\
        \n   OO   OO     T      HHHHHHH    EEEE     L        L       OO   OO\
        \n   OO   OO     T      H     H    E        L    L   L    L  OO   OO\
        \n    OOOOO     TTT    HHH   HHH  EEEEEEE  LLLLLLL  LLLLLLL   OOOOO\n\n";
    cout << "                    ____________________________\n                              THE GAME...\n\
                    ____________________________\n";


  //  After a time delay it prints a new line, which animates the banner
  for(int i=0; i<25; i++)
  {
      for (int j=0; j<100000000; j++){} // A large for loop causes a time delay
      cout<<endl;
  }
}






void wait_(){

    for (int i=0; i<1000000000; i++){ //Waits for 2 seconds using the for loop

    }
}





// Prints 1000 new line, so that the previous part of the game is inaccessible
void new_page()
{
    for(int i=0;i<1000;i++){
        cout<<endl;
    }
}






// Prints the menu and takes input from the user with a do-while loop
void menu()
{
    int input_val;
    cout<<"1. New game\n2. Load a game\n3. Help\n4. Quit\n";
    cout<<endl;

    string in;
    fflush(stdin);

    do{
        cout<<"==> ";
        getline(cin,in);
        if(in.length()==1){
            input_val=in[0]-'0';

        }
        else input_val=5;


        if (input_val==1) {
            // char tmp;
            // scanf("%c",&tmp);
            fflush(stdin);
            new_game(); // starts new game
        }
        else if (input_val==2)
        {
            fflush(stdin);
            if(load_a()==false) continue;
//            new_page();
            print_grid();
            start_game();
        }
        else if (input_val==3){
            help();
            menu();
        }
        else if (input_val==4) exit(0);
        else {
            cout<<"Invalid input. Try again"<<endl;
            continue;
        }
        break;
    }while(true);
}






// Starting a new game
void new_game()
{
    initialize();
    new_page();
    print_grid();
    start_game();

}






// Counts the number of 'O' disk in the grid
int search_o()
{
   int counter_o=0;
   for (int i=1; i<9; i++){
       for (int j=1; j<9; j++)
       {
           if (disk[i][j]=="O") counter_o++;
       }
   }
   return counter_o;
}






// Counts the number of 'O' disk in the grid
int search_x()
{
   int counter_x=0;
   for (int i=1; i<9; i++){
       for (int j=1; j<9; j++)
       {
           if (disk[i][j]=="X") counter_x++;
       }
   }
   return counter_x;
}






void help()
{
    new_page();
    cout<< "\n    INSTRUCTIONS:\n    =============\n\n\
    1. Type your command and press 'Enter' for execution.\n\
    2. Type the co-ordinate of your move in the style <column alphabet> <space> <row number> \
    (E.g: For moving to the co-ordinate with column c and row 3, the command should be: ==> c 3)\n\
    3. For going back to the menu, type 'menu' in the command line\n\
    4. To skip a move, type 'next player'\n\n\
    5. To save the game type 'save a.txt'\n\
    SUPER POWERS:\n\
    >>You have 3 Super Powers, each of them can be used only once. \n\
    >>Type 'super1' for flipping the row that has the highest number of your opponent's disk into your own disk.\n\
    >>Type 'super2' for flipping the column that has the highest number of your opponent's disk into your own disk.\n\
    >>Type 'super3' for making a move ANYWHERE in the board.\
    .\n\n\n";
}






// Prints the '==>' sign and takes command from the player and executes a function for different commands
void start_game()
{
    string input_st;
//    char tmp;
//    scanf("%c",&tmp);

    while(true){
        cout<<"==> ";
        if(valid_move_exists()==false){ // Checks if valid move exists
            cout<<"No valid move available for Player \'"<<current_player<<"\'";
            wait_();
            change_player();
             new_page();
            print_grid();
            continue;
        }
        getline(cin,input_st);  // Takes the input from the user as a string with the getline() function

        if (input_st== "menu"){
            new_page();
            menu();
            return;
        }

        else if (input_st == "next player")
        {
            change_player();
        }

        else if (input_st == "super1")
        {
            if ((current_player == 'O' && o_super1) || (current_player == 'X' && x_super1))
            {
                cout<<"Super power 1 is already used!!!"<<endl;
                continue;
            }
            else
            {
                super_1();
                change_player();
            }
        }
        else if (input_st == "super2")
        {
            if ((current_player == 'O' && o_super2) || (current_player == 'X' && x_super2))
            {
                cout<<"Super power 2 is already used!!!"<<endl;
                continue;
            }
            else
            {
                super_2();
                change_player();
            }
        }
        else if (input_st == "super3")
        {
            if ((current_player == 'O' && o_super3) || (current_player == 'X' && x_super3))
            {
                cout<<"Super power 3 is already used!!!"<<endl;
                continue;
            }
            else
            {
                cout<<"S ==> ";
                super_3();
                change_player();
            }
        }
        else if (input_st == "save a.txt")
        {
            save_a();
            continue;
        }
        else if(input_st.length()==3 && input_st[0]>='a' && input_st[0]<='h' && input_st[1]==' ' && input_st[2]>='1' && input_st[2]<='8'){

            int r,c;

            c=input_st[0]-'a'+1;
            r='9'-input_st[2];

            //check_move();



            if(isFlipped(r,c)==false){
                cout<<"Invalid Move. Please try again! "<<endl;
                continue;
            }
            make_move(r,c);

            change_player();

        }
        else{
            cout<<"Invalid Command. Please try again. "<<endl;
            continue;
        }

        new_page();
        print_grid();

        bool a,b,game_over=false;
        a=valid_move_exists();
        change_player();
        b=valid_move_exists();
        change_player();
        if(a==false && b==false){
            game_over=true;
        }



        if(search_o()+search_x()==64 || game_over) {   //When the grid is full, or the game is over, it declares the winner
                cout<<"########################"<<endl;
                cout<<"#                      #"<<endl;
            if(search_o()<search_x()){                  // Searches for the winner
                cout<<"### Player 1 WINS!!! ###"<<endl;
            }
            else if(search_o()>search_x()){
                cout<<"### Player 2 WINS!!! ###"<<endl;
            }
            else{
                cout<<"###  Match DRAW !!!  ###"<<endl;
            }
                cout<<"#                      #"<<endl;
                cout<<"########################"<<endl;
            break;
        }
    }
    cout<<endl;
    cout<<endl;
    menu();

}






void change_player()
{
    if (current_player=='O') current_player = 'X';
    else if (current_player == 'X') current_player = 'O';
}






/* Creates a file named a.txt and saves the values in the grid, how many times
each of the super powers are used and current player of the game to the file*/
void save_a()
{
    ofstream myfile;
    myfile.open ("a.txt");
    //myfile << "Sample text to write on file.\n";

    if(myfile.is_open()==false){
        cout<<"Unable to open file!"<<endl;
        return;
    }


    for (int i=1; i<=8; i++)
    {
        for (int j=1; j<=8; j++)
        {
            if(disk[i][j]==" "){
                myfile<<'-';       // Replaces the <space>'s in the grid with a Dash '-' and then stores it in the file
            }
            else myfile<<disk[i][j];
        }
        myfile<<endl;
    }
    myfile<<current_player<<endl;
    myfile<<x_super1<<endl<< x_super2<<endl<< x_super3<<endl<< o_super1<<endl<< o_super2<<endl<< o_super3<<endl; // super power variables
    cout<<"Game successfully saved on a.txt.\n";
    myfile.close();
}






// A boolian function that opens the file named a.txt and reads the values saved earlier
// If it cannot open a file it returns 'false'
bool load_a()
{
    string loader;
    ifstream myfile ("a.txt");

    if(myfile.is_open()==false){
        cout<<"Unable to open file!"<<endl;
        return false;
    }

    for(int i=1;i<9;i++){
        getline(myfile,loader);
        // cout<<"loader: "<<loader.length()<<endl;
        for(int j=0;j<8;j++){
            if(loader[j]=='-') disk[i][j+1]=" ";
            else if(loader[j]=='X') disk[i][j+1]="X";
            else disk[i][j+1]="O";
        }
    }
    getline(myfile,loader);
    current_player=loader[0];

    int temp;
    getline(myfile,loader);
    x_super1=loader[0]-'0';
    getline(myfile,loader);
    x_super2=loader[0]-'0';
    getline(myfile,loader);
    x_super3=loader[0]-'0';
    getline(myfile,loader);
    o_super1=loader[0]-'0';
    getline(myfile,loader);
    o_super2=loader[0]-'0';
    getline(myfile,loader);
    o_super3=loader[0]-'0';


    return true;
}







bool chk(int r,int c)
{
    if(r>8 || c>8 || r<1 || c<1) return false;
    return true;
}






// this function takes a cell position as parameter and flips corresponding cells according to the othello game rules
void make_move(int r,int c)
{
    string op=(current_player=='X' ? "O" : "X");

    string cur= (current_player=='X' ? "X" : "O");

    //cout<<cur<<' '<<op<<endl;

    int temp_r=r-1,temp_c=c-1;

    while(chk(temp_r,temp_c)){                  //flips left top diagonal line
        if(disk[temp_r][temp_c]==cur){
            while(temp_r!=r){
                disk[temp_r][temp_c]=cur;
                temp_r++;
                temp_c++;
            }
            break;
        }
        else if(disk[temp_r][temp_c]!=op){
            break;
        }
        temp_r--;
        temp_c--;
    }

    temp_r=r+1;
    temp_c=c+1;
    while(chk(temp_r,temp_c)){                  //flips right top diagonal line
        if(disk[temp_r][temp_c]==cur){
            while(temp_r!=r){
                disk[temp_r][temp_c]=cur;
                temp_r--;
                temp_c--;
            }
            break;
        }
        else if(disk[temp_r][temp_c]!=op){
            break;
        }
        temp_r++;
        temp_c++;
    }


    temp_r=r+1;
    temp_c=c-1;
    while(chk(temp_r,temp_c)){                  //flips left bottom diagonal line
        if(disk[temp_r][temp_c]==cur){
            while(temp_r!=r){
                disk[temp_r][temp_c]=cur;
                temp_r--;
                temp_c++;
            }
            break;
        }
        else if(disk[temp_r][temp_c]!=op){
            break;
        }
        temp_r++;
        temp_c--;
    }


    temp_r=r-1;
    temp_c=c+1;
    while(chk(temp_r,temp_c)){                  //flips right bottom diagonal line
        if(disk[temp_r][temp_c]==cur){
            while(temp_r!=r){
                disk[temp_r][temp_c]=cur;
                temp_r++;
                temp_c--;
            }
            break;
        }
        else if(disk[temp_r][temp_c]!=op){
            break;
        }
        temp_r--;
        temp_c++;
    }



    temp_r=r;
    temp_c=c+1;
    while(chk(temp_r,temp_c)){                      //flips right side
        if(disk[temp_r][temp_c]==cur){
            while(temp_c!=c){
                disk[temp_r][temp_c]=cur;
                temp_c--;
            }
            break;
        }
        else if(disk[temp_r][temp_c]!=op){
            break;
        }
        temp_c++;
    }


    temp_r=r-1;
    temp_c=c;
    while(chk(temp_r,temp_c)){                  //flips left side
        if(disk[temp_r][temp_c]==cur){
            while(temp_r!=r){
                disk[temp_r][temp_c]=cur;
                temp_r++;
            }
            break;
        }
        else if(disk[temp_r][temp_c]!=op){
            break;
        }
        temp_r--;
    }


    temp_r=r+1;
    temp_c=c;
    while(chk(temp_r,temp_c)){                  //flips top side
        if(disk[temp_r][temp_c]==cur){
            while(temp_r!=r){
                disk[temp_r][temp_c]=cur;
                temp_r--;
            }
            break;
        }
        else if(disk[temp_r][temp_c]!=op){
            break;
        }
        temp_r++;
    }

    temp_r=r;
    temp_c=c-1;
    while(chk(temp_r,temp_c)){              //flips bottom side
        if(disk[temp_r][temp_c]==cur){
            while(temp_c!=c){
                disk[temp_r][temp_c]=cur;
                temp_c++;
            }
            break;
        }
        else if(disk[temp_r][temp_c]!=op){
            break;
        }
        temp_c--;
    }


    disk[r][c]=cur;




}







string opponent(char ch)
{
    if(ch=='X') return "O";
    else if(ch=='O') return "X";
    return " ";
}






// Checks the existence of a valid move and returns false if doesn't
bool valid_move_exists()
{
//    cout<<"Valid MOVES: "<<endl;
    bool flag=false;

    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(disk[i][j]==" "){
                if(isFlipped(i,j)==true){
//                    cout<<(char)('a'+j-1)<<' '<<9-i<<endl;
                    flag=true;
                }
            }
        }
    }
//    cout<<endl;
//    cout<<"=> ";
    return flag;

}







// same function like make_move() but here we shall not change any cell instead we'll check if any cell can be flipped
bool isFlipped(int r,int c)
{

    string op=(current_player=='X' ? "O" : "X");

    string cur= (current_player=='X' ? "X" : "O");


    int temp_r=r-1,temp_c=c-1;
    bool flag=false;

    while(chk(temp_r,temp_c)){
        if(disk[temp_r][temp_c]==cur){
            while(temp_r!=r){
                if(disk[temp_r][temp_c]==op) flag=true;         //here instead of flipping we are changing a flag to keep track if any cell can be flipped
                temp_r++;
                temp_c++;
            }
            break;
        }
        else if(disk[temp_r][temp_c]!=op){
            break;
        }
        temp_r--;
        temp_c--;
    }

    temp_r=r+1;
    temp_c=c+1;
    while(chk(temp_r,temp_c)){
        if(disk[temp_r][temp_c]==cur){
            while(temp_r!=r){
                if(disk[temp_r][temp_c]==op) flag=true;
                temp_r--;
                temp_c--;
            }
            break;
        }
        else if(disk[temp_r][temp_c]!=op){
            break;
        }
        temp_r++;
        temp_c++;
    }


    temp_r=r+1;
    temp_c=c-1;
    while(chk(temp_r,temp_c)){
        if(disk[temp_r][temp_c]==cur){
            while(temp_r!=r){
                if(disk[temp_r][temp_c]==op) flag=true;
                temp_r--;
                temp_c++;
            }
            break;
        }
        else if(disk[temp_r][temp_c]!=op){
            break;
        }
        temp_r++;
        temp_c--;
    }


    temp_r=r-1;
    temp_c=c+1;
    while(chk(temp_r,temp_c)){
        if(disk[temp_r][temp_c]==cur){
            while(temp_r!=r){
                if(disk[temp_r][temp_c]==op) flag=true;
                temp_r++;
                temp_c--;
            }
            break;
        }
        else if(disk[temp_r][temp_c]!=op){
            break;
        }
        temp_r--;
        temp_c++;
    }



    temp_r=r;
    temp_c=c+1;
    while(chk(temp_r,temp_c)){
        if(disk[temp_r][temp_c]==cur){
            while(temp_c!=c){
                if(disk[temp_r][temp_c]==op) flag=true;
                temp_c--;
            }
            break;
        }
        else if(disk[temp_r][temp_c]!=op){
            break;
        }
        temp_c++;
    }


    temp_r=r-1;
    temp_c=c;
    while(chk(temp_r,temp_c)){
        if(disk[temp_r][temp_c]==cur){
            while(temp_r!=r){
                if(disk[temp_r][temp_c]==op) flag=true;
                temp_r++;
            }
            break;
        }
        else if(disk[temp_r][temp_c]!=op){
            break;
        }
        temp_r--;
    }


    temp_r=r+1;
    temp_c=c;
    while(chk(temp_r,temp_c)){
        if(disk[temp_r][temp_c]==cur){
            while(temp_r!=r){
                if(disk[temp_r][temp_c]==op) flag=true;
                temp_r--;
            }
            break;
        }
        else if(disk[temp_r][temp_c]!=op){
            break;
        }
        temp_r++;
    }

    temp_r=r;
    temp_c=c-1;
    while(chk(temp_r,temp_c)){
        if(disk[temp_r][temp_c]==cur){
            while(temp_c!=c){
                if(disk[temp_r][temp_c]==op) flag=true;
                temp_c++;
            }
            break;
        }
        else if(disk[temp_r][temp_c]!=op){
            break;
        }
        temp_c--;
    }
    return flag;

}






// Executes the Super Power 1
void super_1()
{
    string opposite_player, current_player_string;
    if (current_player == 'O')
    {
        current_player_string = "O";
        opposite_player = "X";
    }
    else if (current_player == 'X')
    {
        current_player_string = "X";
        opposite_player = "O";
    }


    int counter=0, max_opp=0, flag=0;
    for (int i=1; i<9; i++)
    {
        counter=0;
        for (int j = 1; j< 9; j++)
        {
            if(disk[i][j] == opposite_player)
            {
                counter++;
            }
        }
        if (counter>=max_opp){
            max_opp = counter;
            flag =i;
        }
    }
    for (int k=0; k<9; k++)
    {
        if (disk[flag][k]== opposite_player) disk[flag][k] = current_player_string;
    }
    if (current_player== 'X')
    {
        x_super1++;
    }
    else
    {
        o_super1++;
    }
}







// Executes Super Power 2
void super_2()
{
    string opposite_player, current_player_string;
    if (current_player == 'O')
    {
        current_player_string = "O";
        opposite_player = "X";
    }
    else if (current_player == 'X')
    {
        current_player_string = "X";
        opposite_player = "O";
    }

    int counter=0, max_opp=0, flag=0;
    for (int i=1; i<9; i++)
    {
        counter=0;
        for (int j = 1; j< 9; j++)
        {
            if(disk[j][i] == opposite_player)
            {
                counter++;
            }
        }
        if (counter>=max_opp){
            max_opp = counter;
            flag =i;
        }
    }
    for (int k=0; k<9; k++)
    {
        if (disk[k][flag]== opposite_player) disk[k][flag] = current_player_string;
    }
    if (current_player== 'X')
    {
        x_super2++;
    }
    else
    {
        o_super2++;
    }
}







// Executes Super Power 3
void super_3()
{
    string input_st;
    while(true){

        getline(cin,input_st);

        if(input_st.length()==3 && input_st[0]>='a' && input_st[0]<='h' && input_st[1]==' ' && input_st[2]>='1' && input_st[2]<='8'){

            int r,c;

            c=input_st[0]-'a'+1;
            r='9'-input_st[2];

            make_move(r,c);

            break;
        }
        else {
            cout<<"Invalid input! Please try again! "<<endl;
        }
        cout<<"=> ";
    }

    if (current_player== 'X')
    {
        x_super3++;
    }
    else
    {
        o_super3++;
    }
}






int main()
{
    start_banner();
    new_page();
    initialize();
    menu();


    return 0;
}
