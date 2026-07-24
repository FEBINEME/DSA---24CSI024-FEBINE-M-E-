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

    int arr[n];

    // Read array
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    // Count total number of 1s
    int count = 0;
    for(int i = 0; i < n; i++)
    {
        if(arr[i] == 1)
            count++;
    }

    // If there are 0 or 1 ones, no swaps needed
    if(count <= 1)
    {
        printf("Min Swaps: 0");
        return 0;
    }

    // Count ones in the first window
    int ones = 0;
    for(int i = 0; i < count; i++)
    {
        if(arr[i] == 1)
            ones++;
    }

    int maxOnes = ones;

    // Slide the window
    for(int i = count; i < n; i++)
    {
        if(arr[i - count] == 1)
            ones--;

        if(arr[i] == 1)
            ones++;

        if(ones > maxOnes)
            maxOnes = ones;
    }

    printf("Min Swaps: %d", count - maxOnes);

    return 0;
}