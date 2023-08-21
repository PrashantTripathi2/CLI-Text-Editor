#include "Stack.cpp"
#define INSERT 1
#define DELETE 2
#define APPEND 3
#define UPDATE 4

char* Text(char* text){
	int l;
	for(l=0;text[l]!='\0';l++);
	char *str = new char[l+1];
	for(int i=0;i<l;i++){
		str[i]=text[i];
	}
	str[l]='\0';
	return str;
}

char* concat(char *s1,char *s2){
	int l1,l2;
	for(l1=0;s1[l1]!='\0';l1++);
	for(l2=0;s2[l2]!='\0';l2++);
	char *str = new char[l1+l2+1];
	int k=0;
	for(int i=0;i<l1;i++){
		str[k]=s1[i];
		k++;
	}
	for(int i=0;i<l2;i++){
		str[k]=s2[i];
		k++;
	}
	str[k]='\0';
	return str;
}

Node* createNode(char *text,int line,int type){
	Node *node = new Node;
	node->text = text==NULL?NULL:Text(text);
	node->line = line;
	node->type = type;
	node->next = NULL;
	return node;
}

Stack Line,Undo,Redo;

void insert(char *text){
	Node *node = createNode(text,Line.Top()+1,INSERT);
	Node *undo = createNode(NULL,Line.Top()+1,INSERT);
	Line.push(node);
	Undo.push(undo);
	Redo.empty();
}

void update(int line,char *text){
	if(line>0&&line<=Line.Top()){
		Stack tmp;
		Node *node = createNode(text,line,INSERT);
		Node *t;
		line=Line.Top()-line;
		for(int i=0;i<line;i++){
			tmp.push(Line.pop());
		}
		t=Line.pop();
		t->type=UPDATE;
		Undo.push(t);
		Line.push(node);
		while((node=tmp.pop())!=NULL){
			Line.push(node);
		}
		Redo.empty();
	}
}

void append(char *text,int line){
	if(line>0&&line<=Line.Top()){
		Stack tmp;
		int tmp_line=line;
		line=Line.Top()-line;
		for(int i=0;i<line;i++){
			tmp.push(Line.pop());
		}
		Node *t = Line.pop();
		t->type=APPEND;
		Undo.push(t);
		Node *node = createNode(concat(t->text,text),tmp_line,INSERT);
		Line.push(node);
		while((node=tmp.pop())!=NULL){
			Line.push(node);
		}
		Redo.empty();
	}
}

void _delete(int line){
	if(line>0&&line<=Line.Top()){
		Stack tmp;
		int tmp_line = line;
		line=Line.Top()-line;
		for(int i=0;i<line;i++){
			Node *node = Line.pop();
			node->line--;
			tmp.push(node);
		}
		Node *node = Line.pop();
		node->type=DELETE;
		Undo.push(node);
		while((node=tmp.pop())!=NULL){
			Line.push(node);
		}
		Redo.empty();
	}
}

void save(char *name){
	FILE *fp = fopen(name,"w");
	Stack tmp;
	Node *node;
	while((node=Line.pop())!=NULL){
		tmp.push(node);
	}
	while((node=tmp.pop())!=NULL){
		Line.push(node);
		fwrite(node->text,sizeof(char),strlen(node->text),fp);
		putc('\n',fp);
	}
	fclose(fp);
}

void display(){
	cout<<"\n--------------------------------------------\n";
	Line.show();
	cout<<"----------------------------------------------\n";
}

void _undo(){
	Node *node = Undo.pop();
	if(node==NULL) return ;
	if(node->type==INSERT){
		Node *n1 = Line.pop();
		n1->type=INSERT;
		Redo.push(n1);
		delete node;
	}
	else if(node->type==UPDATE||node->type==APPEND){
		int line = Line.Top()-node->line;
		Stack tmp;
		for(int i=0;i<line;i++){
			tmp.push(Line.pop());
		}
		Node *n1 = Line.pop();
		n1->type=node->type==UPDATE?UPDATE:APPEND;
		Redo.push(n1);
		node->type=INSERT;
		Line.push(node);
		while((node=tmp.pop())!=NULL){
			Line.push(node);
		}
	}
	else if(node->type==DELETE){
		int line = Line.Top()-node->line+1;
		Stack tmp;
		for(int i=0;i<line;i++){
			Node *n = Line.pop();
			n->line++;
			tmp.push(n);
		}
		node->type=INSERT;
		Node *n = node;
		Line.push(node);
		while((node=tmp.pop())!=NULL){
			Line.push(node);
		}
		n = createNode(NULL,n->line,DELETE);
		Redo.push(n);
	}
}

void _redo(){
	Node *node = Redo.pop();
	if(node==NULL) return ;
	if(node->type==INSERT){
		Line.push(node);
		Node *n = createNode(NULL,node->line,INSERT);
		Undo.push(n);
	}
	else if(node->type==UPDATE||node->type==APPEND){
		int line = Line.Top()-node->line;
		Stack tmp;
		for(int i=0;i<line;i++){
			tmp.push(Line.pop());
		}
		Node *n1 = Line.pop();
		n1->type=node->type==UPDATE?UPDATE:APPEND;
		Undo.push(n1);
		node->type=INSERT;
		Line.push(node);
		while((node=tmp.pop())!=NULL){
			Line.push(node);
		}	
	}
	else if(node->type==DELETE){
		int line = Line.Top()-node->line;
		Stack tmp;
		for(int i=0;i<line;i++){
			Node *n = Line.pop();
			n->line--;
			tmp.push(n);
		}
		Node *n = Line.pop();
		n->type=DELETE;
		while((node=tmp.pop())!=NULL){
			Line.push(node);
		}
		Undo.push(n);
		delete node;
	}
}