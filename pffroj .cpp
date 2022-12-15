#include<bits/stdc++.h>
#include<fstream>
using namespace std;

class Person
{
protected:
    string name;
public:
    Person()            {   name = "";  }
    Person(string x)    {   name = x;   }
};

class Login
{
public :
    string L_acc,L_pass;
    int ok=0;
    int loginOK()
    {

        ifstream fin("goo.txt");
        if(!fin)
        {
            cout << "\t\t\t\t\t\tFILE NOT FOUND";
        }
        else
        {
            string line,nm,acc,bl,pss;
            bool flag = 0;

            while(!fin.eof())
            {
                getline(fin, line);
                stringstream ss(line);
                ss >> nm >> acc >> bl >> pss;
                if(L_acc == acc )
                {
                    if (pss==L_pass) {
                    cout << "\n\t\t\tLOGIN SUCCESSFUL\n\n";
                    cout << "\t\t\tNAME    : " << nm << "\n\t\t\tACC_NO  : "<< acc << "\n\t\t\tBALANCE : "<<bl <<"$"<< endl << endl << "\t\t\t";
                    flag=0;
                    ok =1;
                    system("pause");
                    system("cls");
                    break;

                    }
                    else {
                        cout << "\n\t\t\tIncorrect Password!\n\t\t\tPlease Try again Later ...\n\t\t\t";
                        system("pause");
                        system("cls");
                        flag=0 ; break;
                    }
                }
                else   flag = 1 ;
            }
            if(flag == 1)
            {
                cout << "\n\t\t\tYOU ARE NOT LOGGED IN. PLEASE REGISTER FIRST\n\t\t\t";
                system("pause");
                system("cls");
            }
            fin.close();
        }
    }

    void getLogin()
    {
        cout << "\n\n\t\t\tEnter Account No : ";
        cin >> L_acc;
        cout << "\t\t\tEnter Password : ";
        cin >> L_pass;
        this->loginOK();
    }

};

class Account: public Person
{
protected:
    string acc_no,bal,pass;

public:
    Login L;
    Account()
    {
        name = "no name";
        acc_no = "000000";
        bal = "0";
        pass = "nopassword";
    }

    void getInfo()
    {
        bool ok=1;
        cout << "\t\t\tEnter Name : ";              cin >> name ;
        cout << "\t\t\tEnter Password : ";          cin >> pass ;
        cout << "\t\t\tEnter Initial Balance : ";   cin >> bal ;
        while( stoi(bal) <= 500 ) {
            cout << "\n\t\t\tInitial Balance must be at least 500$\n\t\t\tEnter a Valid Balance :";
            cin >> bal ;
        }
        cout << "\n\t\t\tEnter Acc No : ";          cin >> acc_no ;
        // check if in use
        ifstream fin("goo.txt");
        if( fin.is_open() ) {
            string s;
            while(fin >> s) {
                if(acc_no == s) {
                    ok=0; break;
                }
                else ok=1;
            }

            if(ok==0) {
                while( s == acc_no) {
                cout << "\n\t\t\tThe Account No Entered is already in use!";
                cout << "\n\t\t\tPlease Enter a Different Account No : ";
                cin >> acc_no;
                }
            }
            fin.close();
        }
        else cout << "\t\t\t\t\t\tFILE NOT FOUND\n";


    }

    void showInfo()
    {
        cout << "Name : " << name << endl;
        cout << "Acc_no : " << acc_no << endl;
        cout << "Current balance : " << bal << endl;
    }

    void storeInfo()
    {
        ofstream fout("goo.txt",ios::app);

        if( fout.is_open())
        {

            fout << name << "\t\t" << acc_no << "\t\t" << bal << "\t\t" << pass << endl;
            cout << "\n\t\t\tREGISTRATION SUCCESSFULL\n\t\t\t";
            system("pause");
            system("cls");
            fout.close();
        }
        else  cout << "\t\t\t\t\t\tFILE NOT FOUND\n";
    }

    void getnStore()
    {
        getInfo();
        storeInfo();
    }

    void timep(string x, int y)
{
    time_t t =  time(0);   // get time now
    tm* now =  localtime(&t);
    ofstream fout("transtime.txt", ios::app);

    fout << x << "    +" << y << "    ";
    fout << (now->tm_hour) << ":" << (now->tm_min) << ":" << (now->tm_sec)<< "    " <<(now->tm_year + 1900) << '-'<< (now->tm_mon + 1) << '-'<<  now->tm_mday << endl;
    fout.close();
}
    void timen(string x, int y)
{
    time_t t =  time(0);   // get time now
    tm* now =  localtime(&t);
    ofstream fout("transtime.txt", ios::app);

    fout << x << "    -" << y << "    ";
    fout << (now->tm_hour) << ":" << (now->tm_min) << ":" << (now->tm_sec)<< "    " <<(now->tm_year + 1900) << '-'<< (now->tm_mon + 1) << '-'<<  now->tm_mday << endl;
    fout.close();
}

