#include <iostream>
#include <iomanip>
using namespace std;

struct node
{   int data, index;
    node *next, *prev;  };
int n=0, t_b=0, gantt[100], burst[100];
node* head = NULL;
void Insert(int , int);
void Delete(node*);
void Print();
void create_gantt();

int main()
{   cout<<"\t\t\t\t\tSOLVE Round Robin SCHEDULING\n\n";
    cout<<"Enter time bound :";cin>>t_b;
    cout<<"How many jobs available? :";cin>>n;
    cout<<endl;
    for(int i=1; i<=n; i++)
    {   cout<<"Enter BURST time of job "<<i<<" : ";cin>>burst[i];cout<<endl;
        gantt[i]=0;
        Insert(burst[i],i); }
    create_gantt();
    cout<<"Statics :"<<endl;
    cout<<"Process |    BT |  CT |  WT |"<<endl;
    float AVG_WT = 0;
    for(int i=1; i<=n; i++)
    {   cout<<" P "<<i<<"   ->  "<<setw(3)<<burst[i]<<"  |"<<setw(3)<<gantt[i]<<"  |"<<setw(3)<<gantt[i]-burst[i]<<"  |"<<endl;
        AVG_WT += (gantt[i]-burst[i]);  }
    cout<<"Average wT = "<<AVG_WT/n<<"ms"<<endl;    }
void Insert(int x, int i)
{   node *temp = new node();
    temp->data = x;
    temp->index = i;
    temp->prev = temp->next = NULL;
    if(head == NULL)
    {   head = temp;
        temp->next = temp->prev = temp;
        return;    }
    node *temp1 = head;
    do
    {   temp1 = temp1->next;
    }   while(temp1->next != head);
    temp1->next = head->prev = temp;
    temp->prev = temp1;
    temp->next = head;
}
void create_gantt()
{
    node* temp = head;
    int index = 1;
    while(head != NULL)
    {   //int time_bound = t_b;
        for(int i=1; i<=t_b; i++)
        {   if(temp->data != 0)
            {   temp->data--;
                if(index != temp->index)
                {   gantt[temp->index] = gantt[index]+1;    }
                else
                {   gantt[temp->index] += 1;    }   }
            index = temp->index;
            if(temp->data == 0)
            {   Delete (temp);
                break;  }   }
        temp = temp->next;  }
    return;
}
void Delete(node *temp)
{
    if(temp == head && head->next == head)
    {   head = NULL;
        delete temp;
        return; }
    else if(temp ==head && head->next != head)
    {   head = temp->next;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
        return; }
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    delete temp;
    return;
}
void Print()
{   node *temp = head;
    do
    {   cout<<temp->data<< " ";
        temp = temp->next;
    } while(temp != head);
}
