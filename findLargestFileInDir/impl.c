#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pthread.h>
#include <sched.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_FILE_PATH 1024
#define MAX_THREADS 30

void FindFileWithMaxSizeInDir(const char* dirname, char* result, unsigned int result_len);

struct thread_info {
    pthread_t thread_id;
    int	thread_num;
    char dirname[MAX_FILE_PATH];
    char* result;
    unsigned int result_len;
};

volatile unsigned int cur_threads = 0;
volatile unsigned int cur_thread_id = 0;
volatile unsigned int max_len = 0;
//struct thread_info g_tinfo[MAX_THREADS] = {'\0'};

pthread_mutex_t mutex_treads;
pthread_mutex_t mutex_result;

void* thread_entry(void* arg)
{
    struct thread_info *tinfo = arg;
    printf("Start thread %d %s\n", tinfo->thread_num, tinfo->dirname);

    pthread_detach(pthread_self());
    FindFileWithMaxSizeInDir(tinfo->dirname, tinfo->result, tinfo->result_len);

    free(tinfo);
    //pthread_mutex_lock(&mutex_treads);
    cur_threads--;
    //pthread_mutex_unlock(&mutex_treads);
}

void FindFileWithMaxSizeInDir(const char* dirname, char* result, unsigned int result_len){
    char* res = NULL;

    if (!dirname || !strlen(dirname))
        return;
    DIR *pDir = opendir(dirname);
    if (!pDir) {
          if (errno != EACCES)
            printf("open dir failed. %s\n", dirname);
          return;
    }
    struct dirent *dir = NULL;
    while ((dir = readdir(pDir))) {
        if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, ".."))
            continue;
        char filepath[MAX_FILE_PATH]= {'\0'};
        snprintf(filepath, sizeof(filepath), "%s/%s", dirname, dir->d_name);
        struct stat filestat;
        memset(&filestat, 0, sizeof(filestat));
        stat(filepath, &filestat);
        if(S_ISDIR(filestat.st_mode)) {
            printf("directory:%s\n", filepath);

            struct thread_info *tinfo = NULL;
            tinfo = (struct thread_info*)malloc(sizeof(struct thread_info));
            memset(tinfo, 0, sizeof(struct thread_info));
            memcpy(tinfo->dirname, filepath, strlen(filepath));
            tinfo->result = result;
            tinfo->result_len = result_len;

            // wait for free threads
            int i=0;
            while (1) {
                if (pthread_mutex_trylock(&mutex_treads) == 0) {
                    if (cur_threads >= MAX_THREADS) {
                        pthread_mutex_unlock(&mutex_treads);
                        FindFileWithMaxSizeInDir(tinfo->dirname, result, result_len);
                        free(tinfo);
                        break;
                    } else {
                        tinfo->thread_num = cur_thread_id;
                        cur_threads++;
                        cur_thread_id++;

                        printf("Starting thread %d %s...\n", tinfo->thread_num, tinfo->dirname);
                        pthread_create(&tinfo->thread_id, NULL, thread_entry, tinfo);
                        pthread_mutex_unlock(&mutex_treads);
                        break;
                    }
                }
                if (i%10000 == 0) {
                    printf("beyond the limit of maximan threads %d\n", cur_threads);
                }
                i++;
            }
        } else {
            printf("file:%s\n", filepath);

            pthread_mutex_lock(&mutex_result);
            if (max_len <= filestat.st_size) {
                memcpy(result, filepath, sizeof(filepath));
                max_len = filestat.st_size;
            }
            pthread_mutex_unlock(&mutex_result);
        }
    }
    closedir(pDir);
}
