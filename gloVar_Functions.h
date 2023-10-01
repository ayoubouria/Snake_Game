
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>

#define WIDTH    1100
#define HEIGHT   800


void window_and_renderer(void);
void image_animation(void);
void diff_selection (void);
void gameover_menu(void);
void moves(void);
void draw_food(void);
void draw_snake(void);
void eat(void);
void fps(void);
void control(void);
void save_HighScores (void);



enum menu_pages
{
    page_1=1,page_2,page_3,page_4,page_5
};
enum Select
{
    Easy = 1,Medium,Hard,Highscore
};
enum movments
{
    Up = 1,Down,Right,Left
};
enum gameover
{
    Play_again = 1,Exit
};

/*-----------------------------------------------Set the variables to Global variable---------------------------------------------------------*/
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;

/*(icon) */
SDL_Surface* snake_title_surface = NULL;
SDL_Texture* snake_title_texture = NULL;

/* bg */
SDL_Surface* bg_surface = NULL;
SDL_Texture* bg_texture = NULL;

/* b */
SDL_Surface* ingame_bg_surface = NULL;
SDL_Texture* ingame_bg_texture = NULL;

/*  start menu */
SDL_Surface* menu_title_surface = NULL;
SDL_Texture* menu_title_texture = NULL;

/*  select difficulty */
SDL_Surface* diff_title_surface = NULL;
SDL_Texture* diff_title_texture = NULL;

/*  "Press Enter to start" */
SDL_Surface* press_title_surface = NULL;
SDL_Texture* press_title_texture = NULL;

/*  "easy" */
SDL_Surface* easy_surface = NULL;
SDL_Texture* easy_texture = NULL;

/*  "medium" */
SDL_Surface* medium_surface = NULL;
SDL_Texture* medium_texture = NULL;

/*  "hard" */
SDL_Surface* hard_surface = NULL;
SDL_Texture* hard_texture = NULL;

/* select ">" */
SDL_Surface* select_surface = NULL;
SDL_Texture* select_texture = NULL;

/*  gameover */
SDL_Surface* gameover_surface = NULL;
SDL_Texture* gameover_texture = NULL;

/*  play again */
SDL_Surface* playagain_surface = NULL;
SDL_Texture* playagain_texture = NULL;

/*  exit */
SDL_Surface* exit_surface = NULL;
SDL_Texture* exit_texture = NULL;

/*  pause เกม */
SDL_Surface* pausepic_surface = NULL;
SDL_Texture* pausepic_texture = NULL;

/*  score  game over */
SDL_Surface* youscore_surface = NULL;
SDL_Texture* youscore_texture = NULL;

/*  menu */
SDL_Surface* menu_surface = NULL;
SDL_Texture* menu_texture = NULL;

/* snake */
SDL_Surface* snake_surface = NULL;
SDL_Texture* snake_texture = NULL;

/* right */
SDL_Surface* ingame_right_surface = NULL;
SDL_Texture* ingame_right_texture = NULL;

/* right bot */
SDL_Surface* right_bot_surface = NULL;
SDL_Texture* right_bot_texture = NULL;

/* food */
SDL_Surface* food_surface = NULL;
SDL_Texture* food_texture = NULL;

/*score*/
SDL_Surface* ScoreImg_surface = NULL;
SDL_Texture* ScoreImg_texture = NULL;
/*High Scores*/
//Easy
SDL_Surface* HighE = NULL;
SDL_Texture* HighE_texture = NULL;
SDL_Rect HighE_rect = {250, 20, 200, 100};
//Medium
SDL_Surface* HighM = NULL;
SDL_Texture* HighM_texture = NULL;
SDL_Rect HighM_rect = {350, 260, 200, 100};
//Hard
SDL_Surface* HighH = NULL;
SDL_Texture* HighH_texture = NULL;
SDL_Rect HighH_rect = {250, 520, 200,100};
/* music */
Mix_Music *music = NULL;

/*  sound effect  */
Mix_Chunk *eat_sound = NULL;

/*  sound effect  */
Mix_Chunk *selection = NULL;

/*  sound effect  enter  */
Mix_Chunk *enter = NULL;

/*  sound effect  pause */
Mix_Chunk *beep = NULL;

/*  sound effect  */
Mix_Chunk* game_over_sound = NULL;



