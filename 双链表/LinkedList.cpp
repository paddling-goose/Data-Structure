#include<iostream>
using namespace std;

enum Error_code{underflow, overflow, success, Range_error};

/*该list的头节点存储数据*/

template<typename List_entry>
class List{
    private:

        struct Node{
            Node();
            Node(const List_entry& item, Node* add_on_1 = nullptr, Node* add_on_2 = nullptr)
                : next(add_on_1), back(add_on_2), data(item) {}  // 与声明顺序一致

            Node* next;
            Node* back;
            List_entry data;
        };

    public:
        List(): count(0),head(nullptr){} ;
        List(List & mylist) { *this = mylist; } ;
        ~List () { clear(); };

        List& operator = (const List & copy);

        void clear();
        int size() const { return count; }
        bool full() const { return false; }
        bool empty() const { return count == 0; }
        void traverse( void (*visit)(List_entry &) );
  
        Error_code insert (int position, const List_entry & x);
        Error_code remove(int position, List_entry & x);
        Error_code replace(int position, const List_entry & x);
        Error_code retrieve(int position, List_entry &x) const;
     

    protected:

        int count; //记录结点数
        Node* head; //头节点，代表序列的开始

        Node* set_position(int position) const{   //返回所求结点的指针
            if(position <0 || position >= count) return nullptr;

            Node *cur = head;
            for(int i=0;i<position;i++){
                cur = cur->next;
            }
            return cur;
        } 

};

template<typename List_entry>
List<List_entry>& List<List_entry> :: operator = (const List & copy)
{

    if( this ==&copy){
        return *this;
    }

    clear();

    Node* src = copy.head;
    Node* prev = nullptr;

    while(src != nullptr){
        Node* new_node = new Node(src->data, nullptr, prev);

        if(prev == nullptr){
            head = new_node;
        }else{
            prev->next = new_node;
        }

        prev = new_node;
        src = src->next;
    }

    count = copy.count;

    return *this;

};

template<typename List_entry>
void List<List_entry> :: clear(){
    Node* cur = head;
    while(cur != nullptr){
        Node * next = cur->next;
        delete cur;
        cur = next;
    }
    head = nullptr; //必须将head置空
    count = 0;
};

template<typename List_entry>
Error_code List<List_entry> :: insert (int position, const List_entry & x){
    if(position <0 || position > count) return Range_error;

    if(position == 0){
        Node* new_node = new Node(x,head,nullptr);
        if (head != nullptr) head->back = new_node;   //处理没有元素的情况
        head = new_node;
    }else if(position == count){
            Node* last = set_position(count - 1); // 最后一个节点
            Node* new_node = new Node(x, nullptr, last);
            if(last) last->next = new_node;
            else head = new_node; // 空链表
    }else{
        Node* cur = set_position(position);
        Node* prev = cur->back;
        Node* new_node = new Node(x,cur,prev);
        prev->next = new_node;
        cur->back = new_node;
    }

    count ++;

    return success;
}

template<typename List_entry>
Error_code List<List_entry> :: remove(int position, List_entry & x){
    if(position <0 || position >= count) return Range_error;

    Node *cur = set_position(position);
    Node *prev = cur->back;

    if(position == 0){
        head = cur->next;
        if (head != nullptr) head->back = nullptr;
    }else if(position == count-1){
        prev->next = nullptr;
    }else{
        prev->next = cur->next;
        (cur->next)->back = prev;
    }

    x = cur->data;
    delete cur;
    count --;
    return success;
}


template<typename List_entry>
Error_code List<List_entry> :: replace(int position, const List_entry & x){
    if(position <0 || position >= count) return Range_error;

    Node *cur = set_position(position);
    cur->data = x;
    return success;
}


template<typename List_entry>
Error_code List<List_entry> :: retrieve(int position, List_entry &x) const{
    if(position <0 || position >= count) return Range_error;

    Node *cur = set_position(position);
    x = cur->data;
    return success;
}

template<typename List_entry>
void List<List_entry>::traverse(void (*visit)(List_entry&)) {
    Node* cur = head;
    while (cur != nullptr) {
        visit(cur->data);
        cur = cur->next;
    }
}

