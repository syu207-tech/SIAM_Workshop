# Week 3: Adding Psuedo-Motility 
Welcome to Week 3.

Last week we initialized the cell membrane nodes and internal nodes. This week we will make the cell "move". Before we get there however, we need to makes some changes to our code.

# Add Vector library
In the previous code, a node was created and directly written to file. In order to interact with the node, we first need to store it in memory using vectors. In order to use vectors in `c++`, you first need to add the vector header. Add the following code near the top of your code.

```cpp
#include <vector>
```
---
## What is a Vector?
You can think of a vector like a dynamic list. You can use it to store values of the same type. For our code, we will like to store the location for each node by their coordinates. Since we will eventually move in 3D, we will need to store the `x`, `y`, `z` coordinates of each nodes and since we have membrane and internal nodes, we will need 6 total vectors (for now the `z` coordinates will be left as all 0's). Copy the following code into your variable section, usually underneath the `const` variables section.

```cpp
std::vector<double> membraneX, membraneY, membraneZ;     // Vectors for membrane node positions
std::vector<double> interiorX, interiorY, interiorZ;     // Vectors for interior node positions
```
This creates an empty vector of size 0. To add values to the vector, we will use the `push_back` function from the vector class. For example, the following code will first create a type `double` variable `x` with value `1`, assign it to the first vector in `membraneX` vector, then add `1` to `x` and then assign that sum to the second index of `membraneX`.

```cpp
double x = 1.0;
membraneX.push_back(x);
x = ++x;
membraneX.push_back(x);
```
You can access a specific node by adding an index `[i]` after the vector name. Also In `c++`, indexes start at 0. In this following example, we have the `(x,y,z)` location of the 21'st membrane node.
```cpp
(membraneX[22], membraneY[22], membraneZ[22])
```
---
## Changing Building the Nodes
Make the following changes inside the for loops for creating the membrane nodes and creating the interior nodes.

delete
```cpp
membraneFile << x << " " << y << " " << z << "\n";
```
add
```cpp
membraneX.push_back(x);
membraneY.push_back(y);
membraneZ.push_back(z);
```
Similarly,
delete
```cpp
interiorFile << x << " " << y << " " << z << "\n";
```
add
```cpp
interiorX.push_back(x);
interiorY.push_back(y);
interiorZ.push_back(z);
```
We will write to file later.
