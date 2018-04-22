#include "stealth.h"
#include "string.h"
#include "fstream"
#include "bitset"

using namespace std;

typedef struct header_file
{
    char chunk_id[4];
    int chunk_size;
    char format[4];
    char subchunk1_id[4];
    int subchunk1_size;
    short int audio_format;
    short int num_channels;
    int sample_rate;			// sample_rate denotes the sampling rate.
    int byte_rate;
    short int block_align;
    short int bits_per_sample;
    char subchunk2_id[4];
    int subchunk2_size;			// subchunk2_size denotes the number of samples.
} header;

typedef struct header_file* header_p;

Stealth::Stealth()
{
    inputfilename = "";
    outputfilename = "";
    Message = "";
}

void Stealth::Setinput(QString d)
{
    inputfilename = d;
}

void Stealth::Setmessage(QString m)
{
    Message = m;
}

void Stealth::Setoutput(QString o)
{
    outputfilename = o;
}

int Stealth::Encode()
{
    FILE * infile;
    FILE * outfile;
    const string strt = inputfilename.toStdString();
    const char * str1 = strt.c_str();
    infile = fopen(str1, "rb");
    const string str3 = outputfilename.toStdString();
    const char * str2 = str3.c_str();
    outfile = fopen(str2, "wb");
    int BUFSIZE = 16;
    unsigned long count = 0;
    bitset<8> message;
    bitset<16> buffer;
    short int buff16[BUFSIZE];
    int nb;
    string str = Message.toStdString();
    if (infile)
    {
        while (!feof(infile))
        {
            nb = fread(buff16,1,BUFSIZE,infile);
            /* Insert your processing code here*/
            if (count == 3)
            {
                message = str.length();

                buffer = buff16[1];
                for (int i = 0; i < 8; i++)
                {
                    buffer[i] = message[i];
                }
                buff16[1] = buffer.to_ulong();
            }
            if (count<str.length()+5 && count > 4)
            {
                message = str[count-5];
                buffer = buff16[1];
                for (int i = 0; i < 8; i++)
                {
                    buffer[i] = message[i];
                }
                buff16[1] = buffer.to_ulong();
                //char c = message.to_ullong();
            }
            fwrite(buff16,1,nb,outfile);			// Writing read data into output file
            count++;
        }
    }
        return 0;

}

QString Stealth::Decode()
{
FILE * infile;
int BUFSIZE = 16;
int count = 0;
int flag;
flag = 0;
char c;
string str1;
bitset<8> message;
bitset<16> buffer;
short int buff16[BUFSIZE];
int nb;
long len;
const string strt = inputfilename.toStdString();
const char * strf = strt.c_str();
infile = fopen(strf, "rb");
if (infile)
{
    while (!feof(infile))
    {
        nb = fread(buff16,1,BUFSIZE,infile);
        if (count == 3)
        {
            buffer = buff16[1];
            for (int i = 0; i < 8; i++)
            {
                message[i] = buffer[i];
            }
            len = message.to_ulong();
        }
        if (count < len+5 && count > 4)
        {
            buffer = buff16[1];
            for (int i = 0; i < 8; i++)
            {
                message[i] = buffer[i];
            }
            c = message.to_ullong();
            str1 += c;
        }
        count++;
    }
}
QString st = QString::fromStdString(str1);
return st;
}