FILE *Highscore_Easy;
FILE *Highscore_Med;
FILE *Highscore_Hard;


int x[1000]; // arrays of the snake in the cord x
int y[1000]; // arrays of the snake in the cord y
int temp_x[1000], temp_y[1000]; // array reset the snake
int size = 3; // A variable to store the snake's size (length), starting at 3
int select_diff = 1; // The variable holds the difficulty level
int food_x = 0; // The position of the food in the cord x
int food_y = 0; // The position of the food in the cord y
int going = 3; // A variable to indicate the direction of the snake. (R L U D) right left top bottom
int food_status = 1; // variable to check if Has the food been stored? (0 & 1)
int keyboard_bug_fix = 1; // keyboard
int score = 0; // value storage variable score
char score_str[1000]; // score str
int menu_check = 1; // A variable to tell which menu page is now
int diff_y = 250; // variables to store the position of the image. ">" In the menu page, select the difficulty level Axis. y
int diff_x = 440; // variables to store the position of the image. ">" In the menu page, select the difficulty level Axis. x
float menu_x = -820; // variable to store cord x of the menu image
int menu_pos = 1; // variable to keep that now Menu image slides from right to left or left to right.
int pause = 0; // Set a pause variable to use when the user presses the pause button.
int running; //A variable to check if the program is running or not.


