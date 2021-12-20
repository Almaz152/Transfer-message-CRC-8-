/*
  Name  : Прием кодированных сообщений методом CRC-8
  Poly  : 0x31    x^8 + x^5 + x^4 + 1
  Init  : 0xFF
  Revert: false
  XorOut: 0x00
  Check : 0xF7 ("123456789")
  MaxLen: 15 байт(127 бит) - обнаружение
    одинарных, двойных, тройных и всех нечетных ошибок
*/




#include <stdio.h>
#include <locale.h>
#include <unistd.h>

/*---------------------Прототипы функций-------------------------------------------------------------------------------*/
int to_binary(unsigned long n);                                             // Перевод кода символа в двоичный код
unsigned char calculate_crc8(unsigned char *data_ptr, unsigned char len);   // Кодирование CRC-8
unsigned char preamble_crc(unsigned char preamble[]);                       // Кодирование преамбулы
/*---------------------Прототипы функций-------------------------------------------------------------------------------*/

const short int LENGTH = 15;

int main()
{
    setlocale(LC_ALL, "Russian");

    char ch;
    unsigned char preamble[] = {0x01, 0x02, 0x03, 0x04};

    preamble_crc(preamble);
    printf("\nВведите любые символы\n\n");

    while(scanf("%c",&ch)!=sleep(1)) //sleep 1 секунда - макс.время приема приемника
    {
        if(ch!='\n'&&ch!=' ')
        {
            printf("\tСимвол: %c\t\tASCII:\t%d",ch, ch);
            printf("\n\tДвоичный код:\t\t");
            to_binary(ch);
            printf("\n\n");
            printf("\tКодирование CRC-8\n");
            printf("\tСимвол: %c\n", calculate_crc8(&ch, LENGTH));
            printf("\tДвоичный код:\t\t");
            to_binary(calculate_crc8(&ch, LENGTH));
            printf("\n\n\n");
        }


    }

    return 0;
}

/*--------------Перевод значения из десятичной системы в двоичную------*/

int to_binary(unsigned long n)
{
    int r;
    r=n%2;
    if(n>=2)
        to_binary(n/2);
    putchar(r==0? '0':'1');
    return r;
}

/*--------------Функция кодирования данных методом CRC-8----------------------------------------------------------*/

unsigned char calculate_crc8(unsigned char *data_ptr, unsigned char len)
{
  unsigned int i;
  unsigned char j;
  unsigned char crc = 0xFF;
  for (i=0; i<len; i++)
  {
    crc ^= *data_ptr;
    data_ptr++;
    for (j=8; j>0; j--)
    {
      if (crc & 0x80)
      {
        crc <<= 1;
        crc ^= 0x31;    // Старший бит 0x31 удаляется, и выполняется операция XOR только с младшими 8 битами 0x31.
      }
      else
      {
        crc <<= 1;
      //Когда старший бит равен 0, битовое XOR между crc и 0 по-прежнему равно crc, поэтому нет оператора "crc ^ = 0x31;".
      }
    }
  }
  return crc;
}

/*--------------Функция кодирования преамбулы методом CRC-8----------------------------------------------------------*/

unsigned char preamble_crc(unsigned char preamble[])
{


     printf(" Преамбула 4 байта: %x %x %x %x\n\n", preamble[0], preamble[1], preamble[2], preamble[3], preamble[4]);
     printf(" Кодирование CRC-8\n");

     for(int i=0; i<4;i++)
     {
       printf("\tСимвол: %c\n", calculate_crc8(preamble+i, LENGTH));
       printf("\tДвоичный код: ");
       to_binary(calculate_crc8(preamble+i, LENGTH));
       printf("\n\n");
     }

     return *preamble;
}






