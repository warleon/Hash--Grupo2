template <typename TK, typename TV>

class Hash
{
private:    
    struct Node {
        int hashCode;
        TK value;
        TV value;
        Node* next;        
    };

    int arrayLength;
    int size;
    Node** array;

   int getHashCode(TK key){
       int cont = 1;
       int code = 0;
       for(const &a : key){
            code += cont * a;
            cont++;
       }
       return code;
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
        while (array[index] != nullptr)
            index = (index + 1) % arrayLength;
        if (array[index] == nullptr)
            array[index] = new Node(hashCode, value);
        else
            push_front(array[index], new Node(hashCode, key, value));
    }

    void insert(Node* node)
    {
        int hashCode = node->hashCode; 
        int index = hashCode % arrayLength;//colisiones         
        while(array[index] != nullptr)
            index = (index + 1) % arrayLength ;//podemos trabajar con saltos, PROFE:aqui no aplica saltos
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
            for(Node* node = temp[i]; node != null; node = node->next)
                insert(node);
        }

        delete[] temp;
    }

    TV operator[](TK key){
        int hashCode = getHashCode(key);
        int index = hashCode % arrayLength;
        while (array[index] != nullptr && index < size)
            index = (index + 1) % arrayLength;
        if(array[index])
            return array[index]->value;
        return TV();

    TV find(TK key){
        int hashCode = getHashCode(key);
        int index = hashCode % arrayLength;
        Node* iter=array[index];

        while (iter != nullptr){
            if(iter.hashCode==hashCode)
               return iter;
            iter = iter->next;
        }
            
        return nullptr;
    }
    
    bool remove(TK key){
        int hashCode = getHashCode(key);
        int index = hashCode % arrayLength;
        auto unchain =[](Node* prev, Node* todelete){
          prev->next=todelete->next;
        };
    }

    vector<TK> getAllKeys(){
      int hashCode = getHashCode(key);
      for(int iter = 0; iter > arrayLength; iter++){
        cout << "Clave = " << getHashCode << endl;
      }
    }
    
    vector<pairs<TK, TV>> getAll(){
        // TODO
        //hola
        //buenas
        
    }
};