#include<iostream>

enum Error_code {success, overflow, underflow, Range_error};
using namespace std;

template <typename List_entry>
class List;

template <typename Node_entry>
struct Node{
//data members
    Node_entry entry;
    Node* next;
    Node* back;
//constructors
    Node();
    Node(Node_entry item, Node* add_on1 = nullptr, Node* add_on2 = nullptr);
};


template <typename List_entry>
class List{   
    using NodePtr = Node<List_entry>*;

public:
    ~List();
    List();  //直接生成实例
    List(const List<List_entry> &copy); //通过复制列表生成实例
    int size() const;
    void operator = (const List & copy);
    bool full() const;
    bool empty() const;
    void clear();
    void traverse(void (*visit)(List_entry &));
    Error_code retrieve(int position, List_entry &x) const;
    Error_code replace(int position, const List_entry &x);
    Error_code remove(int position, List_entry &x);
    Error_code insert(int position, const List_entry &x);

protected:
    int count;
    NodePtr head;

    NodePtr set_position(int position) const;
    mutable int current_position;
    mutable NodePtr current;
};

template <typename Node_entry>
Node<Node_entry>:: Node(){
    next = nullptr;
    back = nullptr;
}

template <typename Node_entry>
Node<Node_entry>:: Node(Node_entry item, Node*add_on1, Node* add_on2){
    entry = item;
    next = add_on1;
    back = add_on2;
}

template <typename List_entry>
List<List_entry> :: List (){
    count = 0;
    head = new Node<List_entry>();
    current_position = 0;   //position_0 == head
    current = nullptr;
}

template <typename List_entry>
Node<List_entry> *List<List_entry> :: set_position (int position) const{
/*Pre: position is a valid position in the list; 0 <= position < count
  Post：returns a pointer to the Node in position*/
    if (position < 0 || position >= count) return nullptr;

	NodePtr q = head;  
	for(int i = 0; i < position; i++)  q = q->next;
	return q; 
}

template <typename List_entry>
Error_code List<List_entry> :: insert (int position, const List_entry &x) {
    if (position <= 0 || position > count)   return Range_error;

    NodePtr new_node, previous, following;
    if(new_node = nullptr) return overflow;

    if(position ==1){
        if(head->next == nullptr){
            head->next = new_node;
            new_node->back = head;
        }else{
            following = head->next;
            head->next = new_node;
            new_node.back = head;
            new_node.next = following;
            following->back = new_node;
        }

    }else{
        following = set_position(position);
        previous = following->back;
        new_node->next = following;
        new_node.back = previous;
        following.back = new_node;
        previous.next =new_node;
    }
    
    count++;
    return success;
}

template <typename List_entry>
Error_code List<List_entry> :: remove (int position, List_entry &x) { //position 从一开始,虽然令人迷惑
    
    if (position <= 0 || position >= count)    return Range_error;

    NodePtr target = set_position(position);
    if (!target) return Range_error;  // 防止空指针访问

    NodePtr previous = target->back;
    NodePtr following = target->next;

    x = target->entry;

    if(count ==1){
        head->next = nullptr;
    }else{
        if(position ==1){
            head->next = following;
        if(position == count){
            previous->next = following;
        }
        following->back = previous;
        }
    }

    delete target;  //删除目标节点
    count--;

    return success;
}

template <typename List_entry>
int List<List_entry>:: size() const{
    return count;
}

template <typename List_entry>
bool List<List_entry> :: full()const{
    NodePtr new_node;
	new_node = new Node<List_entry>;
	if(new_node == NULL){
        return true;
    }else{
		delete new_node;
		return false;
	}
}

template <typename List_entry>
bool List<List_entry> :: empty() const{
    return count==0;
}

template <typename List_entry>
void List<List_entry> :: clear (){

    List_entry x;
    while(!empty())
        remove(0,x);
}

template <typename List_entry>
void List<List_entry> :: traverse (void(*visit)(List_entry &)){  //可以放一个函数进来!

    NodePtr p_node = head;
    while(p_node){
        (*visit)(p_node->entry);
        p_node = p_node->next;
    }
}

template <typename List_entry>
Error_code List<List_entry> :: retrieve (int position,List_entry &x) const{

	if (position <= 0 || position > count)  return Range_error;

	NodePtr p_node;

	p_node = set_position(position);
	x =p_node->entry;
	return success;
}

template <typename List_entry>
Error_code List<List_entry> :: replace(int position, const List_entry &x){

    if(position <= 0 || position >count)    return Range_error;

    NodePtr p_node;

    p_node = set_position(position);
    p_node->entry = x;
    return success;
}

template <typename List_entry>
List<List_entry> :: List (const List<List_entry> &copy){  //复制另外一个列表来生成列表
	count = 0;
	head = NULL;
	NodePtr q = copy.head;
	int i=1;
	while(q){
		insert(i,q->entry);
		q=q->next;
		i++;
	}
}

template <typename List_entry>
void List<List_entry> :: operator = (const List<List_entry> &copy){

	List_entry x;
	if(this == &copy)  return;

	while(!empty())    
        remove(0,x);

	NodePtr q = copy.head;
	int i=1;
	while(q){
		insert(i,q->entry);
		q=q->next;
		i++;
	}
}

template <typename List_entry>
List<List_entry> :: ~List( ){
	List_entry x;
	while(!empty())remove(0,x);
}

template <typename List_entry>
void update(List_entry &x){
	x*=2;	
}

template <typename List_entry>
void print(List_entry &x){
	cout<<x<<endl;	
}