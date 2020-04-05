#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

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

node list_insert(int value){

    node *tmp = new node;

    tmp->key=value;

    if(HEAD!=NULL){
       tmp->next=HEAD;
    }
    HEAD=tmp;

    return *tmp;
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

void czy_spojna(){
    int i,n=rozmiar_listy();
    node *tmp=HEAD;
    for(i=0;i<n;i++){
        if(tmp==NULL){
            cout<<"nie spojna";
        }
        tmp=tmp->next;
    }
}

void fill_random(int *t, int n){
    fill_increasing(t,n);
    shuffle(t,n);
}

void (*rodzaj_wypelnienia[])(int *,int n) = {fill_increasing,fill_random};
string nazwa_wypelnienia[] = {"(dane wejsciowe rosnoce)","(dane wejsciowe losowe)"};
int nk[]={10000,20000,40000,80000};

int main()
{
    srand(time(NULL));

    int i,j,k;
    node a;
    node *aktualny;

    clock_t start;
    clock_t stop;

    for(k=0;k<2;k++){

            cout<<nazwa_wypelnienia[k]<<endl;

    for(i=0;i<sizeof(nk)/sizeof(*nk);i++){
        int *T = new int[nk[i]];

        cout<<endl<<endl<<"rozmiar listy: "<<nk[i]<<endl;

        rodzaj_wypelnienia[k](T,nk[i]);

        start = clock();
        for(j=0;j<nk[i];j++){
            a=list_insert(T[j]);
        }
        stop = clock();
        czy_spojna();
        cout<<endl<<"czas dodawania elementow: "<<(double)(stop-start)/(double)CLOCKS_PER_SEC;


        shuffle(T,nk[i]);

        start = clock();
        for(j=0;j<nk[i];j++){
            aktualny=list_search(T[j]);
        }
        stop = clock();
        czy_spojna();
        cout<<endl<<"czas wyszukiwania elementow: "<<": "<<(double)(stop-start)/(double)CLOCKS_PER_SEC;

        for(j=0;j<nk[i];j++){
            list_delete(T[j]);
        }
        czy_spojna();

        delete[] T;
    }

    cout<<endl<<endl<<endl<<endl;

    }

    return 0;
}
