#pragma once
// compatibility funcs for boost::python ad pybind11
#ifdef WOO_PYBIND11
	#define add_property_readonly def_property_readonly
	#define add_property def_property
	#define add_static_property def_property_static
	// #define staticmethod(name) def("__" name,[](const auto& o){ return 0; })
	#define staticmethod(name)
	//def("__boost_python_deprecated_filler_" name,[](const auto& o){ return 0; })
	#define WOO_PY_DICT_CONTAINS(dict,key) dict.contains(key)
	// pybind11 needs args separated
	#define WOO_PY_ARGS(...) __VA_ARGS__
	#define WOO_PY_GETTER_COPY(func) py::cpp_function(func,py::return_value_policy::copy)
	#define WOO_PY_EXPOSE_COPY(classT,attr) [](const classT& o){return o.*(attr);},py::return_value_policy::copy
	#define WOO_PY_RETURN__TAKE_OWNERSHIP py::return_value_policy::take_ownership
	#define WOO_PY_STATICMETHOD(name)
	#include<pybind11/pybind11.h>
	namespace pybind11{
		// emulate boost::python::extract
		template<typename T>
		struct __attribute__((visibility("hidden"))) extract{
			const object& obj;
			extract(const object& obj_): obj(obj_){}
			bool check(){ return isinstance<T>(obj); }
			T operator()() const { return cast<T>(obj); }
			operator T() const { return cast<T>(obj); }
		};
		// boost::python::ptr does not seem to be neede in pybind11 when casting from raw pointer
		// make it no-op
		template<typename T>
		T* ptr(T* p){ return p; }
		// bp::import → py::module::import
		module import(const char *name){ return module::import(name); }
		// bp::scope → py::module
		typedef args args_;
		typedef module module_;
	}
#else
	#define def_property_readonly add_property
	#define def_property add_property
	#define def_property_static add_static_property
	#define add_property_readonly add_property
	#define def_static def
	#define WOO_PY_GETTER_COPY(func) py::make_function(func,py::return_value_policy<py::return_by_value>())
	#define WOO_PY_EXPOSE_COPY(classT,attr) py::make_getter(attr,py::return_value_policy<py::return_by_value>())
	#define WOO_PY_DICT_CONTAINS(dict,key) dict.has_key(key)
	// boost::python wants args to be grouped in parens
	#define WOO_PY_ARGS(...) (__VA_ARGS__)

	#define WOO_PY_STATICMETHOD(name) .staticmethod(name)

	#define WOO_PY_RETURN__TAKE_OWNERSHIP py::return_value_policy<py::manage_new_object>()
	namespace boost { namespace python {
		template<typename T> object cast(const T& o){ return object(o); }
		template<typename T> T cast(object& o){ return extract<T>(o)(); }
		template<typename T> bool isinstance(object& o){ return extract<T>(o).check(); }
		// for raw arguments
		typedef dict kwargs;
		typedef tuple args_;
		typedef scope module_;
		#if 0
			// pybind11 exposes import as py::module::import, mimick here
			namespace module{
				py::object import(const char* name){ return ::boost::python::import(name); }
			}
		#endif
	}};
#endif
