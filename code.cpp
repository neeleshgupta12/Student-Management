/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


//              STUDENT MANAGEMENT SYSTEM



/////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////

//              Header Files

/////////////////////////////////////////////////////////////////////////////////////

#include<bits/stdc++.h>
#include<conio.h>
using namespace std;


/////////////////////////////////////////////////////////////////////////////////////
//              Class for Login Purpose
/////////////////////////////////////////////////////////////////////////////////////

class user
{
public: char user_n[20];
	    char pass_n[20];

}u1;


/////////////////////////////////////////////////////////////////////////////////////
//              Class for Student Node
/////////////////////////////////////////////////////////////////////////////////////
class stu
{
public: string name;
        int roll_no, marks_m3, marks_ps, marks_de, marks_ds, marks_dm;
        stu* next;

        stu(string name,int roll_no, int marks_m3=0, int marks_ps=0, int marks_de=0, int marks_ds=0, int marks_dm=0)
        {
            this->name = name;
            this->next = NULL;
            this->roll_no = roll_no;
            this->marks_m3 = marks_m3; this->marks_ps = marks_ps; this->marks_de = marks_de;
            this->marks_ds = marks_ds; this->marks_dm = marks_dm;
        }
};
/////////////////////////////////////////////////////////////////////////////////////
//              Class for Hash Table
/////////////////////////////////////////////////////////////////////////////////////
class hashmap
{
public:
        int currsize;
        int maxsize;
        stu* *bucket;

        hashmap(int defaultsize = 7)
        {
            this->maxsize = defaultsize;
            this->currsize = 0;
            this->bucket = new stu*[this->maxsize];

            for(int i=0;i<this->maxsize;i++)
            {
                this->bucket[i] = NULL;
            }
        }

        int hashfunction(string name)
        {
            int multifactor = 1;
            int idx = 0;

            for(int i=0;i<name.length();i++)
            {
                idx = (idx%this->maxsize + ((name[i]%this->maxsize)*(multifactor%this->maxsize)%this->maxsize));
                idx = idx%this->maxsize;

                multifactor = ((multifactor%this->maxsize)*(37%this->maxsize)%this->maxsize);
            }

            return idx%this->maxsize;
        }

        void rehash()
        {
            int oldsize = this->maxsize;
            stu* *oldbucket = this->bucket;

            this->maxsize = 2*oldsize;
            this->bucket = new stu*[this->maxsize];

            for(int i=0;i<this->maxsize;i++)
            {
                this->bucket[i] = NULL;
            }
            this->currsize = 0;

            for(int i=0;i<oldsize;i++)
            {
                stu* temp = oldbucket[i];

                while(temp!=NULL)
                {
                    insert(temp->name,temp->roll_no,temp->marks_m3,temp->marks_ps,temp->marks_de,temp->marks_ds,temp->marks_dm);
                    temp = temp->next;
                }
            }

            delete [] oldbucket;
        }

        void insert(string name,int roll_no, int marks_m3=0, int marks_ps=0, int marks_de=0, int marks_ds=0, int marks_dm=0)
        {
            float loadfactor = (float)currsize/maxsize;

            if(loadfactor > 0.6)
            {
                rehash();
            }

            int idx = hashfunction(name);

            stu* n = new stu(name,roll_no,marks_m3,marks_ps,marks_de,marks_ds,marks_dm);
            n->next = bucket[idx];
            bucket[idx] = n;

            this->currsize++;
        }

        void display()
        {
            cout<<"***********"<<endl;
            for(int i=0;i<this->maxsize;i++)
            {

                stu* temp = bucket[i];
                if(temp!=NULL)
                {
                    while(temp!=NULL)
                    {
                        cout<<temp->name<<"-> "<<temp->roll_no<<", ";
                        temp = temp->next;
                    }
                    cout<<endl;
                }
            }

            cout<<"***********"<<endl;
        }

