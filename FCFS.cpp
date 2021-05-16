#include<iostream>
#include<iomanip>
using namespace std;

int n = 0, arrival[100], burst[100], ac[100], bc[100], aux[100], gantt[100], index_arrival[100],actual_index[100], ideal_no = 0, ideal_time = 0;
void Sort_arrival(int*, int* ,int*, int);
void check_zero_begin(int*, int*);
void is_cpu_ideal();
void decrement(int);
int check_job_zero(int*, int);
void heart (int*, int*);

int main()
{
    cout<<"\t\t\t\t\tSOLVE FCFS SCHEDULING\n\n";
    cout<<"How many jobs available? :";cin>>n;
    for(int i=1; i<=n; i++)
    {
        cout<<"Enter ""ARRIVAl"" time of job "<<i<<" : ";cin>>arrival[i];
        cout<<"Enter BURST time of job "<<i<<" : ";cin>>burst[i];cout<<endl;
        ac[i]=arrival[i];
        bc[i]=burst[i];
        actual_index[i]=i;
        index_arrival[i]=i;
        aux[i]=0;
        gantt[i]=0;
    }
    Sort_arrival(ac, index_arrival, bc, n);
    check_zero_begin(ac, bc);
    cout<<"Statics :"<<endl;
    cout<<"Process |    AT |  BT |  CT | TAT |  WT |"<<endl;
    float AVG_TAT = 0, AVG_WT = 0;
    for(int i=1; i<=n; i++)
    {
     cout<<" P "<<i<<"   ->  "<<setw(3)<<arrival[i]<<"  |"<<setw(3)<<burst[i]<<"  |"<<setw(3)<<gantt[i]<<"  |"<<setw(3)<<gantt[i]-arrival[i]<<"  |"<<setw(3)<<gantt[i]-arrival[i]-burst[i]<<"  |"<<endl;
     AVG_TAT += (gantt[i]-arrival[i]);
     AVG_WT += (gantt[i]-arrival[i]-burst[i]);
    }
    cout<<"Average TAT = "<<AVG_TAT/n<<"ms"<<endl;
    cout<<"Average wT = "<<AVG_WT/n<<"ms"<<endl;
    is_cpu_ideal();

}
void Sort_arrival(int *a, int *b, int *c, int n)
{
      for(int i=1; i<=n-1; ++i)
      {
          int index = 0;
          int temp = a[i];
          for(int j = i+1; j<=n; ++j)
          {
             if(temp > a[j])
             {
                 index = j;
                 temp = a[j];
             }
          }
          if(index !=0)
          {
              swap(a[i], a[index]);
              swap(b[i], b[index]);
              swap(c[i], c[index]);
          }
      }
      for(int i=1; i<=n; i++)
      {
          cout<<"Arrival: "<< a[i]<<" Burst: "<<c[i]<<" actual index: "<<b[i]<<endl;
      }
}
void check_zero_begin(int *ac, int *bc)
{
    if(ac[1] == 0)
    {
        heart(ac, bc);
        cout<<" Yesss...."<<endl;
    }
    else
    {
        bc[1] += ac[1];
        ideal_no++;
        ideal_time +=  ac[1];
        ac[1] = 0;
        heart(ac, bc);
    }
}
void heart (int* ac, int* bc)
{
 int prev_index = 1;
    for(int i=1; i<=n; i++)
    {
        aux[i] = bc[i];
        if(i<n)
        {
            int index = 1, x = ac[i+1]-ac[i];
            for(int j = 0; j<x; j++)
            {
                index = check_job_zero(aux, i);
                if(index != -1)
                {
                    decrement(index);
                    if(prev_index != actual_index[index])
                    {
                        gantt[actual_index[index]] = gantt[prev_index];
                    }
                    gantt[actual_index[index]] += 1;
                }
                else
                {
                    ideal_no++;
                    bc[i+1] += (ac[i+1]-gantt[prev_index]);
                    ideal_time += (ac[i+1]-gantt[prev_index]);
                    ac[i+1] = gantt[prev_index];
                    break;
                }
                if(index != -1)
                {
                    prev_index = actual_index[index];
                }
            }
        }
    }
    for(int i = 1; i<=n; i++)
    {
        if(i==1 && aux[i] !=0)
        {
            gantt[actual_index[i]] += aux[i];
        }
        else if(i>1 && aux[i] !=0)
        {
            if(gantt[actual_index[i]] > gantt[actual_index[i-1]])
            {
                gantt[actual_index[i]] += aux[i];
            }
            else
            {
                gantt[actual_index[i]] = gantt[actual_index[i-1]] + aux[i];
            }
        }
    }
    for(int i=1; i<=n; i++)
    {
        swap(gantt[index_arrival[i]],gantt[i]);
    }
}
void decrement(int index)
{
 aux[index] -=1;
}

void is_cpu_ideal()
{
    if(ideal_no != 0)
    {
        cout<<"NOTE : C.P.U was ideal "<<ideal_no<<" time/times, for total of "<<ideal_time<< "ms."<<endl;
        return;
    }
    return;
}
int check_job_zero(int *aux, int n)
{
    int i = 1;
    while(aux[i] == 0 && i<=n)
    {
        i++;
    }
    if(aux[i] !=0 && i<=n)
        return i;
    return -1;
}
