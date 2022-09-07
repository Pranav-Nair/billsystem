#include<iostream>
#include<iomanip>
#include<string.h>
#include<fstream>
#include<ctime>
using namespace std;
class customer
{
    protected:
    unsigned int refno;
    unsigned int cid;
    char name[256];
    unsigned long long int pno;
    char filename[50];
    char date[100];
    private:
    char pay_type[100];
    char upi_id[100];
    unsigned long long int card_no;
    public:customer()
    {
        refno=0;
        cid=0;
        pno=0;
        card_no=0;
        strcpy(name,"");
        strcpy(filename,"bills/");
        strcpy(pay_type,"NONE");
        strcpy(upi_id,"N/A");
        strcpy(date,"");
    }
    ~customer()
    {

    }
        void read();
        void display();
        void display_head();
        void display_tail();
        int compare(unsigned int);
        void getdata();
        void readpay();
        int checkincdb(unsigned long long int);
        int comparepno(unsigned long long int);
        void getfromcdb(int);
        unsigned int getrefno();
        unsigned int getcid();
        void writetocdb(customer);
        void readfromcdb();
        void deletecdb();
        void createbill();
        void getdatetime(char[]);
        void searchincdb();
        void copyfilename(char[]);
        unsigned int copyrefno();
};

void customer::read()
{
    cin.ignore();
    cout<<"enter name ";
    cin.getline(name,50);
}

void customer::readpay()
{
    int ch;
    cout<<"choose payment method "<<endl;
    cout<<"1.UPI"<<endl;
    cout<<"2.credit card"<<endl;
    cout<<"3.debit card"<<endl;
    cout<<"4.cash"<<endl;
    cout<<"enter choice ";
    cin>>ch;
    switch(ch)
    {
        case 1:strcpy(pay_type,"UPI");
                cout<<"enter UPI ID ";
                cin.ignore();
                cin.getline(upi_id,100);
                createbill();
            break;
        case 2:strcpy(pay_type,"CREDIT CARD");
                cout<<"enter card no ";
                cin>>card_no;
                createbill();
            break;
        case 3:strcpy(pay_type,"DEBIT CARD");
                cout<<"enter card no ";
                cin>>card_no;
                createbill();
            break;
        case 4:strcpy(pay_type,"CASH");
                createbill();
            break;
        default:cout<<"invalid choice ";
    }
}

void customer::getdata()
{
    int ch;
    cout<<"enter phone number ";
    cin>>pno;
    if(checkincdb(pno)==1)
    {
        cout<<"1.use existing user data"<<endl;
        cout<<"2.create new user"<<endl;
        cout<<"enter choice ";
        cin>>ch;
        switch(ch)
        {
            case 1:getfromcdb(pno);
                refno=getrefno();
//                createbill();
                getdatetime(date);
                break;
            case 2:read();
                refno=getrefno();
                cid=getcid();
//                createbill();
                getdatetime(date);
                break;
            default:cout<<"invalid choice"<<endl;
        }
    }
    else
    {
    refno=getrefno();
    cid=getcid();
    read();
//    createbill();
    getdatetime(date);
    }
}

void customer::getdatetime(char date[100])
{
    time_t curr_time;
    tm* td;
    time(&curr_time);
    td=localtime(&curr_time);
    strftime(date,100,"%B %d %Y",td);
}

unsigned int customer::getrefno()
{
    unsigned int counter=0;
    customer c;
    ifstream file;
    file.open("db/customerdb.bin",ios::binary | ios_base::in);
    if(file)
    {
        while(!file.eof())
        {
            file.read(reinterpret_cast<char*>(&c),sizeof(customer));
            counter=c.refno;
        }
        file.close();
        counter+=1;
    }
    else
    {
        file.close();
        counter=1;
    }
        return counter;
}

unsigned int customer::getcid()
{
    unsigned int counter=0;
    customer c;
    ifstream file;
    file.open("db/customerdb.bin",ios::binary | ios_base::in);
    if(file)
    {
        while(!file.eof())
        {
            file.read(reinterpret_cast<char*>(&c),sizeof(customer));
            counter=c.cid;
        }
        file.close();
        counter+=1;
    }
    else
    {
        file.close();
        counter=1;
    }
        return counter;
}


void customer::display()
{
    cout<<"|"<<setw(10)<<refno<<"|"<<setw(10)<<cid<<"|"<<setw(50)<<name<<"|"<<setw(14)<<left<<pno<<"|"
    <<setw(12)<<pay_type<<"|"<<setw(25)<<upi_id<<"|"<<setw(30)<<card_no<<"|"<<setw(25)<<date<<"|"<<endl;
}

void customer::display_head()
{
    for(int i=0;i<185;i++)
    cout<<"=";
    cout<<endl;
    cout<<"|"<<setw(10)<<left<<"ref_no"<<"|"<<setw(10)<<"customerID"<<"|"<<setw(50)<<"customer-name"<<"|"<<setw(14)<<"phone_no"<<"|"
    <<setw(12)<<"payment_type"<<"|"<<setw(25)<<"UPI_ID"<<"|"<<setw(30)<<"CARD NO"<<"|"<<setw(25)<<"date of transaction"<<"|"<<endl;
    for(int i=0;i<185;i++)
    cout<<"=";
    cout<<endl;
}

void customer::display_tail()
{
    for(int i=0;i<185;i++)
    cout<<"=";
    cout<<endl;
}

int customer::compare(unsigned int id)
{
    if(id==refno)
    return 1;
    else
    return 0;
}

