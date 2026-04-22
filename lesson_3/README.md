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
### New Write to file code
Copy these new code block to your code to write to file, somewhere after the initialization loops.
```cpp
// Write final membrane positions to file
    std::ofstream membraneFile("membrane.dat");
    for (int i = 0; i < N_membrane; i++) {
        membraneFile << membraneX[i] << " "
                     << membraneY[i] << " "
                     << membraneZ[i] << "\n";
    }
    membraneFile << "\n";
``
```cpp
// Write final interior positions to file
    std::ofstream interiorFile("interior.dat");
    for (int i = 0; i < N_interior; i++) {
        interiorFile << interiorX[i] << " "
                     << interiorY[i] << " "
                     << interiorZ[i] << "\n";
    }
    interiorFile << "\n";
```
---
# Euler Algorithm
Now it's time to add motion via the Euler Algorithm. The Euler method is a simple way to update a quantity step by step in time. Mathematically, it is a discrete approximation of an integration in time. The basic idea is

```
new value = old value +rate
```

We will need to do this for each component of the location of the node, so there will be a Euler method for each `x`, `y`, `z` direction. The `time step` is predefined and you can change it to increase or decrease the duration of the simulation. 

Add the following code to your variable section.

```cpp
// Euler motion parameters
    const int N_steps = 1000;
    const double dx = 0.01;
    const double dy = 0.0;
    const double dz = 0.0;
```
Based on these variables, which direction do you think the cell will move?

## Time Step
Here is the plan. For each time step, we will add the rate to each component of the location of the node. We will do this for both the membrane and interior nodes. We will also write to file the new location of the nodes. Copy this after the the initialization and writing to file.
```cpp
// Time stepping loop
for (int step = 0; step < N_steps; step++) {

    // Update membrane node locations
    for (int i = 0; i < N_membrane; i++) {
        membraneX[i] += dx;
        membraneY[i] += dy;
        membraneZ[i] += dz;
    }

    // Update interior node locations
    for (int i = 0; i < N_interior; i++) {
        interiorX[i] += dx;
        interiorY[i] += dy;
        interiorZ[i] += dz;
    }

    // Write membrane nodes for this time step
    for (int i = 0; i < N_membrane; i++) {
        membraneFile << membraneX[i] << " "
                        << membraneY[i] << " "
                        << membraneZ[i] << "\n";
    }
    membraneFile << "\n";

    // Write interior nodes for this time step
    for (int i = 0; i < N_interior; i++) {
        interiorFile << interiorX[i] << " "
                        << interiorY[i] << " "
                        << interiorZ[i] << "\n";
    }
    interiorFile << "\n";
}
```
# Visualize Motion
Let's see the cell move! You will notice that this week's lesson comes with a `.gnu` file. This is just a document with a script for `gnuplot`. So instead of entering the script manually, you can run the `.gnu` file in `gnuplot`.

```gnuplot
load 'plot_animation.gnu'
```
---
