#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SUCCESS 1
#define FAILURE 0

typedef struct tree_node
{

    struct tree_node *left;
    struct tree_node *right;
    struct tree_node *bf;
    struct tree_node *next;
    char name[20];
    char sub_code[10];
    int sem;
    char dept[20];
    int rollnum;
    int marks;
}node;


//initialisation
node* make_node();
node* create_record(node *root,int n);
node* insert_record(node *root);
node* check_avl(node *ptr);
node* check_bf(node *ptr);
node* rotate_left(node *ptr);
node* rotate_right(node *ptr);
node* delete_record(node *root,int roll_num,char* sub);
node* delete_node(node **pptr);
void range_search(node *root,int key1,int key2);
void print_data(node *root);
void print(node *root);
void search(node *root,int roll_num,char* sub);
int num_records(node *root);
node* get_max(node *root, char *sub);
int get_hight(node *root);
void get_failures(node *root,char *sub,int mark);
node* get_topper(node *root);
void print_topper();
node *make_nodes(node *root);
void print_kth(int k,char *sub);
void kth_topper(node *root,char *sub);
node *get_max_kth(node *root);

int res=0;
int ret2=0;
node *lptr=NULL;
node *nptr=NULL;
node *ptr1=NULL;
node *kptr=NULL;
//main function
int main()
{
    node *root,*ptr;
    root=NULL;
    char ch='y';
    int hight,n,key1,key2,k;
    int a,mark,ret,roll_num,num,res;
    char sub[20];

    while(ch == 'y'){
     printf("\t\t====  choose the operation  ====\n");
         	//ENTER THE VALUE
         	 printf("\n\t\t\t 1<<< create record \n");
             printf("\n\t\t\t 2<<< insert record \n");
             printf("\n\t\t\t 3<<< delete record \n");
             printf("\n\t\t\t 4<<< search record \n");
             printf("\n\t\t\t 5<<< get num of records \n");
             printf("\n\t\t\t 6<<< get hight \n");
             printf("\n\t\t\t 7<<< range search \n");
             printf("\n\t\t\t 8<<< print database \n");
             printf("\n\t\t\t 9<<< get max \n");
             printf("\n\t\t\t 10<<< get list of failures\n");
             printf("\n\t\t\t 11<<< get kth highest \n");
             printf("\n\t\t\t 12<<< get topper \n");

             scanf("%d",&a);

        //SWITCH CASE STATEMENT
        switch(a)
       {
         case (1):
             printf("\t\t enter the num of records");
             scanf("%d",&n);
             root=create_record(root,n);
             break;
         case 2:
           // if(root== NULL)
            //{
                root=insert_record(root);


            break;
         case 3:
             if(root == NULL)
             {
                 printf("\trecord is not present\n");
             }
             else{
            printf("enter roll number:\n");
            scanf("%d",&roll_num);
            printf("enter subject code:\n");
            scanf("%s",sub);
            root=delete_record(root,roll_num,sub);
            }

            break;

         case 4:
             printf("enter roll number:\n");
            scanf("%d",&roll_num);
            printf("enter subject code:\n");
            scanf("%s",sub);
            search(root,roll_num,sub);

            break;
         case 5:
            num=num_records(root);
            printf("\t\t\tnumber of records: %d\n",num);
            break;

         case 6:
             hight=get_hight(root);
             printf("\t\t\thight of the record : %d\n",hight);
             break;

         case 7:

              if(root == NULL){printf("record is empty\n");}
              else{
                printf("enter first roll num:\n");
                scanf("%d",&key1);
                printf("enter second roll num:\n");
                scanf("%d",&key2);
                range_search(root,key1,key2);
              }
              break;


         case 8:
            print_data(root);
            break;

         case 9:
            if(root == NULL)
            {
                printf("\t record is empty\n");
            }
            else{
                printf("\t enter subject code:\n");
                scanf("%s",sub);
                kth_topper(root,sub);
                print_kth(1,sub);
                break;
         case 10:
            if(root == NULL){printf("record is empty\n");}
            else{
                printf("\t enter subject code:\n");
                scanf("%s",sub);
                printf("enter passing marks:\n");
                scanf("%d",&mark);
                get_failures(root,sub,mark);}
                break;

         case 11:
            if(root == NULL){printf("record is empty\n");}
            else{
                printf("enter subject code\n");
                scanf("%s",sub);
                kth_topper(root,sub);
                printf("enter k:\n");
                scanf("%d",&k);
                print_kth(k,sub);
            }
            break;

         case 12:
            if(root == NULL){printf("record is empty\n");}
            else{
                lptr=get_topper(root);
                print_topper();
            }
            break;

            }
       }
    }

    return 0;

}
//make node
node* make_node()
{
    node *root;
    char s_name[20];
    char sub[20];
    int mark;
    int semester;
    int rn;
    char dept[20];

    root=(node *)malloc(sizeof(node));
        printf("enter student name:\n");
        scanf("%s",s_name);
        strcpy(root->name,s_name);
        printf("enter department name:\n");
        scanf("%s",dept);
        strcpy(root->dept,dept);
        printf("enter roll num:\n");
        scanf("%d",&rn);
        root->rollnum=rn;
        printf("enter sem:\n");
        scanf("%d",&semester);
        root->sem=semester;
        printf("enter sub code:\n");
        scanf("%s",sub);
        strcpy(root->sub_code,sub);
        printf("enter marks\n");
        scanf("%d",&mark);
        root->marks=mark;
        root->left=NULL;
       root->right=NULL;
        printf("\n\n\n\n");
  return root;
}
//create_record
node* create_record(node *root,int n)
{
    node *temp,*ptr;
    int done=0;
    int ret=FAILURE;
    int i;
       root=make_node();
       printf("=== insert successfull ===\n");
       root->bf=0;

       printf("=== balance factor: %d ===\n",root->bf);

       root=check_avl(root);
      for(i=1; i < n; i++)
      {   ptr=root;
          done=0;
          temp=make_node();
          while(!done)
          {

              if(temp->rollnum < ptr->rollnum)
              {
                  if(ptr->left == NULL)
                  {
                      ptr->left=temp;
                      done=1;
                      ret=SUCCESS;
                  }
                  else{
                    ptr=ptr->left;
                  }
              }
              else if(temp->rollnum > ptr->rollnum)
              {
                  if(ptr->right == NULL)
                  {
                      ptr->right=temp;
                      done=1;
                      ret=SUCCESS;
                  }
                  else{
                    ptr=ptr->right;
                  }
              }
              else
              {
                  if(strcmp(temp->sub_code,ptr->sub_code)<0)
                  {
                      if(ptr->left == NULL)
                      {
                          ptr->left=temp;
                          done=1;
                          ret=SUCCESS;
                      }
                      else {
                        ptr=ptr->left;
                      }
                  }
                  else if(strcmp(temp->sub_code,ptr->sub_code)>0)
                  {
                       if(ptr->right == NULL)
                     {
                      ptr->right=temp;
                      done=1;
                      ret=SUCCESS;
                    }
                     else{
                       ptr=ptr->right;
                     }

                  }
                  else{
                    strcpy(ptr->name,temp->name);
                    ptr->marks=temp->marks;
                    ptr->sem=temp->sem;
                    strcpy(ptr->dept,temp->dept);
                    done=1;
                    ret=SUCCESS;
                  }
              }
          }
          if(ret == 1)
          {
              printf("=== insert successfull ===\n");
              root=check_avl(root);
          }
          else{
            printf("=== error ===\n");
          }



    }


   return root;
}
//check_avl
node* check_avl(node *ptr)
{

        if(ptr!= NULL)
        {
        ptr->left=check_avl(ptr->left);
        ptr->right=check_avl(ptr->right);
        ptr=check_bf(ptr);

       }
 return ptr;
}


