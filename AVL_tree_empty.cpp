
#include <string.h>
#include <iostream>
#include <math.h>

using namespace std;

class Book {
protected:
    const char *aut_name;
    const char *aut_sername;
    const char *book_name;
    int year;
    const char *name_publishers;
    int number_of_pages;
    enum type_of_publication {electronic, paper , audio};
    int circulation;


public:
    Book() {}
    Book(const char* a_n,const char* a_sn, const char* b_n, int ye, const char* n_pub,int n_pag, /*type_of_publication type,*/ int cir) {
        aut_name=a_n;
        aut_sername=a_sn;
        book_name=b_n;
        year=ye;
        name_publishers=n_pub;
        number_of_pages=n_pag;
        /*type_of_publication = type;*/
        circulation=cir;
    }



    ~Book() { cout << "\nBook destructor"; }
    const char* getBook_name() const { return book_name; }

    friend ostream& operator<<(ostream& os, const Book& M) {
        os << "aut_name: " << M.aut_name << endl
           << "aut_sername : " << M.aut_sername << endl
           << "book_name: " << M.book_name << endl
           << "year: " << M. year << endl
           << "name_publishers: " << M.name_publishers << endl
           << "number_of_pages: " << M.number_of_pages << endl
           << "circulation: " << M.circulation << endl;
        return os;
    }
};

bool operator>(const Book& M1, const Book& M2) {
    if (strcmp(M1.getBook_name(), M2.getBook_name()) < 0)
        return true;
    return false;
}
bool operator<(const Book& M1, const Book& M2) {
    if (strcmp(M1.getBook_name(), M2.getBook_name()) > 0)
        return true;
    return false;
}
bool operator==(const Book& M1, const Book& M2) {
    if (strcmp(M1.getBook_name(), M2.getBook_name()) == 0)
        return true;
    return false;
}


template<class T>
class Node
{
protected:
    //закрытые переменные Node N; N.data = 10 вызовет ошибку
    T data;

    //не можем хранить Node, но имеем право хранить указатель
    Node* left;
    Node* right;
    Node* parent;

    //переменная, необходимая для поддержания баланса дерева
    int height;

    virtual Node<T>* Min(Node<T>* current)
    {
        while (current->getLeft() != NULL)
            current = current->getLeft();
        return current;
    }

    virtual Node<T>* Max(Node<T>* current)
    {
        while (current->getRight() != NULL)
            current = current->getRight();
        return current;
    }
public:
    //доступные извне переменные и функции
    virtual void setData(T d) { data = d; }
    virtual T getData() { return data; }
    int getHeight() { return height; }

    virtual Node* getLeft() { return left; }
    virtual Node* getRight() { return right; }
    virtual Node* getParent() { return parent; }

    virtual void setLeft(Node* N) { left = N; }
    virtual void setRight(Node* N) { right = N; }
    virtual void setParent(Node* N) { parent = N; }

    //Конструктор. Устанавливаем стартовые значения для указателей
    Node<T>(T n)
    {
        data = n;
        left = right = parent = NULL;
        height = 1;
    }

    Node<T>()
    {
        left = NULL;
        right = NULL;
        parent = NULL;
        data = 0;
        height = 1;
    }


    virtual void print()
    {
        cout << "\n" << data;
    }

    virtual void setHeight(int h)
    {
        height = h;
    }

    template<class T1> friend ostream& operator<< (ostream& stream, Node<T1>& N);

    Node* operator++()
    {
        return successor();
    }

    Node* operator++(int)
    {
        Node* temp = this;
        temp = successor();
        return temp;
    }


    Node* operator--()
    {
        return predecessor();
    }

    Node* operator--(int)
    {
        Node* temp = this;
        temp = predecessor();
        return temp;
    }


    // Если у узла нет правого потомка, то successor - это узел, у которого значение минимально и больше, чем у заданного узла
    Node* successor()
    {
        if (right != NULL)
            return Min(right);
        Node* current = parent;
        while (current != NULL && current->data < data)
            current = current->parent;
        return current;
    }

    // Если у узла нет левого потомка, то predecessor - это узел, у которого значение максимально и меньше, чем у заданного узла
    Node* predecessor()
    {
        if (left != NULL)
            return Max(left);
        if (parent == NULL) return NULL;
        Node* current = this;
        while (current->parent != NULL && current->parent->left == current)
            current = current->parent;
        return current->parent;
    }
};

