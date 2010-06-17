#include "object.hh"

namespace storm {

Object::Object() : _refcount(0) {}

void Object::_ref() {
	_refcount++;
}

void Object::_unref() {
	_refcount--;
}

unsigned int Object::_refs() const {
	return _refcount;
}

void intrusive_ptr_add_ref(Object* ref) {
	ref->_ref();
}

void intrusive_ptr_release(Object* ref) {
	ref->_unref();
	if (ref->_refs() == 0) {
		delete ref;
	}
}

}
