#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>

#define FAILED_TO_RW_FILE 0
#define FILE_IS_EMPTY 1
#define HASH_FAIL 2

#define INVALID_INPUT 0
#define FILE_IS_CORRUPT 1


#define LINE_LENGTH 60
#define LINE 100


using namespace std;

class HFT
{
    private:
        vector <int> HashMemory;
        vector <unsigned int> HashCounter;

        unsigned int N=0;
        unsigned int Lines=0;
        unsigned int FailLines=0;
        unsigned int mSize=0;
        string actualdata;
        string fileadress;
        string tempdata;
        unsigned int temphash;

        ifstream InputDataFile;
        ofstream OutDataFile;
    public:
        bool h(string);
        bool HasherFile();
        void SetN();
        bool Finder(int);

        bool LoadFile();
        bool TestFile();
        //void ExtractFile(int);

        void PrintData();
        void Graf();

        void Error(int,bool,int);
        void Line(char);
        void StringNumber();

        bool Answer();

        void ClearMemory();

};

/*void HFT::ExtractFile(int n)
{
    InputDataFile.close();
    InputDataFile.open(fileadress);
    for (int i=0;i<n;i++)
    {
       getline(InputDataFile,tempdata,'\n');
       cout<<"Line: "<<i<<"\t Data: "<<tempdata<<endl;
       tempdata.clear();
    }
}*/
void HFT::ClearMemory()
{
    HashMemory.clear();
    HashMemory.shrink_to_fit();
    HashCounter.clear();
    HashCounter.shrink_to_fit();
    Line('*');
    cout<<"!Memory is clear..."<<endl;
}

void HFT::StringNumber()
{
    Line('*');
    cout<<"Number of process string is: "<<Lines<<endl;
    cout<<"Number of corrupt string is: "<<FailLines<<endl;
    //cout<<"File life % : "<<((double)Lines/(double)FailLines)*100<<endl;
    Line('*');
}

void HFT::Line(char c)
{
    for (int i=0;i<LINE_LENGTH;i++)
    {
        cout<<c;
    }
    cout<<endl;
}

void HFT::Error(int id,bool type, int parametr=0)
{
    Line('-');
    if(type)
    {
        switch(id)
        {
        case FAILED_TO_RW_FILE:
            {
              cout << "!ERROR!\t ID:"<<id<<"\t Description: Failed to read/write or find file!"<<endl;
              break;
            }
        case FILE_IS_EMPTY:
            {
              cout << "!ERROR!\t ID:"<<id<<"\t Description: File is empty!"<<endl;
              break;
            }
        case HASH_FAIL:
            {
              cout << "!ERROR!\t ID:"<<id<<"\t Description: Hash function fail!"<<endl;
              break;
            }
        default:
            {
            cout << "!ERROR!\t ID:"<<id<<"\t Description: Unknow error!"<<endl;
            break;
            }
        }
    }
    else
    {
        switch(id)
        {
        case INVALID_INPUT:
            {
              cout << "Warning!\t ID:"<<id<<"\t Description: Invalid input."<<endl;
              break;
            }
        case FILE_IS_CORRUPT:
            {
              cout << "Warning!\t ID:"<<id<<"\t Description: File strings is corrupt/damage or empty. \t Line: "<<parametr<<endl;
              break;
            }
        default:
            {
              cout << "Warning!\t ID:"<<id<<"\t Description: Unknow."<<endl;
              break;
            }
        }
    }
    Line('-');
}

bool HFT::Answer()
{
    string asw;
    cout<<"Answer[yes/no]: ";
    cin>>asw;

    while (asw!="yes"&&asw!="no")
    {
       cin.ignore(LINE,'\n');
       Error(INVALID_INPUT,false);
       cout<<"Please repeat: ";
       cin>>asw;
    }
    if (asw=="yes") return true;
    if (asw=="no") return false;
    return false;
}

