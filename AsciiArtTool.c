#include "RLEList.h"
#include <stdio.h>
RLEList asciiArtRead(FILE* in_stream)
{
    FILE* stream =fopen("in_stream","r");
    if(stream==NULL)
        return NULL;
    char c;
   RLEList list= RLEListCreate();
   Set_Data(list, fgetc(stream));
   Set_times(list,1);

    while((c= fgetc(stream))!=EOF)
    {

        RLEListAppend(list,c);

    }
    fclose(stream);
    return list;
}