    void withdraw()
    {
        string a,b,c,d,x ;
        x = this->L.L_acc;

        ofstream fout("temp.txt",ios::app);
        ifstream fin("goo.txt");

        if( fin.is_open())
        {
            while( fin >> a >> b >> c >> d )
            {
                if(b != x)
                {
                    fout << a << "\t\t" << b << "\t\t" << c << "\t\t" << d <<endl;
                }
                else
                {
                    // bug
                    unsigned int y,r = stoi(c);
                    cout << "\t\t\tEnter Amount to be Withdrawn : " ;
                    cin >> y;
                    while( ( y > (r-10) ) || ( y < 10 ) ){
                        cout << "\n\t\t\tNote :  1. Last 10$ cannot be withdrawn";
                        cout << "\n\t\t\t        2. More than 10$ have to be withdrawn at a time";
                        cout<< "\n\t\t\tYour Current Balance is : " << r << "$\n";
                        cout<< "\n\t\t\tPlease Enter Valid Amount : ";
                        cin >> y;
                    }
                    r -= y;
                    c = to_string(r);
                    fout << a << "\t\t" << b << "\t\t" << c << "\t\t" << d <<endl;
                    cout << "\n\t\t\tAmount Withdrawn Successfully!\n";
                    timen(x,y);
                    cout << "\t\t\tYour New balance is : " << c << "$\n\n\t\t\t";
                }
            }
            fout.close();
            fin.close();
            remove("goo.txt");
            rename("temp.txt","goo.txt");

        }
        else
            cout << "\t\t\t\t\t\tERROR ACCESSING FILE\n";
    }

    void deposit()
    {
        string a,b,c,d,x ;
        x = this->L.L_acc;

        ofstream fout("temp.txt",ios::app);
        ifstream fin("goo.txt");

        if( fin.is_open())
        {
            while( fin >> a >> b >> c >> d )
            {
                if(b != x)
                {
                    fout << a << "\t\t" << b << "\t\t" << c << "\t\t" << d <<endl;
                }
                else
                {

                    unsigned int y=0,r = stoi(c);
                    cout << "\t\t\tEnter Deposit Amount ( 100~100000$ ): " ;
                    cin >> y;
                    while( y<100 || y>100000) {
                        cout << "\n\t\t\tEnter Valid Amount : ";
                        cin >> y;
                    }
                    timep(x, y);
                    y += r;
                    c = to_string(y);
                    fout << a << "\t\t" << b << "\t\t" << c << "\t\t" << d <<endl;
                    cout << "\n\t\t\tAmount Deposited Successfully!\n";
                    cout << "\t\t\tYour New balance is : " << c << "$\n\n\t\t\t";
                }
            }
            fout.close();
            fin.close();
            remove("goo.txt");
            rename("temp.txt","goo.txt");

        }
        else
            cout << "\t\t\t\t\t\tERROR ACCESSING FILE\n";
    }

    virtual void editName() {
        string a,b,c,d,x ;
        x = this->L.L_acc;

        ofstream fout("temp.txt",ios::app);
        ifstream fin("goo.txt");

        if( fin.is_open())
        {
            while( fin >> a >> b >> c >> d )
            {
                if(b != x)
                {
                    fout << a << "\t\t" << b << "\t\t" << c << "\t\t" << d <<endl;
                }
                else
                {
                    cout << "\t\t\tEnter New Name : " ;
                    cin >> a;
                    fout << a << "\t\t" << b << "\t\t" << c << "\t\t" << d <<endl;
                    cout << "\n\t\t\tName Updated Successfully!\n";
                    cout << "\t\t\tYour New Name is : " << a << "\n\n\t\t\t";
                }
            }
            fout.close();
            fin.close();
            remove("goo.txt");
            rename("temp.txt","goo.txt");

        }
        else
            cout << "\t\t\t\t\t\tERROR ACCESSING FILE\n";
    }

    void editPass() {
        string a,b,c,d,x ;
        x = this->L.L_acc;

        ofstream fout("temp.txt",ios::app);
        ifstream fin("goo.txt");

        if( fin.is_open())
        {
            while( fin >> a >> b >> c >> d )
            {
                if(b != x)
                {
                    fout << a << "\t\t" << b << "\t\t" << c << "\t\t" << d <<endl;
                }
                else
                {
                    cout << "\t\t\tEnter New Password : " ;
                    cin >> d;
                    fout << a << "\t\t" << b << "\t\t" << c << "\t\t" << d <<endl;
                    cout << "\n\t\t\tPassword Updated Successfully! Please Keep Your Password Safe " << "\n\n\t\t\t";
                }
            }
            fout.close();
            fin.close();
            remove("goo.txt");
            rename("temp.txt","goo.txt");

        }
        else
            cout << "\t\t\t\t\t\tERROR ACCESSING FILE\n";
    }

    virtual void viewAllInfo() {}

    virtual void viewAllTransac() {}

};


