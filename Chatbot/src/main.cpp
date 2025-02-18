/*
    it is a complete binary tree.🌲🌲
    every lvl fill completly.
    Node always added from left. 
    Max heap ma root ni value vadhare ne child ni value ochi hoy   root->📈 child->📉
    Min heap ma root ni value ochi ne child ni value vadhare hoy   root->📉 child->📈

    /\👁️ In normal cash create this with the help of array 👁️/\

    //  ⚠️⚠️     Make sure you go through 0 or 1 bash index      ⚠️⚠️  //
    // Most IMP --👀-- You can make Max and Min heap with priority queue --👀-- //

*/

#include <bits/stdc++.h>
//for accesing priority queue
#include <queue>
using namespace std;

//This class for MaxHeap
class heap
{
    public:

    int arr[1000];
    int size;

    heap()
    {
        arr[0] = -1;
        size = 0;
    }

    //this function for insert
    void insert(int data)
    {
        //step - 1 insert in heap
        size++;
        int index = size;
        arr[index] = data;

        //step - 2 find that node's actuale palce   

        while(index > 1)
        {
            int parent = index/2; 
            if(arr[parent] < arr[index])
            {
                swap(arr[parent],arr[index]);
                index = parent;
            }
            else
                return;
        }
    }

    void delete_heap()
    {
        if(!size) 
            cout<<"Nothing to delete"<<endl;

        //step 1 : put last element to first
        arr[1] = arr[size];

        //step 2 : remove last element  
        size--;

        //this i reperesent the index taht we are adding from last now move this to correct index
        int i = 1;

        while(i < size)
        {
            int LeftIndex = 2*i;
            int RightIndex = 2*i + 1;

            if(LeftIndex < size && arr[i] < arr[LeftIndex])
            {
                swap(arr[i],arr[LeftIndex]);
                i = LeftIndex; //Goto Left👈
            }
            if(RightIndex < size && arr[i] < arr[RightIndex])
            {
                swap(arr[i],arr[RightIndex]);
                i = RightIndex;//Goto Rigth👉
            }
            else
            {
                //you are here mean all thing are good😊
                return;
            }

        }

    }

    //chalo output joiye aanathi
    void print()
    {
        for(int p = 1 ; p <= size ; p++)
            cout<<arr[p]<<" ";

    }
};

void heapify(int arr[],int n,int i)
{
    int largest = i;
    int left = 2*i;
    int right = 2*i + 1;

    if(left <= n && arr[largest] < arr[left])
    {
        largest = left;
    }
    if(right <= n && arr[largest] < arr[right])
    {
        largest = right;
    }

    if(largest != i)
    {
        swap(arr[largest],arr[i]);
        heapify(arr,n,largest);
    }
 
}

//heap sort
void HeapSort(int arr[],int n)
{
    int t = n;

    while (t > 1)
    {
        //step 1 : swap 
        swap(arr[t],arr[1]);
        t--;

        //step 2
        heapify(arr,t,1);

    }

}

int main()
{
    heap hp;

    for(int p = 1 ;p <= 10 ; p++)
    {
        hp.insert(p);
    }

    hp.print();
    hp.delete_heap();
    cout<<endl;
    hp.print();
    cout<<endl;

    //  ✨  let's implement heap with heapify   ✨ //

    int arr[6] = {-1,54,53,55,52,50};
    int n = 5;

    for(int p = n/2 ; p > 0 ; p--)
    {
        heapify(arr,n,p);
    }
    cout<<"Heapify : ";
    //printing heapify with array
    for(int p = 1 ;p <= n ; p++)
    {
        cout<<arr[p]<<" ";
    }
    cout<<endl;


    //  ✨  HeapSort   ✨ //
    HeapSort(arr,n);
    cout<<"HeapSort : ";
    for(int p = 1 ;p <= n ; p++)
    {
        cout<<arr[p]<<" ";
    }
    cout<<endl;



    //      Use Priority_Queue      //
    cout<<"Using Priority queue"<<endl;
    //     👉MaxHeap 👈     //
    priority_queue<int> pq;

    pq.push(4);
    pq.push(5);
    pq.push(2);
    pq.push(3);

    cout<<"element at top: "<<pq.top()<<endl;
    //pq.push() also a function


    //      👉MinHeap 👈     //
    priority_queue<int,vector<int>,greater<int>> MinHeap;

    MinHeap.push(4);
    MinHeap.push(5);
    MinHeap.push(2);
    MinHeap.push(3);

    cout<<"element at top: "<<MinHeap.top()<<endl;
    //pq.push() also a function

    return 0;
}