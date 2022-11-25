#include "RLEList.h"
#include <stdlib.h>
#include <stdio.h>

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
    addedRLE->next=NULL;
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
/*RLEListResult RLEListRemove(RLEList list, int index)
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
}*/


static void check(RLEList list)
{
    if(list->next!=NULL && list->data==list->next->data)
    {
        RLEList unwantedIndex=list->next;
        list->times+=unwantedIndex->times;
        RLEList toDelete = unwantedIndex;
        list->next = unwantedIndex->next;
        free(toDelete);
    }
}

static RLEListResult Remove_next_node(RLEList list)
{
    RLEList unwantedIndex=list->next;
    if(unwantedIndex==NULL)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    if(unwantedIndex->times!=1)
    {
        unwantedIndex->times--;
    }
    else
    {
        list->next=unwantedIndex->next;
        unwantedIndex->next=NULL;
        RLEListDestroy(unwantedIndex);
        check(list);
        return RLE_LIST_SUCCESS;
    }
    return RLE_LIST_SUCCESS;
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    if(list==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(index<0)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    if(list->times>index)
    {
        if(list->times!=1)
        {
            list->times--;
        }
        else
        {
            if(list->next==NULL)
            {
                list->times=0;
            }
            else
            {
                RLEList to_delete=list->next;
                list->data=to_delete->data;
                list->times=to_delete->times;
                list->next=to_delete->next;
                free(to_delete);
            }
        }
        return RLE_LIST_SUCCESS;
    }
    index-=list->times;
    while(list->next!=NULL)
    {
        if(list->next->times >index)
        {
            return Remove_next_node(list);
        }
        index-=list->next->times;
        list=list->next;
    }
    return RLE_LIST_INDEX_OUT_OF_BOUNDS;
}

int numOfNodes(RLEList list){
    int count=0;
    while(list){
        count++;
        list=list->next;
    }
    return count;
}

int DigitsSingleNode(int num){
    int count=0;
    while (num>0){
        count++;
        num=num/10;
    }
    return count;
}

int DigitsList(RLEList list){
    int sum=0;
    int length= numOfNodes(list);
    for (int i=0;i<length;i++){
        int temp_num=list->times;
        if(temp_num < 10)
        {
            sum++;
        }
        else
        {
            sum+=DigitsSingleNode(list->times);
        }
        list=list->next;
    }
    return sum;
}

int rev_Func(int num){
    int reverse_num=0;
    while(num!=0)
    {
        reverse_num = reverse_num * 10 + num%10;
        num = num/10;
    }
    return reverse_num;
}


char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if(list==NULL)
    {
        if(result!=NULL)
        {
            *result= RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    int count=DigitsList(list),count_num=numOfNodes(list);
    char* string_list= malloc(sizeof(char)*(RLEListSize(list)*2+count+1));
    if(string_list==NULL)
    {
        if(result!=NULL)
        {
            *result=RLE_LIST_OUT_OF_MEMORY;
        }
        return NULL;
    }
    RLEList temp_list=list;
    int index=0,temp_num;
    while(temp_list)
    {
        count_num=0;
        string_list[index++]=temp_list->data;
        temp_num=temp_list->times;
        count_num+=DigitsSingleNode(temp_num);
        int reverse_num=rev_Func(temp_num);
        for(int i=0;i<count_num;i++)
        {
            string_list[index++]=reverse_num%10+'0';
            reverse_num/=10;
        }
        string_list[index++]=10;
        //new line
        temp_list = temp_list->next;
    }
    string_list[index]=(char)0;
    if(result!=NULL)
    {
        *result= RLE_LIST_SUCCESS;
    }
    return string_list;
}
