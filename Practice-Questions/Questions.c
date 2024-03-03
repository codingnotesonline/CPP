#include <stdio.h>

// Question_1
double average(int arr[], int size){
    int i;
    int count = 0;
    double sum = 0;
    for(i = 0;i<size;i++){
        if(arr[i] % 3 == 0){
            sum += arr[i];
            count++;
        }
    }
    return (sum/count);
}

// Question_2
int isPrime(int n){
    int i;
    int is_prime = 1;

  // 0 and 1 are not prime numbers
  if (n == 0 || n == 1) {
    is_prime = 0;
  }

  // loop to check if n is prime
  for (i = 2; i <= n/2; ++i) {
    if (n % i == 0) {
      is_prime = 0;
      break;
    }
  }

  return is_prime;
}

void checkPassword(char arr[]){
    if(arr == ""){

    }

    int count = 0;
    char ch;

    do{
        ch = arr[count];
        count++;
    }while(ch != '\0');

    count--;

    printf("%d\n", count);
}

void main(){
// Question_1
    int arr[] = {2,4,6,7,41,25,36,27,15,18};
    int size = 10;
    printf("%0.2lf\n", average(arr, size));

// Question_2
    printf("is prime: %d\n", isPrime(1));

// Question_3
    checkPassword("qwerty");
}