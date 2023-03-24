#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int x, y;
	char c1, c2;
} Pnt;

int main(){
	Pnt* my_pnt = malloc(sizeof(Pnt));
	my_pnt->x = 20;
	my_pnt->y = 69;
	my_pnt->c1 = 'A';
	my_pnt->c2 = 'b';

	// my_pnt.x = 20;
	// my_pnt.y = 69;
	// my_pnt.c1 = 'A';
	// my_pnt.c2 = 'b';

	printf("Pnt elements are %d, %d, %c, %c\n", my_pnt->x, my_pnt->y, my_pnt->c1, my_pnt->c2);
	return 0;
}
