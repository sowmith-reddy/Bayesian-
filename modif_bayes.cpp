#include<stdio.h>
#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<set>
#include<string>
#include <dirent.h>
#include<map>
#include<math.h>
using namespace std;
map<string,int> mod;
set <string> s;
map<string,int> datapos,dataneg;
map<string,int> common;
set<string>int1,int2;
map<string,int>::iterator it1;
set<string>::iterator it;
int correct=0,wrong=0,negwords=0,poswords=0;
int poscount=0,negcount=0;
int tp=0,tn=0,fp=0,fn=0;
double  find(string data,int f)
{
  for(int i=0;i<data.length();i++)
  {
    if(data[i]>='A'&&data[i]<='Z')
    {
      data[i]=data[i]+32;
    }
  }
  int a=s.count(data);
  if(a==0&&f==1)
  {
    //cout<<(double)datapos[data]<<"\n";
  //  if(datapos[data]==0)
    //return 0;
    //cout<<(double)(datapos[data]+1)/700;
//  cout<<  ((double)(datapos[data]+1)/619)<<"\n";
    double sow= ((double)(datapos[data]+1)/619);
    //cout<<sow<<"\n";
    return sow;
  }
  if(a==0&&f==2)
  {

    double sow= ((double)(dataneg[data]+1)/682);
    //cout<<sow<<"\n";
    return sow;
  }
}
void count(string data,char *str)
{
for(int i=0;i<data.length();i++)
{
  if(data[i]>='A'&&data[i]<='Z')
  {
    data[i]=data[i]+32;
  }
}
//cout<<data<<"\n";
int a=s.count(data);
if(!strcmp(str,"data/aclImdb/train/pos"))
{
  if(a==0)
  {
    datapos[data]++;
  }
}
else
{
  if(a==0)
  {
    dataneg[data]++;
  }
}
}
void classif(char *str)
{
  int psow=0;
  DIR* dpdf;
  struct dirent *epdf;
  dpdf = opendir(str);
  char path[100];
  int j=0,ind=2;
  path[0]='.';
  path[1]='/';
  while(str[j]!='\0'){
    path[ind++]=str[j++];
  }
  path[ind++]='/';

  int k=ind;
  while ((epdf = readdir(dpdf))!=NULL)
  {

    if(epdf->d_name[0]!='.')
    {
    ind=k;
    j=0;
    //cout<<epdf->d_name<<"\n";
    while(epdf->d_name[j]!='\0'){
      //cout<<epdf->d_name[j];
      path[ind++]=epdf->d_name[j++];
    }
    path[ind]='\0';
  //  cout<<"\n"<<path<<"\n";
    ifstream f;
    string data;
    f.open(path);
    if(!strcmp(str,"data/aclImdb/train/pos"))
    {
      mod.clear();
      while(f>>data){//cout<<data<<"\n";
      if(mod[data]!=0)
      continue;
      mod[data]++;
       common[data]++;
       poswords++;
       count(data,str);
      }
    }
    if(!strcmp(str,"data/aclImdb/train/neg"))
    {
      mod.clear();
      while(f>>data){//cout<<data<<"\n";
      if(mod[data]!=0)
      continue;
      mod[data]++;
          common[data]++;
          negwords++;
          count(data,str);}
    }
     //break;
    if(!strcmp(str,"data/aclImdb/test/pos"))
     {
        double  ptest=0;
       double  ntest=0;
       while(f>>data)
       {
         for(int i=0;i<data.length();i++)
         {
           if(data[i]>='A'&&data[i]<='Z')
           {
             data[i]=data[i]+32;
           }
         }
         //cout<<data<<"\n";
         ptest=ptest-log(((double)(datapos[data]+1)/(poswords+common.size())));
         ntest=ntest-log(((double)(dataneg[data]+1)/(negwords+common.size())));
       }
    //   cout<<ptest<<" "<<ntest<<"\n";
       if(ptest<=ntest)
       {
         tp++;
         correct++;
       }
       else
       {
         fn++;
         wrong++;
       }

     }

    if(!strcmp(str,"data/aclImdb/test/neg"))
    {
      double ptest=0;
      double  ntest=0;
      while(f>>data)
      {
        //cout<<data<<"\n";
        ptest=ptest-log(((double)(datapos[data]+1)/(poswords+common.size())));
        ntest=ntest-log(((double)(dataneg[data]+1)/(negwords+common.size())));
      }

    //  cout<<ptest<<" "<<ntest<<"\n";
      if(ptest>=ntest)
      {
        tn++;
        correct++;
      }
      else
      {
        fp++;
        wrong++;
      }

    }
    psow++;
    //if(psow==5000)
    //break;
    }
  }


}
int main()
{
	string data;
	ifstream infile;
	infile.open("stop_words.txt"); //opening  a file
	while(getline(infile,data))
		{
      //cout<<data;
		s.insert(data);//inserting values into the set s
		}
    set<string> :: iterator it;
    for(it=s.begin();it!=s.end();it++)
  		cout<<*it<<endl;
    //  classif("sow");
//  classif("ex/train/pos");
classif("data/aclImdb/train/pos");
  /* for(it1=datapos.begin();it1!=datapos.end();it1++)
   {
     cout<<it1->first<<" "<<it1->second<<"\n";
   }
*/
  //  classif("neg");
  classif("data/aclImdb/train/neg");
  //classif("ex/train/neg");
  //for(it1=dataneg.begin();it1!=dataneg.end();it1++)
  //{
    //cout<<it1->first<<" "<<it1->second<<"\n";
  //}
  poscount=datapos.size();
  negcount=dataneg.size();
classif("data/aclImdb/test/pos");
 //classif("ex/test/pos");
   cout<<"//////////////////////negtest////////////////////////\n";
//  classif("ex/test/neg");
  classif("data/aclImdb/test/neg");
  cout<<correct<<"\n";
  cout<<wrong<<"\n";
  cout<<poscount<<"  "<<negcount<<"\n";
  cout<<"Accuracy---- "<<(((double)correct/25000)*100)<<"\n";
  double prec=((double)tp/(tp+fp));
  cout<<"Positive Precission---- "<<((double)tp/(tp+fp))<<"\n";
  double reca=(double)tp/(tp+fn);
  cout<<"Positvie Recall---- "<<(double)tp/(tp+fn)<<"\n";
  cout<<"Positive F1Score---- "<<2*(reca*prec)/(reca+prec)<<"\n";
  double nprec=((double)tn/(tn+fn));
  cout<<"Negative Precission---- "<<((double)tn/(tn+fn))<<"\n";
  double nreca=(double)tn/(tn+fp);
  cout<<"Negative Recall---- "<<(double)tn/(tn+fp)<<"\n";
  cout<<"Negative F1Score---- "<<2*(nreca*nprec)/(nreca+nprec)<<"\n";


}
