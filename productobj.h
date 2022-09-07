#include<iostream>
#include<iomanip>
#include<fstream>
#include<string.h>
using namespace std;
class product {
    protected:
    unsigned long long int pid;
    char pname[256];
    float price,qty,disc,disc_amt,gst;
    char tqty[12];
    private:float sqty;

    public:void read();
    product()
    {
        pid=0;
        strcpy(pname,"");
        strcpy(tqty,"NONE");
        price=0;
        qty=0;
        sqty=0;
        disc=0;
        disc_amt=0;
        gst=0;
    }
    ~product()
    {

    }
           void display();
           void display_head();
           void display_tail();
           void getdata();
           int compare(unsigned long long int);
           unsigned long long int getpid();
           float disc_cal(float,float);
           float gettaxed_amt();
           float getfinal_amt(float);
           void writetodb(product p);
           void readfromdb();
           void removefromdb(product p[],int);
           void updatetodb(product p[],int);
           void modifystock(unsigned long long int);
           bool addtostock(unsigned long long int,float);
           bool removefromstock(unsigned long long int,float);
           void editstock(int,float);
           bool compareqty(float);
           float getprice();
           void searchdb();
           product getobjfromdb(unsigned long long int,float);
           float getgst();
           void copystr(char[],char[]);
           unsigned long long int copypid();
           float getdisc();
};
void product::read()
{
    int ch;
    cout<<"enter product name ";
    cin.getline(pname,256);
    cout<<"1.killogram"<<endl;
    cout<<"2.litre"<<endl;
    cout<<"3.packet"<<endl;
    cout<<"choose quantity type ";
    cin>>ch;
        switch(ch)
        {
            case 1:cout<<"enter base quantity in kg" ;
                    cin>>qty;
                    strcpy(tqty,"KILLOGRAM");
                    cout<<"enter available stock in kg ";
                    cin>>sqty;
                    break;
            case 2:cout<<"enter quantity in litre ";
                    cin>>qty;
                    strcpy(tqty,"LITRE");
                    cout<<"enter available stock in litre ";
                    cin>>sqty;
                    break;
            case 3:cout<<"enter qyantity in packet/piece ";
                    cin>>qty;
                    strcpy(tqty,"PIECE");
                    cout<<"enter available stock in number of packets/pieces ";
                    cin>>sqty;
                    break;
            default:cout<<"invalid choice"<<endl;
        }
        cout<<"enter price per kg/l/piece ";
        cin>>price;
        cout<<"enter discount in percentage ";
        cin>>disc;
        cout<<"enter GST in percentage ";
        cin>>gst;
    cin.ignore();
}
void product::display()
{
    cout<<"|"<<setw(5)<<pid<<"|"<<setw(50)<<left<<pname<<"|"<<setw(15)<<qty<<"|"<<setw(14)<<tqty<<"|"
    <<setw(15)<<price<<"|"<<setw(7)<<gst<<"|"<<setw(12)<<disc<<"|"<<setw(15)<<disc_amt<<"|"<<setw(15)<<sqty<<"|"<<endl;
}

void product::display_head()
{
    for(int j=0;j<158;j++)
    cout<<"=";
    cout<<endl;
    cout<<"|"<<setw(5)<<left<<"pid"<<"|"<<setw(50)<<left<<"product_name"<<"|"<<setw(15)<<"base quantity"<<"|"<<setw(14)<<"quantity_type"<<"|"<<setw(15)<<"price"<<"|"
    <<setw(7)<<"GST(%)"<<"|"<<setw(12)<<"dicount(%)"<<"|"<<setw(15)<<"discounted_amt"<<"|"<<setw(15)<<"available_stock"<<"|"<<endl;
    for(int j=0;j<158;j++)
    cout<<"=";
    cout<<endl;
}

void product::display_tail()
{
    for(int j=0;j<158;j++)
    cout<<"=";
    cout<<endl;
}
void product::getdata()
{
    pid=getpid();
    read();
    disc_amt=disc_cal(disc,price);
}


int product::compare(unsigned long long int id)
{
    if(pid==id)
    return 1;
    else
    return 0;
}


unsigned long long int product::getpid()
{
    ifstream file;
    unsigned long long int counter=0;
    product p;
    file.open("db/storage.bin",ios_base::in | ios::binary);
    if(file)
    {
    while(!file.eof())
    {
    file.read(reinterpret_cast<char*>(&p),sizeof(product));
    if(p.compare(0))
    break;
    counter=p.pid;
    }
    file.close();
    counter+=1;
    }
    else
    counter=1;
    return counter;
}


