#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include <sys/wait.h>
#include<errno.h>
#include<stdlib.h>
#include <fcntl.h>
#include<sys/stat.h>


#define MAX 50
#define READ_END 0
#define WRITE_END 1 
#define MIN 0

char PATH[50][50] = {"/usr/local/sbin","/usr/local/bin","/usr/sbin","/usr/bin","/sbin","/bin","/usr/games","/usr/local/games","/snap/bin","/snap/bin"};
int path_num = 10;

char history[50][50];
int commands_count = 0;


char* remove_red_spaces(char* str)
{
    char* res = malloc(sizeof(char)*100);
    int n = strlen(str);

    int i = 0;
    int k = 0;

    while(str[i] == ' ')
    {
        i++;

    }
    while(str[i] != ' ')
    {
        res[k++] = str[i++];
    }

    // int count = 0;
    int j;
    for(j = i; j < n; j++)
    {
        res[k++] = ' ';
        while(str[j] == ' ')
        {
            j++;
        }
        while(str[j] != ' ')
        {
            res[k++] = str[j++];
        }
    

    }

    return res;
    
    
}

char** string_to_word_del(char* str,char del)
{
    // char newString[10][10]; 
    int i,j,ctr;

    char** newString = malloc(sizeof(char*)*50);
    for(i=0;i<10;i++)
    {
        newString[i] = malloc(sizeof(char)*50);
    }


    j=0; ctr=0;
    for(i=5;i<=(strlen(str));i++)
    {
        // if space or NULL found, assign NULL into newString[ctr]
        if(str[i]==del||str[i]=='\0')
        {
            newString[ctr][j]='\0';
            ctr++;  //for next word
            j=0;    //for next word, init index to 0
        }
        else
        {
            newString[ctr][j]=str[i];
            j++;
        }
    }
    newString[ctr] = NULL;

    // for(i=0;i < ctr;i++)
    //     printf(" %s\n",newString[i]);

    return newString;

}


char** string_to_word(char* str)
{
    // char newString[10][10]; 
    int i,j,ctr;

    char** newString = malloc(sizeof(char*)*10);
    for(i=0;i<10;i++)
    {
        newString[i] = malloc(sizeof(char)*10);
    }


    j=0; ctr=0;
    for(i=0;i<=(strlen(str));i++)
    {
        // if space or NULL found, assign NULL into newString[ctr]
        if(str[i]==' '||str[i]=='\0')
        {
            newString[ctr][j]='\0';
            ctr++;  //for next word
            j=0;    //for next word, init index to 0
        }
        else
        {
            newString[ctr][j]=str[i];
            j++;
        }
    }
    newString[ctr] = NULL;

    // for(i=0;i < ctr;i++)
    //     printf(" %s\n",newString[i]);

    return newString;

}

