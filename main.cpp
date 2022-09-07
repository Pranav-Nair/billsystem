#include<iostream>
#include<iomanip>
#include<process.h>
#include<dir.h>
#include "billobj.h"
using namespace std;
void startdb();
void start();
void startcdb();
void startbill();
void start_shopinfo();
void startdb()
{
    int num;
    product p[1000];
    product pdb;
    bool state=1;
    while(state)
    {
    int ch;
   cout<<endl;
   cout<<endl;
   cout<<"+";for(int i=0;i<99;i++)
   cout<<"-";
   cout<<"+"<<endl;
    cout<<setw(100)<<left<<"| PRODUCTS DETAILS MENU"<<"|"<<endl;
   cout<<"+";for(int i=0;i<99;i++)
   cout<<"-";
   cout<<"+"<<endl;
    cout<<setw(100)<<left<<"| 1.read product details"<<"|"<<endl;
    cout<<setw(100)<<left<<"| 2.search for product details"<<"|"<<endl;
    cout<<setw(100)<<left<<"| 3.Add item data to existing database"<<"|"<<endl;
    cout<<setw(100)<<left<<"| 4.update details of existing product"<<"|"<<endl;
    cout<<setw(100)<<left<<"| 5.update stock of existing item"<<"|"<<endl;
    cout<<setw(100)<<left<<"| 6.remove item from existing database"<<"|"<<endl;
    cout<<setw(100)<<left<<"| 7.reset the existing database and start fresh"<<"|"<<endl;
    cout<<setw(100)<<left<<"| 8.<--go back"<<"|"<<endl;
    cout<<"+";for(int i=0;i<99;i++)cout<<"-";cout<<"+"<<endl;
    cout<<endl;
    cout<<"choose an option for database ";
    cin>>ch;
    switch(ch)
    {
        case 1:pdb.readfromdb();
                break;
        case 2:pdb.searchdb();
                break;
        case 3:cout<<"enter how many items would u like to add ";
                cin>>num;
                cout<<endl;
                cin.ignore();
                for(int i=0;i<num;i++)
                {
               pdb.writetodb(p[i]);
                cout<<endl;
                }
                break;
        case 4:cout<<"enter pid for item to be updated ";
                cin>>num;
                cin.ignore();
                pdb.updatetodb(p,num);
                break;
        case 5:cout<<"enter pid of item stock to update ";
                cin>>num;
                pdb.modifystock(num);
                break;
        case 6:cout<<"enter the item id of item u like to remove";
                cin>>num;
                pdb.removefromdb(p,num);
                break;
        case 7:cout<<"how many items "<<endl;
                cin>>num;
                cout<<endl;
                cin.ignore();
                remove("db/storage.bin");
                for(int i=0;i<num;i++)
                {
               pdb.writetodb(p[i]);
                cout<<endl;
                }
               break;
        case 8:state=0;
                break;
        default:cout<<"invalid choice ";
    }
    }//image of product details menu below

}
void start()
{
    while(1)
    {
int ch;
cout<<endl;
cout<<endl;
cout<<"+";for(int i=0;i<99;i++)
cout<<"-";
cout<<"+"<<endl;
    cout<<setw(100)<<left<<"| MAIN MENU"<<"|"<<endl;
cout<<"+";for(int i=0;i<99;i++)
cout<<"-";
cout<<"+"<<endl;
    cout<<setw(100)<<left<<"| 1.modify product details"<<"|"<<endl;
    cout<<setw(100)<<left<<"| 2.start a billing process"<<"|"<<endl;
    cout<<setw(100)<<left<<"| 3.view customer details"<<"|"<<endl;
    cout<<setw(100)<<left<<"| 4.view shop details"<<"|"<<endl;
    cout<<setw(100)<<left<<"| 5.exit program"<<"|"<<endl;
    cout<<"+";for(int i=0;i<99;i++)cout<<"-";cout<<"+"<<endl;
    cout<<endl;
    cout<<"enter a choice ";
    cin>>ch;
    switch(ch)
    {
        case 1:startdb();
                break;
        case 2:startbill();
                break;
        case 3:startcdb();
                break;
        case 4:start_shopinfo();
                break;
        case 5:exit(0);
                break;
        default:cout<<"not valid choice"<<endl;
    }
    }//image of main menu here
}
void startcdb()
{
        customer cdb;
        bill b;
        char id[100];
        int ch;
        bool state=1;
        while(state)
        {
        customer c;
        cout<<endl;
        cout<<endl;
        cout<<"+";for(int i=0;i<99;i++)
        cout<<"-";
        cout<<"+"<<endl;
        cout<<setw(100)<<left<<"| CUSTOMER DETAILS MENU"<<"|"<<endl;
        cout<<"+";for(int i=0;i<99;i++)
        cout<<"-";
        cout<<"+"<<endl;
        cout<<setw(100)<<left<<"| 1.display customer data "<<"|"<<endl;
        cout<<setw(100)<<left<<"| 2.search for entries"<<"|"<<endl;
        cout<<setw(100)<<left<<"| 3.delete all records"<<"|"<<endl;
        cout<<setw(100)<<left<<"| 4.check bill details"<<"|"<<endl;
        cout<<setw(100)<<left<<"| 5.<--go back"<<"|"<<endl;
        cout<<"+";for(int i=0;i<99;i++)cout<<"-";cout<<"+"<<endl;
        cout<<endl;
        cout<<"enter a choice ";
        cin>>ch;
        switch(ch)
        {
                case 1:cdb.readfromcdb();
                        break;
                case 2:cdb.searchincdb();
                        break;
                case 3:cdb.deletecdb();
                        break;
                case 4:cout<<"enter ref no. of bill ";
                        cin>>id;
                        b.readfrombill(id);
                        break;
                case 5:state=0;
                        break;
                default:cout<<"invalid choice "<<endl;
        }
        }
}//image of customer details menu here

