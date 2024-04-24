/*
MIT License

Copyright (c) 2024 Leonid Rodniansky

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <string>
#include "lru8.h"

int main()
{

	LRDN::LRU8<std::uint64_t,char> _data;	// Key type std::uint64_t.

	_data[1] = '1';
	_data[2] = '2';
	_data[3] = '3';
	_data[4] = '4';
	_data[5] = '5';
	_data[6] = '6';
	_data[7] = '7';
	_data[8] = '8';	
	_data[9] = '9';		// element 1 evicted.
	_data[10] = 'A';	// element 2 evicted.

	char l1 = _data[5];	// Value '5'.
	char l2 = _data[10];	// Value 'A'.
	
	char &l3 = _data[11];	// Reference to empty value. Element 3 evicted. Element 11 inserted.
	l3 = 'B';		// Now _data[11] == 'B'.

	if (!_data.exists(1))	// Key 1 does not exist because element 1 was previously evicted.
		printf("_data[1] does not exist.\n");

	char &l4 = _data[1];	// Reference to empty value. Element 4 evicted. Element 1 inserted.
	l4 = 'C';		// Now data[1] == 'C'.

	if (_data.exists(1))	// Key 1 exists. Element 1 was inserted before.
		printf("_data[1] exists.\n");

	// _data[1] == 'C', _data[5] == '5', _data[10] == 'A', _data[11] == 'B'
	printf("_data[1]=%c,_data[5]=%c, _data[10]=%c, data[11]=%c\n",_data[1], l1, l2,_data[11]);


	LRDN::LRU8<std::string, int> _strings;	// Key type std::string.

	_strings["one"] = 1;		// Element with key "one" is in LRU with value 1.
	_strings["one"] = 2;		// Same element with key "one" is in LRU with value 2.
	int n1 = _strings["one"];	// Get from LRU.

	printf("_strings[\"one\"]=%d\n",n1);	// n1 == 2

	return 0;
}