        stu* stusearch(string name)
        {
            int idx = hashfunction(name);

            stu* temp = bucket[idx];

            while(temp!=NULL)
            {
                if(temp->name==name)
                {
                    return temp;
                }
                temp = temp->next;
            }

            return NULL;
        }

        void erase(string name)
        {
            int idx = hashfunction(name);

            stu* temp = bucket[idx];

            if(temp==NULL)
            {
                cout<<"Not Found!"<<endl;
                return;
            }

            if(temp->name==name)
            {
                stu* tobedeleted = bucket[idx];
                bucket[idx] = bucket[idx]->next;
                delete tobedeleted;
                return;
            }

            while(temp->next!=NULL)
            {
                if(temp->next->name==name)
                {
                    break;
                }
                temp = temp->next;
            }

            if(temp->next==NULL)
            {
                cout<<"Not Found!"<<endl;
                return;
            }

            stu* tobedeleted = temp->next;
            temp->next = temp->next->next;
            delete tobedeleted;
        }

        void retrieve(int num)
        {
            int j=0;
            vector<pair <int, string> > arr;
            for(int i=0;i<this->maxsize;i++)
            {
                stu* temp = bucket[i];
                if(temp!=NULL)
                {
                    while(temp!=NULL)
                    {
                        if(num==1)
                            arr.push_back(make_pair(temp->marks_m3, temp->name));
                        else if(num==2)
                            arr.push_back(make_pair(temp->marks_ps, temp->name));
                        else if(num==3)
                            arr.push_back(make_pair(temp->marks_de, temp->name));
                        else if(num==4)
                            arr.push_back(make_pair(temp->marks_ds, temp->name));
                        else if(num==5)
                            arr.push_back(make_pair(temp->marks_dm, temp->name));
                        temp = temp->next;
                    }
                }
            }
            sort(arr.begin(), arr.end());
            cout<<"\nMarks List\n\n";
            for(int i = 0; i < currsize; i++)
                cout<<arr[i].second<<"\t\t"<<arr[i].first<<endl;
            getch();
        }
};



/////////////////////////////////////////////////////////////////////////////////////
//          Class for Batch Node
/////////////////////////////////////////////////////////////////////////////////////
class node
{
public:
        int data;
        hashmap h;
        fstream f;
        node *left, *right;
        node(int val = 0)
        {
            data = val;
            left = right = NULL;
        }
};
/////////////////////////////////////////////////////////////////////////////////////
//      Class of Binary Search Tree for Batches
/////////////////////////////////////////////////////////////////////////////////////
class BST
{
public:
    node *root;

    BST()
    {
        root = NULL;
    }

    node* ins(node*, int);

    void traverse(node*);

    node* del(node*, int);

    node* sear(int);

    void addbatchno(int);

    void delbatchno(int);
}a;

node* BST::sear(int d)
{
   node *current = root;

   while(current->data != d)
    {
      if(current != NULL)
      {
         if(current->data > d)
            current = current->left;
         else
            current = current->right;

         if(current == NULL)
            return NULL;
      }
   }
   return current;
}

node* BST::ins(node *insroot, int val)
{
    if(insroot == NULL)
        insroot = new node(val);

    else if(insroot->data <= val)
        insroot->right = ins(insroot->right,val);

    else if(insroot->data > val)
        insroot->left = ins(insroot->left,val);

    return insroot;
}

void BST::traverse(node *rt)
{
    if(rt == NULL)
        return;

    traverse(rt->left);

    cout<<"Batch: "<<rt->data<<"\n";
    rt->h.display();
    cout<<endl;

    traverse(rt->right);

}

void BST::addbatchno(int val)
{
        fstream f1;
        f1.open("batches.txt", ios::app);
        f1<<val<<"\t";
        f1.close();
}