void startbill()
{
        int ch;
        float total=0;
        unsigned long long int id=1;
        customer c,cdb;
        bill* b= new bill[1000];
        bill bdb;
        product pdb;
        char filename[50];
        int i=0;
        c.getdata();
        while(id!=0)
        {
                cout<<endl;
                cout<<"enter the pid of item to add to bill(0 to stop)";
                cin>>id;
                b[i].billgetdata(id);
            if(b[i].comparebid(0)==0)
            {
                b[i].billdisplay_head();
                b[i].billdisplay();
                b[i].billdisplay_tail(0);
            }
                i++;
        }
        cout<<endl<<endl;
        bdb.billdisplay_head();
        for(int j=0;j<i;j++)
        {
            if(b[j].comparebid(0)==0)
            {
            b[j].billdisplay();
            total+=b[j].gettaxed_amt();
            }
        }
        bdb.billdisplay_tail(total);
        cout<<endl<<endl;
        cout<<"confirm this purchase"<<endl;
        cout<<"1.confirm"<<endl;
        cout<<"2.cancel"<<endl;
        cout<<"enter choice ";
        cin>>ch;
        switch(ch)
        {
            case 1:c.readpay();
            c.copyfilename(filename);
            cout<<endl;
            cdb.writetocdb(c);
            for(int j=0;j<i;j++)
            {
                if(b[j].comparebid(0)==0)
                {
                    bdb.writetobill(b[j],filename);
                    pdb.removefromstock(b[j].getbid(),b[j].getqty());
                }
            }
            bdb.writetxtfile(b,filename,i,total,c);
            cout<<endl<<"the purchase was succesful"<<endl;
            break;
            case 2:cout<<"the transaction was cancelled"<<endl;
                break;
            default:cout<<"invalid choice transaction failed"<<endl;

        }
        delete[] b;
}//billing process screenshot and bill output image here

 void start_shopinfo()
{
    bool state=1;
   int ch;
    shop s;
    while(state==1)
    {
     cout<<endl;
        cout<<"+";for(int i=0;i<99;i++)
        cout<<"-";
        cout<<"+"<<endl;
    cout<<setw(100)<<"| SHOP INFORMATION"<<"|"<<endl;
        cout<<"+";for(int i=0;i<99;i++)
        cout<<"-";
        cout<<"+"<<endl;
     cout<<setw(100)<<"| 1.read shop information"<<"|"<<endl;
     cout<<setw(100)<<"| 2.create shop information/reset shop information"<<"|"<<endl;
     cout<<setw(100)<<"| 3.<--go back"<<"|"<<endl;
        cout<<"+";for(int i=0;i<99;i++)
        cout<<"-";
        cout<<"+"<<endl;
     cout<<endl<<endl;
     cout<<"enter a choice ";
    cin>>ch;
    cout<<endl<<endl;
     switch(ch)
     {
        case 2:cin.ignore();
             s.shop_getdata();
             s.writeshopdata(s);
            break;
       case 1:s.readshopinfo();
            break;
       case 3:state=0;
           break;
      default:cout<<"invalid choice"<<endl;
   }
   }
  }
//shop information menu image here

int main()
{
    mkdir("db");
    mkdir("bills");
    start();
}
