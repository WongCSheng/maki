#pragma once

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

#include <rttr/type.h>
#include <rttr/property.h>
#include <rttr/variant.h>
#include <rttr/registration.h>

#include <fstream>
#include <filesystem>

#include "../Engine/Serialiser/JSONSerializer.h"

#include "../Engine/Serialiser/RTTR.h"
