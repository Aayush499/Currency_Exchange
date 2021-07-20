
#include<stdio.h>
#include<string.h>
#include "new2_2.c"

//#define MAX 6
/*
Instructions: 1. AddBank
              2. DeleteBank
              3. AddCurrencyInBank
              4. DeleteCurrencyInBank
              5. AddConversion
              6. DeleteConversion
              7. BestWay
              8. Exit
*/

int main()
{
   FILE* fp;
   int ins,n,name,curr,V,b=0,src,dest,weight;
   char buf,Name_bank[5],instruction[21];
   bank* arr_banks[MAX];
   int delete[MAX]={0};
   fp=fopen("file2.txt","r"); 

   while(!feof(fp) && ins!=9)
   {
      fscanf(fp,"%s",instruction);
      if(strcmp(instruction,"AddBank")==0) ins=1;
      if(strcmp(instruction,"DeleteBank")==0) ins=2;
      if(strcmp(instruction,"AddCurrencyInBank")==0) ins=3;
      if(strcmp(instruction,"DeleteCurrencyInBank")==0) ins=4;
      if(strcmp(instruction,"AddConversion")==0) ins=5;
      if(strcmp(instruction,"DeleteConversion")==0) ins=6;
      if(strcmp(instruction,"BestWay")==0) ins=7;
      if(strcmp(instruction,"printbankinfo")==0) ins=8;
      if(strcmp(instruction,"Exit")==0) ins=9;

       switch(ins){
            case(1):
                  fscanf(fp,"%c%s %d %d",&buf,Name_bank,&V,&n);
                  int* ver =(int*)malloc(V*sizeof(int));
                  for(int i=0;i<V;i++){
                      fscanf(fp,"%d",&ver[i]);
                  }
                  struct Edge* arr=(struct Edge*)malloc(n*sizeof(struct Edge));
                  for(int i=0;i<n;i++){
                  fscanf(fp,"%c%d %d %d",&buf,&arr[i].src,&arr[i].dest,&arr[i].weight);
                  }
                  if(num<MAX) {
                  delete[num]=1;
                  arr_banks[num]=createGraph(Name_bank,ver,V);
                  }
                  else printf("Banks can't be added\n");
                  for(int i= 0;i<n;i++)
                  {
        AddConversion(&arr_banks[num-1]->head[arr[i].src],arr[i].dest,arr[i].weight);
                   if (arr[i].src>V || arr[i].dest>V)
                    printf("%d TO %d NOT POSSIBLE IN %d BANK\n",arr[i].src,arr[i].dest,delete[num-1]);
                  }
                  free(arr);
                  free(ver);
                  //getchar();
                  break;
            case(2):
                  fscanf(fp,"%c%d",&buf,&name);
                  if(delete[name]==0)
                  {
                     printf("%d BANK IS NOT PRESENT\n",name);
                  } 
                  else DeleteBank(arr_banks[name]);
                  delete[name]= 0;
                  //getchar();
                  break;
            case(3):
                  fscanf(fp,"%c%d %d",&buf,&name,&curr); 
                  if(delete[name]==1 && arr_banks[name]->refer[curr]!=1)    
                  AddCurrency(curr,arr_banks[name]);
                  else if(delete[name]!=1 && arr_banks[name]->refer[curr]!=1) printf("%d IS NOT POSSIBLE TO ADD IN %d BANK \n",curr,name);
                  else if(delete[name]==1 && arr_banks[name]->refer[curr]==1) printf("%d IS ALREADY PRESENT IN %d BANK\n",curr,name);
                 // getchar();
                  break;
            case(4):
                  fscanf(fp,"%c%d %d",&buf,&name,&curr);
                  if(delete[name]==1 && arr_banks[name]->refer[curr]==1)
                  deleteCurrency(arr_banks[name],curr);
                  else printf("%d IS NOT BEEN ADDED %d BANK\n",curr,name);
                 // getchar();
                  break;
            case(5):
                  fscanf(fp,"%c%d %d %d %d",&buf,&name,&src,&dest,&weight);
                  if(delete[name]==1 && src!=dest && arr_banks[name]->refer[dest]==1 && arr_banks[name]->refer[src]==1)
                  AddConversion(&arr_banks[name]->head[src],dest,weight);
                  else
                  {
                    if (delete[name]==1)
                     printf("%d TO %d NOT POSSIBLE IN %d BANK\n",src,dest,name);
                     else
                     printf("%d TO %d NOT POSSIBLE in %d BANK\n",src,dest,name);
                  } 
                 // getchar();
                  break;
            case(6):                 
                  fscanf(fp,"%c%d %d %d",&buf,&name,&src,&dest);
                  if(delete[name]==1 && arr_banks[name]->refer[dest]==1 && arr_banks[name]->refer[src]==1)
                  deleteNode(&arr_banks[name]->head[src],dest);
                  else {
                    if (delete[name]==1)
                     printf("%d TO %d NOT POSSIBLE IN %d BANK \n",src,dest,name);
                     else
                     printf("%d TO %d NOT POSSIBLE in %d BANK\n",src,dest,name);
                  } //getchar();
                  break;
            case(7):
                  fscanf(fp,"%c%d %d",&buf,&src,&dest);
                  bestpath(arr_banks,src,dest,delete);
                  //getchar();
                  break;
            case(8):
                 fscanf(fp,"%c%d",&buf,&name);
                 if(delete[name]==1)
                 printGraph(arr_banks[name]);
                 else printf("%d BANK IS NOT PRESENT\n",name);
                 //getchar();                                       
        }
   }
   fclose(fp);
  
}
