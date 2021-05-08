
#include<stdio.h>
#include<string.h>
#include "new2.c"

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


char curr_names[N][4];

int findpos(char arr[])
{
  for(int i=0;i<N;i++)
  {
    if(!strcmp(arr,curr_names[i]))
    {
      return i;
    }
  }
}

int main()
{
  FILE* fp2;
   fp2=fopen("names.txt","r"); 

   for(int i=0;i< N;i++)
   {
    fscanf(fp2,"%s",curr_names[i]);
   } 
  fclose(fp2);
   FILE* fp;
   int ins,n,name,curr,V,b=0,src,dest,weight;
   char buf,Name_bank[5],instruction[21];
   bank* arr_banks[MAX];
   int delete[MAX]={0};
   fp=fopen("file.txt","r"); 

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
        AddConversion(&arr_banks[num]->head[arr[i].src],arr[i].dest,arr[i].weight);
                  }
                  free(arr);
                  free(ver);
                  //getchar();
                  break;
            case(2):
                  fscanf(fp,"%c%d",&buf,&name);
                  if(delete[name]==0) printf("BANK IS ALREADY NOT PRESENT\n");
                  else DeleteBank(arr_banks[name]);
                  delete[name]= 0;
                  //getchar();
                  break;
            case(3):
                  fscanf(fp,"%c%d %d",&buf,&name,&curr); 
                  if(delete[name]==1 && arr_banks[name]->refer[curr]!=1)    
                  AddCurrency(curr,arr_banks[name]);
                  else if(delete[name]!=1 && arr_banks[name]->refer[curr]!=1) printf("NOT POSSIBLE BANK IS NOT ADDED\n");
                  else if(delete[name]==1 && arr_banks[name]->refer[curr]==1) printf("ALREADY PRESENT\n");
                 // getchar();
                  break;
            case(4):
                  fscanf(fp,"%c%d %d",&buf,&name,&curr);
                  if(delete[name]==1 && arr_banks[name]->refer[curr]==1)
                  deleteCurrency(arr_banks[name],curr);
                  else printf("NOT POSSIBLE\n");
                 // getchar();
                  break;
            case(5):
                  fscanf(fp,"%c%d %d %d %d",&buf,&name,&src,&dest,&weight);
                  if(delete[name]==1 && src!=dest && arr_banks[name]->refer[dest]==1 && arr_banks[name]->refer[src]==1)
                  AddConversion(&arr_banks[name]->head[src],dest,weight);
                  else printf("NOT POSSIBLE\n");
                 // getchar();
                  break;
            case(6):                 
                  fscanf(fp,"%c%d %d %d",&buf,&name,&src,&dest);
                  if(delete[name]==1 && arr_banks[name]->refer[dest]==1 && arr_banks[name]->refer[src]==1)
                  deleteNode(&arr_banks[name]->head[src],dest);
                  else printf("NOT POSSIBLE\n");
                  //getchar();
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
                 else printf("BANK IS NOT PRESENT\n");
                 //getchar();                                       
        }
   }
   fclose(fp);
  
}