//check balance factor
node* check_bf(node *ptr)
{
     int lht=0;
     int rht=0;
     int diff=0;
     int balance,hlt,hrt;
     node *rptr=NULL;
     if(ptr->left == NULL && ptr->right== NULL)
     {
         diff=0;

     }
     else{
     lht=get_hight(ptr->left);
     rht=get_hight(ptr->right);
     diff =rht-lht;
     if(diff == 2)
     {


          node *pptr=ptr->right;
           hlt=get_hight(pptr->left);
          hrt=get_hight(pptr->right);
          if((hrt-hlt)==-1)
          {
              pptr=rotate_right(pptr);
              ptr->right=pptr;
              ptr=rotate_left(ptr);
          }
          else if((hrt-hlt)==1 || (hrt-hlt)==0){
            ptr=rotate_left(ptr);
          }

          ptr=check_avl(ptr);

     }
     else if(diff == -2)
     {

      node *pptr=ptr->left;
      hlt=get_hight(pptr->left);
    hrt=get_hight(pptr->right);
          if((hrt-hlt)==1)
          {
              pptr=rotate_left(pptr);
              ptr->left=pptr;
              ptr=rotate_right(ptr);
          }
          else if((hrt-hlt)==-1 || (hrt-hlt)==0){
            ptr=rotate_right(ptr);
          }


          ptr=check_avl(ptr);

     }
   printf("before rotation:");
   printf("b.f %d\n",diff);
   //printf("%s",ptr->name);
  }
return ptr;
}
//rotate right

