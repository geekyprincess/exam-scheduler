/*  Project : Exam Scheduler- creates time slots for exam to be held such that no same student has two exams at the same time slot.
    We have used the greedy approach and knowledge of data structures like graph, linked lists, arrays etc. to create the scheduler
    It is our original work! 
    
    The scheduler has been made by geekprincess(aka Ashima) along with Manisha
    Feel free to share, improvise on the code. Happy Coding....If you find any bug, need help...feel free to ping back... :) 
*/

#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<string.h>

char str[20];
int j=0;
int maxSub;
//structure definition for linked list
typedef struct Node
{
        int check; //created to keep track if the node is alread inserted in a time slot or not.
        int data; // to store unique key for each subject
        char item[20];
        struct Node *next;
}node;

int insert(node *pointer, char *sub)
{
        node *start = pointer;
        //traverse through the list till we encounter the last node.
        while(pointer->next!=start)
        {
                pointer = pointer -> next;
        }
        // allocate memory for the new node and put data in it.
        pointer->next = (node *)malloc(sizeof(node));
        pointer = pointer->next;
        strcpy((pointer->item),sub);
        pointer->data = j;
        pointer->check = 0;
        pointer->next = start;
        j++;
        return (pointer->data);
}

int find(node *pointer, char *item)
{
        node *start = pointer;
        pointer =  pointer -> next; //First node is dummy node.
        //traverse through the entire linked list and search for the key.
        while(pointer!=start)
        {
                if(strcmp(pointer->item,item)==0) //data is found.
                {
                        return (pointer->data);
                }
                pointer = pointer -> next;  //search in the next node.
        }
        return -1;  //data is not found
}

//function to display the name of all the subjects when its unique code and start is passed to it
void showName(int x, node *pointer)
{
        node *start = pointer;
        pointer =  pointer -> next; //First node is dummy node.
        //traverse through the entire linked list and search for the key.
        while(pointer!=start)
        {
                if(pointer->data==x) //key is found.
                {
                        puts(pointer->item);
                }
                pointer = pointer -> next;  //search in the next node.
        }
}

//function which calls to add only unique subject in list
int cal(node *start, char *sub)
{
        int status;
        status = find(start,sub);
        if(status == -1)
            status = insert(start,sub);
        return status;
}

//function returns the unique key for a subject which is not added to graph
int getVertex(node *pointer, node **cur)
{
        pointer = *cur;
        node *start = pointer;
        pointer =  pointer -> next; //First node is dummy node.
        // traverse through the entire linked list and search for the key.
        while(pointer!=start)
        {
                if(pointer->check ==0) //key is found.
                {
                        *cur = pointer;
                        return (pointer->data);
                }
                pointer = pointer -> next;  //search in the next node.
        }
        *cur = pointer;
        //key is not found in the list
        return -1;
}

//function use to set check = 1 when a node of linked list is added to graph
void setVertex(node *pointer, int x)
{
        node *start = pointer;
        pointer =  pointer -> next; //First node is dummy node.
        //traverse through the entire linked list and search for the key
        while(pointer!=start)
        {
                if(pointer->data == x) //key is found.
                {
                        pointer->check = 1;
                        return;
                }
                pointer = pointer -> next;  //search in the next node.
        }
}

// structure to represent an adjacency list node
struct AdjListNode
{
    int index;
    struct AdjListNode* graph_next;
};

// A structure to represent an adjacency liat
struct AdjList
{
    struct AdjListNode *graph_head;  // pointer to graph_head node of list
};

// structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph
{
    int V;
    struct AdjList* array;
};

// function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int x)
{
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->index = x;
    newNode->graph_next = NULL;
    return newNode;
}

// function that creates a graph of V vertices
struct Graph* createGraph()
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = maxSub;
    // Create an array of adjacency lists.  Size of array will be maxSub
    graph->array = (struct AdjList*) malloc(maxSub * sizeof(struct AdjList));
     // Initialize each adjacency list as empty by making head as NULL
    int i;
    for (i = 0; i < maxSub; ++i)
        graph->array[i].graph_head = NULL;

    return graph;
}

// Adds an edge to an undirected graph
void addEdge(struct Graph* graph,int s, int d)
{
    // Add an edge from src to dest if it is not present. A new node is added to the adjacency
    //list of src.
    if(checkEdge(graph,s,d)==0)
    {
        struct AdjListNode* newNode = newAdjListNode(d);
        newNode->graph_next = graph->array[s].graph_head;
        graph->array[s].graph_head = newNode;
        // Since graph is undirected, add an edge from dest to src also
        newNode = newAdjListNode(s);
        newNode->graph_next = graph->array[d].graph_head;
        graph->array[d].graph_head = newNode;
    }
}

//function to find if edge exists between two nodes..Returns 1 if edge exists and 0 if not
int checkEdge(struct Graph* graph, int a, int b)
{
    int y;
    struct AdjListNode* temp = graph->array[a].graph_head;
    while (temp)
    {
        if((temp->index)==b)
        {
             y=1;   //if edge exists
             return y;
        }
        temp = temp->graph_next;
    }
    y=0;//if edge doesn't exist
    return y;
}

//structure for binary tree
typedef struct BinaryTree
{
    int b_data;
    struct BinaryTree *lchild,*rchild;
}b_node;

