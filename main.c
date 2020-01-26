#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define CinemaHallCount 5;

int hourLocal;

struct node {
    int hourStart;
    int minuteStart;
    int hourEnd;
    int minuteEnd;
    char movieName[20];
    char movieDetail[60];
    int freeSpace;
    struct node *next;
};

struct node *createNode(int hourS ,int minuteS , int hourE , int minuteE , char name[] , char detail[], int space){
    struct node *nn;
    nn = (struct node *)malloc(sizeof(struct node));
    nn->hourStart = hourS;
    nn->minuteStart = minuteS;
    nn->hourEnd = hourE;
    nn->minuteEnd = minuteE;
    strcpy(nn->movieName , name);
    nn->freeSpace = space;
    strcpy(nn->movieDetail , detail);
    nn->next = NULL;
    return nn;
}

struct node *insert(struct node **head , struct node *createNode){
    if(*head == NULL)
    {
        *head = createNode;
        return;
    }

    struct node *curr;
    curr = *head;
    while(curr->next != NULL)
        curr = curr->next;
    curr->next = createNode;
}

void deleteNode(struct node **head , char movie[]){
    if(*head == NULL)
    {
        return;
    }

    if(strcmp((*head)->movieName, movie) == 0)
    {
        struct node *temp;
        temp = *head;
        (*head) = (*head)->next;
        free(temp);
        printf("'%s' has been removed\n" , movie);
        return;
    }

    int boolSearch = 0;
    struct node *search = *head;
    while(search->next != NULL){
        if(strcmp((*head)->movieName, movie) == 0){
             boolSearch = 1;
             break;
        }
        search = search->next;
    }
    if(boolSearch == 0)
    {
        printf("'%s' does not exist\n" , movie);
        return;
    }
    else
    {
        struct node *temp;
        temp = search->next;
        search->next = search->next->next;
        free(temp);
        printf("'%s' has been removed\n" , movie);
        return;
    }
}

void printList(struct node *current){
    int i = 1;
    while(current != NULL)
    {
        if(current->hourStart > hourLocal){
            printf("%d)\nStart : %d:%d\nEnd : %d:%d\nmovie name : %s\nmovie detail : %s\ntickets left : %d\n" ,i , current->hourStart , current->minuteStart , current->hourEnd , current->minuteEnd , current->movieName , current->movieDetail , current->freeSpace);
            current = current->next;
            i++;
        }
        else{
            current = current->next;
        }
    }
    return;
}

void sort(struct node **head)
{
    if((*head) == NULL || (*head)->next == NULL) return;
    struct node *curr =  *head;
    while(curr->next != NULL)
    {
        int holdH , holdM , holdS;
        char holdN[20] , holdD[60];
        if(curr->hourStart > curr->next->hourStart)
        {
            holdH = curr->hourStart;
            curr->hourStart = curr->next->hourStart;
            curr->next->hourStart = holdH;

            holdM = curr->minuteStart;
            curr->minuteStart = curr->next->minuteStart;
            curr->next->minuteStart = holdM;

            holdH = curr->hourEnd;
            curr->hourEnd = curr->next->hourEnd;
            curr->next->hourEnd = holdH;

            holdM = curr->minuteEnd;
            curr->minuteEnd = curr->next->minuteEnd;
            curr->next->minuteEnd = holdM;

            holdS = curr->freeSpace;
            curr->freeSpace = curr->next->freeSpace;
            curr->next->freeSpace = holdS;

            strcpy(holdN , curr->movieName);
            strcpy(curr->movieName , curr->next->movieName);
            strcpy(curr->next->movieName , holdN);

            strcpy(holdD , curr->movieDetail);
            strcpy(curr->movieDetail , curr->next->movieDetail);
            strcpy(curr->next->movieDetail , holdD);
        }
    curr = curr->next;
    }
}

int main(){
    struct node *head = NULL;
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    printf ( "Current local time and date: %s", asctime (timeinfo) );
    time_t now;
    struct tm *now_tm;

    now = time(NULL);
    now_tm = localtime(&now);
    hourLocal = now_tm->tm_hour;

    printf("hour : %d\n" , hourLocal);

    int movieCnt = 0;
    printf("main menu :\n");
    while(1)
    {
        printf("1) add a movie\n2) reserve a movie\n3) show list\n4) close page\n");
        int n;
        scanf("%d" , &n);
        if(n == 1)
        {
            int hourS , minuteS , tickets = 56 , hourE , minuteE;
            char movieName[20] , movieDetail[60];
            printf("please enter the movie name : ");
            scanf("%s" , movieName);
            printf("please enter the movie detail : ");
            scanf("%s" , movieDetail);
            printf("please enter the movie START time : ");
            scanf("%d:%d" , &hourS , &minuteS);
            printf("please enter the movie END time : ");
            scanf("%d:%d" , &hourE , &minuteE);
            insert(&head ,createNode(hourS , minuteS , hourE , minuteE , movieName , movieDetail , tickets));
            movieCnt++;
            sort(&head);
        }
        if(n == 2)
        {
            printf("choose a movie : \n");
            printf("%d\n" , movieCnt);
            printList(head);
            int x;
            scanf("%d" , &x);
            x;
            if(x < 0 || x > movieCnt)
            {
                printf("movie not found\n");
            }
            else{
                struct node *curr = head;
                if(x == 1){
                    curr->freeSpace--;
                    printf("reserve completed\n");
                }
                else{
                //x--;
                int i;
                for(i = 1 ; i < x ; i++)
                    curr = curr->next;
                    if(curr->freeSpace > 0){
                        curr->freeSpace--;
                        printf("reserve completed\n");
                    }
                    else{
                        printf("there is not enough space\n");
                    }
                }
            }
        }
        if(n == 3)
        {
            printList(head);
        }
        if(n == 4) return;
    }




    return 0;
}