node* rotate_right(node *ptr)
{
    node *temp;
    int lht,rht;
    if(ptr== NULL)
    {
        printf("error");

    }
    else if(ptr->left == NULL)
    {
        printf("can not rotate\n");
    }
    else{
        temp=ptr->left;
        ptr->left=temp->right;
        temp->right=ptr;
    }
    printf("after right rotation\n");
    lht=get_hight(temp->left);
    rht=get_hight(temp->right);
    printf("bf :%d\n",rht-lht);
    return temp;
}

//rotate left
node* rotate_left(node *ptr)
{
    node *temp;
    int lht,rht;
    if(ptr == NULL)
    {
        printf("error\n");

    }
    else if(ptr->right == NULL)
    {
        printf("can not rotate\n");
    }
    else{
        temp=ptr->right;
        ptr->right=temp->left;
        temp->left=ptr;
    }
    printf("after left rotation\n");
    lht=get_hight(temp->left);
    rht=get_hight(temp->right);
    printf("bf :%d\n",rht-lht);
    //print_data(temp);
    return temp;
}

//insertion
node* insert_record(node* root)
{
     node *pttr=root;
          int ret=0,done=0;
          node* temp=make_node();
          if(root == NULL){
              ret=1;
              printf("=== insert successfull ===\n");
              root=check_avl(root);

                return temp;
          }
          else{
          while(!done)
          {

              if(temp->rollnum < pttr->rollnum)
              {
                  if(pttr->left == NULL)
                  {
                      pttr->left=temp;
                      done=1;
                      ret=SUCCESS;
                  }
                  else{
                    pttr=pttr->left;
                  }
              }
              else if(temp->rollnum > pttr->rollnum)
              {
                  if(pttr->right == NULL)
                  {
                      pttr->right=temp;
                      done=1;
                      root=check_avl(root);
                      printf("%s",root->name);
                      printf("%s",root->left->name);
                      printf("%s",root->right->name);
                      ret=SUCCESS;
                  }
                  else{
                    pttr=pttr->right;
                  }
              }
              else
              {
                  if(strcmp(temp->sub_code,pttr->sub_code)<0)
                  {
                      if(pttr->left == NULL)
                      {
                          pttr->left=temp;
                          done=1;
                          ret=SUCCESS;
                      }
                      else {
                        pttr=pttr->left;
                      }
                  }
                  else if(strcmp(temp->sub_code,pttr->sub_code)>0)
                  {
                       if(pttr->right == NULL)
                     {
                      pttr->right=temp;
                      done=1;
                      ret=SUCCESS;
                    }
                     else{
                       pttr=pttr->right;
                     }

                  }
                  else{
                    strcpy(pttr->name,temp->name);
                    pttr->marks=temp->marks;
                    pttr->sem=temp->sem;
                    strcpy(pttr->dept,temp->dept);
                    done=1;
                    ret=SUCCESS;
                  }
              }
          }

          if(ret == 1)
          {
              printf("=== insert successfull ===\n");
              root=check_avl(root);
          }
          else{
            printf("=== error ===\n");
          }
          }
        return root;
}

