#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <assert.h>

using namespace std;

struct node {
    int key;
    node *next=NULL;
};

node *HEAD=NULL;

int rozmiar_listy(){
    node *tmp=HEAD;
    int i=0;
    while(tmp!=NULL){
        i++;
        tmp=tmp->next;
    }
    return i;
}

node *list_insert(int value){

    node *tmp = new node;

    tmp->key=value;

    if(HEAD!=NULL){
       tmp->next=HEAD;
    }
    HEAD=tmp;

    return tmp;
}

node *list_search(int value){
    node *i=HEAD;
    while(i->key!=value&&i!=NULL){
        i=i->next;
    }
    return i;
}

void fill_increasing(int *t, int n) {
    for (int i = 0; i < n; i++) {
        t[i] = i;
    }
}

void shuffle(int *t, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % i;
        int temp = t[i];
        t[i] = t[j];
        t[j] = temp;
    }
}

void list_delete(int value){
    if(HEAD->key==value){
        node *tmp=HEAD;
        HEAD=HEAD->next;
        delete tmp;
    }
    else {
        node *prev=HEAD;
        node *i=HEAD->next;
        while(i->key!=value&&i!=NULL){
            i=i->next;
            prev=prev->next;
        }
        if(i!=NULL){
        prev->next=i->next;
        delete i;
        }
    }
}

void fill_random(int *t, int n){
    fill_increasing(t,n);
    shuffle(t,n);
}


void (*rodzaj_wypelnienia[])(int *,int n) = {fill_increasing,fill_random};
int ns[]={10000,20000,30000,40000,50000,60000,70000,80000};
fstream plik[2];

int main()
{
    srand(time(NULL));

    int i,j,k,x;
    node *aktualny;

    clock_t start;
    clock_t stop;

    for(k=0;k<2;k++){

            if(k==0){
                plik[k].open("dane_wejsciowe_rosnoce.txt",ios::out);
                cout<<"dane_wejsciowe_rosnoce"<<endl;
            }
            else  {
                plik[k].open("dane_wejsciowe_losowe.txt",ios::out);
                cout<<"dane_wejsciowe_losowe"<<endl;
            }

            plik[k]<<"rozmiar "<<"dodawanie "<<"wyszukiwanie "<<endl;

            cout<<"rozmiar "<<"dodawanie "<<"wyszukiwanie "<<endl;

    for(i=0;i<sizeof(ns)/sizeof(*ns);i++){
        int *T = new int[ns[i]];

        cout<<ns[i]<<" ";
        plik[k]<<ns[i]<<" ";

        rodzaj_wypelnienia[k](T,ns[i]);

        start = clock();
        for(j=0;j<ns[i];j++){
            aktualny=list_insert(T[j]);
            assert(aktualny != NULL);       // inserted element cannot be NULL
            assert(aktualny->key == T[j]);
        }
        stop = clock();

        cout<<(double)(stop-start)/(double)CLOCKS_PER_SEC<<" ";
        plik[k]<<(double)(stop-start)/(double)CLOCKS_PER_SEC<<" ";

        shuffle(T,ns[i]);


        start = clock();
        for(j=0;j<ns[i];j++){
            aktualny=list_search(T[j]);
            assert(aktualny != NULL);       // found element cannot be NULL
            assert(aktualny->key == T[j]);
        }
        stop = clock();

        cout<<(double)(stop-start)/(double)CLOCKS_PER_SEC<<" ";
        plik[k]<<(double)(stop-start)/(double)CLOCKS_PER_SEC<<" ";


        for(j=0;j<ns[i];j++){
            assert(rozmiar_listy() == ns[i]-j);
            list_delete(T[j]);
        }

        assert(rozmiar_listy() == 0);       // after all deletions, the list size is zero
        assert(HEAD == NULL);


        plik[k]<<endl;
        cout<<endl;

        delete[] T;
    }

    cout<<endl<<endl<<endl<<endl;

        plik[k].close();
    }



    return 0;
}

        //x=(stop-start)/CLOCKS_PER_SEC;
        //plik[k]<<x<<","<<((double)(stop-start)/(double)CLOCKS_PER_SEC-x)*1000<<" ";
