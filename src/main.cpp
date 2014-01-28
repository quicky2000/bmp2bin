#include "my_bmp.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>

int main(int argc, char ** argv)
{
  std::cout << argc << " parameters" << std::endl ;
  if(argc != 2)
    {
      std::cout << "Error you must provide a list the input file name as parameter" << std::endl ;
      exit(-1);
    }
  my_bmp l_input_bmp(argv[1]);
  uint32_t l_width = l_input_bmp.get_width();
  uint32_t l_height = l_input_bmp.get_height();
  std::cout << "Width = " << l_width << std::endl ;
  std::cout << "Heigth = " << l_height << std::endl ;
}
