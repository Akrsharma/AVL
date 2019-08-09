#include<iostream>
using namespace std;

class Node{
    int data;
    Node* lchild;
    Node* rchild;
	Node *parent;
    int hit;
    public:
    Node(int data){
        this->data = data;
        this->lchild = NULL;
        this->rchild = NULL;
		this->parent = NULL;
        this->hit = 0;
    }
    int getData(){
		return data;
	}
	void setData(int data){
		this->data = data;
	}
	Node *getParent(){
		return parent;
	}
	void *setParent(Node *parent){
		this->parent = parent;
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
	void preOrder(Node *);
	void inOrder(Node *);
	Node * searchNode(Node *,int );
	Node *deleteNode(Node *, int);
	Node *minValueRightSubTree(Node *);
    public:
    void insertNode(int);
    void searchNode(int);
    int heightAVL();
	void preOrder();
	void inOrder();
	void deleteNode(int );
};

void AVLTree :: preOrder(){
	preOrder(root);
}
void AVLTree :: preOrder(Node *tmp){
	if(tmp){
		cout<<tmp->getData()<<" ";
		preOrder(tmp->getLeftChild());
		preOrder(tmp->getRightChild());
	}
}
void AVLTree :: inOrder(){
	inOrder(root);
}
void AVLTree :: inOrder(Node *tmp){
	if(tmp){
		
		inOrder(tmp->getLeftChild());
		cout<<tmp->getData()<<" ";
		inOrder(tmp->getRightChild());
	}
}
void AVLTree :: insertNode(int data){
	root = insertNode(root,data);
    


}

Node * AVLTree :: RightRotate(Node *tmp){
	Node *tmp1 = tmp->getLeftChild();
	Node *tmp2 = tmp->getLeftChild()->getRightChild();
	tmp1->setRightChild(tmp);
	tmp->setLeftChild(tmp2);
	tmp->setHeight(max(height(tmp->getLeftChild()),height(tmp->getRightChild()))+1);
	tmp1->setHeight(max(height(tmp1->getLeftChild()),height(tmp1->getRightChild()))+1);
	
	return tmp1; 
}
Node * AVLTree :: LeftRotate(Node *tmp){
	Node *tmp1 = tmp->getRightChild();
	Node *tmp2 = tmp->getRightChild()->getLeftChild();
	tmp->setRightChild(tmp2);
	tmp1->setLeftChild(tmp);
	tmp->setHeight(max(height(tmp->getLeftChild()),height(tmp->getRightChild()))+1);
	tmp1->setHeight(max(height(tmp1->getLeftChild()),height(tmp1->getRightChild()))+1);
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
	cout<<tmp->getData()<<" "<<balance<<endl;
	if(balance <= 1 && balance >= -1) return tmp;
	//Node *tmp1 = tmp->getLeftChild();
	if(balance >1 && data < tmp->getLeftChild()->getData()){
		//LL problem
		cout<<"LL rotation\n";
		tmp = RightRotate(tmp);
	}
	else if(balance > 1 && data > tmp->getLeftChild()->getData()){
		//LR problem
		cout<<"LR problemn\n";
		tmp->setLeftChild(LeftRotate(tmp->getLeftChild()));
		tmp = RightRotate(tmp);
	}
	else if(balance < -1 && data > tmp->getRightChild()->getData()){
		//RR problem
		cout<<"RR Problem\n";
		tmp = LeftRotate(tmp);
	}
	else if(balance < -1 && data < tmp->getRightChild()->getData()){
		//RL problem
		cout<<"RL problem\n";
		tmp->setRightChild(RightRotate(tmp->getRightChild()));
		tmp = LeftRotate(tmp);
	}
	
	return tmp;
}
int AVLTree :: balanceFactor(Node *tmp){
	int leftheight = 0, rightheight = 0;
	leftheight = height(tmp->getLeftChild())+1;
	rightheight = height(tmp->getRightChild())+1;
	return leftheight - rightheight;
}
int AVLTree :: height(Node *tmp){
	if(tmp == NULL) return -1;
	else return tmp->getHeight();
}
int AVLTree :: heightAVL(){
	return height(root);
}

void AVLTree :: deleteNode(int data){
	root = deleteNode(root,data);
	//cout<<node->getData()<<endl;
	cout<<"Deletion Done SuccessFully"<<endl;
	

}
Node *AVLTree :: deleteNode(Node *tmp,int data){
	if(tmp == NULL)return NULL;
	if(data < tmp->getData()) tmp->setLeftChild(deleteNode(tmp->getLeftChild(),data));
	else if(data > tmp->getData()) tmp->setRightChild(deleteNode(tmp->getRightChild(),data));
	else{
		if(!tmp->getLeftChild() && !tmp->getRightChild()){
			delete(tmp);
			tmp = NULL;
			return tmp;
		}
		else if(tmp->getLeftChild() && tmp->getRightChild()){
			Node *node = minValueRightSubTree(tmp->getRightChild());
			int n = tmp->getData();
			tmp->setData(node->getData());
			node->setData(n);
			tmp->setRightChild(deleteNode(tmp->getRightChild(),data));
		}
		else{
			Node *tmplchild = tmp->getLeftChild();
			Node *tmprchild = tmp->getRightChild();
			delete(tmp);
			tmp = NULL;
			if(tmplchild) return tmplchild;
			else return tmprchild;
		}
	}

	tmp->setHeight(max(height(tmp->getLeftChild()),height(tmp->getRightChild()))+1);
	//Get the balance factor of this ancestor node to check whether this node became unbalanced or not
	int balance = balanceFactor(tmp);
	cout<<tmp->getData()<<" "<<balance<<endl;
	if(balance <= 1 && balance >= -1) return tmp;
	//Node *tmp1 = tmp->getLeftChild();
	if(balance >1 && (height(tmp->getLeftChild())>=height(tmp->getRightChild()))){
		//LL problem
		cout<<"LL rotation\n";
		tmp = RightRotate(tmp);
	}
	else if(balance > 1 && (height(tmp->getLeftChild())<height(tmp->getRightChild()))){
		//LR problem
		cout<<"LR problemn\n";
		tmp->setLeftChild(LeftRotate(tmp->getLeftChild()));
		tmp = RightRotate(tmp);
	}
	else if(balance < -1 && (height(tmp->getLeftChild()) <= height(tmp->getRightChild()))){
		//RR problem
		cout<<"RR Problem\n";
		tmp = LeftRotate(tmp);
	}
	else if(balance < -1 && (height(tmp->getLeftChild()) > height(tmp->getRightChild()))){
		//RL problem
		cout<<"RL problem\n";
		tmp->setRightChild(RightRotate(tmp->getRightChild()));
		tmp = LeftRotate(tmp);
	}
	
	return tmp;
} 
Node *AVLTree :: minValueRightSubTree(Node *tmp){
	while(tmp->getLeftChild()) tmp = tmp->getLeftChild();
	return tmp;
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
			t.deleteNode(data);
			break;
		case 4 /* constant-expression */:
			/* code */
			height = t.heightAVL();
			cout<<"The height of the BST is : "<<height<<"\n";
			break;
		case 5 /* constant-expression */:
			t.preOrder();
			cout<<"\n";
			break;
		case 6 /* constant-expression */:
			/* code */
			t.inOrder();
			cout<<"\n";
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