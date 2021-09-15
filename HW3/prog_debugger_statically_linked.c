#include <stdio.h>
int main() {
    int n, i;
    unsigned long long fact = 1;
    printf("Enter an integer: ");
    scanf("%d", &n);

    // shows error if the user enters a negative integer
    printInt(n);

    return 0;
}

void printInt(int n){
    printf("this is a test for fist function %d" , n);
    printNumbers();
}

void printNumbers(){
    for(int i=0; i < 10; i++){
        printf(i);
    }
    printDone();
}

void printDone(){
    printf("THE PROGRAM IS DONE");
}
