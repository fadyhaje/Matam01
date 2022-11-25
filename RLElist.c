#include "RLEList.h"
#include <stdlib.h>
struct RLEList_t{
    struct RLEList_t *next;
    char data;
    int times;
};
RLEListResult RLEListAppend(RLEList list, char value){
    if(list==NULL)
    {
      return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList addedRLE=RLEListCreate();
    if(addedRLE==NULL)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }    
    addedRLE->data=value;
    addedRLE->times=1; 
    addedRLE-next=NULL;
    while(list->next) {
        list = list->next;
    }
    if(list->data==value)
    {
        list->times++;
        RLEListDestroy(addedRLE);
    }
    else if(list->times==0){
        list->data=addedRLE->data;
        list->times=addedRLE->times;
        list->next=NULL;
        RLEListDestroy(addedRLE); 
     }
    else{
        list->next=addedRLE;
    }
    return RLE_LIST_SUCCESS;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{  
    if(list==NULL|| map_function==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
RLEList temp=list->next;
list->data=map_function(list->data);
while(temp)
{
    temp->data=map_function(temp->data);
    if(list->data==temp->data){
        list->times+=temp->times;
        list->next=temp->next;
        temp->next=NULL;
        RLEListDestroy(temp);
        temp=list->next->next;
        list=list->next;
    }
    else {
        list = list->next;
        temp = temp->next;
    }
}
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list){
  int count=0;
    if(list==NULL)
    {
        return -1;
    }
    while(list)
    {
        count+=(list->times);
        list=list->next;

    }
return count;
}

char RLEListGet(RLEList list, int index, RLEListResult *result) {
    if (list==NULL){
        if(result!=NULL) {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }
    if(index<0){
        if(result!=NULL) {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0;
    }
    while(list){
        if(list->times>index){//check
            if(result!=NULL) {
                *result = RLE_LIST_SUCCESS;
            }
            return list->data;
        }
        index-=list->times;
        list=list->next;
    }
    if(result!=NULL) {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    return 0;
}
RLEList RLEListCreate()
{
    RLEList list=(RLEList) malloc(sizeof(struct RLEList_t));
    if(list==NULL) {
        return NULL;
    }
    list->next=NULL;
    list->data=(char) 0;
    list->times=0;
    return list;
}

void RLEListDestroy(RLEList list){
    while(list){
        RLEList toDelete=list;
        list=list->next;
        free(toDelete);
    }
}
RLEListResult RLEListRemove(RLEList list, int index)
{
    if(list==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    if(index<0){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    RLEList temp=list;
    while(list){
        if(list->times>index){
            if(list->times>1) {
                list->times--;
            }
            else {
                if (list != temp) {
                temp->next = list->next;
                free(list);
                list = temp->next->next;
                temp = temp->next;
                }
                else{
                    list=list->next;
                    free(temp);
                    temp=list;
                }
            }
                return RLE_LIST_SUCCESS;
        }
        index-=list->times;
        if(list!=temp) {
            list = list->next;
            temp=temp->next;
        }
        else{
            list=list->next;
        }

    }
    return RLE_LIST_INDEX_OUT_OF_BOUNDS;
}
