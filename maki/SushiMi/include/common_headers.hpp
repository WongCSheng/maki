/*!*****************************
* 
* \brief: add all header files in this common header 
file so that in all files you will only need to 
"#include "common_headers.hpp"
* 
*********************************/
#pragma once

#include <iostream>

//c++ std
#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <cassert>
#include <ctime>
#include <array>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <span>
#include <bit>
#include <memory>
#include <typeindex>
#include <scoped_allocator>
#include <typeindex>
#include <utility>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <ostream>
#include <sstream>
#include <iterator>
#include <exception>
#include <cmath>
#include <random>
#include <new>
#include <chrono>
#include <string>
#include <cstring>
#include <cctype>
#include <complex>
#include <iterator>

//imgui
#include <../imgui/imgui_impl_opengl3.h>
#include <../imgui/imgui.h>
#include <../imgui/imgui_impl_glfw.h>

//graphics
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <../include/glhelper.h>
#include <../include/glapp.h>



//Serializer
#include <any>

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/reader.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/writer.h>

#include <rttr/type.h>
#include <rttr/type>
#include <rttr/property.h>
#include <rttr/variant.h>
#include <rttr/registration>

#include <fstream>
#include <filesystem>
#include <iostream>

#include "RTTR.h"


//Input 
#include "Keys.h"
#include "Input.h"