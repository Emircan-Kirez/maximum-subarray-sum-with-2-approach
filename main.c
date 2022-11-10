/* Emircan Kirez - Ch3rry */
/* Last Update: 10/11/2022 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct box{
    int maxValue;
    int leftIndex;
    int rightIndex;
}BOX;


//Function Prototypes
int *createArray(int *size);
BOX bruteForce(int *A, int size);
BOX maxWithMid(int *A, int size, int l, int r);
BOX divideAndConquer(int *A, int size, int l, int r);
BOX max(BOX a, BOX b);

int main(){
    int size;
    int *A = createArray(&size);
    
    BOX box = bruteForce(A, size);
    printf("------ BRUTE FORCE ------\nMax sum: %d\nRange: %d - %d\n\n", box.maxValue, box.leftIndex, box.rightIndex);
    box = divideAndConquer(A, size, 0, size  - 1);
    printf("------ DIVIDE and CONQUER ------\nMax sum: %d\nRange: %d - %d\n", box.maxValue, box.leftIndex, box.rightIndex);
    return 0;
}

int *createArray(int *size){
	printf("Enter the size: ");
    scanf("%d", size);

    int *A = (int *)malloc(sizeof(int) * (*size));
    
    int i;
    for(i = 0; i < *size; i++){
    	printf("Write the %d. number: ", i+1);
        scanf("%d", &A[i]);
    }
    
    return A;
}
BOX bruteForce(int *A, int size){
    int i, j, sum;
    BOX box;
    box.maxValue = INT_MIN;
    for(i = 0; i < size; i++){
        sum = 0;
        for(j = i; j < size; j++){
            sum += A[j];
            if(box.maxValue < sum){
                box.maxValue = sum;
                box.leftIndex = i;
                box.rightIndex = j;
            }
        }
    }
    return box;
}

BOX divideAndConquer(int *A, int size, int l, int r){
    if(l > r){
        BOX box;
        box.maxValue = INT_MIN;
        return box;
    }

    if(l == r){ // base condition
        BOX box;
        box.maxValue = A[l];
        box.rightIndex = box.leftIndex = l;
        return box;
    }

    int m = (l + r) / 2;
    BOX maxLeft = divideAndConquer(A, size, l, m - 1); // max that will come from left side
    BOX maxRight = divideAndConquer(A, size, m + 1, r); // max that will come from right side
    BOX maxMid = maxWithMid(A, size, l, r); // max that will come with mid 
    return max(max(maxLeft, maxRight), maxMid); // return the largest of the three maxs
}

BOX maxWithMid(int *A, int size, int l, int r){
    int i, maxLeft = INT_MIN, maxRight = INT_MIN, sum;
    int mid = (l + r) / 2;
    BOX box;

    // max value from left side with mid
    sum = 0;
    for(i = mid; i >= l; i--){
        sum += A[i];
        if(maxLeft < sum){
            maxLeft = sum;
            box.leftIndex = i;
        }
    }

    // max value from right side with mid
    sum = 0;
    for(i = mid; i <= r; i++){
        sum += A[i];
        if(maxRight < sum){
            maxRight = sum;
            box.rightIndex = i;
        }
    }

    box.maxValue = (maxLeft + maxRight - A[mid]); // since we add the mid value twice, we should subtract it one to get the right value
    return box;
}

BOX max(BOX a, BOX b){
    return a.maxValue > b.maxValue ? a : b;
}
