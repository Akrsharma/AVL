#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
class Node{
    int data;
    Node *lchild;
    Node *rchild;
    public:
    Node(int data){
        this->data = data;
        lchild = NULL;
        rchild = NULL;
    }
    int getData(){
        return data;
    }
    void setData(int data){
        this->data = data;
    }
    Node *getLeftChild(){
        return lchild;
    }
    Node *getRightChild(){
        return rchild;
    }
    void setLeftChild(Node *lchild){
        this->lchild = lchild;
    }
    void setRightchild(Node *rchild){
        this->rchild = rchild;
    }
};

class Tree{
    
    Node *root = NULL;
    Node *createTree1(vector<int>, int, int);
    public:
    void createTree(vector<int>,int, int);
    void preOrder(Node *);
    void inOrder(Node *);
    void sequencePrint();
};
void Tree :: createTree(vector<int> inarr, int left, int right){
    root = createTree1(inarr,left,right);

}
Node* Tree :: createTree1(vector<int> inarr,int left, int right){
    if(left == right){
        Node *node = new Node(inarr[left]);
        return node;
    }
    if(left>right) return NULL;
    int mid = (left+right)/2;
    Node *node = new Node(inarr[mid]);
    node->setRightchild(createTree1(inarr,mid+1,right));
    node->setLeftChild(createTree1(inarr,left,mid-1));
    return node;
}
void Tree :: sequencePrint(){
    Node *tmp = root;
    queue <Node *> q;
    q.push(tmp);
    //cout<<(q.front())->data<<"\n";
    while(!q.empty()){
        Node *tmp1 = q.front();
        cout<<tmp1->getData()<<"\n";
        if(tmp1->getRightChild()) q.push(tmp1->getRightChild());
        if(tmp1->getLeftChild()) q.push(tmp1->getLeftChild());
        q.pop();
    }
}
/*void Tree :: preOrder(Node *tmp){
	if(tmp){
		cout<<tmp->data<<" ";
		preOrder(tmp->lchild);
		preOrder(tmp->rchild);
	}
}
void Tree :: inOrder(Node *tmp){
	if(tmp){	
		inOrder(tmp->lchild);
		cout<<tmp->data<< " ";
		inOrder(tmp->rchild);
	}
}*/
int main(){
    int data;
    vector<int> v;
    int len = 0,i=0;
    while(cin>>data){
        v.push_back(data);
    }
    sort(v.begin(),v.end());
    Tree t;
    t.createTree(v,0,v.size() - 1);
    /*t.preOrder(t.root);
    cout<<"\n";
    t.inOrder(t.root);
    cout<<"\n";*/
    t.sequencePrint();
    return 0;
}