template<class T>
ostream& operator<< (ostream& stream, Node<T>& N)
{
    stream << "\nNode data: " << N.data << ", height: " << N.height;
    return stream;
}
template<class T>
void print(Node<T>* N) { cout << "\n" << N->getData(); }


template<class T>
class Tree
{
protected:
	//корень - его достаточно для хранения всего дерева
	Node<T>* root;
public:
	//доступ к корневому элементу
	virtual Node<T>* getRoot() { return root; }

	//конструктор дерева: в момент создания дерева ни одного узла нет, корень смотрит в никуда
	Tree<T>() { root = NULL; }

	//функция добавления узла в дерево
	virtual Node<T>* push_R(Node<T>* N)
	{
		return push_R(N, root);
	}

	//рекуррентная функция добавления узла. Интерфейс аналогичен (добавляется корень поддерева, 
	//куда нужно добавлять узел), но вызывает сама себя - добавление в левое или правое поддерево
	virtual Node<T>* push_R(Node<T>* N, Node<T>* Current)
	{
		//не передан добавляемый узел
		if (N == NULL) return NULL;

		if (Current == NULL) Current = root;

		//пустое дерево - добавляем в корень
		if (root == NULL)
		{
			root = N;
			return root;
		}

		if (Current->getData() > N->getData())
		{
			//идем влево
			if (Current->getLeft() != NULL) return push_R(N, Current->getLeft());
			else
			{
				Current->setLeft(N);
				N->setParent(Current);
			}
		}
		if (Current->getData() < N->getData())
		{
			//идем вправо
			if (Current->getRight() != NULL) return push_R(N, Current->getRight());
			else
			{
				Current->setRight(N);
				N->setParent(Current);
			}
		}
		return N;
	}

	//функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
	virtual Node<T>* push(T value)
	{
		Node<T>* N = new Node<T>(value);
		return push_R(N);
	}

	//удаление узла
    virtual void Remove(Node<T>* N) {
        if (N == NULL) return;
        if (N == root) {
            Node<T>* left = root->getLeft();
            Node<T>* right = root->getRight();
            root = N->successor();
            root->getParent()->setLeft(root->getRight()); // Левый элемент у successor'a
            root->setParent(NULL);
            root->setLeft(left);
            root->setRight(right);
            delete N;
            return;
        }
        if (N->getLeft() == NULL && N->getRight() == NULL) {
            if (N == N->getParent()->getLeft())
                N->getParent()->setLeft(NULL);
            else
                N->getParent()->setRight(NULL);
            delete N;
        }
        else if (N->getLeft() == NULL) {
            if (N == N->getParent()->getRight())
                N->getParent()->setRight(N->getRight());
            else
                N->getParent()->setLeft(N->getRight());
            delete N;
        }
        else if (N->getRight() == NULL) {
            if (N == N->getParent()->getRight())
                N->getParent()->setRight(N->getLeft());
            else
                N->getParent()->setLeft(N->getLeft());
            delete N;
        }
        else {
            Node<T>* s = N->successor();
            N->setData(s->getData());
            Remove(s);
        }
    }

	//поиск минимума и максимума в дереве
	virtual Node<T>* Min(Node<T>* Current = NULL)
	{
		if (root == NULL)
			return NULL;

		Node<T>* current = root;

		while (current->getLeft() != NULL)
			current = current->getLeft();

		return current;
	}

	virtual Node<T>* Max(Node<T>* Current = NULL)
	{
		if (root == NULL)
			return NULL;

		Node<T>* current = root;

		while (current->getRight() != NULL)
			current = current->getRight();

		return current;
	}

	//поиск узла в дереве
	virtual Node<T>* Find(T data)
	{
		if (root == NULL) return NULL;
		return Find_R(data, root);
	}

	//поиск узла в дереве. Второй параметр - в каком поддереве искать, первый - что искать
	virtual Node<T>* Find_R(T data, Node<T>* Current)
	{
		//база рекурсии
		if (Current == NULL || Current->getData() == data) return Current;
		//рекурсивный вызов
		if (Current->getData() > data) return Find_R(data, Current->getLeft());
		if (Current->getData() < data) return Find_R(data, Current->getRight());
	}

