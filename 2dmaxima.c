#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef long long ll;

typedef struct Point {
    int x;
    int y;
} Point;

Point stack[10000000];
ll top = -1;

void push(Point x){
    if(top == 10000000 - 1){
        return;
    }
    else{
        stack[++top] = x;
    }
}
void pop(){
    if(top == -1){
        return;
    }
    else{
        top--;
    }
}

/// QUICK SORT
void swap(Point *p, Point *q)
{
    Point x = *p;
    *p = *q;
    *q = x;
}
ll partition(Point *arr, ll low, ll high)
{
    ll pivot = arr[high].x;
    ll i = (low - 1);

    for (ll j = low; j <= high - 1; j++)
    {

        if (arr[j].x < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(Point *arr, ll low, ll high)
{
    if (low < high)
    {
        ll pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void brute_force(int n, Point* P){
    int i, j, maximal;
    for(i = 0 ; i < n ; i++){
        maximal = 1;
        for(j = 0 ; j < n ; j++){
            if((i != j) && (P[i].x <= P[j].x) && (P[i].y <= P[j].y)){
                maximal = 0;
                break;
            }
        }
        if(maximal == 0){
            // printf("(%d, %d) \n", P[i].x, P[i].y);
        }
    }
}

void plane_sweep(int n, Point* P){
    quickSort(P, 0, n-1);
    top = -1;
    int i;
    for(i = 1 ; i < n ; i++){
        while(top > -1 && stack[top].y <= P[i].y){
            pop();
        }
        push(P[i]);
    }
    // printf("(%d, %d) \n", P[i].x, P[i].y);
}

int main()
{
    srand(time(0));

    ll n = 10;

    FILE *fp;

    fp = fopen("q1_plot_c.txt", "w");

    if(fp == NULL){
        printf("ERROR Opening File.\n");
    }

    double brute_force_time, efficient_time, mst, qst;

    while (n <= 1000000)
    {
        clock_t time;
        Point P[n];
        for (int k = 1; k <= 10; k++)
        {
            for (ll i = 0; i < n; i++)
            {
                Point Pxc;
                Pxc.x = rand();
                Pxc.y = rand();
                P[i] = Pxc;
            }
            time = clock();
            ///START
            brute_force(n, P);
            ///END
            time = clock() - time;
            mst += ((double)time) / CLOCKS_PER_SEC;
        }
        brute_force_time = mst / 10;

        for (int k = 1; k <= 10; k++)
        {
            for (ll i = 0; i < n; i++)
            {
                Point Pxc;
                Pxc.x = rand();
                Pxc.y = rand();
                P[i] = Pxc;
            }
            time = clock();
            ///START
            plane_sweep(n, P);
            ///END
            time = clock() - time;        
            qst += ((double)time) / CLOCKS_PER_SEC;
        }
        efficient_time = qst / 10;

        fprintf(fp, "%lld, %lf, %lf\n", n, brute_force_time, efficient_time);
        printf("%lld, %lf, %lf\n", n, brute_force_time, efficient_time);

        n *= 10;
    }

    fclose(fp);

    return 0;
}
