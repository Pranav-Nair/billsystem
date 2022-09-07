#include <iostream>
#include<iomanip>
#include<string.h>
#include "customerobj.h"
#include "productobj.h"
#include "shopinfo.h"
using namespace std;
class bill: protected customer,protected product,protected shop
{
    float taxed_amt;
    float bqty;
    public:void billdisplay();
        bill()
        {
            bqty=0;
            taxed_amt=0;
        }
        ~bill()
        {

        }
void readfrombill(char id[50]);
void billdisplay_head();
void billdisplay_tail(float);
void writetobill(bill,char[]);
void billgetdata(unsigned long long int);
bool comparebid(unsigned long long int);
unsigned long long int getbid();
float getqty();
float gettaxed_amt();
void writetxtfile(bill[],char[],int,float,customer);
};
void bill::billdisplay()
{
    cout<<"|"<<left<<setw(8)<<pid<<"|"<<setw(50)<<pname<<"|"<<setw(9)<<bqty<<"|"<<setw(20)<<tqty<<"|"<<setw(9)<<price<<"|"<<setw(12)<<disc<<"|"<<setw(6)<<gst<<"|"<<setw(15)<<taxed_amt<<"|"<<endl;
}

void bill::billdisplay_head()
{
    for(int i=0;i<138;i++)
    cout<<"=";
    cout<<endl;
    cout<<"|"<<left<<setw(8)<<"bid"<<"|"<<setw(50)<<"item_name"<<"|"<<setw(9)<<"quantity"<<"|"<<setw(20)<<"quantity type"<<"|"<<setw(9)<<"price"<<"|"<<setw(12)<<"discount(%)"<<"|"
    <<setw(6)<<"GST(%)"<<"|"<<setw(15)<<"Taxed_amt"<<"|"<<endl;
    for(int i=0;i<138;i++)
    cout<<"=";
    cout<<endl;
}

void bill::billdisplay_tail(float num)
{
    for(int i=0;i<138;i++)
    cout<<"=";
    cout<<endl;
    if(num!=0)
    {
        cout<<"|"<<setw(10)<<left<<"GRAND TOTAL "<<"|"<<setw(123)<<num<<"|"<<endl;
        for(int i=0;i<138;i++)
        cout<<"=";
    }
    cout<<endl;
}

void bill::readfrombill(char id[50])
{
    float total=0;
    bill b[1000];
    char afilename[50];
    strcpy(afilename,"bills/");
    strcat(afilename,id);
    ifstream file;
    file.open(afilename,ios::binary | ios_base::in);
    if(file)
    {
        billdisplay_head();
        int i=0;
        while(!file.eof())
        {
            file.read(reinterpret_cast<char*>(&b[i]),sizeof(bill));
            if(b[i].pid!=0)
            {
            b[i].billdisplay();
            total+=b[i].taxed_amt;
            }
            i++;
        }
        file.close();
        billdisplay_tail(total);
    }
    else
        cout<<"ENTERED REF_NO IS NOT CORRECT!!!";
}//image of a bill f any ref_no and one where ref_no is invalid 2 screenshots
void bill::writetobill(bill b,char argfilename[50])
{
    ofstream file;
    if(b.taxed_amt!=0)
    {
    file.open(argfilename,ios::binary | ios_base::app);
    file.write(reinterpret_cast<char*>(&b),sizeof(bill));
    file.close();
    }
}

void bill::billgetdata(unsigned long long int id)
{
    product p;
    cout<<"enter quantity ";
    cin>>bqty;
    p=p.getobjfromdb(id,bqty);
    pid=p.copypid();
    price=p.getprice();
    p.copystr(pname,tqty);
    gst=p.getgst();
    taxed_amt=p.getfinal_amt(bqty);
    disc=p.getdisc();
    if(price==0)
        cout<<"not enough stock to complete purchase"<<endl;
}

bool bill::comparebid(unsigned long long int id)
{
    if(pid==id)
    return 1;
    else
    return 0;
}

unsigned long long int bill::getbid()
{
    return pid;
}

float bill::getqty()
{
    return bqty;
}

float bill::gettaxed_amt()
{
    return taxed_amt;
}

void bill::writetxtfile(bill b[],char filename[50],int m,float total,customer c)
{
    ofstream file;
    shop s=s.readshopobj();
    s.copyfromobj(sname,aline1,city,state);
    pin=s.getpin();
    spno=s.getpno();
    refno=c.copyrefno();
    strcat(filename,".txt");
    file.open(filename,ios_base::out);
    file<<setw(40)<<" "<<sname<<endl;
    file<<endl;
    file<<setw(30)<<" "<<aline1<<","<<city<<","<<pin<<","<<state<<"."<<endl;
    file<<setw(35)<<" "<<"phone no. "<<spno<<endl;
    file<<"Bill no. "<<refno<<endl;
    for(int i=0;i<138;i++)
    file<<"=";
    file<<endl;
    file<<"|"<<left<<setw(8)<<"Sno."<<"|"<<setw(50)<<"item_name"<<"|"<<setw(9)<<"quantity"<<"|"<<setw(20)<<"quantity type"<<"|"<<setw(9)<<"price"<<"|"<<setw(12)<<"discount(%)"<<"|"
    <<setw(6)<<"GST(%)"<<"|"<<setw(15)<<"Taxed_amt"<<"|"<<endl;
    for(int i=0;i<138;i++)
    file<<"=";
    file<<endl;
    for(int i=0;i<m;i++)
    {
        if(b[i].comparebid(0)==0)
        file<<"|"<<left<<setw(8)<<i+1<<"|"<<setw(50)<<b[i].pname<<"|"<<setw(9)<<b[i].bqty<<"|"<<setw(20)<<b[i].tqty<<"|"<<setw(9)<<b[i].price<<"|"
        <<setw(12)<<b[i].disc<<"|"<<setw(6)<<b[i].gst<<"|"<<setw(15)<<b[i].taxed_amt<<"|"<<endl;
    }
    for(int i=0;i<138;i++)
    file<<"=";
    file<<endl;
    if(total!=0)
    {
        file<<"|"<<setw(10)<<left<<"GRAND TOTAL "<<"|"<<setw(123)<<total<<"|"<<endl;
        for(int i=0;i<138;i++)
        file<<"=";
    }
    file<<endl;
    file.close();

}
//image of bill from text file
