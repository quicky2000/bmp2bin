#include "my_bmp.h"
#include "parameter_manager.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <iostream>
#include <set>
#include <inttypes.h>
#include <queue>

//#define DEBUG
using namespace parameter_manager;

int main(int argc, char ** argv)
{
  std::cout << argc << " parameters" << std::endl ;

  try
    {
      // Defining application command line parameters
      parameter_manager::parameter_manager l_param_manager("dicoplus.exe","--",1);
      parameter_if l_input_file("input_file",false);
      l_param_manager.add(l_input_file);
      
      parameter_if l_nb_line_param("nb_line",true);
      l_nb_line_param.set_text_value("5");
      l_param_manager.add(l_nb_line_param);

      parameter_if l_nb_column_param("nb_column",true);
      l_param_manager.add(l_nb_column_param);
      l_nb_column_param.set_text_value("10");

      parameter_if l_line_height_param("line_height",true);
      l_line_height_param.set_text_value("10");
      l_param_manager.add(l_line_height_param);

      parameter_if l_column_width_param("column_width",true);
      l_column_width_param.set_text_value("5");
	l_param_manager.add(l_column_width_param);
      
      parameter_if l_nb_colors_param("nb_colors",true);
      l_nb_colors_param.set_text_value("2");
      l_param_manager.add(l_nb_colors_param);
      

      // Treating parameters
      l_param_manager.treat_parameters(argc,argv);
      
      if(argc < 2)
	{
	  std::cout << "Error you must provide a list the input file name as parameter" << std::endl ;
	  return(-1);
	}
      lib_bmp::my_bmp l_input_bmp(argv[1]);
      uint32_t l_width = l_input_bmp.get_width();
      uint32_t l_height = l_input_bmp.get_height();
      std::cout << "Image Width = " << l_width << std::endl ;
      std::cout << "Image Heigth = " << l_height << std::endl ;

      uint32_t l_nb_line = l_nb_line_param.get_value<uint32_t>();
      uint32_t l_nb_column = l_nb_column_param.get_value<uint32_t>();
      uint32_t l_column_width = l_column_width_param.get_value<uint32_t>();
      uint32_t l_line_height = l_line_height_param.get_value<uint32_t>();
      uint32_t l_nb_color = l_nb_colors_param.get_value<uint32_t>();
      uint32_t l_nb_bits = log2(l_nb_color);
      std::map<lib_bmp::my_color_alpha,std::string> l_color_codes;
      switch(l_nb_color)
	{
	case 2:
	  break;
	case 4:
	  l_color_codes.insert(std::map<lib_bmp::my_color_alpha,std::string>::value_type(lib_bmp::my_color_alpha(255,255,255,0),"00"));
	  l_color_codes.insert(std::map<lib_bmp::my_color_alpha,std::string>::value_type(lib_bmp::my_color_alpha(255,0,0,0),"11"));
	  l_color_codes.insert(std::map<lib_bmp::my_color_alpha,std::string>::value_type(lib_bmp::my_color_alpha(0,255,0,0),"10"));
	  l_color_codes.insert(std::map<lib_bmp::my_color_alpha,std::string>::value_type(lib_bmp::my_color_alpha(0,0,255,0),"01"));
	  break;
	default:
	  std::cout << "Unsupported number of colors : " << l_nb_color << std::endl ;
	  return(-1);
	}

      uint32_t l_total_nb_bits = l_line_height * l_column_width * l_nb_bits;

      std::cout << "Color nb bits : " << l_nb_bits << std::endl ;
      std::cout << "Total nb bits : " << l_total_nb_bits << std::endl ;

      std::map<std::string,char> l_hex_code;
      l_hex_code.insert(std::map<std::string,char>::value_type("0000",'0'));
      l_hex_code.insert(std::map<std::string,char>::value_type("0001",'1'));
      l_hex_code.insert(std::map<std::string,char>::value_type("0010",'2'));
      l_hex_code.insert(std::map<std::string,char>::value_type("0011",'3'));
      l_hex_code.insert(std::map<std::string,char>::value_type("0100",'4'));
      l_hex_code.insert(std::map<std::string,char>::value_type("0101",'5'));
      l_hex_code.insert(std::map<std::string,char>::value_type("0110",'6'));
      l_hex_code.insert(std::map<std::string,char>::value_type("0111",'7'));
      l_hex_code.insert(std::map<std::string,char>::value_type("1000",'8'));
      l_hex_code.insert(std::map<std::string,char>::value_type("1001",'9'));
      l_hex_code.insert(std::map<std::string,char>::value_type("1010",'A'));
      l_hex_code.insert(std::map<std::string,char>::value_type("1011",'B'));
      l_hex_code.insert(std::map<std::string,char>::value_type("1100",'C'));
      l_hex_code.insert(std::map<std::string,char>::value_type("1101",'D'));
      l_hex_code.insert(std::map<std::string,char>::value_type("1110",'E'));
      l_hex_code.insert(std::map<std::string,char>::value_type("1111",'F'));

      lib_bmp::my_color l_red(255,0,0);

      for(uint32_t l_line = 0; l_line < l_nb_line ; ++l_line)
	{
	  uint32_t l_y_min = 1 + l_line * (l_line_height + 1);
	  for(uint32_t l_column = 0; l_column < l_nb_column ; ++l_column)
	    {

	      // New image
	      uint32_t l_x_min = 1 + l_column * (l_column_width + 1);
	      std::string l_coded;
#ifdef DEBUG
	      std::cout << "Generate object(" << std::hex << l_column << "," << l_line << ")" << std::dec << std::endl ;
	      std:: cout << "Starting from coordinate (" << l_x_min << "," << l_y_min << ")" << std::endl ;
#endif
	      for(uint32_t l_y = l_y_min ; l_y < l_y_min + l_line_height ; ++l_y)
		{
		  for(uint32_t l_x = l_x_min ; l_x < l_x_min + l_column_width ; ++l_x)
		    {
		      lib_bmp::my_color l_black(0,0,0);
		      lib_bmp::my_color_alpha l_color = l_input_bmp.get_pixel_color(l_x,l_y);
#ifdef DEBUG
		      l_color.display();
		      std::cout << " " << (l_color == l_black ? "false" : "true" ) << std::endl ;
#endif
		      if(1 == l_nb_bits)
			{
			  if(l_black == l_color)
			    {
			      l_coded += '1';
			    }
			  else
			    {
			      l_coded += '0';
			    }
			}
		      else
			{
			  std::map<lib_bmp::my_color_alpha,std::string>::const_iterator l_iter = l_color_codes.find(l_color);
			  if(l_color_codes.end() != l_iter)
			    {
			      l_coded += l_iter->second;
			    }
			  else
			    {
			      std::cout << "Unsupported color code : " ;
			      l_color.display();
			      std::cout << " @(" << l_x << "," << l_y << ")" << std::endl ;
			      l_coded += std::string(l_nb_bits,'0');
			    }
			}
		    } 
		}

	      // Add start padding if needed to have integer number of bit quartet
	      size_t l_start_index = l_total_nb_bits % 4;
	      if(l_start_index)
		{
		  l_coded = std::string(4 - l_start_index,'0') + l_coded ;
		}

	      // Convert coded line to hex format
	      std::string l_hex_coded;
	      for(l_start_index = 0; l_start_index < l_coded.size() ; l_start_index = l_start_index + 4)
		{
		  std::string l_substr = l_coded.substr(l_start_index,4);
		  std::map<std::string,char>::const_iterator l_iter = l_hex_code.find(l_substr);
		  if(l_hex_code.end() == l_iter)
		    {
		      throw quicky_exception::quicky_logic_exception("Unsupported bit quartet \"" + l_substr + "\"",__LINE__,__FILE__);
		    }
		  l_hex_coded += l_iter->second;
		}
	      size_t l_pos = l_hex_coded.find_first_not_of("0");
	      if(std::string::npos != l_pos)
		{
		  l_hex_coded = l_hex_coded.substr(l_pos);
		}

	      std::cout << l_line * l_nb_column + l_column <<" => 0x" << std::hex << l_hex_coded << std::dec << std::endl ;
	    }
	}
      std::cout << "Generation successfull" << std::endl ;
    }
  catch(quicky_exception::quicky_runtime_exception & e)
    {
      std::cout << "ERROR : " << e.what() << std::endl ;
      return(-1);
    }
  catch(quicky_exception::quicky_logic_exception & e)
    {
      std::cout << "ERROR : " << e.what() << std::endl ;
      return(-1);
    }
}
