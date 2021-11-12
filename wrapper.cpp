#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <Python.h>
#include "Miller.h"
using namespace std;
namespace py = pybind11;

template<typename T> std::vector<int> argsort(const std::vector<T>& array)
{
	const int array_len(array.size());
	std::vector<int> array_index(array_len, 0);
	for (int i = 0; i < array_len; ++i)
		array_index[i] = i;

	std::sort(array_index.begin(), array_index.end(),
		[&array](int pos1, int pos2) {return (array[pos1] < array[pos2]);});

	return array_index;
}

py::array murty_solve(py::array arr, int kbest){
    py::array_t<double_t> casted_array = py::cast<py::array>(arr);
    auto arr_obj_prop = casted_array.request();
    //initialize values
    typedef MurtyMiller<double>::Edges Edges;

    double *vals = (double*) arr_obj_prop.ptr;
    auto shape_1 = arr_obj_prop.shape[0];
    auto shape_2 = arr_obj_prop.shape[1];
    
    auto max_shape = (shape_2 >= shape_1) ? shape_2 : shape_1;
    auto min_shape = (shape_2 < shape_1) ? shape_2 : shape_1; 

    MurtyMiller<double>::WeightMatrix c_ij(min_shape, max_shape);    
    
    for(auto i = 0; i < shape_1; i++)
    {
        for(auto j = 0; j < shape_2; j++)
        {  
            auto val = vals[i*shape_2 + j];
            if (val < 0) val = -val;
            if (shape_2 < shape_1){ c_ij(j,i) = val;}
            else {c_ij(i,j) = val;}
        }
    } 

    //c_ij /= c_ij.maxCoeff();
    std::vector<Edges> solutions = MurtyMiller<double>::getMBestAssignments(c_ij, kbest);
    vector<vector<vector<int>>> vect_arr(solutions.size(), vector<vector<int>>(2,vector<int>()));
    
    auto idx_sol = 0; auto sr = 0; auto ed = 1;
    if (shape_2 < shape_1){ sr = 1; ed = 0;}
    
    for ( const auto & s : solutions )
    {   
        for ( const auto & e : s )
        {           
            vect_arr[idx_sol][sr].push_back(int(e.x));
            vect_arr[idx_sol][ed].push_back(int(e.y));
        }

        if (shape_2 < shape_1) {
            std::vector<int> idx_arr = argsort(vect_arr[idx_sol][ed]); 
            std::vector<int> reord_ed_arr;
            std::vector<int> reord_sr_arr;

            for (unsigned int i = 0; i < idx_arr.size(); i++){
                reord_ed_arr.push_back(vect_arr[idx_sol][ed][idx_arr[i]]);
                reord_sr_arr.push_back(vect_arr[idx_sol][sr][idx_arr[i]]);
            }
            vect_arr[idx_sol][sr] = reord_sr_arr;
            vect_arr[idx_sol][ed] = reord_ed_arr;
        }
        idx_sol ++;
    }
    
    //cout<<min_shape<<' '<<max_shape<<endl;
    py::array ret = py::cast(vect_arr);
    return ret;
}

PYBIND11_MODULE(MurtyMiller, m) {
    m.doc() = "pybind11 module for iterating over generations";
    m.def("nbest_la", &murty_solve,
      "the function which loops over a numpy array");
}


