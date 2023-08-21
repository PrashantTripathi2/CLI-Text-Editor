struct Node{
    char *text;
    int line;
	int type;
	Node *next;
};
class Stack{
	private:
		Node *head;
		int top;
	public:
		Stack();
		void push(Node*);
		Node* pop(void);
		int Top(void);
		void empty(void);
		void show(void);
};
Stack::Stack(){
	this->head=NULL;
	this->top=0;
}
void Stack::push(Node* node){
	this->top++;
	if(this->head==NULL){
		this->head=node;
	}
	else{
		node->next=this->head;
		this->head=node;
	}
}
Node* Stack::pop(void){
	if(this->head==NULL) return this->head;
	top--;
	Node *t=this->head;
	this->head=this->head->next;
	t->next=NULL;
	return t;
}
int Stack::Top(void){
	return top;
}
void Stack::empty(void){
	Node* t;
	while((t=this->pop())!=NULL){
		delete []t->text;
		delete t;
	}
}
void Stack::show(void){
	Node *node;
	Stack tmp;
	while((node = this->pop())!=NULL){
	    tmp.push(node);
	}
	while((node = tmp.pop())!=NULL){
		cout<<node->text<<endl;
		this->push(node);
	}
}