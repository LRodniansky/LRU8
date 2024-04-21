#include <string>
#include "lru8.h"

int main()
{

	LRDN::LRU8<uint64_t,char> _data;

	_data[1] = '1';
	_data[2] = '2';
	_data[3] = '3';
	_data[4] = '4';
	_data[5] = '5';
	_data[6] = '6';
	_data[7] = '7';
	_data[8] = '8';
	_data[9] = '9';
	_data[10] = 'A';

	char l1 = _data[5];
	char l2 = _data[10];
	
	char &l3 = _data[11];
	l3 = 'B';

	if (!_data.exists(1))
		printf("_data[1] does not exist.\n");

	char &l4 = _data[1];
	l4 = 'C';

	if (_data.exists(1))
		printf("_data[1] exists.\n");

	printf("_data[1]=%c,_data[5]=%c, _data[10]=%c, data[11]=%c\n",_data[1], l1, l2,_data[11]);


	LRDN::LRU8<std::string, int> _strings;

	_strings["one"] = 1;
	_strings["one"] = 2;
	int n1 = _strings["one"];

	printf("_strings[\"one\"]=%d\n",n1);

	return 0;
}


