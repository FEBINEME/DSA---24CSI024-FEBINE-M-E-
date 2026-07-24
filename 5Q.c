/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);

    int arr[n];
    int dq[n];
    int front = 0;
    int rear = -1;

    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    for(int i = 0; i < n; i++)
    {
        while(front <= rear && arr[dq[rear]] <= arr[i])
            rear--;

        dq[++rear] = i;

        if(dq[front] <= i - k)
            front++;

        if(i >= k - 1)
            printf("%d ", arr[dq[front]]);
    }

    return 0;
}