bool HFT::LoadFile()
{
    cout << "Do you want open default file? ";
    if (Answer())
    {
        Line('-');
        fileadress="test.txt";
        fileadress="..\\Data\\"+fileadress;
        cout << "->File adress set to default: "<<fileadress<<endl;
    }
    else
    {
       cout << "Please enter the file name: ";
       cin>>fileadress;
       fileadress="..\\Data\\"+fileadress;
                       if (fileadress.rfind(".")<2)
                {
                    Line('-');
                    fileadress += ".txt";
                    cout << "Autocorrect: add .txt postfix." << endl;
                }

        cout << "->File adress set to: "<<fileadress<<endl;
    }
    InputDataFile.open(fileadress.c_str());
    if (!InputDataFile.is_open())
    {
        Error(FAILED_TO_RW_FILE,true);
        cout << "Repeat? ";
        if(Answer())
        {
        Line('*');
        InputDataFile.close();
        if (LoadFile()) return true;
        else return false;
        }
        else return false;
    }
    else return true;
}

bool HFT::TestFile()
{
    InputDataFile.seekg(InputDataFile.beg);
    while(!InputDataFile.eof())
    {
        Lines++;
        getline(InputDataFile,tempdata,'\n');
        if (tempdata.empty())
        {
            Error(FILE_IS_CORRUPT,false,Lines);
            FailLines++;
        }
        else tempdata.clear();
    }
    tempdata.clear();
    if (Lines==0||Lines==FailLines)
    {
        Error(FILE_IS_EMPTY,true);
        return false;
    }
    if (FailLines!=0)
    {
        cout << "File contains some corrupt or empty strings ["<<FailLines<<" of "<<Lines<<"], do you want continue? "<<endl;
        if (Answer())
        {
            return true;
        }
        else
        {
           return false;
        }
    }
    else return true;
}


void HFT::SetN()
{
    cout<<"Please enter the N parametr:";
    cin>>N;
        while (cin.fail()||N<=0||N>100)
    {
        cin.clear();
        cin.ignore(LINE,'\n');
        Error(INVALID_INPUT,false);
        cout<<"Please repeat: ";
        cin>>N;
    }
    Line('-');
}

bool HFT::h(string s)
{
    temphash=0;
    int ls=s.size();
    for(int i=0;i<ls;i++)
    {
        temphash+=s[i]*pow(31,ls-1-i);
    }
    if (temphash>N)
    {
        temphash%=N;
        return true;
    }
    if (temphash<0)
    {
        return false;
    }
    else
    return true;
}

bool HFT::HasherFile()
{
    Lines=0;
    InputDataFile.close();
    InputDataFile.open(fileadress);
    while(!InputDataFile.eof())
    {
        Lines++;
        getline(InputDataFile,tempdata,'\n');
        if (tempdata.empty())
        {
            cout<<"*Line "<<Lines<<" will be pass over!*"<<endl;
            Line('-');
        }
        else
        {
           if(h(tempdata))
           {
            if (!Finder(temphash))
            {
              HashMemory.push_back(temphash);
              HashCounter.push_back(1);
              mSize++;
            }
           }
           else
           {
            Error(HASH_FAIL,true);
            cout<<"*Line "<<Lines<<" will be pass over!*"<<endl;
            Line('-');
           }
        }
    tempdata.clear();
    }
    tempdata.clear();
    InputDataFile.close();
    return true;
}


bool HFT::Finder(int th)
{
    for (unsigned int i=0;i<mSize;i++)
    {
        if (HashMemory[i]==th)
        {
            HashCounter[i]++;
            return true;
        }
    }
    return false;
}

void HFT::PrintData()
{
    unsigned int i=0;
    Line('-');
    cout<<"|\tHASH \t | \tCOUNT \t|"<<endl;
    Line('-');
    for (i=0;i<mSize;i++)
    {
        cout<<"|\t"<<HashMemory[i]<<"\t | \t"<<HashCounter[i]<<"\t|"<<endl;
    }
    Line('-');

    fileadress="..\\Results\\ResultTable.txt";
    cout<<"Saving results to txt file..["<<fileadress<<"]"<<endl;
    OutDataFile.open(fileadress.c_str());
    if (OutDataFile.is_open())
    {
        OutDataFile<<"|\tHASH \t | \tCOUNT \t|"<<endl;
        for (i=0;i<LINE_LENGTH/2;i++)
        {
        OutDataFile<<"-";
        }
        OutDataFile<<endl;
        for (i=0;i<mSize;i++)
        {
            OutDataFile<<"|\t"<<HashMemory[i]<<"\t | \t"<<HashCounter[i]<<"\t|"<<endl;
        }
        OutDataFile<<"Table refresh at: "<<__DATE__<<" "<<__TIME__;
        cout<<"Done!"<<endl;
        OutDataFile.close();
        return;
    }
    else
    {
        Error(FAILED_TO_RW_FILE,true);
        OutDataFile.close();
        return;
    }
}

