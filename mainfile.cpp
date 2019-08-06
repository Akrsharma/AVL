#include<iostream>
using namespace std;

class Node{
    int data;
    Node* lchild;
    Node* rchild;
    int hit;
    public:
    Node(int data){
        this->data = data;
        this->lchild = NULL;
        this->rchild = NULL;
        this->hit = 0;
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
	void setRightChild(Node *rchild){
		this->rchild = rchild;
	}
	void setLeftChild(Node *lchild){
		this->lchild = lchild;
	}
	int getHeight(){
		return hit;
	}
	void setHeight(int hit){
		this->hit = hit;
	}


};

class AVLTree{
    Node *root = NULL;
    int size = 0;
    Node *insertNode(Node *,int);
	int height(Node *);
	int balanceFactor(Node *);
	Node *LeftRotate(Node *);
	Node *RightRotate(Node*);
    public:
    void insertNode(int);
    void searchNode(int);
    int heightAVL();
};
void AVLTree :: insertNode(int data){
	root = insertNode(root,data);
    


}

Node * AVLTree :: RightRotate(Node *tmp){
	Node *tmp1 = tmp->getLeftChild()->getRightChild();
	Node *tmp2 = tmp->getLeftChild();
	tmp->getLeftChild()->setRightChild(tmp);
	tmp->setLeftChild(tmp1);
	tmp->setHeight(max(height(tmp->getLeftChild()),height(tmp->getRightChild()))+1);
	tmp2->setHeight(max(height(tmp->getLeftChild()),height(tmp->getRightChild()))+1);
	return tmp2; 
}
Node * AVLTree :: LeftRotate(Node *tmp){
	Node *tmp1 = tmp->getRightChild();
	Node *tmp2 = tmp->getRightChild()->getLeftChild();
	tmp->setRightChild(tmp2);
	tmp1->setLeftChild(tmp);
	tmp->setHeight(max(height(tmp->getLeftChild()),height(tmp->getRightChild()))+1);
	tmp1->setHeight(max(height(tmp->getLeftChild()),height(tmp->getRightChild()))+1);
	return tmp1;
}

Node * AVLTree :: insertNode(Node *tmp, int data){
    if(tmp == NULL){
        Node *node = new Node(data);
		return node;
    }
    if(data < tmp->getData()) tmp->setLeftChild(insertNode(tmp->getLeftChild(),data));
    else if(data > tmp->getData())  tmp->setRightChild(insertNode(tmp->getRightChild(),data));
	else return tmp;
	tmp->setHeight(max(height(tmp->getLeftChild()),height(tmp->getRightChild()))+1);
	//Get the balance factor of this ancestor node to check whether this node became unbalanced or not
	int balance = balanceFactor(tmp);
	if(balance <= 1 && balance >= -1) return tmp;
	//Node *tmp1 = tmp->getLeftChild();
	if(tmp->getLeftChild() && (height(tmp->getLeftChild())>height(tmp->getRightChild()))){
		//LL rotation
		tmp = RightRotate(tmp);
	}
	else if(tmp->getLeftChild() && (height(tmp->getLeftChild()) < height(tmp->getRightChild()))){
		//LR rotation
		tmp->setLeftChild(LeftRotate(tmp->getLeftChild()));
		tmp = RightRotate(tmp);
	}
	else if(tmp->getRightChild() && (height(tmp->getLeftChild()) < height(tmp->getRightChild()))){
		//RR rotation
		tmp = LeftRotate(tmp);
	}
	else if(tmp->getRightChild() && (height(tmp->getLeftChild()) > height(tmp->getRightChild()))){
		//RL roation
		tmp->setLeftChild(RightRotate(tmp->getRightChild()));
		tmp = LeftRotate(tmp);
	}
	
	return tmp;
}
int AVLTree :: balanceFactor(Node *tmp){
	return (height(tmp->getLeftChild()) - height(tmp->getRightChild()));
}
int AVLTree :: height(Node *tmp){
	if(tmp == NULL) return 0;
	else return tmp->getHeight();
}
int AVLTree :: heightAVL(){
	return height(root);
}
int main(){
    AVLTree t;
	int option;
	int data;
	int height;
	while(1){
		cout<<"Select your operation on BST: \n";
		cout<<"1. Insert an element in BST \n";
		cout<<"2. Search for an element in BST \n";
		cout<<"3. Delete an element from BST \n";
		cout<<"4. Height of BST \n";
		cout<<"5. Pre Order Travesal of the BST \n";
		cout<<"6. In Order Traversal of the BST \n";
		cout<<"7. Post Order Traversal of the BST \n";
		//cout<<"9. In Order Traversal of the BST \n";
		cout<<"8. Delete BST completely \n";
		cout<<"9. Quit \n";
		cin>>option;
		switch (option)
		{
		case 1: /* Inserting an element in BST*/
			cout<<"Enter an element to insert : ";
			cin>>data;
			
			t.insertNode(data);
			cout<<"Data inserted Successfully."<<endl;
			break;
		case 2 /* constant-expression */:
			/* code */
			cout<<"Enter an element to search : ";
			cin>>data;
			//t.searchNode(data);
			break;
		case 3 /* constant-expression */:
			/* code */
			cout<<"Enter an element to delete : ";
			cin>>data;
			//t.deleteNode(data);
			break;
		case 4 /* constant-expression */:
			/* code */
			height = t.heightAVL();
			cout<<"The height of the BST is : "<<height<<"\n";
			break;
		case 5 /* constant-expression */:
			//t.preOrder();
			break;
		case 6 /* constant-expression */:
			/* code */
			//t.inOrder();
			break;
		case 7 /* constant-expression */:
			/* code */
			//t.postOrder();
			break;
		case 8 /* constant-expression */:
			/* code */
			//t.deleteBSTTree();
			break;
		case 9 /* constant-expression */:
			/* code */
			cout<<"Run the program again to work on BST.\n";
			return 0;
			break;
		default:
			break;
		}
	}
	return 0;
}