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
#include <limits>
#include <complex>
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
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <../include/glhelper.h>
#include <../include/glapp.h>
#include <../model.h>
#include <../object.h>
#include <../Camera2D.h>
//Meths lib
#include "vector3.h"
#include "Vector.h"
#include "Matrix.h"

//Serializer
#include <any>

#include <rapidjson.h>
#include <istreamwrapper.h>
#include <filereadstream.h>
#include <reader.h>
#include <prettywriter.h>
#include <writer.h>
#include <stringbuffer.h>
#include <document.h>
#include <stdexcept>               // std::runtime_error
#include <error/error.h>
#include <error/en.h>
#include <stringbuffer.h>

#include <type.h>
#include <property.h>
#include <variant_impl.h>
#include <variant.h>
#include <registration.h>
#include <version.h>

#include <fstream>
#include <filesystem>

#include "RTTR.h"
#include "JSONSerializer.h"


//Input 
#include "Keys.h"
#include "Input.h"

////Collision
//#include "collision.h"