int customer::comparepno(unsigned long long int no)
{
    if(no==pno)
    return 1;
    else
    return 0;
}

void customer::createbill()
{
    string tmp=to_string(refno);
    char const *temp2=tmp.c_str();
    ofstream file;
    strcat(filename,temp2);
    cout<<filename<<endl;
    file.open(filename,ios::binary | ios_base::out);
    file.close();
}

void customer::writetocdb(customer c)
{
    ofstream file;
    file.open("db/customerdb.bin",ios::binary | ios_base::app);
    if(file)
    {
        file.write(reinterpret_cast<char*>(&c),sizeof(customer));
    }
    else
    {
        file.close();
        file.open("db/customerdb.bin",ios::binary | ios_base::out);
        file.write(reinterpret_cast<char*>(&c),sizeof(customer));
    }
        file.close();
}

void customer::readfromcdb()
{
    ifstream file;
    customer c[1000];
    file.open("db/customerdb.bin",ios::binary | ios_base::in);
    if(file)
    {
    display_head();
    int i=0;
    while(!file.eof())
    {
        file.read(reinterpret_cast<char*>(&c[i]),sizeof(customer));
        if(c[i].compare(0)==0)
        c[i].display();
        i++;
    }
    file.close();
    display_tail();
    }
    else
    {
        file.close();
        cout<<"CUSTOMER DETAILS FILE NOT FOUND"<<endl;
    }
}
//image of cusomer database
int customer::checkincdb(unsigned long long int no)
{
    int val;
    customer c[1000];
    int flag=0;
    ifstream file;
    file.open("db/customerdb.bin",ios::binary | ios_base::in);
    int i=0;
    if(file)
    {

    while(!file.eof())
    {
        file.read(reinterpret_cast<char*>(&c[i]),sizeof(customer));
        if(c[i].comparepno(no)==1)
        {
            flag+=1;
            val=i;
        }
        i++;
    }
    }
    file.close();
    if(flag>0)
    {
    display_head();
    c[val].display();
    display_tail();
    return 1;
    }
    else
    return 0;
}
void customer::getfromcdb(int no)
{
    customer c[1000];
    ifstream file;
    file.open("db/customerdb.bin",ios::binary | ios_base::in);
    if(file)
    {
    int i=0;
    while(!file.eof())
    {
        file.read(reinterpret_cast<char*>(&c[i]),sizeof(customer));
        if(c[i].comparepno(no))
        {
            cid=c[i].cid;
            strcpy(name,c[i].name);
            pno=c[i].pno;
        }
        i++;
    }
    }
    file.close();

}

void customer::deletecdb()
{
    ifstream file;
    customer c[1000];
    int ch=1;
    int i=0;
    cout<<"are you sure you want to delete the database? "<<endl;
    cout<<"1.yes"<<endl;
    cout<<"2.no"<<endl;
    cout<<"enter choice ";
    cin>>ch;
    switch(ch)
    {
        case 1:file.open("db/customerdb.bin",ios::binary | ios_base::in);
            while(!file.eof())
            {
                file.read(reinterpret_cast<char*>(&c[i]),sizeof(customer));
                remove(c[i].filename);
                strcat(c[i].filename,".txt");
                remove(c[i].filename);
                i++;
            }
            file.close();
            remove("db/customerdb.bin");
            break;
        case 2:cout<<"all records are safe "<<endl;
            break;
        default:cout<<"invalid choice "<<endl;
    }
}
//image of customer database after all entries are removed
void customer::searchincdb()
{
    ifstream file;
    customer c[1000];
    int ch;
    unsigned long long int num;
    char sdate[100];
    file.open("db/customerdb.bin",ios::binary | ios_base::in);
    if(file)
    {
    cout<<"1.use ref_no."<<endl;
    cout<<"2.use customer ID"<<endl;
    cout<<"3.use phone no."<<endl;
    cout<<"4.use date"<<endl;
    cout<<"choose a option ";
    cin>>ch;
    int i=0;
    switch(ch)
    {
        case 1:cout<<"enter ref_no ";
            cin>>num;
            display_head();
            while(!file.eof())
            {
                file.read(reinterpret_cast<char*>(&c[i]),sizeof(customer));
                if(c[i].refno==num)
                c[i].display();
                i++;
            }
            break;
        case 2:cout<<"enter customer ID  ";
            cin>>num;
            display_head();
            while(!file.eof())
            {
                file.read(reinterpret_cast<char*>(&c[i]),sizeof(customer));
                if(c[i].cid==num)
                c[i].display();
                i++;
            }
            break;
        case 3:cout<<"enter Phone no.   ";
            cin>>num;
            display_head();
            while(!file.eof())
            {
                file.read(reinterpret_cast<char*>(&c[i]),sizeof(customer));
                if(c[i].pno==num)
                c[i].display();
                i++;
            }
            break;
        case 4:cout<<"enter date in 'monthname dd yyyy' format ";
        cin.ignore();
        cin.getline(sdate,50);
        display_head();
        while(!file.eof())
        {
            file.read(reinterpret_cast<char*>(&c[i]),sizeof(customer));
            if(strcmpi(sdate,c[i].date)==0)
            c[i].display();
            i++;
        }
        break;
        default:cout<<"invalid option"<<endl;
    }
    display_tail();
    }
    else cout<<"CUSTOMER DETAILS FILE NOT FOUND"<<endl;
    file.close();
}
//image of customer details after using each option 4 screenshots total
void customer::copyfilename(char fname[50])
{
    strcpy(fname,filename);
}


unsigned int customer::copyrefno()
{
    return refno;
}
