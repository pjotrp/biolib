%module bpp_maptools
%{
#include "MapTools.h"
using namespace bpp;
%}

%include "std_map.i"
%include "std_vector.i"

using namespace std;

class MapTools
{
	public:
		template <class Key, class T, class Cmp >
		static vector<Key> getKeys(const map<Key, T, Cmp> & myMap);
		
		template <class Key, class T >
		static vector<Key> getKeys(const map<Key, T> & myMap);
		
		template <class Key, class T, class Cmp >
		static vector<T> getValues(const map<Key, T, Cmp> & myMap);

		template <class Key, class T >
		static vector<T> getValues(const map<Key, T> & myMap);
};