float product::disc_cal(float disc,float price)
{
    float temp,da;
    temp=price*(disc/100);
    da=price-temp;
    return da;
}


float product::gettaxed_amt()
{
    float tax_amt;
    if(disc>0)
    return disc_amt;
    else
    {
        tax_amt=price+(price*gst)/100;
        return tax_amt;
    }
}


float product::getfinal_amt(float amt)
{
    float finalamt=0,taxed_amt;
    taxed_amt=gettaxed_amt();
    finalamt=(taxed_amt*amt)/qty;
    return finalamt;
}

void product::writetodb(product p)
{
    ofstream file;
    p.getdata();
    file.open("db/storage.bin",ios::binary | ios_base::app);
    if(file)
    {
    file.write(reinterpret_cast<char*>(&p),sizeof(product));
    file.close();
    }
    else
    {
        file.close();
        file.open("db/storage.bin",ios::binary | ios_base::out);
        file.write(reinterpret_cast<char*>(&p),sizeof(product));
        file.close();
    }
}
//image of product database before and after a new item is added 2 screenshots

void product::readfromdb()
{
    product p[1000];
    ifstream file;
    display_head();
    int i=0;
    file.open("db/storage.bin",ios::binary | ios_base::in);
    if(file)
    {
    while(!file.eof())
    {
        file.read(reinterpret_cast<char*>(&p[i]),sizeof(product));
        i++;
    }
    file.close();
    i=0;
    while(p[i].compare(0)==0)
    {
        if(p[i].compare(0)==0)
        p[i].display();
        i++;
    }
    }
    display_tail();
}
//image of product database
void product::removefromdb(product p[],int id)
{
    ifstream file;
    ofstream file2;
    file.open("db/storage.bin",ios::binary | ios_base::in);
    int i=0;
    if(file)
    {
    while(!file.eof())
    {
        file.read(reinterpret_cast<char*>(&p[i]),sizeof(product));
        i++;
    }
    file.close();
    int j=0;
    file2.open("db/storage.bin",ios::binary | ios_base::out);
    while(p[j].compare(0)==0)
    {
        if(p[j].compare(id)!=1)
        {
        file2.write(reinterpret_cast<char*>(&p[j]),sizeof(product));
        }
        j++;
    }
    file2.close();
    }
    else{
        cout<<"PRODUCT DETAILS FILE NOT FOUND"<<endl;
        file.close();
    }
}
//image of product database before and after a item is removed 2 screenshots

void product::updatetodb(product p[10000],int id)
{
    fstream file;
    int i=0;
    file.open("db/storage.bin",ios::binary | ios_base::in);
    if(file)
    {
    while(!file.eof())
    {
        file.read(reinterpret_cast<char*>(&p[i]),sizeof(product));
        i++;
    }
    file.close();
    i=0;
    file.open("db/storage.bin",ios::binary | ios_base::out);
    while(p[i].compare(0)==0)
    {
        if(p[i].compare(id)==1)
        p[i].read();
        file.write(reinterpret_cast<char*>(&p[i]),sizeof(product));
        i++;
    }
    file.close();
    }
    else
    {
        cout<<"PRODUCT DETAILS FILE NOT FOUND!!!"<<endl;
        file.close();
    }
}//image of item details  update process here image of product database before and after update 2 screenshots

void product::modifystock(unsigned long long int id)
{
    int ch;
    float rqty;
    cout<<"1.add to stock"<<endl;
    cout<<"2.remove from stock"<<endl;
    cout<<"enter choice ";
    cin>>ch;
    switch(ch)
    {
        case 1: cout<<"enter quantity ";
                cin>>rqty;
                if(addtostock(id,rqty))
                cout<<"item added to stock"<<endl;
                else
                cout<<"nothing added make sure pid is correct"<<endl;
                break;
        case 2:cout<<"enter quantity ";
                cin>>rqty;
                if(removefromstock(id,rqty)==1)
                cout<<"item stock removed"<<endl;
                else
                cout<<"nothing removed make sure pid is correct and quantity is less than stock"<<endl;
                break;
        default:cout<<"invalid choice ";
    }
}
//image of product databse before and after item stock is added and before and after item stock is removed 4 screenshots