void BST::delbatchno(int val)
{
    int batchno;
    ifstream f1;
    ofstream f2;
    f2.open("temp.txt");
    f1.open("batches.txt");
    if(f1.is_open())
    {
        while(!f1.eof())
        {
            f1>>batchno;
            if(batchno != val)
                f2<<batchno<<"\t";
        }
    }
    f1.close();
    f2.close();
    remove("batches.txt");
    rename("temp.txt", "batches.txt");
}

node* BST::del(node *delroot, int val)
{
    if(delroot == NULL)
        return NULL;

    if(val == delroot->data)
    {
        if(delroot->right == NULL && delroot->left == NULL)
        {
            delete delroot;
            return NULL;
        }
        else if(delroot->left == NULL && delroot->right != NULL)
        {
            node* temp = delroot->right;
            delete delroot;
            return temp;
        }
        else if(delroot->right == NULL && delroot->left != NULL)
        {
            node* temp = delroot->left;
            delete delroot;
            return temp;
        }
        else
        {
            node* temp = delroot->right;
            while(temp->left != NULL)
                temp = temp->left;
            delroot->data = temp->data;
            delroot->right = del(delroot->right, temp->data);
            return delroot;
        }
    }
    else if(delroot->data > val)
        delroot->left = del(delroot->left, val);
    else
        delroot->right = del(delroot->right, val);
    return delroot;
}




