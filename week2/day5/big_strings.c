#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void big(char *arr[],int size ,char** big11,char** big22)
{
    *big11 = strcmp(arr[0], arr[1]) > 0 ? arr[0] : arr[1];
    *big22 = strcmp(arr[0], arr[1]) <= 0 ? arr[0] : arr[1];

    for (int i = 2; i<5; i++) {
		if (strcmp(arr[i], *big11) > 0) {
			*big22 = *big11;
			*big11 = arr[i];
		} else if (strcmp(arr[i], *big22) > 0 ) {
			*big22 = arr[i];
		}
	}
}


int main(int argc, char *argv[])
{
    char* arr[5] = {"wangdao","fenghua","xianyu","loulou","longge"};
    char **big1, **big2;

    big(arr, 5, big1, big2);
    
    for (size_t i = 0; i < 5; i++) {
        printf("%s, ", arr[i]);
    }

    printf("最大的是%s, 第二大的是%s\n", *big1, *big2);
    return 0;
}