bool product::addtostock(unsigned long long int id,float rqty)
{
    product p[1000];
    fstream file;
    int i=0;
    int flag=0;
    file.open("db/storage.bin",ios::binary | ios_base::in);
    if(file)
    {
    while(!file.eof())
    {
        file.read(reinterpret_cast<char*>(&p[i]),sizeof(product));
        i++;
    }
    file.close();
    i=0;
    while(p[i].compare(0)==0)
    {
        if(p[i].compare(id)==1)
        {
        p[i].editstock(1,rqty);
        flag=1;
        break;
        }
        i++;
    }
    file.open("db/storage.bin",ios::binary | ios_base::out);
    i=0;
    while(p[i].compare(0)==0)
    {
    file.write(reinterpret_cast<char*>(&p[i]),sizeof(product));
    i++;
    }
    }
    else cout<<"PRODUCT DETAILS FILE NOT FOUND"<<endl;
    file.close();
        return flag;
}

bool product::removefromstock(unsigned long long int id,float rqty)
{
    product p[1000];
    fstream file;
    int i=0;
    int flag=0;
    file.open("db/storage.bin",ios::binary | ios_base::in);
    if(file)
    {
    while(!file.eof())
    {
        file.read(reinterpret_cast<char*>(&p[i]),sizeof(product));
        i++;
    }
    file.close();
    i=0;
    while(p[i].compare(0)==0)
    {
        if(p[i].compare(id)==1)
        {
        if(p[i].compareqty(rqty))
        {
            p[i].editstock(0,rqty);
            flag=1;
            break;
        }
        }
        i++;
    }
    file.open("db/storage.bin",ios::binary | ios_base::out);
    i=0;
    while(p[i].compare(0)==0)
    {
    file.write(reinterpret_cast<char*>(&p[i]),sizeof(product));
    i++;
    }
    }
    else cout<<"THE PRODUCT DETAILS FILE NOT FOUND"<<endl;
    file.close();
        return flag;
}

void product::editstock(int signal,float rqty)
{
    if(signal==1)
    sqty+=rqty;
    else
    sqty-=rqty;
}
bool product::compareqty(float rqty)
{
    if(sqty>=rqty)
    return 1;
    else
    return 0;
}

float product::getprice()
{
    return price;
}

void product::searchdb()
{
    ifstream file;
    product p[1000];
    int ch;
    char sname[256];
    unsigned long long int sid;
    cout<<"1.use pid"<<endl;
    cout<<"2.use product name"<<endl;
    cout<<"enter choice ";
    cin>>ch;
    int i=0;
    file.open("db/storage.bin",ios::binary | ios_base::in);
    if(file)
    {
    switch(ch)
    {
        case 1:cout<<"enter pid ";
            cin>>sid;
            display_head();
            while(!file.eof())
            {
                file.read(reinterpret_cast<char*>(&p[i]),sizeof(product));
                if(p[i].pid==sid)
                p[i].display();
                i++;
            }
            break;
        case 2:cout<<"enter product name ";
            cin.ignore();
            cin.getline(sname,256);
            display_head();
            while(!file.eof())
            {
                file.read(reinterpret_cast<char*>(&p[i]),sizeof(product));
                if(strcmpi(sname,p[i].pname)==0)
                p[i].display();
                i++;
            }
            break;
        default:cout<<"invalid choice "<<endl;
    }
    display_tail();
    }
    else
        cout<<"THE PRODUCT DETAILS FILE NOT FOUND"<<endl;
    file.close();
}

product product::getobjfromdb(unsigned long long int id,float rqty)
{
    fstream file;
    product p[1000];
    product p1;
    int i=0;
    file.open("db/storage.bin",ios::binary | ios_base::in);
    if(file)
    {
    while(!file.eof())
    {
    file.read(reinterpret_cast<char*>(&p[i]),sizeof(product));
    if(p[i].pid==id && p[i].compareqty(rqty)==1)
    {
        p1=p[i];
    }
    i++;
    }
    file.close();
    file.open("db/storage.bin",ios::binary | ios_base::out);
    i=0;
    while(p[i].compare(0)==0)
    {
        file.write(reinterpret_cast<char*>(&p[i]),sizeof(product));
        i++;
    }
    }
    else cout<<"PRODUCT DETAILS FILE NOT FOUND"<<endl;
    file.close();
    return p1;
}

float product::getgst()
{
    return gst;
}

void product::copystr(char name[256],char btqty[12])
{
    strcpy(name,pname);
    strcpy(btqty,tqty);
}

unsigned long long int product::copypid()
{
    return pid;
}

float product::getdisc()
{
    return disc;
}
