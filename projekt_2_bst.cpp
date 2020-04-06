#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <assert.h>

using namespace std;

void zamien(int *a,int *b){
    int tmp=*a;
    *a=*b;
    *b=tmp;
}

void usun_korzen(int *heap,unsigned int index,unsigned int rozmiar){//rozmniar - liczba elementów kopca, index - badany element kopca


    unsigned int l=2*index+1;
    unsigned int r=2*index+2;
    unsigned int argmin;
    if(l<rozmiar){
        if(r>=rozmiar || heap[l] < heap[r]){
            argmin=l;
        }
        else argmin=r;
        if(heap[argmin]<heap[index]){
        zamien(&heap[argmin],&heap[index]);
        usun_korzen(heap,argmin,rozmiar);
    }
    }

}

void heap_sort(int *T, unsigned int n) {

    unsigned int i,syn, rodzic, rozmiar=n;

    int heap[n];

    for(i=0;i<n;i++){
        heap[i]=T[i];
    }

    for(i=1;i<n;i++){
            syn=i;
            rodzic=(i-1)/2;
        while(heap[syn]<heap[rodzic]){
            zamien(&heap[syn],&heap[rodzic]);
            syn=rodzic;
            if(rodzic!=0)rodzic=(rodzic-1)/2;
        }
    }//robienie kopca


    for(i=0;i<n;i++){

        T[i]=heap[0];
        rozmiar--;
        heap[0]=heap[rozmiar];
        usun_korzen(heap, 0,rozmiar);

    }//wype³nianie tablicy

}



struct node {
    int key;
    node *left=NULL;
    node *right=NULL;
};

void create_node(node *tmp,int value){
        tmp->key=value;
        tmp->left=NULL;
        tmp->right=NULL;
    }

struct node *ROOT = NULL;

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

void fill_random(int *t, int n){
    fill_increasing(t,n);
    shuffle(t,n);
}

 node **tree_search(node **candidate, int value) {

    if((*candidate)==NULL){
        return candidate;
    }
    if(value<(*candidate)->key){
        return tree_search(&((*candidate)->left), value);
    }
    if(value>(*candidate)->key){
        return tree_search(&((*candidate)->right), value);
    }
    return candidate;
}

void tree_insert(int value) {
    node *tmp = new node;
    create_node(tmp,value);
    *(tree_search(&ROOT , value))=tmp;
}

 node **tree_maximum(node **candidate) {
    if((*candidate)->right==NULL){
        return candidate;
    }
    else {
        return tree_maximum(&((*candidate)->right));
    }
}

int tree_size(node *element) {
    if(element==NULL){
        return 0;
    }
    else if(element->left==NULL&&element->right==NULL){
        return 1;
    }
    else {
        return 1+tree_size(element->left)+tree_size(element->right);
    }
}

void tree_delete(int value){
    node **p;
    p=tree_search(&ROOT,value);

    if(((*p)->left)==NULL&&((*p)->right)==NULL){
        (*p)=NULL;
    }
    else if(((*p)->left)!=NULL&&((*p)->right)==NULL){
        (*p)=((*p)->left);
    }
    else if(((*p)->left)==NULL&&((*p)->right)!=NULL){
        (*p)=((*p)->right);
    }
    else {
        node **maximum=tree_maximum(&((*p)->left));
        (*p)->key=(*maximum)->key;
        (*maximum)=(*maximum)->left;

    }
}

void tree_insert_binary(int *t,int x,int y){
    if(x==y){
        tree_insert(t[x]);
    }
    else if(y-x==1){
        tree_insert(t[x]);
        tree_insert(t[y]);
    }
    else {
        int z=x+((y-x)/2);
        tree_insert(t[z]);
        tree_insert_binary(t,x,z-1);
        tree_insert_binary(t,z+1,y);
    }
}