void window_and_renderer(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("error: failed to initialize SDL: %s\n", SDL_GetError());
        exit_game();
    }// init font
    if (TTF_Init() < 0)
    {
        printf("error: failed to initialize TTF %s\n", TTF_GetError());
        exit_game();
    }// init SDL
    window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN); // create program window
    if (!window)
    {
        printf("error: failed to open %d x %d window: %s\n", WIDTH, HEIGHT, SDL_GetError());
        exit_game();
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // create renderer
    if (!renderer)
    {
        printf("error: failed to create renderer: %s\n", SDL_GetError());
        exit_game();
    }
}
void image_animation(void)
{
    switch (menu_pos)
    {
        case 1 :
            menu_x += 0.2; // Image x-axis menu + 0.01
            break;
        case 2 :
            menu_x -= 0.2;  // The x-axis of the menu image - 0.01
            break;
    }
    if (menu_x >= 0){ //If the x-axis of the menu image is greater than 0, select it to the left.
        menu_pos = 2; // menu_pos = 2
    }
    if (menu_x <= -820){  // If the x-axis of the menu image is less than -820, select it to the right.
        menu_pos = 1; // menu_pos = 1
    }
}
void diff_selection (void)
{
    if (select_diff < Easy){ // If the selection pointer is less than 1, it becomes 3.
        select_diff = Highscore;
    }
    if (select_diff > Highscore){ //If the selection pointer is greater than 3, it becomes 1.
        select_diff = Easy;
    }
    switch (select_diff)
    {
        case Easy :
            diff_y = 250;
            diff_x = 440;
            break;
        case Medium :
            diff_y = 350;
            diff_x = 390;
            break;
        case Hard :
            diff_y = 450;
            diff_x = 440;
            break;
        case Highscore :
            diff_y = 550;
            diff_x = 440;
            break;
    }
}
void gameover_menu(void)
{
    if (select_diff > Exit){ // If the pointer is greater than 2, equals 1.
        select_diff = Play_again;
    }
    if (select_diff < Play_again){ // If the pointer is less than 1, equals 2.
        select_diff = Exit;
    }
    switch (select_diff)
    {
        case Play_again :
            diff_x = 360;
            diff_y = 305;
            break;
        case Exit :
            diff_x = 450;
            diff_y = 505;
            break;
    }
}
void exit_game(void)
{
    SDL_DestroyRenderer(renderer); // Destroy renderer
    SDL_DestroyWindow(window); // destroy the program window
    SDL_Quit(); // exit program

}
void moves(void)
{
    switch (going)
    {
        case Right :
            x[0] += 20;
            break;
        case Left :
            x[0] -= 20;
            break;
        case Up :
            y[0] -= 20;
            break;
        case Down :
            y[0] += 20;
            break;
    }
    /* Conditions when breaking through and then appearing on the other side */
    if (x[0] > 760){
        x[0] = 20;
    }
    if (x[0] < 20){
        x[0] = 760;
    }
    if (y[0] > 760){
        y[0] = 20;
    }
    if (y[0] < 20){
        y[0] = 760;
        }
}
void draw_food(void)
{
    while (food_status){ // Check if the snake has eaten or not.
        food_texture = SDL_CreateTextureFromSurface(renderer, food_surface); //set texture
        food_x = 20 * (rand() % 35); // random x-axis of food
        food_y = 20 * (rand() % 35); // random y-axis of food
        if (food_x == 0) food_x = 20; // If random gets 0, then 20.
        if (food_y == 0) food_y = 20; // If random gets 0, then 20.
        food_status = 0; //Set food_status to 0.

        /* Check if the coordinates of the food are the same as the snake or not. */
        for (int i = 0; i < size; i++){
            if (food_x == x[i] && food_y == y[i]){
                food_status++;
                break;
            }
        }
    }
    SDL_Rect food = {food_x, food_y, 20, 20}; // set the coordinates of the food
    SDL_RenderCopy(renderer, food_texture, NULL, &food); //render food
}
void draw_snake(void)
{
    for (int i = 0; i < size; i++){
        SDL_Rect snake = {x[i], y[i], 20, 20};
        SDL_RenderCopy(renderer, snake_texture, NULL, &snake);
    }
}
void eat(void)
{
    if (x[0] == food_x && y[0] == food_y){ // if food can be stored
//                x[size] = x[size - 1] - 20; // increase the size of the snake
        Mix_PlayChannel( -1, eat_sound, 0 ); // play sound effect eat
        size++; // size variable plus 1
        food_status++; //Set food_status = 1 to render the new food.
        score += 100;
        SDL_DestroyTexture(food_texture); //destroy texture of old food
    }
}
void fps(void)
{
        /* Set the delay time according to the selected difficulty level. */
    int delay_diff;
    switch (select_diff)
    {
        case Easy :
            delay_diff = 65;
            break;
        case Medium :
            delay_diff = 50;
            break;
        case Hard :
            delay_diff = 30;
            break;

    }
    SDL_Delay(delay_diff);
}
void control(void)
{
    switch (menu_check)
    {
        case page_1 :
            if (event.key.keysym.sym == SDLK_RETURN)// If on the first page menu and press ENTER
            {
                menu_check = page_2;// go to the next menu
                Mix_PlayChannel( -1, enter, 0 ); //play sound effect enter
            }
            break;
        case page_2 :
            switch (event.key.keysym.sym)
            {
                case SDLK_UP :// If on the second page menu and press the up arrow
                    select_diff--;
                    Mix_PlayChannel( -1, selection, 0 ); // Play sound effect selection
                    break;
                case SDLK_DOWN :// If on the second page menu and press the down arrow
                    select_diff++;
                    Mix_PlayChannel( -1, selection, 0 ); // Play sound effect selection
                    break;
                case SDLK_RETURN :// If on the second page menu and press ENTER
                    switch (select_diff)
                    {
                        case Highscore :
                            menu_check = page_5;//Go to the High Score Page
                            break;
                        default :
                            menu_check++;//Go to the next menu
                            Mix_PlayChannel( -1, enter, 0 ); //play sound effect enter

                    }
                    break;

            }
            break;
        case page_3 :
            switch (event.key.keysym.sym)
            {
                case SDLK_RIGHT :// If you press the right arrow and the snake's direction is not left and it's in the game screen and doesn't pause.
                    if(going != Left && keyboard_bug_fix  && !pause)
                    {
                        going = Right ;
                        keyboard_bug_fix = 0;
                    }
                    break;
                case SDLK_LEFT :// If you press the left arrow and the snake's direction is not right and it's in the game screen and doesn't pause.
                    if(going != Right && keyboard_bug_fix  && !pause)
                    {
                        going = Left;
                        keyboard_bug_fix = 0;
                    }
                    break;
                case SDLK_UP ://If you press the up arrow and the snake direction is not down and in front of the game and not paused.
                    if(going != Down && keyboard_bug_fix && !pause)
                    {
                        going = Up;
                        keyboard_bug_fix = 0;
                    }
                    break;
                case SDLK_DOWN ://If you press the down arrow and the snake's direction is not up and in front of the game and not paused.
                    if(going != Up && keyboard_bug_fix && !pause)
                    {
                        going = Down;
                        keyboard_bug_fix = 0;
                    }
                    break;
                case SDLK_p ://If on the game screen and press the letter p on the keyboard
                    if (pause == 1){ // Check if it is currently paused.
                        pause = 0; // set pause to 0
                        Mix_PlayChannel( -1, enter, 0 ); // play sound effect ENTER
                    }
                    else{ // If not paused
                        pause = 1; // set Pause to 1.
                        Mix_PlayChannel( -1, beep, 0 ); // play sound effect beep
                    }
                    break;
            }
            break;
        case page_4:
            switch (event.key.keysym.sym )
            {
                case SDLK_UP :// If on the fourth page of the menu and press the up arrow
                    select_diff--;
                    Mix_PlayChannel( -1, selection, 0 ); // Play sound effect selection
                    break;
                case SDLK_DOWN ://If on the fourth page of the menu and press the down arrow
                    select_diff++;
                    Mix_PlayChannel( -1, selection, 0 ); // Play sound effect selection
                    break;
                case SDLK_RETURN :
                    Mix_PlayChannel( -1, enter, 0 ); // play sound effect enter
                    if (select_diff == Play_again){ //If you select play again in the gameover menu page
                        score = 0; // reset score
                        memset(x, 0, sizeof(x)); // clear array of the snake in the cord x
                        memset(y, 0, sizeof(y)); // clear array of the snake in the cord y
                        memset(temp_x, 0, sizeof(temp_x)); // clear array of the snake suspension in the cord x
                        memset(temp_y, 0, sizeof(temp_y)); // clear array of the snake suspension in the cord y
                        size = 3; // The default size is back to the same as 3
                        for (int i = 0;i<3;i++)
                        {
                            x[i] = 400 - 20*i;
                            y[i] = 400;
                        }
                        going = Right; // direction to the right
                        food_status = 1; //Set the food_status variable to 1.
                        keyboard_bug_fix = 1; // keyboard key bug fix
                        menu_check = page_2; // Let the menu page start at the second page (the difficulty level selection page).
                    }
                    else {
                        running = 0;//exit the game
                    }
                    break;
            }
            break;
        case page_5 :
            if(event.key.keysym.sym == SDLK_RETURN)// If on the fifth page of the menu and press tenter
            {
                menu_check = page_2;//Return to Page 2
            }
            break;

    }
}
void save_HighScores (void)
{
    char txt[7],*s;// la chaine de character dans le fichier
    long int_s;//le variable pour convertir la chaine de charcter en int
    switch (select_diff)
    {
        case Easy :
            Highscore_Easy = fopen("files\\Highscore_Easy.txt","r");
            s = fgets(txt,sizeof(txt),Highscore_Easy);
            int_s = atoi(s);
            if (score>int_s)
            {
                if (fclose(Highscore_Easy)!=0)
                {
                    printf("Erreur de femeture du fichier ");
                }
                Highscore_Easy = fopen("files\\Highscore_Easy.txt","w");
                fprintf(Highscore_Easy,"%s",score_str);
                if (fclose(Highscore_Easy)!=0)
                {
                    printf("Erreur de femeture du fichier ");
                }
            }
            break;
        case Medium :
            Highscore_Med = fopen("files\\Highscore_Med.txt","r");
            s = fgets(txt,sizeof(txt),Highscore_Med);
            int_s = atoi(s);
            if (score>int_s)
            {
                if (fclose(Highscore_Med)!=0)
                {
                    printf("Erreur de femeture du fichier ");
                }
                Highscore_Med = fopen("files\\Highscore_Med.txt","w");
                fprintf(Highscore_Med,"%s",score_str);
                if (fclose(Highscore_Med)!=0)
                {
                    printf("Erreur de femeture du fichier ");
                }

            }
            break;
        case Hard :
            Highscore_Hard = fopen("files\\Highscore_Hard.txt","r");
            s = fgets(txt,sizeof(txt),Highscore_Hard);
            int_s = atoi(s);
            if (score>int_s)
            {
                if (fclose(Highscore_Hard)!=0)
                {
                    printf("Erreur de femeture du fichier ");
                }
                Highscore_Hard = fopen("files\\Highscore_Hard.txt","w");
                fprintf(Highscore_Hard,"%s",score_str);
                if (fclose(Highscore_Hard)!=0)
                {
                    printf("Erreur de femeture du fichier ");
                }

            }
            break;
    }
}



