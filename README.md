PBA vs G2O Times comparator
=======================================================
Compare the execution times of g2o for bundle adjustment and pba.

Getting started
-------------------------------------------------------
Compile both project as standard C++ project.
### Compile G2O
Open a terminal in current project direcory.
Follow these instructions to compile g2o_ba:
```
cd g2o_ba/thirdparty/g2o/
mkdir build
cd build
cmake ..
make
cd ../../..
mkdir build
cd build
cmake ..
make
```
### Compile PBA
Open a terminal in current project directory.
Follow these instructions to compile pba:
```
cd pba/
mkdir build
cd build
cmake ..
make
```

Usage
----------------------------------------------------------
Follow these instuctions to get the times in a `.csv`file:
### Untar input files 
Untar the provided input files inside `inputs/` directory. It the archive had size > 100MB we had splitted it in more parts. To join all the parts use this command:
```
cat archive_name.tar.bz2* > archive_name.tar.bz2
```
for example `cat dubrovnik.tar.bz2* > dubrovnik.tar.bz2` will create the joined archive.

### Launch the script
We provide a script which automatically load all the input files given a dataset and memorize its execution times in a `.csv` file inside the `times/` directory.
The script takes as input the dataset directory name inside `inputs/` directory.
For example to launch the script on the dubrovnik dataset
```
./gettimes.sh dubrovnik
```
When the execution is complete you will fild the files `pba.csv` and `g2o.csv` inside the `times/` directory. Remember to rename these files before launch other simulations or the results will be appendend to these files.

### Use your own dataset
You can use your own dataset just by:
- Get the files in PBA format
- Create a directory inside `inputs/` directory
- Move your file inside this directory
- Launch the script cited above 