bool is_bst(struct node *element) {
    // empty tree is a valid BST
    if (element == NULL) {
        return true;
    }
    // leaf node is valid
    if (element->left == NULL && element->right == NULL) {
        return true;
    }
    // only right subnode? check it recursively
    if (element->left == NULL && element->right != NULL) {
        return (element->key < element->right->key) && is_bst(element->right);
    }
    // only left subnode? check it recursively
    if (element->left != NULL && element->right == NULL) {
        return (element->key > element->left->key) && is_bst(element->left);
    }
    // both subnodes present? check both recursively
    return (element->key > element->left->key)
        && (element->key < element->right->key)
        && is_bst(element->left)
        && is_bst(element->right);
}


void insert_increasing(int *t, int n) {
    for (int i = 0; i < n; i++) {
        tree_insert(t[i]);
    }
}

void insert_random(int *t, int n) {
    shuffle(t, n);
    for (int i = 0; i < n; i++) {
        tree_insert(t[i]);
    }
}

void insert_binary(int *t, int n) {
    //heap_sort(t,n);
    tree_insert_binary(t,0,n-1);
}




void (*rodzaj_wstawiania[])(int *,int n) = {insert_increasing,insert_random,insert_binary };
int ns[]={10000,20000,30000,40000,50000,60000};
fstream plik[3];

main(){




    srand(time(NULL));

    int i,j,k;
    node *aktualny;
    node **pnode;

    clock_t start;
    clock_t stop;

    for(k=0;k<3;k++){

            if(k==0){
                plik[k].open("dane_wejsciowe_rosnoce.txt",ios::out);
                cout<<"dane_wejsciowe_rosnoce"<<endl;
            }
            else if(k==1)  {
                plik[k].open("dane_wejsciowe_losowe.txt",ios::out);
                cout<<"dane_wejsciowe_losowe"<<endl;
            }
            else {
                plik[k].open("drzewo_zrownowazone.txt",ios::out);
                cout<<"drzewo_zrownowazone"<<endl;
            }

            plik[k]<<"rozmiar "<<"dodawanie "<<"wyszukiwanie "<<endl;

            cout<<"rozmiar "<<"dodawanie "<<"wyszukiwanie "<<endl;

    for(i=0;i<sizeof(ns)/sizeof(*ns);i++){
        int *T = new int[ns[i]];

        cout<<ns[i]<<" ";
        plik[k]<<ns[i]<<" ";


        fill_increasing(T,ns[i]);


        start= clock();
        rodzaj_wstawiania[k](T,ns[i]);
        stop = clock();

        cout<<(double)(stop-start)/(double)CLOCKS_PER_SEC<<" ";
        plik[k]<<(double)(stop-start)/(double)CLOCKS_PER_SEC<<" ";

        assert(tree_size(ROOT) == ns[i]);       // after all insertions, tree size must be `n`
        assert(is_bst(ROOT));               // after all insertions, tree must be valid BST


        shuffle(T,ns[i]);

        start = clock();
        for(j=0;j<ns[i];j++){
            pnode=tree_search(&ROOT,T[j]);
            aktualny=*pnode;
            assert(aktualny != NULL);       // found element cannot be NULL
            assert(aktualny->key == T[j]);
        }
        stop = clock();

        cout<<(double)(stop-start)/(double)CLOCKS_PER_SEC<<" ";
        plik[k]<<(double)(stop-start)/(double)CLOCKS_PER_SEC<<" ";


        shuffle(T,ns[i]);

        for(j=0;j<ns[i];j++){
            assert(tree_size(ROOT) == ns[i]-j);
            tree_delete(T[j]);
             assert(is_bst(ROOT));           // after deletion, tree must still be valid BST
        }

        assert(tree_size(ROOT) == 0);       // after all deletions, tree has size zero


        plik[k]<<endl;
        cout<<endl;

        delete[] T;
        delete ROOT;
    }

    cout<<endl<<endl<<endl<<endl;

        plik[k].close();
    }

    return 0;
}


//cout<<(double)(stop-start)/(double)CLOCKS_PER_SEC<<" ";
        //x=(stop-start)/CLOCKS_PER_SEC;
        //plik[k]<<x<<","<<((double)(stop-start)/(double)CLOCKS_PER_SEC-x)*1000<<" ";
