#include<stdio.h>                                                                                                                                                                                                                                                                                                                                                                                                                                                                  bankers2.c                                                                                                                                                                                                                                                                                                                                                                                                                                                                             #include<stdio.h>
int n,m,i,j,z;
int available[20],allocation[20][20],need[20][20],max[20][20];
int request[20],work[20],safe[20],finish[20];
 void safety()
 {  z=0;
    int flag=1;
   int count=0;
   for(i=0;i<n;i++)
   {
    finish[i]=0;

   }
   for(j=0;j<m;j++)
   {
       work[j]=available[j];
   }
    while(count<n)
    {

        int found=0;
        for(i=0;i<n;i++)
        {
            if(finish[i]==0)
            {
                int canallocate=1;
                for(j=0;j<m;j++)
                {
                    if(need[i][j]>work[j])
                    {
                        canallocate=0;
                        break;
                    }
                }
                if(canallocate)
                {

                     for(j=0;j<m;j++)
                     {
                        work[j]+=allocation[i][j];
                     }
                     finish[i]=1;
                     safe[z++]=i;
                     found=1;
                }


            }
        }
        if(!found)
        {
            break;
        }
        count++;
    }
    for(i=0;i<n;i++)
    {
        if(finish[i]==0)
        {
            printf("deadlock detected");
            flag=0;
            break;
        }

    }
    if(flag)
    {   printf("safe");
        for(i=0;i<z;i++)
        {
            printf("P%d ",safe[i]);
        }
    }

 }

 void resource(int id)
 {
    for(i=0;i<m;i++)
    {
        if(request[i]>need[id][i])
        {
            printf("need is greater than request");
            return;
        }
        if(request[i]>available[i])
        {
            printf("request greater than available");
            return;
        }
    }
    for(i=0;i<m;i++)
    {
        allocation[id][i]+=request[i];
        need[id][i]-=request[i];
        available[i]-=request[i];


    }
    safety();
    int safe_state=1;
    for(i=0;i<n;i++)
    {
        if(finish[i]==0)
        {
            safe_state=0;
            break;
        }
    }
    if(!safe_state)
    {
        printf("not safe hence cannot allocate");
    }
 }
int main()
{
    char ch;
    printf("Enter the number of processes: ");
   scanf("%d", &n);
   printf("Enter the number of resources: ");
   scanf("%d", &m);
   for (int i = 0; i < m; i++)
   {
      printf("Enter available resources for resource %d: ", i);
      scanf("%d", &available[i]);
   }
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < m; j++)
      {
         printf("Enter the max demand of process %d for resource %d: ", i, j);
         scanf("%d", &max[i][j]);
      }for (int j = 0; j < m; j++){
         printf("Enter the current allocation of process %d for resource %d: ", i, j);
         scanf("%d", &allocation[i][j]);}
         for (int j = 0; j < m; j++){
         need[i][j] = max[i][j] - allocation[i][j];
      }
   }
   printf("Is there any request for any process? (y/n): ");
   scanf(" %c", &ch);
   if (ch == 'y')
   {
      int id;
      printf("Enter the PID of the requesting process: ");
      scanf("%d", &id);
      for (int i = 0; i < m; i++)
      {
         printf("Enter the request of Process %d for resource %d: ", id, i);
         scanf("%d", &request[i]);
      }
      resource(id);
   }
   else
   {
      safety();
   }
   return 0;

}







