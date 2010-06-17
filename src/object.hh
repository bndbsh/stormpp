#ifndef _STORM_OBJECT_HH_
#define _STORM_OBJECT_HH_

#include <boost/intrusive_ptr.hpp>

namespace storm {
/**
 * @brief Base object for managed classes.
 * @author amro
 */
class Object {
public:
	///Initialize _refcount to 0
	Object();
	
	///Increase reference count
	void _ref();
	
	///Decrease reference count
	void _unref();
	
	///@returns reference count
	unsigned int _refs() const;
private:
	///Reference count
	unsigned int _refcount;
};

void intrusive_ptr_add_ref(Object* ref);
void intrusive_ptr_release(Object* ref);

}
#endif
