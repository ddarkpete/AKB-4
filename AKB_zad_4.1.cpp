#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

vector< int > tab;//[1000];
int * multiset_;
int cmulti = 0;
int * res;
int cut_number;
int maxind;


void read_file()
{
    string file_name;
    fstream file;
    cout<<"Podaj nazwe pliku : ";
    cin>>file_name;
    file_name = file_name + ".txt";
    file.open(file_name.c_str(), ios::in);
    while( !file.eof() )
    {
        int buff;
        file >> buff;//tab[ cmulti ];
        tab.push_back(buff);
        cmulti++;
       // cout<<cmulti<<" "<<tab[cmulti]<<endl;
    }
    file.close();
    multiset_ = new int [cmulti];
    for(int i = 0; i < cmulti; i++)
    {
        multiset_[ i ] = tab[ i ];
    }
}
void cuts_number()//obliczamy liczbe ciec
{
    int i;
    //cout<<cmulti<<endl;
    for(int j = 2; j <= cmulti; j++)
    {
        int result= 1;
        for(i = 1; i <= 2; i++)
        {
            result = result * ( j - i + 1 ) / i;
            //cout<<result<<endl;
            // Obliczanie ze wzoru iteracyjnego
        }
        if(result == cmulti)
        {
            cut_number = j - 2;
            cut_number += 1;
            cout<<"Liczba ciec: "<<cut_number - 1<<" "<<cmulti<<endl;
            break;
        }
        if(j == cmulti)//nieprawidlowa liczba danych wejsciowych
        {
            cout<<"Nieprawidlowa licznosc multrizbioru"<<cmulti<<endl;
            system("pause");
        }


    }//to jest ok

}

/*void b_sort(int tab[],int n)//bubble sort
{
    for(int i=0; i<n; i++)
        for(int j=1; j<n-i; j++)
            if(tab[j-1]>tab[j])
                swap(tab[j-1], tab[j]);
}*/
void szukaj(int ind, int *jest, int actual, int act_result[])
{
    if( ind <= maxind )
        {
            //cout<<"*****"<<endl;
            act_result[ind] = multiset_[actual];
            bool c_visited[cmulti];
            for (int i = 0; i < cmulti; ++i)
            {
                c_visited[i] = false;
            }
            c_visited[actual] = true;
            bool unbroken = true;
            if(ind > 0)
            {
                for (int i = 0; i < ind + 1; ++i)
                {
                    for (int j = 0; j < cmulti; ++j)
                    {
                        if(act_result[i]==multiset_[j])
                        {
                            c_visited[j] == true;
                            break;
                        }
                    }
                }
                int sum;
                for(int m = 0;m < ind; m++)
                {
                    sum = act_result[m];
                    for(int s = m + 1; s <= ind; s++)
                    {
                        sum += act_result[s];
                        for (int i = 0; i < cmulti; ++i)
                        {
                            if( sum == multiset_[i] && c_visited[i] == false )
                            {
                                c_visited[i] = true;
                                break;
                            }
                            if (i == cmulti - 1)
                            {
                                unbroken = false;
                                //cout<<sum<<endl;
                                break;
                            }
                        }
                    }
                }
            }
            if( ind == maxind && unbroken)
            {
                cout<<"Rozwiazanie : "<<endl;
                for (int i = 0; i <=maxind; ++i)
                {
                    cout<<act_result[i]<<"  ";

                }
                cout<<endl;
                *jest = 1;
            }
            else if(unbroken)
            {

                for (int i = 0; i < cmulti; ++i)
                {
                    if(*jest == 1)break;
                    if(c_visited[i] == false)
                    {
                        //cout<<"next el "<<i<<endl;
                        szukaj( ind + 1, jest , i , act_result);
                    }
                }
            }
        }

}
main()
{
    int jest = 0;
    read_file();
    double duration;
    for( int j = 0 ; j < cmulti; j++)
    {
        cout<<multiset_[j]<<" ";
    }
    cout<<endl;
    cuts_number();
    //b_sort(multiset_,cmulti);
    //cout<<cmulti<<endl;
    maxind = cut_number - 1;
    //cout<<maxind<<endl;
    res = new int [cut_number];
    clock_t start = clock();
    for(int i = 0; i < cmulti; i++)
    {
        if(jest == 0)
        {
            for(int z = 0 ; z < maxind + 1 ; z++)
            {
                res[z] = 0;
            }
            szukaj(0,&jest, i,res);
        }
    }
    if( jest == 0)
    {
        cout<<" Brak rozwiazania"<<endl;
        system("pause");
    }
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    if(duration < 10.0)
    {
        cout<<"Czas :"<<setprecision( 2 )<<duration<<" sek"<<endl;
    }
    else
    {
        cout<<"Czas :"<<duration<<" sek"<<endl;
    }
    system("pause");
    return 0;
}

