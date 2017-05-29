Bmp2bin
=======

Utility to convert content of a BMP file to hexadecimal representation usable to load a memory in Xilinx FPGA

Continuous integration with [Travis-Ci](https://travis-ci.org/quicky2000/bmp2bin) : ![Build Status](https://travis-ci.org/quicky2000/bmp2bin.svg?branch=master)

License
-------
Please see [LICENSE](LICENSE) for info on the license.

Build
-----

Build process is the same used in [Travis file](.travis.yml)
Reference build can be found [here](https://travis-ci.org/quicky2000/bmp2bin)

```
MY_LOCATION=`pwd`
echo $MY_LOCATION
mkdir ../repositories
cd ..
mv $MY_LOCATION repositories
QUICKY_REPOSITORY=`pwd`/repositories
export QUICKY_REPOSITORY
MY_LOCATION=`pwd`
echo $MY_LOCATION
cd $MY_LOCATION/repositories
git clone https://github.com/quicky2000/quicky_tools.git
git clone https://github.com/quicky2000/quicky_exception.git
git clone https://github.com/quicky2000/lib_bmp.git
git clone https://github.com/quicky2000/parameter_manager.git
git clone https://github.com/quicky2000/quicky_utils.git
cd quicky_tools/setup
. setup.sh
cd $MY_LOCATION
chmod a+x repositories/quicky_tools/bin/*
mkdir build
cd build
generate_makefile bmp2bin
make
```



