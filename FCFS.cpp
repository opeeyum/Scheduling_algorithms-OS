#include <iostream>
using namespace std;

int main()
{
    cout<<"First Come First Serve Scheduling Algorithm\n";

    //cout<<"Enter Number of Process(es): ";
    //Number of Process
    int n=5; 
    //cin>>n;

    int at[n] = {0, 1, 2, 3, 6}, bt[n]= {2, 6, 4, 9, 12}, ct[n];

    /*for(int i=0; i<n; i++)
    {
        cout<<"Arrival time of Process P"<<i<<": ";
        cin>>at[i];
        cout<<"Burst time of Process P"<<i<<": ";
        cin>>bt[i];
    }*/

    int timer = 0, idle = 0;

    for(int i=0; i<n; i++)
    {
        //Case when no new process is to schedule after completion of previous process
        if(timer < at[i])
        {
            idle += at[i] - timer;
            timer = at[i];
        }

        timer += bt[i];
        ct[i] = timer;
    }  

    cout<<"Process | Arr.T | Bur.T | Com.T | Tur.T | Wai.T" <<endl;
    for(int i=0; i<n; i++)
    {       
       printf("P%-6d | %-5d | %-5d | %-5d | %-5d | %-5d\n", i, at[i], bt[i], ct[i], ct[i]-at[i], ct[i]-at[i]-bt[i]);
    }

    if(idle)
    cout<<"CPU was idle for: "<<idle<<" time unit."<<endl;

    return 0;
}