/////////////////////////////////////////////////////////////////////////////////////
//          Administrator Functions
/////////////////////////////////////////////////////////////////////////////////////
void admin();
void batch();
void adins();
void adel();
void admodify();
void adsearch();
void admarks();
void adnoticeboard();
/////////////////////////////////////////////////////////////////////////////////////
//          Student Functions
/////////////////////////////////////////////////////////////////////////////////////
void student();
void stadd();
void stdel();
void stsearch();
void stnoticeboard();
/////////////////////////////////////////////////////////////////////////////////////
//          Registration and Login Functions
/////////////////////////////////////////////////////////////////////////////////////
void registration();
void login();
/////////////////////////////////////////////////////////////////////////////////////
//          File Handling Functions
/////////////////////////////////////////////////////////////////////////////////////
void restore();
void store();
/////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////
//          This Functions controls all the admin options
/////////////////////////////////////////////////////////////////////////////////////
void admin()
{
    int num;
    do
    {
        system("cls");
        cout<<"ADMINSTRATOR OPTIONS\n\n";
        cout<<"1. Insert & Delete batches\n";
        cout<<"2. Insert Student\n";
        cout<<"3. Delete Student\n";
        cout<<"4. View Batches & Students\n";
        cout<<"5. Search Student\n";
        cout<<"6. Edit Student Marks\n";
        cout<<"7. View Marks list\n";
        cout<<"8. Add Notice Board\n";
        cout<<"9. Exit\n";
        cout<<"Input:   "; cin>>num;
        if(num==1)
        {
            batch();
            getch();
        }
        else if(num==2)
        {
            adins();
            getch();
        }
        else if(num==3)
        {
            adel();
            getch();
        }
        else if(num==4)
        {
            cout<<endl;
            a.traverse(a.root);
            getch();
        }
        else if(num==5)
        {
            adsearch();
            getch();
        }
        else if(num==6)
        {
            admodify();
            getch();
        }
        else if(num==7)
        {
            admarks();
            getch();
        }
        else if(num==8)
        {
            adnoticeboard();
            getch();
        }
        else if(num==9)
        {
            return;
        }
        else
        {
            cout<<"\nWrong choice\n";
            getch();
        }
    }while(num!=9);
}
/////////////////////////////////////////////////////////////////////////////////////
//          This function controls insertion and deletion of batches
/////////////////////////////////////////////////////////////////////////////////////
void batch()
{
    int val, x;
    do
    {
        system("cls");
        cout<<"Batches of the Institute!!\n\n";
        cout<<"1. Insert Batch.\n2. Delete Batch.\n3. EXIT.\nInput:  "; cin>>x;
        switch(x)
        {
            case 1: cout<<"\nEnter what batch number to insert: "; cin>>val; a.root=a.ins(a.root,val); a.addbatchno(val); break;
            case 2: cout<<"\nEnter what batch number to delete: "; cin>>val; a.root=a.del(a.root,val); a.delbatchno(val); break;
            case 3: break;
            default: cout<<"\nWrong Choice"; getch();
        }
        cout<<endl;
    }while(x!=3);
}
/////////////////////////////////////////////////////////////////////////////////////
//          This function controls the insertion of student in batch
/////////////////////////////////////////////////////////////////////////////////////
void adins()
{
    system("cls");
    int b;
    string name;
    int roll_no, marks_m3, marks_ps, marks_de, marks_ds, marks_dm;
    node* temp = new node;

    cout<<"\nEnter which batch to insert student: "; cin>>b;
    temp = a.sear(b);

    if(temp==NULL)
    {
        cout<<"\nBatch not found!!";
        return;
    }
    else
    {
        cout<<"\nEnter Student name: "; cin>>name;
        cout<<"\nEnter Student roll no: "; cin>>roll_no;
        cout<<"\nEnter marks in M3: "; cin>>marks_m3;
        cout<<"\nEnter marks in PS: "; cin>>marks_ps;
        cout<<"\nEnter marks in DE: "; cin>>marks_de;
        cout<<"\nEnter marks in DS: "; cin>>marks_ds;
        cout<<"\nEnter marks in DM: "; cin>>marks_dm;
        temp->h.insert(name, roll_no, marks_m3, marks_ps, marks_de, marks_ds, marks_dm);
        cout<<"\nStudent Details have been inserted";
    }
}
/////////////////////////////////////////////////////////////////////////////////////
//      This function controls the deletion of students in a batch
/////////////////////////////////////////////////////////////////////////////////////
void adel()
{
    system("cls");
    int b;
    string name; int roll_no;
    node* temp;

    cout<<"\nEnter which batch to delete student: "; cin>>b;
    temp = a.sear(b);

    if(temp==NULL)
    {
        cout<<"\nBatch not found!!";
        return;
    }
    else
    {
        cout<<"\nEnter Student name to delete: "; cin>>name;
        temp->h.erase(name);
        cout<<"\nStudent record is deleted";
    }
}
/////////////////////////////////////////////////////////////////////////////////////
//      This functions controls the modification of student marks in a batch
/////////////////////////////////////////////////////////////////////////////////////
void admodify()
{
    system("cls");
    int b;
    string name; int roll_no;
    node* temp;

    cout<<"\nEnter which batch to modify student marks: "; cin>>b;
    temp = a.sear(b);

    if(temp==NULL)
    {
        cout<<"\nBatch not found!!";
        return;
    }
    else
    {
        cout<<"\nEnter Student name to modify marks: "; cin>>name;
        stu* temp2 = temp->h.stusearch(name);
        cout<<"\nEnter marks in M3: "; cin>>temp2->marks_m3;
        cout<<"\nEnter marks in PS: "; cin>>temp2->marks_ps;
        cout<<"\nEnter marks in DE: "; cin>>temp2->marks_de;
        cout<<"\nEnter marks in DS: "; cin>>temp2->marks_ds;
        cout<<"\nEnter marks in DM: "; cin>>temp2->marks_dm;
        cout<<"\nMarks have been modified";
    }
}
/////////////////////////////////////////////////////////////////////////////////////
//      This functions controls the searching of a student in a batch
/////////////////////////////////////////////////////////////////////////////////////
void adsearch()
{
    system("cls");
    int b;
    string name; int roll_no;
    node* temp;

    cout<<"\nEnter which batch to search student: "; cin>>b;
    temp = a.sear(b);

    if(temp==NULL)
    {
        cout<<"\nBatch not found!!";
        return;
    }
    else
    {
        cout<<"\nEnter Student name to search: "; cin>>name;
        stu* temp2 = temp->h.stusearch(name);
        cout<<"\nRoll No. is: "<<temp2->roll_no;
        cout<<"\nMarks in M3 is: "<<temp2->marks_m3;
        cout<<"\nMarks in PS is: "<<temp2->marks_ps;
        cout<<"\nMarks in DE is: "<<temp2->marks_de;
        cout<<"\nMarks in DS is: "<<temp2->marks_ds;
        cout<<"\nMarks in DM is: "<<temp2->marks_dm;
    }
}
/////////////////////////////////////////////////////////////////////////////////////
//      This functions controls the mark list of students in batch
/////////////////////////////////////////////////////////////////////////////////////
void admarks()
{
    system("cls");
    int b, num;
    string name; int roll_no;
    node* temp;

    cout<<"\nEnter which batch to search student: "; cin>>b;
    temp = a.sear(b);

    if(temp==NULL)
    {
        cout<<"\nBatch not found!!";
        return;
    }
    else
    {
        do
        {
            system("cls");
            cout<<"Select the subject\n\n";
            cout<<"1. M3\n";
            cout<<"2. PS\n";
            cout<<"3. DE\n";
            cout<<"4. DS\n";
            cout<<"5. DM\n";
            cout<<"6. Exit\n";
            cout<<"Input:   "; cin>>num;
            if(num>0 && num<6)
            {
                temp->h.retrieve(num);
            }
            else if(num==6)
            {
                return;
            }
            else
            {
                cout<<"\nWrong choice\n";
                getch();
            }
        }while(num!=6);
    }
}
/////////////////////////////////////////////////////////////////////////////////////
//      This function controls the notice board for admin
/////////////////////////////////////////////////////////////////////////////////////
void adnoticeboard()
{
    system("cls");
    string word; int n;
    ofstream f1;
    f1.open("temp.txt", ios::out);

    cout<<"Notice\n\n";
    cout<<"Enter the number of lines to insert: "; cin>>n;
    cout<<"\n\nEnter the information\n\n";
    n += 1;
    while(1)
    {
        getline(cin, word);
        f1<<word<<"\n";
        n--;
        if(n==0)
            break;
    }
    f1.close();
    remove("notice.txt");
    rename("temp.txt", "notice.txt");
}