void HFT::Graf()
{
   unsigned int MAX=0,i=0,n=0,GRAFL=LINE_LENGTH/2;
   double p;
  for (i=0;i<mSize;i++)
  {
     if (MAX<HashCounter[i])
     {
         MAX=HashCounter[i];
     }
  }
  p=((double)GRAFL/(double)MAX);
    Line('X');
    cout<<"|\tHASH \t| \t GRAPH      \t\t|      COUNT \t|"<<endl;
    Line('-');
  for (i=0;i<mSize;i++)
  {
    cout<<"|\t"<<HashMemory[i]<<"\t|";
    for (n=0;n<(p*(double)HashCounter[i]);n++)
    {
        cout<<"X";
    }
    for (n=0;n<=(GRAFL-(p*(double)HashCounter[i]));n++)
    {
        cout<<" ";
    }
    cout<<"|\t"<<HashCounter[i]<<"\t|"<<endl;
  }

      fileadress="..\\Results\\ResultGraph.txt";
    cout<<"Saving results to txt file..["<<fileadress<<"]"<<endl;
    OutDataFile.open(fileadress.c_str());
    if (OutDataFile.is_open())
    {
    OutDataFile<<"|\tHASH \t| \t GRAPH      \t\t|      COUNT \t|"<<endl;
    for (i=0;i<LINE_LENGTH;i++)
    {
      OutDataFile<<"-";
    }
    OutDataFile<<endl;
  for (i=0;i<mSize;i++)
  {
    OutDataFile<<"|\t"<<HashMemory[i]<<"\t|";
    for (n=0;n<(p*(double)HashCounter[i]);n++)
    {
        OutDataFile<<"X";
    }
    for (n=0;n<=(GRAFL-(p*(double)HashCounter[i]));n++)
    {
        OutDataFile<<" ";
    }
    OutDataFile<<"|\t"<<HashCounter[i]<<"\t|"<<endl;
  }

        OutDataFile<<"Graph refresh at: "<<__DATE__<<" "<<__TIME__;
        cout<<"Done!"<<endl;
        OutDataFile.close();
        return;
    }
    else
    {
        Error(FAILED_TO_RW_FILE,true);
        OutDataFile.close();
        return;
    }
 return;
}

int main()
{
    HFT Tester;

    cout << "Welcome in the Hash-Function tester!" << endl;
    Tester.Line('X');
    if (Tester.LoadFile())
    {
        Tester.Line('*');
        cout << "File was successfully opened!" << endl;
    }
    else
    {
       Tester.Line('*');
       cout << "Opening file FAIL!" << endl;
       Tester.ClearMemory();
       return 1;
    }
    cout<<"Program starting the test-file process...Please wait.\t TIME: "<<__TIME__<<endl;
    if (Tester.TestFile())
    {
        Tester.StringNumber();
        cout << "Test file status: PASS\t TIME: "<<__TIME__<<endl;
    }
    else
    {
       Tester.StringNumber();
       cout << "Test file status: FAIL\t TIME: " <<__TIME__<< endl;
       Tester.ClearMemory();
       return 1;
    }
    Tester.SetN();

    cout<<"Allright, press any key to continue..."<<endl;
    getchar();
    cout<<"Program starting the hashing-file process...Please wait.\t TIME: "<<__TIME__<<endl;
    Tester.Line('*');
    if (Tester.HasherFile())
    {
        cout << "Hasher file status: DONE\t TIME: " <<__TIME__<< endl;
        cout<<"Allright, press any key to print results..."<<endl;
        getchar();
        Tester.PrintData();
        Tester.Graf();
    }
    else
    {
       cout << "Hasher file status: FAIL\t TIME: " <<__TIME__<< endl;
       Tester.ClearMemory();
       return 1;
    }

    Tester.ClearMemory();
    cout<<"Press any key to exit..."<<endl;
    getchar();

    return 0;
}
