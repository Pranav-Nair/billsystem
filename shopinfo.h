#include<iostream>
#include<iomanip>
#include<string.h>
using namespace std;
class shop
{
    protected:
        char sname[50];
        char aline1[100];
        char city[50];
        char state[50];
        unsigned int pin;
        unsigned long long int spno;
public:shop()
{
    strcpy(sname,"");
    strcpy(aline1,"");
    strcpy(city,"");
    strcpy(state,"");
    pin=0;
    spno=0;
}
~shop()
{

}
void shop_getdata();
void writeshopdata(shop);
void readshopinfo();
shop readshopobj();
void copyfromobj(char[],char[],char[],char[]);
unsigned int getpin();
unsigned long long int getpno();
};

void shop::shop_getdata()
{
    cout<<"enter shop name ";
    cin.getline(sname,50);
    cout<<"enter phone number ";
    cin>>spno;
    cin.ignore();
    cout<<"enter street and area name ";
    cin.getline(aline1,100);
    cout<<"enter city name ";
    cin.getline(city,50);
    cout<<"enter a pin ";
    cin>>pin;
    cin.ignore();
    cout<<"enter state name ";
    cin.getline(state,50);

}

void shop::writeshopdata(shop s)
{
    ofstream file;
    file.open("db/shopinfo.bin",ios::binary | ios_base::out);
    file.write(reinterpret_cast<char*>(&s),sizeof(shop));
    file.close();
}
//image of shop information being inputed
void shop::readshopinfo()
{
    shop s=s.readshopobj();
    cout<<s.sname<<endl;
    cout<<s.aline1<<","<<s.city<<","<<s.pin<<","<<s.state<<"."<<endl;
    cout<<"phone no. "<<s.spno<<endl;
}
//image of shop information
shop shop::readshopobj()
{
    shop s;
    ifstream file;
    file.open("db/shopinfo.bin",ios::binary | ios_base::in);
    if(file)
        file.read(reinterpret_cast<char*>(&s),sizeof(shop));
    file.close();
    return s;
}

void shop::copyfromobj(char aname[50],char argline1[100],char acity[50],char astate[50])
{
    strcpy(aname,sname);
    strcpy(argline1,aline1);
    strcpy(acity,city);
    strcpy(astate,state);
}

unsigned int shop::getpin()
{
    return pin;
}

unsigned long long int shop::getpno()
{
    return spno;
}