/////////////////////////////////////////////////////////////////////////////////////
//      This function controls students options
/////////////////////////////////////////////////////////////////////////////////////
void student()
{
    int num;
    do
    {
        system("cls");
        cout<<"Student Options\n\n";
        cout<<"1. Add record\n";
        cout<<"2. Delete record\n";
        cout<<"3. Search & Display record\n";
        cout<<"4. View Notice Board\n";
        cout<<"5. Exit\n";
        cout<<"Input:   "; cin>>num;
        if(num==1)
        {
            stadd();
            getch();
        }
        else if(num==2)
        {
            stdel();
            getch();
        }
        else if(num==3)
        {
            stsearch();
            getch();
        }
        else if(num==4)
        {
            stnoticeboard();
            getch();
        }
        else if(num==5)
        {
            return;
        }
        else
        {
            cout<<"\nWrong choice\n";
            getch();
        }
    }while(num!=5);
}
/////////////////////////////////////////////////////////////////////////////////////
//      This function controls insertion of student in a batch
/////////////////////////////////////////////////////////////////////////////////////
void stadd()
{
    system("cls");
    int b;
    string name;
    int roll_no;
    node *temp;

    cout<<"\nEnter which batch to insert: "; cin>>b;
    temp = a.sear(b);

    if(temp==NULL)
    {
        cout<<"\nBatch not found!!";
        return;
    }
    else
    {
        cout<<"\nEnter Student name: "; cin>>name;
        cout<<"\nEnter Student roll no: "; cin>>roll_no;
        temp->h.insert(name, roll_no);
        cout<<"\nStudent record is created";
    }
}
/////////////////////////////////////////////////////////////////////////////////////
//      This function controls the deletion of student in a batch
/////////////////////////////////////////////////////////////////////////////////////
void stdel()
{
    system("cls");
    int b;
    string name; int roll_no;
    node* temp;

    cout<<"\nEnter batch number: "; cin>>b;
    temp = a.sear(b);

    if(temp==NULL)
    {
        cout<<"\nBatch not found!!";
        return;
    }
    else
    {
        cout<<"\nEnter your name to delete: "; cin>>name;
        temp->h.erase(name);
        cout<<"\nStudent record is deleted";
    }
}
/////////////////////////////////////////////////////////////////////////////////////
//      This function controls the searching of student in a batch
/////////////////////////////////////////////////////////////////////////////////////
void stsearch()
{
    system("cls");
    int b;
    string name; int roll_no;
    node* temp;

    cout<<"\nEnter batch number: "; cin>>b;
    temp = a.sear(b);

    if(temp==NULL)
    {
        cout<<"\nBatch not found!!";
        return;
    }
    else
    {
        cout<<"\nEnter your name: "; cin>>name;
        stu* temp2 = temp->h.stusearch(name);
        cout<<"\nYour roll No. is: "<<temp2->roll_no;
        cout<<"\nMarks in M3 is: "<<temp2->marks_m3;
        cout<<"\nMarks in PS is: "<<temp2->marks_ps;
        cout<<"\nMarks in DE is: "<<temp2->marks_de;
        cout<<"\nMarks in DS is: "<<temp2->marks_ds;
        cout<<"\nMarks in DM is: "<<temp2->marks_dm;
    }
}
/////////////////////////////////////////////////////////////////////////////////////
//      This function shows the notice board for student
/////////////////////////////////////////////////////////////////////////////////////
void stnoticeboard()
{
    system("cls");
    ifstream f1;
    f1.open("notice.txt", ios::in);
    if(!f1)
    {
        cout<<"No Notice";
        return;
    }
    else
    {
        string word;
        cout<<"Notice for Students!!\n\n";
        while(!f1.eof())
            {
                getline(f1, word);
                cout<<word<<endl;
            }
    }
    f1.close();
}



