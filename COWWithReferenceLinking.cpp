#include <memory>
#include <iostream>

using namespace std;

class StringBuffer
{
private:
	char* _strbuf;
	int _length;
	StringBuffer *next;
	StringBuffer *prev;

public:
	//default constructor

	StringBuffer()
	{
		this->_strbuf = "";
		this->_length = 0;
	}
	//destructor

	~StringBuffer()
	{
		if (this->next == NULL && this->prev == NULL)
			delete[] this->_strbuf;
		else if (this->next != NULL)
			this->next->prev = NULL;
		else if (this->prev != NULL)
			this->prev->next = NULL;
	}

	//copy a const StringBuffer into this string

	StringBuffer(StringBuffer& newString)
	{
		this->_strbuf = new char[newString.length()];
		this->_length = newString.length();
		//copy the passed string into internal buffer
		this->smartCopy(newString._strbuf, _length);
		this->next = &newString;
		newString.prev = this;
	}

	//copy a char* into your string

	StringBuffer(char* newString, int length)
	{
		delete[] this->_strbuf;
		this->_strbuf = new char[length];
		for (int i = 0; i < length; i++)
		{
			this->_strbuf[i] = newString[i];
		}
		this->_length = length;
		this->next = NULL;
		this->prev = NULL;
			//Should I delete the string passed by the user?
			//delete[] newString;
	}

	//make a smart copy of the StringBuffer into the callee StringBuffer

	void smartCopy(StringBuffer* newString)
	{
		int shorterLength = 0;
		(this->_length < newString->_length) ? shorterLength = this->_length : shorterLength = newString->_length;
		int it = 0;
		while (it < shorterLength)
		{
			_strbuf[it] = newString->_strbuf[it];
			it++;
		}
	}

	//make a smart copy of the char* into this string

	void smartCopy(char* newString, int length)
	{
		//(this->_length == length)?:this->_length=length;
		this->_length = length;
		int it = 0;
		while (it < length)
		{
			_strbuf[it] = newString[it];
			it++;
		}
	}
	//make a smart copy of this string into the passed string

	void revSmartCopy(char* newString)
	{
		int it = 0;
		while (it < _length)
		{
			newString[it] = _strbuf[it];
			it++;
		}
	}

	void reserve(int n)
	{
		if (_length < n) {
			int newlength = n; //max(_length*2,n);
			char* newbuf = new char[newlength];
			//copy contents of the stored string in the new buffer
			this->revSmartCopy(newbuf);

			//return stuff from the new buffer to the stored buffer
			//delete[] this->_strbuf;
			this->_strbuf = newbuf;
			this->_length = newlength;
		}
	}

	//append a character at the end of this String, which has already made a reservation
	//Main Assumption: the length has been allocated but not yet utilized and the 
	//length counter has not been increased.

	void append(char c)
	{
		auto_ptr<StringBuffer> newdata(new StringBuffer);
		newdata.get()->reserve(this->_length + 1);
		newdata.get()->smartCopy(this->_strbuf, this->_length + 1);
		this->_strbuf = newdata.release()->_strbuf;
		//copy the new character at the end of this string
		this->_strbuf[this->_length] = c;
		_length++;
	}

	//get length of the string

	int length() const
	{
		return this->_length;
	}

	//get character at index if it is less than length

	char charAt(int index) const
	{
		if (index < _length)
			return _strbuf[index];
		else
			cout << "Index out of bound";
	}
};

void main()
{
	StringBuffer str("Hello", 5);
	StringBuffer str1(str);

	str.append('l');
	cout << str.charAt(5) << endl;
	cout << str1.charAt(4) << endl;
	system("pause");
}
