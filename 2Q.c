/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);

    int arr[n], prefix[n];

    // Read the array
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    // First prefix value
    prefix[0] = arr[0];

    // Find prefix sum
    for(int i = 1; i < n; i++)
    {
        prefix[i] = prefix[i - 1] + arr[i];
    }

    // Print the prefix array
    for(int i = 0; i < n; i++)
    {
        printf("%d ", prefix[i]);
    }

    return 0;
}