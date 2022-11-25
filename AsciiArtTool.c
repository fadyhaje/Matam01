#include "AsciiArtTool.h"
#include <stdio.h>
#include "stdlib.h"

RLEList asciiArtRead(FILE* in_stream)
{
    //if(stream==NULL)
       // return NULL;
    char c;
   RLEList list= RLEListCreate();
    if(list==NULL){
        return NULL;
    }
   //Set_Data(list, fgetc(stream));
   //Set_times(list,1);
    while(!feof(in_stream))
    {
        c=fgetc(stream);
        RLEListAppend(list,c);
    }
    return list;
}

RLEListResult asciiArtPrint(RLEList list, FILE* out_stream)
{
    if(out_stream==NULL || list==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    char data;
    int i;
    RLEListResult result;
    int list_size=RLEListSize(list);
    while(i<list_size){
    {
        data=RLEListGet(list,i,&result);
        if(resul!=RLE_LIST_SUCCESS)
        {
            return result;
        }
        else
        {
            fprintf(out_stream,"%c",data);
        }
        i++;
    }
    return RLE_LIST_SUCCESS;
}

 RLEListResult asciiArtPrintEncoded(RLEList list, FILE* out_stream)
{
    if(out_stream==NULL || list==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult result;
    char* list_string=RLEListExportToString(list, &result);
    if(list_string==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    fprintf(out_stream, "%s", list_string);
    free(list_string);
    return result;
}