//delete record
node* delete_record(node *root,int roll_num,char *sub)
{
    node *ptr, *prev,*new,*new1,*new2,*ptr3;
    new1=root;
    prev=NULL;
    ptr=root;
    int done=0,ret=0;
    while(ptr !=NULL && !done)
    {
        if(ptr->rollnum < roll_num)
        {
            prev=ptr;
            ptr=ptr->right;
        }
        else if(ptr->rollnum > roll_num){
            prev=ptr;
            ptr=ptr->left;
        }
        else{
            if(strcmp(ptr->sub_code,sub)<0)
        {
            prev=ptr;
            ptr=ptr->right;
        }
            else if(strcmp(ptr->sub_code,sub)>0){
            prev=ptr;
            ptr=ptr->left;
           }
           else{
            done=1;
           }
        }
    }

    if(done==1)
    {
        if(ptr!=NULL)
        {
            if(prev!=NULL)
            {
                if(prev->left == ptr)
                {
                    new=delete_node(&(prev->left));
                    prev->left=new;
                    ret=1;
                    //root=check_avl(root);
                }
                else if(prev->right == ptr)
                {//printf("hii");
                    new=delete_node(&(prev->right));
                    prev->right=new;
                    ret=1;printf("%s",root->name);
                    //root=check_avl(root);
                }
            }
            else{
               if(ptr->left!= NULL){
                ptr3=ptr->left;
                new1=ptr3;
                while(ptr3->right!=NULL)
                {
                    ptr3=ptr3->right;
                }
                ptr3->right=ptr->right;
                free(ptr);
                ret=1;

                //new1=check_avl(new1);

            }
            else if(ptr->left == NULL && ptr->right == NULL)
            {
                free(ptr);
                ret=1;
            }

            }
        if(ret==1)
            {
                printf("=== deleted successfull ===\n");
            }
            else{
                printf("=== error ===\n");

            }
        }

    }
    else{
        printf("record is not present\n");
    }

  root=check_avl(new1);
    return root;
}
//delete node
node* delete_node(node **pptr)
{
    node *q=NULL,*r=NULL;
    int done=0;
    if(*pptr == NULL)
    {
        printf("error\n");
    }
    else if((*pptr)->right == NULL)
    {
        if((*pptr)->left !=NULL){
        (*pptr)=(*pptr)->left;
         q=(*pptr);}
        else{
            free(*pptr);
        }
    }
    else if((*pptr)->left == NULL && (*pptr)->right!=NULL)
    {
        *pptr=(*pptr)->right;
        q=(*pptr);
    }
    else
    {
        q=(*pptr)->left;
        while(q->right != NULL)
        {
            r=q;
            q=q->right;
        }/*if(r!=NULL){
        r->right=q->left;}
        q->left=(*pptr)->left;
        q->right=(*pptr)->right;
        r=(*pptr);
        (*pptr)=q;
        free(r);*/
        q->right=(*pptr)->right;
        free(*pptr);

    }
    return q;
}
//search record
void search(node *root,int roll_num,char* sub)
{
    node *ptr,*ptr2;
    ptr=root;
    int done=0;
    while(ptr != NULL && ptr->rollnum != roll_num)
    {
        if(roll_num < ptr->rollnum)
        {
            ptr=ptr->left;
        }
        else{
            ptr=ptr->right;
        }
    }
    ptr2=ptr;
    while(ptr2!= NULL && strcmp(ptr2->sub_code,sub)!=0)
    {
        if(strcmp(ptr2->sub_code,sub)<0)
        {
            ptr2=ptr2->right;
        }
        else{
            ptr2=ptr2->left;
        }
    }
    if(ptr2->rollnum == roll_num && strcmp(ptr2->sub_code,sub)==0)
    {
        done=1;
    }
    if(done == 1)
    {
        printf("\tstudent name: %s\n",ptr2->name);
        printf("\tdepartment name: %s\n",ptr2->dept);
        printf("\tsemester : %d\n",ptr2->sem);
        printf("\troll number: %d\n",ptr2->rollnum);
        printf("\tsubject code: %s\n",ptr2->sub_code);
        printf("\tmarks: %d\n",ptr2->marks);
        printf("===============\n");
    }
    else{
        printf("\trecord is not present\n");
    }
}