//function to make a new node in binary tree
b_node *get_b_node()
 {
    b_node *temp;
    temp=(b_node *)malloc(sizeof(b_node));
    temp->lchild=NULL;
    temp->rchild=NULL;
    return temp;
 }

// function for creating a binary search tree
void b_insert(b_node *root, b_node *new_b_node)
{
  if(new_b_node->b_data < root->b_data)
   {
     if(root->lchild==NULL)
         root->lchild = new_b_node;
     else
         b_insert(root->lchild,new_b_node);
   }

   if(new_b_node->b_data > root->b_data)
    {
        if(root->rchild==NULL)
            root->rchild=new_b_node;
        else
            b_insert(root->rchild,new_b_node);
     }
}

//function know if edge is there or not
int b_tell(struct Graph* graph,b_node *temp, int x)
{
    int y=0;
    if(temp!=NULL)
    {
       y = checkEdge(graph,x,temp->b_data);
       if(y==1)                         //if edge exists
            return y;
       y= b_tell(graph,temp->lchild,x);
       y= b_tell(graph,temp->rchild,x);
    }
    return y;//edge doesn't exist
}
//to traverse the binary tree till not null and call showName funtion for every data to display the name of the subject
void b_traverse(b_node *temp, node *pointer)
{
   if(temp!=NULL)
    {
        b_traverse(temp->lchild,pointer);
        showName(temp->b_data,pointer);
        b_traverse(temp->rchild,pointer);
    }
    else
        return;
}

//function to delete the tree
void deletetree(b_node *tree)
 {
    if (tree)
    {
        deletetree(tree->lchild);
        deletetree(tree->rchild);
        free(tree);
    }
}
//function to read the input text file, extract data and build a graph
void file(struct Graph* graph, node*start)
{
    int x,y,z,i;
    char a[20],b[20],c[20]; //to store the three subjects for each student and call all combinations for creating an edge
    FILE *fp;
    fp=fopen("data.txt","r");//sample file 'data_check.txt' which holds the student name and thre subjects he/she is enrolled in
    fseek(fp,0,SEEK_SET);
    fgets(str,100,fp);
    i=1; //done just for the sake of ease
    while(!feof(fp))
    {
        if(i==4)
        { //condition to check if the subject list for one student is over

            fgets(str,100,fp);
            i=1;
            x = cal(start,a); //load x with the unique index assigned in linked list
            y = cal(start,b);//load y with the unique index assigned in linked list
            addEdge(graph, x, y); //create an edge between the two subjects
            //insert edge between a and b
            x = cal(start,a);
            y = cal(start,c);
             addEdge(graph, x, y);
            //insert edge between a and c
            x = cal(start,b);
            y = cal(start,c);
             addEdge(graph, x, y);
            //insert edge between b and c
            a[0] = '\0'; //to again set the variables to null
            b[0] = '\0';
            c[0] = '\0';
        }
        fgets(str,100,fp);
        {
            if(i==1) //subject 1
                strcpy(a,str);
            if(i==2) // subject 2
                strcpy(b,str);
            if(i==3) //subject 3
                strcpy(c,str);
        }
        i++;
    }
    x = cal(start,a);
    y = cal(start,b);
    addEdge(graph, x, y);
    //insert edge between a and b
    x = cal(start,a);
    y = cal(start,c);
    addEdge(graph, x, y);
    //insert edge between a and c
    x = cal(start,b);
    y = cal(start,c);
    addEdge(graph, x, y);
    //insert edge between b and c
    fclose(fp);
}

//to create the time slot for the exams
void create_time_slot(struct Graph* graph, node*start)
{
    int z, time_slot = 0, t=0;
    node *cur;
    b_node *new_b_node,*b_root,*b_tmp,*b_parent;
    b_node *get_b_node();
    b_root=NULL;
    new_b_node=get_b_node();

    while(t!=-1)
    {
        cur = start;
        for(z =0; z<maxSub; z++)
        {
            if(b_root == NULL)
            {
                if(t!=-1)
                {
                    new_b_node->b_data = t;
                     b_root=new_b_node;
                     setVertex(start,t);
                }
            }
            else
            {
                t = getVertex(start,&cur);
                if(t!=-1)
                {
                    int y;
                    y = b_tell(graph,b_root,t); //to know if edge exists between t and id's in binary tree
                    if(y==0)
                    {
                        new_b_node->b_data = t;
                        b_insert(b_root,new_b_node);
                        setVertex(start,t);
                    }

                }
            }
               new_b_node=get_b_node();
        }
        ++time_slot;
        printf("\nExams in time slot %d are :\n", time_slot);
        b_traverse(b_root,start);
        printf("\n");
        cur = start;
        t = getVertex(start,&cur);
        deletetree(b_root);
        b_root= NULL;
    }
}

void main()
{
    printf("Enter the total no. of unique subjects\t");
    fflush(stdin);
    scanf("%d",&maxSub);
    //Used to create a linked list with starting dummy node
    node *start,*temp, *cur;
    start = (node *)malloc(sizeof(node));
    temp = start;
    temp -> next = start;
    //graph is created using createGraph() funtion
    struct Graph* graph = createGraph(maxSub);
    //file function is called to extract subjects from file and load unique subjects in graph
    file(graph, start);
    //this funtion is used to create time slots
    create_time_slot(graph,start);
}