/////////////////////////////////////////////////////////////////////////////////////
//      This function controls the registration of student
/////////////////////////////////////////////////////////////////////////////////////
void registration()
{
    system("cls");
    cout<<"Registration....\n\n";
    cout<<"Create username: ";
    cin>>u1.user_n;
    cout<<"Create the password: ";
    cin>>u1.pass_n;

    ofstream fout;
    fout.open("userf.txt", ios::app);
    fout<<u1.user_n<<"\t"<<u1.pass_n<<"\n";
    fout.close();

    cout<<"\nSuccessfully registered!!!\n";
    cout<<"\nDo you want to Login? (Y/N): ";
    char a;
    cin>>a;
    if(a=='Y'||a=='y')
    {
        login();
    }
    else
        return;
}
/////////////////////////////////////////////////////////////////////////////////////
//      This function controls the login of student and admin
/////////////////////////////////////////////////////////////////////////////////////
void login()
{
    system("cls");
    char user_c[20], pass_c[20];
    int flag=0, log;

    cout<<"LOGIN...\n\n";
    cout<<"1. Login as administrator\n";
    cout<<"2. Login as student\n";
    cout<<"3. Exit\n";
    cout<<"Input:   "; cin>>log;
    if(log==3)
    {
        return;
    }
    if(log==1 || log==2)
    {
        cout<<"\nEnter username: ";
        cin>>user_c;
        cout<<"\nEnter password: ";
        cin>>pass_c;
    }

    if(log==1)
    {
        if((strcmp(user_c, "admin")==0)&&(strcmp(pass_c, "password")==0))
        {
            cout<<"\nLogged in as administrator\n";
            getch();
            admin();
        }
        else
        {
            cout<<"\nWrong username and password!";
            getch();
        }
    }

    if(log==2)
    {
        ifstream fin;
        fin.open("userf.txt");
        while(!fin.eof())
        {
            fin>>u1.user_n>>u1.pass_n;
            if((strcmp(u1.user_n,user_c)==0) && (strcmp(u1.pass_n,pass_c)==0))
            {
                cout<<"\nSuccessfully Logged In\n"; fin.close(); getch();
                flag=1;
                student();
                break;
            }
        }
        if(flag==0)
        {
            int x;
            cout<<"\nAccount not present";
            cout<<"\nPress -1 to Exit otherwise Register: ";
            cin>>x;
            if(x!=-1)
                registration();
        }
    }

}