//num of records
int num_records(node *root)
{
    if(root == NULL)
    {
        ret2=0;
    }
    else{
        ret2=1+num_records(root->left)+num_records(root->right);
    }
    return ret2;
}


//hight
int get_hight(node *root)
{
    int lht=0;
    int rht=0;
    if(root==NULL){return -1;}
    else if(root->left ==NULL && root->right == NULL){return 0;}
    else{
        lht=get_hight(root->left);
        rht=get_hight(root->right);
        if(lht > rht){return (lht+1);}
        else {return (rht+1);}
    }
}

//range search
void range_search(node *root,int key1, int key2)
{
    if(root != NULL)
    {
        range_search(root->left,key1,key2);
        if((root->rollnum >= key1) && (root->rollnum <=key2))
        {
              print(root);
        }
        range_search(root->right,key1,key2);
    }
}
//print database
void print_data(node *root)
{
    if(root != NULL)
    {


         print(root);
         print_data(root->left);
        print_data(root->right);
    }
}

void print(node *root)
{

        printf("\tstudent name: %s\n",root->name);
        printf("\tdepartment name: %s\n",root->dept);
        printf("\tsemester : %d\n",root->sem);
        printf("\troll number: %d\n",root->rollnum);
        printf("\tsubject code: %s\n",root->sub_code);
        printf("\tmarks: %d\n",root->marks);
        printf("\t===============\n\n\n");
}


//kth topper
void kth_topper(node *root,char *sub)
{
    if(root!=NULL)
    {
        kth_topper(root->left,sub);
        if(strcmp(root->sub_code,sub)==0)
        {
        kptr=make_nodes(root);
        }
        kth_topper(root->right,sub);
    }
}
void print_kth(int k,char *sub)
{

    node *kkptr=NULL;
    int i;

    for(i=k;i>0;i--)
    {
      if(kptr!= NULL){
       kkptr=get_max_kth(kptr);
       if(i-1 !=0)
       {
           free(kkptr);
       }
       else{
        print(kkptr);
       }
       kptr=kptr->next;}

    }

}

node* get_max_kth(node *root)
{
   int result=0;
    while(root!=NULL){
        if(root->marks > result){
         result=root->marks;
         ptr1=root;}
         root=root->next;
    }

     return ptr1;

}

//get list of failures
void get_failures(node *root,char* sub,int mark)
{
    if(root != NULL){
    get_failures(root->left,sub,mark);
    if(strcmp(root->sub_code,sub)==0)
    {
        if(root->marks < mark)
        {
            print(root);
        }
    }
    get_failures(root->right,sub,mark);}

}



node* get_topper(node *root)
{
    if(root !=NULL){
    get_topper(root->left);
    if(lptr==NULL)
    {
        lptr=make_nodes(root);
    }
    else{
    if(strcmp(root->dept,lptr->dept)==0 && root->rollnum == lptr->rollnum && root->sem==lptr->sem){
    lptr->marks=lptr->marks+root->marks;}

    else{
      lptr=make_nodes(root);

    }
    }

    get_topper(root->right);}

  return lptr;

}
node* make_nodes(node *root)
{
    lptr=(node* )malloc(sizeof(node));
    strcpy(lptr->name,root->name);
    strcpy(lptr->dept,root->dept);
    lptr->sem=root->sem;
    lptr->rollnum=root->rollnum;
    lptr->marks=root->marks;
    strcpy(lptr->sub_code,root->sub_code);
    lptr->next=nptr;
    nptr=lptr;
   return lptr;
}
void print_topper()
{
    node *temp;
    int h=0;
    if(lptr->next == NULL)
    {
        print(lptr);
    }
    else{
    lptr=lptr->next;
    while(lptr!=NULL)
    {
        if(lptr->marks > h)
        {
            h=lptr->marks;
            temp=lptr;
        }
        lptr=lptr->next;

    }
    print(nptr);
    }

}


