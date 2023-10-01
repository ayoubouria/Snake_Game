#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <ctype.h>
#include "gloVar_Functions.h"

int main(int argc, char* args[])
{
    window_and_renderer();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048); // Mix_openaudio
    running = 1; // Set the running variable to 1.
    /* load snake image (icon) */
    snake_title_surface = SDL_LoadBMP("image/snake_icon.bmp");
    snake_title_texture = SDL_CreateTextureFromSurface(renderer, snake_title_surface);
    SDL_Rect snake_title = {400, 250, 324, 324};
    /* load frame */
    bg_surface = SDL_LoadBMP("image/bg.bmp");
    bg_texture = SDL_CreateTextureFromSurface(renderer, bg_surface);
    SDL_Rect bg = {0, 0, 1200, 800};
    /* Load the background image in the game. */
    ingame_bg_surface = SDL_LoadBMP("image/ingame_bg.bmp");
    ingame_bg_texture = SDL_CreateTextureFromSurface(renderer, ingame_bg_surface);
    SDL_Rect ingame_bg = {20, 20, 760, 760};
    /* Load the title image in the start menu. */
    menu_title_surface = SDL_LoadBMP("image/menu_title.bmp");
    menu_title_texture = SDL_CreateTextureFromSurface(renderer, menu_title_surface);
    SDL_Rect menu_title = {300, 60, 520, 138};
    /* Load the title image in the difficulty level menu. */
    diff_title_surface = SDL_LoadBMP("image/select_diff.bmp");
    diff_title_texture = SDL_CreateTextureFromSurface(renderer, diff_title_surface);
    SDL_Rect diff_title = {225, 60, 664, 151};
    /* Load the image "Press ENTER to start" in the start menu. */
    press_title_surface = SDL_LoadBMP("image/press_title.bmp");
    press_title_texture = SDL_CreateTextureFromSurface(renderer, press_title_surface);
    SDL_Rect press_title = {320, 660, 443, 53};
    /* Load the image "Easy". */
    easy_surface = SDL_LoadBMP("image/easy.bmp");
    easy_texture = SDL_CreateTextureFromSurface(renderer, easy_surface);
    SDL_Rect easy = {480, 250, 143, 76};
    /* Load the image "Medium". */
    medium_surface = SDL_LoadBMP("image/medium.bmp");
    medium_texture = SDL_CreateTextureFromSurface(renderer, medium_surface);
    SDL_Rect medium = {430, 350, 269, 66};
    /* load image "Hard" */
    hard_surface = SDL_LoadBMP("image/hard.bmp");
    hard_texture = SDL_CreateTextureFromSurface(renderer, hard_surface);
    SDL_Rect hard = {480, 450, 162, 66};
    /* load image ">" */
    select_surface = SDL_LoadBMP("image/select.bmp");
    select_texture = SDL_CreateTextureFromSurface(renderer, select_surface);
    SDL_Rect select = {440, 250, 43, 57};
    /* load image "Game over!!" */
    gameover_surface = SDL_LoadBMP("image/gameover.bmp");
    gameover_texture = SDL_CreateTextureFromSurface(renderer, gameover_surface);
    SDL_Rect gameover = {310, 60, 521, 82};
    /* load image "play again" */
    playagain_surface = SDL_LoadBMP("image/playagain.bmp");
    playagain_texture = SDL_CreateTextureFromSurface(renderer, playagain_surface);
    SDL_Rect playagain = {400, 300, 339, 80};
    /* load image "exit" */
    exit_surface = SDL_LoadBMP("image/exit.bmp");
    exit_texture = SDL_CreateTextureFromSurface(renderer, exit_surface);
    SDL_Rect exit = {490, 500, 134, 66};
    /* Load images to come up on time pause */
    pausepic_surface = SDL_LoadBMP("image/pause.bmp");
    pausepic_texture = SDL_CreateTextureFromSurface(renderer, pausepic_surface);
    SDL_Rect pausepic = {260, 320, 290, 127};
    /* load your score */
    youscore_surface = SDL_LoadBMP("image/youscore.bmp");
    youscore_texture = SDL_CreateTextureFromSurface(renderer, youscore_surface);
    SDL_Rect youscore = {300, 700, 480, 70};
     /* load menu image */
    menu_surface = SDL_LoadBMP("image/menu.bmp");
    menu_texture = SDL_CreateTextureFromSurface(renderer, menu_surface);
    /* load the snake */
    snake_surface = SDL_LoadBMP("image/snake.bmp");
    snake_texture = SDL_CreateTextureFromSurface(renderer, snake_surface);
    /* Load the game image on the right. */
    ingame_right_surface = SDL_LoadBMP("image/right_img.bmp");
    ingame_right_texture = SDL_CreateTextureFromSurface(renderer, ingame_right_surface);
    SDL_Rect ingame_right = {800, 20, 280, 620};
    /* Load the game image on the bottom right. */
    right_bot_surface = SDL_LoadBMP("image/right_bot.bmp");
    right_bot_texture = SDL_CreateTextureFromSurface(renderer, right_bot_surface);
    SDL_Rect right_bot = {800, 660, 280, 120};
    /*Load score image*/
    ScoreImg_surface = SDL_LoadBMP("image/score.bmp");
    ScoreImg_texture = SDL_CreateTextureFromSurface(renderer, ScoreImg_surface);
    SDL_Rect ScoreImg = {490, 530, 128, 90};
    /* load food */
    food_surface = SDL_LoadBMP("image/plus.bmp");
            /* load music */
    music = Mix_LoadMUS("audio/bg_music.mp3");
    /* load sound effect ตอนงูกินอาหาร */
    eat_sound = Mix_LoadWAV("audio/eat.wav");
    /* load sound effect ตอนเลื่อน */
    selection = Mix_LoadWAV("audio/selection.wav");
    /* load sound effect ตอนกด enter */
    enter = Mix_LoadWAV("audio/enter.wav");
    /* load sound effect ตอนกด pause */
    beep = Mix_LoadWAV("audio/beep.ogg");
    /* load sound effect game over */
    game_over_sound = Mix_LoadWAV("audio/gameover.wav");
    /* load fonts */
    TTF_Font* sans = TTF_OpenFont("verdana.ttf", 100);
    /* set color variable*/
    SDL_Color black = {0, 0, 0};
