#include <pybind11/pybind11.h>
#include<pybind11/operators.h>
#include <pybind11/stl.h>
#include "image.hpp"

namespace py = pybind11;

PYBIND11_MODULE(_image, m) {
     py::class_<GaussianKernel>(m, "GaussianKernel")
        .def(py::init<const int &, const float &>())
        .def_readonly("matrix", &GaussianKernel::matrix)
        .def("__getitem__", [](GaussianKernel &m, std::pair<int, int>i){
            return m(i.first, i.second);
        }, py::is_operator())
        .def_readonly("radius", &GaussianKernel::radius)
        .def_readonly("sigma", &GaussianKernel::sigma)
        .def_readonly("dim", &GaussianKernel::dim)
        .def("PrintKernel", &GaussianKernel::PrintKernel)
        .def("Calculation", &GaussianKernel::Calculation);
        

    py::class_<Image>(m, "Image")
        .def(py::init<const std::string &, const std::string &>())
        .def("__getitem__", [](Image &m, std::pair<int, int>i){
            return m(i.first, i.second);
        }, py::is_operator())
        .def_readonly("height", &Image::height)
        .def_readonly("width", &Image::width)
        .def("image_load", &Image::image_load)
        .def("GaussianFilter", &Image::GaussianFilter)
        .def("to_grey", &Image::to_grey)
        .def("SobelFilter", &Image::SobelFilter)
        .def("image_write", &Image::image_write);
}