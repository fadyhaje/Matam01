#include "AsciiArtTool.h"
#include "string.h"
static char reversed(char letter)
{
    if(' '==letter)
    {
        const char MapAt='@';
        return MapAt;
    }
    else if('@'==letter)
    {
        const char MapSpace=' ';
        return MapSpace;
    }
    return letter;
}

int main(int argc, char** argv)
{
    if(argc!=4)
    {
        printf("Missing arguments\n");
        return RLE_LIST_ERROR;
    }
    FILE *input,*output;
    input=fopen(argv[2],"r");
    if(input==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    output=fopen(argv[3],"w");
    if(output==NULL)
    {
        fclose(input);
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList list=asciiArtRead(input);
    if(list==NULL)
    {
        fclose(input);
        fclose(output);
        return RLE_LIST_OUT_OF_MEMORY;
    }
    RLEListResult result;
    if(strcmp(argv[1],"-i")!=0)
    {
        result= asciiArtPrintEncoded(list,output);
    }
    else
    {
        MapFunction mapFunction=reversed;
        result=RLEListMap(list,mapFunction);
        if(result==RLE_LIST_SUCCESS)
        {
            result=asciiArtPrint(list,output);
        }
    }
    RLEListDestroy(list);
    fclose(input);
    fclose(output);
    return result;
}
