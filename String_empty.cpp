

#include <iostream>

using namespace std;

class BaseString
{
protected:
	char* p;
	int len;
	int capacity;
public:
	BaseString(char* ptr)
	{

		cout<<"\nBase Constructor 1\n";
        int i=0;
        for (;ptr[i]!='\0';i++);
        len=i;
        capacity = (len>256) ? len+1 : 256;
        p = new char[capacity];
        for (i=0;ptr[i]!='\0';p[i]=ptr[i],i++);
        p[len]='\0';

	}

    BaseString(const char* ptr)
    {
        cout<<"\nBase Constructor 1\n";
        int i=0;
        for (;ptr[i]!='\0';i++);
        len=i;
        capacity = (len>256) ? len+1 : 256;
        p = new char[capacity];
        for (i=0;ptr[i]!='\0';p[i]=ptr[i],i++);
        p[len]='\0';
    }

	BaseString(int Capacity = 256)
	{
		cout<<"\nBase Constructor 0\n";
		capacity = Capacity;
		p = new char[capacity];
		len = 0;
        capacity=0;
        p=NULL;
	}

	~BaseString()
	{
		cout<<"\nBase Destructor\n";
		if(p!=NULL)
			delete[] p;
		len = 0;
	}

	int Length() {return len;}
	int Capacity() { return capacity; }
	//char* get() {return p;}
	char& operator[](int i) {return p[i];}


	BaseString& operator=(BaseString& s)
	{
		cout<<"\nBase Operator = \n";
        capacity=s.capacity;
        len=s.len;

		
		return *this;
	}

	BaseString(BaseString& s)
	{
		cout<<"\nBase Copy Constructor\n";
        capacity=s.capacity;
        len=s.len;
        p=new char [capacity];
        for (int i=0;i<=len;p[i]=s.p[i],i++);
		
	}

	virtual void print()
	{
		int i=0;
		while(p[i]!='\0')
		{
			cout<<p[i];
			i++;
		}
	}

    virtual int IndexOf(char c, int start=0){
        if (start>len || len==0) return -1;
        /*for (int i=start; p[i]!='\0';  i++){
            if (p[i]==c)
                return i;*/

        for (char* p1=p; *p1; *p1++){
            if (*p1==c)
                return p1-p;
        }
        return -1;

    }
};

class String:public BaseString{
public:
    String(const char* str): BaseString(str) {}
    String(): BaseString(){}
    ~String() {}

    String(String& s)
    {
        cout<<"\nString Copy Constructor\n";
        capacity=s.capacity;
        len=s.len;
        p=new char [capacity];
        for (int i=0;i<=len;p[i]=s.p[i],i++);

    }

    virtual int IndexOf(char c, int start=0){
        if (start==0) start=len-1;
        char* p1=&p[len-1];
        if (len==0 || start>=len) return -1;
        for (; p1>=p; *p1--){
            if (*p1==c)
                break;
        }
        return p1-p;
    }
    bool IsPalindrome(){
        char* p1=p;
        char* p2=&p[len-1];
        while (p1<p2){
            if (*p1!=*p2) return false;
            p1++;
            p2--;
        }
        return true;
    }

    void copy(char* sourse, char* dest){
        while ((*sourse++=*dest++));
    }


    //Вариант 7.Получить символ, который повторяется наибольшее количества раз. Если таких несколько, то вернуть массив из этих символов
    virtual String Max_Count(){
        int *mas=new int[127];
        for (int i=0;i<len;i++){

            mas[(p[i])]++;
        }
        int max_count=0;
        for (int i=0; i<127;i++){
            max_count=max(max_count,mas[i]);
        }
        int count_max=0;
        for (int i=0; i<127;i++){
            if (mas[i]==max_count){count_max++;}
        }
        String res;
        res.len=count_max;
        res.capacity=res.len+1;
        res.p = new char [res.capacity];
        int j=0;
        for (int i=0;i<127;i++){
            if (mas[i]==max_count){
                res.p[j]=char(i);
                j++;
            }

        }
        delete[] mas;
        return res;

    }

};

int main()
{
	if (true)
	{
		String s("testtssrrr");
		s.print();

		String s1 = s;
        String s2(s1);//Конструктор копий
        s1.print();cout<<" ---Проверка оператора =";
        (s.Max_Count()).print();cout<<" ---Вариант 7, Строка(массив) элеметов наиболее часто встречающися в строке";

	}
	char c; cin>>c;
	return 0;
}

