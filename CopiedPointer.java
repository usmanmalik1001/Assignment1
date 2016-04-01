#include <iostream>
#include <memory>

using namespace std;
class StringBuffer{

private:
	char* _strbuf;                                  //buffer to store the original string
	int _length;									//length of the string

public:
	StringBuffer()
	{
		this->_strbuf = "";
		this->_length = 0;
	}//default constructor

	~StringBuffer()
	{
		delete[] this->_strbuf;
	}
	//destructor; would delete the allocated buffer

	StringBuffer(const StringBuffer& newString)
	{
		this->_strbuf = new char[newString.length()];
		this->_length = newString.length();
		//copy the passed string into internal buffer
		for (int i = 0; i < newString.length(); i++)
		{
			this->_strbuf[i] = newString._strbuf[i];
		}
	}//constructor for shallow copying

	StringBuffer(char* newString, int length)
	{
		this->_length = length;
		delete[] this->_strbuf;
		_strbuf = new char[length];
		for (int i = 0; i < length; i++)
		{
			this->_strbuf[i] = newString[i];
		}
	}//constructor to convert a char* to StringBuffer

	char charAt(int index) const
	{
		return this->_strbuf[index];
	}//returns the character at the passed index

	int length() const
	{
		return this->_length;
	}//returns the length of the buffer

	void revSmartCopy(char* newString) {
		int it = 0;
		while (it < _length) {
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

	}//allocates memory for the string, according to the passed character length

	void smartCopy(char* newString, int length) {
		//(this->_length == length)?:this->_length=length;
		this->_length = length;
		int it = 0;
		while (it < length) {
			_strbuf[it] = newString[it];
			it++;
		}
	}

	void append(char c)
	{
		auto_ptr<StringBuffer> newdata(new StringBuffer);
		newdata.get()->reserve(this->_length + 1);
		newdata.get()->smartCopy(this->_strbuf, this->_length + 1);
		this->_strbuf = newdata.release()->_strbuf;
		//copy the new character at the end of this string
		this->_strbuf[this->_length] = c;
		_length++;
	}//appends a single character at the end

	StringBuffer& operator=(const StringBuffer& newBuffer)
	{
		this->_strbuf = new char[newBuffer.length()];
		this->_length = newBuffer.length();
		//copy the passed string into internal buffer
		for (int i = 0; i < newBuffer.length(); i++)
		{
			this->_strbuf[i] = newBuffer._strbuf[i];
		}
		return *this;
	}
};

int main()
{
	StringBuffer str("Hello", 5);
	StringBuffer str1(str);

	str1.append('t');
	str.append('a');

	str = str1;

	cout << str.charAt(4) << endl;
	system("pause");
	return 0;
}
