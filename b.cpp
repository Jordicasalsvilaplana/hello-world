#include <iostream>
#include <string.h>
#include <time.h>

#define MAXF 5
#define MAXC 10
#define MAXMINAS 2

class Hola
{
private:
    int tableroMinas[MAXF][MAXC];
public:
   int** gettableroMinas();
   void settableroMinas();
};
int** gettableroMinas(){

    return tableroMinas;
}

void settableroMinas(int** arr){
    
}

int main(){

    Hola arr;
    arr=gettableroMinas();
    settableroMinas(arr);

    return 0;
}
