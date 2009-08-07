%module si
%include "std_deque.i"
%include "std_map.i"
%include "std_string.i"
%include "std_vector.i"

%include "cpointer.i"
%include "carrays.i"

%pointer_class(int,intp)
%pointer_class(unsigned int,uintp)
%pointer_class(double,doublep)
%pointer_class(std::string,strp)
%pointer_class(char,charp)
//%pointer_class(std::map<std::string>,mapp)
//%pointer_class(std::ostream,ostreamp)

%template(intVector) std::vector<int>;
%template(uintVector) std::vector<unsigned int>;
%template(doubleVector) std::vector<double>;
%template(strVector) std::vector<std::string>;

%template(intDeque) std::deque<int>;
%template(uintDeque) std::deque<unsigned int>;
%template(doubleDeque) std::deque<double>;
%template(stringDeque) std::deque<std::string>;

%template(intMap) std::map<int,int>;
%template(strMap) std::map<std::string,std::string>;


// This tells SWIG to treat char ** as a special case
%typemap(in) char ** {
  /* Check if is a list */
  if (PyList_Check($input)) {
    int size = PyList_Size($input);
    int i = 0;
    $1 = (char **) malloc((size+1)*sizeof(char *));
    for (i = 0; i < size; i++) {
      PyObject *o = PyList_GetItem($input,i);
      if (PyString_Check(o))
	$1[i] = PyString_AsString(PyList_GetItem($input,i));
      else {
	PyErr_SetString(PyExc_TypeError,"list must contain strings");
	free($1);
	return NULL;
      }
    }
    $1[i] = 0;
  } else {
    PyErr_SetString(PyExc_TypeError,"not a list");
    return NULL;
  }
}

// This cleans up the char ** array we malloc'd before the function call
%typemap(freearg) char ** {
  free((char *) $1);
}
