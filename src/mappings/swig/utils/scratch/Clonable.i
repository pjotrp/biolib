%module bpp_clonable
namespace bpp
{

class Clonable
{
	public:
		
		Clonable() {}	
		virtual ~Clonable() {}
	
	public:
		virtual Clonable * clone() const = 0;
};

} //end of namespace bpp.
