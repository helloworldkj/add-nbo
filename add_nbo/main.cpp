#include <stddef.h> // for size_t
#include <stdint.h> // for uint8_t
#include <stdio.h> // for printf


int check_endian(){ //cpu endian check
int test = 0x123456;

    //printf("%x %x\n",(char*)&test,*(char*)&test);
    //printf("%x %x\n", (char*)&test+1, *((char*)&test+1));
    //printf("%x %x\n", (char*)&test+2, *((char*)&test+2));
    if(*((char*)&test+2) == 0x12){
        return 1;//little endian
    }
    else{
        //big endian
    }
}

//이렇게 할 필요없이 기본 제공하는 함수쓰면 빅엔디안에서는 동작하지 않는다. 
//그러면 아래의 my_hton없이 효율적인 코드 가능

uint32_t my_hton(uint32_t n){  //HBO(little endian) to NBO(big endian)
    uint32_t n1= (n & 0xFF000000)>>24;
    uint32_t n2= (n & 0x00FF0000)>>8;
    uint32_t n3= (n & 0x0000FF00)<<8;
    uint32_t n4= (n & 0x000000FF)<<24;

    return n1|n2|n3|n4;
}



int main(int argc, char *argv[]) {

FILE * open1;
open1 = fopen(argv[1], "rb"); //rb : read binary
FILE * open2;
open2=  fopen(argv[2], "rb");

uint32_t num1=0;
uint32_t num2=0;

fread(&num1, 4, 1, open1); // read 4byte binary
fread(&num2, 4, 1, open2);

    //fread의 아이템을 고려해야한다!
    
    //지금 이렇게 코드 중복되는 부분 다 정리할 것
   

if(check_endian()==1){ //check endian and sum
    uint32_t result1 = my_hton(num1);
    uint32_t result2 = my_hton(num2);
    printf("%d(0x%x) + %d(0x%x) = %d(0x%x) \n",result1,result1, result2,result2, result1+result2, result1+result2);
}
else{
    printf("%x+ %x = %x \n",num1, num2, num1+num2);
}

  return 0;
}