//     Define a Score ------
    SDL_Surface* score_die = NULL;
    SDL_Texture* score_die_texture = NULL;
    SDL_Rect score_die_rect = {530, 675, 250, 90};
    /* set the picture of the window window */
    SDL_SetWindowIcon(window, snake_title_surface);
    /* Play a song (never ending)*/
    Mix_PlayMusic(music, -1);
    for (int i = 0;i<3;i++)//Snake's coordinates
    {
        x[i] = 400 - 20*i;
        y[i] = 400;
    }
    char txte_E[7],*st_E,txte_M[7],*st_M,txte_H[7],*st_H;//Variables For High Scores Files

    while (running){ // run program
        while (SDL_PollEvent(&event)) { // check event
            if (event.type == SDL_QUIT) { // If you click to close the window
                running = 0; // Let running be 0
            }

            else if (event.type == SDL_KEYDOWN){// if user presses keyboard
                control();
            }
        }
        if (menu_check == page_1){ // If on the first menu page
            SDL_RenderClear(renderer); // clear the renderer
            SDL_Rect menu = {menu_x, 0, 1920, 800}; // Set the coordinates of the menu image.
            image_animation();//animation d'image
            SDL_RenderCopy(renderer, menu_texture, NULL, &menu); // render menu image
            SDL_RenderCopy(renderer, press_title_texture, NULL, &press_title); // To render the image Press ENTER to Start
            SDL_RenderCopy(renderer, menu_title_texture, NULL, &menu_title); // render the Snake Game image.
            SDL_RenderPresent(renderer); // Present out of the screen
        }
        else if (menu_check == page_2){ // If on the second menu page
            SDL_RenderClear(renderer); // clear the renderer
            SDL_Rect menu = {menu_x, 0, 1920, 800}; // Set the coordinates of the menu image.
            image_animation();
            SDL_RenderCopy(renderer, menu_texture, NULL, &menu); //render menu image
            SDL_RenderCopy(renderer, diff_title_texture, NULL, &diff_title); // render the image Select difficulty
            SDL_RenderCopy(renderer, easy_texture, NULL, &easy);  //  render Easy.
            SDL_RenderCopy(renderer, medium_texture, NULL, &medium);  //render the image Medium
            SDL_RenderCopy(renderer, hard_texture, NULL, &hard); //render the image Hard
            SDL_RenderCopy(renderer,ScoreImg_texture,NULL,&ScoreImg);
            diff_selection();
            SDL_Rect select = {diff_x, diff_y, 43, 57}; // Set the coordinates of the image ">".
            SDL_RenderCopy(renderer, select_texture, NULL, &select); // render the image ">"
            SDL_RenderPresent(renderer); // Present out of the screen
        }
        else if (menu_check == page_3){ // If it's on the third menu (in the game)
            if (pause){ // Check if the pause variable is true (the user presses the pause button or not).
                SDL_RenderCopy(renderer, pausepic_texture, NULL, &pausepic); // to display a pause message
                SDL_RenderPresent(renderer); // Present the original image on the screen.
                continue; // continue
            }
            sprintf(score_str, "%7d", score);//Converts an int score to a 6-character string and stores it in the score_str variable.
            SDL_Surface* surfacemessage = TTF_RenderText_Solid(sans, score_str, black); // Set the font and text and color.
            SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfacemessage); // Set the texture of the message.
            SDL_Rect message_rect = {810, 665, 260, 100};
            SDL_RenderClear(renderer); // clear the renderer
            SDL_RenderCopy(renderer, bg_texture, NULL, &bg); // Make a render of the frame
            SDL_RenderCopy(renderer, ingame_bg_texture, NULL, &ingame_bg); // Make a rendering of the background image.
            SDL_RenderCopy(renderer, ingame_right_texture, NULL, &ingame_right);  //render the image on the right
            SDL_RenderCopy(renderer, right_bot_texture, NULL, &right_bot);  // Make a render of the image on the bottom right.
            draw_food();
            draw_snake();
            moves();
            eat();
            //position
            for (int i = 1; i < size; i++){
                if (x[0] == x[i] && y[0] == y[i]){ // If the snake hits itself
                    Mix_PlayChannel( -1, game_over_sound, 0 ); // play sound effect gameover
                    SDL_Delay(500);
                    menu_check = page_4; //let menu page = 4
                    save_HighScores();
                    score_die = TTF_RenderText_Solid(sans, score_str, black); // Set the text font and color.
                    score_die_texture = SDL_CreateTextureFromSurface(renderer, score_die); // Create a texture score that will be displayed on the 4th menu page.
                    select_diff = 1; //Reset pointer to 1
                    break; //stop this loop
                }
                x[i] = temp_x[i-1]; // Put the reserved snake value into the x-axis array.
                y[i] = temp_y[i-1];// Put the reserved snake value into the y-axis array.
            }

            /* Stores the current snake value in a hold variable.*/
            for (int i = 0; i < size; i++){
                temp_x[i] = x[i];
                temp_y[i] = y[i];
            }
            fps();
            SDL_RenderCopy(renderer, message, NULL, &message_rect); // render score
            SDL_RenderPresent(renderer); // Present out of the screen
            keyboard_bug_fix = 1; // keyboard bug fix variable
        }
        else if (menu_check == page_4){ // If the menu page is 4
            SDL_RenderClear(renderer); // clear thr renderer
            SDL_Rect menu = {menu_x, 0, 1920, 800}; //Set the coordinates of the menu image.
            image_animation();
            gameover_menu();
            SDL_RenderCopy(renderer, menu_texture, NULL, &menu); //render menu image
            SDL_RenderCopy(renderer, gameover_texture, NULL, &gameover); // ทําการ render ภาพ Game over
            SDL_RenderCopy(renderer, playagain_texture, NULL, &playagain); //render the image Play again
            SDL_RenderCopy(renderer, exit_texture, NULL, &exit); // render the image Exit
            SDL_RenderCopy(renderer, youscore_texture, NULL, &youscore); // To render the image Score:
            SDL_RenderCopy(renderer, score_die_texture, NULL, &score_die_rect); // show the score obtained
            SDL_Rect select = {diff_x, diff_y, 43, 57}; //Set the coordinates of the image ">".
            SDL_RenderCopy(renderer, select_texture, NULL, &select); // render the image ">"
            SDL_RenderPresent(renderer); // Present out on the screen
        }
        else if (menu_check == page_5){
            SDL_RenderClear(renderer); // clear the renderer
            SDL_Rect menu = {menu_x, 0, 1920, 800}; // Set the coordinates of the menu image.
            SDL_Rect easy = {50, 20, 143, 76};
            SDL_Rect medium = {50, 260, 269, 66};
            SDL_Rect hard = {50, 520, 162, 66};
            image_animation();
            /*High Scores*/
            Highscore_Easy = fopen("files\\Highscore_Easy.txt","r");//reading Highscore_Easy
            st_E = fgets(txte_E,sizeof(txte_E),Highscore_Easy);
            HighE = TTF_RenderText_Solid(sans, st_E, black); // Set the text font and color.
            HighE_texture = SDL_CreateTextureFromSurface(renderer, HighE); // Create a texture High score that will be displayed on the highscores menu page.
            if (fclose(Highscore_Easy)!=0)
            {
                printf("Erreur de femeture du fichier ");
            }
            Highscore_Med = fopen("files\\Highscore_Med.txt","r");//reading Highscore_Med
            st_M = fgets(txte_M,sizeof(txte_M),Highscore_Med);
            HighM = TTF_RenderText_Solid(sans, st_M, black); // Set the text font and color.
            HighM_texture = SDL_CreateTextureFromSurface(renderer, HighM); // Create a texture High score that will be displayed on the highscores menu page.
            if (fclose(Highscore_Med)!=0)
            {
                printf("Erreur de femeture du fichier ");
            }
            Highscore_Hard = fopen("files\\Highscore_Hard.txt","r");//reading Highscore_Hard
            st_H = fgets(txte_H,sizeof(txte_H),Highscore_Hard);
            HighH = TTF_RenderText_Solid(sans, st_H, black); // Set the text font and color.
            HighH_texture = SDL_CreateTextureFromSurface(renderer, HighH); // Create a texture High score that will be displayed on the highscores menu page.
            if (fclose(Highscore_Hard)!=0)
            {
                printf("Erreur de femeture du fichier ");
            }
            /*Display*/
            SDL_RenderCopy(renderer, menu_texture, NULL, &menu); // render menu image
            SDL_RenderCopy(renderer, easy_texture, NULL, &easy);  //  render Easy.
            SDL_RenderCopy(renderer, medium_texture, NULL, &medium);  //render the image Medium
            SDL_RenderCopy(renderer, hard_texture, NULL, &hard);  //render the image Hard
            SDL_RenderCopy(renderer, HighE_texture, NULL, &HighE_rect); // show the high score obtained
            SDL_RenderCopy(renderer, HighM_texture, NULL, &HighM_rect); // show the high score obtained
            SDL_RenderCopy(renderer, HighH_texture, NULL, &HighH_rect); // show the high score obtained
//            SDL_Delay(5000);
            SDL_RenderPresent(renderer); // Present out of the screen
        }
    }
//    char*name;
//    printf("Enter your name ");
//    scanf("%s",&name);
//    printf("%s :%d",&name,score);
    exit_game();
}