	//три обхода дерева
	virtual void PreOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL)
			f(N);
		if (N != NULL && N->getLeft() != NULL)
			PreOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)
			PreOrder(N->getRight(), f);
	}

	//InOrder-обход даст отсортированную последовательность
	virtual void InOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL && N->getLeft() != NULL)
			InOrder(N->getLeft(), f);
		if (N != NULL)
			f(N);
		if (N != NULL && N->getRight() != NULL)
			InOrder(N->getRight(), f);
	}

	virtual void PostOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL && N->getLeft() != NULL)
			PostOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)
			PostOrder(N->getRight(), f);
		if (N != NULL)
			f(N);
	}


    void moreAndLess(T value) {
        Node<T>* node = Find(value);
        cout << "Nodes less than " << node->getData().getBook_name() << ":" << endl;
        Node<T>* prev = --(*node);
        while (prev != nullptr) {
            cout << prev->getData() << " ";
            prev = --(*prev);
        }
        cout << endl;
        cout << "Nodes greater than " << node->getData().getBook_name() << ":" << endl;
        Node<T>* next = ++(*node);
        while (next != nullptr) {
            cout << next->getData() << " ";
            next = ++(*next);
        }
        cout << endl;
    }

    Node<T>* operator[](T value) {
        return Find(value);
    }

    friend ostream& operator<<(ostream& os, Tree<T>& Tree) {
        Node<T>* node = Tree.Min();
        while (node != NULL) {
            os << node->getData() << endl;
            node = ++(*node);
        }
        return os;
    }
};

template<class T>
class AVL_Tree : public Tree<T>
{
protected:
	//определение разности высот двух поддеревьев
	int bfactor(Node<T>* p)
	{
		int hl = 0;
		int hr = 0;
		if (p->getLeft() != NULL)
			hl = p->getLeft()->getHeight();
		if (p->getRight() != NULL)
			hr = p->getRight()->getHeight();
		return (hr - hl);
	}

	//при добавлении узлов в них нет информации о балансе, т.к. не ясно, куда в дереве они попадут
	//после добавления узла рассчитываем его высоту (расстояние до корня) и редактируем высоты в узлах, где это
	//значение могло поменяться
	void fixHeight(Node<T>* p)
	{
		int hl = 0;
		int hr = 0;
		if (p->getLeft() != NULL)
			hl = p->getLeft()->getHeight();
		if (p->getRight() != NULL)
			hr = p->getRight()->getHeight();
		p->setHeight((hl > hr ? hl : hr) + 1);
	}

	//краеугольные камни АВЛ-деревьев - процедуры поворотов
	Node<T>* RotateRight(Node<T>* p) // правый поворот вокруг p
	{
		Node<T>* q = p->getLeft();
        p->setLeft(q->getRight());
        q->setRight(p);


        if (p==Tree<T>::root) Tree<T>::root=q;
        else{
            if (p->getParent()->getData() > p->getData())
            p->getParent()->setLeft(q);
            else
                p->getParent()->setRight(q);
        }
        if (p->getLeft() !=NULL) p->getLeft()->setParent(p);
        q->setParent(p->getParent());
        p->setParent(q);



		fixHeight(p);
		fixHeight(q);
		return q;
	}

	Node<T>* RotateLeft(Node<T>* q) // левый поворот вокруг q
	{
		Node<T>* p = q->getRight();
        q->setRight(p->getLeft());
        p->setLeft(q);



        if (q==Tree<T>::root) Tree<T>::root=p;
        else{
            if (q->getParent()->getLeft()==q)
                q->getParent()->setLeft(p);
            else
                q->getParent()->setRight(p);
        }
        if (q->getLeft() !=NULL) q->getLeft()->setParent(q);
        p->setParent(q->getParent());
        q->setParent(p);


		fixHeight(q);
		fixHeight(p);
		return p;
	}

	//балансировка поддерева узла p - вызов нужных поворотов в зависимости от показателя баланса
	Node<T>* Balance(Node<T>* p) // балансировка узла p
	{
		fixHeight(p);
		if (bfactor(p) == 2)
		{
            if (bfactor(p->getRight())<0) RotateRight(p->getRight());
            return RotateLeft(p);
		}
		if (bfactor(p) == -2)
		{
            if (bfactor(p->getLeft())>0) RotateLeft(p->getLeft());
            return RotateRight(p);
		}

		return p; // балансировка не нужна
	}

public:
	//конструктор AVL_Tree вызывает конструктор базового класса Tree
	AVL_Tree<T>() : Tree<T>() {}

