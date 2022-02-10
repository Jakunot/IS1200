#include <stdio.h>
//#define list1 = 80;
//#define list2 = 80;
int count = 0;

char* text1 = "This is a string.";
char* text2 = "Yet another thing.";

int list1 [20];                         //Since an int = 4 bytes, 80/4 = 20
int list2 [20];



void printlist(const int* lst)
{
    printf("ASCII codes and corresponding characters.\n");
    while(*lst != 0){
        printf("0x%03X '%c' ", *lst, (char)*lst);
        lst++;
    }
    printf("\n");
}


void endian_proof(const char* c){
    printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n",
           (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));

}


void copyCodes(int* a, char* b, int* c)
{

    while(*b != 0)
    {
        *a = *b;                    //sw $t0,0($a1)
        a++;                        //addi $a0,$a0,1    ,text++
        b++;                        //addi $a1,$a1,4    ,list++
        *c = *c + 1;

    }
}


void work()
{
    copyCodes(list1, text1, &count);
    copyCodes(list2,text2, &count);


}


int main(void)
{
    work();

    printf("\nlist1: ");
    printlist(list1);
    printf("\nlist2: ");
    printlist(list2);
    printf("\nCount = %d\n", count);

    endian_proof((char*) &count);
}
