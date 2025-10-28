#include<stdio.h>
struct process{
        int at;
        int bt;
        int id;
        int rt;
        int wt;
        int tt;
        int ct;
        int started;
        int rem_bt;

}p[100];

void roundrobin(int n,struct process p[],int tq)
{
        int i,j;
        int index,front=0,rear=0;
        int queue[100];
        int completed=0;
        int currenttime=0;
        struct process temp;
        for(i=0;i<n;i++)
        {
                p[i].rem_bt=p[i].bt;
                p[i].started=0;
                p[i].rt=-1;
        }

        for(i=0;i<n-1;i++)
        {
                for(j=0;j<n-1;j++)
                {
                        if(p[j+1].at<p[j].at)
                        {
                                temp=p[j];
                                p[j]=p[j+1];
                                p[j+1]=temp;
                        }
                }
        }
         p[0].started=1;
        queue[rear++]=0;
        while(completed!=n)
        {

                //p[0].started=1;

                index=queue[front++];
                if(p[index].rt==-1)
                {
                        p[index].rt=currenttime-p[index].at;
                }
                if(p[index].rem_bt>tq)
                {
                        p[index].rem_bt-=tq;
                        currenttime+=tq;
                }
                else
                {

                        currenttime+=p[index].rem_bt;
                        p[index].rem_bt=0;
                        p[index].ct=currenttime;
                        completed++;
                        p[index].tt=p[index].ct-p[index].at;
                        p[index].wt=p[index].tt-p[index].bt;

                }
                for(i=0;i<n;i++)
                {
                        if(p[i].at<=currenttime&&p[i].started==0)
                        {
                                queue[rear++]=i;
                                p[i].started=1;
                        }
                }
                if(p[index].rem_bt>0){
                queue[rear++]=index;}
        }
        printf("\nprocess id\tarrival time\tburst time\tcompletion time\twaiting time\tturnaround time\tresponse time");
    for(i=0;i<n;i++){

    printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d",p[i].id,p[i].at,p[i].bt,p[i].ct,p[i].wt,p[i].tt,p[i].rt);}
}
int main()
{
    int i,n,tq;
    printf("Enter the no. of processes : ");
    scanf("%d", &n);
    printf("enter the time quantam");
    scanf("%d",&tq);
    struct process s[20];
    for (i = 0; i < n; i++) {
        printf("\n enter process id \n");
       scanf("%d",&p[i].id);
        printf("Enter the arrival time : ");
        scanf("%d", &p[i].at);
        printf("Enter the burst time : ");
        scanf("%d", &p[i].bt);
       }
       for(i=0;i<n;i++)
       {
        s[i]=p[i];
       }
       roundrobin(n,p,tq);
       return 0;
}