	virtual Node<T>* push_R(Node<T>* N)
	{
		return push_R(N, Tree<T>::root);
	}

	//рекуррентная функция добавления узла. Устроена аналогично, но вызывает сама себя - добавление в левое или правое поддерево
	virtual Node<T>* push_R(Node<T>* N, Node<T>* Current)
	{
		//вызываем функцию push_R из базового класса
		Node<T>* pushedNode = Tree<T>::push_R(N, Current);
		//применяем к добавленному узлу балансировку
		if (Current != NULL)
			return Balance(Current);
		return pushedNode;
	}

	//функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
	virtual Node<T>* push(T n)
	{
		Node<T>* N = new Node<T>;
		N->setData(n);
		return push_R(N);
	}

	//удаление узла
    virtual void Remove(Node<T>* N) {
        if (N == NULL) return;
        Tree<T>::Remove(N);
        Balance(*this->getRoot());
    }
};


int main()
{//Удаление у AVl , enum, переделай main
	/*AVL_Tree<double> T1;
	int arr[15];
	int i = 0;
	for (i = 0; i < 15; i++) arr[i] = (int)(100 * cos(15 * double(i)));
	for (i = 0; i < 15; i++) T1.push(arr[i]);

	Node<double>* M = T1.Min();
	cout << "\nMin = " << M->getData() << "\tFind " << arr[3] << ": " << T1.Find(arr[3]);
	//Node<double>* node_52 = T.Find(arr[3]);
	//cout << "\nSuccessor(52) = " << *(node_52->successor());
	//cout << "\n52 = " << *(node_52->successor()->predecessor());

    while (M != NULL)
    {
        cout << *M; M = M->successor();
    }
    M = T1.Max();
    cout << "\n-----\n";
    while (M != NULL)
    {
        cout << *M; M = M->predecessor();
    }*/


	//void (*f_ptr)(Node<double>*); f_ptr = print;
	/*cout << "\n-----\nPreorder:";
	T.PreOrder(T.getRoot(), f_ptr);*/
	//cout << "\n-----\nInorder:";
	//T1.InOrder(T1.getRoot(), f_ptr);
	/*cout << "\n-----\nPostorder:";
	T.PostOrder(T.getRoot(), f_ptr);*/

    Tree<double> T;
    T.push(15); T.push(2); T.push(1); T.push(6); T.push(7); T.push(4); T.push(5);
    T.push(18); T.push(17); T.push(20); T.push(19);
    Node<double>* N = T.Find(15);
    cout << T;
    T.Remove(N);
    cout << T.getRoot()->getLeft()->getData();
    Tree<Book> T2;
    Book arr1[5];
    arr1[0] = Book("Pavel", "Byev", "Codabra", 1994, "Avito", 2139,313542341);
    arr1[1] = Book("Parot", "Trushin", "Sholkovo", 2000, "OZON", 2139,313542341);
    arr1[2] = Book("Mihail", "Abramovich", "postypashki", 2004, "Yandex", 333339,317368233);
    arr1[3] = Book("Genadiy", "Roshrov", "cric", 1980, "Tinkoff", 3249,999932341);
    arr1[4] = Book("Igor", "Dobronravov", "Idiot", 2012, "Sber", 1119,645382341);
    for (int i = 0; i < 5; i++) T2.push(arr1[i]);


    Node<Book>* M = T2.Min();
    cout << T2.Find(arr1[3])->getData() << endl;
    cout << T2.Max()->getData() << endl;
    cout << T2.Min()->getData() << endl;
    T2.Remove(M);
    cout << T2.getRoot()->getRight()->getLeft()->getLeft()->getData();
    Node<Book>* fmj = T2.getRoot();
    cout << fmj->getData() << endl;
    cout << fmj->predecessor()->getData() << endl;
    cout << fmj->successor()->getData() << endl;
    T2.moreAndLess(arr1[2]);

    void (*f_ptr)(Node<Book>*); f_ptr = print;
    cout << "\n-----\nPreorder:";
    T2.PreOrder(T2.getRoot(), f_ptr);
    cout << "\n-----\nInorder:";
    T2.InOrder(T2.getRoot(), f_ptr);
    cout << "\n-----\nPostorder:";
    T2.PostOrder(T2.getRoot(), f_ptr);


    char c; cin >> c;
	return 0;
}