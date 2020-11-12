#include <vector>
#include <string>
#include <utility>

template <typename TK, typename TV>
class Hash{
private:    
    struct Node {
        int hashCode;
        TK key;
        TV value;
        Node* next;        
		Node(int code,TK k,TV v):hashCode(code),key(k),value(v){}
    };

    int arrayLength;
    Node** array;

   int getHashCode(std::string key){
       int cont = 1;
       int code = 0;
       for(const auto &a : key){
            code += cont * a;
            cont++;
       }
       return code;
   }

   void push_front(Node*& front, Node* newfront){
        newfront->next=front;
        front=newfront;
   }

public:
    Hash(int _length)
    {
        arrayLength = _length;
        array = new Node*[arrayLength];
        for (int i = 0; i < arrayLength; i++)
            array[i] = nullptr;
    }

    void insert(TK key, TV value)
    {
        int hashCode = getHashCode(key);    //funcion hash
        int index = hashCode % arrayLength; //colisiones
        if (array[index] == nullptr)
            array[index] = new Node(hashCode,key,value);
        else
            push_front(array[index], new Node(hashCode, key, value));
    }

    void insert(Node* node)
    {
        int hashCode = node->hashCode; 
        int index = hashCode % arrayLength;//colisiones         
        node->next = nullptr;
        if (array[index] == nullptr)
            array[index] = node;
        push_front(array[index], node);
    }

    void rehashing()
    {
        int tempL = arrayLength;
        Node** temp = array;      

        arrayLength = arrayLength * 2;
        array = new Node*[arrayLength];
        for(int i=0;i<arrayLength;i++)
            array[i] = nullptr;

        for (int i = 0; i < tempL; i++)
        {            
            for(Node* node = temp[i]; node != nullptr; node = node->next)
                insert(node);
        }

        delete[] temp;
    }

    TV operator[](TK key){
        int hashCode = getHashCode(key);
        int index = hashCode % arrayLength;
        Node* iter=array[index];
        while (iter != nullptr){
            if(iter->hashCode==hashCode)
               return iter->value;
            iter = iter->next;
        }
	}

    TV find(TK key){
        int hashCode = getHashCode(key);
        int index = hashCode % arrayLength;
        Node* iter=array[index];

        while (iter != nullptr){
            if(iter->hashCode==hashCode)
               return iter->value;
            iter = iter->next;
        }
            
        return nullptr;
    }
    
    bool remove(TK key){
		int hashCode = getHashCode(key);
        int index = hashCode % arrayLength;
        auto unchain =[](Node* prev, Node*& todelete){
          prev->next=todelete->next;
          todelete->next=nullptr;
          delete todelete;
          todelete = nullptr;
        };
        Node* iter=array[index];

        while (iter->next != nullptr){
            if((iter->next).hashCode==hashCode){
                unchain(iter,iter->next);
                return true;
            }
        }
        return false;
	}

	std::vector<TK> getAllKeys(){
		std::vector<TK> result;
		for (int i = 0; i < arrayLength; i++){
			for(Node* node = array[i]; node != nullptr; node = node->next)
				result.push_back(node->key);
		}
		return result;
    }
    
	std::vector<std::pair<TK, TV>> getAll(){
		std::vector<std::pair<TK, TV>> result;
		for (int i = 0; i < arrayLength; i++){
			for(Node* node = array[i]; node != nullptr; node = node->next)
				result.push_back(std::make_pair(node->key,node->value));
		}
		return result;
    }
};
