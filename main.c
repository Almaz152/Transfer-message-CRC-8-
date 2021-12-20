/*
  Name  : ����� ������������ ��������� ������� CRC-8
  Poly  : 0x31    x^8 + x^5 + x^4 + 1
  Init  : 0xFF
  Revert: false
  XorOut: 0x00
  Check : 0xF7 ("123456789")
  MaxLen: 15 ����(127 ���) - �����������
    ���������, �������, ������� � ���� �������� ������
*/




#include <stdio.h>
#include <locale.h>
#include <unistd.h>

/*---------------------��������� �������-------------------------------------------------------------------------------*/
int to_binary(unsigned long n);                                             // ������� ���� ������� � �������� ���
unsigned char calculate_crc8(unsigned char *data_ptr, unsigned char len);   // ����������� CRC-8
unsigned char preamble_crc(unsigned char preamble[]);                       // ����������� ���������
/*---------------------��������� �������-------------------------------------------------------------------------------*/

const short int LENGTH = 15;

int main()
{
    setlocale(LC_ALL, "Russian");

    char ch;
    unsigned char preamble[] = {0x01, 0x02, 0x03, 0x04};

    preamble_crc(preamble);
    printf("\n������� ����� �������\n\n");

    while(scanf("%c",&ch)!=sleep(1)) //sleep 1 ������� - ����.����� ������ ���������
    {
        if(ch!='\n'&&ch!=' ')
        {
            printf("\t������: %c\t\tASCII:\t%d",ch, ch);
            printf("\n\t�������� ���:\t\t");
            to_binary(ch);
            printf("\n\n");
            printf("\t����������� CRC-8\n");
            printf("\t������: %c\n", calculate_crc8(&ch, LENGTH));
            printf("\t�������� ���:\t\t");
            to_binary(calculate_crc8(&ch, LENGTH));
            printf("\n\n\n");
        }


    }

    return 0;
}

/*--------------������� �������� �� ���������� ������� � ��������------*/

int to_binary(unsigned long n)
{
    int r;
    r=n%2;
    if(n>=2)
        to_binary(n/2);
    putchar(r==0? '0':'1');
    return r;
}

/*--------------������� ����������� ������ ������� CRC-8----------------------------------------------------------*/

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
        crc ^= 0x31;    // ������� ��� 0x31 ���������, � ����������� �������� XOR ������ � �������� 8 ������ 0x31.
      }
      else
      {
        crc <<= 1;
      //����� ������� ��� ����� 0, ������� XOR ����� crc � 0 ��-�������� ����� crc, ������� ��� ��������� "crc ^ = 0x31;".
      }
    }
  }
  return crc;
}

/*--------------������� ����������� ��������� ������� CRC-8----------------------------------------------------------*/

unsigned char preamble_crc(unsigned char preamble[])
{


     printf(" ��������� 4 �����: %x %x %x %x\n\n", preamble[0], preamble[1], preamble[2], preamble[3], preamble[4]);
     printf(" ����������� CRC-8\n");

     for(int i=0; i<4;i++)
     {
       printf("\t������: %c\n", calculate_crc8(preamble+i, LENGTH));
       printf("\t�������� ���: ");
       to_binary(calculate_crc8(preamble+i, LENGTH));
       printf("\n\n");
     }

     return *preamble;
}






