#include <mpi.h>

#include <pybind11/pybind11.h>
#define MPI4PY_LIMITED_API 1
#define MPI4PY_LIMITED_API_SKIP_MESSAGE 1
#define MPI4PY_LIMITED_API_SKIP_SESSION 1
#include <mpi4py/mpi4py.h>
namespace py = pybind11;

template<typename T> T py2mpi(py::object);
template<> MPI_Comm py2mpi(py::object obj)
{
  PyObject *pyobj = obj.ptr();
  MPI_Comm *mpi_ptr = PyMPIComm_Get(pyobj);
  if (!mpi_ptr) throw py::error_already_set();
  return *mpi_ptr;
}

static void hw_sayhello(py::object py_comm)
{
  MPI_Comm comm = py2mpi<MPI_Comm>(py_comm);
}


int add(int i, int j) { return i + j; }


PYBIND11_MODULE(_core, m) {
  m.doc() = R"pbdoc(
      Pybind11 example plugin
      -----------------------
      .. currentmodule:: python_example
      .. autosummary::
         :toctree: _generate
         add
         subtract
  )pbdoc";

  m.def("add", &add, R"pbdoc(
      Add two numbers
      Some other explanation about the add function.
  )pbdoc");

  m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(
      Subtract two numbers
      Some other explanation about the subtract function.
  )pbdoc");
}