/////////////////////////////////////////////////////////////////////////////////////
//      This function controls the reading of text file
/////////////////////////////////////////////////////////////////////////////////////
void restore()
{
    int batchno;
    ifstream f1;
    f1.open("batches.txt", ios::in);
    if(f1.is_open())
    {
        while(f1>>batchno)
        {
            a.root=a.ins(a.root, batchno);
            ifstream f2;
            f2.open(("batchno_" + to_string(batchno) + ".txt").c_str(), ios::in);

            if(f2.is_open())
            {
                string name; int roll_no, marks_m3, marks_ps, marks_de, marks_ds, marks_dm;

                f2.ignore(numeric_limits<streamsize>::max(), '\n');
                f2.ignore(numeric_limits<streamsize>::max(), '\n');

                while(f2>>name>>roll_no>>marks_m3>>marks_ps>>marks_de>>marks_ds>>marks_dm)
                {
                    node* temp = new node;
                    temp = a.sear(batchno);
                    temp->h.insert(name, roll_no, marks_m3, marks_ps, marks_de, marks_ds, marks_dm);

                }
            }
            f2.close();
        }
    }
    f1.close();
}
/////////////////////////////////////////////////////////////////////////////////////
//      This function controls the writing of text file
/////////////////////////////////////////////////////////////////////////////////////
void store()
{
    stack<node*> s;
    node *curr = a.root;

    while (curr != NULL || s.empty() == false)
    {
        while (curr !=  NULL)
        {
            s.push(curr);
            curr = curr->left;
        }

        curr = s.top();
        s.pop();

        ofstream f1;
        f1.open("temp.txt");
        f1<<"Name\tRoll No.\tM3\tPS\tDE\tDS\tDM\n\n";

        for(int i = 0; i < curr->h.maxsize; i++)
        {
            stu* temp = curr->h.bucket[i];
            if(temp != NULL)
            {
                while(temp != NULL)
                {
                    f1<<temp->name<<"\t"<<temp->roll_no<<"\t"<<temp->marks_m3<<"\t"<<temp->marks_ps<<"\t"<<temp->marks_de<<"\t"<<temp->marks_ds<<"\t"<<temp->marks_dm<<"\n";
                    temp = temp->next;
                }
            }
        }

        f1.close();
        remove(("batchno_" + to_string(curr->data) + ".txt").c_str());
        rename("temp.txt", ("batchno_" + to_string(curr->data) + ".txt").c_str());
        curr = curr->right;
    }
}



/////////////////////////////////////////////////////////////////////////////////////
//      MAIN Function controlling main menu
/////////////////////////////////////////////////////////////////////////////////////
int main()
{
    restore();
    int n;
    do
    {
        system("cls");
        cout<<"WELCOME\n\n";
        cout<<"1. Registration for Student\n";
        cout<<"2. Login for Admin and Student\n";
        cout<<"3. Exit\n";
        cout<<"Input:   "; cin>>n;

        if(n==1)
        {
            registration();
        }
        else if(n==2)
        {
            login();
        }
        else if(n==3)
        {
        }
        else
        {
        cout<<"\nIncorrect Input\n";
        cout<<"Please choose again";
        getch();
        }
    }while(n!=3);
    store();
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////
