#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define SCREEN_X_SIZE 10
#define SCREEN_Y_SIZE 10
enum direction
{
    STOP,
    UP,
    RIGHT,
    DOWN,
    LEFT
};

int rand_int(int a, int b)
{
    return a + rand() % (b - a + 1);
}

void print_frame(int head_pos_x, int head_pos_y, int x_size, int y_size, int field[][x_size])
{
    int i, j;
    for (i = 0; i < x_size * 3 + 2; i++)
    {
        printf("=");
    }
    printf("\n");
    for (i = 0; i < y_size; i++)
    {
        printf("|");
        for (j = 0; j < x_size; j++)
        {
            if (head_pos_x == j && head_pos_y == i)
                printf(" \x1B[1;32m@\e[0m ");
            else if (field[i][j] > 0)
                printf(" \x1B[1;32mo\e[0m ");
            else if (!field[i][j])
                printf(" . ");
            else if (field[i][j] == -1)
                printf(" \x1B[1;31mA\e[0m ");
        }
        printf("|");
        printf("\n");
    }
    for (i = 0; i < x_size * 3 + 2; i++)
    {
        printf("=");
    }
    printf("\n");
}

void spawn_apple(int x_size, int y_size, int field[][x_size])
{
    int x, y;
    while (1)
    {
        x = rand_int(0, x_size - 1);
        y = rand_int(0, y_size - 1);
        if (!field[y][x])
        {
            field[y][x] = -1;
            return;
        }
    }
}

int change_frame(int direction, int *head_pos_x, int *head_pos_y, int x_size, int y_size, int field[][x_size], int *score)
{
    int i, j;
    int new_x = *head_pos_x;
    int new_y = *head_pos_y;

    switch (direction)
    {
    case UP:
        new_y = (abs((*head_pos_y) - 1 + y_size)) % y_size;
        break;
    case RIGHT:
        new_x = ((*head_pos_x) + 1) % x_size;
        break;
    case DOWN:
        new_y = ((*head_pos_y) + 1) % y_size;
        break;
    case LEFT:
        new_x = (abs((*head_pos_x) - 1 + x_size)) % x_size;
        break;
    case STOP:
        return 1;
    default:
        break;
    }
    if (field[new_y][new_x] == -1)
    {
        (*score)++;
        field[*head_pos_y][*head_pos_x] = (*score);
        spawn_apple(x_size, y_size, field);
    }
    else if (field[new_y][new_x] > 1)
    {
        return 0;
    }
    else
    {
        for (i = 0; i < y_size; i++)
        {
            for (j = 0; j < x_size; j++)
            {
                if (field[i][j] > 0)
                {
                    field[i][j]--;
                }
            }
        }
    }
    field[new_y][new_x] = field[*head_pos_y][*head_pos_x] + 1;
    *head_pos_x = new_x;
    *head_pos_y = new_y;
    return 1;
}

int game()
{
	clock_t start_time;

    int scr_x = SCREEN_X_SIZE;
    int scr_y = SCREEN_Y_SIZE;

    int head_position_x = scr_x/2;
    int head_postion_y = scr_y/2;

    int field[SCREEN_Y_SIZE][SCREEN_X_SIZE] = {0};

    field[head_postion_y][head_position_x] = 1;
    int i = 0;
    int length = 1;
    int direction = STOP;
    char input;
    int score = 0;
    spawn_apple(scr_x, scr_y, field);
    while (1)
    {
		start_time=clock();
		
        // printf("%d",key_direction(input));
        system("cls");
		printf("\tSCORE: %d\n", score);
        print_frame(head_position_x, head_postion_y, scr_x, scr_y, field);

		while(((double)(clock()-start_time))/CLOCKS_PER_SEC<0.15){
		
	        if (kbhit())
	        {
	            input = _getch();
	            
        	}
        	
		}
			if (input == 'h' && direction != RIGHT && direction != LEFT)
	                direction = LEFT;
	            if (input == 'u' && direction != DOWN && direction != UP)
	                direction = UP;
	            if (input == 'j' && direction != UP && direction != DOWN)
	                direction = DOWN;
	            if (input == 'k' && direction != LEFT && direction != RIGHT)
	                direction = RIGHT;
        if (!change_frame(direction, &head_position_x, &head_postion_y, scr_x, scr_y, field, &score))
            return score;
        //Sleep(150);
    }
}

int main()
{
    int score;
    int key;
    clock_t start_time;
    while (1)
    {
        system("cls");

        printf("\x1b[1;30;47m\tSNAKE\x1b[0m\n\n");
        printf("\tMenu\n"
               "\t1.Start game\n"
               "\t2.Control\n"
               "\t0.Exit\n"
               "\t>> ");
        scanf("%d", &key);
        fflush(stdin);

        switch (key)
        {
        case 1:
            score = game();
            system("cls");

            printf("\x1b[1;30;47m\tGAME OVER\x1b[0m\n\n");
            printf("\n\tYOUR SCORE: %d\n", score);
            //Sleep(2000);
            start_time=clock();
            while(((double)(clock()-start_time))/CLOCKS_PER_SEC<2){		}
            _getch();
            break;
        case 2:
            system("cls");
           printf("\x1b[1;30;47m\tCONTROL\x1b[0m\n\n"
                   "\t  UP - [u]\n"
                   "    LEFT - [h] [j] [k] - RIGHT \n"
                   "\t\t|\n"
                   "\t       DOWN  \n"
                   "\tback - any key\n"
                   "\t>> ");
            _getch();
            break;
        case 0:
            return 0;
        default:
            printf("Unknown command\n");
            break;
        }
    }
    return 0;
}
