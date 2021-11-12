# MurtyAlgorithm
Tis a python wrapper for a C++ implementation of Miller's optimized Murty Algorithm from https://github.com/fbaeuerlein/MurtyAlgorithm

Install

```
git clone https://github.com/fbaeuerlein/MurtyAlgorithm
cd MurtyAlgorithm
{copy setup.py and wrapper.cpp to the repo}
python setup.py install
```

Usage

```
import MurtyMiller.nbest_la as nbla
a = np.array([[0.1,0.2,0.3],[0.1,0.4,0.2]])
num_solution = 2
sol = nbla(a,num_solution) #num_solution x 2 x min(row,col)
```

In wrapper.cpp, I try to ensure same behavior as scipy.optimize.linear_sum_assignment for top1 assignment solution, supporting arbitrary size of input matrix. 
For scipy.optimize.linear_sum_assignment, the return value is (row_idx,col_idx) -> list(np.array<1xm>,np.array<1xm>). In my case, it's (n_solution (row_idx, col_idx)) -> np.array<n, 2, m> in a single numpy array. 