int main()
{
    int pid;

    char prompt[100];
    getcwd(prompt,sizeof(prompt));
    strcat(prompt,"$ ");
    
    
    strcpy(PATH[path_num++],prompt);





    char* buf = malloc(sizeof(char)*MAX);
    int flag = 0;
    while(1)
    {
        char current_wd[100];
        getcwd(current_wd,sizeof(current_wd));
        
        printf("%s",prompt);
        if(fgets(buf,MAX,stdin) == NULL)
        {
            printf("Bye\n");
            exit(1);
        }
        else
        {
            char* res = malloc(sizeof(char)*50);
            res = remove_red_spaces(buf);
            strcpy(buf,res);
            free(res);
            
            if(strcmp(buf,"exit\n") == 0)
            {
                printf("Bye");
                exit(1);
                // return 0;
            }
            char* token = strtok(buf, "\n");
            if(token == NULL)
            {
                fprintf(stderr, "Only Delimiters");
            }

            
            // FILE* fptr;
            // fptr = fopen("/home/jayraj/os/Assignments/shell1/history.txt", "a+");
            // if(fptr == NULL)
            // {
            //     // printf("Entered here");
            //     return -1;
            // }
            // fprintf(fptr, "%s\n",token);
            // // printf("Checkpoint 1\n");
            // // if(fclose(fptr) == EOF)
            // // {
            // //     printf("Error closing file");

            // // }

  
            // // printf("Command enetered is %s",token);
            strcpy(history[commands_count++], token);


            
            if(token[0] == 'P' && token[1] == 'S')
            {
                if(token[5] != '\\' && token[6] != 'w' && token[7] != '$')
                {
                    flag = 1;
                    int k = 0;
                    for(int i = 5; i < strlen(token)-1; i++)
                    {
                        prompt[k++] = token[i];
            

                    }
                    prompt[k] = '\0';
                }
                else
                {
                    strcpy(prompt,current_wd);
                    strcat(prompt,"$ ");
                    

                }
                
                
                
        
            
            }
            else if(strcmp(token, "history") == 0)
            {
                // FILE* fp = fopen("/home/jayraj/os/Assignments/history.txt", "r");
                // char str[100];
                // int i = 0;
                // while(fgets(str,100, fp) != NULL)
                // {
                //     printf("%d %s\n",i,str);
                //     i++;
                // }
                // fclose(fp);
                int k = 0;
                for(k=commands_count-1;k>=0;k--)
                {
                    printf("%d %s\n",k+1, history[k]);
                }

            }
            else if(strcmp(token,"echo $PATH") == 0)
            {
                for(int i = 0; i < path_num; i++)
                {
                    printf("%s:",PATH[i]);
                }
                printf("\n");

        
            }
            else if(token[0] == 'P' && token[1] == 'A' && token[2] == 'T')
            {
                // printf("Came inside");
                char** newString = string_to_word_del(token,':');
                // for(int i=0;i<10;i++)
                // {
                //     newString[i] = malloc(sizeof(char)*50);

                // }
                



                int i = 0;
                path_num = 0;
                while(newString[i] != NULL)
                {
                    
                    strcpy(PATH[path_num++], newString[i]);
                    i++;
                }
                // continue;
                // for(int i = 0; i < path_num; i++)
                // {
                //     printf("%s\n",PATH[i]);
                // }
                getcwd(current_wd,sizeof(current_wd));
                strcpy(PATH[path_num++],current_wd);


                


            }
            else if(token[0] == 'c' && token[1] == 'd')
            {
                char** newString = malloc(sizeof(char*)*10);
                for(int i=0;i<10;i++)
                {
                    newString[i] = malloc(sizeof(char)*10);
                }

                newString = string_to_word(token);

                chdir(newString[1]);

                getcwd(prompt,sizeof(prompt));
                strcpy(PATH[path_num++],prompt);

                strcat(prompt,"$ ");


            }
            else
            {
                char** newString = malloc(sizeof(char*)*10);
                for(int i=0;i<10;i++)
                {
                    newString[i] = malloc(sizeof(char)*10);
                }

                newString = string_to_word(token);
                // printf("Checkpoint 2\n");


                
                char** temp = string_to_word(token);
                char** redirect = malloc(sizeof(char*)*20);
                int fd;
                int k = 0;
                int redirect_flag = 0;
                int rediect_flag1 = 0;
                // int pipe_flag = 0;
                while(temp[k])
                {
                    if(strcmp(temp[k], ">") == 0)
                    {
                        // printf("Strcmp is 0");
                        redirect_flag = 1;
                        break;

                    }
                    if(strcmp(temp[k], "<") == 0)
                    {
                        rediect_flag1 = 1;
                        break;

                    }
                    k++;
                }

                pid = fork();
                // printf("Fork is being called");

                char full_path[100];

                if(pid == 0)
                {
                    if(redirect_flag)
                    {
                        // printf("\nOp redirection detected");
                        close(1);
                        fd = open(temp[++k],O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
                        if(fd == -1)
                        {
                            perror("Open failed: ");
                        }
                        k--;
                        int i;
                        for(i=0;i<k;i++)
                        {
                            redirect[i] = temp[i];
                        }
                        redirect[i] = NULL;

                        strcpy(full_path,"/bin/");
                        strcat(full_path,redirect[0]);
                        
                        int ret = execv(full_path,redirect);
                        if(ret == -1)
                        {
                            perror("Execution failed: ");
                            exit(errno);

                        }
                        close(1);
                        // char* file = stdout;
                        // open();
                        

                    }
                    else if(rediect_flag1)
                    {
                        close(0);
                        fd = open(temp[++k],O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
                        if(fd == -1)
                        {
                            perror("Open failed: ");
                        }
                        k--;
                        int i;
                        for(i=0;i<k;i++)
                        {
                            redirect[i] = temp[i];
                        }
                        redirect[i] = NULL;

                        strcpy(full_path,"/bin/");
                        strcat(full_path,redirect[0]);
                    
                        
                        int ret = execv(full_path,redirect);
                        if(ret == -1)
                        {
                            // printf("Entered here");
                            perror("Execution failed: ");
                            exit(errno);

                        }


                    }
                    else
                    {
                        for(int i = 0; i < path_num; i++)
                        {

                            strcpy(full_path,PATH[i]);
                            strcat(full_path,"/");
                            strcat(full_path,newString[0]);
                            // printf("Checkpoint 3\n");

                            int ret = execv(full_path,newString);
                            if(ret == -1 && i == path_num-1)
                            {
                                perror("Execution failed: ");
                                exit(errno);

                            }
                        }

                    }
                    
                

                }
                else
                {
                    wait(0);
                }

            }



        }

    }


    return 0;
}
