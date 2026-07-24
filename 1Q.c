/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);

    int arr[n], result[n];

    // Read the array
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    int left = 0;
    int right = n - 1;
    int index = n - 1;

    while(left <= right)
    {
        if(abs(arr[left]) > abs(arr[right]))
        {
            result[index] = arr[left] * arr[left];
            left++;
        }
        else
        {
            result[index] = arr[right] * arr[right];
            right--;
        }

        index--;
    }

    // Print the result
    for(int i = 0; i < n; i++)
    {
        printf("%d ", result[i]);
    }

    return 0;
}