class Admin : public Account
{
    string code="1234",input;
public:
    Admin () {}
    void viewAllInfo()
    {
        cout << "\n\n\t\t\tEnter Admin Code : " ;
        cin >> input;
        int i=4;
        while( input!=code && --i)
        {
            cout << "\n\t\t\tInvalid code " << i << " try(s) left" << endl;
            cin >> input;
        }

        if(i<=0)    cout << "\n\t\t\tTry again";
        else
        {
            ifstream fin("goo.txt");
            if(!fin)
            {
                cout << "\t\t\t\t\t\tFILE NOT FOUND";
            }
            else
            {
                string line,nm,acc,bl,pss;
                stringstream ss;
                cout << "\n\t\t\tNAME\t\tACC_NO\t\tBALANCE\t\tPASS" << endl;
                while(!fin.eof())
                {

                    getline(fin, line);
                    cout << "\t\t\t" << line  << endl;
                }
                fin.close();
            }
        }
    }

    void viewAllTransac() {
        ifstream fin("transtime.txt");
        string w,x,y,z;
        cout << "\n\t\t\tTRANSACTION DETAILS : ";
        cout << "\n\n\t\t\tACC_NO	 AMOUNT    TIME       DATE\n";
        while(fin >> w >> x >> y >> z) {
            cout << "\t\t\t"<< w << "   " << x << "   " << y << "   " << z << endl;
        }
        fin.close();
    }
     void editName() {
        string a,b,c,d,x,hm ;
        cout << "\t\t\tEnter the name to be changed : "; cin >> x;


        ofstream fout("temp.txt",ios::app);
        ifstream fin("goo.txt");

        if( fin.is_open())
        {
            while( fin >> a >> b >> c >> d )
            {
                if(a != x)
                {
                    fout << a << "\t\t" << b << "\t\t" << c << "\t\t" << d <<endl;
                }
                else
                {
                    cout << "\t\t\tEnter New Name : " ;
                    cin >> a;
                    fout << a << "\t\t" << b << "\t\t" << c << "\t\t" << d <<endl;
                    cout << "\n\t\t\tName Updated Successfully!\n";
                    cout << "\t\t\tYour New Name is : " << a << "\n\n\t\t\t";
                    system("pause");
                }
            }
            fout.close();
            fin.close();
            remove("goo.txt");
            rename("temp.txt","goo.txt");

        }
        else
            cout << "\t\t\t\t\t\tERROR ACCESSING FILE\n";
    }

};

int main()
{


    Account a ,*p;
    Admin ad;
    p = &ad;
        int c,g;
        do {
            cout << "\n\t\t\t\t\t\t\tMAIN MENU\n\n";
            cout << "\t\t\t[1] LOGIN\n";
            cout << "\t\t\t[2] REGISTER\n";
            cout << "\t\t\t[3] ADMIN\n";
            cout << "\t\t\t[4] QUIT\n\n";

            cout << "\t\t\tEnter Desired Option : ";

            cin >> c;

            if(c==1) {
                a.L.getLogin();
                if( a.L.ok ) {
                do{

                    cout << "\n\t\t\t\t\t\t\tSERVICE MENU\n\n";
                    cout << "\t\t\t[1] WITHDRAW\n";
                    cout << "\t\t\t[2] DEPOSIT\n";
                    cout << "\t\t\t[3] EDIT NAME\n";
                    cout << "\t\t\t[4] EDIT PASSWORD\n";
                    cout << "\t\t\t[5] QUIT\n\n";

                    cout << "\t\t\tEnter desired option : ";

                    cin >> g;

                    if(g==1) {
                        a.withdraw();
                    }
                    else if(g==2) {
                        a.deposit();
                    }
                    else if(g==3) {
                        a.editName();
                    }
                    else if(g==4) {
                        a.editPass();
                    }
                    cout << "\t\t\t";
                    system("pause");
                    system("cls");

                }while(g!= 5);


                }
            }
            else if(c==2) {
                a.getnStore();

            }
            else if(c==3) {


                do{
                    system("cls");
                    cout << "\n\t\t\t\t\t\t\tADMIN MENU\n\n";
                    cout << "\t\t\t[1] VIEW ALL USER INFO\n";
                    cout << "\t\t\t[2] EDIT USERNAME\n";
                    cout << "\t\t\t[3] VIEW ALL TRANSACTION\n";
                    cout << "\t\t\t[4] QUIT\n\n";

                    cout << "\t\t\tEnter Desired Option : ";

                    cin >> g;

                    if(g==1) {

                        p->viewAllInfo();
                        cout << "\n\t\t\t";
                        system("pause");
                    }

                    else if(g==2) {
                        ((Admin *)p)->editName();
                        cout << "\n\t\t\t \n";
                    }
                    else if( g==3) {
                        p->viewAllTransac();
                        cout << "\n\t\t\t";
                        system("pause");
                    }

                }while(g!= 4);
                system("cls");
            }

        }while(c!=4);

    cout << "\n\t\t\t\t\t\t\tTHANK YOU" << endl ;
    return 0;
}
