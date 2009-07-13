%module bpp_stringtokenizer
%{
#include <deque>
#include <string>
#include "StringTokenizer.h"
%}

%include "std_deque.i"
%include "std_string.i"
%include "Exceptions.i"

using namespace std;

namespace bpp
{

class StringTokenizer
{
	public:
		StringTokenizer(const string & s, const string & delimiters = " \t\n\f\r", bool solid = false, bool allowEmptyTokens = false);
		virtual ~StringTokenizer();
		string nextToken() throw (Exception);
		bool hasMoreToken() const;
		int numberOfRemainingTokens() const;
		string getToken(unsigned int pos) const;
		const deque<string> & getTokens() const;
		void removeEmptyTokens();

};

} //end of namespace bpp.
