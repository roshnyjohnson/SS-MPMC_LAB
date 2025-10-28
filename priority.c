#include<stdio.h>
struct process
{

        int at;
        int bt;
        int ct;
        int tt;
        int wt;
        int id;
        int rt;
        int st;
        int priority;
        int completed;
}p[10];

void prior(int n,struct process p[])
{
        int completed=0;int currenttime=0;
        //int totalburst=100000;
        int i,j;
        int tot_ct,tot_tt,tot_wt;
        tot_tt=0;tot_wt=0;tot_ct=0;
        for(i=0;i<n;i++)
        {
                p[i].completed=0;
        }
        while(completed!=n)

        {
                int minimum=100000;
                int min_index=-1;
                for(i=0;i<n;i++)

                {
                        //int minimum=totalburst;
                        //int min_index=-1;
                        if(p[i].completed==0&&p[i].at<=currenttime)
                        {
                                if(p[i].priority<minimum)
                                {
                                        min_index=i;
                                        minimum=p[i].priority;
                                }
                                /*if(p[i].bt==minimum)
                                {
                                        if(p[i].at<p[min_index].at)
                                        {
                                                min_index=i;
                                                minimum=p[i].bt;
                                        }
                                }*/
                        }
                }
                if(min_index==-1)
                {
                        currenttime++;
                }
                else{
                        p[min_index].st=currenttime;
                        completed++;
                        p[min_index].ct=p[min_index].st+p[min_index].bt;
                        currenttime=p[min_index].ct;
                        //p[i].ct=starttime+;
                        p[min_index].completed=1;
                        p[min_index].tt=p[min_index].ct-p[min_index].at;
                        p[min_index].wt=p[min_index].tt-p[min_index].bt;
                        tot_ct+=p[min_index].ct;
                        tot_wt+=p[min_index].wt;
                        tot_tt+=p[min_index].tt;
                }
        }
        printf("\n");
    printf("the average completion time is %.2f\n",(float)tot_ct/n);
    printf("the average tt ime is %.2f\n",(float)tot_tt/n);
    printf("the average waiting time is %.2f\n",(float)tot_wt/n);printf("\n");
    printf("the average completion time is %.2f\n",(float)tot_ct/n);
    printf("the average tt ime is %.2f\n",(float)tot_tt/n);
    printf("the average waiting time is %.2f\n",(float)tot_wt/n);


        printf("\npid\tarrivaltime\tbursttime\tcompletiontimr\t\ttat\t\twaitingtime\n");
    for(i=0;i<n;i++)
    {
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].id,p[i].at,p[i].bt,p[i].ct,p[i].tt,p[i].wt);
    }
}
int main()
{
        int i;
        int n;
        printf("enter the number of process\n");
        scanf("%d",&n);
        for(i=0;i<n;i++)
        {
                printf("enter the id of process%d",i);
                scanf("%d",&p[i].id);

                 printf("enter the at of process%d",i);
                scanf("%d",&p[i].at);

                 printf("enter the bt of process%d",i);
                scanf("%d",&p[i].bt);
                printf("enter the priority of process %d",i);
                scanf("%d",&p[i].priority);
        }
prior(n,p);
return 0;
}
