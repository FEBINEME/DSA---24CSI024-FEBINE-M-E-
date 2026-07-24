/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

int main()
{
    int n, p;
    scanf("%d %d", &n, &p);

    int arr[n];

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    int start = 0;
    int sum = 0;
    int max = 0;

    for(int end = 0; end < n; end++)
    {
        sum = sum + arr[end];

        while(sum > p)
        {
            sum = sum - arr[start];
            start++;
        }

        if(end - start + 1 > max)
        {
            max = end - start + 1;
        }
    }

    printf("Max Length: %d", max);

    return 0;
}